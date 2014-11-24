
// MyDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
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
// �йش����ʵ�֣������ MyDialog.cpp
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
		char CurPath[1024];//ȫ�ֵ�ǰ·��
		char TmpBufer[256];
		char  GamePath[256];
	///�ڴ�й¶���
 
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
    map<CString , CString>  mapYx;//Ӣ�ۺ�Ӣ���ߵ�·��
	multimap<CString , bool>  map_ZhuangBei;//��ǰˢ��Ӣ������Ҫ�����װ���б�

	//����·�߶�Ӧ��ͼƬ �� ����
	YingxiongTa  LAN_Ta_xia[20];//��������
	YingxiongTa  LAN_Ta_zhong[20];//��������
	YingxiongTa  LAN_Ta_shang[20];//��������

	YingxiongTa  HONG_Ta_xia[20];//�췽����
	YingxiongTa  HONG_Ta_zhong[20];//�췽����
	YingxiongTa  HONG_Ta_shang[20];//�췽����
	void Init_Ta();//��ʼ�� �������Ľṹ��  
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
	void Sub_Slect_LeiXin(Mydm* dm,int x ,  int y , int index );//ѡ����Ϸ���� 1��Ҷ�ս 2�˻���ս ������ҳͼƬ��λ��

	void Sub_Slect_Moshi(Mydm* dm,int x ,  int y , int index );//ѡ����Ϸģʽ 1�����ս 2ͳ��ս�� ������ҳͼƬ��λ��

	void Sub_Slect_Ditu(Mydm* dm,int x ,  int y , int index );//ѡ����Ϸ��ͼ 1�ٻ�Ͽ�� 2Ť������ ������ҳͼƬ��λ��
	void Sub_Slect_Nandu(Mydm* dm,int x ,  int y , int index );//ѡ����Ϸ�Ѷ� 1���� 2��  3 ���Ѵ�����ҳͼƬ��λ��
	void Sub_Slect_begin(Mydm* dm,int x ,  int y  );//ѡ��ϵͳƥ�� ������ҳͼƬ��λ��

	bool WaitBegin(Mydm* dm);//�ȴ���Ϸ��ʼ���뷿��

	void ClickKishi(Mydm*  dm);//���ҵ����ʼ��ť ����з����沢���
	bool  Sel_Yingxiong(char*  Name,Mydm* dm);
	bool Wait_GameFun(Mydm* dm);//�ȴ�����Ϸ����
	void  Check_ShiJiao(Mydm*  dm);
	bool GetYingxiongList();//��������ģʽ
		bool GetYingxiongArray();//���鲻����ģʽ
	bool GetZhuangBeiList(char*  YingxiongName);

	//////////////////////////���////////////////////////////////////////////////
	int DaGuai(Mydm*  dm);//���������
	bool  DaXiaoGuai(Mydm*  dm);//��С�� ûС�ַ��ؼ�
	int Check_DianNao(Mydm* dm);//�ж϶Է����� ����-1 ������Ҫ����
	void add_jineng(Mydm* dm);//�Ӽ��ܵ�
	bool Check_HP(Mydm* dm);//���HP�Ƿ���Ҫ�ܻ��߻س�  ���ؼ�  ��Ҫ�ܻ�س�
	int  DaGuai2(Mydm* dm);
	void  Paolu(Mydm* dm); 
	void MoveToMyXiaoGuai(Mydm* dm);//�ߵ��Լ���С����
	bool  IsDear(Mydm* dm);//�Ƿ��ڳ���
	bool IsWeiXian(Mydm* dm);//�ж��Ƿ���Σ��  �з��й��� �Լ��ⷽû��Ԯ��
	void Bay();
	bool  BaySome(Mydm* dm , char* Name);
	///////////////////////////////����߳�///////////////////////////////////////////
	int  Code;//0 ��ִ��  -1������Ϸ�߳�������� 1 ִ����· 2 ִ������ ��д
	void CreateHelpThread();
	void WriteLog(char*  str);
	//////////////////////////////���ߵ�¼////////////////////////////////////////////
	bool FastDengLu(Mydm*  dm);

	bool  Reg_YiYou();
	void  CloseOtherWindow(Mydm* dm);
	CMyDialogApp();



// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyDialogApp theApp;