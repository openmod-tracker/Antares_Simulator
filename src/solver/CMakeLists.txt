OMESSAGE("Antares Solver")

#TODO : see to add bigobj support

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif (MSVC)


add_subdirectory(application)
add_subdirectory(constraints-builder)
add_subdirectory(hydro)
add_subdirectory(infeasible-problem-analysis)
add_subdirectory(lps)
add_subdirectory(misc)
add_subdirectory(optimisation)
add_subdirectory(signal-handling)
add_subdirectory(simulation)
add_subdirectory(ts-generator)
add_subdirectory(utils)
add_subdirectory(variable)
add_subdirectory(optim-model-filler)

#
# Resource file for Windows
#
if (WIN32)
    file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/win32/solver.o")
    FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/win32/solver.ico" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/win32/")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/win32/solver.rc.cmake"
            "${CMAKE_CURRENT_SOURCE_DIR}/win32/solver.rc")

    if (MINGW)
        # resource compilation for mingw
        add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/win32/solver.o"
                COMMAND windres.exe "-I${CMAKE_CURRENT_SOURCE_DIR}"
                "-i${CMAKE_CURRENT_SOURCE_DIR}/win32/solver.rc"
                -o "${CMAKE_CURRENT_BINARY_DIR}/win32/solver.o")
        set(SRCS ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/win32/solver.o")
    else ()
        set(SRCS ${SRCS} "win32/solver.rc")
    endif ()
endif ()


OMESSAGE("  :: application solver")

set(exec_name "antares-solver")

add_library(solver-lib INTERFACE
        ${SRCS}
)

add_executable(antares-solver
        main.cpp
        ${SRCS}
)

set_target_properties(antares-solver PROPERTIES OUTPUT_NAME ${exec_name})

set(ANTARES_SOLVER_LIBS
        Antares::args_helper
        Antares::date
        Antares::benchmarking
        Antares::result_writer
        Antares::sys
        Antares::infoCollection
        Antares::checks
        Antares::misc
        Antares::optimization-options
        Antares::signal-handling
        Antares::locale
        yuni-static-uuid
        yuni-static-core
        ${CMAKE_THREADS_LIBS_INIT}
)

set(ANTARES_SOLVER_LIBS ${ANTARES_SOLVER_LIBS}
        antares-solver-hydro
        antares-solver-variable
        antares-solver-simulation
        antares-solver-ts-generator
        model_antares
        antares-core
)

target_link_libraries(solver-lib
        INTERFACE
        ${ANTARES_SOLVER_LIBS}
)

target_link_libraries(antares-solver
        PRIVATE
        solver-lib
        Antares::application
)

target_include_directories(antares-solver
        PRIVATE
        ${CMAKE_SOURCE_DIR}/solver
)

import_std_libs(antares-solver)
executable_strip(antares-solver)

copy_dependency(sirius_solver antares-solver)
copy_dependency(ortools::ortools antares-solver)
copy_dependency(protobuf::libprotobuf antares-solver)
copy_dependency(Coin::CbcSolver antares-solver)
macro(create_symlink deps target number)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        get_target_property( DEPS_LIB ${deps} IMPORTED_LOCATION_RELEASE )
    else()
        get_target_property( DEPS_LIB ${deps} IMPORTED_LOCATION_DEBUG )
    endif()

    if (NOT "${DEPS_LIB}" STREQUAL "DEP_SHARED_LIB_PATH-NOTFOUND")
        #string(REGEX REPLACE "\\.so\\.*" ".so.${number}" LIB_SYMLINK ${DEPS_LIB})
        # Copy the shared lib file
        #get DEPS_LIB file name
        get_filename_component(DEPS_LIB ${DEPS_LIB} NAME)
        string(REGEX REPLACE "\\.so\\.[0-9.]+" ".so.${number}" LIB_SYMLINK ${DEPS_LIB})
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE_DIR:${target}>/${DEPS_LIB} $<TARGET_FILE_DIR:${target}>/${LIB_SYMLINK}
                COMMENT "Creating symbolic link to LIB_SYMLINK"
        )
        install(FILES $<TARGET_FILE_DIR:${target}>/${LIB_SYMLINK} TYPE BIN)

    endif()

endmacro()
create_symlink(Coin::CbcSolver antares-solver 2)

copy_dependency(Coin::Cbc antares-solver)
create_symlink(Coin::Cbc antares-solver 2)

copy_dependency(Coin::ClpSolver antares-solver)
copy_dependency(Coin::OsiClp antares-solver)
create_symlink(Coin::OsiClp antares-solver 1)
copy_dependency(GLPK::GLPK antares-solver)
copy_dependency(Coin::Cgl antares-solver)
create_symlink(Coin::Cgl antares-solver 0)
copy_dependency(Coin::Osi antares-solver)
create_symlink(Coin::Osi antares-solver 0)

copy_dependency(Coin::Clp antares-solver)
create_symlink(Coin::Clp antares-solver 1)
copy_dependency(Coin::CoinUtils antares-solver)
create_symlink(Coin::CoinUtils antares-solver 2)
copy_dependency(highs::highs antares-solver)
create_symlink(highs::highs antares-solver 1)

copy_dependency(utf8_range::utf8_validity antares-solver)

if(NOT MSVC)
    list(APPEND ABSL_INTERNAL_DLL_FILES
            "flags/commandlineflag.cc"
            "flags/commandlineflag.h"
            "flags/config.h"
            "flags/declare.h"
            "flags/flag.h"
            "flags/internal/commandlineflag.cc"
            "flags/internal/commandlineflag.h"
            "flags/internal/flag.cc"
            "flags/internal/flag.h"
            "flags/internal/parse.h"
            "flags/internal/path_util.h"
            "flags/internal/private_handle_accessor.cc"
            "flags/internal/private_handle_accessor.h"
            "flags/internal/program_name.cc"
            "flags/internal/program_name.h"
            "flags/internal/registry.h"
            "flags/internal/sequence_lock.h"
            "flags/internal/usage.cc"
            "flags/internal/usage.h"
            "flags/marshalling.cc"
            "flags/marshalling.h"
            "flags/parse.cc"
            "flags/parse.h"
            "flags/reflection.cc"
            "flags/reflection.h"
            "flags/usage.cc"
            "flags/usage.h"
            "flags/usage_config.cc"
            "flags/usage_config.h"
            "log/flags.cc"
            "log/flags.h"
            "log/internal/flags.h"
    )
endif()

set(ABSL_INTERNAL_DLL_TARGETS
        "absl_check"
        "absl_log"
        "absl_vlog_is_on"
        "algorithm"
        "algorithm_container"
        "any"
        "any_invocable"
        "atomic_hook"
        "base"
        "base_internal"
        "bind_front"
        "bits"
        "btree"
        "check"
        "city"
        "civil_time"
        "compare"
        "compressed_tuple"
        "config"
        "container_common"
        "container_memory"
        "cord"
        "cord_internal"
        "cordz_functions"
        "cordz_handle"
        "cordz_info"
        "cordz_sample_token"
        "core_headers"
        "crc_cord_state"
        "crc_cpu_detect"
        "crc_internal"
        "crc32c"
        "debugging"
        "debugging_internal"
        "demangle_internal"
        "die_if_null"
        "dynamic_annotations"
        "endian"
        "examine_stack"
        "exponential_biased"
        "failure_signal_handler"
        "fixed_array"
        "flat_hash_map"
        "flat_hash_set"
        "function_ref"
        "graphcycles_internal"
        "hash"
        "hash_function_defaults"
        "hash_policy_traits"
        "hashtable_debug"
        "hashtable_debug_hooks"
        "hashtablez_sampler"
        "inlined_vector"
        "inlined_vector_internal"
        "int128"
        "kernel_timeout_internal"
        "layout"
        "leak_check"
        "log_internal_check_impl"
        "log_internal_check_op"
        "log_internal_conditions"
        "log_internal_config"
        "log_internal_fnmatch"
        "log_internal_format"
        "log_internal_globals"
        "log_internal_log_impl"
        "log_internal_proto"
        "log_internal_message"
        "log_internal_log_sink_set"
        "log_internal_nullguard"
        "log_internal_nullstream"
        "log_internal_strip"
        "log_internal_voidify"
        "log_internal_append_truncated"
        "log_globals"
        "log_initialize"
        "log"
        "log_entry"
        "log_sink"
        "log_sink_registry"
        "log_streamer"
        "log_internal_structured"
        "log_severity"
        "log_structured"
        "low_level_hash"
        "malloc_internal"
        "memory"
        "meta"
        "node_hash_map"
        "node_hash_set"
        "node_slot_policy"
        "non_temporal_arm_intrinsics"
        "non_temporal_memcpy"
        "numeric"
        "optional"
        "periodic_sampler"
        "pretty_function"
        "random_bit_gen_ref"
        "random_distributions"
        "random_internal_distribution_caller"
        "random_internal_fastmath"
        "random_internal_fast_uniform_bits"
        "random_internal_generate_real"
        "random_internal_iostream_state_saver"
        "random_internal_nonsecure_base"
        "random_internal_pcg_engine"
        "random_internal_platform"
        "random_internal_pool_urbg"
        "random_internal_randen"
        "random_internal_randen_engine"
        "random_internal_randen_hwaes"
        "random_internal_randen_hwaes_impl"
        "random_internal_randen_slow"
        "random_internal_salted_seed_seq"
        "random_internal_seed_material"
        "random_internal_traits"
        "random_internal_uniform_helper"
        "random_internal_wide_multiply"
        "random_random"
        "random_seed_gen_exception"
        "random_seed_sequences"
        "raw_hash_map"
        "raw_hash_set"
        "raw_logging_internal"
        "sample_recorder"
        "scoped_set_env"
        "span"
        "spinlock_wait"
        "stacktrace"
        "status"
        "statusor"
        "str_format"
        "str_format_internal"
        "strerror"
        "strings"
        "strings_internal"
        "string_view"
        "symbolize"
        "synchronization"
        "throw_delegate"
        "time"
        "time_zone"
        "type_traits"
        "utility"
        "variant"
        "vlog_config_internal"
        "vlog_is_on"
)

if(NOT MSVC)
    list(APPEND ABSL_INTERNAL_DLL_TARGETS
            "flags"
            "flags_commandlineflag"
            "flags_commandlineflag_internal"
            "flags_config"
            "flags_internal"
            "flags_marshalling"
            "flags_parse"
            "flags_path_util"
            "flags_private_handle_accessor"
            "flags_program_name"
            "flags_reflection"
            "flags_usage"
            "flags_usage_internal"
            "log_internal_flags"
            "log_flags"
    )
endif()

#other link issue
list(APPEND ABSL_INTERNAL_DLL_TARGETS
        "demangle_rust"
        "decode_rust_punycode"
        "utf8_for_code_point"
)

foreach(target ${ABSL_INTERNAL_DLL_TARGETS})
    copy_dependency(absl::${target} antares-solver)
endforeach ()

#TODO : not working inside macro
install(TARGETS antares-solver EXPORT antares-solver DESTINATION bin)

INSTALL(EXPORT antares-solver
        FILE antares-solverConfig.cmake
        DESTINATION cmake
)


#########
