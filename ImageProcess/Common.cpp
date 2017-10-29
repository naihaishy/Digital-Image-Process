#include "stdafx.h"
#include "Common.h"


Common::Common()
{
}


Common::~Common()
{
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
		if (a[i] < a[i - 1]) {               //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入  
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