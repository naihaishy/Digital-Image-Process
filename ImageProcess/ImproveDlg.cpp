// ImproveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "ImproveDlg.h"
#include "afxdialogex.h"


// CImproveDlg 对话框

IMPLEMENT_DYNAMIC(CImproveDlg, CDialogEx)

CImproveDlg::CImproveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMPROVE, pParent)
	, m_bImproveYes(FALSE)
 
{

}

CImproveDlg::~CImproveDlg()
{
}

void CImproveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_IMPROVE_YES, m_bImproveYes);
}


BEGIN_MESSAGE_MAP(CImproveDlg, CDialogEx)
	ON_COMMAND(ID_USER_LOGIN, &CImproveDlg::OnUserLogin)
END_MESSAGE_MAP()


// CImproveDlg 消息处理程序


BOOL CImproveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString config;
	GetPrivateProfileString(_T("Setting"), _T("Improve"), CString("NULL"), config.GetBuffer(MAX_PATH), MAX_PATH, _T("./config.ini") );

	if (config == _T("yes") ) {
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_YES))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_NO))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_NO))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_YES))->SetCheck(FALSE);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CImproveDlg::OnUserLogin()
{
	// TODO: 在此添加命令处理程序代码
}
