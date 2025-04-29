
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

#pragma once

#include <tuple>
#include <vector>

namespace Antares::Optimization
{

struct RemixHydroOutput
{
    std::vector<double> HydroGen;
    std::vector<double> UnsupE;
    std::vector<double> levels;

    // Allow std::tie(a, b, c) = remixHydroOutput;
    inline operator std::tuple<std::vector<double>&, std::vector<double>&, std::vector<double>&>()

    {
        return {HydroGen, UnsupE, levels};
    }
};

RemixHydroOutput shavePeaksByRemixingHydro(const std::vector<double>& DispatchGen,
                                           const std::vector<double>& HydroGen,
                                           const std::vector<double>& UnsupE,
                                           const std::vector<double>& HydroPmax,
                                           const std::vector<double>& HydroPmin,
                                           double initialLevel,
                                           double capacity,
                                           double efficiency,
                                           bool reservoirManagement,
                                           const std::vector<double>& inflow,
                                           const std::vector<double>& overflow,
                                           const std::vector<double>& pump,
                                           const std::vector<double>& Spillage,
                                           const std::vector<double>& DTG_MRG);

} // namespace Antares::Optimization
