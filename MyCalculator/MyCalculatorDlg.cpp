// MyCalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyCalculator.h"
#include "MyCalculatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyCalculatorDlg dialog




CMyCalculatorDlg::CMyCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCalculatorDlg::IDD, pParent)
	, m_strResult(_T(""))
	, m_bNumber(false)
	, m_bOperator(false)
	, m_bIsMinus(false)
	, m_bDot(false)
	, m_strIndirectValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//默认为+法
	m_eOper = OperationFactory::OPER_ADD;
}

void CMyCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT_INDIRECTVALUE, m_strIndirectValue);
}

BEGIN_MESSAGE_MAP(CMyCalculatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CANCLE, &CMyCalculatorDlg::OnBnClickedBtnCancle)
	ON_BN_CLICKED(IDC_BTN_NUM0, &CMyCalculatorDlg::OnBnClickedBtnNum0)
	ON_BN_CLICKED(IDC_BTN_NUM1, &CMyCalculatorDlg::OnBnClickedBtnNum1)
	ON_BN_CLICKED(IDC_BTN_NUM2, &CMyCalculatorDlg::OnBnClickedBtnNum2)
	ON_BN_CLICKED(IDC_BTN_NUM3, &CMyCalculatorDlg::OnBnClickedBtnNum3)
	ON_BN_CLICKED(IDC_BTN_NUM4, &CMyCalculatorDlg::OnBnClickedBtnNum4)
	ON_BN_CLICKED(IDC_BTN_NUM5, &CMyCalculatorDlg::OnBnClickedBtnNum5)
	ON_BN_CLICKED(IDC_BTN_NUM6, &CMyCalculatorDlg::OnBnClickedBtnNum6)
	ON_BN_CLICKED(IDC_BTN_NUM7, &CMyCalculatorDlg::OnBnClickedBtnNum7)
	ON_BN_CLICKED(IDC_BTN_NUM8, &CMyCalculatorDlg::OnBnClickedBtnNum8)
	ON_BN_CLICKED(IDC_BTN_NUM9, &CMyCalculatorDlg::OnBnClickedBtnNum9)
	ON_BN_CLICKED(IDC_BTN_ADD, &CMyCalculatorDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SUB, &CMyCalculatorDlg::OnBnClickedBtnSub)
	ON_BN_CLICKED(IDC_BTN_MUL, &CMyCalculatorDlg::OnBnClickedBtnMul)
	ON_BN_CLICKED(IDC_BTN_DIV, &CMyCalculatorDlg::OnBnClickedBtnDiv)
	ON_BN_CLICKED(IDC_BTN_DOT, &CMyCalculatorDlg::OnBnClickedBtnDot)
	ON_BN_CLICKED(IDC_BTN_MINUS, &CMyCalculatorDlg::OnBnClickedBtnMinus)
	ON_BN_CLICKED(IDC_BTN_LBRACKET, &CMyCalculatorDlg::OnBnClickedBtnLbracket)
	ON_BN_CLICKED(IDC_BTN_RBRACKET, &CMyCalculatorDlg::OnBnClickedBtnRbracket)
	ON_BN_CLICKED(IDC_BTN_EQUAL, &CMyCalculatorDlg::OnBnClickedBtnEqual)
END_MESSAGE_MAP()


// CMyCalculatorDlg message handlers

BOOL CMyCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//清除按钮
void CMyCalculatorDlg::OnBnClickedBtnCancle()
{
	// TODO: Add your control notification handler code here
	m_Calculator.Clear();
	m_bIsMinus = false;
	m_bNumber = false;
	m_bOperator = false;
	m_strResult.Empty();
	m_strIndirectValue.Empty();
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum0()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	if (m_strResult == _T("0"))
	{
		return;
	}
	m_strResult += _T("0");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum1()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("1");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum2()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("2");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum3()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("3");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum4()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("4");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum5()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("5");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum6()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("6");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum7()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("7");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum8()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("8");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnNum9()
{
	// TODO: Add your control notification handler code here
	PushOperator();
	m_strResult += _T("9");
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	//运算符号前面也可能是括号
	if (m_bNumber)
	{
		PushNumber();
	}
	else
	{
		PushOperator();
		//自身也是一种符号，所以将m_bOperator置为true
		m_bOperator = true;
		m_bNumber = false;
		m_bIsMinus = false;
	}
	m_eOper = OperationFactory::OPER_ADD;
}

void CMyCalculatorDlg::OnBnClickedBtnSub()
{
	// TODO: Add your control notification handler code here
	//运算符号前面也可能是括号
	if (m_bNumber)
	{
		PushNumber();
	}
	else
	{
		PushOperator();
		//自身也是一种符号，所以将m_bOperator置为true
		m_bOperator = true;
		m_bNumber = false;
		m_bIsMinus = false;
	}
	m_eOper = OperationFactory::OPER_SUB;
}

void CMyCalculatorDlg::OnBnClickedBtnMul()
{
	// TODO: Add your control notification handler code here
	//运算符号前面也可能是括号
	if (m_bNumber)
	{
		PushNumber();
	}
	else
	{
		PushOperator();
		//自身也是一种符号，所以将m_bOperator置为true
		m_bOperator = true;
		m_bNumber = false;
		m_bIsMinus = false;
	}
	m_eOper = OperationFactory::OPER_MUL;
}

void CMyCalculatorDlg::OnBnClickedBtnDiv()
{
	// TODO: Add your control notification handler code here
	//运算符号前面也可能是括号
	if (m_bNumber)
	{
		PushNumber();
	}
	else
	{
		PushOperator();
		//自身也是一种符号，所以将m_bOperator置为true
		m_bOperator = true;
		m_bNumber = false;
		m_bIsMinus = false;
	}
	m_eOper = OperationFactory::OPER_DIV;
}

void CMyCalculatorDlg::OnBnClickedBtnDot()
{
	// TODO: Add your control notification handler code here
	if (!m_bDot)
	{
		PushOperator();
		m_strResult += _T(".");
		UpdateData(FALSE);
		m_bDot = true;
	}
}

//在数字前加减负号
void CMyCalculatorDlg::OnBnClickedBtnMinus()
{
	// TODO: Add your control notification handler code here
	m_bIsMinus = !m_bIsMinus;
	if (m_bIsMinus)
	{
		m_strResult = _T("-") + m_strResult;
	}
	else
	{
		m_strResult = m_strResult.Right(m_strResult.GetLength()-1);
	}
	
	UpdateData(FALSE);
}

void CMyCalculatorDlg::OnBnClickedBtnLbracket()
{
	// TODO: Add your control notification handler code here
	//左括号左侧只可能是一个运算符或者另一个左括号
	if (m_bOperator)
	{
		PushOperator();
		//自身也是一种符号，所以将m_bOperator置为true
		m_bOperator = true;
		m_bNumber = false;
		m_bIsMinus = false;
	}
	m_eOper = OperationFactory::OPER_LBRACKET;
}

void CMyCalculatorDlg::OnBnClickedBtnRbracket()
{
	// TODO: Add your control notification handler code here
	//右括号左侧可能是数字也可能是另一个右括号
	if (m_bNumber)
	{
		PushNumber();
	}
	else
	{
		PushOperator();
		//自身也是一种符号，所以将m_bOperator置为true
		m_bOperator = true;
		m_bNumber = false;
		m_bIsMinus = false;
	}
	m_eOper = OperationFactory::OPER_RBRACKET;
}

bool CMyCalculatorDlg::PushOperator(void)
{
	if (m_bOperator)
	{
		m_Calculator.PushOperator(m_eOper);
		

		m_bOperator = false;
		m_bNumber = true;
		return true;
	}
	m_bNumber = true;
	return false;
}

bool CMyCalculatorDlg::PushNumber(void)
{
	if (m_bNumber)
	{
		//取得editbox上的数字字符串转换为double
		double dNum = _tstof(m_strResult.GetBuffer(0));
		m_Calculator.PushNumber(dNum);

		//获得中间值
		double dResult = m_Calculator.GetIndirectValue();
		m_strIndirectValue.Format(_T("%lf"), dResult);
		UpdateData(FALSE);

		m_strResult.Empty();
		m_bNumber = false;
		m_bDot = false;
		m_bIsMinus = false;
		m_bOperator = true;
		return true;
	}
	m_bOperator = true;
	return false;
}
void CMyCalculatorDlg::OnBnClickedBtnEqual()
{
	// TODO: Add your control notification handler code here
	//将最后一个数存入
	if (m_bNumber)
	{
		PushNumber();
	}
	//如果以右括号结束运算式，存入右括号
	else
	{
		PushOperator();
		//自身也是一种符号，所以将m_bOperator置为true
		m_bOperator = true;
		m_bNumber = false;
		m_bIsMinus = false;
	}
	m_eOper = OperationFactory::OPER_EQUAL;
	PushOperator();
	//获得结果值
	double dResult = m_Calculator.GetResult();
	m_strResult.Format(_T("%lf"), dResult);
	UpdateData(FALSE);
}
