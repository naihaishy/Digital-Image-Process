// HighBoostFilterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "HighBoostFilterDlg.h"
#include "afxdialogex.h"


// CHighBoostFilterDlg 对话框

IMPLEMENT_DYNAMIC(CHighBoostFilterDlg, CDialogEx)

CHighBoostFilterDlg::CHighBoostFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HIGHBOOST_FILTER, pParent)
	, m_nHighBoostK(_T("1, 2, 3, 4, 4.5, 5, 7, 9"))
{

}

CHighBoostFilterDlg::~CHighBoostFilterDlg()
{
}

void CHighBoostFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HIGHBOOST_K, m_nHighBoostK);
}


BEGIN_MESSAGE_MAP(CHighBoostFilterDlg, CDialogEx)
END_MESSAGE_MAP()


// CHighBoostFilterDlg 消息处理程序
