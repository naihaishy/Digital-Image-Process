#pragma once


// CHistogramDlg 对话框

class CHistogramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDlg)

public:
	CHistogramDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHistogramDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:


	int * HistogramColor;
	

	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
