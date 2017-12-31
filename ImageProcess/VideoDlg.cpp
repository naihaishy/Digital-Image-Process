// VideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "VideoDlg.h"
#include "afxdialogex.h"


// CVideoDlg 对话框

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIDEO, pParent)
{

}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX1, m_player);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoDlg 消息处理程序


BOOL CVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_player.put_URL(m_vidoeUrl);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
