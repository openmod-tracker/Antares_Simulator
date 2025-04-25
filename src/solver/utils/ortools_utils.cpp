/*
** Copyright 2007-2024, RTE (https://www.rte-france.com)
** See AUTHORS.txt
** SPDX-License-Identifier: MPL-2.0
** This file is part of Antares-Simulator,
** Adequacy and Performance assessment for interconnected energy networks.
**
** Antares_Simulator is free software: you can redistribute it and/or modify
** it under the terms of the Mozilla Public Licence 2.0 as published by
** the Mozilla Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** Antares_Simulator is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** Mozilla Public Licence 2.0 for more details.
**
** You should have received a copy of the Mozilla Public Licence 2.0
** along with Antares_Simulator. If not, see <https://opensource.org/license/mpl-2-0/>.
*/
#include "include/antares/solver/utils/ortools_utils.h"

#include <filesystem>
#include <optional>
#include <ortools/math_opt/cpp/parameters.h>
#include <spx_constantes_externes.h>

#include <boost/algorithm/string/join.hpp>

#include <antares/exception/LoadingError.hpp>
#include <antares/logs/logs.h>
#include "antares/antares/Enum.hpp"
#include "antares/optimization-options/options.h"
#include "antares/solver/utils/basis_status.h"
#include "antares/solver/utils/named_problem.h"

using namespace operations_research;

std::string generateTempPath(const std::string& filename)
{
    namespace fs = std::filesystem;
    std::ostringstream tmpPath;
    tmpPath << fs::temp_directory_path().string() << Yuni::IO::SeparatorAsString << filename;
    return tmpPath.str();
}

void removeTemporaryFile(const std::string& tmpPath)
{
    namespace fs = std::filesystem;
    bool ret = false;
    try
    {
        ret = fs::remove(tmpPath);
    }
    catch (fs::filesystem_error& e)
    {
        Antares::logs.error() << e.what();
    }
    if (!ret)
    {
        Antares::logs.warning() << "Could not remove temporary file " << tmpPath;
    }
}

void ORTOOLS_EcrireJeuDeDonneesLineaireAuFormatMPS(MPSolver* solver,
                                                   Antares::Solver::IResultWriter& writer,
                                                   const std::string& filename)
{
    // 0. Logging file name
    Antares::logs.info() << "Solver OR-Tools MPS File: `" << filename << "'";

    // 1. Determine filename
    const auto tmpPath = generateTempPath(filename);

    // 2. Write MPS to temporary file
    solver->Write(tmpPath);

    // 3. Copy to real output using generic writer
    writer.addEntryFromFile(filename, tmpPath);

    // 4. Remove tmp file
    removeTemporaryFile(tmpPath);
}

const std::map<std::string, struct OrtoolsUtils::SolverNames> OrtoolsUtils::mpSolverMap = {
  {"xpress", {"xpress_lp", "xpress"}},
  {"sirius", {"sirius_lp", std::nullopt}}, // only allowed in LP (MIP only supports binaries)
  {"coin", {"clp", "cbc"}},
  {"glpk", {"glpk_lp", "glpk"}},
  {"scip", {std::nullopt, "scip"}}, // SCIP only supports MIPs
  {"highs", {"highs_lp", "highs"}},
  {"pdlp", {"pdlp", std::nullopt}}}; // PDLP only supports LPs

// TODO: enable xpress when using ortools >= 9.12: {"xpress", math_opt::SolverType::kXpress}
const std::map<std::string, math_opt::SolverType> OrtoolsUtils::mathoptSolverMap = {
  {"pdlp", math_opt::SolverType::kPdlp},
  {"scip", math_opt::SolverType::kGscip}};

std::list<std::string> availableLinearSolversList()
{
    std::list<std::string> result;

    for (const auto& solverName: OrtoolsUtils::mpSolverMap)
    {
        MPSolver::OptimizationProblemType solverType;
        if (solverName.second.LPSolverName.has_value())
        {
            MPSolver::ParseSolverType(solverName.second.LPSolverName.value(), &solverType);
        }
        else
        {
            MPSolver::ParseSolverType(solverName.second.MIPSolverName.value(), &solverType);
        }

        if (MPSolver::SupportsProblemType(solverType))
        {
            result.push_back(solverName.first);
        }
    }
    return result;
}

std::list<std::string> availableQuadraticSolversList()
{
    std::list<std::string> result;
    // Sirius is supported, but not through mathopt
    result.push_back("sirius");
    for (const auto& solverName: OrtoolsUtils::mathoptSolverMap)
    {
        result.push_back(solverName.first);
    }
    return result;
}

std::string toString(const std::list<std::string>& solverList)
{
    return boost::algorithm::join(solverList, ",") + ".";
}

static std::optional<std::string> translateSolverName(const std::string& solverName, bool isMip)
{
    if (!OrtoolsUtils::mpSolverMap.contains(solverName))
    {
        return {};
    }
    const auto& names = OrtoolsUtils::mpSolverMap.at(solverName);
    if (isMip)
    {
        return names.MIPSolverName;
    }
    else
    {
        return names.LPSolverName;
    }
}

MPSolver* MPSolverFactory(const bool isMip, const std::string& solverName)
{
    const std::string notFound = "Solver " + solverName
                                 + " not supported for linear problems optimization.";
    const std::invalid_argument except(notFound);

    auto internalSolverName = translateSolverName(solverName, isMip);
    if (!internalSolverName.has_value())
    {
        throw std::invalid_argument("Solver " + solverName
                                    + " is not supported by Antares or does not support "
                                    + (isMip ? "MIP" : "LP") + " problems.");
    }

    MPSolver* solver = MPSolver::CreateSolver(*internalSolverName);
    if (!solver)
    {
        throw std::invalid_argument("Solver " + solverName + " (" + *internalSolverName
                                    + ") could not be loaded by OR-Tools MPSolver.");
    }

    return solver;
}
