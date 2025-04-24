add_library(ui-update)
add_library(Antares::ui-update ALIAS ui-update)

target_sources(ui-update
    PRIVATE
        UpdateStrategy.cpp
        correlation-updater.cpp
        include/ui/common/update/UpdateStrategy.h
        include/ui/common/update/correlation-updater.h
        include/ui/common/update/updater.h
        updater.cpp
)

target_link_libraries(ui-update
    PUBLIC
        Antares::study
)

target_include_directories(ui-update
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)