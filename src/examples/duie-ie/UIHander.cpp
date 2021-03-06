#include "StdAfx.h"
#include "UIHander.h"

#include "MainDlg.h"

#include <ExDispid.h>

CUIHander::CUIHander(CMainDlg * pMainDlg) : m_pMainDlg(pMainDlg),m_dwCookie(0)
{
}

CUIHander::~CUIHander(void)
{
}

HRESULT CUIHander::RegisterEventHandler(IWebBrowser2 *pIE, BOOL inAdvise )
{
	CDuiComQIPtr<IConnectionPointContainer>  pCPC=pIE;
	if(!pCPC) return S_FALSE;
	CDuiComQIPtr<IConnectionPoint> pCP;
	pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2,&pCP);
	if(!pCP) return S_FALSE;
	HRESULT hr=S_FALSE;
	if (inAdvise)
	{
		hr = pCP->Advise((IDispatch*)this, &m_dwCookie);
	}
	else
	{
		hr = pCP->Unadvise(m_dwCookie);
	}
	return hr; 
}

LRESULT CUIHander::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SetMsgHandled(FALSE); 

	m_pIE=m_pMainDlg->FindChildByName2<CDuiActiveX*>("ctrl_ie");
	CDuiComQIPtr<IWebBrowser2> pIE=m_pIE->GetIUnknow();
	RegisterEventHandler(pIE,TRUE);
	DUIASSERT(m_pIE);
    return 0; 
}

void CUIHander::OnGoClick()
{
	CDuiEdit * pEdit = m_pMainDlg->FindChildByName2<CDuiEdit *>("edit_url");
	CDuiComQIPtr<IWebBrowser2> pIE=m_pIE->GetIUnknow();
	if(pIE)
	{
		TCHAR szBuf[1024];
		pEdit->GetWindowText(szBuf,1024);
		CDuiStringW strUrl=DUI_CT2W(szBuf);
		HRESULT hr = pIE->Navigate(bstr_t(strUrl), NULL,NULL,NULL,NULL);
	}	
}

STDMETHODIMP CUIHander::Invoke( /* [in] */ DISPID dispIdMember, /* [in] */ REFIID riid, /* [in] */ LCID lcid, /* [in] */ WORD wFlags, /* [out][in] */ DISPPARAMS *pDispParams, /* [out] */ VARIANT *pVarResult, /* [out] */ EXCEPINFO *pExcepInfo, /* [out] */ UINT *puArgErr )
{
	if ((riid != IID_NULL))
		return E_INVALIDARG;

	switch(dispIdMember)
	{
	case DISPID_BEFORENAVIGATE2:
		BeforeNavigate2(
			pDispParams->rgvarg[6].pdispVal,
			pDispParams->rgvarg[5].pvarVal,
			pDispParams->rgvarg[4].pvarVal,
			pDispParams->rgvarg[3].pvarVal,
			pDispParams->rgvarg[2].pvarVal,
			pDispParams->rgvarg[1].pvarVal,
			pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_COMMANDSTATECHANGE:
		CommandStateChange(
			pDispParams->rgvarg[1].lVal,
			pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_NAVIGATECOMPLETE2:
		NavigateComplete2(
			pDispParams->rgvarg[1].pdispVal,
			pDispParams->rgvarg[0].pvarVal);
		break;
	case DISPID_NAVIGATEERROR:
		NavigateError(
			pDispParams->rgvarg[4].pdispVal,
			pDispParams->rgvarg[3].pvarVal,
			pDispParams->rgvarg[2].pvarVal,
			pDispParams->rgvarg[1].pvarVal,
			pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_STATUSTEXTCHANGE:
		break;
	case DISPID_NEWWINDOW2:
		break;
	case DISPID_NEWWINDOW3:
		break;
	default:
		return DISP_E_MEMBERNOTFOUND;
	}
	return S_OK;
}

void CUIHander::BeforeNavigate2( IDispatch *pDisp,VARIANT *&url,VARIANT *&Flags,VARIANT *&TargetFrameName,VARIANT *&PostData,VARIANT *&Headers,VARIANT_BOOL *&Cancel )
{
	DUITRACE(_T("BeforeNavigate2"));
}

void CUIHander::NavigateError( IDispatch *pDisp,VARIANT * &url,VARIANT *&TargetFrameName,VARIANT *&StatusCode,VARIANT_BOOL *&Cancel )
{
	DUITRACE(_T("NavigateError"));
}

void CUIHander::NavigateComplete2( IDispatch *pDisp,VARIANT *&url )
{
	DUITRACE(_T("NavigateComplete2"));
}

void CUIHander::ProgressChange( LONG nProgress, LONG nProgressMax )
{
	DUITRACE(_T("ProgressChange"));
}

void CUIHander::CommandStateChange( long Command,VARIANT_BOOL Enable )
{
	DUITRACE(_T("CommandStateChange"));
}