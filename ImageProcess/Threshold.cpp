#include "stdafx.h"
#include "Threshold.h"
#include <algorithm>

Threshold::Threshold()
{
}


Threshold::~Threshold()
{
}


 
/*************************************************************************
*
* Function:   Segment()
*
* Description: 基于阈值的图像分割
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns: double T 返回阈值
*
************************************************************************/
void Threshold::BaseThresholding(double *Image, double *DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Type, double *Args) {
	double threshold;
	//通过不同方法获取阈值
	switch (Type) {
	case THRESHOLDING_BASIC_GLOBAL:
		threshold = BasicGlobalThreshold(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Args[0]);
		break;
	case THRESHOLDING_OTSU:
		threshold = OTSUThreshold(Image, DstImage, ImageSize);
		break;
	case THRESHOLDING_LOCAL:
		LocalThreshold(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Args);
		break;
	case THRESHOLDING_MULTI:
		break;

	}

	if (Type == THRESHOLDING_LOCAL) {
		return;
	}

	//图像分割处理 全局阈值
	for (int i = 0; i < ImageSize; i++) {
		if (Image[i] > threshold)
			DstImage[i] = 255;
		else
			DstImage[i] = 0;
	}

}


/*************************************************************************
*
* Function:   BasicGlobalThreshold()
*
* Description: 迭代均值算法(即书上的基本全局阈值处理)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns: double T 返回阈值
*
************************************************************************/
double Threshold::BasicGlobalThreshold(double *Image, double *DstImage,int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double DetaT) {

	//初始化
	int *histogram = new int[256];
	memset(histogram, 0, sizeof(int)*256);

	//直方图灰度级统计
	for (int i = 0; i < ImageSize; i++) {
		int pixel = Image[i];
		histogram[pixel]++; //当前灰度级+1
	}

	//寻找最大最小灰度级
	int histMin = GetHistMin(histogram);
	int histMax = GetHistMax(histogram);
	
	//迭代计算阈值T
	double thresholdOld = (histMin + histMax) / 2.0; //初始一个T
	double thresholdNew = histMax;
	double deta  = thresholdNew - thresholdOld;
	double mean1, mean2;
	while( abs(deta) >= DetaT ) {
		thresholdOld = thresholdNew;
		mean1 = GetHistMean(histMin, (int)thresholdOld, histogram); //小于T得灰度
		mean2 = GetHistMean((int)thresholdOld, histMax + 1, histogram);//大于等于T的灰度
		thresholdNew = (mean1 + mean2) / 2.0;
		deta = thresholdNew - thresholdOld;
	}
	//内存释放
	delete[] histogram;
	return thresholdNew;

}



/*************************************************************************
*
* Function:   IterativeThreshold()
*
* Description: 迭代均值算法(书上的基本全局阈值处理)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns: double T 返回阈值
*
************************************************************************/
double Threshold::OTSUThreshold(double *Image, double *DstImage, int ImageSize) {


	//初始化
	double *histogram = new double[256];
	memset(histogram, 0, sizeof(double) * 256);
 

	//直方图灰度级统计 数目
	for (int i = 0; i < ImageSize; i++) {
		int pixel = Image[i];
		histogram[pixel]++; //当前灰度级+1
	}
	//直方图灰度级统计 概率 
	for (int i = 0; i < 256; i++) {
		histogram[i] = (double(histogram[i]) / ImageSize);
	}

	//贝叶斯 计算阈值
	double maxDeta = -1.0;
	double maxDetaLocation = 0.0;
	double mG = 0.0;

	for (int i = 0; i<256; i++) {
		mG += i * histogram[i];
	}

	for (int i = 0; i<256; i++) {
		double p1 = 0.0;
		double m1 = 0.0;
		double deta = 0.0;
		for (int j = 0; j <= i; j++) {
			p1 += histogram[j];
			m1 += j * histogram[j];
		}
		deta = p1 * (m1 - mG)*(m1 - mG) / (1 - p1);
		if (deta>maxDeta) {
			maxDetaLocation = i;
			maxDeta = deta;
		}
	}


	//内存释放
	delete[] histogram;


	return maxDetaLocation;
 
 
	

 

}

/*************************************************************************
*
* Function:   LocalThreshold()
*
* Description: 局部阈值
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns: double T 返回阈值
*
************************************************************************/
void Threshold::LocalThreshold(double *Image, double *DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double *Args) {
	//初始化
	//输入参数
	int m = Args[0];//窗口大小
	double meanPara = Args[1];//均值
	double stdPara = Args[2];//标准差


	int a = (m - 1) / 2; 


	//处理
	for (int j = a; j < ImageHeight - a; j++) {
		for (int i = a; i < ImageWidth -a ; i++) {
			int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点
			int surroundPosition;//8邻域像素点位置
			double tempMean = 0; //局部均值
			double tempDeviation = 0;//局部标准差

			for (int m = -a; m < a + 1; ++m) {
				for (int n = -a; n < a + 1; ++n) {
					surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8; //周围点位置 
					int pixel = *(Image + surroundPosition);
					tempMean += pixel;
				}
			}//获取周围点像素数组完毕
			tempMean = (double)tempMean / (m * m);//局部均值

			//for (int m = -a; m < a + 1; ++m) {
			//	for (int n = -a; n < a + 1; ++n) {
			//		surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8; //周围点位置 
			//		int pixel = *(Image + surroundPosition);
			//		tempDeviation += (pixel - tempMean)*(pixel - tempMean);
			//	}
			//}//获取周围点像素数组完毕
			//tempDeviation = sqrt( (double)tempDeviation / (m * m) );//局部标准差

			//均值
			if (Image[position]>tempMean*meanPara) {
				DstImage[position] = 255.0;
				DstImage[position+1] = 255.0;
				DstImage[position+2] = 255.0;
			}
			else {
				DstImage[position] = 0.0;
				DstImage[position + 1] = 0;
				DstImage[position + 2] = 0;
			}

		}
	}

}



/*************************************************************************
*
* Function:   GetHistMean()
*
* Description: 计算部分直方图的均值 灰度范围 [start, end) 左闭右开
*
* Input:  
*
* Returns:
*
************************************************************************/
double Threshold::GetHistMean(int Start, int End, int *Hist) {
	int count = 0;
	double value = 0;
	for (int i = Start; i < End; i++) {
		count += Hist[i];	//该灰度范围内的像素总数
		value += (double)Hist[i] * i;//该灰度范围内得像素值和
	}
	return value / (double)count;
}

int Threshold::GetHistMin(int *Hist) {
	for (int i = 0; i <= 255; i++) {
		if (Hist[i] != 0)
			return i;
	}
	return -1;
}
int Threshold::GetHistMax(int *Hist) {
	for (int i = 255; i >= 0; i--) {
		if (Hist[i] != 0)
			return i;
	}
	return -1;
}
