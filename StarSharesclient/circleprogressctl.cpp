
#include "stdafx.h"
#include "circleprogressctl.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMatrixStatic

CCircleProgressCtl::CCircleProgressCtl()
{
	roundColor = RGB(223,243,255);
	roundProgressColor = RGB(27,158,250);
	roundWidth = 5;
	max  = 100;
	progress = 0;
}

CCircleProgressCtl::~CCircleProgressCtl()
{

}


BEGIN_MESSAGE_MAP(CCircleProgressCtl, CStatic)
	//{{AFX_MSG_MAP(CCircleProgressCtl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_PAINT()
	//ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////


void CCircleProgressCtl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	int radius = rc.Width() < rc.Height() ? rc.Width()/ 2 : rc.Height() / 2;
	radius -= roundWidth;
	POINT pt = rc.CenterPoint();

	Graphics graphics(dc);

	dc.FillSolidRect(&rc, RGB(255, 255, 255));

	Gdiplus::FontFamily fontFamily(L"宋体");
	Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
	PointF pointF(40, 40);
	SolidBrush solidBrush(Color(255, 169, 169, 169));
	WCHAR str[256] = {0};
	wcscpy(str, L"认购进度：");
	
	RectF rtGdiplus;//计算消息主题的宽度
	graphics.MeasureString(str, (INT)wcslen(str), &font, pointF, &rtGdiplus); 

	float nChordLen = sqrt(24.0f) / 5.0f * 2 * radius;
	PointF ptLeft(pt.x - nChordLen / 2.0f, pt.y - radius / 5.0f - 10);

	float left = (nChordLen - rtGdiplus.Width) / 2.0f;
	ptLeft.X += left + 8;

	graphics.DrawString(str, (INT)wcslen(str), &font, ptLeft, &solidBrush);
	
	wsprintfW(str, L"%d", progress);
	//wcscpy(str, L"83");

	Gdiplus::Font font2(&fontFamily, 24, FontStyleRegular, UnitPixel);
	graphics.MeasureString(str, (INT)wcslen(str), &font2, pointF, &rtGdiplus); 
	ptLeft.X = pt.x - nChordLen / 2.0f;
	ptLeft.Y = pt.y + radius / 5.0f - 10;

	left =  (nChordLen - rtGdiplus.Width) / 2.0f;
	ptLeft.X += left ;
	SolidBrush blueBrush(Color(255, GetRValue(roundProgressColor), GetGValue(roundProgressColor), GetBValue(roundProgressColor)));
	graphics.DrawString(str, (INT)wcslen(str), &font2, ptLeft, &blueBrush);

	SolidBrush greenBrush(Color(255, GetRValue(roundColor), GetGValue(roundColor), GetBValue(roundColor)));
	wcscpy(str, L"%");
	Gdiplus::FontFamily fontFamily2(L"微软雅黑");
	Gdiplus::Font font3(&fontFamily2,12, FontStyleRegular, UnitPixel);
	PointF ptRight(ptLeft.X + rtGdiplus.Width - 4, ptLeft.Y + 8 );
	graphics.DrawString(str, (INT)wcslen(str), &font3, ptRight, &blueBrush);

	if(progress > max)
	{
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);//抗锯齿 
		//外圆
		Gdiplus::Pen pen(Gdiplus::Color(255, GetRValue(roundColor), GetGValue(roundColor), GetBValue(roundColor)), roundWidth);
		graphics.DrawEllipse(&pen, pt.x - radius, pt.y - radius, radius * 2, radius * 2);

		int nAngle = (int)(1.0f * max / max * 360.0f);
		Gdiplus::Pen penBlue(Gdiplus::Color(255, GetRValue(roundProgressColor), GetGValue(roundProgressColor), GetBValue(roundProgressColor)), roundWidth);
		graphics.DrawArc(&penBlue, pt.x - radius, pt.y - radius, radius * 2, radius * 2, 90, nAngle);
	}
	else
	{
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);//抗锯齿 
		//外圆
		Gdiplus::Pen pen(Gdiplus::Color(255, GetRValue(roundColor), GetGValue(roundColor), GetBValue(roundColor)), roundWidth);
		graphics.DrawEllipse(&pen, pt.x - radius, pt.y - radius, radius * 2, radius * 2);

		int nAngle = (int)(1.0f * progress / max * 360.0f);
		Gdiplus::Pen penBlue(Gdiplus::Color(255, GetRValue(roundProgressColor), GetGValue(roundProgressColor), GetBValue(roundProgressColor)), roundWidth);
		graphics.DrawArc(&penBlue, pt.x - radius, pt.y - radius, radius * 2, radius * 2, 90, nAngle);
	}
	
}

int CCircleProgressCtl::GetProgress()
{
	return progress;
}

void CCircleProgressCtl::SetProgress(int percent)
{
	if(percent < 0)
		return;
	progress =  percent;
	Invalidate(TRUE);
}

BOOL CCircleProgressCtl::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}


