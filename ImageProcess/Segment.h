#pragma once
#include "BmpCommonOp.h"
#include "Common.h"

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <vector>
using std::vector;

#define PI 3.14159265358979323846

#define EDGE_DETECTOR_ROBERT 1
#define EDGE_DETECTOR_PREWITT 2
#define EDGE_DETECTOR_SOBEL 3
#define EDGE_DETECTOR_LOG 4
#define EDGE_DETECTOR_DOG 5
#define EDGE_DETECTOR_CANNY 6

#define SMOOTH_MEAN 11
#define SMOOTH_GAUSSIAN 12
#define SMOOTH_MEDIAN 13
 

class Segment
{
public:
	Segment();
	~Segment();

	void EdgeDetection(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Detector, int Smooth, double Threshold, double Threshold2);
	

	

	//成员变量

	//矩形分割部分
	int m_RectSegWidth;
	int m_RectSegHeight;
	int m_RectSegLineByte;
	int m_RectSegSize;
	BITMAPFILEHEADER m_RectSegbfh;
	BITMAPINFOHEADER m_RectSegbih;
 


	//成员函数


	//void EdgeDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Detector, int Smooth, double Threshold);
	void GetEdgeAngle(double * ImageX, double * ImageY, double * Angle, int ImageSize);
	 

	void SlopeAdjust(double * Image, double * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);

	double * RectSeg(double * Image, vector<CPoint> rectPoints, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, int ImageWidth, int ImageHeight, int BitCount, int LineByte);

	 

	vector<CPoint> DigitalSegPosition(double * Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte);

	void DigitalSeg(double * Image, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], int ImageWidth, int ImageHeight, int BitCount, int LineByte);

 

 
 

private:
	void RobertDetection(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);

	void SobelDetection(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Smooth, double Threshold);

	
	void CannyDetection(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Smooth, double LowThreshold, double HighThreshold);

	void GetNearestDirection(double * Edge, double * DstEdge, int ImageSize);

	 

	void NotMaxSuppression(double * Image, double * DstImage, double * Edge, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);

	void DoubleThreshold(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double LowThreshold, double HighThreshold);

 

};

