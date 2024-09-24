# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
set(local_lib_name "raygui")
print("⚙️ Configuring ${local_lib_name}...")
set(FETCHCONTENT_BASE_DIR "${DEPS_FOLDER}/${local_lib_name}")

FetchContent_Declare(
    ${local_lib_name}
    GIT_REPOSITORY "https://github.com/raysan5/raygui"
    GIT_TAG "4.0"
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE TRUE
    INSTALL_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(${local_lib_name})

target_include_directories(${CLIENT_TARGET_NAME} PRIVATE "${${local_lib_name}_SOURCE_DIR}/src")

print("✅ Configuring ${local_lib_name} Done")
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
