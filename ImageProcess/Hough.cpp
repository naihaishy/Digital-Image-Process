#include "stdafx.h"
#include "Hough.h"
#include <algorithm>

Hough::Hough()
{
}



Hough::~Hough()
{
}


void Hough::HoughLines(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int type) {
	memcpy(DstImage, Image, sizeof(double)*ImageSize);//源拷贝到目标图像



	//极坐标参数空间初始化
	int maxTheta = 90;  //Theta -90~+90
	int maxRho = sqrt(ImageWidth*ImageWidth + ImageHeight * ImageHeight) + 1;//对角线长度  -D D

	 //累加数组 横轴为角度theta  纵轴为半径rho
	int accArrWidth = maxTheta * 2;//180
	int accArrHeight = maxRho * 2;//2D
	int *houghAccAry = new int[accArrWidth * accArrHeight];// -90~90 -D ~D
	memset(houghAccAry, 0, sizeof(int)*accArrWidth * accArrHeight);

	int biasX = 50;//防止图像边界的影响
	int biasY = 50;

	//计算累加数组 Hough accumulator
	for (int j = biasY; j < ImageHeight - biasY; j++) {//y
		for (int i = biasX; i < ImageWidth - biasX; i++) {//x

			int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点										    
			if (Image[position] == 255) {//边缘	255为关注点
										 //遍历所有角度
				for (int k = 0;k < accArrWidth; k++) {//theta  0~180 => -90~ 90
					double radian = (k - 90) * PI / 180;//实际的弧度
					int rho = i * cos(radian) + j * sin(radian) + 0.5;//实际的极径
					int tempy = rho + accArrHeight / 2; //在数组存储时的位置y
					int tempx = k;//在数组中存储的位置 x
					houghAccAry[tempy * accArrWidth + k] += 1;
				}
			}
		}
	}


	/* 直线检测 寻找满足阈值的峰值点
	* 思路： 由于图像较为复杂 我们先检测较长的横线 再检测较短的垂线  使用vector存储满足阈值的theta rho参数组
	*/

	//长线检测 长线基本上是水平线 
	vector<ThetaRho> thetaRhoLong;
	int longLineLength = 280;
	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta 角度 0-180

			if (houghAccAry[j * accArrWidth + i] >= longLineLength) {
				double theta = (i - 90);//实际的角度
				int rho = j - accArrHeight / 2;//实际的极径
				if (abs(theta) <= 90 && abs(theta) >= 85) {//我们认为是水平线
					thetaRhoLong.push_back(ThetaRho(theta, rho));//存储
				}

			}
		}
	}

	//短线检测 短线基本上是垂直线 
	vector<ThetaRho> thetaRhoShort;
	int shortLineLength = 180;
	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta 角度 0-180
			if ((houghAccAry[j * accArrWidth + i] >= 140) && (houghAccAry[j * accArrWidth + i] < 180)) {
				double theta = (i - 90);//实际的角度
				int rho = j - accArrHeight / 2;//实际的极径
				if (abs(theta) <= 5) { //我们认为是垂直线
					thetaRhoShort.push_back(ThetaRho(theta, rho));//存储
				}
			}
		}
	}

	//直线简化 相近的直线均值化 归为一条直线 减少直线的数目
	MeanLine(thetaRhoLong, thetaRhoLong.size());
	MeanLine(thetaRhoShort, thetaRhoShort.size());


	/* 画线
	* 思路： 分为单独画线 和 合并画线 单独画线是为了下面寻找交点的方便
	*/
	//double * LineImage = new double[ImageSize];//仅有直线 水平+垂直 (红色) 不包含原信息
	double * longLineImage = new double[ImageSize];//仅有水平线 (红色) 不包含原信息
	double * shortLineImage = new double[ImageSize];//仅有垂直线 (红色) 不包含原信息
													//memset(LineImage, 0, sizeof(double)*ImageSize);
	memset(longLineImage, 0, sizeof(double)*ImageSize);
	memset(shortLineImage, 0, sizeof(double)*ImageSize);

	for (int i = 0;i < thetaRhoLong.size();i++) {
		DrawLine(longLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);//
	}

	for (int i = 0;i < thetaRhoShort.size();i++) {
		DrawLine(shortLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);//
	}

}

/*************************************************************************
*
* Function:   HoughLines()
*
* Description: 霍夫变换检测直线
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Hough::HoughLines(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	memcpy(DstImage, Image, sizeof(double)*ImageSize);//源拷贝到目标图像
	
	

	//极坐标参数空间初始化
	int maxTheta = 90;  //Theta -90~+90
	int maxRho = sqrt(ImageWidth*ImageWidth + ImageHeight * ImageHeight) + 1;//对角线长度  -D D
	
	//累加数组 横轴为角度theta  纵轴为半径rho
	int accArrWidth = maxTheta*2;//180
	int accArrHeight = maxRho*2;//2D
	int *houghAccAry = new int[accArrWidth * accArrHeight];// -90~90 -D ~D
	memset(houghAccAry, 0, sizeof(int)*accArrWidth * accArrHeight);

	

	//计算累加数组 Hough accumulator
	int biasX = 2;//防止图像边界的影响
	int biasY = 20;
	CalHoughAcc(Image, houghAccAry, accArrWidth, accArrHeight, ImageWidth, ImageHeight, BitCount, LineByte, biasX, biasY);



	/* 直线检测 寻找满足阈值的峰值点 
	 * 思路： 由于图像较为复杂 我们先检测较长的横线 再检测较短的垂线  使用vector存储满足阈值的theta rho参数组
	 */

	//确定检测的阈值 思路：最大值的某个比例
	int maxLineLength = *std::max_element(houghAccAry, houghAccAry + accArrWidth * accArrHeight);
	
	int maxLineLengthIndex = std::distance(houghAccAry, std::max_element(houghAccAry, houghAccAry + accArrWidth * accArrHeight));
	
	int maxLineRho = maxLineLengthIndex / 180;
	int maxLineTheta = maxLineLengthIndex % 180;
	if (abs(maxLineTheta) < 5) {//垂直线
		if (maxLineRho < ImageWidth*0.3) {//垂直线靠左边
			biasX = maxLineRho -5;//将左边的不考虑在内 重新计算累加数组
			biasX = max(biasX, 0);
			CalHoughAcc(Image, houghAccAry, accArrWidth, accArrHeight, ImageWidth, ImageHeight, BitCount, LineByte, biasX, biasY);
		}
	}
	else if (abs(maxLineTheta) > 85) {//水平线
		if (maxLineRho < ImageHeight*0.3) {//水平线靠下方
			biasY = maxLineRho - 5;//将左边的不考虑在内 重新计算累加数组
			biasY = max(biasY, 0);
			CalHoughAcc(Image, houghAccAry, accArrWidth, accArrHeight, ImageWidth, ImageHeight, BitCount, LineByte, biasX, biasY);
		}
	}


	//长线检测 长线基本上是水平线 
	vector<ThetaRho> thetaRhoLong;
	int longLineLength = maxLineLength*0.50;

 	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta 角度 0-180

			if (houghAccAry[j * accArrWidth + i] >= longLineLength) {
				double theta = (i - 90) ;//实际的角度
				int rho = j - accArrHeight / 2;//实际的极径
				if (abs(theta) <= 90 && abs(theta)>=85) {//我们认为是水平线
					thetaRhoLong.push_back( ThetaRho(theta, rho) );//存储
				}
				
			}
		}
	}

	//短线检测 短线基本上是垂直线 
	vector<ThetaRho> thetaRhoShort;
	int shortLineLength1 = 130;
	int shortLineLength2 = 160;

	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta 角度 0-180
			if ( (houghAccAry[j * accArrWidth + i] >= shortLineLength1) && (houghAccAry[j * accArrWidth + i] < shortLineLength2) ) {
				double theta = (i - 90);//实际的角度
				int rho = j - accArrHeight / 2;//实际的极径
				if (abs(theta)<=5) { //我们认为是垂直线
					if (abs(abs(rho) - ImageWidth / 2) > 180) { //这根垂线不跟图像中心靠的很近 否则不要这根线
						thetaRhoShort.push_back(ThetaRho(theta, rho));//存储
					}
					
				}
			}
		}
	}

	//直线简化 相近的直线均值化 归为一条直线 减少直线的数目
	MeanLine(thetaRhoLong, thetaRhoLong.size());
	MeanLine(thetaRhoShort, thetaRhoShort.size());

	 
	/* 画线 
	* 思路： 分为单独画线 和 合并画线 单独画线是为了下面寻找交点的方便 
	*/
	//double * LineImage = new double[ImageSize];//仅有直线 水平+垂直 (红色) 不包含原信息
	double * longLineImage = new double[ImageSize];//仅有水平线 (红色) 不包含原信息
	double * shortLineImage = new double[ImageSize];//仅有垂直线 (红色) 不包含原信息
	//memset(LineImage, 0, sizeof(double)*ImageSize);
	memset(longLineImage, 0, sizeof(double)*ImageSize);
	memset(shortLineImage, 0, sizeof(double)*ImageSize);

	for (int i = 0;i < thetaRhoLong.size();i++) {
		DrawLine(longLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);//
	}
	
	for (int i = 0;i < thetaRhoShort.size();i++) {
		DrawLine(shortLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);//
	}


		
	 

	//寻找距离数字最近的 矩形框的四个点
	SelectPoints(longLineImage, shortLineImage, m_vRectPoints, ImageWidth, ImageHeight, BitCount, LineByte);


}
 

/*************************************************************************
*
* Function:   CalHoughAcc()
*
* Description: 计算霍夫累加数组
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*
* Returns:
*
************************************************************************/
void Hough::CalHoughAcc(double* Image,int *houghAccAry, int accArrWidth, int accArrHeight, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int biasX, int biasY) {
	for (int j = biasY; j < ImageHeight - biasY; j++) {//y
		for (int i = biasX; i < ImageWidth - biasX; i++) {//x

			int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点										    
			if (Image[position] == 255) {//边缘	255为关注点
				//遍历所有角度
				for (int k = 0;k < accArrWidth; k++) {//theta  0~180 => -90~ 90
					double radian = (k - 90) * PI / 180;//实际的弧度
					int rho = i * cos(radian) + j * sin(radian) + 0.5;//实际的极径
					int tempy = rho + accArrHeight / 2; //在数组存储时的位置y
					int tempx = k;//在数组中存储的位置 x
					houghAccAry[tempy * accArrWidth + k] += 1;
				}
			}
		}
	}
}

/*************************************************************************
*
* Function:   GetRectPoints()
*
* Description: 获取矩形框的四个点信息
*
* Input:
*
* Returns: vector<CPoint> 
*
************************************************************************/
vector<CPoint> Hough::GetRectPoints() {
	return m_vRectPoints;
}



/*************************************************************************
*
* Function:   MeanLine()
*
* Description: 根据theat rho相似度进行直线的均值化 目的是减少相同直线的数目
*
* Input:
*
* Returns:
*
************************************************************************/
void Hough::MeanLine(vector<ThetaRho> &thetaRho, int size) {

	double delt = 10;
	for (int i = 0;i < size;i++) {
		double theta = thetaRho[i].theta;
		int rho = thetaRho[i].rho;

		if (theta == 0 && rho == 0)//无效参数 
			continue;//跳出该次循环

		int sumRho = rho;
		//遍历剩下的参数组 求rho的均值
		int k = 1;
		for (int j = 0;(j < size) && (j != i);j++) {
			if (abs(rho - thetaRho[j].rho) <= delt && abs(theta - thetaRho[j].theta) <= delt) {
				sumRho += thetaRho[j].rho;//求和
				thetaRho[j].rho = 0;//该组参数置0 删除
				thetaRho[j].theta = 0;
				k++;
			}
		}
		//均值
		int meanRho = double(sumRho) / k + 0.5;
		thetaRho[i].rho = meanRho;
	}

}



/*************************************************************************
*
* Function:   DrawLine()
*
* Description: 很据rho和theta画直线
*
* Input:  Image 图像数据  ImageWidth ImageHeight 图像宽高 BitCount图像位数 LineByte图像一行所占字节数
*	theta 实际角度 rho实际极径 
*
* Returns:
*
************************************************************************/
void Hough::DrawLine(double *Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double theta, int rho) {

	double radian = theta * PI / 180;//实际的弧度
	if (abs(rho) <= 0.5)
		return;
	if (theta == 0 ) {//垂直线
		int x = rho;//x
		for (int y = 0; y < ImageHeight; y++) {//y
			int position = y * LineByte + x * BitCount / 8;
			Image[position + 2] = 255;
		}
	}
	else if (abs(theta)<45) {//以y为遍历
		//根据y计算x
		for (int y = 0; y < ImageHeight; y++) {//y
			int x = (rho - y * sin(radian)) / cos(radian) + 0.5;//x
			int position = y * LineByte + x * BitCount / 8;
			if (x > 0 && x < ImageWidth) {
				Image[position + 2] = 255;
			}
		}
	}
	else if(abs(theta)>=45){//以x为遍历
		//根据x计算y
		for (int x = 0; x < ImageWidth; x++) {//x
			int y = (rho - x * cos(radian)) / sin(radian) + 0.5;//y
			int position = y * LineByte + x * BitCount / 8;
			if (y > 0 && y < ImageHeight) {
				Image[position + 2] = 255;
			}
		}
		
	}
}







/*************************************************************************
*
* Function:   SelectPoints()
*
* Description: 寻找距离数字最近的矩形框的四个点 
*
* Input:
*
* Returns: 距离数字最近的矩形框的四个点
*
************************************************************************/
void Hough::SelectPoints(double *longLineImage, double *shortLineImage, vector<CPoint> &rectPoints, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	vector<MyStructPoint> mypoint;//交点 水平线与垂线的交点
	//所有交点
	for (int j = 0; j < ImageHeight; j++) {//y
		for (int i = 0; i < ImageWidth; i++) {//x
			int position = j * LineByte + i * BitCount / 8;//当前处理像素中心点
			//R通道
			if (longLineImage[position + 2] == 255 && shortLineImage[position + 2] == 255) {//交点
				mypoint.push_back( MyStructPoint(CPoint(i,j), 0));
			}
		}
	}

	/* 寻找距离数字最近的矩形框的四个点
	 * 思路： 计算待选交点的均值 确定一个中心点 
	 *		 然后计算中心点到各个交点的距离 
	 *		 以中心点为中心将图像分为四个区块 
	 *       从四个区域中选择距离中心最近的点  
	 *       这4个点作为目标点
	 */

	//计算待选交点的均值
	int xSum = 0, ySum = 0;
	int xCenter = 0, yCenter = 0;
	int kkk = 0;
	for (size_t i = 0; i < mypoint.size(); i++)	{
		xSum += mypoint[i].point.x;
		ySum += mypoint[i].point.y;
		kkk++;
	}
	xCenter = xSum * 1.0 / kkk + 0.5;//中心点坐标
	yCenter = ySum * 1.0 / kkk + 0.5;
 
	//计算中心点到各个交点的距离  
	for (size_t i = 0; i < mypoint.size(); i++) {
		mypoint[i].distance =  (mypoint[i].point.x - xCenter)*(mypoint[i].point.x - xCenter) + (mypoint[i].point.y - yCenter)*(mypoint[i].point.y - yCenter);
	}

	//分块
	/*
	
	1  |  3
	-------
	2  |  4
	*/

	vector<MyStructPoint> mypointP1, mypointP2, mypointP3, mypointP4;
	for (size_t i = 0; i < mypoint.size(); i++) {
		if (mypoint[i].point.x < xCenter && mypoint[i].point.y >= yCenter)//1
			mypointP1.push_back(mypoint[i]);
		if (mypoint[i].point.x < xCenter && mypoint[i].point.y < yCenter)//2
			mypointP2.push_back(mypoint[i]);
		if (mypoint[i].point.x >= xCenter && mypoint[i].point.y >= yCenter)//3
			mypointP3.push_back(mypoint[i]);
		if (mypoint[i].point.x >= xCenter && mypoint[i].point.y < yCenter)//4
			mypointP4.push_back(mypoint[i]);
	}

	//对每个区域根据距离进行排序 从小到大
	InsertSort(mypointP1);
	InsertSort(mypointP2);
	InsertSort(mypointP3);
	InsertSort(mypointP4);

	//得到最终的四个点
	vector<CPoint> rectPointsC{ mypointP1[0].point , mypointP2[0].point, mypointP3[0].point, mypointP4[0].point};
	rectPoints.assign(rectPointsC.begin(), rectPointsC.end());
 
	
}


/*************************************************************************
*
* Function:   InsertSort()
*
* Description: 根据距离进行排序
*
* Input: vector<MyStructPoint> a
*
* Returns: 从小到大的点
*
************************************************************************/
void Hough::InsertSort(vector<MyStructPoint> &a) {
	int n = a.size();
	for (int i = 1; i<n; i++) {
		if (a[i].distance < a[i - 1].distance) { //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入  
			int j = i - 1;   //表中最后一个数据
			MyStructPoint x = a[i];        //复制为哨兵，即存储待排序元素  
			a[i] = a[i - 1];           //先后移一个元素 (因为a[i]就是X，所以不怕丢失) 
			while (j >= 0 && x.distance < a[j].distance) {  //查找在有序表的插入位置  (遍历表)
				a[j + 1] = a[j];
				j--;         //元素后移  
			}
			a[j + 1] = x;      //插入到正确位置
		}
	}
}



