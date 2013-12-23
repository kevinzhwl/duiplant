#pragma once
#include "duisingleton.h"

#include "DuiThreadActiveWndManager.h"

#include "duiresprovider.h"
#include "DuiWindowManager.h"
#include "DuiWndFactoryManager.h"
#include "DuiLogger.h"
#include "DuiMessageBox.h"
#include "DuiScriptModule.h"

#include <Richedit.h>
#include <TextServ.h>

#include "DuiCSS.h"
#include "duistringpool.h"
#include "duifontpool.h"
#include "duiskin.h"
#include "duiwndstyle.h"
#include "duiimgpool.h"
#include "Name2ID.h"

#define DUI_VERSION	_T("2.0.0.1")

namespace DuiEngine
{

class DUI_EXP DuiSystem :
    public Singleton<DuiSystem>
{
	friend class CSimpleWnd;
	friend class CDuiMessageBox;

public:
    DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName=_T("DuiHostWnd"));
    ~DuiSystem(void);


    HINSTANCE GetInstance()
    {
        return m_hInst;
    }

	LPCTSTR GetVersion(){return DUI_VERSION;}

    DuiResProviderBase * SetResProvider(DuiResProviderBase *pNewResProvider)
    {
        DuiResProviderBase *pRet=m_pResProvider;
        m_pResProvider=pNewResProvider;
        return pRet;
    }
    DuiResProviderBase * GetResProvider()
    {
        return m_pResProvider;
    }

    DuiLogger *SetLogger(DuiLogger *pLogger)
    {
        DuiLogger *pRet=m_pLogger;
        m_pLogger=pLogger;
        return pRet;
    }
    DuiLogger * GetLogger()
    {
        return m_pLogger;
    }

	IScriptModule * GetScriptModule()
	{
		return m_pScriptModule;
	}

	IScriptModule * SetScriptModule(IScriptModule *pScriptModule)
	{
		IScriptModule *pRet=m_pScriptModule;
		m_pScriptModule=pScriptModule;
		return pRet;
	}

    void logEvent(LPCTSTR message, LoggingLevel level = Standard);

    void logEvent(LoggingLevel level , LPCTSTR format, ...);

	BOOL Init(LPCTSTR pszName ,LPCTSTR pszType=DUIRES_XML_TYPE);

	size_t InitName2ID( UINT uXmlResID,LPCTSTR pszType );
	BOOL LoadXmlDocment(pugi::xml_document & xmlDoc,LPCTSTR pszXmlName ,LPCTSTR pszType=DUIRES_XML_TYPE);

	BOOL SetMsgBoxTemplate(LPCTSTR pszXmlName,LPCTSTR pszType=DUIRES_XML_TYPE);

	HRESULT CreateTextServices(IUnknown *punkOuter, ITextHost *pITextHost, IUnknown **ppUnk);
protected:
	pugi::xml_node GetMsgBoxTemplate(){return m_xmlMsgBoxTempl;}

    void createSingletons();
    void destroySingletons();

    DuiResProviderBase	* m_pResProvider;
	IScriptModule		* m_pScriptModule;
    DuiLogger * m_pLogger;
    HINSTANCE m_hInst;

	HINSTANCE	m_rich20;	//richedit module
	PCreateTextServices	m_funCreateTextServices;

	pugi::xml_document	m_xmlMsgBoxTempl;
};

}//namespace DuiEngine