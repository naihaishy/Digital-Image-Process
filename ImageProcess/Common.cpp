#include "stdafx.h"
#include "Common.h"
#include <afxinet.h> //Http

Common::Common()
{
}


Common::~Common()
{
}

int Common::findIndexofArr(int ar[], int n, int element)//查找元素并返回位置下标,find(数组，长度，元素)  
{
	int i = 0;
	int index = -1;//原始下标，没找到元素返回-1  
	for (i = 0; i <n; i++)
	{
		if (element == ar[i])
		{
			index = i;//记录元素下标  
		}
	}
	return index;//返回下标  
}

/*************************************************************************
* Function:   InsertSort()
*
* Description:    插入排序
*
* Input: 
*
* Returns:  从大到小排序好的数据
************************************************************************/
void Common::InsertSort(int a[], int n) {
	for (int i = 1; i<n; i++) {
		if (a[i] < a[i - 1]) {     //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入  
			int j = i - 1;   //表中最后一个数据
			int x = a[i];        //复制为哨兵，即存储待排序元素  
			a[i] = a[i - 1];           //先后移一个元素 (因为a[i]就是X，所以不怕丢失) 
			while (j >= 0 && x < a[j]) {  //查找在有序表的插入位置  (遍历表)
				a[j + 1] = a[j];
				j--;         //元素后移  
			}
			a[j + 1] = x;      //插入到正确位置  
		}
	}
}



/*************************************************************************
* Function:   GetMedian()
*
* Description:    获取中位数
*
* Input:	 
*
* Returns:  
************************************************************************/
int Common::GetMedian(int arr[], int n) 
{
	int median;
	InsertSort(arr, n);//arr已经排序完成
	if (n%2==1) {//奇数个
		median = arr[(n+1) / 2];
	}
	else {//偶数个
		median = (int) (arr[n / 2] + arr[n/2 -1]) /2;
	}
	return median;
	
}



/*************************************************************************
* Function:   CStringToArray()
*
* Description:    CString转换为数组
*
* Input:
*
* Returns:
************************************************************************/
void Common::CStringToArray(CString string, float *arr) {
	//USES_CONVERSION;
	 


	/*for (int i = 0; i < string.GetLength(); i++) {
		while (string.GetAt(i) != _T(",") )  {

		}
	}*/
	 
}



/*************************************************************************
* Function:   SplitString()
*
* Description:    分割CString为数组
*
* Input:
*
* Returns:
************************************************************************/
float * Common::SplitString(CString str, CString split)
{
	int iSubStrs;
	int iPos = 0; //分割符位置
	int iNums = 0; //分割符的总数
	CString strTemp = str;
	CString strRight;
	USES_CONVERSION;

	//先计算子字符串的数量
	while (iPos != -1)
	{
		iPos = strTemp.Find(split); //不匹配的话返回 - 1; 索引以0 开始
		if (iPos == -1)
		{
			break;
		}
		strRight = strTemp.Mid(iPos + 1);
		strTemp = strRight;
		iNums++; //子字符串的数量
	}


	
	//子字符串数组
	iSubStrs = iNums + 1; //子串的数量 = 分割符数量 + 1
	float* pStrSplit;
	pStrSplit = new float[iSubStrs];
	strTemp = str;
	CString strLeft;


	if (iNums == 0) //没有找到分割符
	{
		//子字符串数就是字符串本身
		iSubStrs = 1;
		LPCSTR tempstrTemp = (LPCSTR)T2A(strTemp);
		pStrSplit[0] = atof(tempstrTemp);
		//return NULL;
	}

	for (int i = 0; i < iNums; i++)
	{
		iPos = strTemp.Find(split);
		//左子串
		strLeft = strTemp.Left(iPos);
		//右子串
		strRight = strTemp.Mid(iPos + 1);
		strTemp = strRight;
		LPCSTR tempstrLeft = (LPCSTR)T2A(strLeft);
		pStrSplit[i] = atof(tempstrLeft);
	}
	LPCSTR tempstrTemp = (LPCSTR)T2A(strTemp);
	pStrSplit[iNums] = atof(tempstrTemp);
	return pStrSplit;
}



/*************************************************************************
* Function:   GetGaussianKernel()
*
* Description:    获取软件配置信息
*
* Input:
*
* Returns:
************************************************************************/
void Common::GetGaussianKernel(double **gaus, const int size, const double sigma){
	const double PI = 4.0*atan(1.0); //圆周率π赋值  
	 
	return;
}



/*************************************************************************
* Function:   GetConfig()
*
* Description:    获取软件配置信息
*
* Input:
*
* Returns:   
************************************************************************/
void Common::GetConfig() {

}



/*************************************************************************
* Function:   SetConfig()
*
* Description:    获取软件配置信息
*
* Input:
*
* Returns:
************************************************************************/
//void Common::SetConfig(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString) {
//	CFileFind finder;   //查找是否存在ini文件
//	BOOL ifFind = finder.FindFile(_T("config.ini"));
//	CString configIni = _T("config.ini");
//	//
//	if (!ifFind)	{//不存在，则生成一个新的默认设置的ini文件 
//		WritePrivateProfileStringW(_T("xwreg"), _T("IP"), _T("10.210.0.9"), configIni);
// 
//	}
//	else {
//		CString strObject;
//		 
//		WritePrivateProfileString(_T("xwreg"), _T("IP"), strObject, _T("d:\\qzze.ini"));
//	}
//
//
//
//}



/*************************************************************************
* Function:   GetHttpBody()
*
* Description:    获取HTTP请求
*
* Input:
*
* Returns:
************************************************************************/
void Common::GetHttpBody(CString requestHost, CString requestUrl, BYTE *Buffer) {
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
		pFile->Read((void *)Buffer, sizeof(Buffer));
	}
	else {
		CString errText;
		errText.Format(L"POST出错，错误码：%d", dwRet);
		AfxMessageBox(errText);
	}
		
	session.Close();
	pFile->Close();
	delete pFile;
}

void Common::LogToFile(double * Input, int Size) {
  
   
	//CFile file(_T("log.txt"), CFile::modeCreate | CFile::modeWrite);
	//for (int i = 0; i < polarWidth * polarHeight; i++) {
	//	CString aa;
	//	aa.Format(_T("%f \t"), houghAccAry[i]);
	//	file.Write(aa, sizeof(CString));
	//}
	//// 关闭文件   
	//file.Close();

 }



 
/*************************************************************************
* Function:   UploadFile()
*
* Description:    HTTP上传文件
*
* Input:
*
* Returns:
************************************************************************/

void Common::UploadByPost(CString strFileName, CString  strServerUrl, CString strServerUploadFile)
{

	DWORD dwTotalRequestLength;
	DWORD dwChunkLength;
	DWORD dwReadLength;
	DWORD dwResponseLength;
	CHttpFile* pHTTP = NULL;

	dwChunkLength = 64 * 1024;
	void* pBuffer = malloc(dwChunkLength);
	CFile file;

	if (!file.Open(strFileName.GetBuffer(),
		CFile::modeRead | CFile::shareDenyWrite))
	{
		return;
	}

	CInternetSession session(_T("sendFile"));
	CHttpConnection *connection = NULL;

	try
	{
		//Create the multi-part form data that goes before and after the actual file upload.

		CString strHTTPBoundary = _T("----WebKitFormBoundarytcFcFiMKaoCRdCof");
		CString strPreFileData = MakePreFileData(strHTTPBoundary, file.GetFileName());
		CString strPostFileData = MakePostFileData(strHTTPBoundary);
		CString strRequestHeaders = MakeRequestHeaders(strHTTPBoundary);
		dwTotalRequestLength = strPreFileData.GetLength() + strPostFileData.GetLength() + file.GetLength();

		connection = session.GetHttpConnection(/*L"www.YOURSITE.com"*/strServerUrl.GetBuffer(), NULL, INTERNET_DEFAULT_HTTP_PORT);

		pHTTP = connection->OpenRequest(CHttpConnection::HTTP_VERB_POST, strServerUploadFile.GetBuffer());//_T("/YOUURL/submit_file.pl"));
		pHTTP->AddRequestHeaders(strRequestHeaders);
		pHTTP->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE);

		//Write out the headers and the form variables
		//pHTTP->Write((LPSTR)(LPCSTR)strPreFileData.GetBuffer(), strPreFileData.GetLength());
		pHTTP->Write((LPSTR)(LPCSTR)CW2A(strPreFileData.GetBuffer()), strPreFileData.GetLength());

		//upload the file.

		dwReadLength = -1;
		int length = file.GetLength(); //used to calculate percentage complete.
		while (0 != dwReadLength)
		{
			dwReadLength = file.Read(pBuffer, dwChunkLength);
			if (0 != dwReadLength)
			{
				pHTTP->Write(pBuffer, dwReadLength);
			}
		}

		file.Close();

		//Finish the upload.
		//pHTTP->Write((LPSTR)(LPCSTR)strPostFileData.GetBuffer(), strPostFileData.GetLength());
		pHTTP->Write((LPSTR)(LPCSTR)CW2A(strPostFileData.GetBuffer()), strPostFileData.GetLength());
		pHTTP->EndRequest(HSR_SYNC);


		//get the response from the server.
		LPSTR szResponse;
		CString strResponse;
		dwResponseLength = pHTTP->GetLength();
		while (0 != dwResponseLength)
		{
			szResponse = (LPSTR)malloc(dwResponseLength + 1);
			szResponse[dwResponseLength] = '\0';
			pHTTP->Read(szResponse, dwResponseLength);
			strResponse += szResponse;
			free(szResponse);
			dwResponseLength = pHTTP->GetLength();
		}

		TRACE(L"%s", strResponse.GetBuffer());

		//将Response写入文件中
		CStdioFile resultFile(_T("images/result.txt"), CFile::modeCreate | CFile::modeWrite|CFile::modeNoTruncate);//
		resultFile.SeekToEnd();
		resultFile.WriteString(strResponse + _T("\r\n") );
		resultFile.Close();// 关闭文件 
		AfxMessageBox(strResponse);

		//close everything up.
		pHTTP->Close();
		connection->Close();
		session.Close();
	}
	catch (CInternetException* e)
	{
		TRACE(L"error: %d \n", e->m_dwError);
	}
	catch (CFileException* e)
	{
		TRACE(L"error: %d \n", e->m_cause);
	}
	catch (...)
	{
		TRACE(L" unexpected error");
	}

}


CString Common::MakeRequestHeaders(CString& strBoundary)
{
	CString strFormat;
	CString strData;
	strFormat = _T("Content-Type: multipart/form-data; boundary=%s\r\n");
	strFormat += _T("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36\r\n");
	strFormat += _T("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n");
	strFormat += _T("Accept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\n");
	strData.Format(strFormat, strBoundary);
	return strData;
}

CString Common::MakePreFileData(CString& strBoundary, CString& strFileName)
{
	CString strFormat;
	CString strData;

	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"file\"; filename=\"%s\"");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Type: text/plain");

	strFormat += _T("\r\n");
	strFormat += _T(" XXXXX ");
	strFormat += _T("\r\n\r\n");

	strData.Format(strFormat, strBoundary,/* m_Name, strBoundary,*/ strFileName);

	return strData;
}

CString Common::MakePostFileData(CString& strBoundary)
{

	CString strFormat;
	CString strData;

	strFormat = _T("\r\n");
	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"submit\"");
	strFormat += _T("\r\n\r\n");
	strFormat += _T("Submit");
	strFormat += _T("\r\n");
	strFormat += _T("--%s--");
	strFormat += _T("\r\n");

	strData.Format(strFormat, strBoundary, strBoundary);

	return strData;

}

 