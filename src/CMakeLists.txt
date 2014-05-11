### ---[ PCL global CMake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PCL_SOURCE_DIR ${CMAKE_SOURCE_DIR})
include(${PCL_SOURCE_DIR}/cmake/duix_build_config.cmake)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "possible configurations" FORCE)

# In case the user does not setup CMAKE_BUILD_TYPE, assume it's RelWithDebInfo
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "build type default to RelWithDebInfo, set to Release to improve performance" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")

project(duixplant)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

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

include(${PCL_SOURCE_DIR}/cmake/pcl_targets.cmake)

set(LIB_INSTALL_DIR "lib")
set(BIN_INSTALL_DIR "bin")
set(PCL_OUTPUT_LIB_DIR ${PCL_BINARY_DIR}/${LIB_INSTALL_DIR})
set(PCL_OUTPUT_BIN_DIR ${PCL_BINARY_DIR}/${BIN_INSTALL_DIR})
make_directory(${PCL_OUTPUT_LIB_DIR})
make_directory(${PCL_OUTPUT_BIN_DIR})
if(WIN32)
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} "${PCL_OUTPUT_LIB_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} "${PCL_OUTPUT_BIN_DIR}")
    # ---[ Windows requires DLLs (shared libraries) to be installed in the same directory as executables
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} "${PCL_OUTPUT_BIN_DIR}")
  endforeach(config)
else(WIN32)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PCL_OUTPUT_LIB_DIR}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PCL_OUTPUT_BIN_DIR}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PCL_OUTPUT_LIB_DIR}")
endif(WIN32)

### ---[ Create the config.h file
set(pcl_config_h_in "${CMAKE_CURRENT_SOURCE_DIR}/pcl_config.h.in")
set(pcl_config_h "${CMAKE_CURRENT_BINARY_DIR}/include/pcl/pcl_config.h")
configure_file(${pcl_config_h_in} ${pcl_config_h})
PCL_ADD_INCLUDES(duixengine "" ${pcl_config_h})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

  set(PCL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/duixengine/include")
  #set(PCL_LIBRARY_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/@LIB_INSTALL_DIR@")


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

