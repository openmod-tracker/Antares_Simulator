include(${CMAKE_SOURCE_DIR}/tests/macros.cmake)

# Useful variables definitions
set(src_solver_simulation "${CMAKE_SOURCE_DIR}/solver/simulation")
set(src_solver_hydro "${CMAKE_SOURCE_DIR}/solver/hydro")
set(src_libs_antares_study "${CMAKE_SOURCE_DIR}/libs/antares/study")

add_executable(tests-ts-numbers)
target_sources(tests-ts-numbers PRIVATE tests-ts-numbers.cpp)
# All tests use boost
target_link_libraries(tests-ts-numbers PRIVATE
        Antares::utils
        Antares::antares-solver-simulation
        Antares::solverTsGenerator
        Boost::unit_test_framework
)

# All executables in <build>/tests
set_target_properties(tests-ts-numbers PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

add_test(NAME tests-ts-numbers COMMAND tests-ts-numbers)

# Adding labels allows ctest filter what tests to run
set_property(TEST tests-ts-numbers PROPERTY LABELS unit)

# Give the IDE some directions to display tests in a "Unit-tests" folder
set_target_properties(tests-ts-numbers PROPERTIES FOLDER Unit-tests)


# ===================================
# Tests on area's store-timeseries-number
# ===================================
add_boost_test(test-store-timeseries-number
        SRC test-store-timeseries-number.cpp
        LIBS
        test_utils_unit
        Antares::study
        Antares::result_writer)

# ===================================
# Tests on time series
# ===================================
add_boost_test(test-time_series
        SRC test-time_series.cpp
        LIBS
        test_utils_unit
        Antares::study
)

# ===================================
# Tests on hydro final reservoir level functions
# ===================================
add_boost_test(test-hydro_final
        SRC
        test-hydro-final-reservoir-level-functions.cpp
        LIBS
        Antares::study
        Antares::hydro
        Antares::array
)

# ===================================
# Tests on hydro remix algorithm
# ===================================
add_boost_test(tests-on-hydro-remix
        SRC
        test-hydro-remix.cpp
        LIBS
        shave-peaks-by-remix-hydro
        test_utils_unit
)