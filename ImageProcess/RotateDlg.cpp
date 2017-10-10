// RotateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "RotateDlg.h"
#include "afxdialogex.h"


// CRotateDlg 对话框

IMPLEMENT_DYNAMIC(CRotateDlg, CDialog)

CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_ROTATE, pParent)
	, m_nRotateAngle(45)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROTATEANGLE, m_nRotateAngle);
	DDV_MinMaxDouble(pDX, m_nRotateAngle, 0, 360);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
END_MESSAGE_MAP()


// CRotateDlg 消息处理程序
