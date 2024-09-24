# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
set(local_lib_name "raylib")
set(lib_name "raylib")
print("⚙️ Configuring ${local_lib_name}...")
set(FETCHCONTENT_BASE_DIR "${DEPS_FOLDER}/${local_lib_name}")

FetchContent_Declare(
    ${local_lib_name}
    GIT_REPOSITORY "https://github.com/raysan5/raylib"
    GIT_TAG "5.0"
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE TRUE
    GIT_SHALLOW TRUE
    INSTALL_COMMAND ""
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
)
FetchContent_MakeAvailable(${local_lib_name})
# disabling enum flag due to some raygui enums
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-enum-compare -Wno-ignored-qualifiers -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-command-line-argument -Wno-unknown-warning-option -Wno-deprecated-declarations")

target_include_directories(${CLIENT_TARGET_NAME} PRIVATE "${${local_lib_name}_BINARY_DIR}/raylib/include")

target_link_libraries(${CLIENT_TARGET_NAME} PRIVATE ${lib_name})

if(WIN32)
    target_link_libraries(${CLIENT_TARGET_NAME} PRIVATE gdi32 winmm)
endif()
if(NOT EMSCRIPTEN AND NOT APPLE)
    # target_link_libraries(${CLIENT_TARGET_NAME} PRIVATE opengl32)
endif()

print("✅ Configuring ${local_lib_name} Done")
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
