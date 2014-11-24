// DLG_YingXiong.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDialog.h"
#include "DLG_YingXiong.h"
#include "afxdialogex.h"


// DLG_YingXiong 对话框

IMPLEMENT_DYNAMIC(DLG_YingXiong, CDialogEx)

DLG_YingXiong::DLG_YingXiong(CWnd* pParent /*=NULL*/)
	: CDialogEx(DLG_YingXiong::IDD, pParent)
{

}

DLG_YingXiong::~DLG_YingXiong()
{
}
CDataExchange* pDX1=NULL;
void DLG_YingXiong::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);    
	DDX_GridControl(pDX, IDC_GRIDCTRL, m_Grid);
	DDX_GridControl(pDX, IDC_t2, m_Grid_Luxian);
	DDX_GridControl(pDX, IDC_GRIDCTRL_JINENG, m_Grid_JINENG);

	DDX_Control(pDX, IDC_COMBO1, m_luxian_box);
	DDX_Control(pDX, IDC_COMBO2, m_jinengBox);
}


BEGIN_MESSAGE_MAP(DLG_YingXiong, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON1, &DLG_YingXiong::OnBnClickedButton1)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRIDCTRL, OnGridEndEdit)
	ON_NOTIFY(NM_CLICK, IDC_GRIDCTRL, OnGridClick)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRIDCTRL, OnGridEndSelChange)
 	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_t2, OnGridEndEdit_LUXIAN)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRIDCTRL_JINENG, OnGridEndEdit_JINENG)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DLG_YingXiong::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &DLG_YingXiong::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()

void DLG_YingXiong::OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT*  pResult)
{ 
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	CString  DD;
	DD.Format(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(DD);
	*pResult = 0/*(m_bRejectEditChanges)? -1 : 0*/;
	//SaveToIni(m_Grid);


	if (pItem->iRow > 0)
	{
		
		 //更新路线表格
			CString  TEXT2 =m_Grid.GetItemText(pItem->iRow, 1);//判断有没有英雄
		
			if (TEXT2.IsEmpty() == FALSE   &&  TEXT2.GetLength()>2)
			{ 
				for (int x = 0 ;  x<m_luxian_box.GetCount() ;x++ )
				{
					int  Index = m_luxian_box.FindString(0,TEXT2.GetBuffer(0)) ;
					if (Index >= 0 )
					{
						m_luxian_box.SetCurSel(Index);
					}else
					{
						m_luxian_box.InsertString(0,TEXT2.GetBuffer(0));
					}
					CString Jinengx;
					Jinengx.Format(".\\英雄配置\\%s装备.TXT",TEXT2.GetBuffer(0));
					m_Grid_Luxian.Load(Jinengx.GetBuffer(0) , '|'); 
					m_Grid_Luxian.Myupdata_Luxian();
				} 
				m_Grid_Luxian.UpdateData(FALSE);
			}

			 
	 ///////////////////////////////更新技能表格///////////////////////////////////////////
			TEXT2.Empty();
		  TEXT2 =m_Grid.GetItemText(pItem->iRow, 1);//判断有没有英雄
			if (TEXT2.IsEmpty() == FALSE   &&  TEXT2.GetLength()>2)
			{ 
				for (int x = 0 ;  x<m_jinengBox.GetCount() ;x++ )
				{
					int  Index = m_jinengBox.FindString(0,TEXT2.GetBuffer(0)) ;
					if (Index >= 0 )
					{
						m_jinengBox.SetCurSel(Index);
					}else
					{
						m_jinengBox.InsertString(0,TEXT2.GetBuffer(0));
					}
					CString Jinengx;
					Jinengx.Format(".\\英雄配置\\%s技能.TXT",TEXT2.GetBuffer(0));
					m_Grid_JINENG.Load(Jinengx.GetBuffer(0) , '|');
					CStringArray AR2;
					AR2.Add("状态技能");
					AR2.Add("点击敌人");
					AR2.Add("点击地面"); 
					m_Grid_JINENG.SetOneColToCellCombo(AR2,1);
					m_Grid_JINENG.SetOneColToCellCombo(AR2,2);
					m_Grid_JINENG.SetOneColToCellCombo(AR2,3);
					m_Grid_JINENG.SetOneColToCellCombo(AR2,4);
					m_Grid_JINENG.Myupdata_JINENG();
				} 
				m_jinengBox.UpdateData(FALSE);
			}
	
		 
	} 
}
// DLG_YingXiong 消息处理程序
void DLG_YingXiong::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;/*
	if (pItem->iRow > 0)
	{
		if (pItem->iColumn  == 2)
		{
			AfxMessageBox("2");
			CString  TEXT2 =m_Grid.GetItemText(pItem->iRow, pItem->iColumn);
			if (TEXT2.IsEmpty() == FALSE)
			{
				if (TEXT2.Find("上路")!=-1)
				{
					m_luxian_box.SetCurSel(0);
					m_Grid_Luxian.Load(".\\英雄配置\\上路.TXT",'|');
				}
				if (TEXT2.Find("中路")!=-1)
				{
					m_luxian_box.SetCurSel(1);
					m_Grid_Luxian.Load(".\\英雄配置\\中路.TXT",'|');
				}
				if (TEXT2.Find("下路")!=-1)
				{
					m_luxian_box.SetCurSel(2);
					m_Grid_Luxian.Load(".\\英雄配置\\下路.TXT",'|');
				}
				m_Grid_Luxian.Myupdata_Luxian();
			}

			 
		}
	}*/
	CString  hh;
	CString  TEXT1 =m_Grid.GetItemText(pItem->iRow, pItem->iColumn);

	hh.Format("Clicked on 第 %d 行,第 %d 列\n",pItem->iRow, pItem->iColumn);
	// AfxMessageBox(hh + TEXT1);
}
void DLG_YingXiong::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	CString  DD;
	DD.Format(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(DD);
	*pResult = 0/*(m_bRejectEditChanges)? -1 : 0*/;
	//SaveToIni(m_Grid); 
	m_Grid.Save(".\\英雄配置\\Save.txt",'|');
	UpdataYingXiong();
}
void DLG_YingXiong::OnGridEndEdit_LUXIAN(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	CString  DD;
	m_luxian_box.GetWindowText(DD);
	DD=".\\英雄配置\\"+DD +"装备.Txt";
	//AfxMessageBox(DD);
	*pResult = 0/*(m_bRejectEditChanges)? -1 : 0*/;
	//SaveToIni(m_Grid);
	m_Grid_Luxian.Save(DD.GetBuffer(0),'|');
}


void DLG_YingXiong::OnGridEndEdit_JINENG(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	CString  DD;
	m_jinengBox.GetWindowText(DD);
	DD=".\\英雄配置\\"+DD +"技能.Txt";
	//AfxMessageBox(DD);
	*pResult = 0/*(m_bRejectEditChanges)? -1 : 0*/;
	//SaveToIni(m_Grid);
		m_Grid_JINENG.Save(DD.GetBuffer(0),'|');
}
void DLG_YingXiong::SetGrid()
{


	m_Grid.Init(3,5);
	m_Grid.SetRowCount(10);
	m_Grid.Load(".\\英雄配置\\save.txt",'|');
	m_Grid.SetColHeaderText("    序号   ",0);
	m_Grid.SetColHeaderText("   英雄   ",1);
	m_Grid.SetColHeaderText("   路线   ",2);

	m_Grid.FormatFillRowNameBy_Index("序号");

	CStringArray  AR;
	AR.FreeExtra();
	AR.Add("上路");
	AR.Add("中路");
				AR.Add("下路");
				m_Grid.SetOneColToCellCombo(AR,2);
				m_Grid.Myupdata();


				//////////////////////////////////////////////////////////////////////////
				m_Grid_Luxian.Init(2,5);
				m_Grid_Luxian.SetRowCount(10); 
				m_Grid_Luxian.SetColHeaderText("游戏内购买的装备",0);
			     m_Grid_Luxian.SetColHeaderText("装备名:",1); 

				m_Grid_Luxian.FormatFillRowNameBy_Index("装备"); 
				m_Grid_Luxian.Myupdata_Luxian();

				//////////////////////////////////////////////////////////////////////////

				m_Grid_JINENG.Init(5,1);
				m_Grid_JINENG.SetRowCount(2); 
				m_Grid_JINENG.SetColHeaderText("技能",0);
				m_Grid_JINENG.SetColHeaderText("Q键",1);
				m_Grid_JINENG.SetColHeaderText("W键",2);
				m_Grid_JINENG.SetColHeaderText("E键",3);  
				m_Grid_JINENG.SetColHeaderText("R键",4);  

				CStringArray AR2;
				AR2.Add("状态技能");
				AR2.Add("点击敌人");
				AR2.Add("点击地面"); 
				m_Grid_JINENG.SetOneColToCellCombo(AR2,1);
				m_Grid_JINENG.SetOneColToCellCombo(AR2,2);
				m_Grid_JINENG.SetOneColToCellCombo(AR2,3);
				m_Grid_JINENG.SetOneColToCellCombo(AR2,4);
				m_Grid_JINENG.Myupdata_JINENG();
}


//void DLG_YingXiong::OnBnClickedButton1()
//{ 
//
//}

void DLG_YingXiong::UpdataYingXiong()
{
	YingxionglIST.clear();
	m_jinengBox.Clear();
	m_luxian_box.Clear();
	for (int x = 1 ;  x<m_Grid.GetRowCount()  ; x++)
	{
		TmpCstring.Empty();
	 TmpCstring =	m_Grid.GetItemText(x,1);
		if (TmpCstring.GetLength() > 2)
		{
			YingxionglIST.push_back(TmpCstring.GetBuffer(0));
			m_jinengBox.AddString(TmpCstring.GetBuffer(0));
				m_luxian_box.AddString(TmpCstring.GetBuffer(0));
		}
	}
}
BOOL DLG_YingXiong::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	 	SetGrid();
		UpdataYingXiong();
/*
		m_luxian_box.InsertString(0,"上路");
		m_luxian_box.InsertString(1,"中路");
		m_luxian_box.InsertString(2,"下路");
		m_luxian_box.SetCurSel(0);*/ 
/*
		m_Grid_Luxian = new MyGrid();
		if (pDX1==NULL)
		{
			AfxMessageBox("nuu");
		}
		  DDX_GridControl(pDX1, IDC_GRIDCTRL2, *m_Grid_Luxian); */
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DLG_YingXiong::OnCbnSelchangeCombo1()
{

		CString Jinengx;
	m_luxian_box.GetWindowTextA(Jinengx);


	Jinengx.Format(".\\英雄配置\\%s装备.TXT",Jinengx.GetBuffer(0)); 
	m_Grid_Luxian.Load(Jinengx.GetBuffer(0) , '|');  
	m_Grid_Luxian.SetColHeaderText("游戏内购买的装备",0);
	m_Grid_Luxian.SetColHeaderText("装备名:",1); 
	m_Grid_Luxian.Myupdata_Luxian();
	// TODO: 在此添加控件通知处理程序代码
/*

	CString  TEXT2; 
	m_luxian_box.GetWindowText(TEXT2);
	if (TEXT2.IsEmpty() == FALSE)
	{
		if (TEXT2.Find("上路")!=-1)
		{
			m_luxian_box.SetCurSel(0);
			m_Grid_Luxian.Load(".\\英雄配置\\上路.TXT",'|');
		}
		if (TEXT2.Find("中路")!=-1)
		{
			m_luxian_box.SetCurSel(1);
			m_Grid_Luxian.Load(".\\英雄配置\\中路.TXT",'|');
		}
		if (TEXT2.Find("下路")!=-1)
		{
			m_luxian_box.SetCurSel(2);
			m_Grid_Luxian.Load(".\\英雄配置\\下路.TXT",'|');
		}
 
		m_Grid_Luxian.Myupdata_Luxian();	}*/

}


void DLG_YingXiong::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码


	CString Jinengx;
	m_jinengBox.GetWindowTextA(Jinengx);


	Jinengx.Format(".\\英雄配置\\%s技能.TXT",Jinengx.GetBuffer(0)); 
		AfxMessageBox(Jinengx);
	m_Grid_JINENG.Load(Jinengx.GetBuffer(0) , '|');  
	m_Grid_JINENG.Myupdata_JINENG();
}
