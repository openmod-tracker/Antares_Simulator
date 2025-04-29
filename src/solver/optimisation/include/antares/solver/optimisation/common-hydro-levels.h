
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

namespace Antares::Optimization
{

/*
** \brief Interpolates water values related to reservoir levels for outputs only
**
** \param areas : the areas of study
** \param problem The weekly problem, from the solver
*point of weekly simulation)
** \param hourInYear The hour in the year of the first hour in the current week
**
** For any hour, the computed water values are related to the beginning of the hour, not the end.
*/
void interpolateWaterValue(const Data::AreaList& areas,
                           PROBLEME_HEBDO& problem,
                           const Date::Calendar& calendar,
                           int hourInTheYear);

/*
** \brief Updating the weekly simulation final reservoir level, to be used as a start for the next
*week.
**
** \param areas : the areas of study
** \param problem The weekly problem, from the solver
*/
void updatingWeeklyFinalHydroLevel(const Data::AreaList& areas, PROBLEME_HEBDO& problem);

} // namespace Antares::Optimization
