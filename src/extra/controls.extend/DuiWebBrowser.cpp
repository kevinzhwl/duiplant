#include "StdAfx.h"
#include "DuiWebBrowser.h"

#define WM_FORWARDMSG       0x037F

namespace DuiEngine
{

	CDuiWebBrowser::CDuiWebBrowser(void):m_dwCookie(0),m_eventDispatch(NULL)
{
	m_clsid=CLSID_WebBrowser;
}

CDuiWebBrowser::~CDuiWebBrowser(void)
{
	RegisterEventHandler(FALSE);
}

HRESULT CDuiWebBrowser::RegisterEventHandler( BOOL inAdvise )
{
	CDuiComQIPtr<IConnectionPointContainer>  pCPC=m_pIE;
	if(!pCPC) return S_FALSE;
	CDuiComQIPtr<IConnectionPoint> pCP;
	pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2,&pCP);
	if(!pCP) return S_FALSE;
	HRESULT hr=S_FALSE;
	if (inAdvise)
	{
		hr = pCP->Advise(&m_eventDispatch, &m_dwCookie);
	}
	else
	{
		hr = pCP->Unadvise(m_dwCookie);
	}
	return hr; 
}

STDMETHODIMP CWebEventDispatch::Invoke( /* [in] */ DISPID dispIdMember, /* [in] */ REFIID riid, /* [in] */ LCID lcid, /* [in] */ WORD wFlags, /* [out][in] */ DISPPARAMS *pDispParams, /* [out] */ VARIANT *pVarResult, /* [out] */ EXCEPINFO *pExcepInfo, /* [out] */ UINT *puArgErr )
{
	if ((riid != IID_NULL) || !m_pEventHandler)
		return E_INVALIDARG;

	switch(dispIdMember)
	{
	case DISPID_BEFORENAVIGATE2:
		m_pEventHandler->BeforeNavigate2(
			pDispParams->rgvarg[6].pdispVal,
			pDispParams->rgvarg[5].pvarVal,
			pDispParams->rgvarg[4].pvarVal,
			pDispParams->rgvarg[3].pvarVal,
			pDispParams->rgvarg[2].pvarVal,
			pDispParams->rgvarg[1].pvarVal,
			pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_COMMANDSTATECHANGE:
		m_pEventHandler->CommandStateChange(
			pDispParams->rgvarg[1].lVal,
			pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_NAVIGATECOMPLETE2:
		m_pEventHandler->NavigateComplete2(
			pDispParams->rgvarg[1].pdispVal,
			pDispParams->rgvarg[0].pvarVal);
		break;
	case DISPID_NAVIGATEERROR:
		m_pEventHandler->NavigateError(
			pDispParams->rgvarg[4].pdispVal,
			pDispParams->rgvarg[3].pvarVal,
			pDispParams->rgvarg[2].pvarVal,
			pDispParams->rgvarg[1].pvarVal,
			pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_DOCUMENTCOMPLETE:
		m_pEventHandler->DocumentComplete(
			pDispParams->rgvarg[1].pdispVal,
			pDispParams->rgvarg[0].pvarVal);
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

void CDuiWebBrowser::OnAxActivate( IUnknown *pUnknwn )
{
	m_pIE=pUnknwn;
	if(m_pIE)
	{
		RegisterEventHandler(TRUE);
		m_pIE->Navigate(bstr_t(m_strUrl),NULL,NULL,NULL,NULL);
	}
}

int CDuiWebBrowser::OnCreate( LPVOID )
{
	int nRet=__super::OnCreate(NULL);
	MsgFilterRegister(GetContainer()->GetHostHwnd());
	return nRet;
}

void CDuiWebBrowser::OnDestroy()
{
	MsgFilterUnregister(GetContainer()->GetHostHwnd());
}

BOOL CDuiWebBrowser::PreTranslateMessage( MSG* pMsg )
{
	BOOL bRet = FALSE;
	if(!m_pIE) return FALSE;
	// give HTML page a chance to translate this message
	CDuiComQIPtr<IOleInPlaceActiveObject> spInPlaceActiveObject(m_pIE);
	if(spInPlaceActiveObject)
	{
		bRet=(spInPlaceActiveObject->TranslateAccelerator(pMsg) == S_OK);
	}
	return bRet;
}
}
