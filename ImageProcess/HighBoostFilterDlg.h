#pragma once


// CHighBoostFilterDlg 对话框

class CHighBoostFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHighBoostFilterDlg)

public:
	CHighBoostFilterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHighBoostFilterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HIGHBOOST_FILTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// K值
	CString m_nHighBoostK;
};
