#include "stdafx.h"
#include "BmpCommonOp.h"


BmpCommonOp::BmpCommonOp()
{
}


BmpCommonOp::~BmpCommonOp()
{
}






/*************************************************************************
*
* Function:  WriteBmpDataToFile ()
*
* Description:   将BMP文件数据写入文件
*
* Input:  FileName 要写入文件的绝对路径和名称; bfh 文件头 bih 信息头 colorTable颜色表
*
* Returns:    
*
************************************************************************/

void BmpCommonOp::WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize) {

 
	FILE *fpw = NULL;

	fopen_s(&fpw, FileName, "wb+");

	//写入文件头
	fwrite(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fpw);
	//写入信息头
	fwrite(&BitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fpw);

	//写入颜色表
	if (BitmapInfoHeader.biBitCount == 8)  // 8bit BMP
	{
		if (BitmapInfoHeader.biClrUsed == 0) //如果该值为零,则有2的biBitCount次幂个元素
		{
			fwrite(colorTable, sizeof(RGBQUAD), 256, fpw);
		}
		else {
			fwrite(colorTable, sizeof(RGBQUAD), BitmapInfoHeader.biClrUsed, fpw);
		}
	}


	//写入位图像素数据
	fwrite(Image, ImageSize, 1, fpw);

	fclose(fpw); //关闭文件指针

	return ;
}



/*************************************************************************
*
* Function:  AddPepperSaltNoise ()
*
* Description:   增加椒盐噪声
*
* Input: Image 图像数据 SNR信噪比 ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数 
*
* Returns:    
*
************************************************************************/
BYTE* BmpCommonOp::AddPepperSaltNoise(BYTE * Image, double SNR, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	int noiseCount = ImageSize*(1 - SNR); //噪声总数
	BYTE *OutputImage = new BYTE[ImageSize];
	memcpy(OutputImage, Image, ImageSize);
	int x = 0, y=0;
	for (int i = 0; i < noiseCount; i++) {
		x =  rand() % ImageWidth; //X
		y = rand() % ImageHeight;//Y

		
		if (BitCount==8) {//8bit BMP
			if (rand() % 2 == 0) { //各有0.5的概率生成 椒(0)或者盐(255)
				*(OutputImage + y*LineByte + x) = 0;
			}
			else {
				*(OutputImage + y*LineByte + x) = 255;
			}
			
		}//end 8bit BMP

		if (BitCount == 24) {//8bit BMP
			if (rand() % 2 == 0) { //各有0.5的概率生成 椒(0)或者盐(255)
				*(OutputImage + y*LineByte + x*3) = 0;
				*(OutputImage + y*LineByte + x*3+1) = 0;
				*(OutputImage + y*LineByte + x*3+2) = 0;
			}
			else {
				*(OutputImage + y*LineByte + x * 3) = 255;
				*(OutputImage + y*LineByte + x * 3 + 1) = 255;
				*(OutputImage + y*LineByte + x * 3 + 2) = 255;
			}

		}//end 24bit BMP


	}

	return OutputImage;


}












