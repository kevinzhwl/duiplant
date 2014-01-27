#pragma once

class CMainDlg;

class CUIHander
{
public:
	CUIHander(CMainDlg *pMainDlg);
	~CUIHander(void);

protected:
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	void OnBtnClick_ProjectOpen();
	LRESULT OnListCtrl_SelChanged(LPDUINMHDR pnmh);

	BEGIN_MSG_MAP_EX(CUIHander)
		MSG_DUI_NOTIFY()
		MSG_WM_INITDIALOG(OnInitDialog)
	END_MSG_MAP()

	DUI_NOTIFY_MAP_BEGIN()
		DUI_NOTIFY_NAME_HANDLER("prj_list_file",DUINM_LBSELCHANGED,OnListCtrl_SelChanged);
		DUI_NOTIFY_NAME_COMMAND("prg_btn_open", OnBtnClick_ProjectOpen)
	DUI_NOTIFY_MAP_END()	
private:
	CDuiStringT	m_strPrjPath;
	CMainDlg * m_pMainDlg; 
};
