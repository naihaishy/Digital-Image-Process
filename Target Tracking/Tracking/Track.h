#pragma once
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\tracking\tracker.hpp>
#include <opencv2\xfeatures2d\nonfree.hpp>
#include "kcf\kcftracker.hpp"

using namespace std;
using namespace cv;

class Track
{
public:
	Track();
	~Track();

	

  


	int PlayVideo(CString filename);

	void GSMDetection(CString filename);

	void FDiffDetection(CString filename);


	void KCF(CString filename);

	Rect FaceDetect(Mat Image);

	void TragetTracker(CString filename, cv::String trackerType);

	void MultiTrackerCompare(CString filename);

	Rect GSMDetectionAre(Mat image01, Mat image02);

	void WriteFPSToFile(cv::String trackertype, float fps);

 


	 
 
	 
};

