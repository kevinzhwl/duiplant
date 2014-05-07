#include "stdafx.h"
#include <dui/extractrls/DuiSpinEdit.h>

CDuiSpinEdit::CDuiSpinEdit() : m_pUpSkinBtn(NULL), m_pDownSkinBtn(NULL), m_dwUpBtnState(0), m_dwDownBtnState(0)
{

}

void CDuiSpinEdit::OnMouseMove(UINT nFlags,CPoint pt)
{	
	CRect rcUpBtn;
	GetUpBtnRect(&rcUpBtn);
	if(rcUpBtn.PtInRect(pt))
	{	
		m_dwUpBtnState = 1;		
	}
	else
	{
		m_dwUpBtnState = 0;			
	}

	CRect rcDownBtn;
	GetDownBtnRect(&rcDownBtn);
	if(rcDownBtn.PtInRect(pt))
	{	
		m_dwDownBtnState = 1;		
	}
	else
	{
		m_dwDownBtnState = 0;			
	}

	if (m_dwUpBtnState || m_dwDownBtnState)
	{
		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}
	else
	{
		__super::OnMouseMove(nFlags, pt);
	}

	CRect rcRect;	
	GetClient(rcRect);
	NotifyInvalidateRect(rcRect);
}

void CDuiSpinEdit::OnMouseLeave()
{
	__super::OnMouseLeave();
	
	m_dwUpBtnState = 0;	
	m_dwDownBtnState = 0;

	CRect rcRect;	
	GetClient(rcRect);
	NotifyInvalidateRect(rcRect);	
}


void CDuiSpinEdit::OnLButtonDown( UINT nFlags,CPoint pt )
{			
	CRect rcUpBtn;
	GetUpBtnRect(&rcUpBtn);
	if(rcUpBtn.PtInRect(pt))
	{	
		m_dwUpBtnState = 2;
		MyDuiNotify(1);
		SetDuiTimer(1, 300);

		
	}
	else
	{
		m_dwUpBtnState = 0;			
	}

	CRect rcDownBtn;
	GetDownBtnRect(&rcDownBtn);
	if(rcDownBtn.PtInRect(pt))
	{	
		m_dwDownBtnState = 2;
		MyDuiNotify(-1);
		SetDuiTimer(2, 300);		
	}
	else
	{
		m_dwDownBtnState = 0;			
	}

	if (m_dwUpBtnState || m_dwDownBtnState)
	{
		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}
	else
	{
		__super::OnLButtonDown(nFlags, pt);
	}

	CRect rcRect;	
	GetClient(rcRect);
	NotifyInvalidateRect(rcRect);	
}

void CDuiSpinEdit::OnDuiTimer(char cTimerID)
{
	switch (cTimerID)
	{	
	case 1:
		{
			MyDuiNotify(1);
		}
		break;
	case 2:
		{
			MyDuiNotify(-1);
		}
		break;	
	}
}


void CDuiSpinEdit::OnLButtonUp(UINT nFlags,CPoint pt)
{
	KillDuiTimer(1);
	KillDuiTimer(2);

	CRect rcBtn;
	GetUpBtnRect(&rcBtn);
	if(rcBtn.PtInRect(pt))
	{
		m_dwUpBtnState = 1;		
	}

	CRect rcDownBtn;
	GetDownBtnRect(&rcDownBtn);
	if(rcDownBtn.PtInRect(pt))
	{	
		m_dwDownBtnState = 1;		
	}

	if (m_dwUpBtnState || m_dwDownBtnState)
	{
		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}
	else
	{
		__super::OnLButtonUp(nFlags, pt);
	}

	CRect rcRect;	
	GetClient(rcRect);
	NotifyInvalidateRect(rcRect);	
}

BOOL CDuiSpinEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	__super::OnMouseWheel(nFlags, zDelta, pt);

	if (zDelta > 0)
	{
		MyDuiNotify(1);
	}
	else
	{
		MyDuiNotify(-1);
	}

	return 0;
}

void CDuiSpinEdit::GetUpBtnRect(LPRECT prc)
{
	SIZE szBtn=m_pUpSkinBtn->GetSkinSize();
	GetClient(prc);
	prc->left=prc->right-szBtn.cx;	
	prc->bottom = prc->top + szBtn.cy;
}

void CDuiSpinEdit::GetDownBtnRect(LPRECT prc)
{
	SIZE szBtn=m_pDownSkinBtn->GetSkinSize();
	GetClient(prc);
	prc->left=prc->right-szBtn.cx;
	prc->top = prc->bottom - szBtn.cy;
}

void CDuiSpinEdit::OnPaint( CDCHandle dc )
{	
	__super::OnPaint(dc);


	CRect rcUpBtn;
	CRect rcDownBtn;
	GetUpBtnRect(&rcUpBtn);	
	GetDownBtnRect(&rcDownBtn);	
	m_pUpSkinBtn->Draw(dc,rcUpBtn,m_dwUpBtnState);
	m_pDownSkinBtn->Draw(dc,rcDownBtn,m_dwDownBtnState);
}

void CDuiSpinEdit::MyDuiNotify(int iDelta)
{
	DUISPINEDITNOTIFY notifyUpDown;
	notifyUpDown.hdr.idFrom = GetCmdID();
	notifyUpDown.hdr.code = DUINM_SPINEDIT_NOTIFY;
	notifyUpDown.hdr.hwndFrom = NULL;

	notifyUpDown.iDelta = iDelta;
	notifyUpDown.iPos = 0;
	DuiNotify((LPDUINMHDR)&notifyUpDown);
}
