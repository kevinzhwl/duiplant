#include "stdafx.h"
#include <dui/gif/DuiGifControl.h>

CDuiGifControl::CDuiGifControl() :m_pgif(NULL), m_iCurFrame(0)
{

}

CDuiGifControl::~CDuiGifControl()
{
}

void CDuiGifControl::OnDuiTimer(char cTimerID)
{	
	KillDuiTimer(1);	

	if(m_pgif)
	{
		int nStates=m_pgif->GetStates();
		m_iCurFrame++;
		m_iCurFrame%=nStates;
		NotifyInvalidate();	
		SetDuiTimer(1, m_pgif->GetFrameDelay());	
	}
}

void CDuiGifControl::OnPaint( CDCHandle dc )
{	
	__super::OnPaint(dc);
	if(m_pgif)
	{		
		m_pgif->Draw(dc, m_rcWindow,m_iCurFrame);
	}
}

void CDuiGifControl::OnShowWindow( BOOL bShow, UINT nStatus )
{
	__super::OnShowWindow(bShow,nStatus);
	if(!bShow)
	{
		KillDuiTimer(1);
	}else if(m_pgif)
	{
		SetDuiTimer(1, m_pgif->GetFrameDelay());					
	}
}

HRESULT DuiEngine::CDuiGifControl::OnAttrGif( const CDuiStringA & strValue, BOOL bLoading )
{
	CDuiSkinBase *pSkin = DuiSkinPool::getSingleton().GetSkin(strValue);
	if(!pSkin) return S_FALSE;
	if(!pSkin->IsClass(CDuiSkinGif::GetClassName())) return S_FALSE;
	m_pgif=static_cast<CDuiSkinGif*>(pSkin);
	return bLoading?S_OK:S_FALSE;
}

CSize DuiEngine::CDuiGifControl::GetDesiredSize( LPRECT pRcContainer )
{
	CSize sz;
	if(m_pgif) sz=m_pgif->GetSkinSize();
	return sz;
}
