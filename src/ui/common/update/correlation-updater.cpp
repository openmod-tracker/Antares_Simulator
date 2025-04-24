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

#include "../../../libs/antares/study/include/antares/study/study.h"
#include "ui/common/update/correlation-updater.h"

namespace Antares
{
    CorrelationUpdater::CorrelationUpdater(Data::Study &study):
        pStudy(study) {
        using namespace Yuni;
        // We can store the INI files in disk because it may not fit in memory
        pTempFile << memory.cacheFolder() << SEP << "antares-corr-save-" << memory.processID()
                << '-' << (void*)(this) << '-';

        pS.clear() << pTempFile << "load.tmp";
        study.preproLoadCorrelation.saveToFile(study, pS);
        pS.clear() << pTempFile << "solar.tmp";
        study.preproSolarCorrelation.saveToFile(study, pS);
        pS.clear() << pTempFile << "wind.tmp";
        study.preproWindCorrelation.saveToFile(study, pS);
        pS.clear() << pTempFile << "hydro.tmp";
        study.preproHydroCorrelation.saveToFile(study, pS);
    }

    CorrelationUpdater::~CorrelationUpdater() {
        using namespace Yuni;
        pS.clear() << pTempFile << "load.tmp";
        pStudy.preproLoadCorrelation.loadFromFile(pStudy, pS, false);
        IO::File::Delete(pS);

        pS.clear() << pTempFile << "solar.tmp";
        pStudy.preproSolarCorrelation.loadFromFile(pStudy, pS, false);
        IO::File::Delete(pS);

        pS.clear() << pTempFile << "wind.tmp";
        pStudy.preproWindCorrelation.loadFromFile(pStudy, pS, false);
        IO::File::Delete(pS);

        pS.clear() << pTempFile << "hydro.tmp";
        pStudy.preproHydroCorrelation.loadFromFile(pStudy, pS, false);
        IO::File::Delete(pS);
    }
}
