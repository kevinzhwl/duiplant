//////////////////////////////////////////////////////////////////////////
//   File Name: duiembedbuton.h
// Description: DuiEmbedButton
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"
#include "duiembedbutton.h"

namespace DuiEngine
{
  CEmbedButton::CEmbedButton()
  {
    SetOwner(NULL);
  }

  CEmbedButton::CEmbedButton( CDuiWindow *pOwner )
  {
	  SetOwner(pOwner);
  }

  void CEmbedButton::OnMouseHover( WPARAM wParam, CPoint ptPos )
  {
	  __super::OnMouseHover(wParam,ptPos);
    CDuiWindow* pDuiWindow = GetOwner();
    if(NULL == pDuiWindow)
    {
      pDuiWindow = GetParent();
    }
    
    if(NULL != pDuiWindow)
    {
      pDuiWindow->DuiSendMessage(WM_MOUSEHOVER,wParam,MAKELPARAM(ptPos.x,ptPos.y));
    }
  }

  void CEmbedButton::OnMouseLeave()
  {
	  __super::OnMouseLeave();

    CDuiWindow* pDuiWindow = GetOwner();
    if(NULL == pDuiWindow)
    {
      pDuiWindow = GetParent();
    }
    
    if(NULL != pDuiWindow)
    {
      pDuiWindow->DuiSendMessage(WM_MOUSELEAVE);
    }
  }



  LRESULT CEmbedButton::DuiNotify( LPDUINMHDR pnms )
  {
	  //转发richedit的txNotify消息
	  if(pnms->code==DUINM_RICHEDIT_NOTIFY)
	  {
      CDuiWindow* pDuiWindow = GetOwner();
      if(NULL == pDuiWindow)
      {
        pDuiWindow = GetParent();
      }
      if(NULL != pDuiWindow)
		    pnms->idFrom = pDuiWindow->GetCmdID();
	  }
	  return __super::DuiNotify(pnms);
  }
}