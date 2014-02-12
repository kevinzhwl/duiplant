#include "StdAfx.h"
#include "UIHander.h"

#include "LoginDlg.h"

CUIHander::CUIHander(CLoginDlg * pMainDlg) : m_pMainDlg(pMainDlg)
{
}

CUIHander::~CUIHander(void)
{
}

LRESULT CUIHander::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SetMsgHandled(FALSE); 

  HICON hIcon = ::LoadIcon((HMODULE)::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINWND));
  ::SendMessage(hWnd, WM_SETICON, TRUE, (LPARAM)hIcon);

	TCHAR szCurrentDir[MAX_PATH+1]; 
  memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, MAX_PATH );

	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   


  CDuiFlashCtrl* pFlash = (CDuiFlashCtrl*)m_pMainDlg->FindChildByName("ctrl_flash");
  if( NULL != pFlash )
  {
	  pFlash->GetFlashInterface()->put_Movie(_bstr_t(CDuiStringT(szCurrentDir) + _T("\\qqres\\login\\morning.swf")));
  }

  CDuiStringA strDisable[] = {"btn_test_net_set", 
    "net_cfg_addr_edt", "net_cfg_user_edt", "net_cfg_pswd_edt", 
    "net_cfg_port_edt", "net_cfg_field_edt", "serv_cfg_addr_edt",
    "serv_cfg_port_edt"};
  CDuiWindow* pDuiWindow = NULL;
  int i;
  for(i = 0; i < 8; i++)
  {
    pDuiWindow = m_pMainDlg->FindChildByName(strDisable[i]);
    if( NULL != pDuiWindow )
    {
      pDuiWindow->ModifyState(DuiWndState_Disable, 0, TRUE);
    }
  }

 	CDuiRichEdit *pEdit=(CDuiRichEdit*)m_pMainDlg->FindChildByCmdID(137);
 	pEdit->DuiSendMessage(EM_SETEVENTMASK,0,ENM_CHANGE);


  return 0; 
}

void CUIHander::OnMsgBtnClick()
{
	DuiMessageBox(NULL,_T("messagebox test"),_T("tip"),MB_YESNOCANCEL|MB_ICONWARNING);
}



LRESULT CUIHander::OnComboNetListSelChanged( LPDUINMHDR pNHdr )
{
	HDUIWND hFocus=m_pMainDlg->GetDuiFocus();
	DUITRACE(_T("duifocus=%d\n"),hFocus);
	LPDUINMLBSELCHANGE pLbSelChange=(LPDUINMLBSELCHANGE)pNHdr;
	CDuiComboBox *pCombobox=(CDuiComboBox*)m_pMainDlg->FindChildByCmdID(133);
  int nCurSel = pCombobox->GetCurSel();

  CDuiWindow* pDuiWindow = NULL;
  CDuiStringA strDisable[] = {"net_cfg_addr_edt", 
    "net_cfg_user_edt", "net_cfg_pswd_edt", 
    "net_cfg_port_edt", "net_cfg_field_edt"};

  BOOL bEnable = FALSE;

  if(1 == nCurSel || 2 == nCurSel)
  {
    bEnable = TRUE;
  }
  else
  {
    bEnable = FALSE;
  }


  int i;
  for(i = 0; i < 5; i++)
  {
    pDuiWindow = m_pMainDlg->FindChildByName(strDisable[i]);
    if( NULL != pDuiWindow )
    {
		pDuiWindow->EnableWindow(bEnable,TRUE);
    }
  }

  CDuiEdit* pEdit = (CDuiEdit*)m_pMainDlg->FindChildByName("net_cfg_port_edt");
  CDuiStringT str;
  switch(nCurSel)
  {
  case 1:
    {      
      str = _T("80");
    }
    break;
  case 2:
    {      
      str = _T("1080");
    }
    break;
  default:
    str = _T("");
    break;
  }

  if(NULL != pEdit)
  {
    pEdit->SetWindowText(str);
  }
	return S_OK;
}


LRESULT CUIHander::OnComboServListSelChanged( LPDUINMHDR pNHdr )
{
	LPDUINMLBSELCHANGE pLbSelChange=(LPDUINMLBSELCHANGE)pNHdr;
	CDuiComboBox *pCombobox=(CDuiComboBox*)m_pMainDlg->FindChildByCmdID(134);
  int nCurSel = pCombobox->GetCurSel();

  CDuiWindow* pDuiWindow = NULL;
  CDuiStringA strDisable[] = {"serv_cfg_addr_edt", 
    "serv_cfg_port_edt"};

  BOOL bEnable = FALSE;

  if(1 == nCurSel || 2 == nCurSel)
  {
    bEnable = TRUE;
  }
  else
  {
    bEnable = FALSE;
  }


  int i;
  for(i = 0; i < 2; i++)
  {
    pDuiWindow = m_pMainDlg->FindChildByName(strDisable[i]);
    if( NULL != pDuiWindow )
    {
		pDuiWindow->EnableWindow(bEnable,TRUE);
    }
  }

  CDuiStringT str1, str2;
  switch(nCurSel)
  {
  case 1:
    {
      str1 = _T("8000");
      str2 = _T("183.60.48.174");
      CDuiEdit* pEdit = (CDuiEdit*)m_pMainDlg->FindChildByName("serv_cfg_port_edt");
      if(NULL != pEdit)
      {
        pEdit->SetWindowText(_T("8000"));
      }

      pEdit = (CDuiEdit*)m_pMainDlg->FindChildByName("serv_cfg_addr_edt");
      if(NULL != pEdit)
      {
        pEdit->SetWindowText(_T("183.60.48.174"));
      }

      
    }
    break;
  case 2:
    {
      str1 = _T("443");
      str2 = _T("183.60.48.171");


    }
    break;
    str1 = _T("");
    str2 = _T("");
  default:
    break;
  }

  CDuiEdit* pEdit = (CDuiEdit*)m_pMainDlg->FindChildByName("serv_cfg_port_edt");
  if(NULL != pEdit)
  {
    pEdit->SetWindowText(str1);
  }

  pEdit = (CDuiEdit*)m_pMainDlg->FindChildByName("serv_cfg_addr_edt");
  if(NULL != pEdit)
  {
    pEdit->SetWindowText(str2);
  }
	return S_OK;
}

void CUIHander::OnStatusBtnClick()
{
	//CPoint pt; 
	//GetCursorPos(&pt);
	//CDuiMenu menu;  
	//menu.LoadMenu(_T("IDR_MENU_STATUS1")); //load menu

	//UINT uRet=menu.TrackPopupMenu(0,pt.x,pt.y,m_pMainDlg->m_hWnd);  
}

LRESULT CUIHander::OnEditNotify( LPDUINMHDR pNHdr )
{
	LPDUIRICHEDITNOTIFY pEditNotify=(LPDUIRICHEDITNOTIFY)pNHdr;
	if(pEditNotify->iNotify==EN_CHANGE)
	{
    CDuiEdit* pEdit = (CDuiEdit*)m_pMainDlg->FindChildByName("net_cfg_addr_edt");
    if(NULL != pEdit)
    {
      TCHAR tchText[256];
      pEdit->GetWindowText(tchText, 255);
      CDuiWindow* pDuiWindow = m_pMainDlg->FindChildByName("btn_test_net_set");
      if(_tcslen(tchText) > 0)
      {        
        if(NULL != pDuiWindow)
        {
			pDuiWindow->EnableWindow(TRUE,TRUE);
        }
      }
      else
      {
        if(NULL != pDuiWindow)
        {
			pDuiWindow->EnableWindow(FALSE,TRUE);
        }
      }
    }    
	}
	return S_OK;
}