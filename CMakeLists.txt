cmake_minimum_required(VERSION 3.20)

# Project Info
set(PROJECT_NAME "erpege")
set(PROJECT_VERSION "0.1.0")
set(PROJECT_DESCRIPTION "")

set(CLIENT_TARGET_NAME "erpege_client")
set(CLIENT_TARGET_VERSION "0.1.0")
set(CLIENT_TARGET_DESCRIPTION "A game client for erpege")


set(CLIENT_SERVER_NAME "erpege_server")
set(CLIENT_SERVER_VERSION "0.1.0")
set(CLIENT_SERVER_DESCRIPTION "A game server for erpege")



# Init settings and variables
include(cmake/init.cmake)

project(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    LANGUAGES C)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Find and set third party libraries
includelibs()

# Find and copy assets
include(cmake/assets.cmake)

print_block("Configuration finished: ${PROJECT_NAME}")
