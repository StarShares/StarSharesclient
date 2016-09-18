// Shape.h: interface for the CShape class. 
// 
/************************************************************************/ 
/*  
* Copyright (c) 2009* All rights reserved. visualsan 
* ATTRIBUTE:        常规几何形状绘制和效果填充 
* FILE NAME:		CShape.h 
* ABSTRACT:			可用于虚拟仪表以及位图绘制 
* CURRENT VERSION:	V1.0 
* AUTHOR:			庄三少 
* ADDRESS:          南京航空航天大学能源于动力学院 
* CONTECT:			visualsan@yahoo.cn	 
* BUILD DATA:		20/7/2009 
* COMPLETION DATE:	22/7/2009 
* PRE-VERSION:		NONE 
* PRE-AUTHOR:		NONE 
* PRE-COMPLETION DATE:	 
* NOTE:	            This source code can be used freely but without guarantee.  
					You are respon responsible for using the following codes 
					可任意修改，发布以及应用。 
                                                                     */ 
/************************************************************************/ 
////////////////////////////////////////////////////////////////////// 
#include "EasyFont.h" 
typedef UINT (CALLBACK* LPFNDLLFUNC1)(HDC,CONST PTRIVERTEX,DWORD,CONST PVOID,DWORD,DWORD); 
 
#if !defined(AFX_SHAPE_H__D2E20270_0E66_4299_AE7A_E6BABF3E5504__INCLUDED_) 
#define AFX_SHAPE_H__D2E20270_0E66_4299_AE7A_E6BABF3E5504__INCLUDED_ 
#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
 
#define  LEFT_TO_RIGHT 1 
#define  TOP_TO_BOTTOM 2 
#define  MIDDLE_TO_SIDE 3 
 
#define  TOP_MIDDLE_BOTTOM 4 
#define  LEFT_MIDDLE_RIGHT 5 
 
#define  FONT_CLOCKWISE 7 
#define  FONT_UNCLOCKWISE 8 
 
#define  TRIANGLE_STYLE_THREEPOINT  9 
#define  TRIANGLE_STYLE_TWOSIDEEQUAL  10 
#define  TRIANGLE_STYLE_THREESIDEEQUAL  11 
 
#define  RECTANGLE_STYLE_CENTERPOIT 12 
#define  RECTANGLE_STYLE_LEFTPOINT 13 
#define  RECTANGLE_STYLE_SIDELEN 14 
 
#define  LINE_STYLE_TWOPOINT 15 
#define  LINE_STYLE_POINT_LEN_ANGLE 16 
#define  LINE_STYLE_CENTERPOINT_LEN_ANGLE 17 
 
 
#define  FONT_STYLE_LINE 18 
#define  FONT_STYLE_LINE_H 19 
#define  FONT_STYLE_LINE_V 20 
#define  FONT_STYLE_CIRCLE_CHINSES 21 
#define  FONT_STYLE_CIRCLE_ABC 22 
 
///////////////////////////////////// 
#define  DRAW_TYPE_POINT  23 
 
#define  DRAW_TYPE_LINE_TWOPOINT  24 
#define  DRAW_TYPE_LINE_POINT_LEN_ANGLE  25 
#define  DRAW_TYPE_LINE_CENTERPOINT_LEN_ANGLE  26 
 
 
#define  DRAW_TYPE_FONT_LINE 27 
#define  DRAW_TYPE_FONT_LINE_H 28 
#define  DRAW_TYPE_FONT_LINE_V 29 
#define  DRAW_TYPE_FONT_CIRCLE_CHINSES 30 
#define  DRAW_TYPE_FONT_CIRCLE_ABC 31 
 
#define  DRAW_TYPE_CIRCLE  32 
#define  DRAW_TYPE_CIRCLE_SHAPE  33 
#define  DRAW_TYPE_CIRCLE_GRADIENT  34 
 
#define  DRAW_TYPE_CONE  35 
#define  DRAW_TYPE_CONE_SHAPE 36 
#define  DRAW_TYPE_CONE_GRADIENT 37 
 
#define  DRAW_TYPE_DIAMOND 38 
#define  DRAW_TYPE_DIAMOND_SHAPE 39 
#define  DRAW_TYPE_DIAMOND_GRADIENT 40 
 
#define  DRAW_TYPE_FAN  41 
#define  DRAW_TYPE_FAN_SHAPE 42 
#define  DRAW_TYPE_FAN_GRADIENT 43 
 
 
#define  DRAW_TYPE_RECTANGLE_CENTERPOIT 44 
#define  DRAW_TYPE_RECTANGLE_CENTERPOIT_SHAPE 45 
#define  DRAW_TYPE_RECTANGLE_CENTERPOIT_GRADIENT 46 
 
#define  DRAW_TYPE_RECTANGLE_LEFTPOINT 47 
#define  DRAW_TYPE_RECTANGLE_LEFTPOINT_SHAPE 48 
#define  DRAW_TYPE_RECTANGLE_LEFTPOINT_GRADIENT 49 
 
#define  DRAW_TYPE_RECTANGLE_SIDELEN 50 
#define  DRAW_TYPE_RECTANGLE_SIDELEN_SHAPE 51 
#define  DRAW_TYPE_RECTANGLE_SIDELEN_GRADIENT 52 
 
#define  DRAW_TYPE_TRIANGLE_THREEPOINT 53 
#define  DRAW_TYPE_TRIANGLE_THREEPOINT_SHAPE 54 
#define  DRAW_TYPE_TRIANGLE_THREEPOINT_GRADIENT 55 
 
#define  DRAW_TYPE_TRIANGLE_TWOSIDEEQUAL 56 
#define  DRAW_TYPE_TRIANGLE_TWOSIDEEQUAL_SHAPE 57 
#define  DRAW_TYPE_TRIANGLE_TWOSIDEEQUAL_GRADIENT 58 
 
#define  DRAW_TYPE_TRIANGLE_THREESIDEEQUAL 59 
#define  DRAW_TYPE_TRIANGLE_THREESIDEEQUAL_SHAPE 60 
#define  DRAW_TYPE_TRIANGLE_THREESIDEEQUAL_GRADIENT 61 
////////////////////////////////// 
class CShape   
{ 
 
public: 
	CShape(); 
	virtual ~CShape(); 
public: 
 
 
	/************************************************************************/ 
	/*圆弧绘制函数                                                                     */ 
	/***********************************************************************/ 
	//绘制圆环，填充一种颜色，取决于画刷,sa为圆环起始角，swa为圆弧扫过角度 
	void DrawCone(CDC *pDC,POINT cp,float r1,float r2,float sa,float swa); 
	//绘制圆环轮廓颜色，颜色取决于画笔 
	void DrawConeShape(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa);//绘制轮廓 
	//绘制渐变圆环,从内到颜色逐渐变化 
	void DrawConeGradientSideToSide(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa, 
		COLORREF nShadowBeginColor,COLORREF nShadowEndColor); 
	//绘制渐变圆环,从中心到边逐渐变化 
	void DrawConeGradientCenterToSide(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa,COLORREF nCenterColor,COLORREF nSideColor); 
	//绘制圆弧，圆心和半径,颜色取决于画笔 
	void DrawCircleShape(CDC *pDC,POINT pCenter,double r); 
	//绘制圆弧，圆心和半径,画笔填充 
	void DrawCircle(CDC *pDC,POINT pCenter,double r); 
	//绘制圆形 
	void DrawCircleGradient(CDC *pDC,POINT pCenter,double r,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE); 
	/************************************************************************/ 
	/* 扇形绘制函数                                                                     */ 
	/************************************************************************/ 
	 
	//绘制扇形，填充单一颜色，取决于画刷 
	void DrawFan(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge); 
	//绘制扇形轮廓，为单一颜色，不填充，颜色取决于画笔 
	void DrawFanShape(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge); 
	//绘制扇形轮廓，颜色为从中心到边渐变 
	void DrawFanGradientSideToSide(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge,COLORREF nShadowBeginColor,COLORREF nShadowEndColor); 
	//绘制扇形轮廓，颜色为从中心到两边渐变 
	void DrawFanGradientCenterToSide(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge,COLORREF nCenterColor,COLORREF nSideColor); 
 
	/************************************************************************/ 
	/* 绘制三角形函数                                                                     */ 
	/************************************************************************/ 
	//绘制三角形，输入三点，颜色由画笔决定，不填充 
	void DrawTriangleShapeFromThreePoint(CDC *pDC,POINT p1,POINT p2,POINT p3); 
	//绘制三角形，输入三点，用当前画笔填充填充 
	void DrawTriangleFromThreePoint(CDC *pDC,POINT p1,POINT p2,POINT p3); 
	//绘制三角形，从边到中心颜色渐变 
	void DrawTriangleFromThreePointGradientCenterToSide(CDC *pDC,POINT p1,POINT p2,POINT p3, 
		COLORREF cP1,COLORREF cP2,COLORREF cP3 ); 
 
	//绘制等腰三角形，参数由底边长度，底边中点和高长度决定，位置由高线与x轴夹角决定。颜色由画笔决定，不填充 
	void DrawSpecialTriangleShapeTwoSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double H,double hAng); 
	//绘制等腰三角形，参数由底边长度，底边中点和高长度决定，位置由高线与x轴夹角决定。颜色由画刷填充 
	void DrawSpecialTriangleTwoSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double H,double hAng); 
    //绘制等腰三角形，参数由底边长度，底边中点和高长度决定，位置由高线与x轴夹角决定。颜色渐变 
	void DrawSpecialTriangleTwoSideEqualGradientCenterToSide(CDC *pDC,POINT middlePoint, 
		double upSideLen,double H,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3  ); 
 
 
	//绘制等边三角形，参数由底边长度，底边中点，位置由高线与x轴夹角决定。颜色由画笔决定，不填充 
	void DrawSpecialTriangleShapeThreeSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double hAng); 
	//绘制等边三角形，参数由底边长度，底边中点，位置由高线与x轴夹角决定。颜色由画刷填充 
	void DrawSpecialTriangleThreeSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double hAng); 
	//绘制等边三角形，参数由底边长度，底边中点，位置由高线与x轴夹角决定。三点渐变颜色 
	void DrawSpecialTriangleShapeThreeSideEqualGradient(CDC *pDC,POINT middlePoint, 
		double upSideLen,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3); 
	//绘制等边三角形，参数由底边长度，底边中点，位置由高线与x轴夹角决定。三点渐变颜色 
	void DrawSpecialTriangleThreeSideEqualGradient(CDC *pDC,POINT middlePoint, 
		double upSideLen,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3); 
 
 
 
	/************************************************************************/ 
	/* 菱形绘制                                                                     */ 
	/************************************************************************/ 
	//根据中心，长短轴，以及长轴和x方向夹角绘制轮廓,绘制轮廓，不填充 
	// longAxisDivideRate和shortAxisDivideRate分别为长短轴的风格率，为上段比例和右两段比例 
	void DrawDiamondShape(CDC *pDC,CPoint centerPoint,double longAxis, 
		double shortAxis,double longAxisAngToX,double longAxisDivideRate=0.5,double shortAxisDivideRate=0.5); 
	//根据中心，长短轴，以及长轴和x方向夹角绘制轮廓,绘制轮廓，单色填充，取决于画刷 
	// longAxisDivideRate和shortAxisDivideRate分别为长短轴的风格率，为上段比例和右两段比例 
	void DrawDiamond(CDC *pDC,CPoint centerPoint,double longAxis, 
		double shortAxis,double longAxisAngToX,double longAxisDivideRate=0.5,double shortAxisDivideRate=0.5); 
	//根据中心，长短轴，以及长轴和x方向夹角绘制轮廓,绘制轮廓，颜色渐变 
	// longAxisDivideRate和shortAxisDivideRate分别为长短轴的风格率，为上段比例和右两段比例 
	void DrawDiamondGradient(CDC *pDC,CPoint centerPoint,double longAxis, 
		double shortAxis,double longAxisAngToX,COLORREF nShadowBeginColor,COLORREF nShadowEndColor , 
		int style=LEFT_TO_RIGHT,double longAxisDivideRate=0.5,double shortAxisDivideRate=0.5); 
 
	/************************************************************************/ 
	/* 矩形绘制                                                                     */ 
	/************************************************************************/ 
	//绘制矩形，不填充，颜色取决于画笔，wideAngleToX为宽度方向和X轴夹角 
	void DrawRectangleShape(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX); 
	//绘制矩形，不填充，颜色取决于画笔,对角点和一般和X轴的夹角 
	void DrawRectangleShape(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX); 
	//绘制矩形，不填充，颜色取决于画笔,一边长度和一边对x轴的夹角及其该边中点，该边高线长度 
	void DrawRectangleShape(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H); 
 
 
 
	//绘制矩形，画刷填充，wideAngleToX为宽度方向和X轴夹角 
	void DrawRectangle(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX); 
	//绘制矩形，画刷填充，对角点和一般和X轴的夹角 
	void DrawRectangle(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX); 
	//绘制矩形，画刷填充,一边长度和一边对x轴的夹角及其该边中点，该边高线长度 
	void DrawRectangle(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H); 
 
 
	//绘制矩形，画刷填充，wideAngleToX为宽度方向和X轴夹角 
	void DrawRectangleGradient(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX 
		,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE ); 
    //绘制矩形，画刷填充，wideAngleToX为宽度方向和X轴夹角 
	void DrawRectangleGradient(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX 
		,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE ); 
    //绘制矩形，画刷填充，wideAngleToX为宽度方向和X轴夹角 
	void DrawRectangleGradient(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H 
		,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE ); 
 
	/************************************************************************/ 
	/* 多边形绘制                                                                     */ 
	/************************************************************************/ 
	//绘制多边形轮廓，根据中心点，边长，边数，和该边和中心连线夹角 
	void DrawPolygonShape(CDC *pDC,POINT centerPoint,double sideLen,int sideNum,double centerToSideAngToX); 
	//绘制多边形轮廓，点数决定 
	void DrawPolygonShape(CDC *pDC,POINT *Point,int pointNum); 
	//绘制多边形轮廓，根据中心点，边长，边数，和该边和中心连线夹角,画刷填充 
	void DrawPolygon(CDC *pDC,POINT centerPoint,double sideLen,int sideNum,double centerToSideAngToX); 
	//绘制多边形轮廓，点数决定，画刷填充 
	void DrawPolygon(CDC *pDC,POINT *Point,int pointNum); 
 
 
	/************************************************************************/ 
	/* 基本几何图形                                                                     */ 
	/************************************************************************/ 
	void DrawPoint(CDC *pDC,CPoint pos,COLORREF pointColor,int size=0); 
	void DrawLine_TwoPoint(CDC *pDC,CPoint pStart,CPoint pEnd,COLORREF lineColor,int size=0,int lineStyle=PS_SOLID); 
	void DrawLine_Point_Len_Angle(CDC *pDC,CPoint pStart,double Len,COLORREF lineColor, 
		double AngToX,int size=0,int lineStyle=PS_SOLID); 
	void DrawLine_CenterPoint_Len_Angle(CDC *pDC,CPoint centerStart,double startLen,double endLen,COLORREF lineColor, 
		double AngToX,int size=0,int lineStyle=PS_SOLID); 
 
	/************************************************************************/ 
	/* 文字处理函数                                                                     */ 
	/************************************************************************/ 
	//直线输出文字 
	void DrawLineText(CDC *pDC,POINT pos,CString str,COLORREF c=RGB(0,0,0));//一定角度的文字 
	void DrawLineTextH(CDC *pDC,POINT pos,CString str,COLORREF c=RGB(0,0,0));//水平写文字,角度无作用 
	void DrawLineTextV(CDC *pDC,POINT pos,CString str,COLORREF c=RGB(0,0,0));//垂直写文字,角度无作用 
 
 
	//设置文字属性 
	void RestFont();//设置文字为默认值 
	void SetFontAngle(double Angle);//设置文字角度，为度数 
	void SwtFontHeight(int Height);//设置文字高度 
	void SetFontWide(int wide);//设置文字宽度 
	void SetFontDlg();//根据文字设置对话框来设置字体 
    void SetFontName(CString name="宋体");//设置文字名称 
 
	//m_nDis为字体间间距，该函数只能用于汉字输出 
	void DrawCircleChineseText(CDC *pDC,POINT centerPoint,double r,double startAngToX, 
		CString str,COLORREF c=RGB(0,0,0),double m_nDis=10 ,int style=FONT_UNCLOCKWISE); 
	////////该函数只能非汉字输出 
	void DrawCircleABCText(CDC *pDC,POINT centerPoint,double r,double startAngToX, 
		CString str,COLORREF c=RGB(0,0,0),double m_nDis=5 ,int style=FONT_UNCLOCKWISE); 
	/************************************************************************/ 
	/*                                                                      */ 
	/************************************************************************/ 
	//绘制背景颜色 
	void DrawBkColor(CDC *pDC,CRect R,COLORREF c); 
 
 
 
private: 
	LPFNDLLFUNC1 handle_GradientFill; 
	HINSTANCE hinst_msimg32; 
	bool m_bGradientFillInit; 
	void _DrawRect(CDC *pDC,CRect rect,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=LEFT_TO_RIGHT); 
	void _DrawTriangle(CDC *pDC,POINT P1,POINT P2,POINT P3, 
		COLORREF cP1,COLORREF cP2,COLORREF cP3); 
	CEasyFont m_Font; 
}; 
 
#endif // !defined(AFX_SHAPE_H__D2E20270_0E66_4299_AE7A_E6BABF3E5504__INCLUDED_) 
 
// EasyFont.h: interface for the CEasyFont class. 
// 
////////////////////////////////////////////////////////////////////// 