#pragma once
#include <dui/duiwnd.h>
#include "DuiSkinGif.h"

namespace DuiEngine
{

class CDuiGifControl : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiGifControl, "gifplayer")
public:
	CDuiGifControl();
	~CDuiGifControl();

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()		
		DUIWIN_CUSTOM_ATTRIBUTE("skin", OnAttrGif)		
	DUIWIN_DECLARE_ATTRIBUTES_END()

protected:
	HRESULT OnAttrGif(const CDuiStringA & strValue, BOOL bLoading);

	virtual CSize GetDesiredSize(LPRECT pRcContainer);

	void OnPaint(CDCHandle dc);
	void OnDuiTimer(char cTimerID);
	void OnShowWindow(BOOL bShow, UINT nStatus);

	DUIWIN_BEGIN_MSG_MAP()	
		
		MSG_WM_DUITIMER(OnDuiTimer)
		MSG_WM_SHOWWINDOW(OnShowWindow)
		MSG_WM_PAINT(OnPaint)			
	DUIWIN_END_MSG_MAP()

private:
	CDuiSkinGif *m_pgif;
	int	m_iCurFrame;
};

}