/*************************************************
Copyright:Naihai
Author: Naihai
Date:2017-10-8
Description:BMP文件的主要操作
**************************************************/


#pragma once
class BmpCommonOp :
	public CDocument
{
public:
	BmpCommonOp();
	~BmpCommonOp();


	//成员变量


	//成员函数

	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize);
	BYTE* AddPepperSaltNoise(BYTE * Image, double SNR, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void RGB2Gray(BYTE*Image);
	void Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte); //图像数据归一化
	void ShowBmpImage(CDC *cdc,BYTE* Image, int Position_x, int Position_y, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//显示BMP图像
	void WriteTextOnScreen(CDC *pDC, int Position_x, int Position_y);
};

