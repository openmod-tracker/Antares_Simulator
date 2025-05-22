#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "antares-analyzer" for configuration "Debug"
set_property(TARGET antares-analyzer APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(antares-analyzer PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/antares-analyzer"
  )

list(APPEND _IMPORT_CHECK_TARGETS antares-analyzer )
list(APPEND _IMPORT_CHECK_FILES_FOR_antares-analyzer "${_IMPORT_PREFIX}/bin/antares-analyzer" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
