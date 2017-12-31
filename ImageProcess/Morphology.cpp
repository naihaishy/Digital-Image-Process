#include "stdafx.h"
#include "Morphology.h"


Morphology::Morphology()
{
}


Morphology::~Morphology()
{
}



/*************************************************************************
*
* Function:   Erosion()
*
* Description: 腐蚀
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Morphology::Erosion(double * Image, double * DstImage, double *SE, int SeWidth, int SeHeight, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
	int a = (SeWidth - 1) / 2;
	int b = (SeHeight - 1) / 2;
	memcpy(DstImage, Image, sizeof(double)*ImageSize);

	for (int j = b; j < ImageHeight - b; j++) {
		for (int i = a; i < ImageWidth - a; i++) {
			int position = j * LineByte + i * BitCount / 8;//当前操作像素 与核心对其
			if (Image[position] == 255) { //中心点
				//当前点是前景 需要处理
				for (int m = -b; m < b + 1; m++) {
					for (int n = -a; n < a + 1; n++) {
						int surroundPosition = (j + m) * LineByte + (i + n) * BitCount / 8; //周围点位置
						if (SE[(m + b) * SeWidth + (n + a)] == 255) {
							if (Image[surroundPosition] == 0) {
								DstImage[position] = 0;
								DstImage[position + 1] = 0;
								DstImage[position + 2] = 0;
							}
							
						}

					}
				}
			}
		}
	}
}




/*************************************************************************
*
* Function:   Dilation()
*
* Description: 膨胀
*
* Input:  SE 结构元  SeWidth SeWidth 
*
* Returns:
*
************************************************************************/
void Morphology::Dilation(double * Image, double * DstImage, double *SE, int SeWidth, int SeHeight, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
 
	int a = (SeWidth - 1) / 2;
	int b = (SeHeight - 1) / 2;
	//memset(DstImage, 0, sizeof(double)*ImageSize);

	for (int j = b; j < ImageHeight - b; j++) {
		for (int i = a; i < ImageWidth -a ; i++) {
			int position = j * LineByte + i * BitCount / 8;//当前操作像素 与核心对其
			if (Image[position] == 255) {
				//当前点是前景 需要处理
				for (int m = -b; m < b + 1; m++) {
					for (int n = -a; n < a + 1; n++) {
						 
						int surroundPosition = (j + m) * LineByte + (i + n) * BitCount / 8; //周围点位置
						if (SE[(m+b) * SeWidth + (n+a)] == 255) {
							DstImage[surroundPosition] = 255;
							DstImage[surroundPosition + 1] = 255;
							DstImage[surroundPosition + 2] = 255;
						}

					}
				}
			}
		}
	}
 


}
