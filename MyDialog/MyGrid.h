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

	//设置指定列不包括固定列的整列格式为下拉列表
	void SetOneColToCellCombo(CStringArray& options,int ColIndex);

	//把第0列格式化成序号字符
	void FormatFillRowNameBy_Index(char* name);
	void Myupdata();
	void  Myupdata_Luxian();
	void  Myupdata_JINENG();
	//设置制定列头的文字
	void  SetColHeaderText(char* text , int col);
	//设置某列只能输入数字
	void Set_NunberOnly(int col);
	~MyGrid(void);
};


 
