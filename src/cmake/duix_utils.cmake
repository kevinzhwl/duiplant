

macro(SETDUIX_TOOLS_DIR _basedir)
  if (NOT DEFINED RESBUILDER_NAME)
    set(RESBUILDER_NAME "residbuilder21.exe")
  endif (NOT DEFINED RESBUILDER_NAME)

  if (NOT DEFINED ZIPBUILDER_NAME)
    set(ZIPBUILDER_NAME "7z.exe")
  endif (NOT DEFINED ZIPBUILDER_NAME)

    set(TOOLS_ROOT ${_basedir})
    set(DUIX_RESBUILDER "${TOOLS_ROOT}/${RESBUILDER_NAME}")
    set(DUIX_ZIPBUILDER "${TOOLS_ROOT}/${ZIPBUILDER_NAME}")

endmacro(SETDUIX_TOOLS_DIR)

macro(GETDUIX_BUILD_CMD _rescmd _xmlfile _rcfile)

if(NOT DEFINED DUIX_RESBUILDER)
    message(STATUS "Not Found Resbuilder")
else(NOT DEFINED DUIX_RESBUILDER)
    set(_rescmd)
    set(_rescmd "${DUIX_RESBUILDER} -i ${_xmlfile} -y -p skin -r ${_rcfile}")
endif(NOT DEFINED DUIX_RESBUILDER)

endmacro(GETDUIX_BUILD_CMD)

macro(ADD_RESBUILD_TARGET _targename _xmlfile _rcfile)

    GETDUIX_BUILD_CMD(_BUILD_CMD ${_xmlfile} ${_rcfile})
    MESSAGE(STATUS ${_BUILD_CMD})

    add_custom_target(${_targetname}
                   COMMAND ${_BUILD_CMD}
                   COMMENT "Build DuiEngine Skin XML File"
                    )

endmacro(ADD_RESBUILD_TARGET)
