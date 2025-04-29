add_library(data)
add_library(Antares::data ALIAS data)
target_sources(data
    PRIVATE
        include/antares/data/sim_structure_probleme_economique.h
        include/antares/data/opt_structure_probleme_a_resoudre.h
        include/antares/data/adequacy_patch_runtime_data.h
        sim_structure_probleme_economique.cpp
        opt_structure_probleme_a_resoudre.cpp
        include/antares/data/SparseVector.hxx
        include/antares/data/constants.h
        constants.cpp
        adequacy_patch_runtime_data.cpp
)

target_link_libraries(data
PUBLIC
Antares::solverUtils
)

target_include_directories(data
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(DIRECTORY include/antares
        DESTINATION "include"
)