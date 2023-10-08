set(PROJECT_NAME Pico)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "cpp.hint"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "crossmapping.hpp"
    "enums.hpp"
    "hooking.hpp"
    "input_hook.hpp"
    "json_service.hpp"
    "key_codes.hpp"
    "log.hpp"
    "native_caller.hpp"
    "native_invoker.hpp"
    "natives.hpp"
    "offset_handler.hpp"
    "script_global.hpp"
    "signature_scanner.hpp"
    "stdafx.hpp"
    "structs.hpp"
    "types.hpp"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__functions
    "functions.hpp"
    "looped.hpp"
    "looped_vals.hpp"
    "player.hpp"
    "utils.hpp"
    "vehicle.hpp"
    "world.hpp"
)
source_group("Header Files\\functions" FILES ${Header_Files__functions})

set(Header_Files__gta
    "ipls.hpp"
    "key_names.hpp"
    "net_game_event.hpp"
    "peds.hpp"
    "sessions.hpp"
    "weapons.hpp"
)
source_group("Header Files\\gta" FILES ${Header_Files__gta})

set(Menu
    "menu_class.cpp"
    "menu_class.hpp"
    "script.cpp"
    "script.hpp"
)
source_group("Menu" FILES ${Menu})

set(Source_Files
    "crossmapping.cpp"
    "hooking.cpp"
    "input_hook.cpp"
    "json_service.cpp"
    "log.cpp"
    "main.cpp"
    "native_invoker.cpp"
    "stdafx.cpp"
    "native_spoofer.asm"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Header_Files__functions}
    ${Header_Files__gta}
    ${Menu}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.hpp>"
)
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Pico)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_RELEASE "${PROJECT_NAME}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/Build/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Build/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Release>:"
        "${gtav_classes_SOURCE_DIR};"
        "${json_SOURCE_DIR}/single_include"
    ">"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${gtav_classes_SOURCE_DIR}"
    "${json_SOURCE_DIR}/single_include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "_WINDOWS;"
    "_USRDLL;"
    "WIN32_EXPORTS;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /std:c++latest;
            /GL-;
            /Ob2;
            /Oi-;
            /WX-
        >
        /Od;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(Main.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:WINDOWS
    )
endif()

################################################################################
# Dependencies
################################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
target_link_libraries(${PROJECT_NAME} PRIVATE minhook)