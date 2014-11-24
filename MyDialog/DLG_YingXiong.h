#pragma once
#include "vsflexgridl1.h"
#include "afxvslistbox.h"
#include "MyGrid.h"
#include "afxwin.h"


// DLG_YingXiong �Ի���

class DLG_YingXiong : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_YingXiong)

public:
	DLG_YingXiong(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DLG_YingXiong();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
   
//	afx_msg void OnBnClickedButton1();
		afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
		afx_msg void OnGridEndEdit_LUXIAN(NMHDR *pNotifyStruct, LRESULT* pResult);
				afx_msg void OnGridEndEdit_JINENG(NMHDR *pNotifyStruct, LRESULT* pResult);
		afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
		afx_msg void OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
		void SetGrid(); 
	 	MyGrid  m_Grid;
	  	MyGrid m_Grid_Luxian;
		MyGrid m_Grid_JINENG;
		virtual BOOL OnInitDialog();
		CComboBox m_luxian_box;
		afx_msg void OnCbnSelchangeCombo1();
		CComboBox m_jinengBox;
		std::vector<std::string> YingxionglIST;//����Ӣ���б�
		void UpdataYingXiong();//��Ӣ���б����Ӣ����ȡ��YingxionglIST

		CString TmpCstring;
		afx_msg void OnCbnSelchangeCombo2();
};
