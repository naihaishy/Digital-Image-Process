// CommonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "CommonDlg.h"
#include "afxdialogex.h"


// CCommonDlg 对话框

IMPLEMENT_DYNAMIC(CCommonDlg, CDialogEx)

CCommonDlg::CCommonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_COMMON_PARA, pParent)
	, m_P1(0)
	, m_P2(0)
	, m_P3(0)
	, m_P4(_T(""))
	, m_P1Text(_T(""))
	, m_P2Text(_T(""))
	, m_P3Text(_T(""))
	, m_P4Text(_T(""))
	, m_bShowP1(0)
	, m_bShowP2(0)
	, m_bShowP3(0)
	, m_bShowP4(0)
	
{

}

CCommonDlg::~CCommonDlg()
{
}

void CCommonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COMMON_P1, m_P1);
	DDX_Text(pDX, IDC_EDIT_COMMON_P2, m_P2);
	DDX_Text(pDX, IDC_EDIT_COMMON_P3, m_P3);
	DDX_Text(pDX, IDC_EDIT_COMMON_P4, m_P4);
	DDX_Text(pDX, IDC_STATIC_COMMON_P1_TEXT, m_P1Text);
	DDX_Text(pDX, IDC_STATIC_COMMON_P2_TEXT, m_P2Text);
	DDX_Text(pDX, IDC_STATIC_COMMON_P3_TEXT, m_P3Text);
	DDX_Text(pDX, IDC_STATIC_COMMON_P4_TEXT, m_P4Text);
	
}


BEGIN_MESSAGE_MAP(CCommonDlg, CDialogEx)
END_MESSAGE_MAP()


// CCommonDlg 消息处理程序


BOOL CCommonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetWindowText(m_sWindowTitle);
	SetDlgItemText(IDC_STATIC_COMMON_HELPTEXT, m_sHelpTitle);

	if (!m_bShowP1) {
		GetDlgItem(IDC_EDIT_COMMON_P1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COMMON_P1_TEXT)->ShowWindow(SW_HIDE);
	}

	if (!m_bShowP2) {
		GetDlgItem(IDC_EDIT_COMMON_P2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COMMON_P2_TEXT)->ShowWindow(SW_HIDE);
	}
	if (!m_bShowP3) {
		GetDlgItem(IDC_EDIT_COMMON_P3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COMMON_P3_TEXT)->ShowWindow(SW_HIDE);
	}
	if (!m_bShowP4) {
		GetDlgItem(IDC_EDIT_COMMON_P4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COMMON_P4_TEXT)->ShowWindow(SW_HIDE);
	}

 
	 
	//默认值
	CString defaultP1;
	defaultP1.Format(_T("%f"), m_P1);
	GetDlgItem(IDC_EDIT_COMMON_P1)->SetWindowText(defaultP1);

	CString defaultP2;
	defaultP2.Format(_T("%f"), m_P2);
	GetDlgItem(IDC_EDIT_COMMON_P2)->SetWindowText(defaultP2);

	CString defaultP3;
	defaultP3.Format(_T("%f"), m_P3);
	GetDlgItem(IDC_EDIT_COMMON_P3)->SetWindowText(defaultP3);

	CString defaultP4;
	defaultP4 = m_P4;
	GetDlgItem(IDC_EDIT_COMMON_P4)->SetWindowText(defaultP4);

	//设置位置
	if (!m_bShowP1 && !m_bShowP2 && !m_bShowP3) {
		CRect rect1, rect2;
		GetDlgItem(IDC_EDIT_COMMON_P1)->GetWindowRect(&rect1);
		GetDlgItem(IDC_STATIC_COMMON_P1_TEXT)->GetWindowRect(&rect2);
		rect1.right += 50;
		rect2.bottom += 50;
		rect2.left += 50;
		GetDlgItem(IDC_EDIT_COMMON_P4)->MoveWindow(rect1); //将P4控件位置移到P1控件处
		GetDlgItem(IDC_STATIC_COMMON_P4_TEXT)->MoveWindow(rect2);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
