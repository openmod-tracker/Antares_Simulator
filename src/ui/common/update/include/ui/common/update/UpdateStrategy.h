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
#include <memory>
#include <antares/study/IUpdateStrategy.h>
#include "ui/common/update/correlation-updater.h"
#include "ui/common/update/updater.h"

namespace Antares {
    namespace Data {
        class Study;
    }

    class ScenarioBuilderUpdater;
    class CorrelationUpdater;
}

class UpdateStrategy : public Antares::IUpdateStrategy {
    std::unique_ptr<Antares::CorrelationUpdater> correlationUpdater;
    std::unique_ptr<Antares::ScenarioBuilderUpdater> scenarioBuilderUpdater;
    Antares::Data::Study &study_;

public:
    explicit UpdateStrategy(Antares::Data::Study &study);

    ~UpdateStrategy() override = default;

    void SBPartBegin() override;

    void SBPartEnd() override;

    void CorrelationPartBegin() override;

    void CorrelationPartEnd() override;

    void begin() override;

    void end() override;
};
