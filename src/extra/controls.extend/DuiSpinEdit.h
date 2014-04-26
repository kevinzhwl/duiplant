#pragma once
#include "duiwnd.h"
#include "DuiRichEdit.h"

namespace DuiEngine
{


#define DUINM_SPINEDIT_NOTIFY	5164
typedef struct tagDUISPINEDITNOTIFY
{
	NMHDR hdr;
	int iPos;
	int iDelta;
} DUISPINEDITNOTIFY, *LPDUISPINEDITNOTIFY;

class CDuiSpinEdit : public CDuiRichEdit
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiSpinEdit, "spinedit")
public:
	CDuiSpinEdit();

public:
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()		
		DUIWIN_SKIN_ATTRIBUTE("upbtnskin", m_pUpSkinBtn, TRUE)
		DUIWIN_SKIN_ATTRIBUTE("downbtnskin", m_pDownSkinBtn, TRUE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

protected:
	CDuiSkinBase *m_pUpSkinBtn;
	CDuiSkinBase *m_pDownSkinBtn;

private:
	DWORD m_dwUpBtnState;
	DWORD m_dwDownBtnState;

protected:
	void OnLButtonDown(UINT nFlags,CPoint pt);
	void OnLButtonUp(UINT nFlags,CPoint pt);	
	void OnMouseMove(UINT nFlags,CPoint pt);
	void OnMouseLeave();
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	void GetUpBtnRect(LPRECT prc);
	void GetDownBtnRect(LPRECT prc);

	void OnPaint(CDCHandle dc);
	void MyDuiNotify(int iDelta);
	void OnDuiTimer(char cTimerID);
		

	DUIWIN_BEGIN_MSG_MAP()	
		MSG_WM_PAINT(OnPaint)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)		
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)	
		MSG_WM_LBUTTONDBLCLK(OnLButtonDown)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		MSG_WM_DUITIMER(OnDuiTimer)
	DUIWIN_END_MSG_MAP()
};

}