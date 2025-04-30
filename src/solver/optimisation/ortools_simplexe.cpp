// Copyright 2007-2025, RTE (https://www.rte-france.com)
// See AUTHORS.txt
// SPDX-License-Identifier: MPL-2.0
// This file is part of Antares-Simulator,
// Adequacy and Performance assessment for interconnected energy networks.
//
// Antares_Simulator is free software: you can redistribute it and/or modify
// it under the terms of the Mozilla Public Licence 2.0 as published by
// the Mozilla Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Antares_Simulator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// Mozilla Public Licence 2.0 for more details.
//
// You should have received a copy of the Mozilla Public Licence 2.0
// along with Antares_Simulator. If not, see <https://opensource.org/license/mpl-2-0/>.

#include "antares/solver/optimisation/ortools_simplexe.h"

#include <ortools/linear_solver/linear_solver.h>

#include "antares/exception/LoadingError.hpp"
#include "antares/optimization-options/options.h"
#include "antares/solver/utils/basis_status.h"
#include "antares/solver/utils/named_problem.h"

#include "pi_constantes_externes.h"
#include "spx_constantes_externes.h"

using namespace operations_research;

namespace
{
// MPSolverParameters's copy constructor is private
void setGenericParameters(MPSolverParameters& params)
{
    params.SetIntegerParam(MPSolverParameters::SCALING, 0);
    params.SetIntegerParam(MPSolverParameters::PRESOLVE, 0);
    // ortools default is 1e-7 for primal tolerance, but this may be too high as we manipulate large
    // values in the problem. Then 1e-7 may be too hard to achieve and has lead to declare some
    // problems infeasible whereas they were not (contraints were active but not violated). Sirius
    // uses 1e-6 (and this cannot be changed with ortools), this has effect for all solvers except
    // sirius
    params.SetDoubleParam(MPSolverParameters::PRIMAL_TOLERANCE, 1e-6);
}

bool solverSupportsWarmStart(const MPSolver::OptimizationProblemType solverType)
{
    switch (solverType)
    {
    case MPSolver::XPRESS_LINEAR_PROGRAMMING:
        return true;
    default:
        return false;
    }
}

bool doWeGiveBasisToSolver(const Antares::OptimizationOptions::SingleOptimOptions& options,
                           const MPSolver* solver,
                           const Antares::Solver::Utils::PROBLEME_SIMPLEXE_NOMME* Probleme)
{
    return solverSupportsWarmStart(solver->ProblemType()) && Probleme->basisExists()
           && options.solverUsesBasis;
}

bool doWeStoreSolverBasis(const Antares::OptimizationOptions::SingleOptimOptions& options,
                          const MPSolver* solver)
{
    return solverSupportsWarmStart(solver->ProblemType()) && options.solverExportsBasis;
}

void extractSolutionValues(const std::vector<MPVariable*>& variables,
                           Antares::Solver::Utils::PROBLEME_SIMPLEXE_NOMME* problemeSimplexe)
{
    int nbVar = problemeSimplexe->NombreDeVariables;
    for (int idxVar = 0; idxVar < nbVar; ++idxVar)
    {
        const MPVariable* var = variables[idxVar];
        problemeSimplexe->X[idxVar] = var->solution_value();
    }
}

void extractReducedCosts(const std::vector<MPVariable*>& variables,
                         Antares::Solver::Utils::PROBLEME_SIMPLEXE_NOMME* problemeSimplexe)
{
    int nbVar = problemeSimplexe->NombreDeVariables;
    for (int idxVar = 0; idxVar < nbVar; ++idxVar)
    {
        const MPVariable* var = variables[idxVar];
        problemeSimplexe->CoutsReduits[idxVar] = var->reduced_cost();
    }
}

void extractDualValues(const std::vector<MPConstraint*>& constraints,
                       Antares::Solver::Utils::PROBLEME_SIMPLEXE_NOMME* problemeSimplexe)
{
    int nbRows = problemeSimplexe->NombreDeContraintes;
    for (int idxRow = 0; idxRow < nbRows; ++idxRow)
    {
        const MPConstraint* row = constraints[idxRow];
        problemeSimplexe->CoutsMarginauxDesContraintes[idxRow] = row->dual_value();
    }
}

void extract_from_MPSolver(const MPSolver* solver,
                           Antares::Solver::Utils::PROBLEME_SIMPLEXE_NOMME* problemeSimplexe)
{
    assert(solver);
    assert(problemeSimplexe);

    const bool isMIP = problemeSimplexe->isMIP();

    extractSolutionValues(solver->variables(), problemeSimplexe);

    if (isMIP)
    {
        // TODO extract dual values & marginal costs from LP with fixed integer variables
        const int nbVar = problemeSimplexe->NombreDeVariables;
        std::fill(problemeSimplexe->CoutsReduits, problemeSimplexe->CoutsReduits + nbVar, 0.);
        const int nbRows = problemeSimplexe->NombreDeContraintes;
        std::fill(problemeSimplexe->CoutsMarginauxDesContraintes,
                  problemeSimplexe->CoutsMarginauxDesContraintes + nbRows,
                  0.);
    }
    else
    {
        extractReducedCosts(solver->variables(), problemeSimplexe);
        extractDualValues(solver->constraints(), problemeSimplexe);
    }
}

void checkSetSolverSpecificParameters(bool status,
                                      const std::string& solverName,
                                      const std::string& specificParameters)
{
    if (!status)
    {
        throw Antares::Error::InvalidSolverSpecificParameters(solverName, specificParameters);
    }
}

bool solveAndManageStatus(MPSolver* solver, int& resultStatus, const MPSolverParameters& params)
{
    auto status = solver->Solve(params);
    if (status == MPSolver::OPTIMAL || status == MPSolver::FEASIBLE)
    {
        resultStatus = OUI_SPX;
    }
    else
    {
        resultStatus = NON_SPX;
    }

    return resultStatus == OUI_SPX;
}

const std::string XPRESS_PARAMS = "THREADS 1";
const std::string SCIP_PARAMS = "parallel/maxnthreads 1";

void TuneSolverSpecificOptions(MPSolver* solver,
                               const std::string& solverName,
                               const std::string& solverParameters)
{
    if (!solver)
    {
        return;
    }

    bool status;
    std::string specificParams;

    switch (solver->ProblemType())
    {
    // Allow solver to use only one thread
    case MPSolver::XPRESS_LINEAR_PROGRAMMING:
    case MPSolver::XPRESS_MIXED_INTEGER_PROGRAMMING:
    {
        specificParams = XPRESS_PARAMS + " " + solverParameters;
        status = solver->SetSolverSpecificParametersAsString(specificParams);
        checkSetSolverSpecificParameters(status, solverName, specificParams);
        break;
    }
    case MPSolver::SCIP_MIXED_INTEGER_PROGRAMMING:
    {
        specificParams = SCIP_PARAMS + ", " + solverParameters;
        status = solver->SetSolverSpecificParametersAsString(specificParams);
        checkSetSolverSpecificParameters(status, solverName, specificParams);
        break;
    }
    default:
        break;
    }
}
} // namespace

namespace Antares::Optimization
{
MPSolver* ORTOOLS_Simplexe(Antares::Solver::Utils::PROBLEME_SIMPLEXE_NOMME* Probleme,
                           MPSolver* solver,
                           const OptimizationOptions::SingleOptimOptions& options)
{
    MPSolverParameters params;
    // Keep generic params for default settings working for all solvers
    setGenericParameters(params);
    if (options.solverLogs) // May be overriden by log level if set as specific parameters
    {
        solver->EnableOutput();
    }
    TuneSolverSpecificOptions(solver, options.solverName, options.solverParameters);

    if (doWeGiveBasisToSolver(options, solver, Probleme))
    {
        Probleme->basisStatus.setStartingBasis(solver);
    }

    if (solveAndManageStatus(solver, Probleme->ExistenceDUneSolution, params))
    {
        extract_from_MPSolver(solver, Probleme);
        if (doWeStoreSolverBasis(options, solver))
        {
            Probleme->basisStatus.extractBasis(solver);
        }
    }

    return solver;
}
} // namespace Antares::Optimization
