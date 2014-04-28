// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#include <dui\duistd.h>
#include <dui\duihostwnd.h>
#include <dui\duictrls.h>
#include <dui\duiwndnotify.h>
#include <dui\DuiCSS.h>

#if defined(DLL_DUI)  && !defined(_WIN64)
#define LUA_TEST 
#endif

#ifdef LUA_TEST	//DLL version duiengine support lua
#include <modules\luaScriptModule\luaScriptModule.h>

#ifdef _DEBUG
#pragma comment(lib,"luaScriptModule-win32-debug-shared.lib")
#else
#pragma comment(lib,"luaScriptModule-win32-release-shared.lib")
#endif

#endif


#include "resource.h"	//APP×ÊÔ´
#include "duires/winres.h"	//¿Ø¼þID

#include <zlib/zconf.h>
#include <zlib/zlib.h>

using namespace DuiEngine;

#ifdef _DEBUG

#if defined(_WIN64)

#pragma comment(lib,"zlib-x64-debug.lib")

	#if defined(USING_ATL)
	# pragma comment(lib, "duiengine-x64-debug-atl.lib")
	#elif defined(DLL_DUI)
	# pragma comment(lib, "duiengine-x64-debug-shared.lib")
	#else
	# pragma comment(lib, "duiengine-x64-debug-static.lib")
	#endif

#else

#pragma comment(lib,"zlib-win32-debug.lib")

	#if defined(USING_ATL)
	# pragma comment(lib, "duiengine-win32-debug-atl.lib")
	#elif defined(DLL_DUI)
	# pragma comment(lib, "duiengine-win32-debug-shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-debug-static.lib")
	#endif

#endif

#else

#if defined(_WIN64)
#pragma comment(lib,"zlib-x64-release.lib")

	#if defined DLL_DUI
	# pragma comment(lib, "duiengine-x64-release-shared.lib")
	#else
	# pragma comment(lib, "duiengine-x64-release-static.lib")
	#endif

#else
#pragma comment(lib,"zlib-win32-release.lib")

	#if defined DLL_DUI
	# pragma comment(lib, "duiengine-win32-release-shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-release-static.lib")
	#endif

#endif


#endif





