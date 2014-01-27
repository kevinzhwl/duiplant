#include "StdAfx.h"
#include "UIHander.h"

#include "MainDlg.h"

#include "ScintillaWnd.h"

#include <atlbase.h>
#include <atlapp.h>
#include <atldlgs.h>

using namespace pugi;

CUIHander::CUIHander(CMainDlg * pMainDlg) : m_pMainDlg(pMainDlg)
{
}

CUIHander::~CUIHander(void)
{
}

LRESULT CUIHander::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SetMsgHandled(FALSE); 
    return 0; 
}

void CUIHander::OnBtnClick_ProjectOpen()
{
	CFileDialog fileDlg(TRUE,_T("xml"),_T("index.xml"),6,_T("xml files(*.xml)\0*.xml\0All files (*.*)\0*.*\0\0"));
	if(IDOK==fileDlg.DoModal())
	{
		xml_document xmlDoc;
		if(xmlDoc.load_file(fileDlg.m_szFileName))
		{
			xml_node xmlNode=xmlDoc.first_child();
			if(strcmp("resid",xmlNode.name())!=0)
				xmlNode=xmlNode.next_sibling("resid");

			CDuiListCtrl * pListFile=m_pMainDlg->FindChildByName2<CDuiListCtrl *>("prj_list_file");
			pListFile->DeleteAllItems();

			int iItem=0;
			while(xmlNode)
			{
				pListFile->InsertItem(iItem,DUI_CA2T(xmlNode.attribute("type").value(),CP_UTF8));
				pListFile->SetSubItemText(iItem,1,DUI_CA2T(xmlNode.attribute("name").value(),CP_UTF8));
				pListFile->SetSubItemText(iItem,2,DUI_CA2T(xmlNode.attribute("file").value(),CP_UTF8));
				pListFile->SetSubItemText(iItem,3,DUI_CA2T(xmlNode.attribute("layer").value(),CP_UTF8));
				iItem++;
				xmlNode=xmlNode.next_sibling("resid");
			}
			m_strPrjPath=fileDlg.m_szFileName;
			int index=m_strPrjPath.ReverseFind(_T('\\'));
			m_strPrjPath=m_strPrjPath.Left(index+1);
		}
	}
}

LRESULT CUIHander::OnListCtrl_SelChanged( LPDUINMHDR pnmh )
{
	DUINMLBSELCHANGE *pLCNmhdr=(DUINMLBSELCHANGE*)pnmh;
	if(pLCNmhdr->nNewSel!=-1)
	{
		CDuiListCtrl * pListFile=m_pMainDlg->FindChildByName2<CDuiListCtrl *>("prj_list_file");
		CDuiTabCtrl * pTabView=m_pMainDlg->FindChildByName2<CDuiTabCtrl *>("tab_view");
		TCHAR szBuf[1025]={0};
		DXLVSUBITEM item;
		item.mask=DUI_LVIF_TEXT;
		item.cchTextMax=300;
		item.strText=szBuf;
		pListFile->GetSubItem(pLCNmhdr->nNewSel,0,&item);
		if(_tcscmp(szBuf,_T("XML"))==0)
		{
			pTabView->SetCurSel(1);
			pListFile->GetSubItem(pLCNmhdr->nNewSel,2,&item);
			CDuiStringT strXmlPath=m_strPrjPath+szBuf;
			CDuiRealWnd *pRealWnd=m_pMainDlg->FindChildByName2<CDuiRealWnd *>("xmleditor");
			CScintillaWnd *pXmlEditor=(CScintillaWnd *)pRealWnd->GetUserData();
			if(pXmlEditor) pXmlEditor->OpenFile(strXmlPath);
		}else
		{
			pTabView->SetCurSel(0);
		}
	}
	return 0;
}