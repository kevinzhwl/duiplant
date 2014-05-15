#include "stdafx.h"

extern "C"
{
#include "../lua-5.1/lua.h"
#include "../lua-5.1/lualib.h"
#include "../lua-5.1/lauxlib.h"
};

#include "../lua_tinker.h"

using namespace DuiEngine;

#include "ExpDuiBasic.h"
#include "ExpDuiSystem.h"
#include "ExpDuiWindow.h"
#include "ExpDuiMessageBox.h"
#include "ExpDuiScriptModule.h"
#include "ExpDuiThreadActiveWndMgr.h"
#include "ExpDuiResProvider.h"

BOOL DuiEngine_Export_Lua(lua_State *L)
{
	lua_tinker::init(L);
	BOOL bRet=ExpLua_Basic(L);
	bRet=ExpLua_DuiSystem(L);
	bRet=ExpLua_DuiWindow(L);
	bRet=ExpLua_DuiMessageBox(L);
	bRet=ExpLua_DuiScriptModule(L);
	bRet=ExpLua_DuiThreadActiveWndMgr(L);
	bRet=ExpLua_DuiResProvider(L);

	return bRet;
}