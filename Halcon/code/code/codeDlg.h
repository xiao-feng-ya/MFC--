
// codeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CcodeDlg 对话框
class CcodeDlg : public CDialogEx
{
// 构造
public:
	CcodeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 一号相机复选框的变量
	CButton m_check1;
	// 第2个相机的复选框变量
	CButton m_check2;
	// 第3个相机的复选框变量
	CButton m_check3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void Icamera1();//初始化相机1,
	void Icamera2();//初始化相机2，
	void Icamera3();//初始化相机3，
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5();
};
