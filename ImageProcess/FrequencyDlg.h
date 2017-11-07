#pragma once


// CFrequencyDlg 对话框

class CFrequencyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFrequencyDlg)

public:
	CFrequencyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFrequencyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FREQUENCY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	//成员变量
	
	int m_nCutoffFre;// 截止频率
	CString m_sWindowTitle;
	CString m_sHelpTitle;

	//成员函数
	virtual BOOL OnInitDialog();
};
