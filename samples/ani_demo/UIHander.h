#pragma once

class CMainDlg;

class CUIHander
{
public:
	CUIHander(CMainDlg *pMainDlg);
	~CUIHander(void);

protected:
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	void OnBtnClose();
	void OnBtnAnimate();
	
	BEGIN_MSG_MAP_EX(CUIHander)
		MSG_DUI_NOTIFY()
		MSG_WM_INITDIALOG(OnInitDialog)
	END_MSG_MAP()

	DUI_NOTIFY_MAP_BEGIN()
		DUI_NOTIFY_NAME_COMMAND("btn_ani", OnBtnAnimate)
		DUI_NOTIFY_NAME_COMMAND("btn_close", OnBtnClose)
	DUI_NOTIFY_MAP_END()	
private:
	CMainDlg * m_pMainDlg; 
};
