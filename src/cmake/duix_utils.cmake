

macro(SETDUIX_TOOLS_DIR _basedir)
  if (NOT DEFINED RESBUILDER_NAME)
    set(RESBUILDER_NAME "residbuilder2.exe")
  endif (NOT DEFINED RESBUILDER_NAME)
  if (NOT DEFINED ZIPBUILDER_NAME)
    set(RESBUILDER_NAME "7z.exe")
  endif (NOT DEFINED ZIPBUILDER_NAME)

    set(TOOLS_ROOT ${_basedir})
    set(DUIX_RESBUILDER "${TOOLS_ROOT}/${RESBUILDER_NAME}")
    set(DUIX_ZIPBUILDER "${TOOLS_ROOT}/${ZIPBUILDER_NAME}")

endmacro(SETDUIX_TOOLS_DIR)

macro(GETDUIX_BUILD_CMD _rescmd _xmlfile _rcfile)

if(NOT DEFINED DUIX_RESBUILDER)
    message(WARNING "Not Found Resbuilder")
else(NOT DEFINED DUIX_RESBUILDER)
    set(_rescmd ${RESBULDER} -i ${xmlfile} -y -p skin -r ${_rcfile})
endif(NOT DEFINED DUIX_RESBUILDER)

endmacro(GETDUIX_BUILD_CMD)
