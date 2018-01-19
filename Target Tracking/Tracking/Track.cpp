#include "stdafx.h"
#include "Track.h"


#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

Track::Track()
{
}


Track::~Track()
{
}

/*************************************************************************
*
* Function:   PlayVideo()
*
* Description: 视频播放
*
* Input:
*
* Returns:
*
************************************************************************/
int Track::PlayVideo(CString filename){

	USES_CONVERSION;
	LPCSTR videopath = (LPCSTR)T2A(filename); //将CString转成const char*

	//读入视频
	VideoCapture capture(videopath);

	//循环显示每一帧
	while (1){
		Mat frame;//定义一个Mat变量，用于存储每一帧的图像
		capture >> frame;  //读取当前帧

		//若视频播放完成，退出循环
		if (frame.empty()){
			break;
		}

		imshow("视频播放", frame);//显示当前帧
		waitKey(30);  //延时30ms
	}

	return 0;
}




 
/*************************************************************************
*
* Function:   GSMDetection()
*
* Description: 混合高斯模型进行目标检测  
*
* Input:
*
* Returns:
*
************************************************************************/
void Track::GSMDetection(CString filename) {

	USES_CONVERSION;

	LPCSTR videopath = (LPCSTR)T2A(filename);


	VideoCapture capture(videopath);


	Mat image01, image02, imgdiff;

	while (true) {
		//隔两帧配准
		capture >> image01;

		if (image01.empty()) {
			break;
		}

		capture >> image02;
		capture >> image02;

		if (image02.empty()) {
			break;
		}

		//GaussianBlur(image02, image02, Size(3,3), 0);

		double time0 = static_cast<double>(getTickCount());//开始计时

		//灰度图转换  
		Mat image1, image2;
		cvtColor(image01, image1, CV_RGB2GRAY);
		cvtColor(image02, image2, CV_RGB2GRAY);

		//提取特征点    
		auto surfDetector = xfeatures2d::SURF::create(2500);// 海塞矩阵阈值，高一点速度会快些
		vector<KeyPoint> keyPoint1, keyPoint2;
		surfDetector->detect(image1, keyPoint1);
		surfDetector->detect(image2, keyPoint2);

		//特征点描述，为下边的特征点匹配做准备    
		auto SurfDescriptor = xfeatures2d::SurfDescriptorExtractor::create();
		Mat imageDesc1, imageDesc2;
		SurfDescriptor->compute(image1, keyPoint1, imageDesc1);
		SurfDescriptor->compute(image2, keyPoint2, imageDesc2);

		//获得匹配特征点，并提取最优配对     
		FlannBasedMatcher matcher;
		vector<DMatch> matchePoints;
		matcher.match(imageDesc1, imageDesc2, matchePoints, Mat());
		sort(matchePoints.begin(), matchePoints.end()); //特征点排序    

		//获取排在前N个的最优匹配特征点  
		vector<Point2f> imagePoints1, imagePoints2;
		for (int i = 0; i<(int)(matchePoints.size()*0.25); i++) {
			imagePoints1.push_back(keyPoint1[matchePoints[i].queryIdx].pt);
			imagePoints2.push_back(keyPoint2[matchePoints[i].trainIdx].pt);
		}

		//获取图像1到图像2的投影映射矩阵 尺寸为3*3  
		Mat homo = findHomography(imagePoints1, imagePoints2, CV_RANSAC);


		//图像配准  
		Mat imageTransform1, imgpeizhun, imgerzhi;
		warpPerspective(image01, imageTransform1, homo, Size(image02.cols, image02.rows));
		//imshow("经过透视矩阵变换后",imageTransform1);  

		absdiff(image02, imageTransform1, imgpeizhun);
		//imshow("配准diff", imgpeizhun);  

		threshold(imgpeizhun, imgerzhi, 50, 255.0, CV_THRESH_BINARY);
		//imshow("配准二值化", imgerzhi);

		//输出所需时间
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		cout << 1 / time0 << endl;

		Mat temp, image02temp;
		float m_BiLi = 0.9;

		image02temp = image02.clone();
		cvtColor(imgerzhi, temp, CV_RGB2GRAY);

		//检索连通域
		Mat se = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(temp, temp, MORPH_DILATE, se);

		vector<vector<Point>> contours;
		findContours(temp, contours, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		if (contours.size()<1) {
			continue;
		}

		for (int k = 0; k < contours.size(); k++) {
			Rect bomen = boundingRect(contours[k]);
			//删除比较小的检测
			if (bomen.height < 30 || bomen.width < 30) {
				continue;
			}

			//省略由于配准带来的边缘无效信息
			if (bomen.x > image02temp.cols * (1 - m_BiLi) && bomen.y > image02temp.rows * (1 - m_BiLi)
				&& bomen.x + bomen.width < image02temp.cols * m_BiLi && bomen.y + bomen.height < image02temp.rows * m_BiLi)
			{
				//初始化	 
				rectangle(image02temp, bomen, Scalar(255, 0, 0), 1, 8, 0);
			}

		}

		imshow("GSM运动目标检测", image02temp);
		waitKey(20);

		if (waitKey(1) == 27) {
			break;
		}
	}

}



/*************************************************************************
*
* Function:   FDiffDetection()
*
* Description: 帧间差目标检测
*
* Input:
*
* Returns:
*
************************************************************************/
void Track::FDiffDetection(CString filename) {

	USES_CONVERSION;
	LPCSTR videopath = (LPCSTR)T2A(filename);


	VideoCapture capture(videopath);

	if (!capture.isOpened()) {
		return;
	}
	double rate = capture.get(CV_CAP_PROP_FPS);//获取视频帧率
	int delay = 1000 / rate;
	Mat framepro, frame, dframe;
	Mat grayImage;
	bool flag = false;

	namedWindow("image");
 
	while (capture.read(frame)){
		if (false == flag){
			framepro = frame.clone();//将第一帧图像拷贝给framePro
			flag = true;
		}
		else{
			absdiff(frame, framepro, dframe);//帧间差分计算两幅图像各个通道的相对应元素的差的绝对值。
			framepro = frame.clone();//将当前帧拷贝给framepro
			threshold(dframe, dframe, 60, 255, CV_THRESH_BINARY);//阈值分割
			imshow("dframe", dframe);
			//寻找轮廓
			cvtColor(dframe, grayImage, CV_BGR2GRAY);
			vector<vector<Point>> contours;
			findContours(grayImage, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
			if (contours.size()<1) {
				continue;
			}


			for (int k = 0; k < contours.size(); k++) {
				Rect bomen = boundingRect(contours[k]);
				 
				if (bomen.width>20 && bomen.height>20) {
					rectangle(frame, bomen, Scalar(0, 0, 255), 2, 8, 0);
				}
				
	
			}

			imshow("image", frame);
			//imshow("test", dframe);
			waitKey(delay);
			int k = waitKey(1);
			if (k == 27) {

				break;
			}
		}
	}
	return;
	 
	
}





/*************************************************************************
*
* Function:   KCF()
*
* Description: KCF目标跟踪
*
* Input:
*
* Returns:
*
************************************************************************/
void Track::KCF(CString filename) {

	USES_CONVERSION;

	LPCSTR videopath = (LPCSTR)T2A(filename);
	 

	bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;

	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);
	VideoCapture video(videopath);

	if (!video.isOpened()) {
		AfxMessageBox(_T("无法打开视频文件"));
		return;
	}

	//直接跳到指定帧
	long nFrame = static_cast<long>(video.get(CV_CAP_PROP_FRAME_COUNT)); // 获取总帧数
	double position = 660;
	video.set(CV_CAP_PROP_POS_FRAMES, position);

	//读取第一帧
	Mat frame;
	video.read(frame);

	bool flag = false;
	int isfirst = true;
	//目标矩形区域
	Rect2d selectArea;

	int kk = 0;
	//循环处理视频的每一帧
	while (video.read(frame)){
		//开始计时 timer
		double timer = (double)getTickCount();
		if (!flag) {
			//没有检测到目标 不能进行跟踪 需要执行目标检测
			selectArea = FaceDetect(frame);

			if (!selectArea.empty()) {
				//该帧检测到要跟踪的目标 执行tracker初始化
				flag = true;
				tracker.init(selectArea, frame);
				rectangle(frame, selectArea, Scalar(0, 0, 255), 2, 1);//红色 画笔宽度为2 线型为1

			}
			else {
				//该帧仍然没有检测到要跟踪的目标 播放视频
				putText(frame, "no traget detected", Point(100, 120), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
				imshow("Tracking", frame);
				flag = false;
				//continue;
			}
		}
		else {
			//前面已经检测到了目标 继续执行跟踪
			//更新tracker
			//Rect2d roi = selectArea;
			selectArea = tracker.update(frame);//若返回false表明目标物体不在画面中

			if (!selectArea.empty()) {//检测到指定目标
				rectangle(frame, selectArea, Scalar(0, 0, 255), 2, 1);//红色 画笔宽度为2 线型为1
				kk = 0;
				//flag = true;
			}
			else {//没有检测到指定目标 目标离开了
				putText(frame, "no traget detected", Point(100, 120), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
				kk++;
				if (kk > 100) {
					//离开了100帧
					flag = false;
					kk = 0;
				}
				else {
					flag = true;
				}



			}

		}


	 
		//auto indec = video.get(CV_CAP_PROP_POS_FRAMES);

		//putText(frame, "Index : " + SSTR(int(indec)), Point(100, 170), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);
		
		//计算FPS（Frames per second）
		float fps = getTickFrequency() / ((double)getTickCount() - timer);

		//显示FPS信息
		putText(frame, "FPS : " + SSTR(int(fps)), Point(100, 70), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

		//显示其他辅助信息
		putText(frame, "KCF Tracker", Point(100, 30), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);
		putText(frame, "ESC to stop the programm and close windows manuall", Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);


		imshow("Tracking", frame);
		
		//ESC退出程序
		char c = (char)waitKey(40);
		if (c == 27) {
			break;
		}



	}




}





/*************************************************************************
*
* Function:   FaceDetect()
*
* Description: 人脸检测
*
* Input:
*
* Returns:
*
************************************************************************/
Rect Track::FaceDetect(Mat Image){

	//Mat Image = imread("22.jpg");
	 
	//resize(Image, Image, Size(Image.cols / 2, Image.rows / 2), 0, 0, INTER_LINEAR);
	Mat grayImage;
	vector<Rect> faces;

	CascadeClassifier faces_cascade;
	faces_cascade.load("haarcascade_frontalface_default.xml");

	cvtColor(Image, grayImage, CV_BGR2GRAY);
		
	faces_cascade.detectMultiScale(grayImage, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE| CV_HAAR_DO_CANNY_PRUNING, Size(15, 15));

	
	/*for (int i = 0;i < faces.size();i++) {

		rectangle(Image, faces[i], Scalar(0, 255, 0), 2, 8, 0);
	}
	imwrite("face.jpg", Image);
*/

	if (faces.size() < 1) {
		return Rect(0, 0, 0, 0);
	}
	else {
		return faces[0];
	}

	


}




/*************************************************************************
*
* Function:   Tracker()
*
* Description: 目标跟踪
*
* Input:
*
* Returns:
*
************************************************************************/
void Track::TragetTracker(CString filename, cv::String trackerType) {

	USES_CONVERSION;

	LPCSTR videopath = (LPCSTR)T2A(filename);

 // 

	// Create a tracker
	Ptr<Tracker> tracker;

 
	if (trackerType == "BOOSTING")
		tracker = TrackerBoosting::create();
	if (trackerType == "MIL")
		tracker = TrackerMIL::create();
	if (trackerType == "KCF")
		tracker = TrackerKCF::create();
	if (trackerType == "TLD")
		tracker = TrackerTLD::create();
	if (trackerType == "MEDIANFLOW")
		tracker = TrackerMedianFlow::create();
	if (trackerType == "GOTURN")
		tracker = TrackerGOTURN::create();
	if (trackerType == "MOSSE")
		tracker = TrackerMOSSE::create();
	 
 

	// Read video
	VideoCapture video(videopath);
	//get the fps
	double rate = video.get(CV_CAP_PROP_FPS);
	int delay = 1000 / rate;

	long nFrame = static_cast<long>(video.get(CV_CAP_PROP_FRAME_COUNT)); 
	double position = 600;
	video.set(CV_CAP_PROP_POS_FRAMES, position);

	// Exit if video is not opened
	if (!video.isOpened()){
		AfxMessageBox(_T("Could not read video file"));
		return ;
	}

	// Read first frame
	Mat frame;
	bool ok = video.read(frame);

	// Define initial boundibg box
	Rect2d bbox(287, 23, 86, 320);

	// Uncomment the line below to select a different bounding box
	bbox = selectROI(frame, false);

	// Display bounding box.
	rectangle(frame, bbox, Scalar(0, 0, 0), 2, 1);

	imshow("Tracking", frame);

	tracker->init(frame, bbox);

	while (video.read(frame)){

		// Start timer
		double timer = (double)getTickCount();

		// Update the tracking result
		bool ok = tracker->update(frame, bbox);

		// Calculate Frames per second (FPS)
		float fps = getTickFrequency() / ((double)getTickCount() - timer);


		if (ok)	{
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox, Scalar(0, 0, 255), 2, 1);
		}
		else{
			// Tracking failure detected.
			putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
		}

		// Display tracker type on frame
		putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 255, 0), 2);

		// Display FPS on frame
		putText(frame, "FPS : " + SSTR(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 255, 0), 2);

		// Display other info
		putText(frame, "ESC to stop the programm and close windows manually", Point(100, 70), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 255, 0), 2);
		// Display frame.
		imshow("Tracking", frame);

		//写入fps信息
		WriteFPSToFile(trackerType, fps);

		// Exit if ESC pressed.
		int k = waitKey(delay);
		if (k == 27){
		 
			break;
		}

	}

}


/*************************************************************************
*
* Function:   MultiTrackerCompare()
*
* Description: 多目标跟踪算法对比
*
* Input:
*
* Returns:
*
************************************************************************/

void Track::MultiTrackerCompare(CString filename) {
	USES_CONVERSION;

	LPCSTR videopath = (LPCSTR)T2A(filename);

	// Create a tracker
	Ptr<Tracker> trackerboosting = TrackerBoosting::create();
	Ptr<Tracker> trackermil = TrackerMIL::create();
	Ptr<Tracker> trackertld = TrackerTLD::create();
	Ptr<Tracker> trackerkcf = TrackerKCF::create();
	Ptr<Tracker> trackermedianflow = TrackerMedianFlow::create();
	Ptr<Tracker> trackermosse = TrackerMOSSE::create();

	// Read video
	VideoCapture video(videopath);
	long nFrame = static_cast<long>(video.get(CV_CAP_PROP_FRAME_COUNT)); // 获取总帧数
	double position = 100;
	video.set(CV_CAP_PROP_POS_FRAMES, position);

	// Exit if video is not opened
	if (!video.isOpened()) {
		AfxMessageBox(_T("Could not read video file"));
		return;
	}

	// Read first frame
	Mat frame;
	Mat frameboosting, frametld, framemil, framekcf, framemoose, framemedianflow;
	video.read(frame);

	// Define initial boundibg box
	Rect2d bbox(287, 23, 86, 320);

	// Uncomment the line below to select a different bounding box
	bbox = selectROI(frame, false);

	// Display bounding box.
	rectangle(frame, bbox, Scalar(0, 0, 0), 2, 1);

	imshow("Tracking", frame);

	trackerboosting->init(frame, bbox);
	trackermil->init(frame, bbox);
	trackertld->init(frame, bbox);
	trackerkcf->init(frame, bbox);
	trackermedianflow->init(frame, bbox);
	trackermosse->init(frame, bbox);

	while (video.read(frame)) {

		frame.copyTo(frameboosting);
		frame.copyTo(frametld);
		frame.copyTo(framemil);
		frame.copyTo(framekcf);
		frame.copyTo(framemoose);
		frame.copyTo(framemedianflow);

		// Update the tracking result
		bool okboosting = trackerboosting->update(frameboosting, bbox);
		bool okmil = trackermil->update(framemil, bbox);
		bool oktld = trackertld->update(frametld, bbox);
		bool okkcf = trackerkcf->update(framekcf, bbox);
		bool okmdieanflow = trackermedianflow->update(framemedianflow, bbox);
		bool okmoose = trackermosse->update(framemoose, bbox);
 


		if (okboosting) {
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox, Scalar(0, 0, 255), 1, 1);
		}

		if (okmil) {
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox, Scalar(0, 255, 0), 1, 1);
		}

		if (oktld) {
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox, Scalar(255, 0, 0), 1, 1);
		}

		if (okkcf) {
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox, Scalar(255, 0, 255), 1, 1);
		}

		if (okmdieanflow) {
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox, Scalar(255, 255, 0), 1, 1);
		}

		if (okmoose) {
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox, Scalar(122, 255, 255), 1, 1);
		}



		
		// Display frame.
		imshow("Tracking", frame);

		// Exit if ESC pressed.
		int k = waitKey(1);
		if (k == 27) {

			break;
		}

	}
}


Rect Track::GSMDetectionAre(Mat image01, Mat image02) {
 
	Mat imgdiff;

 
	//隔两帧配准
		 
	if (image01.empty()) {
		return Rect(0, 0, 0, 0);
	}

	if (image02.empty()) {
		return Rect(0, 0, 0, 0);
	}

	//GaussianBlur(image02, image02, Size(3,3), 0);

	double time0 = static_cast<double>(getTickCount());//开始计时

	//灰度图转换  
	Mat image1, image2;
	cvtColor(image01, image1, CV_RGB2GRAY);
	cvtColor(image02, image2, CV_RGB2GRAY);

	//提取特征点    
	auto surfDetector = xfeatures2d::SURF::create(2500);// 海塞矩阵阈值，高一点速度会快些
	vector<KeyPoint> keyPoint1, keyPoint2;
	surfDetector->detect(image1, keyPoint1);
	surfDetector->detect(image2, keyPoint2);

	//特征点描述，为下边的特征点匹配做准备    
	auto SurfDescriptor = xfeatures2d::SurfDescriptorExtractor::create();
	Mat imageDesc1, imageDesc2;
	SurfDescriptor->compute(image1, keyPoint1, imageDesc1);
	SurfDescriptor->compute(image2, keyPoint2, imageDesc2);

	//获得匹配特征点，并提取最优配对     
	FlannBasedMatcher matcher;
	vector<DMatch> matchePoints;
	matcher.match(imageDesc1, imageDesc2, matchePoints, Mat());
	sort(matchePoints.begin(), matchePoints.end()); //特征点排序    

	//获取排在前N个的最优匹配特征点  
	vector<Point2f> imagePoints1, imagePoints2;
	for (int i = 0; i<(int)(matchePoints.size()*0.25); i++) {
		imagePoints1.push_back(keyPoint1[matchePoints[i].queryIdx].pt);
		imagePoints2.push_back(keyPoint2[matchePoints[i].trainIdx].pt);
	}

	//获取图像1到图像2的投影映射矩阵 尺寸为3*3  
	Mat homo = findHomography(imagePoints1, imagePoints2, CV_RANSAC);


	//图像配准  
	Mat imageTransform1, imgpeizhun, imgerzhi;
	warpPerspective(image01, imageTransform1, homo, Size(image02.cols, image02.rows));
	//imshow("经过透视矩阵变换后",imageTransform1);  

	absdiff(image02, imageTransform1, imgpeizhun);
	//imshow("配准diff", imgpeizhun);  

	threshold(imgpeizhun, imgerzhi, 50, 255.0, CV_THRESH_BINARY);
	//imshow("配准二值化", imgerzhi);

	//输出所需时间
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << 1 / time0 << endl;

	Mat temp, image02temp;
	float m_BiLi = 0.9;

	image02temp = image02.clone();
	cvtColor(imgerzhi, temp, CV_RGB2GRAY);

	//检索连通域
	Mat se = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(temp, temp, MORPH_DILATE, se);

	vector<vector<Point>> contours;
	findContours(temp, contours, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if (contours.size()<1) {
		return Rect(0, 0, 0, 0);
	}
	int maxX = 0;
	int minX = image01.cols;
	int maxY = 0;
	int minY = image01.rows;

	for (int k = 0; k < contours.size(); k++) {
		Rect bomen = boundingRect(contours[k]);
		//删除比较小的检测
		if (bomen.height < 30 || bomen.width < 30) {
			continue;
		}
		//合并矩形框
		maxX = std::max(bomen.x, maxX);
		maxY = std::max(bomen.y, maxY);
		minX = std::min(bomen.x, minX);
		minY = std::min(bomen.y, minY);
	}

	if (abs(maxX - minX) > 200 || abs(maxY - minY) > 200) {
		return Rect(0, 0, 0, 0);
	}

	else {
		Rect ROI = Rect(Point(minX, minY), Point(maxX, maxY));
		return ROI;
	}

	

	 
}


/*************************************************************************
*
* Function:   WriteFPSToFile()
*
* Description: 将FPS写入文件 为了分析各个算法的平均FPS
*
* Input:
*
* Returns:
*
************************************************************************/
void Track::WriteFPSToFile(cv::String trackertype, float fps) {
	CStdioFile resultFile(_T("fps.txt"), CFile::modeNoTruncate);//
	resultFile.SeekToEnd();
	//类型转换
	
	CString fpsstr;
	fpsstr.Format(_T("%d"), fps); //int ->CString

	CString trackertyp;
	trackertyp.Format(_T("%s"), trackertype.c_str()); //cv::string->CString

	resultFile.WriteString(trackertyp + fpsstr +  _T("\r\n"));

	resultFile.Close();// 关闭文件 
}