
// ImageProcessView.cpp : CImageProcessView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageProcess.h"
#endif


#include "ImageProcessDoc.h"
#include "ImageProcessView.h"
#include "HelpDlg.h"
#include "Common.h"
#include "BmpCommonOp.h"
#include "HistogramDlg.h"
#include "CommonDlg.h"
#include "ImproveDlg.h"
//#include "UserDlg.h"
#include "VideoDlg.h"
#include <afxinet.h> //Http
#include <algorithm>  
#include "Segment.h"
#include "Threshold.h"
#include "Morphology.h"
#include "Hough.h"
#include "Test.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessView

IMPLEMENT_DYNCREATE(CImageProcessView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcessView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CImageProcessView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CImageProcessView::OnFileSave)
	ON_COMMAND(ID_WRITE_CHARCTER, &CImageProcessView::OnWriteCharcter)
	ON_COMMAND(ID_BILINEAR_INTERPOLATION, &CImageProcessView::OnBilinearInterpolation)
	ON_COMMAND(ID_ROTATE, &CImageProcessView::OnRotate)
	ON_COMMAND(ID_HELP, &CImageProcessView::OnHelp)
	ON_COMMAND(ID_SHOW_HISTOGRAM, &CImageProcessView::OnShowHistogram)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CImageProcessView::OnHistogramEqualization)
	ON_COMMAND(ID_MEAN_FILTER, &CImageProcessView::OnMeanFilter)
	ON_COMMAND(ID_MEDIAN_FILTER, &CImageProcessView::OnMedianFilter)
	ON_COMMAND(ID_GAUSS_FILTER, &CImageProcessView::OnGaussFilter)
	ON_COMMAND(ID_PEPPER_SALT, &CImageProcessView::OnPepperSalt)
	ON_COMMAND(ID_HIGHBOOST_FILTER, &CImageProcessView::OnHighboostFilter)
	ON_COMMAND(ID_UNSHARP_MASKING, &CImageProcessView::OnUnsharpMasking)
	ON_COMMAND(ID_FFT, &CImageProcessView::OnFft)
	ON_COMMAND(ID_TEST, &CImageProcessView::OnTest)
	ON_COMMAND(ID_IFFT, &CImageProcessView::OnIfft)
	ON_COMMAND(ID_ILPF, &CImageProcessView::OnIlpf)
	ON_COMMAND(ID_BLPF, &CImageProcessView::OnBlpf)
	ON_COMMAND(ID_GLPF, &CImageProcessView::OnGlpf)
	ON_COMMAND(ID_BHPF, &CImageProcessView::OnBhpf)
	ON_COMMAND(ID_GHPF, &CImageProcessView::OnGhpf)
	ON_COMMAND(ID_IHPF, &CImageProcessView::OnIhpf)
	//ON_COMMAND(ID_FRQUENCY_LAPLACE, &CImageProcessView::OnFrquencyLaplace)
	//ON_COMMAND(ID_FRQUENCY_HIGHBOOST, &CImageProcessView::OnFrquencyHighboost)
	//ON_COMMAND(ID_HIGH_FREQUENCY_EMPHASIS, &CImageProcessView::OnHighFrequencyEmphasis)
	ON_COMMAND(ID_HOMOFILTER, &CImageProcessView::OnHomofilter)
	ON_COMMAND(ID_GAUSSIAN_NOISE, &CImageProcessView::OnGaussianNoise)
	ON_COMMAND(ID_SALT_NOISE, &CImageProcessView::OnSaltNoise)
	ON_COMMAND(ID_PEPPERSALT_NOISE, &CImageProcessView::OnPeppersaltNoise)
	ON_COMMAND(ID_PEPPER_NOISE, &CImageProcessView::OnPepperNoise)
	ON_COMMAND(ID_CONTRAHARMONIC_MEAN_FILTER, &CImageProcessView::OnContraharmonicMeanFilter)
	ON_COMMAND(ID_REPOST_ISSUE, &CImageProcessView::OnRepostIssue)
	ON_COMMAND(ID_IMPROVE_SETTING, &CImageProcessView::OnImproveSetting)
	ON_COMMAND(ID_USER_LOGIN, &CImageProcessView::OnUserLogin)
	ON_COMMAND(ID_ALPHA_TRIMMED_MEAN_FILTER, &CImageProcessView::OnAlphaTrimmedMeanFilter)
	ON_COMMAND(ID_ADAPTIVE_MEDIAN_FILTER, &CImageProcessView::OnAdaptiveMedianFilter)
	ON_COMMAND(ID_DOWNLOAD_TEST_IMAGES, &CImageProcessView::OnDownloadTestImages)
	ON_COMMAND(ID_GRAY, &CImageProcessView::OnGray)
	ON_COMMAND(ID_VIDEO_PLAY, &CImageProcessView::OnVideoPlay)
	ON_COMMAND(ID_IMAGE_SEG, &CImageProcessView::OnImageSeg)
	//ON_COMMAND(ID_EDGE_DETECTION, &CImageProcessView::OnEdgeDetection)
	ON_COMMAND(ID_SOBEL_OPERATOR, &CImageProcessView::OnSobelOperator)
	//ON_COMMAND(ID_LOG_OPERATOR, &CImageProcessView::OnLogOperator)
	//ON_COMMAND(ID_DOG_OPERATOR, &CImageProcessView::OnDogOperator)
	//ON_COMMAND(ID_PREWITT_OPERATOR, &CImageProcessView::OnPrewittOperator)
	ON_COMMAND(ID_CANNY_EDGE_DETACTION, &CImageProcessView::OnCannyEdgeDetaction)
	ON_COMMAND(ID_BASIC_GLOBAL_THRESHOLD, &CImageProcessView::OnBasicGlobalThreshold)
	ON_COMMAND(ID_OTSU_THRESHOLD, &CImageProcessView::OnOtsuThreshold)
	ON_COMMAND(ID_LOCAL_THRESHOLD, &CImageProcessView::OnLocalThreshold)
	ON_COMMAND(ID_DILATION, &CImageProcessView::OnDilation)
	
	
	ON_COMMAND(ID_EROSION, &CImageProcessView::OnErosion)
	ON_COMMAND(ID_WATER_DIGIFINALL, &CImageProcessView::OnWaterDigifinall)
	ON_COMMAND(ID_HOUGH_TRANSFORM, &CImageProcessView::OnHoughTransform)
	ON_COMMAND(ID_DIG_PROJECTION, &CImageProcessView::OnDigProjection)
	ON_COMMAND(ID_IMAGE_POSITIVE, &CImageProcessView::OnImagePositive)
	ON_COMMAND(ID_DIGITAL_SEGMENT, &CImageProcessView::OnDigitalSegment)
	 
END_MESSAGE_MAP()

// CImageProcessView 构造/析构

CImageProcessView::CImageProcessView()
{
	// TODO: 在此处添加构造代码
	
	

}

CImageProcessView::~CImageProcessView()
{
}

BOOL CImageProcessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}


void CImageProcessView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	SetScrollSizes(MM_TEXT, CSize(1200, 900));
	 
}
// CImageProcessView 绘制

//void CImageProcessView::OnDraw(CDC* /*pDC*/)
//{
//	CImageProcessDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: 在此处为本机数据添加绘制代码
//}


// CImageProcessView 打印

BOOL CImageProcessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageProcessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageProcessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CImageProcessView 诊断

#ifdef _DEBUG
void CImageProcessView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessDoc* CImageProcessView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessDoc)));
	return (CImageProcessDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessView 消息处理程序


/*************************************************************/
/* numPicture变量显示图片数量
/* 0-提示错误或未打开图片 1-显示一张图片 2-显示两张图片和处理
/*************************************************************/
int numPicture = 0;
CString flag  = _T("normal"); //标志位
int boolFourierinit = 0;//傅里叶操作初始化标志

//****************显示BMP格式图片****************//
void CImageProcessView::ShowBitmap(CDC *pDC, CString BmpName)
{



	//定义bitmap指针 调用函数LoadImage装载位图
	HBITMAP m_hBitmap = NULL ;
	m_hBitmap = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

	if (m_bitmap.m_hObject)
	{
		m_bitmap.Detach();           //切断CWnd和窗口联系
	}
	m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联

									 //边界
	CRect rect;
	GetClientRect(&rect);

	//图片显示(x,y)起始坐标
	int m_showX = 0;
	int m_showY = 0;
	int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度
	int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度

	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
		return;

	BITMAP m_bmp;                          //临时bmp图片变量
	m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中

	CBitmap *pbmpOld = NULL;
	dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境
 
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOut(0, m_bmp.bmHeight + 1, m_pDrawText.GetAt(0), _tcslen(m_pDrawText.GetAt(0))  );

	//图片显示调用函数stretchBlt
	pDC->StretchBlt(0, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);


	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
	DeleteObject(&m_bitmap);               //删除内存中的位图
	dcBmp.DeleteDC();                      //删除CreateCompatibleDC得到的图片DC


	/**
	* 是否显示效果图片
	*/
	if (numPicture == 2) {

		//显示图片函数LoadImage  
		HBITMAP m_hBitmapChange = NULL;

		//LW_LOADMAP3DCOLORS 的添加导致了效果文件出现了白色亮点/纹路  该问题困惑了好几天。。
		m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION);
				 

		if (m_bitmap.m_hObject) {
			m_bitmap.Detach();            //m_bitmap为创建的位图对象  
		}
		m_bitmap.Attach(m_hBitmapChange);
		//定义并创建一个内存设备环境  
		CDC dcBmp;
		if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC  
			return;
		BITMAP m_bmp ;                          //临时bmp图片变量  
		m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中  
		CBitmap *pbmpOld = NULL;
		dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境  

		//设置字体信息
		CFont font;
		font.CreateFont(20, 20, 0, 0, 200, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Microsoft YaHei"));
		dcBmp.SetTextColor(RGB(255, 0, 0));
		dcBmp.SelectObject(&font); //将字体属性选入DC
		dcBmp.SetBkMode(TRANSPARENT); //背景透明
		//dcBmp.TextOut(1, 1, _T("效果图"), 3);

		//如果原图+效果图的 宽度和 大于窗口宽度 则申请更大的窗口
		if (m_nDrawWidth + m_bmp.bmWidth < m_nWindowWidth) {
			SetScrollSizes(MM_TEXT, CSize(m_nWindowWidth , m_bmp.bmHeight + 10)); //窗口滚轮高度自适应
		}
		else {
			SetScrollSizes(MM_TEXT, CSize(m_nDrawWidth + m_bmp.bmWidth + 12 , m_bmp.bmHeight + 10));
		}
		pDC->BitBlt(m_nDrawWidth + 12, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, SRCCOPY);
		pDC->TextOut(m_nDrawWidth + 12, m_bmp.bmHeight + 1, m_pDrawText.GetAt(1), _tcslen(m_pDrawText.GetAt(1)));
		
		
		dcBmp.SelectObject(pbmpOld);	//恢复临时DC的位图  
		DeleteObject(&m_bitmap);        //删除内存中的位图
		dcBmp.DeleteDC();               //删除CreateCompatibleDC得到的图片DC

		

	}

	if(numPicture>2) { //多个图像显示问题
		
		CBitmap bitmapTemp;	//创建位图对象
		CString TempFileName;//
		
		for (int i = 0; i < numPicture-1; i++) {
 
			TempFileName.Format(_T("picture_%d.bmp"), i );

			//显示图片函数LoadImage  
			HBITMAP BitmapChange = NULL;
			BitmapChange = (HBITMAP)LoadImage(NULL, TempFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION);

			if (bitmapTemp.m_hObject) {
				bitmapTemp.Detach();            //m_bitmap为创建的位图对象  
			}
			bitmapTemp.Attach(BitmapChange);
			//定义并创建一个内存设备环境  
			CDC dcBmpTemp;
			if (!dcBmpTemp.CreateCompatibleDC(pDC))   //创建兼容性的DC  
				return;
			BITMAP bmpTemp;                          //临时bmp图片变量  
			bitmapTemp.GetBitmap(&bmpTemp);            //将图片载入位图中  
			
			
			dcBmpTemp.SelectObject(&bitmapTemp);         //将位图选入临时内存设备环境  

			//设置字体信息
			CFont font;
			font.CreateFont(15, 15, 0, 0, 200, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Times New Roman"));
			dcBmpTemp.SetTextColor(RGB(255, 0, 0));
			dcBmpTemp.SelectObject(&font); //将字体属性选入DC
			//dcBmpTemp.SetBkMode(TRANSPARENT); //背景透明
 

			//dcBmpTemp.TextOut(bmpTemp.bmWidth / 2, bmpTemp.bmHeight, m_pDrawText.GetAt(i + 1), sizeof(m_pDrawText.GetAt(i + 1)) + 1);
			//dcBmpTemp.TextOut(500, 420, _T("Johnny Carson"), 13);
			pDC->SetTextColor(RGB(255, 0, 0));
			pDC->TextOut((bmpTemp.bmWidth+1)*i, (bmpTemp.bmHeight+20)*2+3, m_pDrawText.GetAt(i + 1), _tcslen(m_pDrawText.GetAt(i + 1)) );
			 //如果原图+效果图的 宽度和 大于窗口宽度 则申请更大的窗口
			if ( (bmpTemp.bmWidth+1)*numPicture > m_nWindowWidth) {
				SetScrollSizes(MM_TEXT, CSize((bmpTemp.bmWidth + 1)*(numPicture-1), (bmpTemp.bmHeight+ 20)*2 + 30)); //窗口滚轮高度自适应
			}
			 
			pDC->BitBlt((m_nDrawWidth+1)*i , bmpTemp.bmHeight+ 20, bmpTemp.bmWidth, bmpTemp.bmHeight, &dcBmpTemp, 0, 0, SRCCOPY);

			dcBmpTemp.SelectObject(pbmpOld);	//恢复临时DC的位图  
			
			dcBmpTemp.DeleteDC();
		}

		DeleteObject(&bitmapTemp);        //删除内存中的位图
	}




}





//***************读取图片数据*************//
bool CImageProcessView::ReadBmp(CString FileName) //FileName
{


	USES_CONVERSION;
	LPCSTR FileNameChar = (LPCSTR)T2A(FileName); //将CString转成const char*

	FILE *fp;
	errno_t err = fopen_s(&fp, FileNameChar, "rb");

	if (err != 0)
	{
		AfxMessageBox(_T("无法打开文件!"), MB_OK, 0);
		return 0;
	}
	//读取文件头 解决BMP格式倒置的方法
	fread(&bfh.bfType, sizeof(WORD), 1, fp);
	fread(&bfh.bfSize, sizeof(DWORD), 1, fp);
	fread(&bfh.bfReserved1, sizeof(WORD), 1, fp);
	fread(&bfh.bfReserved2, sizeof(WORD), 1, fp);
	fread(&bfh.bfOffBits, sizeof(DWORD), 1, fp);
	//图像文件的总字节数
	m_nSize = bfh.bfSize;
	//判断是否是bmp格式图片
	if (bfh.bfType != 0x4d42)   //'BM'
	{
		AfxMessageBox(_T("不是BMP格式图片!"), MB_OK, 0);
		return 0;
	}
	//读取信息头
	fread(&bih.biSize, sizeof(DWORD), 1, fp);
	fread(&bih.biWidth, sizeof(LONG), 1, fp);
	fread(&bih.biHeight, sizeof(LONG), 1, fp);
	fread(&bih.biPlanes, sizeof(WORD), 1, fp);
	fread(&bih.biBitCount, sizeof(WORD), 1, fp);
	fread(&bih.biCompression, sizeof(DWORD), 1, fp);
	fread(&bih.biSizeImage, sizeof(DWORD), 1, fp);
	fread(&bih.biXPelsPerMeter, sizeof(LONG), 1, fp);
	fread(&bih.biYPelsPerMeter, sizeof(LONG), 1, fp);
	fread(&bih.biClrUsed, sizeof(DWORD), 1, fp);
	fread(&bih.biClrImportant, sizeof(DWORD), 1, fp);
	if (bih.biSize != sizeof(bih))
	{
		AfxMessageBox(_T("本结构所占用字节数出现错误"));
		return 0;
	}
	//位图压缩类型，必须是 0（不压缩） 1（BI_RLE8压缩类型）或2（BI_RLE压缩类型）之一
	if (bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox(_T("位图被压缩!"));
		return 0;
	}
	
	//读取颜色表  2 4 8位需要  24位不需要  目前仅支持24位和8位的BMP图像处理
	if (bih.biBitCount == 8)  // 8bit bmp
	{  
		if (bih.biClrUsed == 0) //如果该值为零,则有2的biBitCount次幂个元素
		{
			memset(m_pPal, 0, sizeof(RGBQUAD) * 256);
			fseek(fp, bfh.bfOffBits - sizeof(RGBQUAD) * 256, SEEK_SET);
			fread(&m_pPal, sizeof(RGBQUAD), 256, fp); //8bit BMP
		}
		else {
			memset(m_pPal, 0, sizeof(RGBQUAD)*bih.biClrUsed);
			fseek(fp, bfh.bfOffBits - sizeof(RGBQUAD)*bih.biClrUsed, SEEK_SET);
			fread(&m_pPal, sizeof(RGBQUAD), bih.biClrUsed, fp);
		}
		
	}

	//获取图像高宽和每个像素所占位数
	m_nHeight = bih.biHeight;
	m_nWidth = bih.biWidth;
	m_nDrawHeight = bih.biHeight;
	m_nDrawWidth = bih.biWidth;
	m_nBitCount = bih.biBitCount;   //每个像素所占位数
	//计算图像每行像素所占的字节数（必须是32的倍数）
	m_nLineByte = (m_nWidth*m_nBitCount + 31) / 32 * 4;

	//图片大小 调用系统自带的文件头 BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih; 
	//否则用 BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;要 m_nImage = m_nLineByte * m_nHeight - 2;
	m_nImage = m_nLineByte * m_nHeight;
	//位图实际使用的颜色表中的颜色数 biClrUsed
	m_nPalette = 0;                       //初始化

	if (bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//申请位图空间 大小为位图大小 m_nImage
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fp);
	fclose(fp);
	return true;
}



//****************保存文件****************//
bool CImageProcessView::SaveBmp(LPCSTR lpFileName) //lpFileName为要保存为的位图文件名
{
	
	USES_CONVERSION;

	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin); //将CString转成const char*

	FILE *fpo;
	errno_t err = fopen_s(&fpo, BmpFileNameLin, "rb"); //从临时效果文件中读取数据

	if (err != 0)
	{
		AfxMessageBox(_T("不存在效果文件!"), MB_OK, 0);
		return 0;
	}


	//不会影响全局变量
	BITMAPFILEHEADER tempBfh ; //临时文件头
	BITMAPINFOHEADER tempBih ; //临时信息头
	RGBQUAD tempPal[256]; //临时颜色表

	fread(&tempBfh, sizeof(BITMAPFILEHEADER), 1, fpo); //文件头
	fread(&tempBih, sizeof(BITMAPINFOHEADER), 1, fpo); //信息头
	
	//读取颜色表 
	if (bih.biBitCount == 8)  // 8bit bmp
	{
		if (bih.biClrUsed == 0) //如果该值为零,则有2的biBitCount次幂个元素
		{
			memset(tempPal, 0, sizeof(RGBQUAD) * 256);
			fseek(fpo, bfh.bfOffBits - sizeof(RGBQUAD) * 256, SEEK_SET);
			fread(&tempPal, sizeof(RGBQUAD), 256, fpo); //8bit BMP
		}
		else {
			memset(tempPal, 0, sizeof(RGBQUAD)*bih.biClrUsed);
			fseek(fpo, bfh.bfOffBits - sizeof(RGBQUAD)*bih.biClrUsed, SEEK_SET);
			fread(&tempPal, sizeof(RGBQUAD), bih.biClrUsed, fpo);
		}

	}

	int tempSrcImageSize = tempBfh.bfSize - tempBfh.bfOffBits; //实际大小-头大小=实际位图数据大小

	BYTE * tempSrcImage = (BYTE*)malloc(tempSrcImageSize);  //申请内存空间  
	//BYTE * tempSrcImage = new BYTE[tempSrcImageSize];
	fread(tempSrcImage, tempSrcImageSize, 1, fpo);  //位图数据

	//将BMP图像数据写入文件
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(lpFileName, tempBfh, tempBih, tempPal, tempSrcImage, tempSrcImageSize);

	fclose(fpo);
	free(tempSrcImage);
	//free(&tempPal);
	//delete[] tempPal;
	return true;
}


//****************在图片中写入字符****************//
void CImageProcessView::WriteCharOnImage(CDC *pDC,CString FileName, LPCTSTR Characters, int m_xPosition, int m_yPosition)
{

	//定义bitmap指针 调用函数LoadImage装载位图
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);


	if (m_bitmap.m_hObject)
	{
		m_bitmap.Detach();           //切断CWnd和窗口联系
	}
	m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联

									 //边界
	CRect rect;
	GetClientRect(&rect);

	//图片显示(x,y)起始坐标
	int m_showX = 0;
	int m_showY = 0;
	int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度
	int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度

	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
		return;

	BITMAP m_bmp;                          //临时bmp图片变量
	m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中

	CBitmap *pbmpOld = NULL;
	dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

	//设置字体信息
	CFont font;
	font.CreateFont(20, 20, 0, 0, 200, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Times New Roman"));
	dcBmp.SetTextColor(RGB(255, 0, 0));

	dcBmp.SelectObject(&font); //将字体属性选入DC
	

	dcBmp.SetBkMode(TRANSPARENT); //背景透明

	//两种方法绘制文字
	//dcBmp.DrawText(Characters, sizeof(Characters), &CRect(0, 0, 100, 40), DT_CENTER); 

	dcBmp.TextOut(m_xPosition, m_yPosition, Characters, _tcslen(Characters));

	//将带有文字的图片存入临时文件中

	unsigned char *pTemp = new unsigned char[m_nLineByte*m_nHeight];
	GetDIBits(dcBmp, (HBITMAP)m_bitmap.m_hObject, 0, m_nHeight, (LPVOID)pTemp, (BITMAPINFO*)&bih, DIB_RGB_COLORS);

	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin); //将CString转成const char*

	//将BMP图像数据写入文件
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, pTemp, m_nImage);

	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图

	numPicture = 2;
	Invalidate();
	
}







//****************双线性内插****************//
/*目前存在的问题：
1.8bit bmp处理后 显示时出现白色纹路2017.10.8   ===已解决2017.10.11 
*/

void CImageProcessView::BilinearInterpolation(int Width, int Height)
{
	
	//宽和高的比例
	float f_wScale = (float) m_nWidth  / Width;
	float f_hScale = (float) m_nHeight / Height;

	 
	int DstLineByte = (Width*m_nBitCount + 31) / 32 * 4; //目标位图每行大小 字节
	int DstImageSize = DstLineByte * Height;			 //目标位图数据大小
 
	//字节对齐问题 解决斜线
	if (Width %4 != 0) {
		Width = Width + (4 - Width % 4);
	}

	BYTE *DstImage = NULL;
	DstImage = new BYTE[DstImageSize];
 

	USES_CONVERSION;
	//LPCSTR BmpFileName = (LPCSTR)T2A(BmpName);
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);

	
	
	

	//处理开始
	for (int j = 0; j < Height;j++)  //Y
	{

		float y = (float)((j + 0.5)*f_hScale - 0.5); //对应源图像的Y坐标 两个图像的几何中心重合
		int z_y = (int)floor(y); //向下取整  整数部分
		float x_y = y - z_y; //小数部分

		if (z_y < 0) {
			x_y = 0; z_y = 0;
		}
		if (z_y > m_nHeight - 1) {
			x_y = 0; z_y = m_nHeight - 2;
		}

		for (int i = 0; i < Width;i++) //X
		{
			float x = (float)((i + 0.5)*f_wScale - 0.5); //对应源图像的X坐标 两个图像的几何中心重合 
			int z_x = (int)floor(x); //向下取整  整数部分
			float x_x = x - z_x; //小数部分

			if (z_x < 0) {
				x_x = 0; z_x = 0;
			}
			if (z_x > m_nWidth - 1) {
				x_x = 0; z_x = m_nWidth - 2;
			}

			//8bit BMP
			if (bih.biBitCount == 8) {
				int q11 = *(m_pImage + z_x + z_y*m_nLineByte);
				int q21 = *(m_pImage + (z_x + 1) + z_y*m_nLineByte);
				int q12 = *(m_pImage + z_x + (z_y + 1)*m_nLineByte);
				int q22 = *(m_pImage + (z_x + 1) + (z_y + 1)*m_nLineByte);

				*(DstImage + j*Width + i) = q11*(1.0 - x_x)*(1.0 - x_y) + q21*x_x*(1.0 - x_y) + q12*(1.0 - x_x)*x_y + q22*x_x*x_y; //必然小于255
			}

			//24bit BMP
			if (bih.biBitCount == 24) {

				//分别计算原图中 四个点的坐标
				unsigned int a1 = z_x * 3 + z_y*m_nLineByte;
				if (a1 > m_nImage) 	a1 = m_nImage - 2;//防止越界
				int q11_r = *(m_pImage + a1);
				int q11_g = *(m_pImage + a1 + 1);
				int q11_b = *(m_pImage + a1 + 2);

				unsigned int a2 = (z_x + 1) * 3 + z_y*m_nLineByte;
				if (a2 > m_nImage) 	a2 = m_nImage - 2;//防止越界
				int q21_r = *(m_pImage + a2);
				int q21_g = *(m_pImage + a2 + 1);
				int q21_b = *(m_pImage + a2 + 2);

				unsigned int a3 = z_x * 3 + (z_y + 1)*m_nLineByte;
				if (a3 > m_nImage) a3 = m_nImage - 2;//防止越界
				int q12_r = *(m_pImage + a3);
				int q12_g = *(m_pImage + a3 + 1);
				int q12_b = *(m_pImage + a3 + 2);


				unsigned int a4 = (z_x + 1) * 3 + (z_y + 1)*m_nLineByte;
				if (a4 > m_nImage) 	a4 = m_nImage - 2;//防止越界
				int q22_r = *(m_pImage + a4);
				int q22_g = *(m_pImage + a4 + 1);
				int q22_b = *(m_pImage + a4 + 2);

				//RGB 分量
				*(DstImage + j*Width * 3 + i * 3) = q11_r*(1.0 - x_x)*(1.0 - x_y) + q21_r*x_x*(1.0 - x_y) + q12_r*(1.0 - x_x)*x_y + q22_r*x_x*x_y;
				*(DstImage + j*Width * 3 + i * 3 + 1) = q11_g*(1.0 - x_x)*(1.0 - x_y) + q21_g*x_x*(1.0 - x_y) + q12_g*(1.0 - x_x)*x_y + q22_g*x_x*x_y;
				*(DstImage + j*Width * 3 + i * 3 + 2) = q11_b*(1.0 - x_x)*(1.0 - x_y) + q21_b*x_x*(1.0 - x_y) + q12_b*(1.0 - x_x)*x_y + q22_b*x_x*x_y;




			}

		}
	}

 
	//处理结束



	//文件头和信息头的修改 
	BITMAPFILEHEADER tempBfh = bfh; //临时文件头
	BITMAPINFOHEADER tempBih = bih; //临时信息头

	tempBfh.bfSize = DstImageSize + tempBfh.bfOffBits;
	tempBih.biWidth = Width;
	tempBih.biHeight = Height;

	//将BMP图像数据写入文件
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, tempBfh, tempBih, m_pPal, DstImage, DstImageSize);

	///fclose(fpo);
	delete[] DstImage;
	//delete[] SrcImage;
	numPicture = 2;
	Invalidate();

}






//**************图像旋转****************//

/*目前存在的问题：
1.图像清晰度效果不佳 2017.10.7      ===已优化 采用双线性插值 2017.10.8
2.边缘锯齿化在某些角度下比较明显 2017.10.7  


*/

void CImageProcessView::RotateImage(int Angle)
{

	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);

	/*定义PA=3.14时使用的方法是arcsin(1.0/2)*6即为π*/
	double PA; //3.1415926
	PA = asin(0.5) * 6;

	double degree;
	degree = (double) PA*Angle / 180; //弧度

	int XCenter = (int)bih.biWidth / 2;  //原图中心点X坐标
	int YCenter = (int)bih.biHeight / 2; //原图中心点Y坐标


	

	//处理开始


	//源图像坐标
	float x_pre; //双线性插值 
	float y_pre;


	//直接设置目标图像大小 也可以通过数学计算 以对角线长度的最为最终的宽高
	//int DstImageWidth = 2 * m_nWidth; //注意是像素单位 不是字节单位
	//int DstImageHeight = 2 * m_nHeight;

	int DstImageWidth = (int) sqrt(m_nWidth*m_nWidth + m_nHeight*m_nHeight) + 1;
	if (DstImageWidth % 4 != 0) {
		DstImageWidth = DstImageWidth + (4 - DstImageWidth % 4);
	}
	int DstImageHeight = DstImageWidth;


	int DstImageLine = (DstImageWidth * bih.biBitCount + 31) / 32 * 4;
	int DstImageSize = DstImageLine*DstImageHeight;
	BYTE * DstImage = new BYTE[DstImageSize];
	memset(DstImage, 255, DstImageSize); //初始化为255 白色

	//由目标图像坐标 找到对应的源图像坐标
	
	
	for (int x = 0; x < DstImageWidth; x++) {
		for (int y = 0; y < DstImageHeight; y++) {

			//关于与原图对应点的问题 涉及插值 

			//直接int 则是最近邻插值 
			//这里暂时使用最近邻插值 后期则会使用双线性内插 2017.10.7
			//x_pre = (int)((x - DstImageWidth / 2)*cos(degree) - (y - DstImageWidth / 2)*sin(degree) + XCenter);
			//y_pre = (int)((x - DstImageHeight / 2)*sin(degree) + (y - DstImageHeight / 2)*cos(degree) + YCenter);


			//2017.10.8更新 采用双线性内插
			x_pre = (float)((x - DstImageWidth / 2)*cos(degree) - (y - DstImageWidth / 2)*sin(degree) + XCenter);
			y_pre = (float)((x - DstImageHeight / 2)*sin(degree) + (y - DstImageHeight / 2)*cos(degree) + YCenter);

			int z_x = (int)floor(x_pre); //整数部分 向下取整
			float x_x = x_pre - z_x;  //小数部分
			int z_y = (int)floor(y_pre); //整数部分 向下取整
			float x_y = y_pre - z_y; //小数部分


			//if (x_pre >= 0 && y_pre >= 0 && x_pre < m_nWidth && y_pre < m_nHeight) {
			if (z_x >= 0 && z_y >= 0 && z_x + 1 < m_nWidth && z_y + 1  < m_nHeight) {


				//8bit 和24bit分开处理

				//8bit BMP处理
				if (bih.biBitCount == 8) {
					//最近邻插值2017.10.7
					//*(DstImage + x + y * DstImageWidth) = *(m_pImage + x_pre + y_pre *m_nWidth);

					//双线性插值 2017.10.8
					int q11 = *(m_pImage + z_x + z_y*m_nLineByte);
					int q21 = *(m_pImage + (z_x + 1) + z_y*m_nLineByte);
					int q12 = *(m_pImage + z_x + (z_y + 1)*m_nLineByte);
					int q22 = *(m_pImage + (z_x + 1) + (z_y + 1)*m_nLineByte);

					*(DstImage + y*DstImageWidth + x) = q11*(1.0 - x_x)*(1.0 - x_y) + q21*x_x*(1.0 - x_y) + q12*(1.0 - x_x)*x_y + q22*x_x*x_y;


				}


				//24bit BMP处理
				if (bih.biBitCount == 24) {

					//最近邻插值2017.10.7
					//int position = x_pre * 3 + y_pre *m_nWidth * 3; //原图中的位置
					//if (position + 2 < m_nImage) {
					//	*(DstImage + x * 3 + y * DstImageWidth * 3) = *(m_pImage + position);
					//	*(DstImage + x * 3 + y * DstImageWidth * 3 + 1) = *(m_pImage + position + 1);
					//	*(DstImage + x * 3 + y * DstImageWidth * 3 + 2) = *(m_pImage + position + 2);
					//}

					//双线性插值 2017.10.8

					//分别计算原图中 四个点的坐标
					unsigned int a1 = z_x * 3 + z_y*m_nLineByte;
					if (a1 > m_nImage) 	a1 = m_nImage - 2; //防止越界
					int q11_r = *(m_pImage + a1);
					int q11_g = *(m_pImage + a1 + 1);
					int q11_b = *(m_pImage + a1 + 2);

					unsigned int a2 = (z_x + 1) * 3 + z_y*m_nLineByte;
					if (a2 > m_nImage) 	a2 = m_nImage - 2;//防止越界
					int q21_r = *(m_pImage + a2);
					int q21_g = *(m_pImage + a2 + 1);
					int q21_b = *(m_pImage + a2 + 2);

					unsigned int a3 = z_x * 3 + (z_y + 1)*m_nLineByte;
					if (a3 > m_nImage) a3 = m_nImage - 2;//防止越界
					int q12_r = *(m_pImage + a3);
					int q12_g = *(m_pImage + a3 + 1);
					int q12_b = *(m_pImage + a3 + 2);


					unsigned int a4 = (z_x + 1) * 3 + (z_y + 1)*m_nLineByte;
					if (a4 > m_nImage) 	a4 = m_nImage - 2;//防止越界
					int q22_r = *(m_pImage + a4);
					int q22_g = *(m_pImage + a4 + 1);
					int q22_b = *(m_pImage + a4 + 2);


					*(DstImage + y*DstImageWidth * 3 + x * 3)	  = q11_r*(1.0 - x_x)*(1.0 - x_y) + q21_r*x_x*(1.0 - x_y) + q12_r*(1.0 - x_x)*x_y + q22_r*x_x*x_y;
					*(DstImage + y*DstImageWidth * 3 + x * 3 + 1) = q11_g*(1.0 - x_x)*(1.0 - x_y) + q21_g*x_x*(1.0 - x_y) + q12_g*(1.0 - x_x)*x_y + q22_g*x_x*x_y;
					*(DstImage + y*DstImageWidth * 3 + x * 3 + 2) = q11_b*(1.0 - x_x)*(1.0 - x_y) + q21_b*x_x*(1.0 - x_y) + q12_b*(1.0 - x_x)*x_y + q22_b*x_x*x_y;



				}

				
			}

		}
	}


	//处理结束


	//文件头和信息头的修改 
	BITMAPFILEHEADER tempBfh = bfh; //临时文件头
	BITMAPINFOHEADER tempBih = bih; //临时信息头

	tempBfh.bfSize = DstImageSize + tempBfh.bfOffBits;
	tempBih.biWidth = DstImageWidth;
	tempBih.biHeight = DstImageHeight;

	//将BMP图像数据写入文件
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, tempBfh, tempBih, m_pPal, DstImage, DstImageSize);

 

	 
	delete[] DstImage;
	numPicture = 2;
	flag = _T("rotate");  //几何变换           
	Invalidate();

	 
}



//****************双三次插值****************//
//void CImageProcessView::BicubicInterpolation(int Width, int Height) {
//
//
//
//
//
//}


//****************显示直观图****************//
void  CImageProcessView::ShowHistogram(BYTE* Image) {

	memset(m_nHistogramColor, 0, sizeof(int) *256);

	//m_nHistogramColor 统计数值
	for (unsigned int i = 0; i < m_nImage; i++) {
			int currentColor = Image[i];
			m_nHistogramColor[currentColor]++; //当前灰度级+1
	}

	//m_dHistogramColor 概率
	for (int i = 0; i < 256; i++) {
		m_dHistogramColor[i] =   (double(m_nHistogramColor[i]) / m_nImage);
	}
}

//****************直方图均衡化****************//
void CImageProcessView::HistogramEqualization() {

	//BYTE * GraySrcImage = new BYTE[m_nImage];
	BmpCommonOp bmpcommonop;
	//bmpcommonop.RGB2Gray(m_pImage, GraySrcImage, m_nWidth, m_nHeight,bih.biBitCount, m_nLineByte);


	ShowHistogram(m_pImage);
	double  accuColor[256]; //CDF
	int resultColor[256]; //s=T(r)中的s 输出像素
	memset(accuColor, 0, sizeof(int) * 256); //初始化
	accuColor[0] = m_dHistogramColor[0]; 
	resultColor[0] = (int)((256 - 1)*accuColor[0] + 0.5);  
	//计算累加概率CDF
	for (unsigned int i = 1; i < 256; i++) {
		accuColor[i] = accuColor[i - 1] + m_dHistogramColor[i];
		resultColor[i] = (int)  ( (256 - 1)*accuColor[i] + 0.5) ;  //四舍五入
	}


	//保存到效果文件中
	BYTE * OutputImage = new BYTE[m_nImage];
	memset(OutputImage, 0 ,  m_nImage); //初始化
	int resultHistogramColor[256]; //均衡化图像的灰度级统计
	memset(resultHistogramColor, 0, sizeof(int)*256);

	 //按照灰度级对应关系计算每个原图像素的目标像素值
	for (int i = 0; i < m_nImage; i++) {
		int current = m_pImage[i]; //当前点的像素  输入像素
		OutputImage[i] =  resultColor[current]; //均衡化后的像素 输出像素
		resultHistogramColor[resultColor[current]] ++ ; //当前灰度级+1 
	}



	//将BMP图像数据写入文件
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);

	//显示效果图像的直方图
	CHistogramDlg dlg_effect;	//显示对话框
	dlg_effect.HistogramColor = resultHistogramColor;  //将统计结果传递给对话框
	dlg_effect.m_sWindowTitle =  _T("均衡化后直方图") ;
	dlg_effect.DoModal();

	//显示原图直方图
	CHistogramDlg dlg_src;
	ShowHistogram(m_pImage); //统计灰度
	dlg_src.HistogramColor = m_nHistogramColor;  //将统计结果传递给对话框
	dlg_src.m_sWindowTitle = _T("原图直方图");
	dlg_src.DoModal();
 
	 


	delete[] OutputImage;
	numPicture = 2;   
	Invalidate();
}

//******************模板滤波*****************//
void CImageProcessView::TemplateFilter(BYTE* Image, BYTE* DstImage, int *mask, int m , int n, bool needWc=true) {

	//BYTE * OutputImage = new BYTE[m_nImage];
	memcpy(DstImage, Image, m_nImage); //初始化 将原图数据拷贝到目标图像
	int a = (m - 1) / 2; //m=2a+1
	int b = (n - 1) / 2;  //n=2b+1

	//获取数组权值总和
	int weight_count;
	if (needWc) {//是否需要计算模板之和
		weight_count = 0;
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < m; i++) {
				weight_count += *(mask + j*m + i);
			}
		}
	}
	else {
		weight_count = 1;
	}
	

	for (int y = b; y < m_nHeight - b; y++) { // Y 边缘的不处理
		for (int x = a; x < m_nWidth - a; x++) {//X

			int sum = 0, sum_r = 0, sum_g = 0, sum_b = 0; //加权和
			for (int i = -a; i < a + 1; i++) {//m
				for (int j = -b; j < b + 1; j++) {//n

					if ((y + b)*m_nLineByte + (x + a) < m_nImage) {//防止越界     

						//8bit BMP
						if (bih.biBitCount == 8) {
							int currentPosition = y*m_nLineByte + x;//当前处理像素点位置
							int position = (y + j)*m_nLineByte + x + i; //周围点位置
							sum += *(Image + position)*( *(mask + (i + a) + (j + b)*m ) );
							*(DstImage + currentPosition) = sum / weight_count;
						}//end 8bit bmp



						 //24bit BMP
						if (bih.biBitCount == 24) {
							if ((y + b)*m_nLineByte + (x + a) * 3 + 2 < m_nImage) {//防止越界  
								int currentPosition = y*m_nLineByte + x * 3;//当前处理像素点位置 RGB 
								int position_r = (y + j)*m_nLineByte + (x + i) * 3;
								int position_g = (y + j)*m_nLineByte + (x + i) * 3 + 1;
								int position_b = (y + j)*m_nLineByte + (x + i) * 3 + 2;

								sum_r += *(Image + position_r)*(*(mask + (i + a) + (j + b)*m) ); //R
								sum_g += *(Image + position_g)*(*(mask + (i + a) + (j + b)*m ) ); //G
								sum_b += *(Image + position_b)*(*(mask + (i + a) +( j + b)*m) ); //B
								*(DstImage + currentPosition) = sum_r / weight_count; //R
								*(DstImage + currentPosition + 1) = sum_g / weight_count; //G
								*(DstImage + currentPosition + 2) = sum_b / weight_count; //B
							}
						}//end 24bit bmp


					}//endif


				}
			}//end operatiom  for one point

		}
	}//end the whole image

	 //将BMP图像数据写入文件
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);


}


//******************均值滤波*****************//
void CImageProcessView::MeanFilter(int m, int n) { 

	//构造均值模板
	int *meanMask = new int[m*n];
	for (int i = 0; i < m*n; i++)
		meanMask[i] = 1;
	//将模板传递模板滤波函数
	BYTE * OutputImage = new BYTE[m_nImage];
	TemplateFilter(m_pImage, OutputImage, meanMask, m, n);

	//销毁资源
	delete[] meanMask;
	delete[] OutputImage;
	numPicture = 2;
	Invalidate();
}

 

//******************中值滤波*****************//
void CImageProcessView::MedianFilter(int m,int n) { //m x 宽  n y高

	BYTE * OutputImage = new BYTE[m_nImage];
	memcpy(OutputImage, m_pImage, m_nImage); //将原图数据拷贝到目标图像 为了解决 [窗口m n变大时边缘图像信息的丢失 导致出现黑框(系统默认初始为0)]这个问题
	Common common; //实例化common对象 内涵常用操作函数

	int a = (m - 1) / 2; //m=2a+1
	int b = (n - 1) / 2;  //n=2b+1
	int median = 0;
	int *arr, *arr_r, *arr_g, *arr_b; //滤波框中像素点数组 为了选择中值
	arr = (int *)malloc(sizeof(int)*m*n);//分配内存
	memset(arr,0, sizeof(int)*m*n);
	arr_r = (int *)malloc(sizeof(int)*m*n);
	arr_g = (int *)malloc(sizeof(int)*m*n);
	arr_b = (int *)malloc(sizeof(int)*m*n);

	for (int y = b; y <= m_nHeight-b; y++) {//Y  边缘的不处理
		for (int x = a; x <= m_nWidth-a; x++) {//X

			//8bit BMP
			if (bih.biBitCount==8) {
				int currentPosition = y*m_nLineByte + x;//当前处理像素点位置
				int k = 0;
				if (  (y + b)*m_nLineByte + (x + a) < m_nImage ) {//防止越界    
					for (int i = -a; i < a + 1; i++) {//m
						for (int j = -b; j < b + 1; j++) {//n
							int position = (y + j)*m_nLineByte + x + i; //周围点位置
							arr[k] = *(m_pImage + position);
							k++;
						}
					}//获取周围点像素数组完毕
					median = common.GetMedian(arr, m*n); //计算中值
					*(OutputImage + currentPosition) = median;
				}//end if
			}//end 8bit

			//24bit BMP
			if (bih.biBitCount == 24) {
				int currentPosition = y*m_nLineByte + x * 3;//当前处理像素点位置 RGB 
				int k = 0;
				if (  (y + b)*m_nLineByte + (x + a) * 3 + 2 < m_nImage ) {//防止越界
					for (int i = -a; i < a + 1; i++) {//m
						for (int j = -b; j < b + 1; j++) {//n
							int position_r = (y + j)*m_nLineByte + (x + i) * 3;
							int position_g = (y + j)*m_nLineByte + (x + i) * 3 + 1;
							int position_b = (y + j)*m_nLineByte + (x + i) * 3 + 2;
							arr_r[k] = *(m_pImage + position_r); //R
							arr_g[k] = *(m_pImage + position_g); //G
							arr_b[k] = *(m_pImage + position_b); //B
							k++;
						}
					}//获取周围点像素数组完毕
					int median_r = common.GetMedian(arr_r, m*n); //计算中值
					int median_g = common.GetMedian(arr_g, m*n);
					int median_b = common.GetMedian(arr_b, m*n);
					*(OutputImage + currentPosition) = median_r; //R
					*(OutputImage + currentPosition + 1) = median_g; //G
					*(OutputImage + currentPosition + 2) = median_b; //B
				}//end if
			}//end 24bit

		}
	}//end the whole image




	//将BMP图像数据写入文件
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	BmpCommonOp bmpcommomop;
	//边缘处理
	bmpcommomop.FilterEdgeProcess(OutputImage, OutputImage, a, b, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);


	delete[] OutputImage;
	numPicture = 2;
	Invalidate();

}


//******************高斯滤波*****************//
void CImageProcessView::GaussFilter(int m) { //这里仅使用3x3的模板 高斯核比较麻烦构造
	
	BYTE * OutputImage = new BYTE[m_nImage];
	if (m == 3) {
		int gaussMask[] = { 1, 2, 1 ,  2, 4, 2 ,  1, 2, 1 };//定义mask
		TemplateFilter(m_pImage, OutputImage, gaussMask, 3, 3);
		delete[] OutputImage;
		numPicture = 2;
		Invalidate();

	}
	if (m == 5) {
		int gaussMask[] = { 1, 4,7,4,1,4,16,26,16,4,7,26,41,26,7,4,16,26,16,4,1,4,7,4,1 };

		TemplateFilter(m_pImage, OutputImage, gaussMask, 5, 5);
		delete[] OutputImage;
		numPicture = 2;
		Invalidate();
	}


 

}



//******************高提升滤波*****************//
void CImageProcessView::HighboostFilter(float karr[], int n) {


	int length = n; //k值的个数 即可同时处理一组k值

	USES_CONVERSION;
   
	BmpCommonOp bmpcommonop;
	//BYTE * GraySrcImage = RGB2Gray(); //灰度化  是否需要灰度化应该根据用户操作进行决策

	//1.高斯平滑
	int gaussMask[] = { 1, 4,7,4,1,4,16,26,16,4,7,26,41,26,7,4,16,26,16,4,1,4,7,4,1 };
	BYTE * OutputImage = new BYTE[m_nImage];
	TemplateFilter(m_pImage, OutputImage, gaussMask, 5, 5);

	//2.生成非锐化模板
	int *mask = new int[m_nImage]; //mask中会出现负数 注意这一点

	for (int j = 0; j < m_nHeight;j++) { 
		for (int i = 0; i < m_nWidth; i++) {

			if (bih.biBitCount==8) {
				int postion = j*m_nLineByte + i;
				mask[postion] = m_pImage[postion] - OutputImage[postion];
			}

			if (bih.biBitCount==24) {
				int postion = j*m_nLineByte + i * 3;
				for (int m = 0; m < 3; m++) {
					mask[postion+m] = m_pImage[postion+m] - OutputImage[postion+m];
				}
			}

		}
	}

	
	//3.将模板加到原图像中
	BYTE * DstImage = new BYTE[m_nImage];
	int *TempImage = new int[m_nImage]; //有负数 并且可能高于255

	for (int s = 0; s < length; s++) {

		for (int j = 0; j < m_nHeight; j++) {
			for (int i = 0; i < m_nWidth; i++) {

				if (bih.biBitCount == 8) {
					int postion = j*m_nLineByte + i;
					TempImage[postion] = (int) (m_pImage[postion] + mask[postion] * karr[s] + 0.5); //四舍五入
				}

				if (bih.biBitCount == 24) {
					int postion = j*m_nLineByte + i * 3;
					for (int m = 0; m < 3; m++) {
						TempImage[postion + m] =(int) (m_pImage[postion + m] + mask[postion + m] * karr[s] + 0.5); //四舍五入
					}
				}

			}
		}


		//4.像素归一化到[0 ,255]   线性拉伸  RGB三个通道

		bmpcommonop.Normalized(TempImage, DstImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

		//将BMP图像数据写入文件
		

		CString TempFileName;
		
		TempFileName.Format(_T("picture_%d.bmp"), s);
		

		 
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(TempFileName);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

		CString bmpTitle;
		bmpTitle.Format(_T("K=%2.2f"), karr[s]);
		m_pDrawText.Add(bmpTitle);
		 

		//显示图像
		//bmpcommonop.ShowBmpImage(cdc, DstImage, m_nWidth *s + s, m_nHeight*3+3, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);//boost filter
	}
	 
 

	

 	 

	

	//将mask保存到文件  需要归一化到[0,255] 线性拉伸
	BYTE* maskImage = new BYTE[m_nImage]; 
	bmpcommonop.Normalized(mask, maskImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

 
	CString TempFileName;
	TempFileName.Format(_T("picture_%d.bmp"), length);
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(TempFileName);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin,  bfh, bih, m_pPal, maskImage, m_nImage);///mask
	m_pDrawText.Add(_T("非锐化模板"));
	TempFileName.Format(_T("picture_%d.bmp"), length+1);
	BmpFileNameLin = (LPCSTR)T2A(TempFileName);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);///gaussian blur
	m_pDrawText.Add(_T("高斯模糊 "));

	
	//bmpcommonop.ShowBmpImage(cdc, OutputImage, 0, m_nHeight+1, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte); //gaussian blur
	//bmpcommonop.ShowBmpImage(cdc, maskImage, 0, m_nHeight*2+2, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);//mask
 
	



	//销毁资源
	delete[] mask;
	delete[] OutputImage;
	delete[] maskImage;
	delete[] DstImage;
	delete[] TempImage;
	numPicture = length+3;

	Invalidate();
	

} 




/*----------------------------------------------------------------------
							       频域处理
------------------------------------------------------------------------*/

//******************FFT*****************//
void CImageProcessView::FFT() {

	BmpCommonOp	bmpcommonop;
	bmpcommonop.ImgFFT(m_pImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

	boolFourierinit = bmpcommonop.m_bFourierinit; 
	BYTE * FFTSpeImage = new BYTE[bmpcommonop.m_nImageSize]; //频谱图的宽高使用新宽高 2幂

	if (bih.biBitCount == 8) {
		bmpcommonop.GetAmplitudespectrum(bmpcommonop.m_FrequencyDomain, FFTSpeImage, bmpcommonop.m_nImageWidth, bmpcommonop.m_nImageHeight, bih.biBitCount, 0);
	}

	if (bih.biBitCount == 24) {
		bmpcommonop.GetAmplitudespectrum(bmpcommonop.m_FrequencyDomainB, bmpcommonop.m_FrequencyDomainG, bmpcommonop.m_FrequencyDomainR, FFTSpeImage, bmpcommonop.m_nImageWidth, bmpcommonop.m_nImageHeight, bih.biBitCount,0);
	}

	//文件头和信息头的修改 
	BITMAPFILEHEADER tempBfh = bfh; //临时文件头
	BITMAPINFOHEADER tempBih = bih; //临时信息头

	tempBfh.bfSize = bmpcommonop.m_nImageSize + tempBfh.bfOffBits;
	tempBih.biWidth = bmpcommonop.m_nImageWidth;
	tempBih.biHeight = bmpcommonop.m_nImageHeight;

	//图像保存
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, tempBfh, tempBih, m_pPal, FFTSpeImage, bmpcommonop.m_nImageSize);

	delete[] FFTSpeImage;
	numPicture = 2;
	m_pDrawText.Add(_T("FFT频谱图"));
	Invalidate();
}

//******************IFFT*****************//
void CImageProcessView::IFFT() {

	//根原图相同规格 无需修改bmp头文件信息
	BYTE * IFFTSpeImage = new BYTE[m_nImage]; //恢复图像 频谱图
	BmpCommonOp	bmpcommonop;
	bmpcommonop.ImgFFT(m_pImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	bmpcommonop.ImgIFFT(IFFTSpeImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

	//图像保存
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, IFFTSpeImage, m_nImage);

	delete[] IFFTSpeImage;
	numPicture = 2;
	Invalidate();

}



//******************频域滤波*****************//
void CImageProcessView::FrequencyDomainFiltering(CString PFFlag, int nFreq, int nOrder, int Sigma) {

	BmpCommonOp	bmpcommonop;
	
	bmpcommonop.ImgFFT(m_pImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte); //FFT
	BYTE * DstImage = new BYTE[m_nImage]; //恢复图像
								 
	
	if (PFFlag==_T("ILPF")) {//理想低通滤波
		bmpcommonop.ImgIdealPassFilter(DstImage, nFreq, 0,m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}
	if (PFFlag == _T("BLPF")) {//布特沃斯低通滤波
		bmpcommonop.ImgButterworthPassFilter(DstImage, nFreq, nOrder, 0, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}
	if (PFFlag == _T("GLPF")) {//高斯低通滤波
		bmpcommonop.ImgGaussianPassFilter(DstImage, Sigma, 0, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}
	if (PFFlag == _T("IHPF")) {//理想高通滤波
		bmpcommonop.ImgIdealPassFilter(DstImage, nFreq, 1, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}
	if (PFFlag == _T("BHPF")) {//布特沃斯高通滤波
		bmpcommonop.ImgButterworthPassFilter(DstImage, nFreq, nOrder, 1, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}
	if (PFFlag == _T("GHPF")) {//高斯高通滤波
		bmpcommonop.ImgGaussianPassFilter(DstImage, Sigma, 1, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}

	//图像保存
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	delete[] DstImage;
 
	numPicture = 2;
	Invalidate();


}
 


//******************同态滤波*****************//
void CImageProcessView::HomomorphicFilter(int Sigma, double c, double GammaH, double GammaL) {

	BYTE * DstImage = new BYTE[m_nImage]; //恢复图像
	USES_CONVERSION;
	BmpCommonOp	*bmpcommonop = new BmpCommonOp();

	/*CString TempFileName;

	for (int i = 1; i < 30;i++) {
		
		TempFileName.Format(_T("picture_%d.bmp"), i);
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(TempFileName);
		bmpcommonop->ImgHomomorphicFilter(m_pImage, DstImage, 3000, 1, 3, 1.5, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
		bmpcommonop->WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);
	}*/


	bmpcommonop->ImgHomomorphicFilter(m_pImage, DstImage, Sigma, c, GammaH,  GammaL, m_nWidth,  m_nHeight, bih.biBitCount, m_nLineByte);
	//图像保存
	 
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop->WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	delete[] DstImage;
	delete bmpcommonop;
 
	numPicture = 2;
	Invalidate();
}




//******************修正的阿尔法均值滤波*****************//
void CImageProcessView::AlphaTrimmedMeanFilter(int m, int n, int d) {

	BYTE * OutputImage = new BYTE[m_nImage];
	memcpy(OutputImage, m_pImage, m_nImage); //将原图数据拷贝到目标图像

	Common common; //实例化common对象 内涵常用操作函数

	int a = (m - 1) / 2; //m=2a+1
	int b = (n - 1) / 2;  //n=2b+1
	int currentPosition; //当前处理像素点位置
	//8bit BMP 
	if (bih.biBitCount == 8) {

		int *arr = new int[m*n];
		memset(arr, 0, sizeof(int)*m*n);

		for (int y = b; y < m_nHeight - b; y++) {//Y  边缘的不处理
			for (int x = a; x < m_nWidth - a; x++) {//X
				currentPosition = y*m_nLineByte + x;
				int k = 0;
				int sum = 0;
				  
				for (int i = -a; i < a + 1; i++) {//m
					for (int j = -b; j < b + 1; j++) {//n
						int position = (y + j)*m_nLineByte + x + i; //周围点位置
						arr[k] = *(m_pImage + position);
						k++;
					}
				}//获取周围点像素数组完毕
				//排序
				common.InsertSort(arr, m*n);//得到排序好的数组

				//减去d个点 前d/2和后d/2 计算中间部分均值
				for (int kk = d; kk < m*n - d; kk++) {
					sum += arr[kk];//和
				}

				*(OutputImage + currentPosition) = sum / (m*n - 2*d) + 0.5;//四舍五入
				
			}
		}

		 
	}//end 8bit

	 //24bit BMP
	if (bih.biBitCount == 24) {

		int *arr_r = new int[m*n];
		int *arr_g = new int[m*n];
		int *arr_b = new int[m*n];
		memset(arr_r, 0, sizeof(int)*m*n);
		memset(arr_g, 0, sizeof(int)*m*n);
		memset(arr_b, 0, sizeof(int)*m*n);

		for (int y = b; y <= m_nHeight - b; y++) {//Y  边缘的不处理
			for (int x = a; x <= m_nWidth - a; x++) {//X
				currentPosition = y*m_nLineByte + x * 3;
				int k = 0;
				int sum_r = 0, sum_g = 0, sum_b = 0;
				if ((y + b)*m_nLineByte + (x + a) * 3 + 2 < m_nImage) {//防止越界
					for (int i = -a; i < a + 1; i++) {//m
						for (int j = -b; j < b + 1; j++) {//n
							int position_r = (y + j)*m_nLineByte + (x + i) * 3;
							int position_g = (y + j)*m_nLineByte + (x + i) * 3 + 1;
							int position_b = (y + j)*m_nLineByte + (x + i) * 3 + 2;
							arr_r[k] = *(m_pImage + position_r); //R
							arr_g[k] = *(m_pImage + position_g); //G
							arr_b[k] = *(m_pImage + position_b); //B
							k++;
						}
					}//获取周围点像素数组完毕
					 //排序
					common.InsertSort(arr_r, m*n);
					common.InsertSort(arr_g, m*n);
					common.InsertSort(arr_b, m*n);
					//减去d个点 前d/2和后d/2 计算中间部分均值
					for (int l = d / 2; l < m*n - d / 2; l++) {
						sum_r += arr_r[l];
						sum_g += arr_g[l];
						sum_b += arr_b[l];
					}


					*(OutputImage + currentPosition) = sum_r / (m*n - d) + 0.5; //R
					*(OutputImage + currentPosition + 1) = sum_g / (m*n - d) + 0.5; //G
					*(OutputImage + currentPosition + 2) = sum_b / (m*n - d) + 0.5; //B


				}//end if

			}
		}

		
 
	}

	BmpCommonOp  bmpcommonop;
	//边缘处理
	bmpcommonop.FilterEdgeProcess(OutputImage, OutputImage, a, b, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

	//将BMP图像数据写入文件
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	//BmpCommonOp bmpcommonop;
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);


	delete[] OutputImage;
	numPicture = 2;
	Invalidate();


}


//**************自适应中值滤波****************//
void CImageProcessView::AdaptiveMedianFilter(int Smax) {

	BYTE * OutputImage = new BYTE[m_nImage];
	memcpy(OutputImage, m_pImage, m_nImage); //将原图数据拷贝到目标图像  
	Common common; //实例化common对象 内涵常用操作函数
 
	int currentPosition; //当前处理像素点位置
	int surroundPosition;//周围点位置
	int edge = (Smax - 1) / 2;
	


	//8bit BMP 
	if (bih.biBitCount == 8) {

		for (int y = edge; y < m_nHeight-edge;y++) {//Y
			for (int x = edge; x < m_nWidth-edge;x++) {//X
				int m = 3;//初始窗口大小为3x3 
				currentPosition = y*m_nLineByte + x;//当前点
				while (m <= Smax) {
					int a = (m - 1) / 2;//m=2a+1
					int *arr = new int[m*m];//存放窗口像素值
					memset(arr, 0, sizeof(int)*m*m);//初始化为0
					int k = 0;
					for (int i = -a; i < a + 1; i++) {//m
						for (int j = -a; j < a + 1; j++) {//n
							surroundPosition = (y + j)*m_nLineByte + x + i; //周围点位置
							arr[k] = *(m_pImage + surroundPosition);
							k++;
						}
					}//获取周围点像素数组完毕
					//排序
					common.InsertSort(arr, m*m);//得到排序好的数组 从小到大
					int median = arr[(m*m-1)/2];//得到中值
					int min = arr[0];//最小
					int max = arr[m*m - 1];//最大
					int pix = *(m_pImage + currentPosition);//当前像素值
					//A
					if (median>min && median<max) {//中值既不是最大也不是最小
						//B
						if (pix>min && pix<max) {//当前像素既不是最大也不是最小
							*(OutputImage + currentPosition) = pix;
						}
						else {//输出中值
							*(OutputImage + currentPosition) = median;
						}
						//释放内存
						delete[] arr;
						break;//跳出循环 已经不需要增加窗口的循环处理了
					}
					//增加窗口大小
					m += 2;//奇数

				}//end while

			}
		}
 
		 

	}//end 8bit

	//24bit
	if (bih.biBitCount == 24) {
		
	}//end 24bit





	 //将BMP图像数据写入文件
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	BmpCommonOp bmpcommomop;

	//边缘处理
	bmpcommomop.FilterEdgeProcess(OutputImage, OutputImage, edge, edge, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);


	delete[] OutputImage;
	numPicture = 2;
	Invalidate();

}


//**************边缘检测****************//
void CImageProcessView::EdgeDetection(int Detector, int Smooth, double Threshold, double Threshold2=0.0) {

	//初始化
	Segment segment;
	BmpCommonOp bmpcommonop;
	//内存分配
	double * SrcImage = new double[m_nImage];
	double * EdgeOutImage = new double[m_nImage];
	BYTE * DstImage = new BYTE[m_nImage];

	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		SrcImage[i] = m_pImage[i]; //BYTE=> double 格式化输入图像数据
	}
	
	//边缘检测
	segment.EdgeDetection(SrcImage, EdgeOutImage, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte, Detector, Smooth, Threshold, Threshold2);
	
	
	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		DstImage[i] = BYTE( int(EdgeOutImage[i] + 0.5 ) ); //double=> BYTE 格式化输出图像数据
	}

	//将图像数据保存为图像
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);	
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	//内存释放
	delete[] SrcImage;
	delete[] EdgeOutImage;
	delete[] DstImage;
 
	//显示效果图像
	numPicture = 2;
	Invalidate();
	
}


//**************阈值处理****************//
void CImageProcessView::Thresholding(int Type, double Args[] = {}) {
	//初始化
	Threshold threshold;
	BmpCommonOp bmpcommonop;

	//内存分配
	double * SrcImage = new double[m_nImage];
	double * ThresholdOutImage = new double[m_nImage];
	BYTE * DstImage = new BYTE[m_nImage];

	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		SrcImage[i] = m_pImage[i]; //BYTE=> double 格式化输入图像数据
	}

	//灰度化
	if (bih.biBitCount==24) {
		bmpcommonop.RGB2Gray(SrcImage, SrcImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}
	
	//噪声处理
	bmpcommonop.GaussFilter(SrcImage, SrcImage, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte, 5, 5);//高斯滤波
	
	//阈值处理
	threshold.BaseThresholding(SrcImage, ThresholdOutImage, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte, Type, Args);

	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		DstImage[i] = BYTE(int(ThresholdOutImage[i] + 0.5)); //double=> BYTE 格式化输出图像数据
	}


	//将图像数据保存为图像
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	//内存释放
	delete[] SrcImage;
	delete[] ThresholdOutImage;
	delete[] DstImage;

	//显示效果图像
	numPicture = 2;
	Invalidate();
}


//**************形态学处理****************//
void CImageProcessView::Morphologying(int type){

	Morphology morphology;

	double * SrcImage = new double[m_nImage];
	double * OutImage = new double[m_nImage];
	BYTE * DstImage = new BYTE[m_nImage];

	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		SrcImage[i] = m_pImage[i]; //BYTE=> double 格式化输入图像数据
	}

	//semask设计
	double *SeMask = new double[9];
	for (int i = 0; i < 9; i++) {
		SeMask[i] = 255; //有效
	}

	switch (type){
		case 1://膨胀
			morphology.Dilation(SrcImage, OutImage, SeMask, 3, 3, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
			break;
		case 2://腐蚀
			break;
			morphology.Erosion(SrcImage, OutImage, SeMask, 3, 3, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	}

	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		DstImage[i] = BYTE(int(OutImage[i] + 0.5)); //double=> BYTE 格式化输出图像数据
	}


	//将图像数据保存为图像
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	BmpCommonOp bmpcommonop;
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	//内存释放
	delete[] SrcImage;
	delete[] OutImage;
	delete[] DstImage;

	//显示效果图像
	numPicture = 2;
	Invalidate();

}
//****************霍夫变换***************//
void CImageProcessView::HoughTransform(){
	//初始化

	BmpCommonOp bmpcommonop;

	//内存分配
	double * SrcImage = new double[m_nImage];
	double * EdgeOutImage = new double[m_nImage];
	BYTE * DstImage = new BYTE[m_nImage];

	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		SrcImage[i] = m_pImage[i]; //BYTE=> double 格式化输入图像数据
	}

	Hough hough;
	//霍夫变换检测直线
	hough.HoughLines(SrcImage, EdgeOutImage, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte, 1);


	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		DstImage[i] = BYTE(int(EdgeOutImage[i] + 0.5)); //double=> BYTE 格式化输出图像数据
	}



	//将图像数据保存为图像
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	//内存释放
	delete[] SrcImage;
	delete[] EdgeOutImage;
	delete[] DstImage;

	//显示效果图像
	numPicture = 2;
	Invalidate();
}



//****************水表数字检测***************//
void CImageProcessView::WaterDigifinall(){

	//初始化
	Segment segment;
	BmpCommonOp bmpcommonop;
	Morphology morphology;
	Hough hough;
	Threshold threshold;

	//内存分配
	double * SrcImage = new double[m_nImage];//原图 double类型
	double * EdgeOutImage = new double[m_nImage];//边缘检测后的二值化图像
	double * morDilationImage = new double[m_nImage];//膨胀后的图像
	double * houghOutImage = new double[m_nImage];//霍夫变换检测出来的直线(红色 带有二值化的图像)
 
	//初始化
	for (int i = 0; i < m_nImage; ++i) {
		SrcImage[i] = 0;
		EdgeOutImage[i] = 0;
		morDilationImage[i] = 0;
		houghOutImage[i] = 0;
	}
	 
 

	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		SrcImage[i] = m_pImage[i]; //BYTE=> double 格式化输入图像数据
	}

	//Canny边缘检测
	double ThresholdL = 120; 
	double ThresholdH = 240;
	segment.EdgeDetection(SrcImage, EdgeOutImage, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte, EDGE_DETECTOR_CANNY, SMOOTH_GAUSSIAN, ThresholdL, ThresholdH);

	//膨胀操作
	double *SeMask = new double[9];
	for (int i = 0; i < 9; i++) {
		SeMask[i] = 255; //有效
	}
	morphology.Dilation(EdgeOutImage, morDilationImage, SeMask, 3, 3, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);


	//霍夫变换检测直线
	hough.HoughLines(morDilationImage, houghOutImage, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	
	vector<CPoint> rectPoints = hough.GetRectPoints();//得到 距离数字最近的 矩形框的四个点

	//从原图中截取矩形框内像素   
	double *digOnlyImage = segment.RectSeg(SrcImage, rectPoints, bfh, bih, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
	
	//注意***从下面开始是处理矩形框内的像素*** 

	//反色 目的是为了下面的阈值处理 （因为数字是黑色的）
	for (int i = 0;i < segment.m_RectSegSize;i++) {
		digOnlyImage[i] = 255 - digOnlyImage[i];
	}
	//灰度化
	if (bih.biBitCount == 24) {
		bmpcommonop.RGB2Gray(digOnlyImage, digOnlyImage, segment.m_RectSegWidth, segment.m_RectSegHeight, bih.biBitCount, segment.m_RectSegLineByte);
	}
		
	 

	//阈值处理 
	double args[] = { 52.0 };//采用基本全局阈值处理 40
	double *ThresholdOutImage = new double[segment.m_RectSegSize];
	for (int i = 0;i < segment.m_RectSegSize;i++) {
		ThresholdOutImage[i] = 0;//初始化
	}
	threshold.BaseThresholding(digOnlyImage, ThresholdOutImage, segment.m_RectSegSize, segment.m_RectSegWidth, segment.m_RectSegHeight, bih.biBitCount, segment.m_RectSegLineByte, THRESHOLDING_BASIC_GLOBAL, args);
	
	//膨胀
	double *SegDilationImage = new double[segment.m_RectSegSize];
	for (int i = 0;i < segment.m_RectSegSize;i++) {
		SegDilationImage[i] = 0;//初始化
	}
	morphology.Dilation(ThresholdOutImage, SegDilationImage, SeMask, 3, 3, segment.m_RectSegSize, segment.m_RectSegWidth, segment.m_RectSegHeight, bih.biBitCount, segment.m_RectSegLineByte);


	//每个数字的分割
	segment.DigitalSeg(SegDilationImage, segment.m_RectSegbfh, segment.m_RectSegbih, m_pPal , segment.m_RectSegWidth, segment.m_RectSegHeight, bih.biBitCount, segment.m_RectSegLineByte);

	AfxMessageBox(_T("数字分割完毕, 输出在images/digits目录下!"));

	//数字的识别
	Test test;
	test.DigitPredict();

	//数字识别结果的显示
	AfxMessageBox(_T("数字分类完毕, 输出为images目录下的result.txt文件!"));





	 /*
	  * 下面是将各个阶段效果图的显示出来
	  */

	BYTE *DstImageEdge = new BYTE[m_nImage];
	for (int i = 0; i < m_nImage; ++i)
		DstImageEdge[i] = BYTE(int(EdgeOutImage[i] + 0.5));//Canny边缘检测

	BYTE *DstImageDilation  = new BYTE[m_nImage];
	for (int i = 0; i < m_nImage; ++i)
		DstImageDilation[i] = BYTE(int(houghOutImage[i] + 0.5));//膨胀

	BYTE *DstImageHough = new BYTE[m_nImage];
	for (int i = 0; i < m_nImage; ++i)
		DstImageHough[i] = BYTE(int(houghOutImage[i] + 0.5));//霍夫变换



	BYTE *DstImageDig = new BYTE[segment.m_RectSegSize];
	for (int i = 0; i < segment.m_RectSegSize; ++i)
		DstImageDig[i] = BYTE(int(digOnlyImage[i] + 0.5));//数字矩形区域

	BYTE *DstImageThreshold = new BYTE[segment.m_RectSegSize];
	for (int i = 0; i < segment.m_RectSegSize; ++i) 
		DstImageThreshold[i] = BYTE(int(SegDilationImage[i] + 0.5));//数字区域阈值处理

	
		
	//将图像数据保存为图像
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);


	bmpcommonop.WriteBmpDataToFile("images/CannyDector.bmp", bfh, bih, m_pPal, DstImageEdge, m_nImage, m_nWidth, m_nHeight);//Canny边缘检测
	bmpcommonop.WriteBmpDataToFile("images/CannyDialation.bmp", bfh, bih, m_pPal, DstImageDilation, m_nImage, m_nWidth, m_nHeight);//膨胀
	bmpcommonop.WriteBmpDataToFile("images/CannyHough.bmp", bfh, bih, m_pPal, DstImageHough, m_nImage, m_nWidth, m_nHeight);//霍夫变换

	bmpcommonop.WriteBmpDataToFile("images/DigRectangle.bmp", segment.m_RectSegbfh, segment.m_RectSegbih, m_pPal, DstImageDig, segment.m_RectSegSize, segment.m_RectSegWidth, segment.m_RectSegHeight);
	bmpcommonop.WriteBmpDataToFile("images/DigThreshold.bmp", segment.m_RectSegbfh, segment.m_RectSegbih, m_pPal, DstImageThreshold, segment.m_RectSegSize, segment.m_RectSegWidth, segment.m_RectSegHeight);



	AfxMessageBox(_T("各个流程的图像输出在images目录下，请查看!"));


	//数字识别
	//Test test;
	//test.DigitPredict();


	//内存释放
	delete[] SrcImage;
	delete[] EdgeOutImage;
	delete[] morDilationImage;
	delete[] houghOutImage;
	delete[] digOnlyImage;
	delete[] ThresholdOutImage;
	
	delete[] DstImageEdge;
	delete[] DstImageDilation;
	delete[] DstImageHough;
	delete[] DstImageDig;
	delete[] DstImageThreshold;
 

	//显示效果图像
	numPicture = 1;
	Invalidate();
	


}

//****************数字投影图***************//
void CImageProcessView::DigProjection(){
	BYTE* DstImage = new BYTE[m_nImage];
	memset(DstImage, 0, m_nImage);

	int *Arr = new int[m_nWidth] { 0 };
	//向x轴投影
	int biasy = 15;
	for (int i = 0; i < m_nWidth; i++) {
		for (int j = biasy; j < m_nHeight - biasy; j++) {
			int position = j * m_nLineByte + i * bih.biBitCount / 8;//当前处理像素中心点
																	//B单通道
			if (m_pImage[position] == 255) {
				Arr[i] += 1;
			}
		}
	}

	//找到投影图
	for (int i = 0;i < m_nWidth;i++) {
		for (int j = 0;j < Arr[i];j++) {
			int position = j * m_nLineByte + i * bih.biBitCount / 8;
			for (int k = 0;k < bih.biBitCount / 8;k++) {
				DstImage[position + k] = 255;
			}
		}
	}

	//将图像数据保存为图像
	BmpCommonOp bmpcommonop;
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	//显示效果图像
	numPicture = 2;
	Invalidate();


}







/*----------------------------------------------------------------------
								消息处理
------------------------------------------------------------------------*/

//**************绘制图像****************//
void CImageProcessView::OnDraw(CDC* pDC)
{
	CImageProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: 在此处为本机数据添加绘制代码

	

	if (EntName.Compare(_T("bmp")) == 0)
	{

		if (ReadBmp(BmpName)) {
			ShowBitmap(pDC, BmpName);
		}
		
	}

}


//**************文件打开****************//
void CImageProcessView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
 

	//目前仅支持BMP文件的保存
	CString bmpfilter = _T("BMP(*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, bmpfilter, this);

	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{

		BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp

		BmpNameLin = _T("picture.bmp");   //临时变量名  
		numPicture = 1;                  //显示一张图片 
		boolFourierinit = 0;
		EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();             //将文件扩展名转换为一个小写字符
		m_pDrawText.RemoveAll();//清除
		m_pDrawText.Add(_T("原图"));
		Invalidate();                    //调用该函数就会调用OnDraw重绘画图
	}
}





//******************文件保存*****************//
void CImageProcessView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码

	//目前仅支持BMP文件的保存
	CString bmpfilter = _T("BMP(*.bmp)|*.bmp||");
	//1-文件打开 0-文件保存
	CFileDialog dlg(0, NULL, _T("effect"), OFN_HIDEREADONLY, bmpfilter, NULL);
	//按下确定按钮
	if (dlg.DoModal() == IDOK) {

		CString str;
		CString strName;
		CString filename;
		str = dlg.GetPathName();           //获取文件的路径
		filename = dlg.GetFileTitle();     //获取文件名
		int nFilterIndex = dlg.m_ofn.nFilterIndex;
		if (nFilterIndex == 1)            //当用户选择文件过滤器为".BMP"时
		{
			str = str + _T(".bmp");	           //自动加扩展名.bmp

			USES_CONVERSION;
			LPCSTR lpstr = (LPCSTR)T2A(str);

			if ( SaveBmp(lpstr) )  AfxMessageBox(_T("图片保存成功"), MB_OK, 0);  //保存bmp图片  
		              

			
		}
	}
}


//******************使用帮助*****************//
void CImageProcessView::OnHelp()
{
	// TODO: 在此添加命令处理程序代码
	CHelpDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		
	}
}



//******************写入字符*****************//
void CImageProcessView::OnWriteCharcter()
{
	// TODO: 在此添加命令处理程序代码
	
	//如果没有导入图片直接写入字符 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能写入字符!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("写入字符效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("写入字符");
	dlg.m_sHelpTitle = _T("写入字符参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	dlg.m_bShowP4 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入X坐标"); //参数1 xPosition 
	dlg.m_P2Text = _T("请输入Y坐标"); //参数2 yPosition 
	dlg.m_P4Text = _T("请输入字符串"); //参数3 char 
	//设置默认值
	dlg.m_P1 = 1;
	dlg.m_P2 = 1;
	dlg.m_P4 = _T("U");

	//显示对话框
	if (dlg.DoModal() == IDOK ) 
	{
		if (int(dlg.m_P1) <= 0 || int(dlg.m_P2) <= 0) {
			AfxMessageBox(_T("输入坐标必须为正整数!"), MB_OK, 0);
			return;
		}
		if (dlg.m_P1 > m_nWidth || dlg.m_P2 > m_nHeight) {
			AfxMessageBox(_T("输入坐标不能为超过原图长宽!"), MB_OK, 0);
			return;
		}

		if (dlg.m_P4.GetLength()==0) {
			AfxMessageBox(_T("写入字符不得为空!"), MB_OK, 0);
			return;
		}

		CDC *pDc = GetDC();	 //获取当前DC
		WriteCharOnImage(pDc, BmpName, dlg.m_P4, int(dlg.m_P1), int(dlg.m_P2));

	}

	
}


//******************双线性内插*****************//
void CImageProcessView::OnBilinearInterpolation()
{
	// TODO: 在此添加命令处理程序代码

	//如果没有导入图片 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能执行双线性内插!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("双线性内插效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("双线性内插");
	dlg.m_sHelpTitle = _T("双线性内插参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入缩放后宽度"); //参数1 宽度 
	dlg.m_P2Text = _T("请输入缩放后高度"); //参数2 高度 
	//设置默认值
	dlg.m_P1 = 1152; 
	dlg.m_P2 = 864;
	
	if (dlg.DoModal() == IDOK) 
	{
		if (dlg.m_P1 <= 0 || dlg.m_P2 <= 0) {
			AfxMessageBox(_T("输入宽和高必须为正整数!"), MB_OK, 0);
			return;
		}
		BilinearInterpolation(int(dlg.m_P1), int(dlg.m_P2));
		 
	}

}



//******************图片旋转*****************//
void CImageProcessView::OnRotate()
{
	// TODO: 在此添加命令处理程序代码

	//如果没有导入图片 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能执行图片旋转!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("图片旋转效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("图片旋转");
	dlg.m_sHelpTitle = _T("图片旋转参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入旋转角度"); //参数1 angle 
	//设置默认值
	dlg.m_P1 = 45;//旋转角度45度

	if (dlg.DoModal() == IDOK)
	{
		RotateImage(int(dlg.m_P1)); //旋转
	}



}

//******************显示直方图*****************//
void CImageProcessView::OnShowHistogram()
{
	// TODO: 在此添加命令处理程序代码

	//如果没有导入图片 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能显示直方图!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
 
	//显示对话框
	CHistogramDlg dlg_src;
	ShowHistogram(m_pImage); //统计灰度
	dlg_src.HistogramColor = m_nHistogramColor;  //将统计结果传递给对话框
	dlg_src.m_sWindowTitle = _T("原图直方图");
	if (dlg_src.DoModal() == IDOK)
	{
		 
	}
}




//******************直方图均衡化*****************//
void CImageProcessView::OnHistogramEqualization()
{
	// TODO: 在此添加命令处理程序代码
	//如果没有导入图片 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行直方图均衡化处理!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("直方图均衡化效果图"));
	HistogramEqualization(); 

}



//******************均值滤波*****************//
void CImageProcessView::OnMeanFilter()
{
	// TODO: 在此添加命令处理程序代码
	//如果没有导入图片 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行均值滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("均值滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("均值滤波");
	dlg.m_sHelpTitle = _T("均值滤波参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入m"); //参数1 m
	dlg.m_P2Text = _T("请输入n"); //参数2 n
	//设置默认值
	dlg.m_P1 = 3;
	dlg.m_P2 = 3;

	if (dlg.DoModal() ==IDOK) {
		if (dlg.m_P1 <= 0 || dlg.m_P2 <= 0  || int(dlg.m_P1) %2==0 || int(dlg.m_P2) %2==0) {
			AfxMessageBox(_T("输入m和n必须为正奇数!"), MB_OK, 0);
			return;
		}

		MeanFilter(int(dlg.m_P1), int(dlg.m_P2));
	}
	
}

//******************中值滤波*****************//
void CImageProcessView::OnMedianFilter()
{
	// TODO: 在此添加命令处理程序代码
	//如果没有导入图片 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行中值滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("中值滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("中值滤波");
	dlg.m_sHelpTitle = _T("中值滤波参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入m"); //参数1 m
	dlg.m_P2Text = _T("请输入n"); //参数2 n
	//设置默认值
	dlg.m_P1 = 3;
	dlg.m_P2 = 3;

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1 <= 0 || dlg.m_P2 <= 0 || int(dlg.m_P1) % 2 == 0 || int(dlg.m_P2) % 2 == 0) {
			AfxMessageBox(_T("输入m和n必须为正奇数!"), MB_OK, 0);
			return;
		}

		MedianFilter(int(dlg.m_P1), int(dlg.m_P2));
	}
 


}

//******************高斯滤波*****************//
void CImageProcessView::OnGaussFilter()
{
	// TODO: 在此添加命令处理程序代码

	//如果没有导入图片 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行高斯滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("高斯滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("高斯滤波");
	dlg.m_sHelpTitle = _T("高斯滤波参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入m"); //参数1 m
	dlg.m_P2Text = _T("请输入n"); //参数2 n
	//设置默认值
	dlg.m_P1 = 3;
	dlg.m_P2 = 3;

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1 <= 0 || dlg.m_P2 <= 0 || int(dlg.m_P1) % 2 == 0 || int(dlg.m_P2) % 2 == 0) {
			AfxMessageBox(_T("输入m和n必须为正奇数!"), MB_OK, 0);
			return;
		}

		GaussFilter(int(dlg.m_P1));
	}

 

}


//******************椒盐噪声*****************//
void CImageProcessView::OnPepperSalt()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能添加噪声!"));
		return;
	}
	AfxMessageBox(_T("生成的图像请保存，并用于测试对比中值滤波的效果!"));
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("椒盐噪声效果图"));
	BmpCommonOp bmpcommonop;
	BYTE * OutputImage =  bmpcommonop.AddPepperSaltNoise(m_pImage, 0.005, 0, m_nImage, m_nWidth, m_nHeight, bih.biBitCount,  m_nLineByte);
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);

	delete[] OutputImage;
	numPicture = 2;
	Invalidate();
}

//******************高提升滤波*****************//
void CImageProcessView::OnHighboostFilter()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行高提升滤波!"));
		return;
	}

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("高提升滤波");
	dlg.m_sHelpTitle = _T("高提升滤波参数设置");
	//显示控件
	dlg.m_bShowP4 = true;
	//参数指定
	dlg.m_P4Text = _T("请输入一组K值\r多个K值请用英语半角逗号隔开"); //参数1 K
	//设置默认值
	dlg.m_P4 = _T("1, 2, 3, 4, 4.5, 5, 7, 9");//K


	if (dlg.DoModal() == IDOK) {
		Common commonl;
		float *karr;
		karr = commonl.SplitString(dlg.m_P4, _T(","));
		//float karr[] = { 1, 2, 3, 4, 4.5, 5, 7, 9 };
		int karr_size = _msize(karr) / sizeof(float);//数组的大小
		m_pDrawText.RemoveAll();//清除
		m_pDrawText.Add(_T("原图"));
		HighboostFilter(karr, karr_size); //k>1
	}

	
}

//******************非锐化掩蔽*****************//
void CImageProcessView::OnUnsharpMasking()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行非锐化掩蔽!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	float karr[] = { 1.0 };
	HighboostFilter(karr, 1);//k=1
}


//******************FFT*****************//
void CImageProcessView::OnFft()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行FFT!"));
		return;
	}

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("FFT频谱图"));
	FFT();
	

}




//******************IFFT*****************//
void CImageProcessView::OnIfft()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行IFFT!"));
		return;
	}
	if (!boolFourierinit) {
		AfxMessageBox(_T("FFT之后才能进行IFFT!"));
		return;
	}
 
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("IFFT 图"));

	IFFT();



}


//******************理想低通滤波*****************//
void CImageProcessView::OnIlpf()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行理想低通滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("理想低通滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("理想低通滤波器");
	dlg.m_sHelpTitle = _T("理想低通滤波器参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入截止频率");//参数1 截止频率
	//设置默认值
	dlg.m_P1 = 50;

	
	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0 ) {
			AfxMessageBox(_T("截止频率不得为负"), MB_OK, 0);
			return;
		}
		FrequencyDomainFiltering(_T("ILPF"), dlg.m_P1, 0, 0);
	}
}


//******************布特沃斯低通滤波*****************//
void CImageProcessView::OnBlpf()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行布特沃斯低通滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("布特沃斯低通滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("布特沃斯低通滤波器");
	dlg.m_sHelpTitle = _T("布特沃斯低通滤波器参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入截止频率");//参数1 截止频率
	//设置默认值
	dlg.m_P1 = 50;


	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0) {
			AfxMessageBox(_T("截止频率不得为负"), MB_OK, 0);
			return;
		}
		FrequencyDomainFiltering(_T("BLPF"), dlg.m_P1, 2, 0); //默认2阶
 
	}
}


//******************高斯低通滤波*****************//
void CImageProcessView::OnGlpf()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行高斯低通滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("高斯低通滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("高斯低通滤波器");
	dlg.m_sHelpTitle = _T("高斯低通滤波器参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入截止频率");//参数1 截止频率
	//设置默认值
	dlg.m_P1 = 50;


	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0) {
			AfxMessageBox(_T("截止频率不得为负"), MB_OK, 0);
			return;
		}
		FrequencyDomainFiltering(_T("GLPF"), dlg.m_P1, 0, dlg.m_P1); // a=D0
		 
	}
}


//******************理想高通滤波*****************//
void CImageProcessView::OnIhpf()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行理想高通滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("理想高通滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("理想高通滤波器");
	dlg.m_sHelpTitle = _T("理想高通滤波器参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入截止频率");//参数1 截止频率
	//设置默认值
	dlg.m_P1 = 50;

 

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0) {
			AfxMessageBox(_T("截止频率不得为负"), MB_OK, 0);
			return;
		}
		FrequencyDomainFiltering(_T("IHPF"), dlg.m_P1, 0, 0);
	 
	}
}


//******************高斯高通滤波*****************//
void CImageProcessView::OnGhpf()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行高斯高通滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("高斯高通滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("高斯高通滤波器");
	dlg.m_sHelpTitle = _T("高斯高通滤波器参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入截止频率");//参数1 截止频率
	//设置默认值
	dlg.m_P1 = 50;


	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0) {
			AfxMessageBox(_T("截止频率不得为负"), MB_OK, 0);
			return;
		}
		FrequencyDomainFiltering(_T("GHPF"), dlg.m_P1, 0, dlg.m_P1); // a=D0
	}
}


//******************布特沃斯高通滤波*****************//
void CImageProcessView::OnBhpf()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行布特沃斯高通滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("布特沃斯高通滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("布特沃斯高通滤波器");
	dlg.m_sHelpTitle = _T("布特沃斯高通滤波器参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入截止频率");//参数1 截止频率
	dlg.m_P2Text = _T("请输入阶数");//参数1 阶数
	//设置默认值
	dlg.m_P1 = 50;
	dlg.m_P2 = 2;

 

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0 || dlg.m_P2<0) {
			AfxMessageBox(_T("截止频率或者阶数不得为负"), MB_OK, 0);
			return;
		}
		FrequencyDomainFiltering(_T("BHPF"), dlg.m_P1, dlg.m_P2, 0); //2阶
	}
}




void CImageProcessView::OnFrquencyLaplace()
{
	// TODO: 在此添加命令处理程序代码
}


void CImageProcessView::OnFrquencyHighboost()
{
	// TODO: 在此添加命令处理程序代码
}


void CImageProcessView::OnHighFrequencyEmphasis()
{
	// TODO: 在此添加命令处理程序代码
}


//******************同态滤波*****************//
void CImageProcessView::OnHomofilter()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行同态滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("同态滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("同态滤波中高通滤波器");
	dlg.m_sHelpTitle = _T("同态滤波中高通滤波器参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	dlg.m_bShowP3 = true;
	dlg.m_bShowP4 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入截止频率");//参数1 截止频率
	dlg.m_P2Text = _T("请输入C");//参数2 C 
	dlg.m_P3Text = _T("请输入GammaH");//参数3 GammaH
	dlg.m_P4Text = _T("请输入GammaL");//参数4 GammaL
	//设置默认值
	dlg.m_P1 = 600;
	dlg.m_P2 = 0.2;
	dlg.m_P3 = 2.5;
	dlg.m_P4 = _T("0.2");
	 

 
	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0 || dlg.m_P2 <0 || dlg.m_P3 <0 || _tstof(dlg.m_P4) <0 ) {
			AfxMessageBox(_T("参数不得为负"), MB_OK, 0);
			return;
		}
		HomomorphicFilter(dlg.m_P1, dlg.m_P2, dlg.m_P3, _tstof(dlg.m_P4)); // 一般取Sigma=nFreq  默认给定  GammaH 2与 GammaL 0.25 c=1
	} 

	 
}


//******************高斯噪声*****************//
void CImageProcessView::OnGaussianNoise()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能添加噪声!"));
		return;
	}

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("高斯噪声效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("高斯噪声");
	dlg.m_sHelpTitle = _T("高斯噪声参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	dlg.m_bShowP3 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入噪声比例");//参数1 噪声比例
	dlg.m_P2Text = _T("请输入均值");//参数2 均值
	dlg.m_P3Text = _T("请输入方差");//参数3 方差
	//设置默认值
	dlg.m_P1 = 0.2;
	dlg.m_P2 = 30;
	dlg.m_P3 = 400;



	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0 || dlg.m_P1 >1) {
			AfxMessageBox(_T("噪声比例请控制在0-1之间!"));
			return;
		}
		
		BmpCommonOp bmpcommonop;
		BYTE * OutputImage = bmpcommonop.GaussianNoise(m_pImage, dlg.m_P1, dlg.m_P2, dlg.m_P3, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
		USES_CONVERSION;
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);
		
		delete[] OutputImage;
		numPicture = 2;
		Invalidate();
	}

}


//******************盐噪声*****************//
void CImageProcessView::OnSaltNoise()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能添加噪声!"));
		return;
	}

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("盐噪声效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("盐噪声");
	dlg.m_sHelpTitle = _T("盐噪声参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入噪声比例"); //参数1 噪声比例
	//设置默认值
	dlg.m_P1 = 0.15;

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0 || dlg.m_P1 >1) {
			AfxMessageBox(_T("噪声比例请控制在0-1之间!"));
			return;
		}
		double noiseRate = dlg.m_P1;
		BmpCommonOp bmpcommonop;
		BYTE * OutputImage = bmpcommonop.AddPepperSaltNoise(m_pImage, noiseRate, 1, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
		USES_CONVERSION;
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);
		numPicture = 2;
		delete[] OutputImage;
		Invalidate();
	}
}


//******************椒盐噪声*****************//
void CImageProcessView::OnPeppersaltNoise()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能添加噪声!"));
		return;
	}

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("椒盐噪声效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("椒盐噪声");
	dlg.m_sHelpTitle = _T("椒盐噪声参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入噪声比例"); //参数1 噪声比例
	//设置默认值
	dlg.m_P1 = 0.05;
	 
	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0 || dlg.m_P1 >1) {
			AfxMessageBox(_T("噪声比例请控制在0-1之间!"));
			return;
		}
		double noiseRate = dlg.m_P1;
		BmpCommonOp bmpcommonop;
		BYTE * OutputImage = bmpcommonop.AddPepperSaltNoise(m_pImage, noiseRate, 0, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
		USES_CONVERSION;
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);
		numPicture = 2;
		delete[] OutputImage;
		Invalidate();
	}


	
	
	
}


//******************椒噪声*****************//
void CImageProcessView::OnPepperNoise()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能添加噪声!"));
		return;
	}

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("椒噪声效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("椒噪声");
	dlg.m_sHelpTitle = _T("椒噪声参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入噪声比例"); //参数1 噪声比例
	//设置默认值
	dlg.m_P1 = 0.25;

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1<0 || dlg.m_P1 >1) {
			AfxMessageBox(_T("噪声比例请控制在0-1之间!"));
			return;
		}
		double noiseRate = dlg.m_P1;
		BmpCommonOp bmpcommonop;
		BYTE * OutputImage = bmpcommonop.AddPepperSaltNoise(m_pImage, noiseRate, 2, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);
		USES_CONVERSION;
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);
		numPicture = 2;
		delete[] OutputImage;
		Invalidate();
	}
}

 
//******************逆谐波均值滤波器*****************//
void CImageProcessView::OnContraharmonicMeanFilter()
{
	// TODO: 在此添加命令处理程序代码

	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能滤波!"));
		return;
	}

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("逆谐波均值滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("逆谐波均值滤波");
	dlg.m_sHelpTitle = _T("逆谐波均值滤波参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	dlg.m_bShowP3 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入m"); //参数1 m
	dlg.m_P2Text = _T("请输入n"); //参数2 n
	dlg.m_P3Text = _T("请输入Q"); //参数3 q
	//设置默认值
	dlg.m_P1 = 3;
	dlg.m_P2 = 3;
	dlg.m_P3 = 0;

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_P1 <= 0 || dlg.m_P2 <= 0 || int(dlg.m_P1) % 2 == 0 || int(dlg.m_P2) % 2 == 0) {
			AfxMessageBox(_T("输入m和n必须为正奇数!"), MB_OK, 0);
			return;
		}
		BYTE *OutputImage = new BYTE[m_nImage];
		BmpCommonOp bmpcommonop;
		bmpcommonop.ContraharmonicMeanFilter(m_pImage, OutputImage, dlg.m_P1, dlg.m_P2, dlg.m_P3, m_nImage, m_nWidth, m_nHeight, bih.biBitCount, m_nLineByte);

		//保存图像数据到文件
		USES_CONVERSION;
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, OutputImage, m_nImage);
		numPicture = 2;
		delete[] OutputImage;
		Invalidate();
	}

 

}


//******************修正的阿尔法均值滤波*****************//
void CImageProcessView::OnAlphaTrimmedMeanFilter()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行修正的阿尔法均值滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("修正的阿尔法均值滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("修正的阿尔法均值滤波");
	dlg.m_sHelpTitle = _T("修正的阿尔法均值滤波参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	dlg.m_bShowP3 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入m"); //参数1 m
	dlg.m_P2Text = _T("请输入n"); //参数2 n
	dlg.m_P3Text = _T("请输入2d"); //参数3 d
	//设置默认值
	dlg.m_P1 = 5;//m
	dlg.m_P2 = 5;//n
	dlg.m_P3 = 5;//d

	if (dlg.DoModal() == IDOK) {

		if (dlg.m_P1 <= 0 || dlg.m_P2 <= 0 || int(dlg.m_P1) % 2 == 0 || int(dlg.m_P2) % 2 == 0) {
			AfxMessageBox(_T("输入m和n必须为正奇数!"), MB_OK, 0);
			return;
		}
		if (dlg.m_P3<0 || dlg.m_P3 > int(dlg.m_P1*dlg.m_P2)) {
			AfxMessageBox(_T("输入d请在0-m*n之间"));
			return;
		}

		AlphaTrimmedMeanFilter(dlg.m_P1, dlg.m_P2, dlg.m_P3);//

	}
}


//******************自适应中值滤波*****************//
void CImageProcessView::OnAdaptiveMedianFilter()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行自适应中值滤波!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("自适应中值滤波效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("自适应中值滤波");
	dlg.m_sHelpTitle = _T("自适应中值滤波参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入s"); //参数1 s
	//设置默认值
	dlg.m_P1 = 7;//s

	if (dlg.DoModal() == IDOK) {

		if (dlg.m_P1<0 || dlg.m_P1 > m_nWidth || dlg.m_P1>m_nHeight){
			AfxMessageBox(_T("输入S为正整数并且不得大于图像高宽!"));
			return;
		}
		if(int(dlg.m_P1)/2 == 0) {
			AfxMessageBox(_T("输入S为奇数!"));
			return;
		}

		AdaptiveMedianFilter(int(dlg.m_P1));

	}
}





/*----------------------------------------------------------------------
								软件设置
------------------------------------------------------------------------*/

void CImageProcessView::OnRepostIssue()
{
	// TODO: 在此添加命令处理程序代码

}


void CImageProcessView::OnImproveSetting()
{
	// TODO: 在此添加命令处理程序代码
	CImproveDlg dlg;
	
	if (dlg.DoModal() == IDOK) {//写入ini文件
		if (dlg.m_bImproveYes) {
			if (WritePrivateProfileString(_T("Setting"), _T("Improve"), _T("no"), _T("./config.ini"))) 
				AfxMessageBox(_T("保存成功!"), MB_OK, 0);
		}
		else {
			if (WritePrivateProfileString(_T("Setting"), _T("Improve"), _T("yes"), _T("./config.ini")))
				AfxMessageBox(_T("保存成功!"), MB_OK, 0);
		}
	}
}



void CImageProcessView::OnUserLogin()
{
	// TODO: 在此添加命令处理程序代码
	
	//CString loginInfo, loginTime;
	//bool m_bUserlogin;
	//GetPrivateProfileString(_T("Information"), _T("Login"), _T("no"), loginInfo.GetBuffer(12), 12, _T("./config.ini"));
	//GetPrivateProfileString(_T("Information"), _T("LoginTime"), _T("0"), loginTime.GetBuffer(20), 20, _T("./config.ini"));
	// 
	//USES_CONVERSION;
	//LPCSTR loginTimeStr = (LPCSTR)T2A(loginTime);
	//int oldlogin= atoi(loginTimeStr);
	//int current = time(0);

	////30分钟有效期
	//if (loginInfo == _T("yes")  && (current - oldlogin) < 1800 )
	//	m_bUserlogin = 1;
	//else
	//	m_bUserlogin = 0;


	//CUserDlg dlg;
	//dlg.m_Userlogin = m_bUserlogin;//传递用户登录信息
	//dlg.DoModal();

}




//******************下载测试图像*****************//
void CImageProcessView::OnDownloadTestImages()
{
	// TODO: 在此添加命令处理程序代码
	CString url = _T("https://cdn.zhfsky.com/Test-Images.zip");
	CInternetSession session;
	CInternetFile* file =(CInternetFile*)session.OpenURL(url, 1, INTERNET_FLAG_TRANSFER_BINARY);

	if (file == NULL){
		file->Close();
		delete file;
		session.Close();
		MessageBox(_T("下载文件失败!"), _T("提示"), MB_ICONERROR);
		return;
	}

	CFile downFile;

	if (downFile.Open(_T("Test-Images.zip"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, NULL))
	{
		int readlen = -1;
		char buf[1024];
		while (1)
		{
			//char* buf = new char[1024];
			readlen = file->Read(buf, 1024);
			if (readlen == 0)
			{
				//delete buf;
				break;
			}
			downFile.Write(buf, readlen);
			//delete buf;
			ZeroMemory(buf, 1024);
		}
		downFile.Close();
		AfxMessageBox(_T("测试图片下载完成!"));
	}
	else
	{
		MessageBox(_T("下载文件失败!"), _T("提示"), MB_ICONERROR);
		file->Close();
		delete file;
		session.Close();
		return;
	}

	file->Close();
	delete file;
	session.Close();

}


void CImageProcessView::OnGray()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行灰度变换!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("灰度变换效果图"));
	BYTE * GraySrcImage = new BYTE[m_nImage];
	BmpCommonOp bmpcommonop;
	bmpcommonop.RGB2Gray(m_pImage, GraySrcImage, m_nWidth, m_nHeight,bih.biBitCount, m_nLineByte);
	//将BMP图像数据写入文件
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);

	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, GraySrcImage, m_nImage);

	delete[] GraySrcImage;
	numPicture = 2;
	Invalidate();

}







void CImageProcessView::OnVideoPlay()
{
	// TODO: 在此添加命令处理程序代码
	CString filter = _T("MP4|*.mp4||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, this);
	CString VidoeName;

	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (fileDlg.DoModal() == IDOK)
	{

		VidoeName = fileDlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
		EntName = fileDlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();             //将文件扩展名转换为一个小写字符
	}

	CVideoDlg videoDlg;
	videoDlg.m_vidoeUrl = VidoeName;
	videoDlg.DoModal();
}

//******************图像分割*****************//
void CImageProcessView::OnImageSeg()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行图像分割!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("图像分割效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("图像分割");
	dlg.m_sHelpTitle = _T("图像分割参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入s"); //参数1 s
							   //设置默认值
	dlg.m_P1 = 7;//s

	if (dlg.DoModal() == IDOK) {

		if (dlg.m_P1<0 || dlg.m_P1 > m_nWidth || dlg.m_P1>m_nHeight) {
			AfxMessageBox(_T("输入S为正整数并且不得大于图像高宽!"));
			return;
		}
		if (int(dlg.m_P1) / 2 == 0) {
			AfxMessageBox(_T("输入S为奇数!"));
			return;
		}

		//AdaptiveMedianFilter(int(dlg.m_P1));

	}
}

 

//******************Sobel算子*****************//
void CImageProcessView::OnSobelOperator()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行Sobel算子边缘检测!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("Sobel算子边缘检测效果图"));

	EdgeDetection(EDGE_DETECTOR_SOBEL, SMOOTH_MEAN, 0.1);

}

////******************LoG算子*****************//
//void CImageProcessView::OnLogOperator()
//{
//	// TODO: 在此添加命令处理程序代码
//}
//
////******************DoG算子*****************//
//void CImageProcessView::OnDogOperator()
//{
//	// TODO: 在此添加命令处理程序代码
//}
//
//
//void CImageProcessView::OnPrewittOperator()
//{
//	// TODO: 在此添加命令处理程序代码
//	if (numPicture == 0)
//	{
//		AfxMessageBox(_T("载入图片后才能进行Prewitt算子边缘检测!"));
//		return;
//	}
//	m_pDrawText.RemoveAll();//清除
//	m_pDrawText.Add(_T("原图"));
//	m_pDrawText.Add(_T("Prewitt算子边缘检测效果图"));
//}

//******************Canny边缘检测*****************//
void CImageProcessView::OnCannyEdgeDetaction()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行Canny边缘检测!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("Canny边缘检测效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("Canny边缘检测");
	dlg.m_sHelpTitle = _T("Canny边缘检测双阈值参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入低阈值");
	dlg.m_P2Text = _T("请输入高阈值");
	//设置默认值
	dlg.m_P1 = 90;//s
	dlg.m_P2 = 180;//s

	if (dlg.DoModal() == IDOK) {

		if (dlg.m_P1 <= 0 || dlg.m_P2 <= 0) {
			AfxMessageBox(_T("输入为正数!"));
			return;
		}
		EdgeDetection(EDGE_DETECTOR_CANNY, SMOOTH_GAUSSIAN, dlg.m_P1, dlg.m_P2);
		
	}

	
}

//******************基本全局阈值处理*****************//
void CImageProcessView::OnBasicGlobalThreshold()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行阈值处理!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("阈值处理效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("基本全局阈值处理");
	dlg.m_sHelpTitle = _T("基本全局阈值处理参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入deta"); //参数1 deta
	//设置默认值
	dlg.m_P1 = 0.01;//s

	if (dlg.DoModal() == IDOK) {

		if (dlg.m_P1<=0 ) {
			AfxMessageBox(_T("输入deta要为正数!"));
			return;
		}

		double args[] = { dlg.m_P1 };
		Thresholding(THRESHOLDING_BASIC_GLOBAL, args);//阈值处理函数

	}


}


//******************OTSU阈值处理*****************//
void CImageProcessView::OnOtsuThreshold()
{
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行OTSU阈值处理!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("OTSU阈值处理效果图"));

	Thresholding(THRESHOLDING_OTSU);//阈值处理函数
}


//******************局部阈值处理*****************//
void CImageProcessView::OnLocalThreshold()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行阈值处理!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("阈值处理效果图"));

	CCommonDlg dlg;
	//标题显示
	dlg.m_sWindowTitle = _T("基于局部均值与方差的阈值处理");
	dlg.m_sHelpTitle = _T("局部阈值处理参数设置");
	//显示控件
	dlg.m_bShowP1 = true;
	dlg.m_bShowP2 = true;
	dlg.m_bShowP3 = true;
	//参数指定
	dlg.m_P1Text = _T("请输入窗口大小");  
	dlg.m_P2Text = _T("请输入局部均值倍数, 高于此倍数将被置255"); 
	dlg.m_P3Text = _T("请输入局部方差倍数, 高于此倍数将被置255");  
	//设置默认值
	dlg.m_P1 = 5;//s
	dlg.m_P2 = 5;//s
	dlg.m_P3 = 5;//s

	if (dlg.DoModal() == IDOK) {

		if (dlg.m_P1<0 || dlg.m_P1 > m_nWidth || dlg.m_P1>m_nHeight) {
			AfxMessageBox(_T("输入窗口大小为正整数并且不得大于图像高宽!"));
			return;
		}
		if (int(dlg.m_P1) / 2 == 0) {
			AfxMessageBox(_T("输入窗口大小为奇数!"));
			return;
		}

		double args[] = { dlg.m_P1 , dlg.m_P2 , dlg.m_P3};
		Thresholding(THRESHOLDING_LOCAL, args);//阈值处理函数

	}
}



//******************形态学膨胀*****************//
void CImageProcessView::OnDilation()
{
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行处理!"));
		return;
	}

	/*for (int i = 0;i < m_nImage / 8;i++) {
		if ( (m_pImage[i] != 0) && (m_pImage[i] != 255) ) {
			AfxMessageBox(_T("请先二值化"));
			return;
		}
	}*/

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("膨胀效果图"));

	Morphologying(1);

}


//******************形态学腐蚀*****************//
void CImageProcessView::OnErosion()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行处理!"));
		return;
	}
	/*for (int i = 0;i < m_nImage / 8;i++) {
		if ( (m_pImage[i] != 0) && (m_pImage[i] != 255) ) {
			AfxMessageBox(_T("请先二值化"));
			return;
		}
	}*/

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("腐蚀效果图"));
	Morphologying(2);
	
}


//******************霍夫变换*****************//
void CImageProcessView::OnHoughTransform()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行霍夫变换!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("霍夫变换效果图"));

	for (int i = 0;i < m_nImage / 8;i++) {
		if (m_pImage[i] != 0 && m_pImage[i] != 255) {
			AfxMessageBox(_T("请先二值化"));
			return;
		}
	}

	HoughTransform();

}








//******************数字投影图*****************//
void CImageProcessView::OnDigProjection() {
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行 !"));
		return;
	}

	for (int i = 0;i < m_nImage / 8;i++) {
		if (m_pImage[i] != 0 && m_pImage[i] != 255) {
			AfxMessageBox(_T("请先二值化"));
			return;
		}
	}

	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T(" 效果图"));

	DigProjection();
}



//******************水表数字检测*****************//
void CImageProcessView::OnWaterDigifinall()
{
	// TODO: 在此添加命令处理程序代码
	//第5次作业的最终集成效果 上面的菜单只是单独拆分了功能 该项是最终效果
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行水表数字检测!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("水表数字检测效果图"));
	WaterDigifinall();
}






//******************反色处理*****************//
void CImageProcessView::OnImagePositive()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行反色处理!"));
		return;
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));
	m_pDrawText.Add(_T("图像反色处理效果图"));
	BYTE *DstImage = new BYTE[m_nImage];
	for (int i = 0; i < m_nImage; ++i) {
		DstImage[i] = 255 - m_pImage[i];
	}
	//将图像数据保存为图像
	BmpCommonOp bmpcommonop;
	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);
	bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, DstImage, m_nImage);

	//显示效果图像
	numPicture = 2;
	Invalidate();
}

//******************数字分割*****************//
void CImageProcessView::OnDigitalSegment()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能进行数字分割!"));
		return;
	}
	for (int i = 0;i < m_nImage / 8;i++) {
		if (m_pImage[i] != 0 && m_pImage[i] != 255) {
			AfxMessageBox(_T("请先二值化"));
			return;
		}
	}
	m_pDrawText.RemoveAll();//清除
	m_pDrawText.Add(_T("原图"));

	Segment seg;
	double *SrcImage = new double[m_nImage];
	//类型转换
	for (int i = 0; i < m_nImage; ++i) {
		SrcImage[i] = m_pImage[i]; //BYTE=> double 格式化输入图像数据
	}

	seg.DigitalSeg(SrcImage, bfh, bih, m_pPal, m_nWidth, m_nHeight, m_nBitCount, m_nLineByte);

	AfxMessageBox(_T("数字分割完毕, 输出在程序文件夹下!"));


}


void CImageProcessView::OnTest()
{
	// TODO: 在此添加命令处理程序代码
	//if (numPicture == 0)
	//{
	//	AfxMessageBox(_T("载入图片后才能进行测试!"));
	//	return;
	//}
	//m_pDrawText.RemoveAll();//清除
	//m_pDrawText.Add(_T("原图"));
	Test test;
	test.DigitPredict();
	
	 
 
 
 

}










