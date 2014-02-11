//////////////////////////////////////////////////////////////////////////
//   File Name: duiembededit.cpp
// Description: DuiEmbedEdit
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"
#include "duiembededit.h"

namespace DuiEngine
{
  CEmbedEdit::CEmbedEdit()
  {
    SetOwner(NULL);
  }

  CEmbedEdit::CEmbedEdit( CDuiWindow *pOwner )
  {
	  SetOwner(pOwner);
  }

  void CEmbedEdit::OnMouseHover( WPARAM wParam, CPoint ptPos )
  {
	  __super::OnMouseHover(wParam,ptPos);
    CDuiWindow* pOwner = NULL;
    pOwner = GetOwner();
	  if(NULL != pOwner)
    {
      pOwner->DuiSendMessage(WM_MOUSEHOVER,wParam,MAKELPARAM(ptPos.x,ptPos.y));
    }
    else
    {
      CDuiWindow* pParent = GetParent();
      if(NULL != pParent)
      {
        pParent->DuiSendMessage(WM_MOUSEHOVER, wParam, MAKELPARAM(ptPos.x, ptPos.y));
      }
    }
  }

  void CEmbedEdit::OnMouseLeave()
  {
	  __super::OnMouseLeave();
	  
    CDuiWindow* pOwner = NULL;
    pOwner = GetOwner();
	  if(NULL != pOwner)
    {
      pOwner->DuiSendMessage(WM_MOUSELEAVE);
    }
    else
    {
      CDuiWindow* pParent = GetParent();
      if(NULL != pParent)
      {
        pParent->DuiSendMessage(WM_MOUSELEAVE);
      }
    }

  }

  void CEmbedEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
  {
	  CDuiWindow *pOwner = GetOwner();
    CDuiWindow *pParent = GetParent();
	  if (pOwner && (nChar == VK_DOWN || nChar == VK_ESCAPE))
	  {
		  pOwner->DuiSendMessage(WM_KEYDOWN, nChar, MAKELONG(nFlags, nRepCnt));
		  return;
	  }
    else if(pParent && (nChar == VK_DOWN || nChar == VK_ESCAPE) )
    {
      pParent->DuiSendMessage(WM_KEYDOWN, nChar, MAKELONG(nFlags, nRepCnt));
    }

	  SetMsgHandled(FALSE);
  }

  LRESULT CEmbedEdit::DuiNotify( LPDUINMHDR pnms )
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
		    pnms->idFrom=pDuiWindow->GetCmdID();
	  }
	  return __super::DuiNotify(pnms);
  }
}