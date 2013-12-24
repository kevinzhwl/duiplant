// residbuilder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tinyxml/tinyxml.h"

const wchar_t  RB_HEADER[]=
L"/*<------------------------------------------------------------------------------------------------->*/\n"\
L"/*该文件由residbuilder2生成，请不要手动修改*/\n"\
L"/*<------------------------------------------------------------------------------------------------->*/\n";

const wchar_t RB_RC2INCLUDE[]=L"#pragma once\n#include <duires.h>\n";


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

int UpdateName2ID(map<string,int> *pmapName2ID,TiXmlDocument *pXmlDocName2ID,TiXmlElement *pXmlEleLayer,int & nCurID)
{
	int nRet=0;
	const char * strName=pXmlEleLayer->Attribute("name");
	int nID=0;
	pXmlEleLayer->Attribute("id",&nID);
	if(strName && pmapName2ID->find(strName)==pmapName2ID->end())
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
		nRet++;
	}
	TiXmlElement *pXmlChild=pXmlEleLayer->FirstChildElement();
	if(pXmlChild) nRet+=UpdateName2ID(pmapName2ID,pXmlDocName2ID,pXmlChild,nCurID);
	TiXmlElement *pXmlSibling=pXmlEleLayer->NextSiblingElement();
	if(pXmlSibling) nRet+=UpdateName2ID(pmapName2ID,pXmlDocName2ID,pXmlSibling,nCurID);
	return nRet;
}

#define ID_AUTO_START	65536


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

	printf("%s\n",GetCommandLineA());
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
		printf("not specify input file, using -i to define the input file");
		return 1;
	}

	//打开index.xml文件
	TiXmlDocument xmlIndexFile;
	if(!xmlIndexFile.LoadFile(strIndexFile.c_str()))
	{
		printf("parse input file failed");
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
	char szUtf16LE[2]={0xFF,0xFE};
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

		//write output string to target res file
		FILE * f=fopen(strRes.c_str(),"wb");
		if(f)
		{
			fwrite(szUtf16LE,sizeof(WCHAR),1,f);//写UTF16文件头。
			fwrite(RB_HEADER,sizeof(WCHAR),wcslen(RB_HEADER),f);
			fwrite(RB_RC2INCLUDE,2,wcslen(RB_RC2INCLUDE),f);
			fwrite(strOut.c_str(),sizeof(WCHAR),strOut.length(),f);
			fclose(f);
			printf("build resource succeed!\n");
		}

	}

	//build resource head
	if(strName2ID.length() && strHead.length())
	{
		TiXmlDocument xmlName2ID;

		map<string,int> mapNamedID;
		int nCurID=ID_AUTO_START;

		int nNewNamedID=0;
		TiXmlElement *pXmlIdmap=xmlIndexFile.FirstChildElement("resid");
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
					TiXmlDocument xmlDocLayer;
					xmlDocLayer.LoadFile(strXmlLayer.c_str());
					nNewNamedID+=UpdateName2ID(&mapNamedID,&xmlName2ID,xmlDocLayer.RootElement(),nCurID);
				}
			}
			pXmlIdmap=pXmlIdmap->NextSiblingElement("resid");
		}

		FILE *f=fopen(strName2ID.c_str(),"w");
		if(f)
		{
			xmlName2ID.Print(f);
			fclose(f);
			printf("build name2id succeed!");
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
			fwrite(szUtf16LE,2,1,f);//写UTF16文件头。
			fwrite(strOut.c_str(),sizeof(WCHAR),strOut.length(),f);
			fclose(f);
			printf("build header succeed!\n");
		}
	}

	return 0;
}

