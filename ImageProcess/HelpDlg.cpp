// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialog)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_HELP, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	//ON_EN_CHANGE(IDC_MFCMASKEDEDIT1, &CHelpDlg::OnEnChangeMfcmaskededit1)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序


 
