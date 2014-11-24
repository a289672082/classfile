#pragma once
#include "afxwin.h"


// dlg_YouxiMoshi 对话框

class dlg_YouxiMoshi : public CDialogEx
{
	DECLARE_DYNAMIC(dlg_YouxiMoshi)

public:
	dlg_YouxiMoshi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dlg_YouxiMoshi();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_duizhan;
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_youximoshi;
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_nandu;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_str;
	CEdit m_nun;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CEdit m_lujin;
	afx_msg void OnBnClickedButton7();
	CButton m_bulujin;
	afx_msg void OnBnClickedCheck1();
};
