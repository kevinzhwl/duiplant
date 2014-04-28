
// mfc.demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc.demo.h"
#include "mfc.demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcdemoDlg 对话框




CmfcdemoDlg::CmfcdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcdemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1,OnDuiDlg)
END_MESSAGE_MAP()


// CmfcdemoDlg 消息处理程序

BOOL CmfcdemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfcdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <dui/DuiSystem.h> 
#include <dui/DuiDefaultLogger.h>
#include "MainDlg.h"

using namespace DuiEngine;

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

void CmfcdemoDlg::OnDuiDlg()
{
	TCHAR szCurrentDir[MAX_PATH+1]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, MAX_PATH );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   

	DuiSystem duiSystem(theApp.m_hInstance);

	DefaultLogger loger;
	loger.setLogFilename(CDuiStringT(szCurrentDir)+_T("\\dui-demo.log"));
	duiSystem.SetLogger(&loger);

	duiSystem.logEvent(_T("demo started"));
	//加载ID名称对照表
	pugi::xml_document xmlNamedID;
	LoadXmlFromResource(xmlNamedID,theApp.m_hInstance,MAKEINTRESOURCE(IDR_NAME2ID),_T("XML2"));
	DuiName2ID::getSingletonPtr()->Init(xmlNamedID.first_child());
	//从资源加载皮肤
	duiSystem.SetResProvider(new DuiResProviderPE(theApp.m_hInstance));
	BOOL bOK=duiSystem.Init(_T("IDR_DUI_INIT")); //初始化DUI系统,原来的系统初始化方式依然可以使用。
	duiSystem.SetMsgBoxTemplate(_T("IDR_DUI_MSGBOX"));

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}

	duiSystem.logEvent(_T("demo end"));

	delete duiSystem.GetResProvider();
}

