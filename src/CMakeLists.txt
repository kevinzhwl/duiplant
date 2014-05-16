### ---[ PCL global CMake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(duix)
string(TOLOWER ${PROJECT_NAME} DUIX_PROJECT_NAME)

#set(DUIX_SOURCE_DIR ${CMAKE_SOURCE_DIR})
include(${CMAKE_SOURCE_DIR}/cmake/duix_build_config.cmake)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "possible configurations" FORCE)

# In case the user does not setup CMAKE_BUILD_TYPE, assume it's RelWithDebInfo
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "build type default to Release" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")

### ---[ Find universal dependencies
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

# ---[ Release/Debug specific flags

#if(WIN32)
#  if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
#    set(CMAKE_DEBUG_POSTFIX "_debug")
#  endif()
#  if(NOT DEFINED CMAKE_RELEASE_POSTFIX)
#    set(CMAKE_RELEASE_POSTFIX "_release")
#  endif()
#endif()

# Update the documentation string of CMAKE_BUILD_TYPE for GUIs
SET(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Maintainer."
    FORCE)

include(${CMAKE_SOURCE_DIR}/cmake/pcl_utils.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/pcl_targets.cmake)
#set(PCL_VERSION 1.7.0 CACHE STRING "PCL version")
#DISSECT_VERSION()
GET_OS_INFO()
SET_INSTALL_DIRS()

#set(PCL_BINARY_DIR ${CMAKE_BINARY_DIR})
#set(DUIX_INSTALL_LIB_DIR "lib")
#set(DUIX_INSTALL_BIN_DIR "bin")
set(DUIX_OUTPUT_LIB_DIR ${CMAKE_BINARY_DIR}/${INSTALLATION_LIB_DIR})
set(DUIX_OUTPUT_BIN_DIR ${CMAKE_BINARY_DIR}/${INSTALLATION_BIN_DIR})
make_directory(${DUIX_OUTPUT_LIB_DIR})
make_directory(${DUIX_OUTPUT_BIN_DIR})
set(INSTALLATION_INCLUDE_DIR "include")
set(DUIX_OUTPUT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/${INSTALLATION_INCLUDE_DIR})
make_directory(${DUIX_OUTPUT_BIN_DIR})

if(WIN32)
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} "${DUIX_OUTPUT_LIB_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} "${DUIX_OUTPUT_BIN_DIR}")
    # ---[ Windows requires DLLs (shared libraries) to be installed in the same directory as executables
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} "${DUIX_OUTPUT_BIN_DIR}")
  endforeach(config)
else(WIN32)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${DUIX_OUTPUT_LIB_DIR}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${DUIX_OUTPUT_BIN_DIR}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${DUIX_OUTPUT_LIB_DIR}")
endif(WIN32)

### ---[ Create the config.h file
set(duix_config_h_in "${CMAKE_CURRENT_SOURCE_DIR}/duix_config.h.in")
set(duix_config_h "${CMAKE_CURRENT_BINARY_DIR}/include/duix_config.h")
configure_file(${duix_config_h_in} ${duix_config_h})
PCL_ADD_INCLUDES(duix "" ${duix_config_h})
include_directories(${DUIX_OUTPUT_INCLUDE_DIR})

set(ENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/duixengine/include")
set(ZLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/addons")
#set(PCL_LIBRARY_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/@INSTALLATION_LIB_DIR@")

IF(DUIX_BUILD_INSTALLATION AND CMAKE_INSTALL_PREFIX)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../${DUIX_PROJECT_NAME}-installation")
ENDIF()


file (GLOB modules_subdirs */CMakeLists.txt)

    foreach(subdir ${modules_subdirs})
        # PATH of get_filename_component has problem dealing with windows shared folders "//xxx.xxx.xxx.xxx/folder"
        # Check here for the discussion: http://www.pcl-developers.org/Small-hack-to-get-filename-component-td5706691.html
        # Modified by Yangyan Li(yangyan.lee@gmail.com)
        # get_filename_component (dir ${subdir} PATH)
        get_filename_component (absolute ${subdir} ABSOLUTE)
        get_filename_component (name ${subdir} NAME)
        STRING(REGEX REPLACE ${name} "" dir ${absolute})
        list(APPEND PCL_MODULES_DIRS ${dir})
    endforeach(subdir)
    # Display the found subdirectories
    message (STATUS "PCL_MODULES_DIRS ${PCL_MODULES_DIRS}")
    # Add the subdirectories
    foreach(subdir ${PCL_MODULES_DIRS})
    add_subdirectory(${subdir})
    endforeach(subdir)

