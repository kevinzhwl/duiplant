#pragma once

class CMainDlg;

class CNewSkinDlg : public CDuiHostWnd
{
public:
	CNewSkinDlg(CMainDlg *pMainDlg);
	~CNewSkinDlg(void);

protected:
	void UpdateImglstPreview();
	void UpdateImgframePreview();

	LRESULT OnInitDialog(HWND wnd, LPARAM lParam);

	LRESULT OnEditNotify_imglst(LPDUINMHDR pNHdr);
	LRESULT OnEditNotify_imgframe(LPDUINMHDR pNHdr);

	void OnOK();

	DUI_NOTIFY_MAP_BEGIN()
		DUI_NOTIFY_NAME_HANDLER("edit_imglst_src_name",DUINM_RICHEDIT_NOTIFY,OnEditNotify_imglst)
		DUI_NOTIFY_NAME_HANDLER("edit_imglst_states",DUINM_RICHEDIT_NOTIFY,OnEditNotify_imglst)
		DUI_NOTIFY_NAME_COMMAND("chk_imglst_vert",UpdateImglstPreview)
		DUI_NOTIFY_NAME_COMMAND("chk_imglst_tile",UpdateImglstPreview)

		DUI_NOTIFY_NAME_HANDLER("edit_imgframe_src_name",DUINM_RICHEDIT_NOTIFY,OnEditNotify_imgframe)
		DUI_NOTIFY_NAME_HANDLER("edit_imgframe_states",DUINM_RICHEDIT_NOTIFY,OnEditNotify_imgframe)
		DUI_NOTIFY_NAME_HANDLER("edit_imgframe_frame",DUINM_RICHEDIT_NOTIFY,OnEditNotify_imgframe)
		DUI_NOTIFY_NAME_COMMAND("chk_imgframe_vert",UpdateImgframePreview)
		DUI_NOTIFY_NAME_COMMAND("chk_imgframe_tile",UpdateImgframePreview)

		DUI_NOTIFY_ID_COMMAND(IDOK,OnOK)
	DUI_NOTIFY_MAP_END()	

	BEGIN_MSG_MAP_EX(CNewSkinDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_DUI_NOTIFY()
		CHAIN_MSG_MAP(CDuiHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
	CMainDlg *m_pMainDlg;
};
