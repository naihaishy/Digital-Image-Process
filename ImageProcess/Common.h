#pragma once
class Common
{
public:
	Common();
	~Common();

	int findIndexofArr(int ar[], int n, int element);

	void InsertSort(int array[], int n);//插入排序
	int GetMedian(int array[], int n);// 获取数据的中位数
	void CStringToArray(CString string, float *arr);//CString转换为数组
	float * SplitString(CString str, CString split);
	//void NormalDistribution();//正态分布

	void GetGaussianKernel(double ** gaus, const int size, const double sigma);

	void GetConfig();//获取软件配置信息
	void GetHttpBody(CString Host, CString Url, BYTE *Buffer);

	void LogToFile(double * Input, int Size);

	void UploadFile(CString strFileName, CString strServerUrl, CString strServerUploadFile);

	void UploadByPost(CString strFileName, CString strServerUrl, CString strServerUploadFile);

	CString MakeRequestHeaders(CString & strBoundary);

	CString MakePreFileData(CString & strBoundary, CString & strFileName);

	CString MakePostFileData(CString & strBoundary);



	 


 
};

