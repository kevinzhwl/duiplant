#pragma once

#ifndef DUI_EXP
#define DUI_EXP
#endif

#include <dui/duiresproviderbase.h>
#include <dui/DuiImgBase.h>

#include "ZipArchive.h"

namespace DuiEngine{

class DuiResProviderBase;

class DuiResProviderZip : public DuiResProviderBase
{
public:
	DuiResProviderZip(CDuiImgDecoder *pImgDecoder=NULL);
	~DuiResProviderZip(void);

	HBITMAP	LoadBitmap(LPCTSTR strType,LPCTSTR pszResName);
	HICON   LoadIcon(LPCTSTR strType,LPCTSTR pszResName,int cx=0,int cy=0);
	CDuiImgBase * LoadImage(LPCTSTR strType,LPCTSTR pszResName);
	size_t GetRawBufferSize(LPCTSTR strType,LPCTSTR pszResName);
	BOOL GetRawBuffer(LPCTSTR strType,LPCTSTR pszResName,LPVOID pBuf,size_t size);
	BOOL HasResource(LPCTSTR strType,LPCTSTR pszResName);

	BOOL Init(LPCTSTR pszZipFile);
	BOOL Init(HINSTANCE hInst,LPCTSTR pszResName,LPCTSTR pszType=_T("ZIP"));
protected:
	BOOL LoadSkin();
	CDuiStringT GetFilePath(LPCTSTR pszResName,LPCTSTR pszType);
	CDuiMap<DuiResID,CDuiStringT> m_mapFiles;

	CZipArchive m_zipFile;
};

}//namespace DuiEngine
