// MainDlg.cpp : implementation of the CLoginDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginDlg.h"
#include "UIHander.h"


#include "Dui3DView.h"



CLoginDlg::CLoginDlg() 
  : CDuiHostWnd(_T("IDR_DUI_MAIN_DIALOG"))

{
	m_pUiHandler = new CUIHander(this);
  SetDuiWindow(this);
  SetFrontSide("login_form");
  SetBackSide("set_form");
  SetCartoon("cartoon");
  SetYStep(10);
  SetZStep(140);
} 

CLoginDlg::~CLoginDlg()
{
	delete m_pUiHandler; 
}

void CLoginDlg::OnCancelSet()
{
  Turn(TRUE);
}

void CLoginDlg::OnConfirmSet()
{
  Turn(TRUE);
}

void CLoginDlg::OnLoginSet()
{
  Turn(FALSE);  
}