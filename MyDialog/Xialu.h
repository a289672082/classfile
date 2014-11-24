#pragma once
#include "Mydm.h"
typedef  struct _MyStructTa
{
	POINT  ArrayFangYu;
	POINT  ArrayGongJi;
	char   TA_NO_END_PIC[256];
	int x1;
	int y1;
	int x2;
	int y2;
}MyStructTa,*PMyStructTa; 

class CXialu
{
public:
	POINT  PaoluXY;
	int CurIndex;
	MyStructTa  CurTA_XY; 
	MyStructTa  TA[20];
	void SetCurTA(int index);
	bool  GotoTA_SUB(Mydm* dm); 
	bool  CXialu::GotoTA_SUB_gongji(Mydm* dm);
	bool IsTA_GONGJI_OVER(Mydm* dm);
	void  InitXialu();
	void InitZhongLu();
	void InitShangLu();
	void CXialu::Check_ShiJiao(Mydm* dm,bool OFF);//�л��ӽ�  true ���Լ�Ϊ���� false ƽ��ģʽ
	CXialu(void);
	~CXialu(void);
};

