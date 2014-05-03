### ---[ PCL global CMake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

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

file ( GLOB_RECURSE ENGINE_EXTRA_SRCS "include/*.cpp" )
file ( GLOB_RECURSE ENGINE_SRCS "src/*.cpp" )

set(MFC_APP_SRCS
"dllmain.cpp"
)

set(CPP_SRCS
${ENGINE_SRCS}
${ENGINE_EXTRA_SRCS}
)


set(ALL_INCLUDES
    ${ENGINE_INCS}
    ${ENGINE_EXTRA_INCS}
)

set(ALL_SOURCES
    ${MFC_APP_SRCS}
    ${CPP_SRCS}
)

set(ALL_LIBRARIES
)


# Allow the developer to select if Dynamic or Static libraries are built
OPTION (SEG_BUILD_SHARED_LIBS "Build Shared Libraries" ON)
# Set the PROJ_TARGET_LIB_TYPE variable to STATIC
SET(PROJ_TARGET_LIB_TYPE STATIC)
IF(SEG_BUILD_SHARED_LIBS)
# User wants to build Dynamic Libraries, so change to 'SHARED'
  SET(PROJ_TARGET_LIB_TYPE SHARED)
ENDIF(SEG_BUILD_SHARED_LIBS)

add_library(${PROJ_TARGET_NAME} ${PROJ_TARGET_LIB_TYPE} ${ALL_SOURCES} )
target_link_libraries(${PROJ_TARGET_NAME} ${ALL_LIBRARIES})
