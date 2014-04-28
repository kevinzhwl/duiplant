#pragma once

#include <dui/DuiMenu.h> 


class CLoginDlg;

class CUIHander
{
public:
	CUIHander(CLoginDlg *pMainDlg);
	~CUIHander(void);

protected:
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	void OnMsgBtnClick();
  void OnStatusBtnClick();
	
  LRESULT OnComboNetListSelChanged(LPDUINMHDR pNHdr);
  LRESULT OnComboServListSelChanged(LPDUINMHDR pNHdr);
  LRESULT OnEditNotify(LPDUINMHDR pNHdr);

	BEGIN_MSG_MAP_EX(CUIHander)
		MSG_DUI_NOTIFY()
		MSG_WM_INITDIALOG(OnInitDialog)
	END_MSG_MAP()

	DUI_NOTIFY_MAP_BEGIN()
		DUI_NOTIFY_NAME_COMMAND("btn_msgbox", OnMsgBtnClick)
		DUI_NOTIFY_NAME_COMMAND("btn_status", OnStatusBtnClick)
		DUI_NOTIFY_ID_HANDLER(137,DUINM_RICHEDIT_NOTIFY,OnEditNotify)
		DUI_NOTIFY_ID_HANDLER(133,DUINM_LBSELCHANGED,OnComboNetListSelChanged)
		DUI_NOTIFY_ID_HANDLER(134,DUINM_LBSELCHANGED,OnComboServListSelChanged)
	DUI_NOTIFY_MAP_END()	
private:
	CLoginDlg * m_pMainDlg; 
};
