#include "duistd.h"
#include "DuiSystem.h"
#include "mybuffer.h"
#include "SimpleWnd.h"


namespace DuiEngine
{

template<> DuiSystem* Singleton<DuiSystem>::ms_Singleton = 0;

DuiSystem::DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName/*=_T("DuiHostWnd")*/)
    :m_hInst(hInst)
    ,m_pResProvider(NULL)
    ,m_pLogger(NULL)
	,m_pScriptModule(NULL)
	,m_funCreateTextServices(NULL)
{
    createSingletons();
	CSimpleWndHelper::Init(hInst,pszHostClassName);
	m_rich20=LoadLibrary(_T("riched20.dll"));
	if(m_rich20) m_funCreateTextServices= (PCreateTextServices)GetProcAddress(m_rich20,"CreateTextServices");
}

DuiSystem::~DuiSystem(void)
{
    destroySingletons();
	CSimpleWndHelper::Destroy();

	if(m_rich20) FreeLibrary(m_rich20);
	m_funCreateTextServices=NULL;
}

void DuiSystem::createSingletons()
{
    new DuiThreadActiveWndManager();
    new DuiSkinFactoryManager();
    new DuiSkinPool();
    new DuiWindowFactoryManager();
    new DuiWindowManager();
    new CDuiTimerEx();
    new DuiStringPool();
    new DuiCSS();
    new DuiFontPool();
    new DuiStylePool();
    new DuiImgPool();
	new DuiName2ID();
}

void DuiSystem::destroySingletons()
{
    delete DuiFontPool::getSingletonPtr();
    delete DuiStylePool::getSingletonPtr();
    delete DuiStringPool::getSingletonPtr();
    delete CDuiTimerEx::getSingletonPtr();
    delete DuiWindowFactoryManager::getSingletonPtr();
    delete DuiSkinPool::getSingletonPtr();
    delete DuiSkinFactoryManager::getSingletonPtr();
    delete DuiCSS::getSingletonPtr();
    delete DuiImgPool::getSingletonPtr();
    delete DuiThreadActiveWndManager::getSingletonPtr();
    delete DuiWindowManager::getSingletonPtr();
	delete DuiName2ID::getSingletonPtr();
}

void DuiSystem::logEvent( LPCTSTR message, LoggingLevel level /*= Standard*/ )
{
    if(m_pLogger) m_pLogger->logEvent(message,level);
}

void DuiSystem::logEvent(LoggingLevel level , LPCTSTR pszFormat, ...)
{
    if(!m_pLogger) return;
    TCHAR szBuffer[1025] = { 0 };
    va_list argList;
    va_start(argList, pszFormat);
    ::wvnsprintf(szBuffer,ARRAYSIZE(szBuffer)-1, pszFormat, argList);
    va_end(argList);
    m_pLogger->logEvent(szBuffer,level);
}

BOOL DuiSystem::Init( LPCTSTR pszName ,LPCTSTR pszType/*=DUIRES_XML_TYPE*/ )
{
	pugi::xml_document xmlDoc;
	if(!LoadXmlDocment(xmlDoc,pszName,pszType)) return FALSE;
	//set default font
	pugi::xml_node xmlFont;
	xmlFont=xmlDoc.first_child().child("font");
	if(xmlFont)
	{
		int nSize=xmlFont.attribute("size").as_int(12);
		DuiFontPool::getSingleton().SetDefaultFont(DUI_CA2T(xmlFont.attribute("face").value(),CP_UTF8),nSize);
	}
	//load string table
	pugi::xml_node xmlStr=xmlDoc.first_child().child("string");
	if(xmlStr)
	{
		DuiStringPool::getSingleton().Init(xmlStr);
	}
	//load style table
	pugi::xml_node xmlStyle=xmlDoc.first_child().child("style");
	if(xmlStyle)
	{
		DuiStylePool::getSingleton().Init(xmlStyle);
	}
	//load skin
	pugi::xml_node xmlSkin=xmlDoc.first_child().child("skins");
	if(xmlSkin)
	{
		DuiSkinPool::getSingleton().Init(xmlSkin);
	}
	pugi::xml_node xmlObjAttr=xmlDoc.first_child().child("objattr");
	//load objattr
	if(xmlObjAttr)
	{
		DuiCSS::getSingleton().Init(xmlObjAttr);
	}
	return TRUE;
}

BOOL DuiSystem::LoadXmlDocment(pugi::xml_document & xmlDoc, LPCTSTR pszXmlName ,LPCTSTR pszType/*=DUIRES_XML_TYPE*/ )
{
	DUIASSERT(GetResProvider());
	DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
	if(!pRes) return FALSE;

	DWORD dwSize=pRes->GetRawBufferSize(pszType,pszXmlName);
	if(dwSize==0) return FALSE;

	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	pRes->GetRawBuffer(pszType,pszXmlName,strXml,dwSize);

	pugi::xml_parse_result result= xmlDoc.load_buffer(strXml,strXml.size(),pugi::parse_default,pugi::encoding_utf8);
	DUIRES_ASSERTA(result,"parse xml error! xmlName=%s,desc=%s,offset=%d",pszXmlName,result.description(),result.offset);
	return result;
}

BOOL DuiSystem::SetMsgBoxTemplate( LPCTSTR pszXmlName,LPCTSTR pszType/*=DUIRES_XML_TYPE*/ )
{
	if(!LoadXmlDocment(m_xmlMsgBoxTempl,pszXmlName,pszType)) goto format_error;
	if(!m_xmlMsgBoxTempl.child("layer").attribute("frame_size").value()[0]) goto format_error;
	if(!m_xmlMsgBoxTempl.child("layer").attribute("minsize").value()[0]) goto format_error;

	return TRUE;
format_error:
	m_xmlMsgBoxTempl.reset();
	return FALSE;
}

HRESULT DuiSystem::CreateTextServices( IUnknown *punkOuter, ITextHost *pITextHost, IUnknown **ppUnk )
{
	if(!m_funCreateTextServices) return E_NOTIMPL;
	return m_funCreateTextServices(punkOuter,pITextHost,ppUnk);
}

size_t DuiSystem::InitName2ID(LPCTSTR pszRes,LPCTSTR pszType )
{
	DuiResProviderPE resProvider(m_hInst,NULL);

	DWORD dwSize=resProvider.GetRawBufferSize(pszType,pszRes);
	if(dwSize==0) return 0;

	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	resProvider.GetRawBuffer(pszType,pszRes,strXml,dwSize);

	pugi::xml_document xmlDoc;
	if(!xmlDoc.load_buffer(strXml,strXml .size(),pugi::parse_default,pugi::encoding_utf8)) return 0;

	return DuiName2ID::getSingletonPtr()->Init(xmlDoc.first_child());
}
}//namespace DuiEngine