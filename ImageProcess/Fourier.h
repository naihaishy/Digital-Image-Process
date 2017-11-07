#include <complex>
#define PI 3.1415926
using namespace std;


#pragma once
class Fourier
{
public:
	Fourier();
	~Fourier();


	//成员变量


	//成员函数
	
	void FFT2(complex<double> * TimeDomain, complex<double> * FrequencyDomain, int width, int height);
	void IFFT2(complex<double> * FrequencyDomain, complex<double> * TimeDomain, int width, int height);
	void FFT(complex<double> * TimeDomain, complex<double> * FrequencyDomain, int r);
	void IFFT(complex<double> * FrequencyDomain, complex<double> * TimeDomain, int r);
	bool BitReversedOrder(complex<double> * src, int n);//

};

