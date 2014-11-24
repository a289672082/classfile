#include "stdafx.h"
#include "MyGrid.h"


MyGrid::MyGrid(void)
{
}


MyGrid::~MyGrid(void)
{
}
void MyGrid::FormatFillRowNameBy_Index(char* name)
{
	char buf[256]={0};
	for (int x = 1 ; x <this->GetRowCount() ; x++)
	{
		sprintf_s(buf,256,"%s%d",name,x);
		this->SetItemText(x,0,buf);
	}
}
void MyGrid::SetColHeaderText(char* text ,int col)
{

/*
		CString str;
		str.Format("%s",text);*/

	GV_ITEM Item;

	Item.mask = GVIF_TEXT;
	Item.row = 0;
	Item.col = col;
	Item.strText=text ;
		this->SetItem(&Item);
		this->AutoSize();
		this->Invalidate();
}
void MyGrid::Set_NunberOnly(int col)
{
	for (int x = 1 ; x<this->GetRowCount() ; x++)
	{
		this->SetCellType(x,col, RUNTIME_CLASS(CGridCellNumeric) ); 

	} 
	

}
void  MyGrid::Init(int col , int row)
{
 

	this->SetVirtualMode(0);
	this->SetEditable(1);
	this->SetAutoSizeStyle();

		TRY { 
			this->SetRowCount(row);
			this->SetColumnCount(col); 
			this->SetFixedColumnCount(1);
			this->SetFixedRowCount(1);
		}
		CATCH (CMemoryException, e)
		{
			e->ReportError();
			return;
		}
		END_CATCH 
			// fill rows/cols with text 
	this->AutoSize();
 

	//UpdateMenuUI();
	this->SetSingleRowSelection(TRUE);//������ɵ�ѡ
	this->SetSingleColSelection(TRUE);//������ɵ�ѡ
	this->SetFixedColumnSelection(FALSE);//��ͷ����ѡ
	this->SetFixedRowSelection(FALSE);//��ͷ����ѡ

	this->EnableTitleTips(FALSE);
	

/*

	LoadFormIni(m_Grid);
	Set_row_text(m_Grid);*/
	this->Invalidate(TRUE);
/*
	����ԭ�ͣ�void EnableTitleTips(BOOL bEnable = TRUE) 
		�������� �������Ƿ�ʹ�ñ�����ʾ*/
	UpdateData(FALSE);
}

 


void MyGrid::Myupdata()
{ 
       this->SetEditable(1); 
		this->SetSingleRowSelection(TRUE);//������ɵ�ѡ
	this->SetSingleColSelection(TRUE);//������ɵ�ѡ
	this->SetFixedColumnSelection(FALSE);//��ͷ����ѡ
	this->SetFixedRowSelection(FALSE);//��ͷ����ѡ

	this->EnableTitleTips(FALSE); 
	this->SetFixedColumnCount(1);
	this->SetFixedRowCount(1);

	this->AutoSize();
	RECT rect;
	this->GetWindowRect(&rect);
	int w = rect.right  - rect.left;
	this->SetColumnWidth(0,w*0.2);
	this->SetColumnWidth(1,w*0.5);
	this->SetColumnWidth(2,w*0.2+10);

	for (int x =1; x< this->GetRowCount() ; x++)
	{
		COLORREF clr = RGB(rand()%180+175 , rand()%180+175, rand()%180+175);

		this->SetItemBkColour(x,1,clr);
		//COLORREF clr2 = RGB(rand()%255 , rand()%255, rand()%255);
		this->SetItemBkColour(x,2,clr); 

		//COLORREF clr3 = RGB(rand()%255 , rand()%255, rand()%255);
		//this->SetItemBkColour(x,0,clr); 
	}
	this->Invalidate(TRUE);
}



void MyGrid::Myupdata_Luxian()
{ 
	this->SetEditable(1); 
	this->SetSingleRowSelection(TRUE);//������ɵ�ѡ
	this->SetSingleColSelection(TRUE);//������ɵ�ѡ
	this->SetFixedColumnSelection(FALSE);//��ͷ����ѡ
	this->SetFixedRowSelection(FALSE);//��ͷ����ѡ

	this->EnableTitleTips(FALSE); 
	this->SetFixedColumnCount(1);
	this->SetFixedRowCount(1);
	this->SetColHeaderText("��Ϸ�ڹ����װ��",0);
	this->SetColHeaderText("װ����:",1); 
	this->AutoSize();
	RECT rect;
	this->GetWindowRect(&rect);
	int w = rect.right  - rect.left;
	this->SetColumnWidth(0,w*0.5);
	this->SetColumnWidth(1,w*0.4); 

	for (int x =1; x< this->GetRowCount() ; x++)
	{
		COLORREF clr = RGB(rand()%255 , rand()%255, rand()%255);

		this->SetItemBkColour(x,1,clr);
		COLORREF clr2 = RGB(rand()%255 , rand()%255, rand()%255);
		this->SetItemBkColour(x,2,clr2); 
	}
	this->Invalidate(TRUE);
}

void MyGrid::Myupdata_JINENG()
{ 
	this->SetEditable(1); 
	this->SetSingleRowSelection(TRUE);//������ɵ�ѡ
	this->SetSingleColSelection(TRUE);//������ɵ�ѡ
	this->SetFixedColumnSelection(FALSE);//��ͷ����ѡ
	this->SetFixedRowSelection(FALSE);//��ͷ����ѡ

	this->EnableTitleTips(FALSE); 
	this->SetFixedColumnCount(1);
	this->SetFixedRowCount(1);
		this->SetItemText(1,0,"����"); 

	
		this->AutoSize();

	RECT rect;
	this->GetWindowRect(&rect);
	int w = rect.right  - rect.left;
	this->SetColumnWidth(0,w*0.2-7);
	this->SetColumnWidth(1,w*0.2+1);
	this->SetColumnWidth(2,w*0.2+1);
	this->SetColumnWidth(3,w*0.2+1);
	this->SetColumnWidth(4,w*0.2+1);
	
	for (int x =1; x< this->GetRowCount() ; x++)
	{
		COLORREF clr = RGB(rand()%255 , rand()%255, rand()%255);

		this->SetItemBkColour(x,1,clr);
		COLORREF clr2 = RGB(rand()%255 , rand()%255, rand()%255);
		this->SetItemBkColour(x,2,clr2); 

		  clr2 = RGB(rand()%255 , rand()%255, rand()%255);
		this->SetItemBkColour(x,3,clr2); 

		  clr2 = RGB(rand()%255 , rand()%255, rand()%255);
		this->SetItemBkColour(x,4,clr2); 

		  clr2 = RGB(rand()%255 , rand()%255, rand()%255);
		this->SetItemBkColour(x,0,clr2); 
	}


	
	this->Invalidate(TRUE);
}

void  MyGrid::SetOneColToCellCombo(CStringArray& options,int ColIndex)
{
	int row = this->GetRowCount(); 

	for (int x= 1 ; x< row ; x++)
	{


		  

		this->SetCellType(x,ColIndex, RUNTIME_CLASS(CGridCellCombo));
		//m_Grid.SetItemText(x,2, _T("��·"));
		CGridCellCombo *pCell = (CGridCellCombo*) this->GetCell(x,ColIndex);
		pCell->SetOptions(options);
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE


	}
}
