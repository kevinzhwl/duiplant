set(SUBSYS_NAME examples)
set(SUBSYS_DESC "examples for duixengine")
#set(SUBSYS_DEPS )

set(DEFAULT TRUE)
set(REASON "Code examples are disabled by default.")
PCL_SUBSYS_OPTION(build ${SUBSYS_NAME} ${SUBSYS_DESC} ${DEFAULT} ${REASON})
PCL_SUBSYS_DEPEND(build ${SUBSYS_NAME} DEPS ${SUBSYS_DEPS})

if (build)

    set(zlib_incs
            ${CMAKE_CURRENT_SOURCE_DIR}/../3rd/zlib/zconf.h
            ${CMAKE_CURRENT_SOURCE_DIR}/../3rd/zlib/zlib.h
        )
    PCL_ADD_INCLUDES(zlib "zlib" ${zlib_incs})
    set(ZLIB_LIBRARY_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../duixengine-installation/lib")
    include_directories(${ZLIB_INCLUDE_DIRS})
    link_directories(${ZLIB_LIBRARY_DIRS})

    include_directories(${ENGINE_INCLUDE_DIR})
    include_directories(${ZLIB_INCLUDE_DIR})

    # This looks for all examples/XXX/CMakeLists.txt
    file (GLOB examples_sbudirs */CMakeLists.txt)
    # Extract only relevant XXX and append it to PCL_EXAMPLES_SUBDIRS
    foreach(subdir ${examples_sbudirs})
        # PATH of get_filename_component has problem dealing with windows shared folders "//xxx.xxx.xxx.xxx/folder"
        # Check here for the discussion: http://www.pcl-developers.org/Small-hack-to-get-filename-component-td5706691.html
        # Modified by Yangyan Li(yangyan.lee@gmail.com)
        # get_filename_component (dir ${subdir} PATH)
        get_filename_component (absolute ${subdir} ABSOLUTE)
        get_filename_component (name ${subdir} NAME)
        STRING(REGEX REPLACE ${name} "" dir ${absolute})
        list(APPEND PCL_EXAMPLES_SUBDIRS ${dir})
    endforeach(subdir)
    # Display the found subdirectories
    message (STATUS "PCL_EXAMPLES_SUBDIRS ${PCL_EXAMPLES_SUBDIRS}")
    # Add the subdirectories
    foreach(subdir ${PCL_EXAMPLES_SUBDIRS})
    add_subdirectory(${subdir})
    endforeach(subdir)

endif (build)
