
// MyDialog.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "MyCom.h"
#include "./classFile/MyClass.h"
#include "./classFile/FileMapBindWindow.h"
#include "./classFile/ImeInject.h"
#include  "MYDM.h"
#include <setjmp.h> 
#include "dlg_YouxiMoshi.h"
#include "DLG_YingXiong.h"
#include <memory>
#include <map>
#include "Xialu.h"
#include <atlfile.h>
#include <boost/smart_ptr.hpp>
#include<opencv\highgui.h>
#include<opencv\cv.h> 
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include "MyBmp.h"
#include <atlconv.h>
// CMyDialogApp:
// 有关此类的实现，请参阅 MyDialog.cpp
//

typedef int (__stdcall *_MessageBoxTimeoutA)(int a1,char* text1,char* text2,int a3,__int16 a4,int a5);

using namespace std;
typedef  struct _Gamestrct
{
	int DuizhanMoshi;
	int YouxiMoshi;
	int youxiDITU;
	int nandu;

}Gamestrct,*PGamestrct;

typedef  struct _Yingxiongstrct
{
	char yingxiongName[255];
	char LuxianName[255];
}Yingxiong,*PYingxiong;

typedef  struct _YingxiongTa
{
	char TaPicName[255];
	POINT  TaXY ;
	RECT  PIC_RECT;
}YingxiongTa,*PYingxiongTa;

class CMyDialogApp : public CWinApp
{
public:
		 _MessageBoxTimeoutA MessageBoxTimeoutA;
		char CurPath[1024];//全局当前路径
		char TmpBufer[256];
		char  GamePath[256];
	///内存泄露检查
 
	bool  isBind_RomWindow;
	cv::Mat*  mat;
	int TestX,TestY;
		int tmpint1,Tmpint2;
		int indexx;
		CAtlFile  LogFile;
	MyClass  class_code;
	MyFileMap_d3d  class_filemap;
	
	CString  CurYingXiong;
		BOOL  IS_FIRST_GO;
		CXialu  xialu;
	CString  Tmps1,Tmps2, Tmps3;
	CStringW   Tmpsw1;
 	Gamestrct  gm_struct;
	Yingxiong  yingxiongStru[255];
    map<CString , CString>  mapYx;//英雄和英雄走的路线
	multimap<CString , bool>  map_ZhuangBei;//当前刷的英雄所需要购买的装备列表

	//各种路线对应的图片 和 坐标
	YingxiongTa  LAN_Ta_xia[20];//蓝方下塔
	YingxiongTa  LAN_Ta_zhong[20];//蓝方中塔
	YingxiongTa  LAN_Ta_shang[20];//蓝方上塔

	YingxiongTa  HONG_Ta_xia[20];//红方下塔
	YingxiongTa  HONG_Ta_zhong[20];//红方中塔
	YingxiongTa  HONG_Ta_shang[20];//红方上塔
	void Init_Ta();//初始化 上面塔的结构体  
	dlg_YouxiMoshi  m_dlg_youximoshi;
	DLG_YingXiong   m_dlg_yingxiong;
public:
	VARIANT  Tmx,Tmx2,Tmx3,Tmx4;
	VARIANT  Tmy,Tmy2,Tmy3,Tmy4;
	CWinThread* Thread_BeginGame_Win_wait;
	CWinThread* Thread_GameThread;
	CWinThread* Thread_GameThread_Sub;
		CWinThread* Thread_GameThread_Sub_Help;
 
	jmp_buf JMP1,JMP2;
	bool IsEndGame;
		bool IsEndGame_SUB;
		bool  is_endHelp ;
		bool IsGameOver(Mydm*  dm);
	Mydm   dm,dm_game,dm_Help,dm_denglu;
	void  InitDM();
	void Wait(int Mseconds);
		void Wait2(int Mseconds);
	bool Isgame_Begin(Mydm* dm);
	bool  IF_GameBegin(Mydm*  dm);
	void Sub_Slect_LeiXin(Mydm* dm,int x ,  int y , int index );//选择游戏类型 1玩家对战 2人机对战 传入主页图片的位置

	void Sub_Slect_Moshi(Mydm* dm,int x ,  int y , int index );//选择游戏模式 1经典对战 2统治战场 传入主页图片的位置

	void Sub_Slect_Ditu(Mydm* dm,int x ,  int y , int index );//选择游戏地图 1召唤峡谷 2扭曲丛林 传入主页图片的位置
	void Sub_Slect_Nandu(Mydm* dm,int x ,  int y , int index );//选择游戏难度 1入门 2简单  3 困难传入主页图片的位置
	void Sub_Slect_begin(Mydm* dm,int x ,  int y  );//选择系统匹配 传入主页图片的位置

	bool WaitBegin(Mydm* dm);//等待游戏开始进入房间

	void ClickKishi(Mydm*  dm);//查找点击开始按钮 如果有返回真并点击
	bool  Sel_Yingxiong(char*  Name,Mydm* dm);
	bool Wait_GameFun(Mydm* dm);//等待主游戏窗口
	void  Check_ShiJiao(Mydm*  dm);
	bool GetYingxiongList();//容器排序模式
		bool GetYingxiongArray();//数组不排序模式
	bool GetZhuangBeiList(char*  YingxiongName);

	//////////////////////////打怪////////////////////////////////////////////////
	int DaGuai(Mydm*  dm);//打怪主函数
	bool  DaXiaoGuai(Mydm*  dm);//打小怪 没小怪返回假
	int Check_DianNao(Mydm* dm);//判断对方电脑 返回-1 就是需要逃跑
	void add_jineng(Mydm* dm);//加技能点
	bool Check_HP(Mydm* dm);//检查HP是否需要跑或者回城  返回假  需要跑或回城
	int  DaGuai2(Mydm* dm);
	void  Paolu(Mydm* dm); 
	void MoveToMyXiaoGuai(Mydm* dm);//走到自己的小兵那
	bool  IsDear(Mydm* dm);//是否在城里
	bool IsWeiXian(Mydm* dm);//判断是否处于危险  敌方有怪物 自己这方没有援助
	void Bay();
	bool  BaySome(Mydm* dm , char* Name);
	///////////////////////////////检测线程///////////////////////////////////////////
	int  Code;//0 不执行  -1代表游戏线程正常完成 1 执行跑路 2 执行其他 待写
	void CreateHelpThread();
	void WriteLog(char*  str);
	//////////////////////////////掉线登录////////////////////////////////////////////
	bool FastDengLu(Mydm*  dm);

	bool  Reg_YiYou();
	void  CloseOtherWindow(Mydm* dm);
	CMyDialogApp();



// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMyDialogApp theApp;