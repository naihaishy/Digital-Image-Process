#pragma once


// CImproveDlg 对话框

class CImproveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImproveDlg)

public:
	CImproveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CImproveDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPROVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
 
	BOOL m_bImproveYes;
	virtual BOOL OnInitDialog();
	afx_msg void OnUserLogin();
};
