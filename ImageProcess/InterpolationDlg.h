#pragma once


// CInterpolationDlg 对话框

class CInterpolationDlg : public CDialog
{
	DECLARE_DYNAMIC(CInterpolationDlg)

public:
	CInterpolationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInterpolationDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INTERPOLATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 宽度
	int m_nWidth;
	// 高度
	int m_nHeight;

	
};
