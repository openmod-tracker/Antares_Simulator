include(${CMAKE_SOURCE_DIR}/tests/macros.cmake)

# Useful variables definitions
set(src_solver_simulation "${CMAKE_SOURCE_DIR}/solver/simulation")
set(src_solver_hydro "${CMAKE_SOURCE_DIR}/solver/hydro")
set(src_libs_antares_study "${CMAKE_SOURCE_DIR}/libs/antares/study")

add_boost_test(tests-ts-numbers
        SRC tests-ts-numbers.cpp
        LIBS
        Antares::utils
        Antares::antares-solver-simulation
        antares-solver-ts-generator
)


# ===================================
# Tests on area's store-timeseries-number
# ===================================
add_boost_test(test-store-timeseries-number
        SRC test-store-timeseries-number.cpp
        LIBS
        test_utils_unit
        antares-solver-simulation
        Antares::study
        Antares::result_writer)

# ===================================
# Tests on time series
# ===================================
add_boost_test(test-time_series
        SRC test-time_series.cpp
        LIBS
        test_utils_unit
        antares-solver-simulation
        Antares::study)

# ===================================
# Tests on hydro final reservoir level functions
# ===================================
add_boost_test(test-hydro_final
        SRC
        test-hydro-final-reservoir-level-functions.cpp
        LIBS
        Antares::study
        antares-solver-simulation
        Antares::hydro
        Antares::array)

# ===================================
# Tests on hydro remix algorithm
# ===================================
add_boost_test(tests-on-hydro-remix
        SRC
        test-hydro-remix.cpp
        LIBS
        shave-peaks-by-remix-hydro
        test_utils_unit)