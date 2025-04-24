set(SRC
        basis_status.cpp
        basis_status_impl.cpp
        basis_status_impl.h
        filename.cpp
        include/antares/solver/utils/basis_status.h
        include/antares/solver/utils/filename.h
        include/antares/solver/utils/mps_utils.h
        include/antares/solver/utils/name_translator.h
        include/antares/solver/utils/named_problem.h
        include/antares/solver/utils/opt_period_string_generator.h
        include/antares/solver/utils/ortools_quadratic_wrapper.h
        include/antares/solver/utils/ortools_utils.h
        mps_utils.cpp
        name_translator.cpp
        named_problem.cpp
        opt_period_string_generator.cpp
        ortools_quadratic_wrapper.cpp
        ortools_utils.cpp
)

add_library(utils ${SRC})
add_library(Antares::solverUtils ALIAS utils)
if (NOT MSVC)
    target_compile_options(utils
            PUBLIC
            "-Wno-unused-variable")
endif ()
target_link_libraries(utils
        PUBLIC
        ortools::ortools
        sirius_solver
        Antares::study
        Antares::result_writer
        Antares::optimization-options
        antares-core
)

target_include_directories(utils
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(DIRECTORY include/antares
        DESTINATION "include"
)
