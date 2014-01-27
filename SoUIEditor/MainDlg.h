// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UIHander.h"

class CMainDlg : public CDuiHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose()
	{
		AnimateHostWindow(200,AW_CENTER|AW_HIDE);
		EndDialog(IDCANCEL);
	}
	void OnMaximize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	void OnRestore()
	{
		SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	void OnMinimize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}

	void OnSize(UINT nType, CSize size)
	{
		SetMsgHandled(FALSE);
		if(!FindChildByName("btn_sys_close")) return;
		if(nType==SIZE_MAXIMIZED)
		{
			FindChildByName("btn_sys_restore")->SetVisible(TRUE);
			FindChildByName("btn_sys_maximize")->SetVisible(FALSE);
		}else if(nType==SIZE_RESTORED)
		{
			FindChildByName("btn_sys_restore")->SetVisible(FALSE);
			FindChildByName("btn_sys_maximize")->SetVisible(TRUE);
		}
	}
protected:
	virtual HWND OnRealWndCreate(CDuiRealWnd *pRealWnd);
	virtual void OnRealWndDestroy(CDuiRealWnd *pRealWnd);

	DUI_NOTIFY_MAP_BEGIN()
		DUI_NOTIFY_NAME_COMMAND("btn_sys_close", OnClose)
		DUI_NOTIFY_NAME_COMMAND("btn_sys_maximize", OnMaximize)
		DUI_NOTIFY_NAME_COMMAND("btn_sys_restore", OnRestore)
		DUI_NOTIFY_NAME_COMMAND("btn_sys_minimize", OnMinimize)
	DUI_NOTIFY_MAP_END()	

	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CLOSE(OnClose)//响应在系统菜单中关闭窗口消息
		MSG_WM_SIZE(OnSize)
		MSG_DUI_NOTIFY()
		CHAIN_MSG_MAP_MEMBER((*m_pUiHandler))
		CHAIN_MSG_MAP(CDuiHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

private:
	CUIHander *    m_pUiHandler; 
};
