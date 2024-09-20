# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
set(local_lib_name "imgui")
set(lib_name "_imgui")
print("⚙️ Configuring ${local_lib_name}...")
set(FETCHCONTENT_BASE_DIR "${DEPS_FOLDER}/${local_lib_name}")

FetchContent_Declare(
    ${local_lib_name}
    GIT_REPOSITORY "https://github.com/ocornut/imgui"
    GIT_TAG "fdc084f532189fda8474079f79e74fa5e3541c9f"
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE TRUE
    GIT_SHALLOW TRUE
    INSTALL_COMMAND ""
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
)
FetchContent_MakeAvailable(${local_lib_name})
add_library(${lib_name} STATIC
    ${${local_lib_name}_SOURCE_DIR}/imgui.cpp
    ${${local_lib_name}_SOURCE_DIR}/imgui_demo.cpp
    ${${local_lib_name}_SOURCE_DIR}/imgui_draw.cpp
    ${${local_lib_name}_SOURCE_DIR}/imgui_widgets.cpp
    ${${local_lib_name}_SOURCE_DIR}/imgui_tables.cpp
    # ${${local_lib_name}_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    # ${${local_lib_name}_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)
target_include_directories(${lib_name} PRIVATE "${${local_lib_name}_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${${local_lib_name}_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${lib_name})

print("✅ Configuring ${local_lib_name} Done")
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
