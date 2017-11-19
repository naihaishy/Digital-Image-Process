#pragma once


// CUserDlg 对话框

class CUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//成员变量
	CDatabase m_dbfile;
	CString m_Email;
	CString m_Password;
	bool m_Userlogin;//是否已经登录
	CString m_Name;
	CString m_Ip;

	//成员函数
	virtual BOOL OnInitDialog();
	//bool UserLogin(CString email, CString password);//登录
	void UserCenter();//
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonRegister();
};
