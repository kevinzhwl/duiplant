// magicbox2.cpp : main source file for magicbox2.exe
//

#include "stdafx.h"
#include "DuiSystem.h" 
#include "DuiDefaultLogger.h"
 

#include "MainDlg.h"
 
CAppModule _Module;


BOOL LoadXmlFromResource(pugi::xml_document & xmlDoc,HINSTANCE hInst,LPCTSTR pszName,LPCTSTR pszType)
{
	DuiResProviderPE res(hInst);
	DWORD dwSize=res.GetRawBufferSize(pszType,pszName);
	if(dwSize==0) return FALSE;
	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	res.GetRawBuffer(pszType,pszName,strXml,dwSize);
	pugi::xml_parse_result result= xmlDoc.load_buffer(strXml,strXml.size(),pugi::parse_default,pugi::encoding_utf8);
	DUIRES_ASSERTA(result,"parse xml error! xmlName=%s,desc=%s,offset=%d",pszName,result.description(),result.offset);
	return result;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = CoInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	TCHAR szCurrentDir[MAX_PATH+1]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, MAX_PATH );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   

	DuiSystem duiSystem(hInstance);
	DefaultLogger loger;
	loger.setLogFilename(CDuiStringT(szCurrentDir)+_T("\\dui-demo.log"));
	duiSystem.SetLogger(&loger);

	duiSystem.logEvent(_T("demo started"));


	pugi::xml_document xmlNamedID;
	LoadXmlFromResource(xmlNamedID,hInstance,MAKEINTRESOURCE(IDR_NAME2ID),_T("XML2"));
	DuiName2ID::getSingletonPtr()->Init(xmlNamedID.first_child());

	//从资源加载皮肤
	duiSystem.SetResProvider(new DuiResProviderPE(hInstance));
	// 以下 Load xx 的语句是必须的，否则皮肤将不能显示。这部分资源属性皮肤级别，不同的皮肤可以有不同的定义
	DuiStringPool::getSingleton().Init(_T("IDR_DUI_STRING_DEF")); // 加载字符串
	DuiFontPool::getSingleton().SetDefaultFont(_T("宋体"), -12); // 设置字体
	DuiSkinPool::getSingleton().Init(_T("IDR_DUI_SKIN_DEF")); // 加载皮肤
	DuiStylePool::getSingleton().Init(_T("IDR_DUI_STYLE_DEF")); // 加载风格
	DuiCSS::getSingleton().Init(_T("IDR_DUI_OBJATTR_DEF"));//加载类默认属性

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}

	duiSystem.logEvent(_T("demo end"));

	delete duiSystem.GetResProvider();

	CoUninitialize();
	return nRet;
}
