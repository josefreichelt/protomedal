# Copy everything from assets folder to bin folder
if(NOT EMSCRIPTEN)
    file(GLOB ASSET_FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
    list(LENGTH ASSET_FILES ASSET_FILES_COUNT)
    if (NOT ASSET_FILES_COUNT EQUAL 0)
        print_block("🖌️  Copying ${ASSET_FILES_COUNT} assets")
        file(COPY ${ASSET_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
    endif()
endif()


# Naive approach to copy dlls to output folder
if(WIN32 AND NOT EMSCRIPTEN)
    # Copy all .dll files from lib folder
    file(GLOB_RECURSE DLL_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/deps/*.dll)
    print_block("📚  Copying DLLs" DLL_FILES)
    file(COPY ${DLL_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
