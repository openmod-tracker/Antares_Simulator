include(${CMAKE_SOURCE_DIR}/tests/macros.cmake)

add_boost_test(tests-adq-patch
        SRC adequacy_patch.cpp
        LIBS
        array
        Antares::exception
)
