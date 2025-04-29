add_library(antares_utils)
target_sources(antares_utils PRIVATE
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
        include/antares/solver/utils/ortools_utils.h
        mps_utils.cpp
        name_translator.cpp
        named_problem.cpp
        opt_period_string_generator.cpp
        ortools_utils.cpp
)

add_library(Antares::solverUtils ALIAS antares_utils)

target_link_libraries(antares_utils
        PUBLIC
        ortools::ortools
        sirius_solver
        Antares::result_writer
        Antares::optimization-options
        Antares::exception
)

target_include_directories(antares_utils
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(DIRECTORY include/antares
        DESTINATION "include"
)
