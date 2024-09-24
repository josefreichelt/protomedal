# Initialize some settings
cmake_policy(SET CMP0048 NEW)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For clangd LSP
# Dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
set(DEPS_FOLDER "${CMAKE_SOURCE_DIR}/deps")


# Enable and setup Fetch Content
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_BASE_DIR ${DEPS_FOLDER})


# Helper functions
include(cmake/utils/libloader.cmake)
include(cmake/utils/printer.cmake)

# Source and include files, hpp files put to sources for intellisense
file(GLOB_RECURSE CLIENT_SRC_FILES CONFIGURE_DEPENDS SOURCES ${CMAKE_SOURCE_DIR}/source/client/*)
# Exlude test files from build:
list(FILTER CLIENT_SRC_FILES EXCLUDE REGEX "\_test\.(c|h)$")
# Include only cpp and hpp files
list(FILTER CLIENT_SRC_FILES INCLUDE REGEX "\.(c|h)$")

# Source and include files, hpp files put to sources for intellisense
file(GLOB_RECURSE SERVER_SRC_FILES CONFIGURE_DEPENDS SOURCES ${CMAKE_SOURCE_DIR}/source/server/*)
# Exlude test files from build:
list(FILTER SERVER_SRC_FILES EXCLUDE REGEX "\_test\.(c|h)$")
# Include only cpp and hpp files
list(FILTER SERVER_SRC_FILES INCLUDE REGEX "\.(c|h)$")

# Compile definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

print_block("Project settings"
    CLIENT_TARGET_NAME
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    CMAKE_BUILD_TYPE
    CMAKE_C_COMPILER
    CMAKE_HOST_SYSTEM_NAME
    HOME
    )
print_block("Client Source files" CLIENT_SRC_FILES)
print_block("Server Source files" SERVER_SRC_FILES)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -std=c99 -Wno-unused-function ")
endif()

# Hide console on windows release
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--subsystem,windows")
endif()
