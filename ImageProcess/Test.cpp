#include "stdafx.h"
#include "Test.h"
#include "Common.h"

Test::Test()
{
}


Test::~Test()
{
}


//数字的识别
void Test::DigitPredict() {
	//查找Images/digits目录下所有图像
	CString szFileNameDir = _T("images\\digits\\");
	CString szFileName = szFileNameDir + "*.bmp"; //搜索目标为目录下的所有bmp文件
	WIN32_FIND_DATA findData;
	HANDLE hFindFile = ::FindFirstFile(szFileName, &findData);
	if (hFindFile != INVALID_HANDLE_VALUE){
		do	{
			// 名称为“.”的目录代表本目录，名称为“..”的目录代表上一层目录
			if (findData.cFileName[0] == '.')
				continue;

			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){// 找到的不是目录而是文件
				CString strFileName = szFileNameDir;//路径
				strFileName += findData.cFileName;//文件名

				//TRACE(L"%s\r\n", strFileName);
				//上传图像
				Common common;
				//CString filename = _T("picture.bmp");
				CString serverHost = _T("doc.zhfsky.com");
				CString requestUrl = _T("/api/python/digit/index.php");
				common.UploadByPost(strFileName, serverHost, requestUrl);//得到预测的数字
				Sleep(500);
				
				
			}

		} while (::FindNextFile(hFindFile, &findData));
		::FindClose(hFindFile);
	}


	

	//得到预测的数字

	

}
 
