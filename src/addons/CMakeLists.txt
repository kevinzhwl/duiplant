set(SUBSYS_NAME addons)
set(SUBSYS_DESC "addons for duixengine")
#set(SUBSYS_DEPS )

set(DEFAULT TRUE)
set(REASON "Zlib are disabled by default.")
PCL_SUBSYS_OPTION(build ${SUBSYS_NAME} ${SUBSYS_DESC} ${DEFAULT} ${REASON})
PCL_SUBSYS_DEPEND(build ${SUBSYS_NAME} DEPS ${SUBSYS_DEPS})

if (build)

    # This looks for all addons/XXX/CMakeLists.txt
    file (GLOB addons_sbudirs */CMakeLists.txt)
    # Extract only relevant XXX and append it to DUIX_ADDONS_SUBDIRS
    foreach(subdir ${addons_sbudirs})
        # PATH of get_filename_component has problem dealing with windows shared folders "//xxx.xxx.xxx.xxx/folder"
        # Check here for the discussion: http://www.pcl-developers.org/Small-hack-to-get-filename-component-td5706691.html
        # Modified by Yangyan Li(yangyan.lee@gmail.com)
        # get_filename_component (dir ${subdir} PATH)
        get_filename_component (absolute ${subdir} ABSOLUTE)
        get_filename_component (name ${subdir} NAME)
        STRING(REGEX REPLACE ${name} "" dir ${absolute})
        list(APPEND DUIX_ADDONS_SUBDIRS ${dir})
    endforeach(subdir)
    # Display the found subdirectories
    message (STATUS "DUIX_ADDONS_SUBDIRS ${DUIX_ADDONS_SUBDIRS}")
    # Add the subdirectories
    foreach(subdir ${DUIX_ADDONS_SUBDIRS})
    add_subdirectory(${subdir})
    endforeach(subdir)

endif (build)
