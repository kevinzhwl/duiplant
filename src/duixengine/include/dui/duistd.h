
#ifdef DLL_DUI
# ifdef DUIENGINE_EXPORTS
# pragma message("dll export")
#  define DUI_EXP __declspec(dllexport)
# else
#  define DUI_EXP __declspec(dllimport)
# endif // DUIENGINE_EXPORTS
#else
#define DUI_EXP
#endif

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0601
#define _RICHEDIT_VER	0x0200

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_NON_CONFORMING_SWPRINTFS
#endif

# pragma warning(disable:4661)
# pragma warning(disable:4251)
# pragma warning(disable:4100)	//unreferenced formal parameter

#include <Windows.h>
#include <CommCtrl.h>
#include <Shlwapi.h>
#include <OleCtl.h>
#include <tchar.h>
#include <stdio.h>

#include <dui/duidef.h>

//export pugixml interface
#include <pugixml/pugixml.hpp>

#include <dui/DuiUtilities.h>

#ifdef USING_ATL
	#define _COLL_NS	ATL
	#include <atlbase.h>
	#include <atlapp.h>
	#include <atlmisc.h>
	#include <atlgdi.h>
	#include <atlstr.h>
	#include <atlcoll.h>
	#include <atlcomcli.h>
	#define CDuiComPtr	CComPtr
	#define CDuiComQIPtr	CComQIPtr

	#include <dui/wtl.mini/duicrack.h>
	#define CDuiArray	CAtlArray
	#define CDuiList	CAtlList
	#define CDuiMap		CAtlMap
	#define CDuiStringA	CAtlStringA
	#define CDuiStringW CAtlStringW
	#define CDuiStringT CAtlString

	#include <dui/wtl.mini/strcpcvt.h>

#else//ATL_FREE
	#define _WTYPES_NS DuiEngine
	#define _COLL_NS	DuiEngine
	#include <dui/wtl.mini/duicrack.h>
	#include <dui/wtl.mini/duimisc.h>
	#include <dui/wtl.mini/duigdi.h>
// 	#include <dui/wtl.mini/duistr.h> 
	#include <dui/wtl.mini/tstring.h> 
	#include <dui/wtl.mini/strcpcvt.h>
	#include <dui/wtl.mini/duicoll.h>
	#include <dui/atl.mini/atldef.h>
	#include <dui/atl.mini/duicomcli.h>

#endif//USING_ATL


#include <dui/DuiAttrCrack.h>

#pragma comment(lib,"Msimg32.lib")
#pragma comment(lib,"shlwapi.lib")
