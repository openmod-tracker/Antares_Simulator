set(SRC_STUDY_SCENARIO_BUILDER
        include/antares/study/scenario-builder/BindingConstraintsTSNumbersData.h
        include/antares/study/scenario-builder/HydroTSNumberData.h
        include/antares/study/scenario-builder/LoadTSNumberData.h
        include/antares/study/scenario-builder/NTCTSNumberData.h
        include/antares/study/scenario-builder/RenewableTSNumberData.h
        include/antares/study/scenario-builder/TSnumberData.h
        include/antares/study/scenario-builder/ThermalTSNumberData.h
        include/antares/study/scenario-builder/WindTSNumberData.h
        include/antares/study/scenario-builder/applyToMatrix.hxx
        include/antares/study/scenario-builder/hydroLevelsData.h
        include/antares/study/scenario-builder/rules.h
        include/antares/study/scenario-builder/rules.hxx
        include/antares/study/scenario-builder/scBuilderDataInterface.h
        include/antares/study/scenario-builder/scBuilderUtils.h
        include/antares/study/scenario-builder/sets.h
        include/antares/study/scenario-builder/sets.hxx
        include/antares/study/scenario-builder/solarTSNumberData.h
        scenario-builder/BindingConstraintsTSNumbersData.cpp
        scenario-builder/HydroTSNumberData.cpp
        scenario-builder/LoadTSNumberData.cpp
        scenario-builder/NTCTSNumberData.cpp
        scenario-builder/RenewableTSNumberData.cpp
        scenario-builder/SolarTSNumberData.cpp
        scenario-builder/TSnumberData.cpp
        scenario-builder/ThermalTSNumberData.cpp
        scenario-builder/WindTSNumberData.cpp
        scenario-builder/hydroLevelsData.cpp
        scenario-builder/rules.cpp
        scenario-builder/scBuilderUtils.cpp
        scenario-builder/sets.cpp
)
source_group("study\\scenario builder" FILES ${SRC_MATRIX})

set(SRC_AREAS
        area/area.cpp
        area/links.cpp
        area/list.cpp
        area/scratchpad.cpp
        area/store-timeseries-numbers.cpp
        include/antares/study/area/area.h
        include/antares/study/area/area.hxx
        include/antares/study/area/constants.h
        include/antares/study/area/links.h
        include/antares/study/area/scratchpad.h
        include/antares/study/area/store-timeseries-numbers.h
        include/antares/study/area/store-timeseries-numbers.hxx
)
source_group("study\\area" FILES ${SRC_AREAS})


set(SRC_STUDY_AREA_UI
        include/antares/study/area/ui.h
        area/ui.cpp
)
source_group("study\\area\\ui" FILES ${SRC_STUDY_AREA_UI})


set(SRC_STUDY_PART_COMMON
        include/antares/study/parts/common/cluster.h
        include/antares/study/parts/common/cluster_list.h
        parts/common/cluster.cpp
        parts/common/cluster_list.cpp
)
source_group("study\\part\\common" FILES ${SRC_STUDY_PART_COMMON})

set(SRC_STUDY_PART_THERMAL
        include/antares/study/parts/thermal/cluster.h
        include/antares/study/parts/thermal/cluster.hxx
        include/antares/study/parts/thermal/cluster_list.h
        include/antares/study/parts/thermal/container.h
        include/antares/study/parts/thermal/cost_provider.h
        include/antares/study/parts/thermal/ecoInput.h
        include/antares/study/parts/thermal/pollutant.h
        parts/thermal/cluster.cpp
        parts/thermal/cluster_list.cpp
        parts/thermal/constant_cost_provider.cpp
        parts/thermal/container.cpp
        parts/thermal/ecoInput.cpp
        parts/thermal/pollutant.cpp
        parts/thermal/scenarized_cost_provider.cpp
)
source_group("study\\part\\thermal" FILES ${SRC_STUDY_PART_THERMAL})

set(SRC_STUDY_PART_RENEWABLE
        include/antares/study/parts/renewable/cluster.h
        include/antares/study/parts/renewable/cluster_list.h
        include/antares/study/parts/renewable/container.h
        include/antares/study/parts/renewable/container.hxx
        parts/renewable/cluster.cpp
        parts/renewable/cluster_list.cpp
        parts/renewable/container.cpp
)
source_group("study\\part\\renewable" FILES ${SRC_STUDY_PART_RENEWABLE})

set(SRC_STUDY_PART_SHORT_TERM_STORAGE
        include/antares/study/parts/short-term-storage/additionalConstraints.h
        include/antares/study/parts/short-term-storage/cluster.h
        include/antares/study/parts/short-term-storage/container.h
        include/antares/study/parts/short-term-storage/properties.h
        include/antares/study/parts/short-term-storage/series.h
        parts/short-term-storage/additionalConstraints.cpp
        parts/short-term-storage/cluster.cpp
        parts/short-term-storage/container.cpp
        parts/short-term-storage/properties.cpp
        parts/short-term-storage/series.cpp
)
source_group("study\\part\\short-term-storage" FILES ${SRC_STUDY_PART_SHORT_TERM_SOTRAGE})

set(SRC_STUDY_PART_WIND
        include/antares/study/parts/wind/container.h
        include/antares/study/parts/wind/prepro.h
        include/antares/study/parts/wind/prepro.hxx
        parts/wind/container.cpp
        parts/wind/prepro.cpp
)
source_group("study\\part\\wind" FILES ${SRC_STUDY_PART_WIND})

set(SRC_STUDY_PART_HYDRO
        include/antares/study/parts/hydro/allocation.h
        include/antares/study/parts/hydro/allocation.hxx
        include/antares/study/parts/hydro/container.h
        include/antares/study/parts/hydro/hydromaxtimeseriesreader.h
        include/antares/study/parts/hydro/prepro.h
        include/antares/study/parts/hydro/series.h
        parts/hydro/allocation.cpp
        parts/hydro/container.cpp
        parts/hydro/hydromaxtimeseriesreader.cpp
        parts/hydro/prepro.cpp
        parts/hydro/series.cpp
)
source_group("study\\part\\hydro" FILES ${SRC_STUDY_PART_HYDRO})

set(SRC_STUDY_UI
        include/antares/study/ui-runtimeinfos.h
        ui-runtimeinfos.cpp
)
source_group(study\\UI FILES ${SRC_STUDY_UI})

set(SRC_STUDY_PARAMETERS
        UnfeasibleProblemBehavior.cpp
        include/antares/study/parameters.h
        include/antares/study/parameters/adq-patch-params.h
        parameters.cpp
        parameters/adq-patch-params.cpp
        # TODO JMK : should be in a target_include_directories : but need to remove all .h from all SRC
        include/antares/study/UnfeasibleProblemBehavior.hpp
)
source_group("study\\general data" FILES ${SRC_STUDY_PARAMETERS})


set(SRC_STUDY_FINDER
        finder/finder.cpp
        include/antares/study/finder/finder.h
)
source_group("study\\finder" FILES ${SRC_STUDY_FINDER})


set(SRC_STUDY_BINDING_CONSTRAINT
        binding_constraint/BindingConstraint.cpp
        binding_constraint/BindingConstraintGroup.cpp
        binding_constraint/BindingConstraintGroupRepository.cpp
        binding_constraint/BindingConstraintLoader.cpp
        binding_constraint/BindingConstraintSaver.cpp
        binding_constraint/BindingConstraintsRepository.cpp
        include/antares/study/binding_constraint/BindingConstraint.h
        include/antares/study/binding_constraint/BindingConstraint.hxx
        include/antares/study/binding_constraint/BindingConstraintGroup.h
        include/antares/study/binding_constraint/BindingConstraintGroupRepository.h
        include/antares/study/binding_constraint/BindingConstraintLoader.h
        include/antares/study/binding_constraint/BindingConstraintSaver.h
        include/antares/study/binding_constraint/BindingConstraintStructures.h
        include/antares/study/binding_constraint/BindingConstraintsRepository.h
        include/antares/study/binding_constraint/BindingConstraintsRepository.h
        include/antares/study/binding_constraint/BindingConstraintsRepository.hxx
        include/antares/study/binding_constraint/EnvForLoading.h
        include/antares/study/constraint.h
)

source_group("study\\constraint" FILES ${SRC_STUDY_BINDING_CONSTRAINT})


set(SRC_XCAST
        include/antares/study/xcast.h
        include/antares/study/xcast/xcast.h
        xcast/xcast.cpp
)
source_group("study\\xcast" FILES ${SRC_XCAST})

set(SRC_STUDY
        duplicates.cpp
        area/sets.cpp
        cleaner/cleaner-v20.cpp
        cleaner/cleaner.cpp
        filter.cpp
        fwd.cpp
        header.cpp
        importlogs.cpp
        include/antares/study/cleaner.h
        include/antares/study/cleaner/versions.h
        include/antares/study/duplicates.h
        include/antares/study/filter.h
        include/antares/study/fwd.h
        include/antares/study/header.h
        include/antares/study/layerdata.h
        include/antares/study/load-options.h
        include/antares/study/output.h
        include/antares/study/output.hxx
        include/antares/study/parts/load/container.h
        include/antares/study/parts/load/prepro.h
        include/antares/study/parts/load/prepro.hxx
        include/antares/study/parts/parts.h
        include/antares/study/parts/solar/container.h
        include/antares/study/parts/solar/prepro.h
        include/antares/study/parts/solar/prepro.hxx
        include/antares/study/progression/progression.h
        include/antares/study/progression/progression.hxx
        include/antares/study/runtime.h
        include/antares/study/runtime/runtime.h
        include/antares/study/sets.h
        include/antares/study/simulation.h
        include/antares/study/study.h
        include/antares/study/study.h
        include/antares/study/study.hxx
        include/antares/study/variable-print-info.h
        include/antares/study/version.h
        layerdata.cpp
        load-options.cpp
        load.cpp
        output.cpp
        parts/load/container.cpp
        parts/load/prepro.cpp
        parts/solar/container.cpp
        parts/solar/prepro.cpp
        progression/progression.cpp
        runtime/runtime.cpp
        save.cpp
        simulation.cpp
        study.cpp
        study.extra.cpp
        study.importprepro.cpp
        variable-print-info.cpp
        version.cpp
)

source_group("study\\study" FILES ${SRC_STUDY})

set(SRC_ALL
        ${SRC_STDCXX}
        ${SRC_AREAS}
        ${SRC_XCAST}
        ${SRC_STUDY_AREA_UI}
        ${SRC_STUDY_UI}
        ${SRC_STUDY_PARAMETERS}
        ${SRC_STUDY_FINDER}
        ${SRC_STUDY_BINDING_CONSTRAINT}
        ${SRC_STUDY_PART_WIND}
        ${SRC_STUDY_PART_HYDRO}
        ${SRC_STUDY_PART_COMMON}
        ${SRC_STUDY_PART_THERMAL}
        ${SRC_STUDY_PART_RENEWABLE}
        ${SRC_STUDY_PART_SHORT_TERM_STORAGE}
        ${SRC_STUDY_SCENARIO_BUILDER}
        ${SRC_STUDY}
)

add_library(study ${SRC_ALL})
add_library(Antares::study ALIAS study)

target_link_libraries(study
        PUBLIC
        Antares::antares-study-system-model
        Antares::array
        Antares::correlation
        Antares::date #parameters
        Antares::hydro
        Antares::inifile #parameters
        Antares::load-modeler-files
        Antares::mersenne
        Antares::modeler-parameters
        Antares::path
        Antares::result_writer #study.h
        Antares::series
        Antares::solverUtils #sim_structure_probleme_economique.h -> optimization_statistics.h
        Antares::stdcxx #enum.hxx
        Antares::utils #area.hxx
        antares-core
        antares-solver-simulation
        linear-problem-api
        yuni-static-core
        PRIVATE
        Antares::memory
        Antares::benchmarking
        Antares::exception
        antares-solver-variable
)

target_include_directories(study
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

        # Make more than just study visible but it's the lesser evil for now
)

install(DIRECTORY include/antares
        DESTINATION "include"
)
