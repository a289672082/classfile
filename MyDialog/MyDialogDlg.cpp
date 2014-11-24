
// MyDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyDialog.h"
#include "MyDialogDlg.h"
#include "afxdialogex.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMyDialogDlg �Ի���



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


// CMyDialogDlg ��Ϣ�������

BOOL CMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	RegisterHotKey(this->m_hWnd , 100,NULL , VK_HOME);
	RegisterHotKey(this->m_hWnd , 110,NULL , VK_F10);
	RegisterHotKey(this->m_hWnd , 111,NULL , VK_F11);
	SetTab();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMyDialogDlg::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	theApp.InitDM();
//	theApp.dm.Uninit();
//
//	theApp.Thread_BeginGame_Win_wait= AfxBeginThread(AFX_THREADPROC(WaitBeginGames),this);
//}


//void CMyDialogDlg::OnBnClickedButton2()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	theApp.InitDM();
	//	theApp.dm.Uninit();

	theApp.Thread_BeginGame_Win_wait= AfxBeginThread(AFX_THREADPROC(WaitBeginGames),this);
}


void CMyDialogDlg::OnBnClickedButton2()
{
// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	m_tab1.InsertItem(0,"��Ϸģʽ");
	m_tab1.InsertItem(1,"Ӣ������");
	/*
	TAB_ALL.InsertItem(1,"�˺�����");
	TAB_ALL.InsertItem(2,"ˢͼ����");
	TAB_ALL.InsertItem(3,"������������");
	TAB_ALL.InsertItem(4,"�ȼ����ͼ����");
	TAB_ALL.InsertItem(5,"�������ϼ�");
	TAB_ALL.InsertItem(6,"ƣ��ˢ�������");
	TAB_ALL.InsertItem(7,"��ȫ����");
	TAB_ALL.InsertItem(8,"�Դ��ڴ�ϸ������");
	TAB_ALL.InsertItem(9,"תְ");
	TAB_ALL.InsertItem(10,"�ű��༭");*/
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

	int rrt= theApp.MessageBoxTimeoutA(0,"3����Զ����и��� \r\n  ȡ����������","3�����ʧ",MB_YESNO,0,3000);
	if (rrt != IDNO)
	{
		theApp.m_dlg_youximoshi.OnBnClickedButton1();
	}
}

void CMyDialogDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
