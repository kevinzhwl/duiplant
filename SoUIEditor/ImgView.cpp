#include "StdAfx.h"
#include "ImgView.h"
namespace DuiEngine
{

	CImgView::CImgView(void):m_nStates(1),m_bVertical(FALSE),m_bTile(FALSE)
	{
	}

	CImgView::~CImgView(void)
	{
	}

	void CImgView::OnPaint( CDCHandle dc )
	{
		CRect rcWnd;
		GetClient(&rcWnd);
		if(!m_img.IsEmpty())
		{
			CRect rcState=rcWnd;
			rcState.right=rcState.left+rcWnd.Width()/m_nStates;
			SIZE szImg;
			m_img.GetImageSize(szImg);
			if(m_bVertical) szImg.cy/=m_nStates;
			else szImg.cx/=m_nStates;

			CRect rcSour(0,0,szImg.cx,szImg.cy);
			
			CPen pen;
			pen.CreatePen(PS_DASHDOT,1,RGB(255,0,0));
			HPEN hOldPen=dc.SelectPen(pen);
			for(int i=0;i<m_nStates;i++)
			{
				CDuiSkinBase::FrameDraw(dc,&m_img,rcSour,rcState,m_rcMargin,-1,-1,m_bTile,255);
				if(i<m_nStates-1)
				{
					dc.MoveTo(rcState.right,rcState.top);
					dc.LineTo(rcState.right,rcState.bottom);
				}

				if(m_rcMargin.left!=0)
				{
					dc.MoveTo(rcState.left+m_rcMargin.left,rcState.top);
					dc.LineTo(rcState.left+m_rcMargin.left,rcState.bottom);
				}
				if(m_rcMargin.right!=0)
				{
					dc.MoveTo(rcState.right-m_rcMargin.right,rcState.top);
					dc.LineTo(rcState.right-m_rcMargin.right,rcState.bottom);
				}
				if(m_rcMargin.top!=0)
				{
					dc.MoveTo(rcState.left,rcState.top+m_rcMargin.top);
					dc.LineTo(rcState.right,rcState.top+m_rcMargin.top);
				}
				if(m_rcMargin.bottom!=0)
				{
					dc.MoveTo(rcState.left,rcState.bottom-m_rcMargin.bottom);
					dc.LineTo(rcState.right,rcState.bottom-m_rcMargin.bottom);
				}
				
				rcState.OffsetRect(rcState.Width(),0);
				if(m_bVertical) rcSour.OffsetRect(0,rcSour.Height());
				else rcSour.OffsetRect(rcSour.Width(),0);
			}
			dc.SelectPen(hOldPen);
		}else
		{
			CGdiAlpha::DrawText(dc,_T("没有指定图片"),-1,rcWnd,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}

	BOOL CImgView::SetImageFile( LPCTSTR pszFileName )
	{
		m_nStates=1;
		m_bTile=FALSE;
		m_rcMargin=CRect();
		m_bVertical=FALSE;
		m_img.Clear();
		m_strFileName.Empty();
		BOOL bOK=m_img.LoadFromFile(pszFileName);
		if(bOK) m_strFileName=pszFileName;
		NotifyInvalidate();
		return bOK;
	}
}