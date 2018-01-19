// VideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tracking.h"
#include "VideoDlg.h"
#include "afxdialogex.h"


// CVideoDlg 对话框

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIDEO, pParent)
{

	EnableAutomation();

}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX1, m_player);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVideoDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IVideoDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {67300A47-852E-4F72-AE96-94CB23680D99}
static const IID IID_IVideoDlg =
{ 0x67300A47, 0x852E, 0x4F72, { 0xAE, 0x96, 0x94, 0xCB, 0x23, 0x68, 0xD, 0x99 } };

BEGIN_INTERFACE_MAP(CVideoDlg, CDialogEx)
	INTERFACE_PART(CVideoDlg, IID_IVideoDlg, Dispatch)
END_INTERFACE_MAP()


// CVideoDlg 消息处理程序


BOOL CVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_player.put_URL(m_vidoeUrl);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
