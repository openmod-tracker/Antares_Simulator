
#pragma once

#include "antares/solver/optimisation/adequacy_patch_csr/hourly_csr_problem.h"
#include "antares/solver/optimisation/opt_structure_probleme_a_resoudre.h"
#include "antares/study/parameters/adq-patch-params.h"

bool ADQ_PATCH_CSR(const OptimizationOptions::SingleOptimOptions& options,
                   PROBLEME_ANTARES_A_RESOUDRE&,
                   HourlyCSRProblem&,
                   const Data::AdequacyPatch::AdqPatchParams&,
                   unsigned int week,
                   int year);
