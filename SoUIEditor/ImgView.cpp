#include "StdAfx.h"
#include "ImgView.h"
namespace DuiEngine
{

	CImgView::CImgView(void):m_viewType(VT_IMGLST),m_crSep(255),m_crFrame(128)
	{
		m_skinImgFrame.SetImage(&m_img);
		m_skinImgList.SetImage(&m_img);
		m_skinScroll.SetImage(&m_img);
	}

	CImgView::~CImgView(void)
	{
	}

	void CImgView::OnPaint( CDCHandle dc )
	{
		CRect rcWnd;
		GetClient(&rcWnd);
		CRect rcState=rcWnd;
		int nStates=GetSkin()->GetStates();
		rcState.right=rcState.left+rcState.Width()/nStates;
		for(int i=0;i<nStates;i++)
		{
			GetSkin()->Draw(dc,rcState,i);
			rcState.OffsetRect(rcState.Width(),0);
		}

		//draw seperate line
		rcState=rcWnd;
		rcState.right=rcState.left+rcState.Width()/nStates;
		for(int i=0;i<nStates-1;i++)
		{
			CGdiAlpha::DrawLine(dc,rcState.right,rcState.top,rcState.right,rcState.bottom,m_crSep,PS_DASHDOTDOT);
			rcState.OffsetRect(rcState.Width(),0);
		}

		//draw frame
		if(m_viewType==VT_IMGFRAME)
		{
			CRect rcMargin=m_skinImgFrame.GetMargin();
			rcState=rcWnd;
			rcState.right=rcState.left+rcState.Width()/nStates;
			
			for(int i=0;i<nStates;i++)
			{
				if(rcMargin.left!=0)
				{
					CGdiAlpha::DrawLine(dc,
						rcState.left+rcMargin.left,rcState.top,
						rcState.left+rcMargin.left,rcState.bottom,
						m_crFrame,PS_DASHDOT);
				}
				if(rcMargin.right!=0)
				{
					CGdiAlpha::DrawLine(dc,
						rcState.right-rcMargin.right,rcState.top,
						rcState.right-rcMargin.right,rcState.bottom,
						m_crFrame,PS_DASHDOT);
				}
				if(rcMargin.top!=0)
				{
					CGdiAlpha::DrawLine(dc,
						rcState.left,rcState.top+rcMargin.top,
						rcState.right,rcState.top+rcMargin.top,
						m_crFrame,PS_DASHDOT);
				}
				if(rcMargin.bottom!=0)
				{
					CGdiAlpha::DrawLine(dc,
						rcState.left,rcState.bottom-rcMargin.bottom,
						rcState.right,rcState.bottom-rcMargin.bottom,
						m_crFrame,PS_DASHDOT);
				}

				rcState.OffsetRect(rcState.Width(),0);
			}
		}
	}

	BOOL CImgView::SetImageFile( LPCTSTR pszFileName )
	{
		m_img.Clear();
		BOOL bOK=m_img.LoadFromFile(pszFileName);
		NotifyInvalidate();
		return bOK;
	}

	void CImgView::SetViewType( VIEWTYPE vt )
	{
		m_viewType=vt;
	}

	CDuiSkinBase * CImgView::GetSkin()
	{
		switch(m_viewType)
		{
		case VT_SCROLL:return &m_skinScroll;
		case VT_IMGLST:return &m_skinImgList;
		case VT_IMGFRAME:return &m_skinImgFrame;
		case VT_BUTTON:return &m_skinButton;
		}
		return NULL;
	}

	void CImgView::SetStates( int nStates )
	{
		m_skinImgList.SetStates(nStates);
		m_skinImgFrame.SetStates(nStates);
	}

	void CImgView::SetMargin( CRect rcMargin )
	{
		m_skinImgFrame.SetMargin(rcMargin);
	}

	void CImgView::SetTile( BOOL bTile )
	{
		m_skinImgFrame.SetTile(bTile);
		m_skinImgList.SetTile(bTile);
	}

	void CImgView::SetVertical( BOOL bVertical )
	{
		m_skinImgFrame.SetVertical(bVertical);
		m_skinImgList.SetVertical(bVertical);
	}
}