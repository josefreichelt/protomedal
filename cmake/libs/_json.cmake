# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
set(local_lib_name "nlohmannjson")
print("⚙️ Configuring ${local_lib_name}...")
set(FETCHCONTENT_BASE_DIR "${DEPS_FOLDER}/${local_lib_name}")

FetchContent_Declare(
    ${local_lib_name}
    GIT_REPOSITORY "https://github.com/nlohmann/json"
    GIT_TAG "v3.11.3"
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE TRUE
    INSTALL_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_MakeAvailable(${local_lib_name})

target_include_directories(${CLIENT_TARGET_NAME} PRIVATE "${${local_lib_name}_SOURCE_DIR}/single_include")

print("✅ Configuring ${local_lib_name} Done")
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
