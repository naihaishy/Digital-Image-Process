#pragma once

struct Direction {
	int x;
	int y;
};

class Morphology
{
public:
	Morphology();
	~Morphology();
	//void Erosion(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void Erosion(double * Image, double * DstImage, double * SE, int SeWidth, int SeHeight, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void Dilation(double * Image, double * DstImage, double * SE, int SeWidth, int SeHeight, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	//void Or(double * Image0, double * Image1, double * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	//void Translation(double * Image, double * DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, Direction * direction);
};

