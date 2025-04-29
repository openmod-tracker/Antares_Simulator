#
# Simulation
#
set(SRC_SIMULATION
        TimeSeriesNumbersWriter.cpp
        adequacy.cpp
        apply-scenario.cpp
        common-eco-adq.cpp
        economy.cpp
        include/antares/solver/simulation/BindingConstraintsTimeSeriesNumbersWriter.h
        include/antares/solver/simulation/ITimeSeriesNumbersWriter.h
        include/antares/solver/simulation/adequacy.h
        include/antares/solver/simulation/apply-scenario.h
        include/antares/solver/simulation/common-eco-adq.h
        include/antares/solver/simulation/economy.h
        include/antares/solver/simulation/opt_time_writer.h
        include/antares/solver/simulation/sim_alloc_probleme_hebdo.h
        include/antares/solver/simulation/sim_structure_donnees.h
        include/antares/solver/simulation/simulation-run.h
        include/antares/solver/simulation/simulation.h
        include/antares/solver/simulation/solver.data.h
        include/antares/solver/simulation/solver.h
        include/antares/solver/simulation/solver.hxx
        include/antares/solver/simulation/solver_utils.h
        include/antares/solver/simulation/timeseries-numbers.h
        opt_time_writer.cpp
        sim_alloc_probleme_hebdo.cpp
        sim_calcul_economique.cpp
        simulation-run.cpp
        solver.data.cpp
        solver_utils.cpp
        timeseries-numbers.cpp
)
source_group("simulation" FILES ${SRC_SIMULATION})

#
# --- Library VARIABLES ---
#
add_library(antares-solver-simulation)
add_library(Antares::antares-solver-simulation ALIAS antares-solver-simulation)
target_sources(antares-solver-simulation
        PRIVATE
        ${SRC_SIMULATION})

target_include_directories(antares-solver-simulation
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(antares-solver-simulation
        PUBLIC
        Antares::infoCollection
        yuni-static-core
        Antares::study
        Antares::result_writer
        Antares::concurrency
        Antares::solverUtils
        Antares::misc
        Antares::optimisation
        Antares::data
        antares-solver-hydro
        antares-solver-variable
        antares-solver-ts-generator
)

install(DIRECTORY include/antares
        DESTINATION "include"
)
