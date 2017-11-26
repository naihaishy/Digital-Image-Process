#pragma once


// CCommonDlg 对话框

class CCommonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommonDlg)

public:
	CCommonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommonDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COMMON_PARA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	//成员变量
	double m_P1;
	double m_P2;
	double m_P3;
	CString m_P4;

	CString m_P1Text;
	CString m_P2Text;
	CString m_P3Text;
	CString m_P4Text;

	CString m_sWindowTitle;
	CString m_sHelpTitle;

	bool m_bShowP1;
	bool m_bShowP2;
	bool m_bShowP3;
	bool m_bShowP4;



	//成员函数
 

	
	virtual BOOL OnInitDialog();
 
};
