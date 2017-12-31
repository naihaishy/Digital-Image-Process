#pragma once
#define PI 3.14159265358979323846

#include <vector>

using std::vector;

struct MyStructPoint
{
	CPoint point;
	int distance;
	//构造函数
	MyStructPoint(const CPoint &apoint, int distances) {
		point = apoint;
		distance = distances;
	}
};


struct ThetaRho
{
	double theta;//角度
	int rho;//极径
	//构造函数
	ThetaRho(double atheta, int arho) {
		theta = atheta;
		rho = arho;
	}
};


class Hough
{
public:
	Hough();
	
	virtual ~Hough();

	void HoughLines(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int type);

	//成员变量
	//int m_nBitCount;
	//int m_nLineByte;
	//int m_nImageSize;
	//int m_nImageWidth;
	//int m_nImageHeight;
	//int *houghAccAry;//累加数组
	//vector<ThetaRho> thetaRhoLong;//存储满足阈值的theta rho参数组
	//vector<ThetaRho> thetaRhoShort;
 

	vector<CPoint> m_vRectPoints;//距离数字最近的 矩形框的四个点


	//成员函数 


	void HoughLines(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void CalHoughAcc(double * Image, int * houghAccAry, int accArrWidth, int accArrHeight, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int biasX, int biasY);
	vector<CPoint> GetRectPoints();

	void MeanLine(vector<ThetaRho> &thetaRho, int size);
	void DrawLine(double * Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double theta, int rho);
	void SelectPoints(double * longLineImage, double * shortLineImage, vector<CPoint> &rectPoints, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void InsertSort(vector<MyStructPoint> &a);


private:

};

