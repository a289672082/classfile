// dlg_YouxiMoshi.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDialog.h"
#include "dlg_YouxiMoshi.h"
#include "afxdialogex.h" 
#include "GameThread.hpp"


// dlg_YouxiMoshi 对话框

IMPLEMENT_DYNAMIC(dlg_YouxiMoshi, CDialogEx)

dlg_YouxiMoshi::dlg_YouxiMoshi(CWnd* pParent /*=NULL*/)
	: CDialogEx(dlg_YouxiMoshi::IDD, pParent)
{

}

dlg_YouxiMoshi::~dlg_YouxiMoshi()
{
}

void dlg_YouxiMoshi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_duizhan);
	DDX_Control(pDX, IDC_COMBO2, m_youximoshi);
	DDX_Control(pDX, IDC_COMBO3, m_nandu);
	DDX_Control(pDX, IDC_EDIT1, m_str);
	DDX_Control(pDX, IDC_EDIT2, m_nun);
	DDX_Control(pDX, IDC_EDIT3, m_lujin);
	DDX_Control(pDX, IDC_BUTTON7, m_bulujin);
}


BEGIN_MESSAGE_MAP(dlg_YouxiMoshi, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO1, &dlg_YouxiMoshi::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &dlg_YouxiMoshi::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &dlg_YouxiMoshi::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON1, &dlg_YouxiMoshi::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &dlg_YouxiMoshi::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &dlg_YouxiMoshi::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &dlg_YouxiMoshi::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &dlg_YouxiMoshi::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &dlg_YouxiMoshi::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &dlg_YouxiMoshi::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_CHECK1, &dlg_YouxiMoshi::OnBnClickedCheck1)
END_MESSAGE_MAP()


// dlg_YouxiMoshi 消息处理程序


BOOL dlg_YouxiMoshi::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化   
	  theApp.gm_struct.DuizhanMoshi=   ::GetPrivateProfileIntA("游戏模式设置","对战模式",1,".\\配置.ini");
		  theApp.gm_struct.YouxiMoshi=     ::GetPrivateProfileIntA("游戏模式设置","游戏模式",0,".\\配置.ini");
		  theApp.gm_struct.nandu=  	::GetPrivateProfileIntA("游戏模式设置","难度",1,".\\配置.ini");

		::GetPrivateProfileStringA("主界面","游戏路径","",theApp.TmpBufer,256,".\\配置.ini");
		  m_lujin.SetWindowTextA(theApp.TmpBufer);
		  CButton*  bu = (CButton*)GetDlgItem(IDC_CHECK1);
		  theApp.Tmpint2 =  ::GetPrivateProfileIntA("主界面","是否快捷登录",0,".\\配置.ini") ;
		  bu->SetCheck( theApp.Tmpint2);
		  if (theApp.Tmpint2 == 0)
		  {
			  m_lujin.ShowWindow(0);
			    m_bulujin.ShowWindow(0);
		  }
		  //////////////////////////////////////////////////////////////////////////
	m_duizhan.InsertString(0,"玩家对战(别用)");
	m_duizhan.InsertString(1,"人机对战");
	m_duizhan.SetCurSel(  theApp.gm_struct.DuizhanMoshi); 
 	

	 
	m_youximoshi.ResetContent();
	m_youximoshi.InsertString(0,"经典对战模式");
	m_youximoshi.InsertString(1,"统治战场(以后开发)");
	m_youximoshi.SetCurSel(  theApp.gm_struct.YouxiMoshi);



	m_nandu.ResetContent();
	m_nandu.InsertString(0,"入门");
	m_nandu.InsertString(1,"简单(推荐)");
	m_nandu.InsertString(2,"一般(别用)"); 
	m_nandu.SetCurSel(  theApp.gm_struct.nandu);

	OnCbnSelchangeCombo1();
	/*OnCbnSelchangeCombo2();
	OnCbnSelchangeCombo3();*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void dlg_YouxiMoshi::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus); 
	// TODO: 在此处添加消息处理程序代码
}

#include <memory>
void dlg_YouxiMoshi::OnCbnSelchangeCombo1()
{
 int sel=	m_duizhan.GetCurSel(); 

 std::shared_ptr<CString> STR(new CString); 
 STR->Format("%d",sel);
 ::WritePrivateProfileStringA("游戏模式设置","对战模式",STR->GetBuffer(0),".\\配置.ini");
 if (sel == 0)
 {
	 theApp.gm_struct.DuizhanMoshi = 0; 
	 m_youximoshi.ResetContent();
	 m_youximoshi.InsertString(0,"经典对战模式");
	 m_youximoshi.InsertString(1,"暂未开放");
	 m_youximoshi.SetCurSel(theApp.gm_struct.YouxiMoshi);
	 OnCbnSelchangeCombo2();//触发选择变化事件


 
	 m_nandu.ResetContent();
	 m_nandu.InsertString(0,"暂未开放");
	 m_nandu.InsertString(1,"暂未开放");
	 m_nandu.InsertString(2,"自选模式");
	 m_nandu.SetCurSel(theApp.gm_struct.nandu);
	 OnCbnSelchangeCombo3();
 }else if (sel == 1)
 { 
	 theApp.gm_struct.DuizhanMoshi = 1;
	 m_youximoshi.ResetContent();
	 m_youximoshi.InsertString(0,"经典对战模式");
	  m_youximoshi.InsertString(1,"统治战场(以后开发)");
	 m_youximoshi.SetCurSel(theApp.gm_struct.YouxiMoshi);
	  OnCbnSelchangeCombo2();


	  m_nandu.ResetContent();
	  m_nandu.InsertString(0,"入门");
	  m_nandu.InsertString(1,"简单(推荐)");
	  m_nandu.InsertString(2,"一般(别用)");
	   m_nandu.SetCurSel(theApp.gm_struct.nandu);
	  OnCbnSelchangeCombo3();

 }

	// TODO: 在此添加控件通知处理程序代码
}


void dlg_YouxiMoshi::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码



	int sel=	m_youximoshi.GetCurSel();

	std::shared_ptr<CString> STR(new CString); 
	STR->Format("%d",sel);
	::WritePrivateProfileStringA("游戏模式设置","游戏模式",STR->GetBuffer(0),".\\配置.ini");

	if (sel == 0)
	{
		theApp.gm_struct.YouxiMoshi = 0;  
	}else if (sel == 1)
	{
		theApp.gm_struct.YouxiMoshi = 1;  
	} 
}


void dlg_YouxiMoshi::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码


	int sel=	m_nandu.GetCurSel();

	std::shared_ptr<CString> STR(new CString); 
	STR->Format("%d",sel);
	::WritePrivateProfileStringA("游戏模式设置","难度",STR->GetBuffer(0),".\\配置.ini");


	if (sel == 0)
	{
		theApp.gm_struct.nandu = 0; 
	
	}else if (sel == 1)
	{
		theApp.gm_struct.nandu = 1;  
	}else if (sel == 2)
	{
		theApp.gm_struct.nandu = 2;  
	}
}


void dlg_YouxiMoshi::OnBnClickedButton1()
{
	
	// TODO: 在此添加控件通知处理程序代码
	 	 theApp.GetYingxiongList();//这个列表用来找路线索引  英雄数组由下面代替 
		theApp.GetYingxiongArray();//路线无效  但是加上去就算了  用不到
		theApp.Init_Ta(); 
	theApp.InitDM();  
	theApp.Thread_BeginGame_Win_wait= AfxBeginThread(AFX_THREADPROC(WaitBeginGames),this);

}


void dlg_YouxiMoshi::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码



	theApp.InitDM();  
	theApp.dm.Init();
	if (!theApp.dm.MyReg())
	{
		AfxMessageBox("erro");
	}

	OutputDebugStringA(theApp.dm.Ver());  

	theApp.dm.ForceUnBindWindow(	theApp.dm.FindWindowEx(0,"","PVP.net"));


	long m_hwnd =  theApp.dm.FindWindowEx(0,"RiotWindowClass","League of Legends (TM) Client");
	if (m_hwnd<2)
	{
		theApp.dm.ForceUnBindWindow(m_hwnd);
	}
}


void dlg_YouxiMoshi::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.GetYingxiongList();
	theApp.Init_Ta(); 
	theApp.InitDM();
	theApp.Thread_GameThread_Sub=AfxBeginThread(AFX_THREADPROC(BeginGames_sub),&theApp);
 
}


void dlg_YouxiMoshi::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
		theApp.InitDM();
		theApp.dm_game.Init();
		theApp.dm_game.MyReg();
		//PVP.net 客户端
	long  wnd = (long)::FindWindowA(NULL,"League of Legends (TM) Client");
	if (wnd == 0)
	{
		AfxMessageBox("erro  window");
		return  ;
	}
	DWORD pid;
	::GetWindowThreadProcessId((HWND)wnd,&pid);
	theApp.class_filemap.BindWindow(pid,wnd);
	if (!theApp.dm_game.FindInputMethod("沫、D输入法225"))
	{
			AfxMessageBox("输入法没安装");
			    ImeInstallEx(NULL);

	}
	  ImeInstallEx(NULL);
//"沫、D输入法225"

	if (!theApp.dm_game.CheckInputMethod(wnd,"沫、D输入法225"))
	{
		AfxMessageBox("指定窗口的输入法没开启");
		if (	!theApp.dm_game.ActiveInputMethod(wnd,"沫、D输入法225"))
		{
			AfxMessageBox("指定窗口的输入法激活失败");
		}

	}
	// ImeUnInstallEx();
	theApp.dm_game.Uninit();
}


 
static void TestThread(int lp){

	theApp.dm_game.Init();
	theApp.dm_game.MyReg();
	theApp.dm_game.BindWindows2();


	CString  yy;
	theApp.m_dlg_youximoshi.m_str.GetWindowTextA(yy);
	 theApp.TestX=  StrToIntA(yy.GetBuffer(0));


	theApp.m_dlg_youximoshi.m_nun.GetWindowTextA(yy);
	 theApp.TestY=  StrToIntA(yy.GetBuffer(0));

    theApp.IsGameOver(&theApp.dm_game);

	 int Backx=0;
	 int Backy=0;
	while (1)
	{

		Sleep(1000);

		theApp.m_dlg_youximoshi.m_str.GetWindowTextA(yy);
		theApp.TestX=  StrToIntA(yy.GetBuffer(0)); 
		theApp.m_dlg_youximoshi.m_nun.GetWindowTextA(yy);
		theApp.TestY=  StrToIntA(yy.GetBuffer(0));

		if (Backx!=theApp.TestX   ||  Backy!=theApp.TestY )
		{
			theApp.dm_game.MoveTo(theApp.TestX , theApp.TestY);
			Sleep(100);
			theApp.dm_game.RightClick();

			Backx =theApp.TestX ;
			Backy =theApp.TestY;
		}
	}
}


bool  Is_Ontest=false;
void dlg_YouxiMoshi::OnBnClickedButton5()
{

	if (Is_Ontest==true)
	{
		return ;
	}
	Is_Ontest =true;
	// TODO: 在此添加控件通知处理程序代码
 
/*
	CString  yy;
	m_str.GetWindowTextA(yy);
	DWORD  stride =  StrToIntA(yy.GetBuffer(0));


	m_nun.GetWindowTextA(yy);
	DWORD  num =  StrToIntA(yy.GetBuffer(0));
 
		theApp.TestX =stride;
	theApp.TestY =num; */

	theApp.GetYingxiongList(); 
	theApp.Init_Ta(); 
	theApp.InitDM();  
	theApp.Thread_BeginGame_Win_wait= AfxBeginThread(AFX_THREADPROC(TestThread),this);

}


void dlg_YouxiMoshi::OnBnClickedButton6()
{
 
	if (::FindWindowA("#32770","Error Report") != 0)
	{

		OutputDebugStringA("game windows  end");
		system("taskkill /f /im LolClient.exe   & taskkill /f /im LolClient.exe   & taskkill /f /im BsSndRpt.exe & lol.launcher_tencent.exe & exit");
		theApp.IsEndGame_SUB =true;
		theApp.IsEndGame=true;
 
	}
	//theApp.Reg_YiYou();

//	system("taskkill /f /im LolClient.exe   & taskkill /f /im LolClient.exe");

 
/*
	theApp.InitDM();
	theApp.dm.Init();
	theApp.dm.MyReg();
	VARIANT data;
	VARIANT size1;
 theApp.dm.GetScreenDataBmp(0,0,800,600,(VARIANT*)&data ,(VARIANT*) &size1);
         long adr =	theApp.dm.GetScreenData(0,0,800,600);

		 
		 cv::Mat img2;
	cv::Mat img(3,(const int*)&size1.lVal,CV_8UC3,(void*)data.lVal);
	cvtColor(img, img2, CV_BGRA2BGR);
	cv::imshow("w",img2);
	cv::imwrite("c:\\1.bmp",img2);*/
/*
	 AfxMessageBox("end");
	typedef void (WINAPI *PSWITCHTOTHISWINDOW) (HWND,BOOL);
	PSWITCHTOTHISWINDOW SwitchToThisWindow;
	HMODULE hUser32=GetModuleHandle(_T("user32"));
	SwitchToThisWindow=(PSWITCHTOTHISWINDOW)GetProcAddress(hUser32,"SwitchToThisWindow");
 
	SwitchToThisWindow((HWND)theApp.dm_game.m_hwnd,false);*/
 
}


void dlg_YouxiMoshi::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码

	char bufdir[1024]={0};
	::GetCurrentDirectoryA(1024,bufdir);
	AfxMessageBox(bufdir);
	CFileDialog dlg(TRUE,//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
		".exe",//默认的打开文件的类型 
		"Client.exe",//默认打开的文件名 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//打开只读文件 
		"文本文件(*.exe)|Client.exe|所有文件 (*.*)|*.*||");//所有可以打开的文件类型 

	CString m_FilePath;
	if(dlg.DoModal()==IDOK)   
	{ 
		m_FilePath = dlg.GetPathName();////////取出文件路径 
		//	AfxMessageBox(m_FilePath);
		m_lujin.SetWindowText(m_FilePath);
		UpdateData(FALSE); 


		char* SaveGamePath=NULL;
		SaveGamePath=new char[1024];
		sprintf_s(SaveGamePath,1024,"%s\\配置.ini",theApp.CurPath);
		WritePrivateProfileString("主界面","游戏路径",m_FilePath,SaveGamePath);


		delete []SaveGamePath;
	} 

	::SetCurrentDirectoryA(bufdir);


}


void dlg_YouxiMoshi::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码

	CButton*  bu = (CButton*)GetDlgItem(IDC_CHECK1);

 	if (bu->GetCheck() == 0)
	{
		m_lujin.ShowWindow(0);
		m_bulujin.ShowWindow(0);
		::WritePrivateProfileStringA("主界面","是否快捷登录","0",".\\配置.ini");
	}else
	{
		::WritePrivateProfileStringA("主界面","是否快捷登录","1",".\\配置.ini");
		m_lujin.ShowWindow(1);
		m_bulujin.ShowWindow(1);
	}
	
}
