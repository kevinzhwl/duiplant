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

#include "resource.h"	//APP资源
#include "duires/winres.h" //包含DUI资源定义

using namespace DuiEngine;

#ifdef _DEBUG
	# pragma comment(lib, "duiengine_static_d.lib")
#else
	# pragma comment(lib, "duiengine_static.lib")

#endif





