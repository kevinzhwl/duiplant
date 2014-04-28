#pragma once
#include <dui/duisingleton.h>

#include <dui/DuiThreadActiveWndManager.h>

#include <dui/duiresprovider.h>
#include <dui/DuiWindowManager.h>
#include <dui/duiwndfactorymanager.h>
#include <dui/DuiLogger.h>
#include <dui/DuiMessageBox.h>
#include <dui/DuiScriptModule.h>

#include <Richedit.h>
#include <TextServ.h>

#include <dui/DuiCSS.h>
#include <dui/duistringpool.h>
#include <dui/duifontpool.h>
#include <dui/duiskin.h>
#include <dui/duiwndstyle.h>
#include <dui/duiimgpool.h>
#include <dui/Name2ID.h>

#define DUI_VERSION	_T("2.1.0.1")

namespace DuiEngine
{

class DUI_EXP DuiSystem :
    public Singleton<DuiSystem>
{
	friend class CSimpleWnd;
	friend class CDuiMessageBox;
	friend class CDuiRichEdit;

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

	size_t InitName2ID( LPCTSTR pszRes,LPCTSTR pszType );
	BOOL LoadXmlDocment(pugi::xml_document & xmlDoc,LPCTSTR pszXmlName ,LPCTSTR pszType=DUIRES_XML_TYPE);

	BOOL SetMsgBoxTemplate(LPCTSTR pszXmlName,LPCTSTR pszType=DUIRES_XML_TYPE);

protected:
	pugi::xml_node GetMsgBoxTemplate(){return m_xmlMsgBoxTempl;}
	pugi::xml_node GetEditMenuTemplate(){return m_xmlEditMenu;}

    void createSingletons();
    void destroySingletons();

    DuiResProviderBase	* m_pResProvider;
	IScriptModule		* m_pScriptModule;
    DuiLogger * m_pLogger;
    HINSTANCE m_hInst;

	pugi::xml_document	m_xmlMsgBoxTempl;
	pugi::xml_document	m_xmlEditMenu;
};

}//namespace DuiEngine