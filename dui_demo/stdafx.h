// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#include <duistd.h>
#include <duihostwnd.h>
#include <duictrls.h>
#include <duiwndnotify.h>
#include <DuiCSS.h>

#if defined(DLL_DUI)  && !defined(_WIN64)
#define LUA_TEST 
#endif

#ifdef LUA_TEST	//DLL version duiengine support lua
#include "..\scriptModule\luaScriptModule\luaScriptModule\luaScriptModule.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\scriptModule\\luaScriptModule\\lib\\luaScriptModule_d.lib")
#else
#pragma comment(lib,"..\\scriptModule\\luaScriptModule\\lib\\luaScriptModule.lib")
#endif

#endif


#include "resource.h"	//APP×ÊÔ´
#include "duires/winres.h"	//¿Ø¼þID

#include "../zlib/zconf.h"
#include "../zlib/zlib.h"

using namespace DuiEngine;

#ifdef _DEBUG

#if !defined(_WIN64)
#pragma comment(lib,"zlib_d.lib")
#endif

	#ifdef USING_ATL
	# pragma comment(lib, "duiengine_static_atl_d.lib")
	#elif DLL_DUI
	# pragma comment(lib, "duiengine_d.lib")
	#else
	# pragma comment(lib, "duiengine_static_d.lib")
	#endif
#else

#if !defined(_WIN64)
#pragma comment(lib,"zlib.lib")
#endif

	#ifdef DLL_DUI
	# pragma comment(lib, "duiengine.lib")
	#else
	# pragma comment(lib, "duiengine_static.lib")
	#endif

#endif





