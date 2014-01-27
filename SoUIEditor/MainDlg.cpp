// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "UIHander.h"
#include "ScintillaWnd.h"

CMainDlg::CMainDlg() : CDuiHostWnd(_T("IDR_DUI_MAIN_DIALOG"))
{
	m_pUiHandler = new CUIHander(this);
} 

CMainDlg::~CMainDlg()
{
	delete m_pUiHandler; 
}


HWND CMainDlg::OnRealWndCreate( CDuiRealWnd *pRealWnd )
{
	if(pRealWnd->GetRealWndParam().m_strClassName==_T("scintilla"))
	{
		CScintillaWnd *pWnd=new CScintillaWnd;
		BOOL bOK=pWnd->Create(pRealWnd->GetRealWndParam().m_strWindowName,WS_CHILD,CRect(0,0,0,0),pRealWnd->GetContainer()->GetHostHwnd(),pRealWnd->GetCmdID(),DuiSystem::getSingleton().GetInstance());
		if(!bOK)
		{
			DUIASSERT(FALSE);
			delete pWnd;
			return 0;
		}
		pRealWnd->SetUserData((ULONG_PTR)pWnd);
		return pWnd->m_hWnd;
	}else
	{
		return __super::OnRealWndCreate(pRealWnd);
	}
}

void CMainDlg::OnRealWndDestroy( CDuiRealWnd *pRealWnd )
{
	if(pRealWnd->GetRealWndParam().m_strClassName==_T("scintilla"))
	{
		CScintillaWnd *pWnd=(CScintillaWnd *)pRealWnd->GetUserData();
		if(pWnd)
		{
			pWnd->DestroyWindow();
			delete pWnd;
		}
	}else
	{
		__super::OnRealWndDestroy(pRealWnd);
	}
}