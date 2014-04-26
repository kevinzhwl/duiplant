#pragma once

class CMainDlg;

#include <ExDisp.h>

class CUIHander : public IDispatch
{
public:
	CUIHander(CMainDlg *pMainDlg);
	~CUIHander(void);

protected:
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	void OnGoClick();
	
	BEGIN_MSG_MAP_EX(CUIHander)
		MSG_DUI_NOTIFY()
		MSG_WM_INITDIALOG(OnInitDialog)
	END_MSG_MAP()

	DUI_NOTIFY_MAP_BEGIN()
		DUI_NOTIFY_NAME_COMMAND("btn_go", OnGoClick)
	DUI_NOTIFY_MAP_END()	


protected:
	// IUnknown
	STDMETHOD_(ULONG,AddRef)(){return 1;}
	STDMETHOD_(ULONG,Release)(){return 1;}
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppvObject)
	{
		if(IsEqualGUID(riid,__uuidof(IUnknown)) || IsEqualGUID(riid,__uuidof(IDispatch)))
		{
			*ppvObject=this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	//IDispatch
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( 
		/* [out] */ __RPC__out UINT *pctinfo){ return E_NOTIMPL;}

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( 
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo){ return E_NOTIMPL;}



	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
		/* [range][in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId){ return E_NOTIMPL;}


	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke( 
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS *pDispParams,
		/* [out] */ VARIANT *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);


protected:
	// DWebBrowserEvents2
	void BeforeNavigate2( IDispatch *pDisp,VARIANT *&url,VARIANT *&Flags,VARIANT *&TargetFrameName,VARIANT *&PostData,VARIANT *&Headers,VARIANT_BOOL *&Cancel );
	void NavigateError(IDispatch *pDisp,VARIANT * &url,VARIANT *&TargetFrameName,VARIANT *&StatusCode,VARIANT_BOOL *&Cancel);
	void NavigateComplete2(IDispatch *pDisp,VARIANT *&url);
	void ProgressChange(LONG nProgress, LONG nProgressMax);
	void CommandStateChange(long Command,VARIANT_BOOL Enable);

	HRESULT RegisterEventHandler(IWebBrowser2 *pIE, BOOL inAdvise );
	CDuiActiveX *m_pIE;

	DWORD	m_dwCookie;
private:
	CMainDlg * m_pMainDlg; 
};
