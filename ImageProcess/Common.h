#pragma once
class Common
{
public:
	Common();
	~Common();

	void InsertSort(int array[], int n);//插入排序
	int GetMedian(int array[], int n);// 获取数据的中位数
	void CStringToArray(CString string, float *arr);//CString转换为数组
	float * SplitString(CString str, CString split);


	void GetConfig();//获取软件配置信息
};

