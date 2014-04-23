//////////////////////////////////////////////////////////////////////////
//   File Name: Dui3DView.h
// Description: Dui3DView
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Dui3DView.h"


namespace DuiEngine
{

	CDui3DView::CDui3DView(void):m_hBmpOrig(NULL),m_hBmpTrans(NULL)
	{
		memset(&m_3dparam,0,sizeof(m_3dparam));
	}

	CDui3DView::~CDui3DView(void)
	{
		//if(m_hBmpOrig) DeleteObject(m_hBmpOrig);
		if(m_hBmpTrans) DeleteObject(m_hBmpTrans);
	}

	int DuiEngine::CDui3DView::OnCreate( LPVOID )
	{
		__super::OnCreate(NULL);

		return 0;
	}

	void CDui3DView::OnSize( UINT nType, CSize size )
	{
		HDC hdc=GetDC(NULL);

		m_hBmpTrans=CGdiAlpha::CreateBitmap32(hdc,size.cx,size.cy,NULL,0);
		ReleaseDC(NULL,hdc);
		Update();
	}

	void CDui3DView::OnPaint( CDCHandle dc )
	{
		if( (NULL == m_hBmpTrans) ||
      (NULL == m_hBmpOrig) )
    {
      return ;
    }
		CMemDC memdc(dc,m_hBmpTrans);
		CRect rcClient;
		GetClient(&rcClient);
		BLENDFUNCTION bf={AC_SRC_OVER,0,255,AC_SRC_ALPHA};
		AlphaBlend(dc,rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height(),memdc,0,0,rcClient.Width(),rcClient.Height(),bf);
	}

	void CDui3DView::Update()
	{
		if( (NULL == m_hBmpTrans) ||
      (NULL == m_hBmpOrig) )
    {
      return ;
    }

		C3DTransform image3d;
		BITMAP bmSour,bmDest;
		GetObject(m_hBmpOrig,sizeof(BITMAP),&bmSour);
		GetObject(m_hBmpTrans,sizeof(BITMAP),&bmDest);
		image3d.SetImage((LPBYTE)bmSour.bmBits,(LPBYTE)bmDest.bmBits,bmSour.bmWidth,bmSour.bmHeight,bmSour.bmBitsPixel);
		image3d.Render(m_3dparam);
		NotifyInvalidate();
	}
}
