// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

// #define DLL_DUI
#include <dui/duistd.h>
#include <dui/duihostwnd.h>
#include <dui/duictrls.h>
#include <dui/duiwndnotify.h>
#include <dui/DuiCSS.h>


#include "resource.h"	//APP×ÊÔ´
#include "duires/winres.h"	//¿Ø¼þID

using namespace DuiEngine;

#ifdef _DEBUG
	#ifdef DLL_DUI
	# pragma comment(lib, "duiengine-win32-debug-shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-debug-static.lib")
	#endif
#else
	#ifdef DLL_DUI
	# pragma comment(lib, "duiengine-win32-release-shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-release-static.lib")
	#endif

#endif




