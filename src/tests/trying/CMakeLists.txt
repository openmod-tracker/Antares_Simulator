add_executable(tests-dummy)
target_sources(tests-dummy PRIVATE dummy.cpp)
# All tests use boost
target_link_libraries(tests-dummy PRIVATE
        Antares::antares-solver-simulation
        Boost::unit_test_framework
)