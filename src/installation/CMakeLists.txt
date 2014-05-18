
set(SUBSYS_NAME installation)
set(SUBSYS_DESC "installation for duixengine")

set(DEFAULT TRUE)
set(REASON "Code examples are disabled by default.")
PCL_SUBSYS_OPTION(build ${SUBSYS_NAME} ${SUBSYS_DESC} ${DEFAULT} ${REASON})
PCL_SUBSYS_DEPEND(build ${SUBSYS_NAME} DEPS ${SUBSYS_DEPS})

option(BUILD_INSTALLATION_CACHE "copy installation file to build dir" OFF)

if (build)

    file(GLOB_RECURSE INST_TOOLS "${CMAKE_CURRENT_SOURCE_DIR}/tools/*.*")
    file(GLOB_RECURSE INST_WTL "${CMAKE_CURRENT_SOURCE_DIR}/wtl81/*.*")
    file(GLOB_RECURSE INST_VSPROPS "${CMAKE_CURRENT_SOURCE_DIR}/vsprops/*.*")

    set(INST_ALL ${INST_TOOLS} ${INST_WTL} ${INST_VSPROPS})
    set(INST_DIRS tools wtl81 vsprops)

    if( BUILD_INSTALLATION_CACHE )

    foreach(file ${INST_ALL})
        get_filename_component (absolute ${file} ABSOLUTE)
        get_filename_component (name ${file} NAME)
        STRING(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" dir ${absolute})
        configure_file(${file} ${dir} COPYONLY)
    endforeach(file)

    endif(BUILD_INSTALLATION_CACHE)

    if(NOT SKIP_INSTALL_ALL )
    install(DIRECTORY ${INST_DIRS} DESTINATION "${CMAKE_INSTALL_PREFIX}")
    endif()



endif(build)
