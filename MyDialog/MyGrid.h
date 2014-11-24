#pragma once
#include "GridCtrl_src/GridCtrl.h" 
#include "NewCellTypes/GridURLCell.h"
#include "NewCellTypes/GridCellCombo.h"
#include "NewCellTypes/GridCellCheck.h"
#include "NewCellTypes/GridCellNumeric.h"
#include "NewCellTypes/GridCellDateTime.h"

class MyGrid :public CGridCtrl
{
public:
	MyGrid(void);
	void Init(int col,int row);

	//����ָ���в������̶��е����и�ʽΪ�����б�
	void SetOneColToCellCombo(CStringArray& options,int ColIndex);

	//�ѵ�0�и�ʽ��������ַ�
	void FormatFillRowNameBy_Index(char* name);
	void Myupdata();
	void  Myupdata_Luxian();
	void  Myupdata_JINENG();
	//�����ƶ���ͷ������
	void  SetColHeaderText(char* text , int col);
	//����ĳ��ֻ����������
	void Set_NunberOnly(int col);
	~MyGrid(void);
};


 
