// UserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include "Common.h"
#include <afxinet.h> //Http
#include "time.h"
 
#include <regex> 
 
// CUserDlg 对话框

IMPLEMENT_DYNAMIC(CUserDlg, CDialogEx)

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_USER_LOGIN, pParent)
	, m_Email(_T(""))
	, m_Password(_T(""))
{

}

CUserDlg::~CUserDlg()
{
	///断开数据库；连接
	if (m_dbfile.IsOpen()) {
		m_dbfile.Close();//

	}

}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER_LOGIIN_EM, m_Email);
	DDX_Text(pDX, IDC_EDIT_USER_LOGIIN_PA, m_Password);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CUserDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CUserDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CUserDlg 消息处理程序


BOOL CUserDlg::OnInitDialog()
{
	
	
	
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(_T("用户登录"));

	//连接数据库
	CString sConnect = _T("DSN= ;server =  ;PWD= ;UID= ;database =  ; port =  "); //mysql
	try {
		m_dbfile.Open(NULL, false, false, sConnect);
		//AfxMessageBox(_T("数据库连接成功!"));
	}
	catch (CDBException &e) { // 连接失败
		AfxMessageBox(_T("数据库连接失败!"));
		return false;
	}

	if (m_Userlogin) {
		UserCenter(); //已经登录  转到个人中心页面  
		OnCancel();//关闭模态对话框
	}
	
	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




//******************用户中心*****************//
void CUserDlg::UserCenter() {
	if (!m_Userlogin) return;

	CDialog*  Dlg = new CDialog;
	Dlg->Create(IDD_DIALOG_USER_CENTER);
	Dlg->SetWindowText(_T("个人中心"));
	Dlg->ShowWindow(SW_SHOW);
	//显示用户信息
	//SetDlgItemText(IDC_STATIC_USER_NAME, m_Name);
	//SetDlgItemText(IDC_STATIC_USER_EMAIL, m_Email);
 

}




//******************登录*****************//
void CUserDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);


	//密码加密md5 通过http发送get请求得到加密后字符串
	CString requestHost = _T("doc.zhfsky.com");
	CString requestUrl;
	requestUrl.Format(_T("/api/md5/?str=%s") , m_Password);
	char responseBody[32];
 
	
	//通过 http GET 协议
	CInternetSession session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

	CHttpConnection* pConnection = session.GetHttpConnection(requestHost, (INTERNET_PORT)80);
	CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, requestUrl);
	CString szHeaders = _T("Accept: text/plain, text/html, text/htm\r\n");
	pFile->AddRequestHeaders(szHeaders);//请求头
	pFile->SendRequest();//发送请求
	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);

	if (dwRet = HTTP_STATUS_OK) {
		pFile->Read((void *)responseBody, sizeof(responseBody));
	}
	else {
		CString errText;
		errText.Format(L"POST出错，错误码：%d", dwRet);
		AfxMessageBox(errText);
	}
	session.Close();
	pFile->Close();
	delete pFile;

	CString Password;
	for (int i = 0; i < 32;i++) {
		Password += responseBody[i];
	}
 
	//输入检查
	if (m_Email.IsEmpty()) {
		AfxMessageBox(_T("请输入邮箱!"), MB_OK, 0);
		return;
	}

	std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
	USES_CONVERSION;
	LPCSTR  Email_Str = (LPCSTR)T2A(m_Email);
	if (!std::regex_match(Email_Str, pattern)) {
		AfxMessageBox(_T("请输入合法的邮箱!"), MB_OK, 0);
		return;
	}

	if (m_Password.IsEmpty()){
		AfxMessageBox(_T("请输入密码!"), MB_OK, 0);
		return;
	}
	


	// 数据库查询操作
	if (m_dbfile.IsOpen()) {
		//构建CRecordset对象
		CRecordset recordSet(&m_dbfile);
		//SQL语句
		CString sqlStr;
		sqlStr.Format(_T("SELECT id, email , password FROM user WHERE email = '%s' AND password='%s'"), m_Email, Password);
		//AfxMessageBox(sqlStr);
		 
		//打开记录集
		bool  isExists = recordSet.Open(CRecordset::forwardOnly, sqlStr, CRecordset::readOnly);
		if (!recordSet.IsEOF() ) {
			//登录成功
			//AfxMessageBox(_T("登录成功!"));
			//读取用户信息
			//recordSet.MoveFirst();
			//recordSet.GetFieldValue(_T("name"), m_Name); 
			//recordSet.GetFieldValue(_T("ip"), m_Ip);
			m_Userlogin = 1;
			UserCenter();
			OnCancel();//关闭模态对话框
			//写入登录信息
			CString timeStr;
			timeStr.Format(_T("%d"), time(0));
			WritePrivateProfileString(_T("Information"), _T("Login"), _T("yes"), _T("./config.ini"));
			WritePrivateProfileString(_T("Information"), _T("LoginTime"), timeStr, _T("./config.ini"));

		}
		else {
			//登录失败
			AfxMessageBox(_T("账号或者密码错误!"));
		}


	}
	else {
		AfxMessageBox(_T("数据库未连接!"));
	}

}


void CUserDlg::OnBnClickedButtonRegister()
{
	// TODO: 在此添加控件通知处理程序代码
}
