
// MyDialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDialog.h"
#include "MyDialogDlg.h"
#include "afxdialogex.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyDialogDlg 对话框



CMyDialogDlg::CMyDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab1);
}

BEGIN_MESSAGE_MAP(CMyDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CMyDialogDlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON2, &CMyDialogDlg::OnBnClickedButton2)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyDialogDlg::OnTcnSelchangeTab1)
ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CMyDialogDlg 消息处理程序

BOOL CMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	RegisterHotKey(this->m_hWnd , 100,NULL , VK_HOME);
	RegisterHotKey(this->m_hWnd , 110,NULL , VK_F10);
	RegisterHotKey(this->m_hWnd , 111,NULL , VK_F11);
	SetTab();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyDialogDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMyDialogDlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	theApp.InitDM();
//	theApp.dm.Uninit();
//
//	theApp.Thread_BeginGame_Win_wait= AfxBeginThread(AFX_THREADPROC(WaitBeginGames),this);
//}


//void CMyDialogDlg::OnBnClickedButton2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//
//	theApp.dm.Init();
//	if (!theApp.dm.MyReg())
//	{
//		AfxMessageBox("erro");
//	}
//
//	OutputDebugStringA(theApp.dm.Ver());  
// 
//	theApp.dm.ForceUnBindWindow(	theApp.dm.FindWindowEx(0,"","PVP.net"));
//}



/*
void CMyDialogDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.InitDM();
	//	theApp.dm.Uninit();

	theApp.Thread_BeginGame_Win_wait= AfxBeginThread(AFX_THREADPROC(WaitBeginGames),this);
}


void CMyDialogDlg::OnBnClickedButton2()
{
// TODO: 在此添加控件通知处理程序代码

theApp.dm.Init();
if (!theApp.dm.MyReg())
{
AfxMessageBox("erro");
}

OutputDebugStringA(theApp.dm.Ver());  

theApp.dm.ForceUnBindWindow(	theApp.dm.FindWindowEx(0,"","PVP.net"));
}
*/


void  CMyDialogDlg::SetTab()
{
	m_tab1.InsertItem(0,"游戏模式");
	m_tab1.InsertItem(1,"英雄设置");
	/*
	TAB_ALL.InsertItem(1,"账号设置");
	TAB_ALL.InsertItem(2,"刷图配置");
	TAB_ALL.InsertItem(3,"各种命令配置");
	TAB_ALL.InsertItem(4,"等级与地图配置");
	TAB_ALL.InsertItem(5,"卖物与上架");
	TAB_ALL.InsertItem(6,"疲劳刷完后设置");
	TAB_ALL.InsertItem(7,"安全设置");
	TAB_ALL.InsertItem(8,"自带内存细化设置");
	TAB_ALL.InsertItem(9,"转职");
	TAB_ALL.InsertItem(10,"脚本编辑");*/
	RECT mtab_rect;
	m_tab1.GetClientRect(&mtab_rect);
	mtab_rect.left=mtab_rect.left;
	mtab_rect.top=mtab_rect.top+20;
	mtab_rect.right=mtab_rect.right;
	mtab_rect.bottom=mtab_rect.bottom-0;

	theApp.m_dlg_youximoshi.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB1));
	theApp.m_dlg_youximoshi.MoveWindow(&mtab_rect);
	theApp.m_dlg_youximoshi.ShowWindow(1);

	theApp.m_dlg_yingxiong.Create(IDD_DIALOG2,GetDlgItem(IDC_TAB1));
	theApp.m_dlg_yingxiong.MoveWindow(&mtab_rect);
	theApp.m_dlg_yingxiong.ShowWindow(0);

	int rrt= theApp.MessageBoxTimeoutA(0,"3秒后将自动运行辅助 \r\n  取消请点击‘否’","3秒后消失",MB_YESNO,0,3000);
	if (rrt != IDNO)
	{
		theApp.m_dlg_youximoshi.OnBnClickedButton1();
	}
}

void CMyDialogDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int TABSEL=m_tab1.GetCurSel();
	switch (TABSEL)
	{
	case 0:
		theApp.m_dlg_yingxiong.ShowWindow(0);
		theApp.m_dlg_youximoshi.ShowWindow(1);
		
		break;

	case 1:
		theApp.m_dlg_youximoshi.ShowWindow(0);
		theApp.m_dlg_yingxiong.ShowWindow(1);
		break;
	default:
		break;
	}
}


void CMyDialogDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

/*
	RegisterHotKey(this->m_hWnd , 100,NULL , VK_HOME);
	RegisterHotKey(this->m_hWnd , 110,NULL , VK_F10);
	RegisterHotKey(this->m_hWnd , 111,NULL , VK_F11);*/
	if (nHotKeyId ==100)
	{
	 theApp.m_dlg_youximoshi.OnBnClickedButton1();
	}else  if (nHotKeyId ==110)
	{
		if (theApp.Thread_GameThread != nullptr)
		{
			theApp.Thread_GameThread->SuspendThread();
		}
		if (theApp.Thread_GameThread_Sub != nullptr)
		{
			theApp.Thread_GameThread_Sub->SuspendThread();
		}
	 
	} else  if (nHotKeyId ==111)
	{

		if (theApp.Thread_GameThread != nullptr)
		{
				theApp.Thread_GameThread->ResumeThread();
		}
		if (theApp.Thread_GameThread_Sub != nullptr)
		{
				theApp.Thread_GameThread_Sub->ResumeThread();
		}


	
	} 
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);

}
