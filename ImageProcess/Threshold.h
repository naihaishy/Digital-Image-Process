#pragma once


#define THRESHOLDING_BASIC_GLOBAL 1
#define THRESHOLDING_OTSU 2
#define THRESHOLDING_LOCAL 3
#define THRESHOLDING_MULTI 4

class Threshold
{
public:
	Threshold();
	virtual ~Threshold();

	void BaseThresholding(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Type, double *Args);
	



private:	

	double BasicGlobalThreshold(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double DetaT);
	
	//double OTSUThreshold(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double DetaT);

	double OTSUThreshold(double * Image, double * DstImage, int ImageSize);

	void LocalThreshold(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double *Args);

	double GetHistMean(int Start, int End, int * Hist);

	int GetHistMax(int * Hist);

	int GetHistMin(int * Hist);
};

