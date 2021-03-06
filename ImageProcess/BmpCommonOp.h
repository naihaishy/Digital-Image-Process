/*************************************************
Copyright:Naihai
Author: Naihai
Date:2017-10-8
Description:BMP文件的主要操作
**************************************************/
#include "Fourier.h"
#include <complex>
#include <math.h>
#include <random>
using namespace std;

 
#pragma once
class BmpCommonOp :
	public CDocument
{
public:
	BmpCommonOp();
	~BmpCommonOp();


	//成员变量
	complex<double>* m_TimeDomain; //二维原图像时域复数数组
	complex<double>* m_TimeDomainB;
	complex<double>* m_TimeDomainG;
	complex<double>* m_TimeDomainR;
	complex<double>* m_FrequencyDomain; //二维原图像FFT变换得到的频域数组
	complex<double>* m_FrequencyDomainB;
	complex<double>* m_FrequencyDomainG;
	complex<double>* m_FrequencyDomainR;

	int m_nImageWidth;  //补0操作后新图像宽 
	int m_nImageHeight;//补0操作后新图像高
	int m_nLineByte;    //图像一行所占字节数  
	int m_nLineBytePer;//每个通道 图像一行所占字节数  
	int m_isExpanded; //是否执行了补0操作
	int m_nImageSize; //新图像大小 byte
	int m_nImageSizePer; //新图像大小 byte 每个通道
	int m_bFourierinit; //是否初始化过 1 yes 0no


	//成员函数

	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize);
	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize, int ImageWidth, int ImageHeight);
	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize, int Bitcount);
	BYTE* AddPepperSaltNoise(BYTE * Image, double Rate, int noiseChose, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//椒盐噪声
	void RGB2Gray(BYTE*Image, BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void RGB2Gray(double *Image, double* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	//void RGB2Gray8Bit(BYTE * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, BITMAPFILEHEADER & BitmapFileHeader, BITMAPINFOHEADER & BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, int ImageWidth, int ImageHeight, int BitCount);
	//BYTE * RGB24BitToGray8Bit(BYTE * Image, int ImageWidth, int ImageHeight);
	void RGB24BitToGray8Bit(BYTE * Image, BYTE * DstImage, int ImageWidth, int ImageHeight);
	void Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte); //图像数据归一化
	void ShowBmpImage(CDC *cdc,BYTE* Image, int Position_x, int Position_y, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//显示BMP图像
	void WriteTextOnScreen(CDC *pDC, int Position_x, int Position_y);
	
	void ImgFourierInit(int ImageWidth, int ImageHeight, int BitCount);
	void ImgFFT(BYTE* Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void ImgIFFT( BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void GetAmplitudespectrum(complex<double>  * src, BYTE * DstImage, int width, int height, int BitCount, int ShitFlag); //获取图像的频谱图 8bit
	void GetAmplitudespectrum(complex<double>  * srcB, complex<double>  * srcG, complex<double>  * srcR, BYTE * DstImage, int width, int height, int BitCount, int isReverse); //24bit
	void ImgFreTemplateFilter(BYTE* DstImage, double *filter, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//频谱模板滤波
	void ImgIdealPassFilter(BYTE* DstImage, int nFreq, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//理想滤波
	void ImgButterworthPassFilter(BYTE* DstImage, int nOrder,  int nFreq, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//布特沃斯滤波
	void ImgGaussianPassFilter(BYTE* DstImage, int Sigma, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//高斯滤波
	void ImgHomomorphicFilter(BYTE* Image, BYTE* DstImage, int Sigma, double c, double GammaH, double GammaL, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//同态滤波

	BYTE* GaussianNoise(BYTE * Image, double Rate, double mean, double viarance, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//高斯噪声

	void ContraharmonicMeanFilter(BYTE* Image, BYTE* DstImage, int m, int n, int  q, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//逆谐波均值滤波器

	void FilterEdgeProcess(BYTE* Image,BYTE* DstImage,int a,int b, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//滤波的边缘处理
	void TemplateFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int *mask, int m, int n, bool needWc); //模板滤波
	void MeanFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n);//均值滤波
	void MedianFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n);//中值滤波
	void GaussFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n);//高斯滤波
	
	
};

