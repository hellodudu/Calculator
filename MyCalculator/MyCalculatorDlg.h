// MyCalculatorDlg.h : header file
//

#pragma once

#include "Operation.h"
#include "OperationFactory.h"
#include "Calculator.h"

// CMyCalculatorDlg dialog
class CMyCalculatorDlg : public CDialog
{
// Construction
public:
	CMyCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYCALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCancle();
	Calculator m_Calculator;
	afx_msg void OnBnClickedBtnNum0();
	afx_msg void OnBnClickedBtnNum1();
	afx_msg void OnBnClickedBtnNum2();
	afx_msg void OnBnClickedBtnNum3();
	afx_msg void OnBnClickedBtnNum4();
	afx_msg void OnBnClickedBtnNum5();
	afx_msg void OnBnClickedBtnNum6();
	afx_msg void OnBnClickedBtnNum7();
	afx_msg void OnBnClickedBtnNum8();
	afx_msg void OnBnClickedBtnNum9();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSub();
	afx_msg void OnBnClickedBtnMul();
	afx_msg void OnBnClickedBtnDiv();
	afx_msg void OnBnClickedBtnDot();
	afx_msg void OnBnClickedBtnMinus();
	afx_msg void OnBnClickedBtnLbracket();
	afx_msg void OnBnClickedBtnRbracket();
	CString m_strResult;
	// 是否在之前按下过了数字按钮
	bool m_bNumber;
	// 是否在之前按下过了运算符按钮
	bool m_bOperator;
	// 是否在之前按下过了正负号按钮
	bool m_bIsMinus;
	// 存放按下的运算符
	OperationFactory::OPERATION m_eOper;
	bool PushOperator(void);
	bool PushNumber(void);
	afx_msg void OnBnClickedBtnEqual();
	bool m_bDot;
	CString m_strIndirectValue;
};
