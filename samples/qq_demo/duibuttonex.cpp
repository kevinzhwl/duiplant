//////////////////////////////////////////////////////////////////////////
//   File Name: duibuttonex.cpp
// Description: DuiButtonEx
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.01.25 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"
#include "duibuttonex.h"

namespace DuiEngine
{
  CDuiButtonEx::CDuiButtonEx()
    : m_pSkinNormal(NULL)
    , m_pSkinHover(NULL)
    , m_pSkinDown(NULL)
    , m_pSkinDisable(NULL)
  {

  }

  CDuiButtonEx::~CDuiButtonEx()
  {

  }

  BOOL CDuiButtonEx::NeedRedrawWhenStateChange()
  {
      return TRUE;
  }


  void CDuiButtonEx::OnPaint(CDCHandle dc)
  {
    int state = IIF_STATE3(GetState(), DuiWndState_Normal, DuiWndState_Hover, DuiWndState_PushDown);
    CDuiSkinBase* pSkin = NULL;
    switch(state)
    {
    case DuiWndState_Normal:
      pSkin = m_pSkinNormal;
      break;
    case DuiWndState_Hover:
      pSkin = m_pSkinHover;
      break;
    case DuiWndState_PushDown:
      pSkin = m_pSkinDown;
      break;
    case DuiWndState_Disable:
      pSkin = m_pSkinDisable;
      break;

    }

    if(NULL != pSkin)
    {
      pSkin->Draw(dc, m_rcWindow, 0);
    }

    CDuiWindow::OnPaint(dc);
  }
}