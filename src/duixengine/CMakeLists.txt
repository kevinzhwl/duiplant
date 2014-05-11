
set(SUBSYS_NAME duixengine)
set(SUBSYS_DESC "duixengine")
#set(SUBSYS_DEPS )

set(DEFAULT TRUE)
set(REASON "build engine are enabled by default.")
PCL_SUBSYS_OPTION(build ${SUBSYS_NAME} ${SUBSYS_DESC} ${DEFAULT} ${REASON})
PCL_SUBSYS_DEPEND(build ${SUBSYS_NAME} DEPS ${SUBSYS_DEPS})

if(build)

    #OPTION (DUIX_BUILD_SHARED_LIBS "Build Shared Libraries" ON)
    #OPTION (DUIX_BUILD_STATIC_LIBS "Build Static Libraries" OFF)
    #OPTION (DUIX_BUILD_WIN64_PLATFORM "Build X64 Platform" OFF)
    #OPTION (DUIX_BUILD_INSTALLATION "Build DuixEngine Installation" OFF)
    #OPTION (DUIX_BUILD_RELEASE "Build Release Version" OFF)

    #判断是32位编译还是64位编译。
    #在 Win32 配置下，_WIN32 有定义，_WIN64 没有定义。
    #在 x64 配置下，两者都有定义。即在 VC 下，_WIN32 一定有定义。
    #因此，WIN32/_WIN32 可以用来判断是否 Windows 系统（对于跨平台程序），
    #而 _WIN64 用来判断编译环境是 x86 还是 x64。附一个表
    set(DUIX_BUILD_WIN64_PLATFORM OFF)

    #include(cmake/mfc.cmake.in)
    set(DUIX_PROJECT_NAME "${SUBSYS_NAME}")
    set(DUIX_TARGET_PLATFORM "Win32")
    if(DUIX_BUILD_WIN64_PLATFORM)
    add_definitions("-D_WIN64")
    set(DUIX_WIN64 ON)
    set(DUIX_TARGET_PLATFORM "x64")
    MESSAGE("build duixengine-64bit")
    endif(DUIX_BUILD_WIN64_PLATFORM)

    add_definitions("-DUNICODE -D_UNICODE")

    if(WIN32)
        # lots of warnings with cl.exe right now, use /W1
        add_definitions("/W3 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS /bigobj")
    endif(WIN32)

    #set the C/C++ include path to the "include" directory
    #include_directories("${PROJECT_SOURCE_DIR}/include")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

    file( GLOB_RECURSE HEADER_INCS "*.h" "*.hpp" "*.tlh" "*.tli")

    file( GLOB_RECURSE ENGINE_INCS "${CMAKE_CURRENT_SOURCE_DIR}/include/dui/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/dui/*.hpp")
    file( GLOB_RECURSE ENGINE_EXTRA_INCS "${CMAKE_CURRENT_SOURCE_DIR}/include/dui/*.tlh" "${CMAKE_CURRENT_SOURCE_DIR}/include/dui/*.tli")
    file( GLOB PUGIXML_INCS "${CMAKE_CURRENT_SOURCE_DIR}/include/pugixml/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/pugixml/*.hpp")

    file( GLOB_RECURSE ENGINE_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
    file( GLOB PUGIXML_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/include/pugixml/*.cpp" )

    set(MFC_APP_SRCS
    "src/dllmain.cpp"
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
      ${HEADER_INCS}
    )

    set(ALL_LIBRARIES
        #shlwapi.lib
        #Msimg32.lib
        )

    #set(LIB_NAME pcl_${SUBSYS_NAME})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

    if(BUILD_duixengine_static)
        set(DUIX_TRAGET_STATIC_NAME "${DUIX_PROJECT_NAME}-${DUIX_TARGET_PLATFORM}-${CMAKE_BUILD_TYPE}-static")
        add_library("${DUIX_TRAGET_STATIC_NAME}" STATIC ${ALL_SOURCES} )
        #target_link_libraries("${DUIX_TRAGET_STATIC_NAME}" ${ALL_LIBRARIES})
    endif(BUILD_duixengine_static)


    if(BUILD_duixengine_shared)
        set(DUIX_TRAGET_SHARED_NAME "${DUIX_PROJECT_NAME}-${DUIX_TARGET_PLATFORM}-${CMAKE_BUILD_TYPE}-shared")
        #ADD_MSVC_PRECOMPILED_HEADER("include/dui/duistd.h" "src/duistd.cpp" ALL_SOURCES)
        add_library(${DUIX_TRAGET_SHARED_NAME} SHARED ${ALL_SOURCES} )
        target_link_libraries(${DUIX_TRAGET_SHARED_NAME} ${ALL_LIBRARIES})
        set_property(TARGET ${DUIX_TRAGET_SHARED_NAME}
         PROPERTY COMPILE_DEFINITIONS _USRDLL DUIENGINE_EXPORTS DLL_DUI )

#        PCL_ADD_LIBRARY(${LIB_NAME} ${SUBSYS_NAME} ${ALL_SOURCES} ${ALL_INCLUDES} )
#        target_link_libraries(${LIB_NAME} ${ALL_LIBRARIES} )
    #    PCL_MAKE_PKGCONFIG(${LIB_NAME} ${SUBSYS_NAME} "${SUBSYS_DESC}" "${SUBSYS_DEPS}" "" "" "" "")
        # Install include files
#        PCL_ADD_INCLUDES(${SUBSYS_NAME} ${SUBSYS_NAME} ${ALL_INCLUDES})

    endif(BUILD_duixengine_shared)

#/////////////////////////////////////////////////////////////////
# installation setting

        # set CMAKE Installation Options
        IF(DUIX_BUILD_INSTALLATION)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../${DUIX_PROJECT_NAME}-installation")
        ENDIF()

        # set customize Options
        set(DUIX_INSTALL_DIR_NAME "${DUIX_PROJECT_NAME}-install")
        set(DUIX_INSTALL_DIR "${CMAKE_SOURCE_DIR}/../${DUIX_INSTALL_DIR_NAME}")

        IF(DUIX_BUILD_INSTALLATION)
        set(DUIX_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}")
        ENDIF()

        #set the default path for built executables to the "bin" directory
        set(DUIX_INSTALL_EXEC_DIR ${DUIX_INSTALL_DIR}/bin)
        #set the default path for built libraries(shared) to the "lib" directory
        set(DUIX_INSTALL_LIB_DIR ${DUIX_INSTALL_DIR}/lib)
        #set the default path for built libraries(static)
        set(DUIX_INSTALL_ARCH_DIR ${DUIX_INSTALL_DIR}/lib)

        IF(BUILD_duixengine_static)
        install (
            TARGETS "${DUIX_TRAGET_STATIC_NAME}"
            RUNTIME DESTINATION ${DUIX_INSTALL_EXEC_DIR}
            LIBRARY DESTINATION ${DUIX_INSTALL_LIB_DIR}
            ARCHIVE DESTINATION ${DUIX_INSTALL_ARCH_DIR}
        )
        ENDIF(BUILD_duixengine_static)

        IF(BUILD_duixengine_shared)
        install (
            TARGETS "${DUIX_TRAGET_SHARED_NAME}"
            RUNTIME DESTINATION ${DUIX_INSTALL_EXEC_DIR}
            LIBRARY DESTINATION ${DUIX_INSTALL_LIB_DIR}
            ARCHIVE DESTINATION ${DUIX_INSTALL_ARCH_DIR}
        )
        ENDIF(BUILD_duixengine_shared)



        install (
            DIRECTORY include
            DESTINATION ${DUIX_INSTALL_DIR}
            FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.tli" PATTERN "*.tlh"
        )



endif(build)
