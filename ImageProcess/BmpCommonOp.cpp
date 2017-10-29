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




/*************************************************************************
*
* Function:  RGB2Gray ()
*
* Description:   彩色图转为灰度图
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::RGB2Gray(BYTE*Image) {

}


/*************************************************************************
*
* Function:  Normalized ()
*
* Description:   像素归一化到[0 ,255]   线性拉伸  RGB三个通道
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	int min = 65535, max = 0;
	int min_r = 65535, min_g = 65535, min_b = 65535, max_r = 0, max_g = 0, max_b = 0;
	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			//8bit BMP
			if (BitCount == 8) {
				int postion = j*LineByte + i;
				max = Image[postion] > max ? Image[postion] : max;
				min = Image[postion] < min ? Image[postion] : min;
			}
			//24bit BMP
			if (BitCount == 24) {
				int postion = j*LineByte + i * 3;
				max_r = Image[postion] > max_r ? Image[postion] : max_r;
				min_r = Image[postion] < min_r ? Image[postion] : min_r;
				max_g = Image[postion + 1] > max_g ? Image[postion + 1] : max_g;
				min_g = Image[postion + 1] < min_g ? Image[postion + 1] : min_g;
				max_b = Image[postion + 2] > max_b ? Image[postion + 2] : max_b;
				min_b = Image[postion + 2] < min_b ? Image[postion + 2] : min_b;
			}

		}
	}

	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			//8bit BMP
			if (BitCount == 8) {
				int postion = j*LineByte + i;
				DstImage[postion] = (double(Image[postion] - min) * 255 / (max - min)) + 0.5; //四舍五入
			}
			//24bit BMP
			if (BitCount == 24) {
				int postion = j*LineByte + i * 3;
				DstImage[postion] = (double(Image[postion] - min_r) * 255 / (max_r - min_r)) + 0.5; //四舍五入
				DstImage[postion + 1] = (double(Image[postion + 1] - min_g) * 255 / (max_g - min_g)) + 0.5; //四舍五入
				DstImage[postion + 2] = (double(Image[postion + 2] - min_b) * 255 / (max_b - min_b)) + 0.5; //四舍五入
			}

		}
	}
}



/*************************************************************************
*
* Function:  ShowBmpImage ()
*
* Description:   显示图像
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::ShowBmpImage(CDC *cdc, BYTE* Image,  int Position_x, int Position_y,  int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

 
	for (int j = 0; j < ImageHeight; j++) {
		for (int i = 0; i < ImageWidth; i++) {
			//8bit BMP
			if (BitCount == 8) {
				int postion = j*LineByte + i;
				cdc->SetPixel(Position_x +i, Position_y+ImageHeight- j, RGB(Image[postion] , Image[postion], Image[postion]) );
			}
			//24bit BMP
			if (BitCount == 24) {
				int postion = j*LineByte + i * 3;
				cdc->SetPixel(Position_x+i, Position_y+ImageHeight-j, RGB(Image[postion+2], Image[postion+1], Image[postion])); //BGR  我其实一直以RGB顺序存储 稍微改动一下顺序既可 暂时不想改动前面代码
			}
		}
	}

 
}




/*************************************************************************
*
* Function:  WriteTextOnScreen ()
*
* Description:   写字符串
*
* Input: Image 图像数据   ImageSize图像像素大小 ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void BmpCommonOp::WriteTextOnScreen(CDC *pDC,int Position_x, int Position_y) {
 
	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
		return;

	CBitmap *pbmpOld = NULL;
	//设置字体信息
	CFont font;
	font.CreateFont(20, 20, 0, 0, 200, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Times New Roman"));
	dcBmp.SetTextColor(RGB(255, 0, 0));

	dcBmp.SelectObject(&font); //将字体属性选入DC
	dcBmp.SetBkMode(TRANSPARENT); //背景透明
	dcBmp.TextOut(Position_x, Position_y, _T("sss"), 3);
	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
}






