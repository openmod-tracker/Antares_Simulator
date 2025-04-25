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
#pragma once

extern "C"
{
#include "spx_definition_arguments.h"
#include "spx_fonctions.h"
#include "srs_api.h"
}

#include "antares/study/fwd.h"

#include "named_problem.h"
#include "ortools_utils.h"

// ======================
// MPS files writing
// ======================

class I_MPS_writer
{
public:
    explicit I_MPS_writer(uint currentOptimNumber):
        current_optim_number_(currentOptimNumber)
    {
    }

    I_MPS_writer() = default;
    virtual ~I_MPS_writer() = default;
    virtual void runIfNeeded(Antares::Solver::IResultWriter& writer, const std::string& filename)
      = 0;

protected:
    uint current_optim_number_ = 0;
};

// Caution : this class should be removed if we want Sirius behind or-tools
// But we want to keep the way we write MPS files for a named problem,
// so we keep it for now.
class fullMPSwriter final: public I_MPS_writer
{
public:
    fullMPSwriter(Antares::Optimization::PROBLEME_SIMPLEXE_NOMME* named_splx_problem,
                  uint currentOptimNumber);
    void runIfNeeded(Antares::Solver::IResultWriter& writer, const std::string& filename) override;

private:
    Antares::Optimization::PROBLEME_SIMPLEXE_NOMME* named_splx_problem_ = nullptr;
};

class fullOrToolsMPSwriter: public I_MPS_writer
{
public:
    ~fullOrToolsMPSwriter() override = default;
    fullOrToolsMPSwriter(operations_research::MPSolver* solver, uint currentOptimNumber);
    void runIfNeeded(Antares::Solver::IResultWriter& writer, const std::string& filename) override;

private:
    operations_research::MPSolver* solver_ = nullptr;
};

class nullMPSwriter: public I_MPS_writer
{
public:
    ~nullMPSwriter() override = default;
    using I_MPS_writer::I_MPS_writer;

    void runIfNeeded(Antares::Solver::IResultWriter& /*writer*/,
                     const std::string& /*filename*/) override
    {
        // Does nothing
    }
};

class mpsWriterFactory
{
public:
    virtual ~mpsWriterFactory() = default;
    mpsWriterFactory(Antares::Data::mpsExportStatus exportMPS,
                     bool exportMPSOnError,
                     int current_optim_number,
                     operations_research::MPSolver* solver);

    std::unique_ptr<I_MPS_writer> create();
    std::unique_ptr<I_MPS_writer> createOnOptimizationError();

private:
    // Member functions...
    std::unique_ptr<I_MPS_writer> createFullmpsWriter();
    bool doWeExportMPS();

    // Member data...
    Antares::Data::mpsExportStatus export_mps_;
    bool export_mps_on_error_;
    operations_research::MPSolver* solver_ = nullptr;
    uint current_optim_number_;
};
