#include "stdafx.h"
#include "Fourier.h"


Fourier::Fourier()
{
}


Fourier::~Fourier()
{
}


/*************************************************************************
*
* Function:
*
* Description:
*
* Input:
*
* Returns:
*
************************************************************************/
void Fourier::FFT2(complex<double> * TimeDomain, complex<double> * FrequencyDomain, int width, int height) {

	complex<double>*Temp = new complex<double>[height];
	complex<double>*Temp2 = new complex<double>[height];
	complex<double>*Input = new complex<double>[width*height];
	memcpy(Input, TimeDomain, sizeof(complex<double>)*width*height); //赋初值
	//先纵向FFT
	for (int u = 0; u<width; u++) {
		for (int v = 0; v<height; v++) {
			Temp[v] = complex<double>(Input[v*width + u].real(), Input[v*width + u].imag() ); //每列赋值
		}
		FFT(Temp, Temp2, height); //对该列数据FFT  
		for (int v = 0; v<height; v++) {
			Input[v*width + u] = complex<double>(Temp2[v].real(), Temp2[v].imag());
		}

	}

	//再横向FFT
	for (int v = 0; v<height; v++) {
		FFT(Input+v*width, Input + v*width, width);
	}

	memcpy(FrequencyDomain, Input, sizeof(complex<double>)*width*height);  

	delete[]Input, Temp;
}



/*************************************************************************
*
* Function:
*
* Description:
*
* Input: 
*
* Returns:
*
************************************************************************/
void Fourier::IFFT2(complex<double> * FrequencyDomain, complex<double> * TimeDomain, int width, int height) {

	complex<double>*Temp = new complex<double>[height];
	complex<double>*Input = new complex<double>[width*height];
	memcpy(Input, FrequencyDomain, sizeof(complex<double>)*width*height); //赋初值
	//先纵向IFFT
	for (int u = 0; u<width; u++) {
		for (int v = 0; v<height; v++) {
			Temp[v] = complex<double>(Input[v*width + u].real(), Input[v*width + u].imag()); //每列赋值
		}
		IFFT(Temp, Temp, height); //对该列数据IFFT  
		for (int v = 0; v<height; v++) {
			Input[v*width + u] = complex<double>(Temp[v].real(), Temp[v].imag());
		}

	}

	//再横向IFFT
	for (int v = 0; v<height; v++) {
		IFFT(Input + v*width, Input + v*width, width);
	}

	memcpy(TimeDomain, Input, sizeof(complex<double>)*width*height);
	delete[]Input, Temp;
}



/*************************************************************************
*
* Function:
*
* Description:
*
* Input: r级数
*
* Returns:
*
************************************************************************/
void Fourier::FFT(complex<double> * TimeDomain, complex<double> * FrequencyDomain, int n) {

	//long n = 1 << r; 
	int r = log2(n);
	 
	complex<double> *Wn, *Temp1, *Temp2, *X;
	Wn = new complex<double>[n / 2]; //Wn系数数组
	Temp1 = new complex<double>[n];
	Temp2 = new complex<double>[n];

	// 计算系数Wn
	double	angle;	 
	for (int i = 0; i < n / 2; i++) {
		angle = -i * PI * 2 / n;
		Wn[i] = complex<double>(cos(angle), sin(angle));
	}
	memcpy(Temp1, TimeDomain, sizeof(complex<double>) * n);// 将时域点写入X1

	int	 bfsize, p;	 
	// 采用蝶形算法进行快速傅立叶变换
	for (int k = 0; k < r; k++) {
		for (int j = 0; j < 1 << k; j++) {
			bfsize = 1 << (r - k);
			for (int i = 0; i < bfsize / 2; i++) {
				p = j * bfsize;
				Temp2[i + p] = Temp1[i + p] + Temp1[i + p + bfsize / 2];
				Temp2[i + p + bfsize / 2] = (Temp1[i + p] - Temp1[i + p + bfsize / 2]) * Wn[i * (1 << k)];
			}
		}
		X = Temp1;
		Temp1 = Temp2;
		Temp2 = X;
	}

	// 重新排序
	for (int j = 0; j < n; j++) {
		p = 0;
		for (int i = 0; i < r; i++) {
			if (j&(1 << i)) {
				p += 1 << (r - i - 1);
			}
		}
		FrequencyDomain[j] = Temp1[p];
	}

	// 释放内存
	delete[] Wn;
	delete[] Temp1;
	delete[] Temp2;

	 
}




/*************************************************************************
*
* Function:   
*
* Description:    
*
* Input:  
*
* Returns:
*
************************************************************************/
void Fourier::IFFT(complex<double> * FrequencyDomain, complex<double> * TimeDomain, int n) {
 
	complex<double>*Input = new complex<double>[n];
	complex<double>*Output = new complex<double>[n];
	memcpy(Input, FrequencyDomain, sizeof(complex<double>)*n);  //防止改变输入数据 (输入为指针)

	//共轭
	for (int i = 0; i < n; i++) {
		Input[i] = complex<double>(Input[i].real(), -Input[i].imag()); //虚部加负号
	}
	//一维快速傅立叶变换
	FFT(Input, Output, n);

	//时域数据求共轭，并除以n
	for (int i = 0; i<n; i++) {
		TimeDomain[i] = complex<double>(Output[i].real() / n, -Output[i].imag() / n);
	}

}


 
bool Fourier::BitReversedOrder(complex<double> * src, int n) {

	if (n == 1)
		return 0;
	complex<double>* temp = new complex<double>[n];
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {//偶数位序
			temp[i / 2] = src[i]; 
		}
		else {//奇数位序
			temp[(n+i) / 2] = src[i];
		}
	}
	for (int i = 0; i < n; i++) 
		src[i] = temp[i];

	//递归
	BitReversedOrder(src, n / 2);
	BitReversedOrder(src + n / 2, n / 2);

	delete[] temp;
	return 1;
}
