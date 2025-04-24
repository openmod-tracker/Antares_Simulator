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

#include "ui/common/update/updater.h"

namespace Antares
{
ScenarioBuilderUpdater::ScenarioBuilderUpdater(Data::Study &study):
    pStudy(study) {
    using namespace Yuni;
    // We can store the INI files in disk because it may not fit in memory

    if (study.scenarioRules)
    {
        study.scenarioRules->inUpdaterMode = true;
        logs.debug() << "[scenario-builder] updater mode ON";

        logs.debug()
                << "[scenario-builder] writing data to a temporary file before structure changes";
        pTempFile << memory.cacheFolder() << SEP << "antares-scenbld-save-"
                << memory.processID() << '-' << (size_t)(this) << "-scenariobuilder.tmp";
        // Dump the memory
        study.scenarioRules->saveToINIFile(pTempFile);
        study.scenarioRules->clear();
    }
}
}