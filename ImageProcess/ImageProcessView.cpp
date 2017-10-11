
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
#include "WriteCharDlg.h"
#include "InterpolationDlg.h"
#include "RotateDlg.h"
#include "HelpDlg.h"
#include "BmpCommonOp.h"

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


		//如果原图+效果图的 宽度和 大于窗口宽度 则申请更大的窗口
		if (m_nDrawWidth + m_bmp.bmWidth < m_nWindowWidth) {
			SetScrollSizes(MM_TEXT, CSize(m_nWindowWidth , m_bmp.bmHeight + 10)); //窗口滚轮高度自适应
 
		}
		else {
			SetScrollSizes(MM_TEXT, CSize(m_nDrawWidth + m_bmp.bmWidth + 12 , m_bmp.bmHeight + 10));
			
		}
		pDC->BitBlt(m_nDrawWidth + 12, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, SRCCOPY);
		 
		
		
		dcBmp.SelectObject(pbmpOld);	//恢复临时DC的位图  
		DeleteObject(&m_bitmap);        //删除内存中的位图
		dcBmp.DeleteDC();               //删除CreateCompatibleDC得到的图片DC
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

 

	//FILE *fpo;

	////读取图像  原图还是效果图? 如果是连续操作则是效果图 
	//if (fopen_s(&fpo, BmpFileNameLin, "rb") == 0) { //如果存在效果图 则使用效果图
	//	ReadBmp(BmpNameLin);
	//	 
	//}
	//else { //如果不存在效果图 则直接使用原图数据
	//	ReadBmp(BmpName);
	//	 
	//}
	
	
	

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

				*(DstImage + j*Width + i) =  q11*(1.0 - x_x)*(1.0 - x_y) + q21*x_x*(1.0 - x_y) + q12*(1.0 - x_x)*x_y + q22*x_x*x_y;
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
	//delete[] DstImage;
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
	//8bit BMP
	//读写文件

	USES_CONVERSION;
	 
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);

	//FILE *fpo;
	////读取图像  原图还是效果图? 如果是连续操作则是效果图 
	//if (fopen_s(&fpo, BmpFileNameLin, "rb") == 0) { //如果存在效果图 则使用效果图
	//	ReadBmp(BmpNameLin);
	//	fclose(fpo);
	//}
	//else { //如果不存在效果图 则直接使用原图数据
	//	ReadBmp(BmpName);
	//	fclose(fpo);
	//}

 

	


	/*定义PA=3.14时使用的方法是arcsin(1.0/2)*6即为π*/
	double PA; //3.1415926
	PA = asin(0.5) * 6;

	double degree;
	degree = (double) PA*Angle / 180; //弧度

	int XCenter = (int)bih.biWidth / 2;  //原图中心点X坐标
	int YCenter = (int)bih.biHeight / 2; //原图中心点Y坐标


	

	//处理开始


	//源图像坐标

	/*int x_pre;
	int y_pre;*/
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
		EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();             //将文件扩展名转换为一个小写字符

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


//******************写入字符U/D*****************//
void CImageProcessView::OnWriteCharcter()
{
	// TODO: 在此添加命令处理程序代码
	
	//如果没有导入图片直接写入字符 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox(_T("载入图片后才能写入字符!"));
		return;
	}
	//定义写入字符输入对话框
	CWriteCharDlg dlg;
	//显示对话框
	if (dlg.DoModal() == IDOK ) 
	{
	 

		if (dlg.m_xPosition <= 0 || dlg.m_yPosition <= 0) {
			AfxMessageBox(_T("输入坐标必须为正整数!"), MB_OK, 0);
			return;
		}
		if (dlg.m_xPosition > m_nWidth || dlg.m_yPosition > m_nHeight) {
			AfxMessageBox(_T("输入坐标不能为超过原图长宽!"), MB_OK, 0);
			return;
		}

		if (dlg.m_wCharacter.GetLength()==0) {
			AfxMessageBox(_T("写入字符不得为空!"), MB_OK, 0);
			return;
		}

		CDC *pDc = GetDC();	 //获取当前DC
		WriteCharOnImage(pDc, BmpName, dlg.m_wCharacter, dlg.m_xPosition, dlg.m_yPosition);

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

	//显示对话框
	CInterpolationDlg dlg;
	
	if (dlg.DoModal() == IDOK) 
	{
		if (dlg.m_nWidth <= 0 || dlg.m_nHeight <= 0) {
			AfxMessageBox(_T("输入宽和高必须为正整数!"), MB_OK, 0);
			return;
		}

		BilinearInterpolation(dlg.m_nWidth, dlg.m_nHeight);
		 
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


	CRotateDlg dlg;
	//显示对话框
	if (dlg.DoModal() == IDOK)
	{

		RotateImage(dlg.m_nRotateAngle); //旋转

	}



}






//******************使用帮助*****************//
void CImageProcessView::OnHelp()
{
	// TODO: 在此添加命令处理程序代码

	CHelpDlg dlg;
	//显示对话框
	if (dlg.DoModal() == IDOK)
	{

	}
}
