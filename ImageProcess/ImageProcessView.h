
// ImageProcessView.h : CImageProcessView 类的接口
//

#pragma once


class CImageProcessView : public CScrollView
{
protected: // 仅从序列化创建
	CImageProcessView();
	DECLARE_DYNCREATE(CImageProcessView)

// 特性
public:
	CImageProcessDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:

	//添加成员变量
	CString BmpName;	// 图像文件名
	CString EntName;	// 图像扩展名
	CBitmap m_bitmap;	//创建位图对象

	CBitmap m_bitmaplin;   //创建临时位图对象进行处理  
	CString BmpNameLin;    //保存图像副本文件  


	int m_nWidth;       //图像实际宽度  
	int m_nHeight;      //图像实际高度  
	int m_nDrawWidth;   //图像显示宽度  
	int m_nDrawHeight;  //图像显示高度  
	DWORD m_nImage;     //图像数据的字节数 只含位图  
	DWORD m_nSize;      //图像文件大小  
	int m_nLineByte;    //图像一行所占字节数  
	int m_nBitCount;    //图像每个像素所占位数  
	int m_nPalette;     //位图实际使用的颜色表中的颜色数  

	BYTE *m_pImage;         //读入图片数据后的指针  
	BITMAPFILEHEADER bfh;   //全局变量文件头  
	BITMAPINFOHEADER bih;   //全局变量信息头  
	RGBQUAD m_pPal[256];         //颜色表指针  

	



	//添加成员函数
	void ShowBitmap(CDC *pDc, CString BmpName); //显示位图函数
	bool ReadBmp(CString FileName);              //用来读取bmp格式图片  
	bool SaveBmp(LPCSTR lpFileName); //用来保存bmp格式图片 
	void WriteCharOnImage(CDC *pDc, CString FileName, LPCTSTR Characters, int m_xPosition, int m_yPosition); //在图片中写入字符
	void BilinearInterpolation(int Width, int Height);//双线性插值
	void RotateImage(int Angle);//旋转
	



	virtual ~CImageProcessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnWriteCharcter();
	afx_msg void OnBilinearInterpolation();
	afx_msg void OnRotate();
	virtual void OnInitialUpdate();
	afx_msg void OnHelp();
};

#ifndef _DEBUG  // ImageProcessView.cpp 中的调试版本
inline CImageProcessDoc* CImageProcessView::GetDocument() const
   { return reinterpret_cast<CImageProcessDoc*>(m_pDocument); }
#endif

