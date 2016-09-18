// Shape.h: interface for the CShape class. 
// 
/************************************************************************/ 
/*  
* Copyright (c) 2009* All rights reserved. visualsan 
* ATTRIBUTE:        ���漸����״���ƺ�Ч����� 
* FILE NAME:		CShape.h 
* ABSTRACT:			�����������Ǳ��Լ�λͼ���� 
* CURRENT VERSION:	V1.0 
* AUTHOR:			ׯ���� 
* ADDRESS:          �Ͼ����պ����ѧ��Դ�ڶ���ѧԺ 
* CONTECT:			visualsan@yahoo.cn	 
* BUILD DATA:		20/7/2009 
* COMPLETION DATE:	22/7/2009 
* PRE-VERSION:		NONE 
* PRE-AUTHOR:		NONE 
* PRE-COMPLETION DATE:	 
* NOTE:	            This source code can be used freely but without guarantee.  
					You are respon responsible for using the following codes 
					�������޸ģ������Լ�Ӧ�á� 
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
	/*Բ�����ƺ���                                                                     */ 
	/***********************************************************************/ 
	//����Բ�������һ����ɫ��ȡ���ڻ�ˢ,saΪԲ����ʼ�ǣ�swaΪԲ��ɨ���Ƕ� 
	void DrawCone(CDC *pDC,POINT cp,float r1,float r2,float sa,float swa); 
	//����Բ��������ɫ����ɫȡ���ڻ��� 
	void DrawConeShape(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa);//�������� 
	//���ƽ���Բ��,���ڵ���ɫ�𽥱仯 
	void DrawConeGradientSideToSide(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa, 
		COLORREF nShadowBeginColor,COLORREF nShadowEndColor); 
	//���ƽ���Բ��,�����ĵ����𽥱仯 
	void DrawConeGradientCenterToSide(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa,COLORREF nCenterColor,COLORREF nSideColor); 
	//����Բ����Բ�ĺͰ뾶,��ɫȡ���ڻ��� 
	void DrawCircleShape(CDC *pDC,POINT pCenter,double r); 
	//����Բ����Բ�ĺͰ뾶,������� 
	void DrawCircle(CDC *pDC,POINT pCenter,double r); 
	//����Բ�� 
	void DrawCircleGradient(CDC *pDC,POINT pCenter,double r,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE); 
	/************************************************************************/ 
	/* ���λ��ƺ���                                                                     */ 
	/************************************************************************/ 
	 
	//�������Σ���䵥һ��ɫ��ȡ���ڻ�ˢ 
	void DrawFan(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge); 
	//��������������Ϊ��һ��ɫ������䣬��ɫȡ���ڻ��� 
	void DrawFanShape(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge); 
	//����������������ɫΪ�����ĵ��߽��� 
	void DrawFanGradientSideToSide(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge,COLORREF nShadowBeginColor,COLORREF nShadowEndColor); 
	//����������������ɫΪ�����ĵ����߽��� 
	void DrawFanGradientCenterToSide(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge,COLORREF nCenterColor,COLORREF nSideColor); 
 
	/************************************************************************/ 
	/* ���������κ���                                                                     */ 
	/************************************************************************/ 
	//���������Σ��������㣬��ɫ�ɻ��ʾ���������� 
	void DrawTriangleShapeFromThreePoint(CDC *pDC,POINT p1,POINT p2,POINT p3); 
	//���������Σ��������㣬�õ�ǰ���������� 
	void DrawTriangleFromThreePoint(CDC *pDC,POINT p1,POINT p2,POINT p3); 
	//���������Σ��ӱߵ�������ɫ���� 
	void DrawTriangleFromThreePointGradientCenterToSide(CDC *pDC,POINT p1,POINT p2,POINT p3, 
		COLORREF cP1,COLORREF cP2,COLORREF cP3 ); 
 
	//���Ƶ��������Σ������ɵױ߳��ȣ��ױ��е�͸߳��Ⱦ�����λ���ɸ�����x��нǾ�������ɫ�ɻ��ʾ���������� 
	void DrawSpecialTriangleShapeTwoSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double H,double hAng); 
	//���Ƶ��������Σ������ɵױ߳��ȣ��ױ��е�͸߳��Ⱦ�����λ���ɸ�����x��нǾ�������ɫ�ɻ�ˢ��� 
	void DrawSpecialTriangleTwoSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double H,double hAng); 
    //���Ƶ��������Σ������ɵױ߳��ȣ��ױ��е�͸߳��Ⱦ�����λ���ɸ�����x��нǾ�������ɫ���� 
	void DrawSpecialTriangleTwoSideEqualGradientCenterToSide(CDC *pDC,POINT middlePoint, 
		double upSideLen,double H,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3  ); 
 
 
	//���Ƶȱ������Σ������ɵױ߳��ȣ��ױ��е㣬λ���ɸ�����x��нǾ�������ɫ�ɻ��ʾ���������� 
	void DrawSpecialTriangleShapeThreeSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double hAng); 
	//���Ƶȱ������Σ������ɵױ߳��ȣ��ױ��е㣬λ���ɸ�����x��нǾ�������ɫ�ɻ�ˢ��� 
	void DrawSpecialTriangleThreeSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double hAng); 
	//���Ƶȱ������Σ������ɵױ߳��ȣ��ױ��е㣬λ���ɸ�����x��нǾ��������㽥����ɫ 
	void DrawSpecialTriangleShapeThreeSideEqualGradient(CDC *pDC,POINT middlePoint, 
		double upSideLen,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3); 
	//���Ƶȱ������Σ������ɵױ߳��ȣ��ױ��е㣬λ���ɸ�����x��нǾ��������㽥����ɫ 
	void DrawSpecialTriangleThreeSideEqualGradient(CDC *pDC,POINT middlePoint, 
		double upSideLen,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3); 
 
 
 
	/************************************************************************/ 
	/* ���λ���                                                                     */ 
	/************************************************************************/ 
	//�������ģ������ᣬ�Լ������x����нǻ�������,��������������� 
	// longAxisDivideRate��shortAxisDivideRate�ֱ�Ϊ������ķ���ʣ�Ϊ�϶α����������α��� 
	void DrawDiamondShape(CDC *pDC,CPoint centerPoint,double longAxis, 
		double shortAxis,double longAxisAngToX,double longAxisDivideRate=0.5,double shortAxisDivideRate=0.5); 
	//�������ģ������ᣬ�Լ������x����нǻ�������,������������ɫ��䣬ȡ���ڻ�ˢ 
	// longAxisDivideRate��shortAxisDivideRate�ֱ�Ϊ������ķ���ʣ�Ϊ�϶α����������α��� 
	void DrawDiamond(CDC *pDC,CPoint centerPoint,double longAxis, 
		double shortAxis,double longAxisAngToX,double longAxisDivideRate=0.5,double shortAxisDivideRate=0.5); 
	//�������ģ������ᣬ�Լ������x����нǻ�������,������������ɫ���� 
	// longAxisDivideRate��shortAxisDivideRate�ֱ�Ϊ������ķ���ʣ�Ϊ�϶α����������α��� 
	void DrawDiamondGradient(CDC *pDC,CPoint centerPoint,double longAxis, 
		double shortAxis,double longAxisAngToX,COLORREF nShadowBeginColor,COLORREF nShadowEndColor , 
		int style=LEFT_TO_RIGHT,double longAxisDivideRate=0.5,double shortAxisDivideRate=0.5); 
 
	/************************************************************************/ 
	/* ���λ���                                                                     */ 
	/************************************************************************/ 
	//���ƾ��Σ�����䣬��ɫȡ���ڻ��ʣ�wideAngleToXΪ��ȷ����X��н� 
	void DrawRectangleShape(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX); 
	//���ƾ��Σ�����䣬��ɫȡ���ڻ���,�Խǵ��һ���X��ļн� 
	void DrawRectangleShape(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX); 
	//���ƾ��Σ�����䣬��ɫȡ���ڻ���,һ�߳��Ⱥ�һ�߶�x��ļнǼ���ñ��е㣬�ñ߸��߳��� 
	void DrawRectangleShape(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H); 
 
 
 
	//���ƾ��Σ���ˢ��䣬wideAngleToXΪ��ȷ����X��н� 
	void DrawRectangle(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX); 
	//���ƾ��Σ���ˢ��䣬�Խǵ��һ���X��ļн� 
	void DrawRectangle(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX); 
	//���ƾ��Σ���ˢ���,һ�߳��Ⱥ�һ�߶�x��ļнǼ���ñ��е㣬�ñ߸��߳��� 
	void DrawRectangle(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H); 
 
 
	//���ƾ��Σ���ˢ��䣬wideAngleToXΪ��ȷ����X��н� 
	void DrawRectangleGradient(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX 
		,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE ); 
    //���ƾ��Σ���ˢ��䣬wideAngleToXΪ��ȷ����X��н� 
	void DrawRectangleGradient(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX 
		,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE ); 
    //���ƾ��Σ���ˢ��䣬wideAngleToXΪ��ȷ����X��н� 
	void DrawRectangleGradient(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H 
		,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg=MIDDLE_TO_SIDE ); 
 
	/************************************************************************/ 
	/* ����λ���                                                                     */ 
	/************************************************************************/ 
	//���ƶ�����������������ĵ㣬�߳����������͸ñߺ��������߼н� 
	void DrawPolygonShape(CDC *pDC,POINT centerPoint,double sideLen,int sideNum,double centerToSideAngToX); 
	//���ƶ������������������ 
	void DrawPolygonShape(CDC *pDC,POINT *Point,int pointNum); 
	//���ƶ�����������������ĵ㣬�߳����������͸ñߺ��������߼н�,��ˢ��� 
	void DrawPolygon(CDC *pDC,POINT centerPoint,double sideLen,int sideNum,double centerToSideAngToX); 
	//���ƶ����������������������ˢ��� 
	void DrawPolygon(CDC *pDC,POINT *Point,int pointNum); 
 
 
	/************************************************************************/ 
	/* ��������ͼ��                                                                     */ 
	/************************************************************************/ 
	void DrawPoint(CDC *pDC,CPoint pos,COLORREF pointColor,int size=0); 
	void DrawLine_TwoPoint(CDC *pDC,CPoint pStart,CPoint pEnd,COLORREF lineColor,int size=0,int lineStyle=PS_SOLID); 
	void DrawLine_Point_Len_Angle(CDC *pDC,CPoint pStart,double Len,COLORREF lineColor, 
		double AngToX,int size=0,int lineStyle=PS_SOLID); 
	void DrawLine_CenterPoint_Len_Angle(CDC *pDC,CPoint centerStart,double startLen,double endLen,COLORREF lineColor, 
		double AngToX,int size=0,int lineStyle=PS_SOLID); 
 
	/************************************************************************/ 
	/* ���ִ�����                                                                     */ 
	/************************************************************************/ 
	//ֱ��������� 
	void DrawLineText(CDC *pDC,POINT pos,CString str,COLORREF c=RGB(0,0,0));//һ���Ƕȵ����� 
	void DrawLineTextH(CDC *pDC,POINT pos,CString str,COLORREF c=RGB(0,0,0));//ˮƽд����,�Ƕ������� 
	void DrawLineTextV(CDC *pDC,POINT pos,CString str,COLORREF c=RGB(0,0,0));//��ֱд����,�Ƕ������� 
 
 
	//������������ 
	void RestFont();//��������ΪĬ��ֵ 
	void SetFontAngle(double Angle);//�������ֽǶȣ�Ϊ���� 
	void SwtFontHeight(int Height);//�������ָ߶� 
	void SetFontWide(int wide);//�������ֿ�� 
	void SetFontDlg();//�����������öԻ������������� 
    void SetFontName(CString name="����");//������������ 
 
	//m_nDisΪ������࣬�ú���ֻ�����ں������ 
	void DrawCircleChineseText(CDC *pDC,POINT centerPoint,double r,double startAngToX, 
		CString str,COLORREF c=RGB(0,0,0),double m_nDis=10 ,int style=FONT_UNCLOCKWISE); 
	////////�ú���ֻ�ܷǺ������ 
	void DrawCircleABCText(CDC *pDC,POINT centerPoint,double r,double startAngToX, 
		CString str,COLORREF c=RGB(0,0,0),double m_nDis=5 ,int style=FONT_UNCLOCKWISE); 
	/************************************************************************/ 
	/*                                                                      */ 
	/************************************************************************/ 
	//���Ʊ�����ɫ 
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