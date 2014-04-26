#include "StdAfx.h"
#include "UIHander.h"

#include "MainDlg.h"

CUIHander::CUIHander(CMainDlg * pMainDlg) : m_pMainDlg(pMainDlg)
{
}

CUIHander::~CUIHander(void)
{
}

LRESULT CUIHander::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SetMsgHandled(FALSE); 
	//演示在程序初始化的时候通过如用户配置文件设置PANE的大小.
    return 0; 
}
