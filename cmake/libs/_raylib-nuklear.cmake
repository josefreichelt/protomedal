# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
set(local_lib_name "raylib-nuklear")
print("⚙️ Configuring ${local_lib_name}...")
set(FETCHCONTENT_BASE_DIR "${DEPS_FOLDER}/${local_lib_name}")

FetchContent_Declare(
    ${local_lib_name}
    GIT_REPOSITORY "https://github.com/RobLoach/raylib-nuklear"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE TRUE
    GIT_SHALLOW TRUE
    INSTALL_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_MakeAvailable(${local_lib_name})

target_include_directories(${CLIENT_TARGET_NAME} PRIVATE "${${local_lib_name}_SOURCE_DIR}/include")
# target_link_libraries(${CLIENT_TARGET_NAME} PRIVATE ${lib_name})no-enum-compare -Wno-ignored-qualifiers -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-command-line-argument -Wno-unknown-warning-option -Wno-deprecated-declaration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
print("✅ Configuring ${local_lib_name} Done")
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
