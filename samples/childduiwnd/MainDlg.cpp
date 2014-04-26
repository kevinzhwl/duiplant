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

#include "DuiChild.h"

HWND CMainDlg::OnRealWndCreate( CDuiRealWnd *pRealWnd )
{
	const CDuiRealWndParam & params=pRealWnd->GetRealWndParam();
	if(params.m_strClassName==_T("DUI"))
	{
		CDuiChild *pDuiChild=new CDuiChild;
		pDuiChild->Create(m_hWnd,0,WS_CHILD,0,0,0,0,0,0);
		pRealWnd->SetData(pDuiChild);
		return pDuiChild->m_hWnd;  
	}  
	return __super::OnRealWndCreate(pRealWnd);
}

void CMainDlg::OnRealWndDestroy( CDuiRealWnd *pRealWnd )
{
	const CDuiRealWndParam & params=pRealWnd->GetRealWndParam();
	if(params.m_strClassName==_T("DUI")) 
	{
		CDuiChild *pDuiChild=(CDuiChild *)pRealWnd->GetData();
		pDuiChild->DestroyWindow();
		delete pDuiChild;
		return;
	}
	__super::OnRealWndDestroy(pRealWnd);
}

void CMainDlg::OnDel()  
{
	CDuiRealWnd *pRealWnd=(CDuiRealWnd*)FindChildByCmdID(IDC_DUICHILD);
	pRealWnd->GetParent()->DestroyChild(pRealWnd);
}

