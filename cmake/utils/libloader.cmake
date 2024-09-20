
# Neatly loads all .cmake files from libs folder
function(includelibs)
    file(GLOB LIB_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} cmake/libs/*.cmake)
    # Exclude files starting with underscore
    list(FILTER LIB_FILES EXCLUDE REGEX "/\_.*")
    list(LENGTH LIB_FILES LIB_FILES_COUNT)

    if(NOT LIB_FILES_COUNT EQUAL 0)
        print_block_start()
        print("📚 Loading libraries")
        foreach(lib_file ${LIB_FILES})
            print("🧾 Configuring ${lib_file}")
            include(${lib_file})
        endforeach()
        print_block_end()
    endif()
endfunction(includelibs)
