#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "antares-modeler" for configuration "Debug"
set_property(TARGET antares-modeler APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(antares-modeler PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/antares-modeler"
  )

list(APPEND _IMPORT_CHECK_TARGETS antares-modeler )
list(APPEND _IMPORT_CHECK_FILES_FOR_antares-modeler "${_IMPORT_PREFIX}/bin/antares-modeler" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
