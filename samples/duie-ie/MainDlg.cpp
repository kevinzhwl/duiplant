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
