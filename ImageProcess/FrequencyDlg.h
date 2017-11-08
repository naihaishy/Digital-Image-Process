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
	double m_dGammaH; //同态滤波GammaH
	double m_dGammaL; //同态滤波GammaL
	double m_dHomoC;
	int showGammaControls; //是否显示同态滤波的Gamma


	//成员函数
	virtual BOOL OnInitDialog();
	

	
};
