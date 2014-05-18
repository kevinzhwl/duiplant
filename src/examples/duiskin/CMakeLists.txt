include(${CMAKE_SOURCE_DIR}/cmake/duix_utils.cmake)

if(BUILD_examples)

    set(EXAMPLE_TARGET_NAME "duiskin")

    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

    file(GLOB_RECURSE APP_SRCS "src/*.cpp")
    file(GLOB_RECURSE APP_INCS "src/*.h")
    file(GLOB_RECURSE APP_SKINS "src/skin/*.*")
    file(GLOB APP_RES "src/duires/*.*" "src/duidemo.rc")

    set(XML_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/skin/index.xml")
    set(RC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/duires/winres.rc2")
    set_source_files_properties( ${RC_FILE} PROPERTIES GENERATED TRUE )

    set(ALL_SOURCES
        ${APP_SRCS} ${APP_INCS} ${APP_SKINS} ${APP_RES} ${RC_FILE})


    add_definitions("-DUNICODE -D_UNICODE")
    add_executable(${EXAMPLE_TARGET_NAME} WIN32 ${ALL_SOURCES})

#$(DUITOOL_DIR)residbuilder2.exe" -i "%(FullPath)" -y -p skin -r .\duires\winres.rc2
   # SETDUIX_TOOLS_DIR("${CMAKE_SOURCE_DIR}/duixengine-installation/tools")
    #GETDUIX_BUILD_CMD(BUILD_CMD ${XML_FILE} ${RC_FILE})

    set(BUILD_CMD ${DUIX_RESBUILDER} -i ${XML_FILE} -y -p skin -r ${RC_FILE})
    MESSAGE(STATUS "${BUILD_CMD}")

    set(EXAMPLE_TARGET_SKINRES "${EXAMPLE_TARGET_NAME}_skinres")
    add_custom_target(${EXAMPLE_TARGET_SKINRES}
                   COMMAND ${BUILD_CMD}
                   COMMENT "Build DuiEngine Skin XML File"
                   )
    add_dependencies(${EXAMPLE_TARGET_NAME} ${EXAMPLE_TARGET_SKINRES} ${ZLIB_SHARED_NAME})

##   add_custom_command may (or not) work above vs2010
#    add_custom_command(TARGET ${EXAMPLE_TARGET_NAME}
 #                        PRE_BUILD
  #                      COMMAND ${BUILD_CMDA}
   #                      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    #                     COMMENT "comment:build duiskin "
     #                    VERBATIM
      #                  )

endif(BUILD_examples)

