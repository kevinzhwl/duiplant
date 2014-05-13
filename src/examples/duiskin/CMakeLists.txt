
if(BUILD_examples)

   # PCL_SUBSYS_DEPEND(build ${SUBSYS_NAME} DEPS surface)
	
	
#    PCL_ADD_EXAMPLE(pcl_test_nurbs_fitting_surface
#            FILES test_nurbs_fitting_surface.cpp
#                    LINK_WITH pcl_common pcl_io pcl_surface pcl_visualization)

    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

    file(GLOB_RECURSE APP_SRCS "src/*.cpp")
    file(GLOB_RECURSE APP_INCS "src/*.h")
    file(GLOB_RECURSE APP_SKINS "src/skin/*.*")
    file(GLOB APP_RES "src/duires/*.*" "src/duidemo.rc")

    set(ALL_SOURCES
        ${APP_SRCS} ${APP_INCS} ${APP_SKINS} ${APP_RES})

#$(DUITOOL_DIR)residbuilder2.exe" -i "%(FullPath)" -y -p skin -r .\duires\winres.rc2
    set(TOOL_DIR ${CMAKE_SOURCE_DIR}/duixengine-installation/tools)
    set(RESBULDER ${TOOL_DIR}/residbuilder2.exe)
    set(INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/skin/index.xml)
    set(OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/duires/winres.rc2)
    set(CMDARGS -i ${INPUT_FILE} -y -p skin -r ${OUTPUT_FILE})
    set(BUILD_CMD ${RESBULDER} ${CMDARGS})

    set(PROJ_TARGET_NAME "duiskin")
    add_definitions("-DUNICODE -D_UNICODE")

MESSAGE(${BUILD_CMD})
    add_executable(${PROJ_TARGET_NAME} WIN32 ${ALL_SOURCES})

    add_custom_command(TARGET ${PROJ_TARGET_NAME}
                         PRE_BUILD
                         COMMAND ${BUILD_CMD}
                         WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
                         COMMENT "comment:build duiskin "
                         VERBATIM
                        )
    set_source_files_properties( ${OUPUT_FILE} PROPERTIES GENERATED TRUE )

#    add_custom_target(skinres
 #                  COMMAND ${BUILD_CMD}
  #                 COMMENT "generate file"
   #                 )
    #add_dependencies( ${PROJ_TARGET_NAME} skinres )

endif(BUILD_examples)

