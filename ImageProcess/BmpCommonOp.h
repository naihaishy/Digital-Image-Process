/*************************************************
Copyright:Naihai
Author: Naihai
Date:2017-10-8
Description:BMP文件的主要操作
**************************************************/
#include "Fourier.h"
#include <complex>
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
	BYTE* AddPepperSaltNoise(BYTE * Image, double SNR, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void RGB2Gray(BYTE*Image, BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte); //图像数据归一化
	void ShowBmpImage(CDC *cdc,BYTE* Image, int Position_x, int Position_y, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//显示BMP图像
	void WriteTextOnScreen(CDC *pDC, int Position_x, int Position_y);
	
	void ImgFourierInit(int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void ImgFFT(BYTE* Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void ImgIFFT( BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void GetAmplitudespectrum(complex<double>  * src, BYTE * DstImage, int width, int height, int BitCount, int ShitFlag); //获取图像的频谱图 8bit
	void GetAmplitudespectrum(complex<double>  * srcB, complex<double>  * srcG, complex<double>  * srcR, BYTE * DstImage, int width, int height, int BitCount, int isReverse); //24bit
	void ImgFreTemplateFilter(BYTE* DstImage, double *filter, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//频谱模板滤波
	void ImgIdealLowPassFilter(BYTE* DstImage, int nFreq, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//理想低通滤波
 
};

