#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "antares-ui-simulator" for configuration "Debug"
set_property(TARGET antares-ui-simulator APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(antares-ui-simulator PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/antares-ui-simulator"
  )

list(APPEND _IMPORT_CHECK_TARGETS antares-ui-simulator )
list(APPEND _IMPORT_CHECK_FILES_FOR_antares-ui-simulator "${_IMPORT_PREFIX}/bin/antares-ui-simulator" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
