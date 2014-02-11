//////////////////////////////////////////////////////////////////////////
//   File Name: duiembedbutton.h
// Description: DuiEmbedButton
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "duibuttonex.h"


namespace DuiEngine
{

//////////////////////////////////////////////////////////////////////////
// EmbedEdit
// Use src attribute specify a resource id
//
// Usage: <embedbutton />
//

class CEmbedButton:public CDuiButtonEx
{
  DUIOBJ_DECLARE_CLASS_NAME(CEmbedButton, "embedbutton")
public:
  CEmbedButton();
	CEmbedButton(CDuiWindow *pOwner);
	virtual ~CEmbedButton(){}

protected:
	void OnMouseHover(WPARAM wParam, CPoint ptPos);
	
	void OnMouseLeave();


	virtual LRESULT DuiNotify(LPDUINMHDR pnms);

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
	DUIWIN_END_MSG_MAP()
};

}