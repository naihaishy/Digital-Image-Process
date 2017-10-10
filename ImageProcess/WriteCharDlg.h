#pragma once


// CWriteCharDlg 对话框

class CWriteCharDlg : public CDialog
{
	DECLARE_DYNAMIC(CWriteCharDlg)

public:
	CWriteCharDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWriteCharDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WRITECHAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 字符
	CString m_wCharacter;
	int m_xPosition;
	int m_yPosition;
};
