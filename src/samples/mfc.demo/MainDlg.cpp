// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "UIHander.h"

CMainDlg::CMainDlg() : CDuiHostWnd(_T("IDR_DUI_MAIN_DIALOG"))
{
	m_pUiHandler = new CUIHander(this);
} 

CMainDlg::~CMainDlg()
{
	delete m_pUiHandler; 
}

HWND CMainDlg::OnRealWndCreate( DuiEngine::CDuiRealWnd *pRealWnd )
{
	const DuiEngine::CDuiRealWndParam &param=pRealWnd->GetRealWndParam();
	if(param.m_strClassName==_T("button"))
	{
		CButton *pbtn=new CButton;
		pbtn->Create(param.m_strWindowName,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(0,0,0,0),CWnd::FromHandle(pRealWnd->GetContainer()->GetHostHwnd()),pRealWnd->GetCmdID());
		pRealWnd->SetData(pbtn);
		return pbtn->m_hWnd;
	}
	return __super::OnRealWndCreate(pRealWnd);
}

void CMainDlg::OnRealWndDestroy( DuiEngine::CDuiRealWnd *pRealWnd )
{
	const DuiEngine::CDuiRealWndParam &param=pRealWnd->GetRealWndParam();
	if(param.m_strClassName==_T("button"))
	{
		CButton *pbtn=(CButton*) pRealWnd->GetData();
		if(pbtn)
		{
			pbtn->DestroyWindow();
			delete pbtn;
		}
		return ;
	}
	__super::OnRealWndDestroy(pRealWnd);
}
