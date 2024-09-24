cmake_minimum_required(VERSION 3.20)

# Project Info
set(PROJECT_NAME "erpege")
set(PROJECT_VERSION "0.1.0")
set(PROJECT_DESCRIPTION "")

set(CLIENT_TARGET_NAME "erpege_client")
set(CLIENT_TARGET_VERSION "0.1.0")
set(CLIENT_TARGET_DESCRIPTION "A game client for erpege")


set(SERVER_TARGET_NAME "erpege_server")
set(SERVER_TARGET_VERSION "0.1.0")
set(SERVER_TARGET_DESCRIPTION "A game server for erpege")



# Init settings and variables
include(cmake/init.cmake)

project(
    ${CLIENT_TARGET_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    LANGUAGES C)
project(
    ${SERVER_TARGET_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    LANGUAGES C)
add_executable(${CLIENT_TARGET_NAME} ${CLIENT_SRC_FILES})
add_executable(${SERVER_TARGET_NAME} ${SERVER_SRC_FILES})

# Find and set third party libraries
includelibs()

# Find and copy assets
include(cmake/assets.cmake)

print_block("Configuration finished: ${CLIENT_TARGET_NAME}")
