//////////////////////////////////////////////////////////////////////////
//   File Name: Dui3DView.h
// Description: CDui3DView
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "image3d/3dTransform.h"
using namespace IMAGE3D;

namespace DuiEngine
{

class CDui3DView :
	public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDui3DView, "image3dview")
public:
	CDui3DView(void);
	~CDui3DView(void);

	PARAM3DTRANSFORM & Get3dParam(){return m_3dparam;}

	void Update();

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		/*DUIWIN_SKIN_ATTRIBUTE("image", m_pImage,TRUE)*/
		DUIWIN_INT_ATTRIBUTE("rotate-x", m_3dparam.nRotateX,TRUE)
		DUIWIN_INT_ATTRIBUTE("rotate-y", m_3dparam.nRotateY,TRUE)
		DUIWIN_INT_ATTRIBUTE("rotate-z", m_3dparam.nRotateZ,TRUE)
		DUIWIN_INT_ATTRIBUTE("offset-z", m_3dparam.nOffsetZ,TRUE)
	DUIWIN_DECLARE_ATTRIBUTES_END()
protected:
	void OnSize(UINT nType, CSize size);
	void OnPaint(CDCHandle dc);
	int OnCreate(LPVOID);

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_SIZE(OnSize)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CREATE(OnCreate)
	DUIWIN_END_MSG_MAP()

	//CDuiSkinBase *m_pImage;
	HBITMAP			m_hBmpOrig;
	HBITMAP			m_hBmpTrans;

	PARAM3DTRANSFORM	m_3dparam;
public:
  void SetBmpOrig(HBITMAP hBmpOrig) { m_hBmpOrig = hBmpOrig; }
};
}