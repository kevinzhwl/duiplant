### ---[ PCL global CMake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_DEBUG_POSTFIX "")
set(CMAKE_RELEASE_POSTFIX "")

OPTION (DUIX_BUILD_SHARED_LIBS "Build Shared Libraries" ON)
OPTION (DUIX_BUILD_STATIC_LIBS "Build Static Libraries" ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "possible configurations" FORCE)

# In case the user does not setup CMAKE_BUILD_TYPE, assume it's RelWithDebInfo
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "build type default to RelWithDebInfo, set to Release to improve performance" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")

project(DuiXEngine)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
set(PROJ_TARGET_NAME DuiXEngine)


#set the C/C++ include path to the "include" directory
include_directories("${PROJECT_SOURCE_DIR}/include")

file ( GLOB_RECURSE ENGINE_INCS "include/*.h" "include/*.hpp")
file ( GLOB_RECURSE ENGINE_EXTRA_INCS "include/*.tlh" "include/*.tli")
file ( GLOB_RECURSE ENGINE_INCS "include/pugixml/*.h" "include/pugixml/*.hpp")

file ( GLOB_RECURSE ENGINE_SRCS "src/*.cpp" )
file ( GLOB_RECURSE PUGIXML_SRCS "include/pugixml/*.cpp" )

set(MFC_APP_SRCS
"dllmain.cpp"
)

set(CPP_SRCS
${ENGINE_SRCS}
${ENGINE_EXTRA_SRCS}
${PUGIXML_SRCS}
)


set(ALL_INCLUDES
    ${ENGINE_INCS}
    ${ENGINE_EXTRA_INCS}
    ${PUGIXML_INCS}
)

set(ALL_SOURCES
    ${MFC_APP_SRCS}
    ${CPP_SRCS}
)

set(ALL_LIBRARIES
)

source_group(engine FILES ${ENGINE_INCS})

if (WIN32)
    # lots of warnings with cl.exe right now, use /W1
    add_definitions("/W3 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS /bigobj")
else(WIN32)
    add_definitions( "-Wall -Wno-unknown-pragmas -Wno-unused-function" )
endif(WIN32)

if (WIN32)
    set(DUIX_TARGET_PLATFORM "Win32")
else(WIN32)
    set(DUIX_TARGET_PLATFORM "x64")
endif(WIN32)

set(DUIX_TRAGET_STATIC_NAME "${PROJECT_NAME}-${DUIX_TARGET_PLATFORM}-${CMAKE_BUILD_TYPE}-static")
set(DUIX_TRAGET_SHARED_NAME "${PROJECT_NAME}-${DUIX_TARGET_PLATFORM}-${CMAKE_BUILD_TYPE}-shared")

IF(DUIX_BUILD_SHARED_LIBS)
add_library("${DUIX_TRAGET_SHARED_NAME}" SHARED ${ALL_SOURCES} )
target_link_libraries("${DUIX_TRAGET_SHARED_NAME}" ${ALL_LIBRARIES})
set_property(TARGET "${DUIX_TRAGET_SHARED_NAME}"
 PROPERTY COMPILE_DEFINITIONS _USRDLL DUIENGINE_EXPORTS DLL_DUI )
ENDIF()


IF(DUIX_BUILD_STATIC_LIBS)
add_library("${DUIX_TRAGET_STATIC_NAME}" STATIC ${ALL_SOURCES} )
target_link_libraries("${DUIX_TRAGET_STATIC_NAME}" ${ALL_LIBRARIES})
ENDIF()

IF(DUIX_BUILD_SHARED_LIBS)
ENDIF()
IF(DUIX_BUILD_STATIC_LIBS)
ENDIF()


# set customize Options
set(DUIX_INSTALL_DIR_NAME "${PROJECT_NAME}-install")
set(DUIX_INSTALL_DIR "${CMAKE_SOURCE_DIR}/../${DUIX_INSTALL_DIR_NAME}")
# set CMAKE Options
set(CMAKE_INSTALL_PREFIX "${DUIX_INSTALL_DIR}")

#set the default path for built executables to the "bin" directory
set(DUIX_EXEC_INSTALL_DIR ${DUIX_INSTALL_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(DUIX_LIB_INSTALL_DIR ${DUIX_INSTALL_DIR}/lib)

IF(DUIX_BUILD_SHARED_LIBS)
install (
    TARGETS "${DUIX_TRAGET_SHARED_NAME}"
    RUNTIME DESTINATION ${DUIX_EXEC_INSTALL_DIR}
    LIBRARY DESTINATION ${DUIX_LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${DUIX_LIB_INSTALL_DIR}
)
ENDIF()

IF(DUIX_BUILD_STATIC_LIBS)
install (
    TARGETS "${DUIX_TRAGET_STATIC_NAME}"
    RUNTIME DESTINATION ${DUIX_EXEC_INSTALL_DIR}
    LIBRARY DESTINATION ${DUIX_LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${DUIX_LIB_INSTALL_DIR}
)
ENDIF()

install (
    DIRECTORY include
    DESTINATION ${DUIX_INSTALL_DIR}
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.tli" PATTERN "*.tlh"
)
