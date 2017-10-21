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
