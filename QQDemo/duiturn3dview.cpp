//////////////////////////////////////////////////////////////////////////
//   File Name: DuiTurn3dView.cpp
// Description: DuiTurn3dView
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duiturn3dview.h"
#include "Dui3DView.h"

namespace DuiEngine
{
  CDuiTurn3dView::CDuiTurn3dView()
    : m_lpDesk(NULL)
    , m_nFrameIndex(0)
    , m_hBitmapBefore(NULL)
    , m_hBitmapAfter(NULL)
    , m_nZStep(50)
    , m_pDuiWindow(NULL)
    , m_strFrontSide("front-side")
    , m_strBackSide("back-side")
    , m_strCartoon("cartoon")
    , m_strImage3dView("image3dview")
    , m_idEvent(1)
    , m_bTurn2Front(FALSE)
    , m_uElapse(20)
    , m_nYStep(10)
  {

  }

  CDuiTurn3dView::~CDuiTurn3dView()
  {
    if(NULL != m_hBitmapBefore)
    {
      ::DeleteObject(m_hBitmapBefore);
      m_hBitmapBefore = NULL;
    }

    if( NULL != m_hBitmapAfter )
    {
      ::DeleteObject(m_hBitmapAfter);
      m_hBitmapAfter = NULL;
    }
  }

  void CDuiTurn3dView::SetFrontSide(CDuiStringA strFrontSide)
  {
    m_strFrontSide = strFrontSide;
  }

  void CDuiTurn3dView::SetBackSide(CDuiStringA strBackSide)
  {
    m_strBackSide = strBackSide;
  }

  void CDuiTurn3dView::SetCartoon(CDuiStringA strCartoon)
  {
    m_strCartoon = strCartoon;
  }

  void CDuiTurn3dView::SetDuiWindow(CDuiWindow* pDuiWindow)
  {
    m_pDuiWindow = pDuiWindow;
  }

  void CDuiTurn3dView::SetZStep(int nZStep)
  {
    m_nZStep = nZStep;
  }

  void CDuiTurn3dView::SetYStep(int nYStep)
  {
    m_nYStep = nYStep;
  }

  void CDuiTurn3dView::SetImage3dView(CDuiStringA str3dView)
  {
    m_strImage3dView = str3dView;
  }

  void CDuiTurn3dView::SetIdEvent(UINT_PTR idEvent)
  {
    m_idEvent = idEvent;
  }

  void CDuiTurn3dView::OnTimer(UINT_PTR idEvent)
  {
    if(idEvent == m_idEvent)
    {
      ShowFrame();
    }
  }

  void CDuiTurn3dView::ShowFrame()
  {
    if(NULL == m_pDuiWindow)
    {
      return ;
    }

    int n = 1;

    if(m_bTurn2Front)
    {
      n = -1;
    }

    int nMaxBeforeFrame, nMaxAfterFrame;
    nMaxBeforeFrame = 90 / m_nYStep;
    nMaxAfterFrame = 180 / m_nYStep;

    CDui3DView* pDui3dView = (CDui3DView*)m_pDuiWindow->FindChildByName(m_strImage3dView);
    if(NULL != pDui3dView)
    {      
      if(m_nFrameIndex <= nMaxBeforeFrame)
      {
        pDui3dView->Get3dParam().nOffsetZ = m_nZStep * m_nFrameIndex;
        pDui3dView->Get3dParam().nRotateY = n * m_nYStep * m_nFrameIndex;
        pDui3dView->SetBmpOrig(m_hBitmapBefore);
        pDui3dView->Update();           
      }
      else if(m_nFrameIndex > nMaxBeforeFrame && m_nFrameIndex < nMaxAfterFrame)
      {
        pDui3dView->Get3dParam().nOffsetZ = m_nZStep * (nMaxAfterFrame - m_nFrameIndex);
        pDui3dView->Get3dParam().nRotateY = n * m_nYStep * (m_nFrameIndex - nMaxAfterFrame);
        pDui3dView->SetBmpOrig(m_hBitmapAfter);
        pDui3dView->Update();        
      }
      else if(m_nFrameIndex >= nMaxAfterFrame)
      {
        CDuiStringA strShow, strHide;
        if(m_bTurn2Front)
        {
          strShow = m_strFrontSide;
          strHide = m_strBackSide;
        }
        else
        {
          strShow = m_strBackSide;
          strHide = m_strFrontSide;
        }
        CDuiWindow* pDuiWindow = NULL;
        pDuiWindow = m_pDuiWindow->FindChildByName(strHide);
        if(NULL != pDuiWindow)
        {
          pDuiWindow->SetVisible(FALSE, FALSE);
        }

        pDuiWindow = m_pDuiWindow->FindChildByName(m_strCartoon);
        if(NULL != pDuiWindow)
        {
          pDuiWindow->SetVisible(FALSE, FALSE);
        }

        pDuiWindow = m_pDuiWindow->FindChildByName(strShow);
        if(NULL != pDuiWindow)
        {
          pDuiWindow->SetVisible(TRUE, TRUE);
        }

        CDuiContainer* pContainer = m_pDuiWindow->GetContainer();
        if(NULL != pContainer)
        {
          ::KillTimer(pContainer->GetHostHwnd(), m_idEvent);          
        }        
      }
      m_nFrameIndex++;
    }
  }

  void CDuiTurn3dView::SetElapse(UINT uElapse)
  {
    m_uElapse = uElapse;
  }

  void CDuiTurn3dView::Turn(BOOL bTurn2Front)
  {
    if(NULL == m_pDuiWindow)
      return ;

    m_bTurn2Front = bTurn2Front;
    CDuiStringA strBefore, strAfter;
    if(bTurn2Front)
    {
      strBefore = m_strBackSide;
      strAfter = m_strFrontSide;
    }
    else
    {
      strBefore = m_strFrontSide;
      strAfter = m_strBackSide;
    }
    CRect rcWnd;
    m_pDuiWindow->GetRect(&rcWnd);

    //复制正面窗体的图像
    CRgn rgn;
    rgn.CreateRectRgnIndirect(rcWnd);

    CDCHandle dc=m_pDuiWindow->GetDuiDC(rcWnd,OLEDC_NODRAW,FALSE);

    

    if(NULL == m_hBitmapBefore)
    {
      m_hBitmapBefore = CGdiAlpha::CreateBitmap32(dc,rcWnd.Width(),rcWnd.Height(),NULL,255);
    }
    CMemDC dcBefore(dc, m_hBitmapBefore);
    dcBefore.SetBitmapOwner(TRUE); 

    //渲染窗口变化前状态
    m_pDuiWindow->PaintBackground(dc,rcWnd);
    m_pDuiWindow->RedrawRegion(CDCHandle(dc),rgn);


    BitBlt(dcBefore,rcWnd.left,rcWnd.top,rcWnd.Width(),rcWnd.Height(),dc,rcWnd.left,rcWnd.top,SRCCOPY);

    //更新窗口可见性
    CDuiWindow* pDuiWindow = m_pDuiWindow->FindChildByName(strBefore);
    if(NULL != pDuiWindow)
    {
      pDuiWindow->SetVisible(FALSE, FALSE);
    }

    pDuiWindow = m_pDuiWindow->FindChildByName(strAfter);
    if(NULL != pDuiWindow)
    {
      pDuiWindow->SetVisible(TRUE, TRUE);
      
    }

    
    if(NULL == m_hBitmapAfter)
    {
      m_hBitmapAfter = CGdiAlpha::CreateBitmap32(dc,rcWnd.Width(),rcWnd.Height(),NULL,0);
    }

    CMemDC dcAfter(dc,m_hBitmapAfter);
    dcAfter.SetBitmapOwner(TRUE); 
    

    m_pDuiWindow->PaintBackground(dc,rcWnd);
    m_pDuiWindow->RedrawRegion(CDCHandle(dc),rgn);
    BitBlt(dcAfter,rcWnd.left,rcWnd.top,rcWnd.Width(),rcWnd.Height(),dc,rcWnd.left,rcWnd.top,SRCCOPY);
    m_pDuiWindow->ReleaseDuiDC(dc);


    m_nFrameIndex = 0;



    pDuiWindow = m_pDuiWindow->FindChildByName(strAfter);
    if(NULL != pDuiWindow)
    {
      pDuiWindow->SetVisible(FALSE, TRUE);
      
    }


    HBITMAP hBmpTrans;

    hBmpTrans=CGdiAlpha::CreateBitmap32(dc,rcWnd.Width(),rcWnd.Height(),NULL,0);

    pDuiWindow = m_pDuiWindow->FindChildByName(m_strCartoon);


    if(NULL != pDuiWindow)
    {    
      pDuiWindow->SetVisible(TRUE, TRUE);   
      CDui3DView* pDui3dView = (CDui3DView*)m_pDuiWindow->FindChildByName(m_strImage3dView);
      if(NULL != pDui3dView)
      {
        pDui3dView->Get3dParam().nOffsetZ = m_nZStep ;
        pDui3dView->Get3dParam().nRotateY = -10;
        pDui3dView->SetBmpOrig(m_hBitmapBefore);
        pDui3dView->Update();    
        m_nFrameIndex = 1;
        CDuiContainer* pContainer = m_pDuiWindow->GetContainer();
        if(NULL != pContainer)
        {
          ::SetTimer(pContainer->GetHostHwnd(), m_idEvent, m_uElapse, 0);
        }
        
      }
    }  
  }
}