// residbuilder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tinyxml/tinyxml.h"

#include <string>
#include <vector>
#include <map>
using namespace std;

const wchar_t  RB_HEADER[]=
L"/*<------------------------------------------------------------------------------------------------->*/\n"\
L"/*该文件由residbuilder2生成，请不要手动修改*/\n"\
L"/*<------------------------------------------------------------------------------------------------->*/\n";

const wchar_t RB_RC2INCLUDE[]=L"#pragma once\n#include <dui/duires.h>\n";


struct IDMAPRECORD
{
	WCHAR szType[100];
	WCHAR szName[200];
	WCHAR szPath[MAX_PATH];
};

struct NAME2IDRECORD
{
	WCHAR szName[100];
	int   nID;
	WCHAR szRemark[300];
};

//获得文件的最后修改时间
__int64 GetLastWriteTime(LPCSTR pszFileName)
{
	__int64 tmFile=0;
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(pszFileName, &findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		tmFile= *(__int64*)&findFileData.ftLastWriteTime;
		FindClose(hFind);
	}
	return tmFile;
}

//将单反斜扛转换成双反斜扛
wstring BuildPath(LPCWSTR pszPath)
{
	LPCWSTR p=pszPath;
	WCHAR szBuf[MAX_PATH*2]={0};
	WCHAR *p2=szBuf;
	while(*p)
	{
		if(*p==L'\\')
		{
			if(*(p+1)!=L'\\')
			{//单斜扛
				p2[0]=p2[1]=L'\\';
				p++;
				p2+=2;
			}else
			{//已经是双斜扛
				p2[0]=p2[1]=L'\\';
				p+=2;
				p2+=2;
			}
		}else
		{
			*p2=*p;
			p++;
			p2++;
		}
	}
	*p2=0;
	return wstring(szBuf);
}

void UpdateName2ID(map<string,int> *pmapName2ID,TiXmlDocument *pXmlDocName2ID,TiXmlElement *pXmlEleLayer,int & nCurID)
{
	const char * strName=pXmlEleLayer->Attribute("name");
	int nID=0;
	pXmlEleLayer->Attribute("id",&nID);
	if(strName)
	{//找到一个节点有name属性
		if(pmapName2ID->find(strName)==pmapName2ID->end())//当前name不在表中
		{
			TiXmlElement pNewNamedID=TiXmlElement("name2id");
			pNewNamedID.SetAttribute("name",strName);
			if(nID==0) nID=++nCurID;
			pNewNamedID.SetAttribute("id",nID);
			const char * strRemark=pXmlEleLayer->Attribute("fun");
			if(strRemark)
			{
				pNewNamedID.SetAttribute("remark",strRemark);
			}
			pXmlDocName2ID->InsertEndChild(pNewNamedID);
			(*pmapName2ID)[strName]=nID;
		}else
		{
			_tprintf(TEXT("find a element which uses a used name attribute %s \n"),strName);
		}
	}
	TiXmlElement *pXmlChild=pXmlEleLayer->FirstChildElement();
	if(pXmlChild) UpdateName2ID(pmapName2ID,pXmlDocName2ID,pXmlChild,nCurID);
	TiXmlElement *pXmlSibling=pXmlEleLayer->NextSiblingElement();
	if(pXmlSibling) UpdateName2ID(pmapName2ID,pXmlDocName2ID,pXmlSibling,nCurID);
}

#define ID_AUTO_START	65535
#define STAMP_FORMAT	L"//stamp:0000000000000000\r\n"
#define STAMP_FORMAT2	L"//stamp:%08x%08x\r\n"

#pragma pack(push,1)

class FILEHEAD
{
public:
	unsigned char szBom[2];
	WCHAR szHeadLine[ARRAYSIZE(STAMP_FORMAT)];

	FILEHEAD(__int64 ts=0)
	{
		szBom[0]=0xFF,szBom[1]=0xFE;
		swprintf(szHeadLine,STAMP_FORMAT2,(ULONG)((ts>>32)&0xffffffff),(ULONG)(ts&0xffffffff));		
	}
	static __int64 ExactTimeStamp(LPCSTR pszFile)
	{
		__int64 ts=0;
		FILE *f=fopen(pszFile,"rb");
		if(f)
		{
			FILEHEAD head;
			fread(&head,sizeof(FILEHEAD),1,f);
			DWORD dHi=0,dLow=0;
			if(wcsncmp(head.szHeadLine,STAMP_FORMAT2,8)==0)
			{
				swscanf(head.szHeadLine,STAMP_FORMAT2,&dHi,&dLow);
				ts=((__int64)dHi)<<32|dLow;
			}
			fclose(f);
		}
		return ts;
	}
};
#pragma  pack(pop)

typedef map<string,int> NAME2IDMAP;

BOOL IsName2IDMapChanged(NAME2IDMAP & map1,NAME2IDMAP & map2)
{
	if(map1.size()!=map2.size()) return TRUE;

	NAME2IDMAP::iterator it=map1.begin();
	while(it!=map1.end())
	{
		NAME2IDMAP::iterator it2=map2.find(it->first);
		if(it2==map2.end()) return TRUE;
		if(it2->second!=it->second) return TRUE;
		it++;
	}
	return FALSE;
}


void printUsage()
{
    const TCHAR  cmd_usage[]=
    TEXT("\n")\
    TEXT("=================================================\n")\
    TEXT("| \n")\
    TEXT("| residbulider2 用于生成duiengine的是资源文件\n")\
    TEXT("| 包括winres.rc2/ name2id winres.h\n")\
    TEXT("| residbuilder2 在构建之前事件中调用\n")\
    TEXT("| residbuilder2A 是对 residbuilder2的改版，主要是增加这个说明\n")\
    TEXT("| 示例\n")\
    TEXT("| residbuilder -y -p skin -i skin\\index.xml -r .\\duires\\winres.rc2 -n .\\duires\\name2id.xml -h .\\duires\\winres.h\n")\
    TEXT("=================================================\n")\
    TEXT("\n");

    _tprintf(TEXT("%s"),cmd_usage);
}

//residbuilder -y -p skin -i skin\index.xml -r .\duires\winres.rc2 -n .\duires\name2id.xml -h .\duires\winres.h
int _tmain(int argc, _TCHAR* argv[])
{
	string strSkinPath;	//皮肤路径,相对于程序的.rc文件
	string strIndexFile;
	string strRes;		//rc2文件名
	string strHead;		//资源头文件,如winres.h
	string strName2ID;	//名字-ID映射表XML
	char   cYes=0;		//强制改写标志

	int c;

	_tprintf(TEXT("%s\n"),GetCommandLine());
	while ((c = getopt(argc, argv, _T("i:r:h:n:y:p:"))) != EOF)
	{
		switch (c)
		{
		case _T('i'):strIndexFile=optarg;break;
		case _T('r'):strRes=optarg;break;
		case _T('h'):strHead=optarg;break;
		case _T('n'):strName2ID=optarg;break;
		case _T('y'):cYes=1;optind--;break;
		case _T('p'):strSkinPath=optarg;break;
		}
	}
	if(strIndexFile.empty())
	{
		_tprintf(TEXT("not specify input file, using -i to define the input file"));
        printUsage();
		return 1;
	}

	//打开index.xml文件
	TiXmlDocument xmlIndexFile;
	if(!xmlIndexFile.LoadFile(strIndexFile.c_str()))
	{
		_tprintf(TEXT("parse input file failed"));
        printUsage();
		return 1;
	}

	vector<IDMAPRECORD> vecIdMapRecord;
	//load xml description of resource to vector
	TiXmlElement *xmlEle=xmlIndexFile.RootElement();
	while(xmlEle)
	{
		if(strcmp(xmlEle->Value(),"resid")==0)
		{
			IDMAPRECORD rec={0};
			const char *pszValue;
			pszValue=xmlEle->Attribute("type");
			if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szType,100);
			pszValue=xmlEle->Attribute("name");
			if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szName,200);
			pszValue=xmlEle->Attribute("file");
			if(pszValue)
			{
				string str;
				if(!strSkinPath.empty()){ str=strSkinPath+"\\"+pszValue;}
				else str=pszValue;
				MultiByteToWideChar(CP_UTF8,0,str.c_str(),str.length(),rec.szPath,MAX_PATH);
			}

			vecIdMapRecord.push_back(rec);
		}
		xmlEle=xmlEle->NextSiblingElement();
	}
	if(strRes.length())
	{//编译资源.rc2文件
		//build output string by wide char
		wstring strOut;

		vector<IDMAPRECORD>::iterator it2=vecIdMapRecord.begin();
		while(it2!=vecIdMapRecord.end())
		{
			WCHAR szRec[2000];
			wstring strFile=BuildPath(it2->szPath);
			swprintf(szRec,L"DEFINE_%s(%s,\t%\"%s\")\n",it2->szType,it2->szName,strFile.c_str());
			strOut+=szRec;
			it2++;
		}

		__int64 tmIdx=GetLastWriteTime(strIndexFile.c_str());
		__int64 tmSave=FILEHEAD::ExactTimeStamp(strRes.c_str());
		//write output string to target res file
		if(tmIdx!=tmSave)
		{
			FILE * f=fopen(strRes.c_str(),"wb");
			if(f)
			{
				FILEHEAD tmStamp(tmIdx);
				fwrite(&tmStamp,sizeof(FILEHEAD)-sizeof(WCHAR),1,f);//写UTF16文件头及时间。-sizeof(WCHAR)用来去除stamp最后一个\0
				fwrite(RB_HEADER,sizeof(WCHAR),wcslen(RB_HEADER),f);
				fwrite(RB_RC2INCLUDE,2,wcslen(RB_RC2INCLUDE),f);
				fwrite(strOut.c_str(),sizeof(WCHAR),strOut.length(),f);
				fclose(f);
				_tprintf(TEXT("build resource succeed!\n"));
			}
		}else
		{
			_tprintf(TEXT("%s has not been modified\n"),strIndexFile.c_str());
		}

	}

	//build resource head
	if(strName2ID.length() && strHead.length())
	{
		TiXmlDocument xmlName2ID;
		xmlName2ID.LoadFile(strName2ID.c_str());
		NAME2IDMAP mapNamedID_Old;
		TiXmlElement *pXmlName2ID=xmlName2ID.FirstChildElement("name2id");
		while(pXmlName2ID)
		{
			string strName=pXmlName2ID->Attribute("name");
			int uID=0;
			pXmlName2ID->Attribute("id",&uID);
			mapNamedID_Old[strName]=uID;
			pXmlName2ID=pXmlName2ID->NextSiblingElement("name2id");
		}
		xmlName2ID.Clear();

		NAME2IDMAP mapNamedID;
		TiXmlElement *pXmlIdmap=xmlIndexFile.FirstChildElement("resid");
		int nCurID=ID_AUTO_START;
		while(pXmlIdmap)
		{
			int layer=0;
			pXmlIdmap->Attribute("layer",&layer);
			if(layer && _stricmp(pXmlIdmap->Attribute("type"),"xml")==0)
			{
				string strXmlLayer=pXmlIdmap->Attribute("file");
				if(!strSkinPath.empty()) strXmlLayer=strSkinPath+"\\"+strXmlLayer;
				if(strXmlLayer.length())
				{//找到一个窗口描述XML
					_tprintf(TEXT("extracting named element from %s\n"),strXmlLayer.c_str());
					TiXmlDocument xmlDocLayer;
					xmlDocLayer.LoadFile(strXmlLayer.c_str());
					UpdateName2ID(&mapNamedID,&xmlName2ID,xmlDocLayer.RootElement(),nCurID);
				}
			}
			pXmlIdmap=pXmlIdmap->NextSiblingElement("resid");
		}

		if(!IsName2IDMapChanged(mapNamedID,mapNamedID_Old))
		{
			_tprintf(TEXT("name2id map doesn't need to be updated!"));
		}else
		{

			FILE *f=fopen(strName2ID.c_str(),"w");
			if(f)
			{
				xmlName2ID.Print(f);
				fclose(f);
				_tprintf(TEXT("build name2id succeed!"));
			}

			vector<NAME2IDRECORD> vecName2ID;
			//load xml description of resource to vector
			TiXmlElement *xmlEle=xmlName2ID.RootElement();
			while(xmlEle)
			{
				if(strcmp(xmlEle->Value(),"name2id")==0)
				{
					NAME2IDRECORD rec={0};
					const char *pszValue;
					pszValue=xmlEle->Attribute("name");
					if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szName,100);
					pszValue=xmlEle->Attribute("id");
					if(pszValue) rec.nID=atoi(pszValue);
					pszValue=xmlEle->Attribute("remark");
					if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szRemark,300);

					if(rec.szName[0] && rec.nID) vecName2ID.push_back(rec);
				}
				xmlEle=xmlEle->NextSiblingElement();
			}

			//build output string by wide char
			wstring strOut;
			strOut+=RB_HEADER;

			vector<NAME2IDRECORD>::iterator it2=vecName2ID.begin();
			while(it2!=vecName2ID.end())
			{
				WCHAR szRec[2000];
				if(it2->szRemark[0])
					swprintf(szRec,L"#define\t%s\t\t%d	\t//%s\n",it2->szName,it2->nID,it2->szRemark);
				else
					swprintf(szRec,L"#define\t%s\t\t%d\n",it2->szName,it2->nID);
				strOut+=szRec;
				it2++;
			}

			//write output string to target res file
			f=fopen(strHead.c_str(),"wb");
			if(f)
			{
				unsigned char szBom[2]={0xFF,0xFE};
				fwrite(szBom,2,1,f);//写UTF16文件头。
				fwrite(strOut.c_str(),sizeof(WCHAR),strOut.length(),f);
				fclose(f);
				_tprintf(TEXT("build header succeed!\n"));
			}
		}
	}

	return 0;
}

