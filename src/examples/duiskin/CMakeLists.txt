if(BUILD_examples)

    PCL_SUBSYS_DEPEND(build ${SUBSYS_NAME} DEPS surface)
	
	
#    PCL_ADD_EXAMPLE(pcl_test_nurbs_fitting_surface
#            FILES test_nurbs_fitting_surface.cpp
#                    LINK_WITH pcl_common pcl_io pcl_surface pcl_visualization)
                   
    file (GLOB_RECURSE APP_SRCS "src/*.cpp")
    file (GLOB_RECURSE APP_INCS "src/*.h")

    file (GLOB_RECURSE APP_SKINS "src/skin/*.*")

    file (GLOB APP_RES "src/duires/*.*" "src/duidemo.rc")

    set(ALL_SOURCES
        ${APP_SRCS} ${APP_INCS} ${APP_SKINS} ${APP_RES})
    set(PROJ_TARGET_NAME "duiskin")
    add_executable(${PROJ_TARGET_NAME} WIN32 ${ALL_SOURCES})

endif(BUILD_examples)

