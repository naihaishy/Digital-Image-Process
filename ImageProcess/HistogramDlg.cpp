// HistogramDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"


// CHistogramDlg 对话框

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HISTOGRAM, pParent)
{

	HistogramColor = NULL;
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistogramDlg 消息处理程序


BOOL CHistogramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(m_sWindowTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CHistogramDlg::OnPaint()
{
	 
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	 
 
 
	//获取窗口及绘制图形的区域
	CWnd *pWnd = GetDlgItem(IDC_STATIC_HISTOGRAM);
	CDC *pDC = pWnd->GetDC();
	 
	CRect rectpic;
	pWnd->GetWindowRect(&rectpic);

	int x, y;
	x = rectpic.Width();//X轴
	y = rectpic.Height();//Y轴


	int x_offset = 10;//设置偏置 偏置保持直方图在坐标系下合理的位置
	int y_offset = 10;

	//画笔设置
	CPen *RedPen = new CPen();
 
	RedPen->CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); //创建实心画笔，粗度为1，颜色为红色
													
	CGdiObject *RedOlderPen = pDC->SelectObject(RedPen); // 选择新画笔，并将旧画笔的指针保存到RedOlderPen   



	double max = 0; //统计中的最大值
	for (int i = 0; i < 256; i++) {
		if (HistogramColor[i] > max) {
			max = HistogramColor[i];
		}
	}


	//绘制图形
	/*说明：由于windows在扫描和存储图像是是以4个字节为内存单元 
		因此图像字节对齐中 默认以0或255填充（主要是在memset的第二个值 ），
		故0的比例可能是最大的，因此对于图像宽度不是4的倍数的将在像素为0或255处出现统计峰值
	*/
	for (int i = 0; i<256; i++)
	{
		int y_Position = ((double)HistogramColor[i] / max * (y-y_offset));//按比例缩放到Y轴  y_Position小于Y 因此不必进行越界处理
		int x_Position = (double (i) /256) *(x- x_offset); //按比例缩放到X轴								 
		pDC->MoveTo(x_Position, y-1);
		pDC->LineTo(x_Position, y - y_Position);

	}


	//恢复以前画笔
	pDC->SelectObject(RedOlderPen);
	delete RedPen;
	ReleaseDC(pDC);

}



