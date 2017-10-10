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
* Returns:   成功返回0 失败返回 -1 非0
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
