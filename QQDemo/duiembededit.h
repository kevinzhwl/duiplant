//////////////////////////////////////////////////////////////////////////
//   File Name: duiembededit.h
// Description: DuiEmbedEdit
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////
#pragma once

namespace DuiEngine
{

//////////////////////////////////////////////////////////////////////////
// EmbedEdit
// Use src attribute specify a resource id
//
// Usage: <embededit />
//

class CEmbedEdit:public CDuiEdit
{
  DUIOBJ_DECLARE_CLASS_NAME(CEmbedEdit, "embededit")
public:
  CEmbedEdit();
	CEmbedEdit(CDuiWindow *pOwner);
	virtual ~CEmbedEdit(){}

protected:
	void OnMouseHover(WPARAM wParam, CPoint ptPos);
	
	void OnMouseLeave();

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	virtual LRESULT DuiNotify(LPDUINMHDR pnms);

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_KEYDOWN(OnKeyDown)
	DUIWIN_END_MSG_MAP()
};

}