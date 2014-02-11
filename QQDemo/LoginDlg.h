// MainDlg.h : interface of the CLoginDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UIHander.h"
#include "wtlhelper/whwindow.h"
#include "image3d/3dTransform.h"
#include "duiturn3dview.h"

class CLoginDlg : public CDuiHostWnd
  ,public CWHRoundRectFrameHelper<CLoginDlg>	//需要圆角窗口时启用
  ,public CDuiTurn3dView
{
public:
	CLoginDlg();
	~CLoginDlg();

	void OnClose()
	{
		EndDialog(IDCANCEL);
	}

  void OnMini()
  {
    ::ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
  }

  void OnLoginSet();
  void OnCancelSet();
  void OnConfirmSet();
protected:

	DUI_NOTIFY_MAP_BEGIN()
		DUI_NOTIFY_ID_COMMAND(1, OnClose)
    DUI_NOTIFY_ID_COMMAND(2, OnMini)    
    DUI_NOTIFY_ID_COMMAND(3, OnLoginSet)
    DUI_NOTIFY_ID_COMMAND(131, OnCancelSet)
    DUI_NOTIFY_ID_COMMAND(132, OnConfirmSet)
	DUI_NOTIFY_MAP_END()	

	BEGIN_MSG_MAP_EX(CLoginDlg)    
    CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CLoginDlg>) //需要圆角窗口时启用
		MSG_WM_CLOSE(OnClose)
		MSG_DUI_NOTIFY()
		CHAIN_MSG_MAP_MEMBER((*m_pUiHandler))
		CHAIN_MSG_MAP(CDuiHostWnd)
    CHAIN_MSG_MAP(CDuiTurn3dView)
		REFLECT_NOTIFICATIONS_EX()

	END_MSG_MAP()

private:
	CUIHander *      m_pUiHandler; 

};
