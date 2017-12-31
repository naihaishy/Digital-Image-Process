#pragma once

#include "stdafx.h"
#include "Segment.h"






Segment::Segment()
{
}


Segment::~Segment()
{
}



/*************************************************************************
*
* Function:   EdgeDetection()
*
* Description: 边缘检测
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Segment::EdgeDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Detector, int Smooth, double Threshold, double Threshold2=0) {
	switch (Detector) {
		case EDGE_DETECTOR_ROBERT:
			break;
		case EDGE_DETECTOR_PREWITT:
			break;
		case EDGE_DETECTOR_SOBEL:
			SobelDetection(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Smooth, Threshold);
			break;
		case EDGE_DETECTOR_LOG:
			break;
		case EDGE_DETECTOR_DOG:
			break;
		case EDGE_DETECTOR_CANNY:
			CannyDetection(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Smooth, Threshold, Threshold2);
			break;

	}
}






/*************************************************************************
*
* Function:   RobertDetection()
*
* Description: 获取梯度的方向(角度)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Segment::RobertDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	//定义mask
	 
}


/*************************************************************************
*
* Function:   PrewittDetection()
*
* Description: 获取梯度的方向(角度)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/


/*************************************************************************
*
* Function:   SobelDetection()
*
* Description: 获取梯度的方向(角度)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
* Smooth 使用何种滤波器进行噪声处理
* Returns:
*
************************************************************************/
void Segment::SobelDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Smooth, double Threshold) {
	
	//初始化
	BmpCommonOp bmpcommonop;

	double * GrayImage = new double[ImageSize];//灰度图

	double * EdgeOutImageX = new double[ImageSize];//X梯度
	double * EdgeOutImageY = new double[ImageSize];//Y梯度
	double * EdgeOutImage = new double[ImageSize];//梯度幅值
	double * EdgeAngle= new double[ImageSize];//梯度方向
 
	
	//定义mask
	int MaskX[] = { -1,-2,-1,  0,0,0 ,  1,2,1 };//3x3 sobel mask
	int MaskY[] = { -1,0,1,  -2,0,2,  -1,0,1 };


	//灰度化
	if (BitCount == 24)
		bmpcommonop.RGB2Gray(Image, GrayImage, ImageWidth, ImageHeight, BitCount, LineByte);
	else
		memcpy(GrayImage, Image, sizeof(double)*ImageSize);

	//噪声处理
	switch (Smooth) {
		case SMOOTH_MEAN:
			bmpcommonop.MeanFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//均值滤波
			break;
		case SMOOTH_GAUSSIAN:
			bmpcommonop.GaussFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//均值滤波
			break;
		case SMOOTH_MEDIAN:

			break;
		default:
			break;//默认不进行平滑处理
	}

	//梯度计算
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageX, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskX, 3, 3, false);
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageY, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskY, 3, 3, false);

	//梯度幅值图像
	for (int i = 0; i < ImageSize; ++i) {
		EdgeOutImage[i] = abs(EdgeOutImageX[i]) + abs(EdgeOutImageY[i]);
	}

	//梯度方向
	GetEdgeAngle(EdgeOutImageX, EdgeOutImageY, EdgeAngle, ImageSize);

	//阈值
	//局部阈值 与全局阈值处理
	double maxE = *max_element(EdgeOutImage, EdgeOutImage + ImageSize);//最大梯度
	if (Threshold<=1.0) {
		//比例阈值 梯度最大值的比例
		for (int i = 0; i < ImageSize; ++i) {
			if (EdgeOutImage[i] <maxE*Threshold)
				DstImage[i] = 0;
			else
				DstImage[i] = 255;
		}
	}
	else {
		//固定阈值
		for (int i = 0; i < ImageSize; ++i) {
			if (EdgeOutImage[i] <Threshold)
				DstImage[i] = 0;
			else
				DstImage[i] = 255;
		}
	}



	//内存释放
	delete[] GrayImage;
	delete[] EdgeOutImageX;
	delete[] EdgeOutImageY;
	delete[] EdgeOutImage;

}


/*************************************************************************
*
* Function:   LoGDetection()
*
* Description: 获取梯度的方向(角度)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/



/*************************************************************************
*
* Function:   DoGDetection()
*
* Description: 获取梯度的方向(角度)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/



/*************************************************************************
*
* Function:   CannyDetection()
*
* Description: 获取梯度的方向(角度)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Segment::CannyDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Smooth, double LowThreshold, double HighThreshold) {

	//初始化
	BmpCommonOp bmpcommonop;

	//内存分配
	double * GrayImage = new double[ImageSize];//灰度图

	double * EdgeOutImageX = new double[ImageSize];//X梯度
	double * EdgeOutImageY = new double[ImageSize];//Y梯度
	double * EdgeOutImage = new double[ImageSize];//梯度幅值
	double * EdgeAngle = new double[ImageSize];//梯度角度
	//double * EdgeDirection= new double[ImageSize];//梯度基本方向 

	//定义mask
	int MaskX[] = { -1,-2,-1,  0,0,0 ,  1,2,1 };//3x3 sobel mask
	int MaskY[] = { -1,0,1,  -2,0,2,  -1,0,1 };


	//灰度化
	if (BitCount == 24) {
		bmpcommonop.RGB2Gray(Image, GrayImage, ImageWidth, ImageHeight, BitCount, LineByte);
	}
	else {
		memcpy(GrayImage, Image, sizeof(double)*ImageSize);
	}
	


	//噪声处理
	switch (Smooth) {
	case SMOOTH_MEAN:
		bmpcommonop.MeanFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//均值滤波
		break;
	case SMOOTH_GAUSSIAN:
		bmpcommonop.GaussFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//高斯滤波
		break;
	case SMOOTH_MEDIAN:

		break;
	default:
		bmpcommonop.GaussFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//高斯滤波
		break;//默认高斯滤波
	}

	//梯度计算 卷积
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageX, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskX, 3, 3, false);
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageY, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskY, 3, 3, false);

	//梯度幅值图像
	for (int i = 0; i < ImageSize; ++i) {
		EdgeOutImage[i] = abs(EdgeOutImageX[i]) + abs(EdgeOutImageY[i]);
	}

	//梯度方向
	GetEdgeAngle(EdgeOutImageX, EdgeOutImageY, EdgeAngle, ImageSize);
	//非最大抑制
	GetNearestDirection(EdgeAngle, EdgeAngle, ImageSize);//基本方向
	NotMaxSuppression(EdgeOutImage, EdgeOutImage, EdgeAngle, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte);//对梯度幅值图像进行非极大抑制

	//双阈值处理与连接边缘
	DoubleThreshold(EdgeOutImage, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, LowThreshold, HighThreshold);

	//内存释放
	delete[] GrayImage;
	delete[] EdgeOutImageX;
	delete[] EdgeOutImageY;
	delete[] EdgeOutImage;
	delete[] EdgeAngle;

}



/*************************************************************************
*
* Function:   getEdgeAngle()
*
* Description: 获取梯度的方向(角度)
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Segment::GetEdgeAngle(double *ImageX, double *ImageY, double *Angle, int ImageSize) {

	double x, y;
	for (int i = 0; i<ImageSize; ++i) {
		x = ImageX[i];
		y = ImageY[i];
		if (!(x == 0.0&&y == 0.0)) {
			double angle = atan2(y, x)*180.0 / PI;
			if (angle<0.0)
				angle += 360.0;
			Angle[i] = angle;
		}
		else
			Angle[i] = -1.0;
	}

}



/*************************************************************************
*
* Function:   GetNearestDirection()
*
* Description: 获取梯度方向最近的基本边缘方向 
*
* Input:  
*	Edge 梯度方向数据(注意这里是0~360 书上是-180~180) 水平 -45 垂直 +45 => 1.0 2.0 3.0 4.0 
*	ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Segment::GetNearestDirection(double* Edge, double* DstEdge, int ImageSize) {
	double angle = 0.0;
	for (int i = 0; i<ImageSize; i++) {
		angle = Edge[i];
		if (angle< 22.5 && angle>= 0)//水平边缘
			DstEdge[i] = 1.0;
		else if (angle<67.5 && angle >= 22.5)//-45
			DstEdge[i] = 2.0;
		else if (angle<112.5 && angle >= 67.5) //垂直边缘
			DstEdge[i] = 3.0;
		else if (angle<157.5 && angle >= 112.5)//+45
			DstEdge[i] = 4.0;
		else if (angle<202.5 && angle >= 157.5)//水平边缘
			DstEdge[i] = 1.0;
		else if (angle<247.5 && angle >= 202.5)//-45
			DstEdge[i] = 2.0;
		else if (angle<292.5 && angle >= 247.5)//垂直边缘
			DstEdge[i] = 3.0;
		else if (angle<337.5 && angle >= 292.5)//+45
			DstEdge[i] = 4.0;
		else if(angle < 360 && angle >= 337.5)//水平边缘
			DstEdge[i] = 1.0;
		else if (angle == -1.0)//无效的角度
			DstEdge[i] = -1.0;
	}
}



/*************************************************************************
*
* Function:   NotMaxSuppression()
*
* Description: 非极大抑制
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*	Edge基本方向数组
*
* Returns:
*
************************************************************************/
void Segment::NotMaxSuppression(double* Image, double* DstImage, double* Edge, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
	memcpy(DstImage, Image, sizeof(double)*ImageSize);
	//int wSize = 3;//设置窗口大小为3x3 即8邻域 
	for (int j = 1; j < ImageHeight-1; j++) {//边界的1个像素不处理
		for (int i = 1; i < ImageWidth-1; i++) {
			int position = j * LineByte + i * BitCount/8;//当前处理像素中心点 即p5 arr[5]
			int surroundPosition;//8邻域像素点位置

			double *arr = new double[9];//存放窗口像素值
			memset(arr, 0, sizeof(double)*9);//初始化为0
			int k = 0;
			for (int m = -1; m < 2; ++m) {
				for (int n = -1; n < 2; ++n) {
					surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8; //周围点位置
					arr[k] = *(Image + surroundPosition);
					k++;
				}
			}//获取周围点像素数组完毕
			 
			switch(int(Edge[position])){
				case 1://水平
					if (arr[5] >= arr[4] && arr[5] >= arr[6])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
						 
					break;
				case 2://-45
					if (arr[5] >= arr[3] && arr[5] >= arr[7])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
					break;
				case 3://垂直
					if (arr[5] >= arr[2] && arr[5] >= arr[8])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
					break;
				case 4://+45
					if (arr[5] >= arr[1] && arr[5] >= arr[9])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
					break;
				default:
					break;

			}

		}
	}

}



/*************************************************************************
*
* Function:   DoubleThreshold()
*
* Description: 双阈值处理
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Segment::DoubleThreshold(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double LowThreshold, double HighThreshold) {
	
	memcpy(DstImage, Image, sizeof(double)*ImageSize);//源拷贝到目标图像

	//双阈值简单处理
	for (int i = 0; i < ImageSize;i++) {
		if (Image[i] < LowThreshold)
			DstImage[i] = 0;
		if(Image[i] > HighThreshold)
			DstImage[i] = 255;//强像素点
	}

	//中间 弱像素点
	for (int j = 1; j < ImageHeight - 1; j++) {//边界的1个像素不处理
		for (int i = 1; i < ImageWidth - 1; i++) {
			int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点 即p5 arr[5]

			//当前已经是255或0 直接退出该层循环
			if ( (DstImage[position] == 255) || (DstImage[position] == 0) ){
				continue;
			}
				

			int surroundPosition;//8邻域像素点位置

			double *arr = new double[9];//存放8邻域像素值
			memset(arr, 0, sizeof(double) * 9);//初始化为0
			int k = 0;
			for (int m = -1; m < 2; m++) {
				for (int n = -1; n < 2; n++) {
					surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8 ; //周围点位置
					arr[k] = *(DstImage + surroundPosition);
					k++;
				}
			}//获取周围点像素数组完毕

			double maxE = *max_element(arr, arr + 9);//邻域中最大像素

			if (maxE == 255) {
				for (int kk = 0; kk < BitCount / 8; kk++) {
					DstImage[position + kk] = 255;
				}
					
			}
			else {
				for (int kk = 0; kk < BitCount / 8; kk++) {
					DstImage[position + kk] = 0;
				}	
			}
				
		}
	}
 
}









/*************************************************************************
*
* Function:   SlopeAdjust()
*
* Description: 角度校正
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Segment::SlopeAdjust(double *Image, double *DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
}



/*************************************************************************
*
* Function:   RectSeg()
*
* Description: 矩形框的分割 
*
* Input:  Image 图像数据 RectPoints点的向量信息
*
* Returns: double* 分割后得到的矩形框
*
************************************************************************/
double* Segment::RectSeg(double *Image, vector<CPoint> rectPoints, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
	 
	int minX = min(rectPoints[0].x, rectPoints[1].x) + 5;
	int maxX = max(rectPoints[2].x, rectPoints[3].x) - 5;
	int minY = min(rectPoints[0].y, rectPoints[1].y) + 5;
	int maxY = max(rectPoints[2].y, rectPoints[3].y) - 5;

	int digImWidth = (maxX - minX);
	int digImHeight = (maxY - minY);
	int digImLineByte = (digImWidth*BitCount + 31) / 32 * 4;
	int digImSize = digImLineByte * digImHeight;
	//内存分配
	double * digOnlyImage = new double[digImSize];
	//初始化
	for (int i = 0;i < digImSize;i++) {
		digOnlyImage[i] = 0;
	}

	for (size_t j = minY, jj = 0; j < maxY, jj<digImHeight; j++, jj++) {
		for (size_t i = minX, ii = 0; i < maxX, ii<digImWidth; i++, ii++) {
			int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点
			int positionDig = jj * digImLineByte + ii * BitCount / 8;//当前处理像素中心点
			for (int k = 0;k < BitCount / 8;k++) {
				digOnlyImage[positionDig + k] = Image[position + k];//从原始图像中截取
			}
		}
	}

	//更新成员变量信息
	m_RectSegWidth = digImWidth;
	m_RectSegHeight = digImHeight;
	m_RectSegLineByte = digImLineByte;
	m_RectSegSize = digImSize;
	//文件头和信息头的更新
	m_RectSegbfh = BitmapFileHeader;
	m_RectSegbih = BitmapInfoHeader;
	m_RectSegbfh.bfSize = BitmapFileHeader.bfOffBits + digImSize;
	m_RectSegbih.biWidth = digImWidth;
	m_RectSegbih.biHeight = digImHeight;
	m_RectSegbih.biSizeImage = digImSize;
 

	return digOnlyImage;
}



/*************************************************************************
*
* Function:   DigitalSegPosition()
*
* Description: 数字切割位置查找 
*
* Input:  Image 输入得到的矩形框内的数字图像(二值化过后的)数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns: vector<CPoint>point 各个数字的起始位置 
*
************************************************************************/
vector<CPoint> Segment::DigitalSegPosition(double *Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	int *Arr = new int[ImageWidth];
	memset(Arr, 0 ,sizeof(int)* ImageWidth);

	//向x轴投影
	int biasy = 10;
	for (int i = 0; i < ImageWidth; i++) {
		for (int j = biasy; j < ImageHeight- biasy; j++) {
			int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点
			//B单通道
			if (Image[position] == 255) {
				Arr[i] += 1;
			}
		}
	}

	//根据间隔找到各个数字的起始位置(横坐标)
	int biasx = 100;//去除前面mm字母的影响
	int start = 0;
	int end = 0;
	bool flag = false;
	vector<CPoint> point;//x=start y=end
	for (int i = biasx; i < ImageWidth; i++) {
		int maxheight = 0;
		if (!flag && Arr[i] > 10) {//数字区域
			//看看
			int *temarr = new int[ImageHeight];
			
			for (int kk = ImageHeight-5;kk>0;kk--) {
				int position = kk * LineByte + i * BitCount / 8;
				if (Image[position] == 255) {
					maxheight = kk;//该数字的高度
					break;
				}	
			}
			if (maxheight > 30) {//我们假设高度大于20的确实是数字  否则是噪声
				flag = true;
				start = i;
			}
		}
		else if (Arr[i] <= 5 && flag) {//间隔区域 
			flag = false;
			end = i;
			if (end - start < 20 && maxheight < 20)//高度和宽度均非常小 则是点 或者噪声  舍去
				continue;
			point.push_back(CPoint(start, end));
		}
	}

	return point;

}

/*************************************************************************
*
* Function:   DigitalSeg()
*
* Description: 数字分割
*
* Input:  Image 输入得到的矩形框内的数字图像(二值化过后的)数据
*
* Returns: 无 直接输出图像到本地文件
*
************************************************************************/
void Segment::DigitalSeg(double *Image, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

 
	//各个数字的起始位置
	vector<CPoint> digSegPoints = DigitalSegPosition(Image, ImageWidth, ImageHeight, BitCount, LineByte);
	int testsize = ImageHeight * LineByte;
	//对图像进行切割
	int biasy = 0;
	int digHeight = 160;//假设数字均为 160 高度

	int digbaisx = 5;//向前偏置
	int digbiasy = 5;//向后偏置

	for (int k = 0;k < digSegPoints.size();k++) {
		//偏置处理
		/*digSegPoints[k].y += digbiasy;
		digSegPoints[k].x -= digbaisx;*/

		//分配内存
		int width = digSegPoints[k].y - digSegPoints[k].x;
		int height = digHeight;
		int lineByte = (width* BitCount + 31) / 32 * 4;
		int imageSize = lineByte * height;
		BYTE *ImageSeg = new BYTE[imageSize];
		memset(ImageSeg, 0, imageSize);

		for (size_t i = digSegPoints[k].x, ii = 0; i < digSegPoints[k].y, ii<width; i++, ii++) {//x
			for (size_t j = 0, jj = 0; j < height, jj<height; j++, jj++) {//y
				
				int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点
				int positionDig = jj * lineByte + ii * BitCount / 8;//当前数字
				if (position < ImageHeight*LineByte) {
					for (int kk = 0;kk < BitCount / 8;kk++) {
						ImageSeg[positionDig + kk] = Image[position];//从矩形框图像中截取各个数字
					}
				}
				
			}
			
		}


		//将BMP图像数据写入文件
		BmpCommonOp bmpcommonop;
		CString TempFileName;
		CreateDirectory(_T("images\\digits"), NULL);
		TempFileName.Format(_T("images/digits/picture_%d.bmp"), k);
		USES_CONVERSION;
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(TempFileName);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, BitmapFileHeader, BitmapInfoHeader, colorTable, ImageSeg, imageSize, width, height);

	}

}

