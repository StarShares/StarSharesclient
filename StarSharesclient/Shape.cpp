// Shape.cpp: implementation of the CShape class.   
//   
//////////////////////////////////////////////////////////////////////   
/************************************************************************/   
/*   
* Copyright (c) 2009* All rights reserved. visualsan  
* ATTRIBUTE:        常规几何形状绘制和效果填充  
* FILE NAME:        CShape.cpp  
* ABSTRACT:         可用于虚拟仪表以及位图绘制  
* CURRENT VERSION:  V1.0  
* AUTHOR:           庄三少  
* ADDRESS:          南京航空航天大学能源于动力学院  
* CONTECT:          visualsan@yahoo.cn    
* BUILD DATA:       20/7/2009  
* COMPLETION DATE:  22/7/2009  
* PRE-VERSION:      NONE  
* PRE-AUTHOR:       NONE  
* PRE-COMPLETION DATE:    
* NOTE:             This source code can be used freely but without guarantee.   
                    You are respon responsible for using the following codes  
                    可任意修改，发布以及应用。  
                                                                     */   
/************************************************************************/   
#include "stdafx.h"   
#include "Shape.h"   
#include <math.h>   
   
#ifdef _DEBUG   
#undef THIS_FILE   
static char THIS_FILE[]=__FILE__;   
#define new DEBUG_NEW   
#endif   
   
#define  pi 3.1415926   
//////////////////////////////////////////////////////////////////////   
// Construction/Destruction   
//////////////////////////////////////////////////////////////////////   
   
CShape::CShape()   
{   
    m_bGradientFillInit=false;   
    hinst_msimg32=NULL;   
    hinst_msimg32 = LoadLibrary( "msimg32.dll" );   
    if(hinst_msimg32)   
    {   
        m_bGradientFillInit = TRUE;     
        handle_GradientFill = ((LPFNDLLFUNC1) GetProcAddress( hinst_msimg32, "GradientFill" ));   
    }   
   
   
}   
   
CShape::~CShape()   
{   
    if (m_bGradientFillInit)   
    {   
        FreeLibrary( hinst_msimg32 );   
    }   
   
}   
void CShape::DrawCone(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa)   
{   
       
    double x,y;   
    pDC->BeginPath();   
    x=r2*cos(sa/180.0*pi)+cp.x;   
    y=-r2*sin(sa/180.0*pi)+cp.y;   
    pDC->MoveTo(x,y);   
    x=r1*cos(sa/180.0*pi)+cp.x;   
    y=-r1*sin(sa/180.0*pi)+cp.y;   
    pDC->LineTo(x,y);   
    pDC->AngleArc(cp.x,cp.y,r1,sa,swa);   
    x=r2*cos(sa/180.0*pi+swa/180.0*pi)+cp.x;   
    y=-r2*sin(sa/180.0*pi+swa/180.0*pi)+cp.y;   
    pDC->LineTo(x,y);   
    pDC->AngleArc(cp.x,cp.y,r2,sa+swa,-swa);   
    pDC->EndPath();   
    pDC->FillPath();   
       
       
}   
void CShape::DrawConeShape(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa)   
{   
       
    double x,y;   
    x=r2*cos(sa/180.0*pi)+cp.x;   
    y=-r2*sin(sa/180.0*pi)+cp.y;   
    pDC->MoveTo(x,y);   
    x=r1*cos(sa/180.0*pi)+cp.x;   
    y=-r1*sin(sa/180.0*pi)+cp.y;   
    pDC->LineTo(x,y);   
    pDC->AngleArc(cp.x,cp.y,r1,sa,swa);   
    x=r2*cos(sa/180.0*pi+swa/180.0*pi)+cp.x;   
    y=-r2*sin(sa/180.0*pi+swa/180.0*pi)+cp.y;   
    pDC->LineTo(x,y);   
    pDC->AngleArc(cp.x,cp.y,r2,sa+swa,-swa);    
}   
void CShape::DrawConeGradientSideToSide(CDC *pDC,POINT cp, float r1, float r2, float sa, float swa,COLORREF nShadowBeginColor,COLORREF nShadowEndColor)   
    {   
       
    double x,y;   
    int nRed = (GetRValue(nShadowEndColor) - GetRValue(nShadowBeginColor));      
    int nGreen = (GetGValue(nShadowEndColor) - GetGValue(nShadowBeginColor));      
    int nBlue = (GetBValue(nShadowEndColor) - GetBValue(nShadowBeginColor));      
    //使进程条显示的总数   等于最大的颜色差值      
    int nSteps = abs(r1-r2);   
    float fRefStep = 0.0f, fGreenStep =0.0f, fBlueStep = 0.0f;    
    fRefStep = nRed / (float)nSteps;      
    fGreenStep = nGreen / (float)nSteps;      
    fBlueStep = nBlue / (float)nSteps;    
       
       
    nRed = GetRValue(nShadowBeginColor);      
    nGreen =  GetGValue(nShadowBeginColor);      
    nBlue = GetBValue(nShadowBeginColor);   
    CBrush b;   
    CBrush *oldbrush;   
    for (int i=r2;i<r1-1;i++)   
    {   
        b.CreateSolidBrush(RGB(nRed+abs(i-r2)*fRefStep,nGreen+   
            abs(i-r2)*fGreenStep,nBlue+abs(i-r2)*fBlueStep));   
        oldbrush=pDC->SelectObject(&b);   
        DrawCone(pDC,cp,i+2,i,sa,swa);   
        pDC->SelectObject(oldbrush);   
        b.DeleteObject();   
    }   
       
}   
void CShape::DrawConeGradientCenterToSide(CDC *pDC,POINT cp, float r1, float r2, float sa,    
                                        float swa,COLORREF nCenterColor,COLORREF nSideColor)   
{   
       
    DrawConeGradientSideToSide(pDC,cp,(r1+r2)/2.0+1,r2,sa,swa,nSideColor,nCenterColor);   
    DrawConeGradientSideToSide(pDC,cp,r1,(r1+r2)/2.0-1,sa,swa,nCenterColor,nSideColor);   
       
}   
void CShape::DrawFan(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge)   
{   
    float x,y;   
    x=r*cos(sAnge/180.0*pi)+pCenter.x;   
    y=-r*sin(sAnge/180.0*pi)+pCenter.y;   
    pDC->BeginPath();   
    pDC->MoveTo(pCenter);   
    pDC->LineTo(x,y);   
    pDC->AngleArc(pCenter.x,pCenter.y,r,sAnge,sweepAnge);   
    pDC->LineTo(pCenter);   
    pDC->EndPath();   
    pDC->FillPath();   
}   
void CShape::DrawFanShape(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge)   
{   
    float x,y;   
    x=r*cos(sAnge/180.0*pi)+pCenter.x;   
    y=-r*sin(sAnge/180.0*pi)+pCenter.y;   
    pDC->MoveTo(pCenter);   
    pDC->LineTo(x,y);   
    pDC->AngleArc(pCenter.x,pCenter.y,r,sAnge,sweepAnge);   
    pDC->LineTo(pCenter);   
       
}   
void CShape::DrawFanGradientSideToSide(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge,   
                                       COLORREF nShadowBeginColor,COLORREF nShadowEndColor)   
{   
    double x,y;   
    int nRed = (GetRValue(nShadowEndColor) - GetRValue(nShadowBeginColor));      
    int nGreen = (GetGValue(nShadowEndColor) - GetGValue(nShadowBeginColor));      
    int nBlue = (GetBValue(nShadowEndColor) - GetBValue(nShadowBeginColor));      
    //使进程条显示的总数   等于最大的颜色差值      
    int nSteps = abs(r);   
    float fRefStep = 0.0f, fGreenStep =0.0f, fBlueStep = 0.0f;    
    fRefStep = nRed / (float)nSteps;      
    fGreenStep = nGreen / (float)nSteps;      
    fBlueStep = nBlue / (float)nSteps;    
       
       
    nRed = GetRValue(nShadowBeginColor);      
    nGreen =  GetGValue(nShadowBeginColor);      
    nBlue = GetBValue(nShadowBeginColor);   
    CBrush b;   
    CBrush *oldbrush;   
    for (int i=r;i>=0;i--)   
    {   
        b.CreateSolidBrush(RGB(nRed+abs(i)*fRefStep,nGreen+   
            abs(i)*fGreenStep,nBlue+abs(i)*fBlueStep));   
        oldbrush=pDC->SelectObject(&b);   
        DrawFan(pDC,pCenter,i,sAnge,sweepAnge);   
        pDC->SelectObject(oldbrush);   
        b.DeleteObject();   
    }   
   
}   
void CShape::DrawFanGradientCenterToSide(CDC *pDC,POINT pCenter,float r,float sAnge,float sweepAnge,   
                                         COLORREF nCenterColor,COLORREF nSideColor)   
{   
    DrawFanGradientSideToSide(pDC,pCenter,r/2,sAnge,sweepAnge,nSideColor,nCenterColor);   
    DrawConeGradientSideToSide(pDC,pCenter,r,r/2-1,sAnge,sweepAnge,nCenterColor,nSideColor);   
   
}   
void CShape::DrawTriangleShapeFromThreePoint(CDC *pDC,POINT p1,POINT p2,POINT p3)   
{   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p1);   
}   
void CShape::DrawTriangleFromThreePoint(CDC *pDC,POINT p1,POINT p2,POINT p3)   
{   
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
       
}   
void CShape::DrawTriangleFromThreePointGradientCenterToSide(CDC *pDC,POINT p1,POINT p2,POINT p3,   
                COLORREF cP1,COLORREF cP2,COLORREF cP3 )   
{   
    _DrawTriangle(pDC,p1,p2,p3,cP1,cP2,cP3);   
}   
   
void CShape::DrawSpecialTriangleShapeTwoSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double H,double hAng)   
{   
   
    double x,y;   
    POINT p1,p2,p3;   
    x=middlePoint.x+H*cos(hAng/180.0*pi);   
    y=-H*sin(hAng/180.0*pi)+middlePoint.y;   
    p1.x=x;   
    p1.y=y;   
   
    x=middlePoint.x+upSideLen/2.0*cos((90-hAng)/180.0*pi);   
    y=upSideLen/2.0*sin((90-hAng)/180.0*pi)+middlePoint.y;   
    p2.x=x;   
    p2.y=y;   
   
    p3.x=2*middlePoint.x-p2.x;   
    p3.y=2*middlePoint.y-p2.y;   
   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p1);   
       
}   
void CShape::DrawSpecialTriangleTwoSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,   
                                             double H,double hAng)   
{   
    double x,y;   
    POINT p1,p2,p3;   
    x=middlePoint.x+H*cos(hAng/180.0*pi);   
    y=-H*sin(hAng/180.0*pi)+middlePoint.y;   
    p1.x=x;   
    p1.y=y;   
       
    x=middlePoint.x+upSideLen/2.0*cos((90-hAng)/180.0*pi);   
    y=upSideLen/2.0*sin((90-hAng)/180.0*pi)+middlePoint.y;   
    p2.x=x;   
    p2.y=y;   
       
    p3.x=2*middlePoint.x-p2.x;   
    p3.y=2*middlePoint.y-p2.y;   
       
   
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
       
}   
void CShape::DrawSpecialTriangleTwoSideEqualGradientCenterToSide(CDC *pDC,POINT middlePoint,double upSideLen,   
             double H,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3  )   
{   
    double x,y;   
    CPoint p1,p2,p3;   
    x=middlePoint.x+H*cos(hAng/180.0*pi);   
    y=-H*sin(hAng/180.0*pi)+middlePoint.y;   
    p1.x=x;   
    p1.y=y;   
       
    x=middlePoint.x+upSideLen/2.0*cos((90-hAng)/180.0*pi);   
    y=upSideLen/2.0*sin((90-hAng)/180.0*pi)+middlePoint.y;   
    p2.x=x;   
    p2.y=y;   
       
    p3.x=2*middlePoint.x-p2.x;   
    p3.y=2*middlePoint.y-p2.y;   
   
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
    _DrawTriangle(pDC,p1,p2,p3,cP1,cP2,cP3);   
}   
   
   
void CShape::DrawSpecialTriangleShapeThreeSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double hAng)   
{   
   
    double h=upSideLen*sqrt(3.0)/2.0;   
    DrawSpecialTriangleShapeTwoSideEqual(pDC,middlePoint,upSideLen,h,hAng);   
}   
void CShape::DrawSpecialTriangleShapeThreeSideEqualGradient(CDC *pDC,POINT middlePoint,   
        double upSideLen,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3)   
{   
    double H=upSideLen*sqrt(3.0)/2.0;   
    double x,y;   
    POINT p1,p2,p3;   
    x=middlePoint.x+H*cos(hAng/180.0*pi);   
    y=-H*sin(hAng/180.0*pi)+middlePoint.y;   
    p1.x=x;   
    p1.y=y;   
       
    x=middlePoint.x+upSideLen/2.0*cos((90-hAng)/180.0*pi);   
    y=upSideLen/2.0*sin((90-hAng)/180.0*pi)+middlePoint.y;   
    p2.x=x;   
    p2.y=y;   
       
    p3.x=2*middlePoint.x-p2.x;   
    p3.y=2*middlePoint.y-p2.y;   
       
    _DrawTriangle(pDC,p1,p2,p3,cP1,cP2,cP3);   
       
}   
   
void CShape::DrawSpecialTriangleThreeSideEqual(CDC *pDC,POINT middlePoint,double upSideLen,double hAng)   
{   
    double h=upSideLen*sqrt(3.0)/2.0;   
    DrawSpecialTriangleTwoSideEqual(pDC,middlePoint,upSideLen,h,hAng);   
   
}   
void CShape::DrawSpecialTriangleThreeSideEqualGradient(CDC *pDC,POINT middlePoint,   
                                                       double upSideLen,double hAng,COLORREF cP1,COLORREF cP2,COLORREF cP3)   
{   
    double H=upSideLen*sqrt(3.0)/2.0;   
    double x,y;   
    POINT p1,p2,p3;   
    x=middlePoint.x+H*cos(hAng/180.0*pi);   
    y=-H*sin(hAng/180.0*pi)+middlePoint.y;   
    p1.x=x;   
    p1.y=y;   
       
    x=middlePoint.x+upSideLen/2.0*cos((90-hAng)/180.0*pi);   
    y=upSideLen/2.0*sin((90-hAng)/180.0*pi)+middlePoint.y;   
    p2.x=x;   
    p2.y=y;   
       
    p3.x=2*middlePoint.x-p2.x;   
    p3.y=2*middlePoint.y-p2.y;   
    _DrawTriangle(pDC,p1,p2,p3,cP1,cP2,cP3);   
       
}   
   
   
void CShape::DrawDiamondShape(CDC *pDC,CPoint centerPoint,double longAxis,   
                              double shortAxis,double longAxisAngToX,double longAxisDivideRate,   
                              double shortAxisDivideRate)   
   
{   
    double x,y;   
    double rate;   
    POINT p1,p2,p3,p4;   
   
    rate=longAxisDivideRate*longAxis;   
    x=centerPoint.x+rate*cos(longAxisAngToX/180.0*pi);   
    y=-rate*sin(longAxisAngToX/180.0*pi)+centerPoint.y;   
    p1.x=x;   
    p1.y=y;   
   
    rate=longAxis-longAxisDivideRate*longAxis;   
    x=centerPoint.x-rate*cos(longAxisAngToX/180.0*pi);   
    y=rate*sin(longAxisAngToX/180.0*pi)+centerPoint.y;   
    p3.x=x;   
    p3.y=y;   
   
   
    rate=shortAxisDivideRate*shortAxis;   
    x=centerPoint.x+rate*cos((90-longAxisAngToX)/180.0*pi);   
    y=rate*sin((90-longAxisAngToX)/180.0*pi)+centerPoint.y;   
    p4.x=x;   
    p4.y=y;   
       
    rate=shortAxis-shortAxisDivideRate*shortAxis;   
    x=centerPoint.x-rate*cos((90-longAxisAngToX)/180.0*pi);   
    y=-rate*sin((90-longAxisAngToX)/180.0*pi)+centerPoint.y;   
    p2.x=x;   
    p2.y=y;   
   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
   
   
   
}   
   
void CShape::DrawDiamond(CDC *pDC,CPoint centerPoint,double longAxis,   
                 double shortAxis,double longAxisAngToX,double longAxisDivideRate,double shortAxisDivideRate)   
{   
    if (longAxis<=0||shortAxis<=0)   
    {   
        return;   
    }   
    if (longAxisDivideRate<0||longAxisDivideRate>1)   
    {   
        longAxisDivideRate=0.5;   
    }   
    if (shortAxisDivideRate<0||shortAxisDivideRate>1)   
    {   
        shortAxisDivideRate=0.5;   
    }   
   
    double x,y;   
    double rate;   
    POINT p1,p2,p3,p4;   
       
    rate=longAxisDivideRate*longAxis;   
    x=centerPoint.x+rate*cos(longAxisAngToX/180.0*pi);   
    y=-rate*sin(longAxisAngToX/180.0*pi)+centerPoint.y;   
    p1.x=x;   
    p1.y=y;   
       
    rate=longAxis-longAxisDivideRate*longAxis;   
    x=centerPoint.x-rate*cos(longAxisAngToX/180.0*pi);   
    y=rate*sin(longAxisAngToX/180.0*pi)+centerPoint.y;   
    p3.x=x;   
    p3.y=y;   
       
       
    rate=shortAxisDivideRate*shortAxis;   
    x=centerPoint.x+rate*cos((90-longAxisAngToX)/180.0*pi);   
    y=rate*sin((90-longAxisAngToX)/180.0*pi)+centerPoint.y;   
    p4.x=x;   
    p4.y=y;   
       
    rate=shortAxis-shortAxisDivideRate*shortAxis;   
    x=centerPoint.x-rate*cos((90-longAxisAngToX)/180.0*pi);   
    y=-rate*sin((90-longAxisAngToX)/180.0*pi)+centerPoint.y;   
    p2.x=x;   
    p2.y=y;   
       
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
}   
void CShape::DrawDiamondGradient(CDC *pDC,CPoint centerPoint,double longAxis,   
                                     double shortAxis,double longAxisAngToX,COLORREF nShadowBeginColor,COLORREF nShadowEndColor ,   
        int style,double longAxisDivideRate,double shortAxisDivideRate)   
{   
    POINT cp=centerPoint;   
   
    if (style<1||style>5)   
    {   
        return;   
    }   
    if(longAxisDivideRate<0||longAxisDivideRate>1) longAxisDivideRate=0.5;   
    if(shortAxisDivideRate<0||shortAxisDivideRate>1) shortAxisDivideRate=0.5;   
    double x,y;   
    double rate;   
    POINT p1,p2,p3,p4;   
       
    rate=longAxisDivideRate*longAxis;   
    x=centerPoint.x+rate*cos(longAxisAngToX/180.0*pi);   
    y=-rate*sin(longAxisAngToX/180.0*pi)+centerPoint.y;   
    p1.x=x;   
    p1.y=y;   
       
    rate=longAxis-longAxisDivideRate*longAxis;   
    x=centerPoint.x-rate*cos(longAxisAngToX/180.0*pi);   
    y=rate*sin(longAxisAngToX/180.0*pi)+centerPoint.y;   
    p3.x=x;   
    p3.y=y;   
       
       
    rate=shortAxisDivideRate*shortAxis;   
    x=centerPoint.x+rate*cos((90-longAxisAngToX)/180.0*pi);   
    y=rate*sin((90-longAxisAngToX)/180.0*pi)+centerPoint.y;   
    p4.x=x;   
    p4.y=y;   
       
    rate=shortAxis-shortAxisDivideRate*shortAxis;   
    x=centerPoint.x-rate*cos((90-longAxisAngToX)/180.0*pi);   
    y=-rate*sin((90-longAxisAngToX)/180.0*pi)+centerPoint.y;   
    p2.x=x;   
    p2.y=y;   
       
    COLORREF C;   
    int r1,g1,b1,r2,g2,b2;   
    r1=GetRValue(nShadowBeginColor);   
    g1=GetGValue(nShadowBeginColor);   
    b1=GetBValue(nShadowBeginColor);   
    r2=GetRValue(nShadowEndColor);   
    g2=GetGValue(nShadowEndColor);   
    b2=GetBValue(nShadowEndColor);   
    C=RGB((r1+r2)/2,(g1+g2)/2,(b1+b2)/2);   
   
    if (style==LEFT_TO_RIGHT)   
    {   
        _DrawTriangle(pDC,p1,p2,p4,C,nShadowBeginColor,nShadowEndColor);   
        _DrawTriangle(pDC,p2,p3,p4,nShadowBeginColor,C,nShadowEndColor);   
    }   
    if (style==TOP_TO_BOTTOM)   
    {   
        _DrawTriangle(pDC,p1,p2,p3,nShadowBeginColor,C,nShadowEndColor);   
        _DrawTriangle(pDC,p3,p4,p1,nShadowEndColor,C,nShadowBeginColor);   
    }   
   
    if (style==TOP_MIDDLE_BOTTOM)   
    {   
        _DrawTriangle(pDC,p1,p2,p3,nShadowBeginColor,nShadowEndColor,nShadowBeginColor);   
        _DrawTriangle(pDC,p3,p4,p1,nShadowBeginColor,nShadowEndColor,nShadowBeginColor);   
    }   
    if (style==LEFT_MIDDLE_RIGHT||style==MIDDLE_TO_SIDE)   
    {   
        _DrawTriangle(pDC,p1,p2,p4,nShadowEndColor,nShadowBeginColor,nShadowBeginColor);   
        _DrawTriangle(pDC,p2,p3,p4,nShadowBeginColor,nShadowEndColor,nShadowBeginColor);   
    }   
   
}   
void CShape::DrawRectangleShape(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX)   
{   
    POINT p1,p2,p3,p4;   
    double x,y,thea;   
    thea=atan(height/wide);   
   
       
    p1.x=centerPoint.x+sqrt(height*height+wide*wide)/2.0*cos(wideAngleToX/180.0*pi+thea);   
    p1.y=centerPoint.y-sqrt(height*height+wide*wide)/2.0*sin(wideAngleToX/180.0*pi+thea);   
   
   
    p3.x=centerPoint.x*2-p1.x;   
    p3.y=centerPoint.y*2-p1.y;   
   
    p4.x=centerPoint.x+sqrt(height*height+wide*wide)/2.0*cos(wideAngleToX/180.0*pi-thea);   
    p4.y=centerPoint.y-sqrt(height*height+wide*wide)/2.0*sin(wideAngleToX/180.0*pi-thea);   
       
   
       
    p2.x=centerPoint.x*2-p4.x;   
    p2.y=centerPoint.y*2-p4.y;   
   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
   
   
}   
void CShape::DrawRectangleShape(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX)   
{   
    double x,y,thea,thea1,d;   
    POINT p1,p2,p3,p4;   
    p1=leftbottomPoint;   
    p3=righttopPoint;   
    d=sqrt((double)((leftbottomPoint.x-righttopPoint.x)*(leftbottomPoint.x-righttopPoint.x)+   
        (leftbottomPoint.y-righttopPoint.y)*(leftbottomPoint.y-righttopPoint.y)));   
       
    CString str;   
    str.Format("%f",d);   
    pDC->TextOut(101,100,str);   
   
   
    thea=atan(-double(leftbottomPoint.y-righttopPoint.y)/double(leftbottomPoint.x-righttopPoint.x));   
    thea1=thea-wideAngleToX/180.0*pi;   
   
    d=cos(thea1)*d;   
    x=leftbottomPoint.x+d*cos(wideAngleToX/180.0*pi);   
    y=leftbottomPoint.y-d*sin(wideAngleToX/180.0*pi);   
   
    p2.x=x;   
    p2.y=y;   
   
    p4.x=p1.x+p3.x-p2.x;   
    p4.y=p1.y+p3.y-p2.y;   
   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
   
   
       
   
}   
void CShape::DrawRectangleShape(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H)   
{   
    double x,y;   
    POINT centerPoint;   
    x=-H/2.0*sin(sideAngleToX/180.0*pi)+sideMiddlePoint.x;   
    y=-H/2.0*cos(sideAngleToX/180.0*pi)+sideMiddlePoint.y;   
    centerPoint.x=x;   
    centerPoint.y=y;   
   
    POINT p1,p2,p3,p4;   
    double thea;   
    thea=atan(H/sideLen);   
       
    p1.x=centerPoint.x+sqrt(H*H+sideLen*sideLen)/2.0*cos(sideAngleToX/180.0*pi+thea);   
    p1.y=centerPoint.y-sqrt(H*H+sideLen*sideLen)/2.0*sin(sideAngleToX/180.0*pi+thea);   
       
       
    p3.x=centerPoint.x*2-p1.x;   
    p3.y=centerPoint.y*2-p1.y;   
       
    p4.x=centerPoint.x+sqrt(H*H+sideLen*sideLen)/2.0*cos(sideAngleToX/180.0*pi-thea);   
    p4.y=centerPoint.y-sqrt(H*H+sideLen*sideLen)/2.0*sin(sideAngleToX/180.0*pi-thea);   
       
       
       
    p2.x=centerPoint.x*2-p4.x;   
    p2.y=centerPoint.y*2-p4.y;   
       
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
   
   
}   
void CShape::DrawRectangle(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX)   
{   
   
    POINT p1,p2,p3,p4;   
    double x,y,thea;   
    thea=atan(height/wide);   
       
       
    p1.x=centerPoint.x+sqrt(height*height+wide*wide)/2.0*cos(wideAngleToX/180.0*pi+thea);   
    p1.y=centerPoint.y-sqrt(height*height+wide*wide)/2.0*sin(wideAngleToX/180.0*pi+thea);   
       
       
    p3.x=centerPoint.x*2-p1.x;   
    p3.y=centerPoint.y*2-p1.y;   
       
    p4.x=centerPoint.x+sqrt(height*height+wide*wide)/2.0*cos(wideAngleToX/180.0*pi-thea);   
    p4.y=centerPoint.y-sqrt(height*height+wide*wide)/2.0*sin(wideAngleToX/180.0*pi-thea);   
       
       
       
    p2.x=centerPoint.x*2-p4.x;   
    p2.y=centerPoint.y*2-p4.y;   
       
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
   
}   
//绘制矩形，画刷填充，对角点和一般和X轴的夹角   
void CShape::DrawRectangle(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX)   
{   
    double x,y,thea,thea1,d;   
    POINT p1,p2,p3,p4;   
    p1=leftbottomPoint;   
    p3=righttopPoint;   
    d=sqrt((double)((leftbottomPoint.x-righttopPoint.x)*(leftbottomPoint.x-righttopPoint.x)+   
        (leftbottomPoint.y-righttopPoint.y)*(leftbottomPoint.y-righttopPoint.y)));   
       
   
       
       
    thea=atan(-double(leftbottomPoint.y-righttopPoint.y)/double(leftbottomPoint.x-righttopPoint.x));   
    thea1=thea-wideAngleToX/180.0*pi;   
       
    d=cos(thea1)*d;   
    x=leftbottomPoint.x+d*cos(wideAngleToX/180.0*pi);   
    y=leftbottomPoint.y-d*sin(wideAngleToX/180.0*pi);   
       
    p2.x=x;   
    p2.y=y;   
       
    p4.x=p1.x+p3.x-p2.x;   
    p4.y=p1.y+p3.y-p2.y;   
       
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
       
   
   
}   
//绘制矩形，画刷填充,一边长度和一边对x轴的夹角及其该边中点，该边高线长度   
void CShape::DrawRectangle(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H)   
{   
    double x,y;   
    POINT centerPoint;   
    x=-H/2.0*sin(sideAngleToX/180.0*pi)+sideMiddlePoint.x;   
    y=-H/2.0*cos(sideAngleToX/180.0*pi)+sideMiddlePoint.y;   
    centerPoint.x=x;   
    centerPoint.y=y;   
       
    POINT p1,p2,p3,p4;   
    double thea;   
    thea=atan(H/sideLen);   
       
    p1.x=centerPoint.x+sqrt(H*H+sideLen*sideLen)/2.0*cos(sideAngleToX/180.0*pi+thea);   
    p1.y=centerPoint.y-sqrt(H*H+sideLen*sideLen)/2.0*sin(sideAngleToX/180.0*pi+thea);   
       
       
    p3.x=centerPoint.x*2-p1.x;   
    p3.y=centerPoint.y*2-p1.y;   
       
    p4.x=centerPoint.x+sqrt(H*H+sideLen*sideLen)/2.0*cos(sideAngleToX/180.0*pi-thea);   
    p4.y=centerPoint.y-sqrt(H*H+sideLen*sideLen)/2.0*sin(sideAngleToX/180.0*pi-thea);   
       
       
       
    p2.x=centerPoint.x*2-p4.x;   
    p2.y=centerPoint.y*2-p4.y;   
       
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
   
}   
void CShape::DrawRectangleGradient(CDC *pDC,POINT centerPoint,double wide,double height,double wideAngleToX   
        ,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg )   
{   
    POINT cp=centerPoint;   
    CBitmap bmp;   
    CDC memDC;   
    memDC.CreateCompatibleDC(pDC);   
    CRect wndRC;   
    POINT p1,p2,p3,p4;   
    double x,y,thea;   
    thea=atan(height/wide);   
       
       
    p1.x=centerPoint.x+sqrt(height*height+wide*wide)/2.0*cos(wideAngleToX/180.0*pi+thea);   
    p1.y=centerPoint.y-sqrt(height*height+wide*wide)/2.0*sin(wideAngleToX/180.0*pi+thea);   
       
       
    p3.x=centerPoint.x*2-p1.x;   
    p3.y=centerPoint.y*2-p1.y;   
       
    p4.x=centerPoint.x+sqrt(height*height+wide*wide)/2.0*cos(wideAngleToX/180.0*pi-thea);   
    p4.y=centerPoint.y-sqrt(height*height+wide*wide)/2.0*sin(wideAngleToX/180.0*pi-thea);   
    p2.x=centerPoint.x*2-p4.x;   
    p2.y=centerPoint.y*2-p4.y;   
   
    wndRC.left=min(min(min(p1.x,p2.x),p3.x),p4.x);   
    wndRC.right=max(max(max(p1.x,p2.x),p3.x),p4.x);   
    wndRC.top=min(min(min(p1.y,p2.y),p3.y),p4.y);   
    wndRC.bottom=max(max(max(p1.y,p2.y),p3.y),p4.y);   
    cp=wndRC.CenterPoint();   
   
       
    bmp.CreateCompatibleBitmap(pDC,wndRC.Width(),wndRC.Height());   
    memDC.SelectObject(&bmp);   
    ////////////////////////////////////////   
    CBrush *oldbrush,brush;   
   
    int nRed = (GetRValue(nShadowEndColor) - GetRValue(nShadowBeginColor));      
    int nGreen = (GetGValue(nShadowEndColor) - GetGValue(nShadowBeginColor));      
    int nBlue = (GetBValue(nShadowEndColor) - GetBValue(nShadowBeginColor));      
    //使进程条显示的总数   等于最大的颜色差值      
    int nSteps;   
    float fRefStep = 0.0f, fGreenStep =0.0f, fBlueStep = 0.0f;    
    CBrush b;   
    CBrush *oldb;   
    CRect r;   
   
       
    CRect rt;   
    rt.left=0;   
    rt.top=0;   
    rt.right=max(wndRC.Width(),wndRC.Height());   
    rt.bottom=max(wndRC.Width(),wndRC.Height());   
    _DrawRect(&memDC,rt,nShadowBeginColor,nShadowEndColor,falg);   
       
///////////////////////////////////////   
   
    brush.CreatePatternBrush(&bmp);   
    oldbrush=pDC->SelectObject(&brush);   
    pDC->SetBrushOrg(CPoint(wndRC.left,wndRC.bottom));   
   
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
    pDC->SelectObject(oldbrush);   
    brush.DeleteObject();   
    bmp.DeleteObject();   
    memDC.DeleteDC();   
   
}   
void CShape::DrawRectangleGradient(CDC *pDC,POINT leftbottomPoint,POINT righttopPoint,double wideAngleToX   
        ,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg )   
{   
    POINT cp;   
    CBitmap bmp;   
    CDC memDC;   
    memDC.CreateCompatibleDC(pDC);   
    CRect wndRC;   
    double x,y,thea,thea1,d;   
    POINT p1,p2,p3,p4;   
    p1=leftbottomPoint;   
    p3=righttopPoint;   
    d=sqrt((double)((leftbottomPoint.x-righttopPoint.x)*(leftbottomPoint.x-righttopPoint.x)+   
        (leftbottomPoint.y-righttopPoint.y)*(leftbottomPoint.y-righttopPoint.y)));   
       
    thea=atan(-double(leftbottomPoint.y-righttopPoint.y)/double(leftbottomPoint.x-righttopPoint.x));   
    thea1=thea-wideAngleToX/180.0*pi;   
       
    d=cos(thea1)*d;   
    x=leftbottomPoint.x+d*cos(wideAngleToX/180.0*pi);   
    y=leftbottomPoint.y-d*sin(wideAngleToX/180.0*pi);   
       
    p2.x=x;   
    p2.y=y;   
       
    p4.x=p1.x+p3.x-p2.x;   
    p4.y=p1.y+p3.y-p2.y;   
   
   
    wndRC.left=min(min(min(p1.x,p2.x),p3.x),p4.x);   
    wndRC.right=max(max(max(p1.x,p2.x),p3.x),p4.x);   
    wndRC.top=min(min(min(p1.y,p2.y),p3.y),p4.y);   
    wndRC.bottom=max(max(max(p1.y,p2.y),p3.y),p4.y);   
    cp=wndRC.CenterPoint();   
   
       
    bmp.CreateCompatibleBitmap(pDC,wndRC.Width(),wndRC.Height());   
    memDC.SelectObject(&bmp);   
    ////////////////////////////////////////   
    CBrush *oldbrush,brush;   
   
    int nRed = (GetRValue(nShadowEndColor) - GetRValue(nShadowBeginColor));      
    int nGreen = (GetGValue(nShadowEndColor) - GetGValue(nShadowBeginColor));      
    int nBlue = (GetBValue(nShadowEndColor) - GetBValue(nShadowBeginColor));      
    //使进程条显示的总数   等于最大的颜色差值      
    int nSteps;   
    float fRefStep = 0.0f, fGreenStep =0.0f, fBlueStep = 0.0f;    
    CBrush b;   
    CBrush *oldb;   
    CRect r;   
   
    {   
        CRect rt;   
        rt.left=0;   
        rt.top=0;   
        rt.right=max(wndRC.Width(),wndRC.Height());   
        rt.bottom=max(wndRC.Width(),wndRC.Height());   
        _DrawRect(&memDC,rt,nShadowBeginColor,nShadowEndColor,falg);   
    }   
//////////////////////  /////////////////   
   
    brush.CreatePatternBrush(&bmp);   
    oldbrush=pDC->SelectObject(&brush);   
    pDC->SetBrushOrg(CPoint(wndRC.left,wndRC.bottom));   
   
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
    pDC->SelectObject(oldbrush);   
    brush.DeleteObject();   
    bmp.DeleteObject();   
    memDC.DeleteDC();   
   
}   
void CShape::DrawRectangleGradient(CDC *pDC,double sideLen,POINT sideMiddlePoint,double sideAngleToX,double H   
        ,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg )   
   
{   
    POINT cp;   
    CBitmap bmp;   
    CDC memDC;   
    memDC.CreateCompatibleDC(pDC);   
    CRect wndRC;   
    double x,y;   
    POINT centerPoint;   
    x=-H/2.0*sin(sideAngleToX/180.0*pi)+sideMiddlePoint.x;   
    y=-H/2.0*cos(sideAngleToX/180.0*pi)+sideMiddlePoint.y;   
    centerPoint.x=x;   
    centerPoint.y=y;   
       
    POINT p1,p2,p3,p4;   
    double thea;   
    thea=atan(H/sideLen);   
       
    p1.x=centerPoint.x+sqrt(H*H+sideLen*sideLen)/2.0*cos(sideAngleToX/180.0*pi+thea);   
    p1.y=centerPoint.y-sqrt(H*H+sideLen*sideLen)/2.0*sin(sideAngleToX/180.0*pi+thea);   
       
       
    p3.x=centerPoint.x*2-p1.x;   
    p3.y=centerPoint.y*2-p1.y;   
       
    p4.x=centerPoint.x+sqrt(H*H+sideLen*sideLen)/2.0*cos(sideAngleToX/180.0*pi-thea);   
    p4.y=centerPoint.y-sqrt(H*H+sideLen*sideLen)/2.0*sin(sideAngleToX/180.0*pi-thea);   
       
       
       
    p2.x=centerPoint.x*2-p4.x;   
    p2.y=centerPoint.y*2-p4.y;   
   
    wndRC.left=min(min(min(p1.x,p2.x),p3.x),p4.x);   
    wndRC.right=max(max(max(p1.x,p2.x),p3.x),p4.x);   
    wndRC.top=min(min(min(p1.y,p2.y),p3.y),p4.y);   
    wndRC.bottom=max(max(max(p1.y,p2.y),p3.y),p4.y);   
    cp=wndRC.CenterPoint();   
   
       
    bmp.CreateCompatibleBitmap(pDC,wndRC.Width(),wndRC.Height());   
    memDC.SelectObject(&bmp);   
    ////////////////////////////////////////   
    CBrush *oldbrush,brush;   
   
    int nRed = (GetRValue(nShadowEndColor) - GetRValue(nShadowBeginColor));      
    int nGreen = (GetGValue(nShadowEndColor) - GetGValue(nShadowBeginColor));      
    int nBlue = (GetBValue(nShadowEndColor) - GetBValue(nShadowBeginColor));      
    //使进程条显示的总数   等于最大的颜色差值      
    int nSteps;   
    float fRefStep = 0.0f, fGreenStep =0.0f, fBlueStep = 0.0f;    
    CBrush b;   
    CBrush *oldb;   
    CRect r;   
   
       
    {   
        CRect rt;   
        rt.left=0;   
        rt.top=0;   
        rt.right=max(wndRC.Width(),wndRC.Height());   
        rt.bottom=max(wndRC.Width(),wndRC.Height());   
        _DrawRect(&memDC,rt,nShadowBeginColor,nShadowEndColor,falg);   
    }   
///////////////////////////////////////   
    brush.CreatePatternBrush(&bmp);   
    oldbrush=pDC->SelectObject(&brush);   
    pDC->SetBrushOrg(CPoint(wndRC.left,wndRC.bottom));   
   
    pDC->BeginPath();   
    pDC->MoveTo(p1);   
    pDC->LineTo(p2);   
    pDC->LineTo(p3);   
    pDC->LineTo(p4);   
    pDC->LineTo(p1);   
    pDC->EndPath();   
    pDC->FillPath();   
    pDC->SelectObject(oldbrush);   
    brush.DeleteObject();   
    bmp.DeleteObject();   
    memDC.DeleteDC();   
   
}   
void CShape::DrawPolygonShape(CDC *pDC,POINT centerPoint,double sideLen,int sideNum,   
                              double centerToSideAngToX)   
{   
    if (sideNum<=2)   
    {   
        return;   
    }   
    double perAng,x,y,thea,d;   
    perAng=pi/double(sideNum);   
    POINT *p=new POINT[sideNum];   
    CString str;   
    centerToSideAngToX=90-centerToSideAngToX;   
    d=sideLen/2.0/sin(perAng);   
    thea=centerToSideAngToX/180.0*pi; 
	int i=0;
    for (;i<sideNum;i++)   
    {   
        thea=centerToSideAngToX/180.0*pi+i*(2*perAng);   
        x=centerPoint.x-d*sin(thea+perAng);   
        y=centerPoint.y+d*cos(thea+perAng);   
        p[i].x=x;   
        p[i].y=y;      
    }   
    pDC->MoveTo(p[0]);   
    for (i=1;i<sideNum;i++)   
    {   
        pDC->LineTo(p[i]);   
    }   
    pDC->LineTo(p[0]);   
   
    delete p;   
   
}   
void CShape::DrawPolygonShape(CDC *pDC,POINT *Point,int pointNum)   
{   
    pDC->MoveTo(Point[0]);   
    for (int i=1;i<pointNum;i++)   
    {   
        pDC->LineTo(Point[i]);   
    }   
    pDC->LineTo(Point[0]);   
   
}   
void CShape::DrawPolygon(CDC *pDC,POINT centerPoint,double sideLen,int sideNum,   
                              double centerToSideAngToX)   
{   
    if (sideNum<=2)   
    {   
        return;   
    }   
    double perAng,x,y,thea,d;   
    perAng=pi/double(sideNum);   
    POINT *p=new POINT[sideNum];   
    CString str;   
    centerToSideAngToX=90-centerToSideAngToX;   
    d=sideLen/2.0/sin(perAng);   
    thea=centerToSideAngToX/180.0*pi;   
	int i=0;
    for (;i<sideNum;i++)   
    {   
        thea=centerToSideAngToX/180.0*pi+i*(2*perAng);   
        x=centerPoint.x-d*sin(thea+perAng);   
        y=centerPoint.y+d*cos(thea+perAng);   
        p[i].x=x;   
        p[i].y=y;      
    }   
    pDC->BeginPath();   
    pDC->MoveTo(p[0]);   
    for (i=1;i<sideNum;i++)   
    {   
        pDC->LineTo(p[i]);   
    }   
    pDC->LineTo(p[0]);   
    pDC->EndPath();   
    pDC->FillPath();   
       
    delete p;   
       
}   
void CShape::DrawPolygon(CDC *pDC,POINT *Point,int pointNum)   
{   
    pDC->BeginPath();   
    pDC->MoveTo(Point[0]);   
    for (int i=1;i<pointNum;i++)   
    {   
        pDC->LineTo(Point[i]);   
    }   
    pDC->LineTo(Point[0]);   
    pDC->EndPath();   
    pDC->FillPath();   
       
}   
void CShape::_DrawRect(CDC *pDC,CRect rect,COLORREF nShadowBeginColor,COLORREF nShadowEndColor,int falg )   
{   
    TRIVERTEX rcVertex[2];   
    rcVertex[0].x=rect.left;   
    rcVertex[0].y=rect.top;   
    rcVertex[0].Red=GetRValue(nShadowBeginColor)<<8; // color values from 0x0000 to 0xff00 !!!!   
    rcVertex[0].Green=GetGValue(nShadowBeginColor)<<8;   
    rcVertex[0].Blue=GetBValue(nShadowBeginColor)<<8;   
    rcVertex[0].Alpha=0x0000;   
    rcVertex[1].x=rect.right;    
    rcVertex[1].y=rect.bottom;   
    rcVertex[1].Red=GetRValue(nShadowEndColor)<<8;   
    rcVertex[1].Green=GetGValue(nShadowEndColor)<<8;   
    rcVertex[1].Blue=GetBValue(nShadowEndColor)<<8;   
    rcVertex[1].Alpha=0;   
   
       
    GRADIENT_RECT rect1;   
    rect1.UpperLeft=0;   
    rect1.LowerRight=1;   
    if (falg==LEFT_TO_RIGHT)   
        handle_GradientFill( pDC->GetSafeHdc(),rcVertex,2,&rect1,1,  GRADIENT_FILL_RECT_H);   
    if (falg==TOP_TO_BOTTOM)   
        handle_GradientFill( pDC->GetSafeHdc(),rcVertex,2,&rect1,1, GRADIENT_FILL_RECT_V );   
    if (falg==LEFT_MIDDLE_RIGHT)   
    {   
        rcVertex[0].x=rect.left;   
        rcVertex[0].y=rect.top;   
        rcVertex[0].Red=GetRValue(nShadowBeginColor)<<8; // color values from 0x0000 to 0xff00 !!!!   
        rcVertex[0].Green=GetGValue(nShadowBeginColor)<<8;   
        rcVertex[0].Blue=GetBValue(nShadowBeginColor)<<8;   
        rcVertex[0].Alpha=0x0000;   
        rcVertex[1].x=rect.right-rect.Width()/2;    
        rcVertex[1].y=rect.bottom;   
        rcVertex[1].Red=GetRValue(nShadowEndColor)<<8;   
        rcVertex[1].Green=GetGValue(nShadowEndColor)<<8;   
        rcVertex[1].Blue=GetBValue(nShadowEndColor)<<8;   
        rcVertex[1].Alpha=0;   
        handle_GradientFill( pDC->GetSafeHdc(),rcVertex,2,&rect1,1,  GRADIENT_FILL_RECT_H);   
        rcVertex[0].x=rect.left+rect.Width()/2-1;   
        rcVertex[0].y=rect.top;   
        rcVertex[0].Red=GetRValue(nShadowEndColor)<<8; // color values from 0x0000 to 0xff00 !!!!   
        rcVertex[0].Green=GetGValue(nShadowEndColor)<<8;   
        rcVertex[0].Blue=GetBValue(nShadowEndColor)<<8;   
        rcVertex[0].Alpha=0x0000;   
        rcVertex[1].x=rect.right;    
        rcVertex[1].y=rect.bottom;   
        rcVertex[1].Red=GetRValue(nShadowBeginColor)<<8;   
        rcVertex[1].Green=GetGValue(nShadowBeginColor)<<8;   
        rcVertex[1].Blue=GetBValue(nShadowBeginColor)<<8;   
        rcVertex[1].Alpha=0;   
        handle_GradientFill( pDC->GetSafeHdc(),rcVertex,2,&rect1,1,  GRADIENT_FILL_RECT_H);   
    }   
    if (falg==TOP_MIDDLE_BOTTOM)   
    {   
        rcVertex[0].x=rect.left;   
        rcVertex[0].y=rect.top;   
        rcVertex[0].Red=GetRValue(nShadowBeginColor)<<8; // color values from 0x0000 to 0xff00 !!!!   
        rcVertex[0].Green=GetGValue(nShadowBeginColor)<<8;   
        rcVertex[0].Blue=GetBValue(nShadowBeginColor)<<8;   
        rcVertex[0].Alpha=0x0000;   
        rcVertex[1].x=rect.right;    
        rcVertex[1].y=rect.bottom-rect.Height()/2;   
        rcVertex[1].Red=GetRValue(nShadowEndColor)<<8;   
        rcVertex[1].Green=GetGValue(nShadowEndColor)<<8;   
        rcVertex[1].Blue=GetBValue(nShadowEndColor)<<8;   
        rcVertex[1].Alpha=0;   
        handle_GradientFill( pDC->GetSafeHdc(),rcVertex,2,&rect1,1,  GRADIENT_FILL_RECT_V);   
        rcVertex[0].x=rect.left;   
        rcVertex[0].y=rect.top-1+rect.Height()/2;   
        rcVertex[0].Red=GetRValue(nShadowEndColor)<<8; // color values from 0x0000 to 0xff00 !!!!   
        rcVertex[0].Green=GetGValue(nShadowEndColor)<<8;   
        rcVertex[0].Blue=GetBValue(nShadowEndColor)<<8;   
        rcVertex[0].Alpha=0x0000;   
        rcVertex[1].x=rect.right;    
        rcVertex[1].y=rect.bottom;   
        rcVertex[1].Red=GetRValue(nShadowBeginColor)<<8;   
        rcVertex[1].Green=GetGValue(nShadowBeginColor)<<8;   
        rcVertex[1].Blue=GetBValue(nShadowBeginColor)<<8;   
        rcVertex[1].Alpha=0;   
        handle_GradientFill( pDC->GetSafeHdc(),rcVertex,2,&rect1,1,  GRADIENT_FILL_RECT_V);   
    }   
    if (falg==MIDDLE_TO_SIDE)   
    {   
        POINT p1,p2,p3,p4,p;   
        p1.x=rect.left;p1.y=rect.bottom;   
        p2.x=rect.right;p2.y=rect.bottom;   
        p3.x=rect.right;p3.y=rect.top;   
        p4.x=rect.left;p4.y=rect.top;   
        p=rect.CenterPoint();   
        _DrawTriangle(pDC,p1,p2,p,nShadowEndColor,nShadowEndColor,nShadowBeginColor);   
        _DrawTriangle(pDC,p2,p3,p,nShadowEndColor,nShadowEndColor,nShadowBeginColor);   
        _DrawTriangle(pDC,p3,p4,p,nShadowEndColor,nShadowEndColor,nShadowBeginColor);   
        _DrawTriangle(pDC,p4,p1,p,nShadowEndColor,nShadowEndColor,nShadowBeginColor);   
    }   
       
   
   
}   
void CShape:: _DrawTriangle(CDC *pDC,POINT P1,POINT P2,POINT P3,   
        COLORREF cP1,COLORREF cP2,COLORREF cP3)   
{   
    TRIVERTEX        vert [4] ;   
    vert [0] .x       =  P1.x;   
    vert [0] .y       =  P1.y;   
    vert [0].Red=GetRValue(cP1)<<8; // color values from 0x0000 to 0xff00 !!!!   
    vert [0].Green=GetGValue(cP1)<<8;   
    vert [0].Blue=GetBValue(cP1)<<8;   
    vert [0] .Alpha   =  0;   
       
    vert [1] .x       =  P2.x;   
    vert [1] .y       =  P2.y;   
    vert [1].Red=GetRValue(cP2)<<8; // color values from 0x0000 to 0xff00 !!!!   
    vert [1].Green=GetGValue(cP2)<<8;   
    vert [1].Blue=GetBValue(cP2)<<8;   
    vert [1] .Alpha   =  0;   
       
    vert [2] .x      =  P3.x;   
    vert [2] .y       =  P3.y;    
    vert [2].Red=GetRValue(cP3)<<8; // color values from 0x0000 to 0xff00 !!!!   
    vert [2].Green=GetGValue(cP3)<<8;   
    vert [2].Blue=GetBValue(cP3)<<8;   
    vert [2] .Alpha   =  0;   
       
    _GRADIENT_TRIANGLE  gTRi[1];   
       
    gTRi[0].Vertex1   = 0;   
    gTRi[0].Vertex2   = 1;   
    gTRi[0].Vertex3   = 2;   
    handle_GradientFill(pDC->GetSafeHdc(),vert,4,&gTRi,1,GRADIENT_FILL_TRIANGLE);   
   
   
}   
void CShape::DrawCircleShape(CDC *pDC,POINT pCenter,double r)   
{   
    pDC->MoveTo(pCenter.x+r,pCenter.y);   
    pDC->AngleArc(pCenter.x,pCenter.y,r,0,360);   
}   
void CShape::DrawCircle(CDC *pDC,POINT pCenter,double r)   
{   
    CRect rt;   
    rt.left=pCenter.x-r;   
    rt.right=pCenter.x+r;   
    rt.top=pCenter.y-r;   
    rt.bottom=pCenter.y+r;   
    pDC->BeginPath();   
    pDC->Ellipse(rt);   
    pDC->EndPath();   
    pDC->FillPath();   
}   
void CShape::DrawCircleGradient(CDC *pDC,POINT pCenter,double r,COLORREF nShadowBeginColor,   
                        COLORREF nShadowEndColor,int falg)   
{   
    if (falg>6||falg<=0)   
    {   
        falg=MIDDLE_TO_SIDE;   
    }   
    CRect rect;   
    rect.left=0;   
    rect.top=0;   
    rect.right=r*2;   
    rect.bottom=r*2;   
   
    CBitmap bmp;   
    CDC memDC;   
    memDC.CreateCompatibleDC(pDC);   
    CRect wndRC;   
    wndRC.left=pCenter.x-r;   
    wndRC.right=pCenter.x+r;   
    wndRC.top=pCenter.y-r;   
    wndRC.bottom=pCenter.y+r;   
       
   
   
    bmp.CreateCompatibleBitmap(pDC,wndRC.Width(),wndRC.Height());   
    memDC.SelectObject(&bmp);   
    ////////////////////////////////////////   
    CBrush *oldbrush,brush;   
   
    int nRed = (GetRValue(nShadowEndColor) - GetRValue(nShadowBeginColor));      
    int nGreen = (GetGValue(nShadowEndColor) - GetGValue(nShadowBeginColor));      
    int nBlue = (GetBValue(nShadowEndColor) - GetBValue(nShadowBeginColor));      
    //使进程条显示的总数   等于最大的颜色差值      
    int nSteps = max(wndRC.Width(),wndRC.Height());   
    float fRefStep = 0.0f, fGreenStep =0.0f, fBlueStep = 0.0f;    
    fRefStep = nRed / (float)nSteps;      
    fGreenStep = nGreen / (float)nSteps;      
    fBlueStep = nBlue / (float)nSteps;    
       
    nRed = GetRValue(nShadowBeginColor);      
    nGreen =  GetGValue(nShadowBeginColor);      
    nBlue = GetBValue(nShadowBeginColor);   
    CBrush b;   
    CBrush *oldb;   
   
    if (falg==MIDDLE_TO_SIDE)   
    for (int i=nSteps;i>=0;i--)   
    {   
        b.CreateSolidBrush(RGB(nRed+abs(i)*fRefStep,nGreen+   
            abs(i)*fGreenStep,nBlue+abs(i)*fBlueStep));   
        oldb=memDC.SelectObject(&b);   
        DrawFan(&memDC,CPoint(nSteps/2,nSteps/2),i,0,360);   
        memDC.SelectObject(oldb);   
        b.DeleteObject();   
       
    }   
    else   
    {   
        _DrawRect(&memDC,rect,nShadowBeginColor,nShadowEndColor,falg);   
    }   
   
//  pDC->BitBlt(0,0,100,100,&memDC,0,0,SRCCOPY);   
///////////////////////////////////////   
       
    brush.CreatePatternBrush(&bmp);   
    oldbrush=pDC->SelectObject(&brush);   
    pDC->SetBrushOrg(CPoint(wndRC.left,wndRC.bottom));   
   
    pDC->BeginPath();   
   
    pDC->Ellipse(wndRC);   
    pDC->EndPath();   
    pDC->FillPath();   
   
   
   
       
   
    pDC->SelectObject(oldbrush);   
    brush.DeleteObject();   
    bmp.DeleteObject();   
    memDC.DeleteDC();   
   
}   
void CShape::DrawPoint(CDC *pDC,CPoint pos,COLORREF pointColor,int size)   
{   
   
    CRect r;   
    r.left=pos.x-size-1;   
    r.right=pos.x+size+1;   
    r.top=pos.y-1-size;   
    r.bottom=pos.y+size+1;   
    CBrush *oldbrush,brush(pointColor);   
    oldbrush=pDC->SelectObject(&brush);   
    pDC->BeginPath();   
    pDC->Ellipse(r);   
    pDC->EndPath();   
    pDC->FillPath();   
    pDC->SelectObject(oldbrush);   
           
}   
void CShape::DrawLine_TwoPoint(CDC *pDC,CPoint pStart,CPoint pEnd,   
                      COLORREF lineColor,int size,int lineStyle)   
{   
   
    CPen *oldpen,pen;   
    pen.CreatePen(lineStyle,size,lineColor);   
    oldpen=pDC->SelectObject(&pen);   
    pDC->MoveTo(pStart);   
    pDC->LineTo(pEnd);   
    pDC->SelectObject(oldpen);   
}   
   
void CShape::DrawLine_Point_Len_Angle(CDC *pDC,CPoint pStart,double Len,COLORREF lineColor,   
        double AngToX,int size,int lineStyle)   
{   
       
    CPen *oldpen,pen;   
    pen.CreatePen(lineStyle,size,lineColor);   
    oldpen=pDC->SelectObject(&pen);   
    pDC->MoveTo(pStart);   
    pDC->LineTo(pStart.x+Len*cos(AngToX/180.0*pi),pStart.y-Len*sin(AngToX/180.0*pi));   
    pDC->SelectObject(oldpen);   
}   
void CShape::DrawLine_CenterPoint_Len_Angle(CDC *pDC,CPoint centerStart,double startLen,double endLen,COLORREF lineColor,   
        double AngToX,int size,int lineStyle)   
{   
    CPen *oldpen,pen;   
    pen.CreatePen(lineStyle,size,lineColor);   
    oldpen=pDC->SelectObject(&pen);   
    pDC->MoveTo(centerStart.x+startLen*cos(AngToX/180.0*pi),centerStart.y-startLen*sin(AngToX/180.0*pi));   
    pDC->LineTo(centerStart.x+endLen*cos(AngToX/180.0*pi),centerStart.y-endLen*sin(AngToX/180.0*pi));   
    pDC->SelectObject(oldpen);   
   
}   
   
void CShape::SetFontWide(int wide)   
{   
    if (wide<=0)   
    {   
        return;   
    }   
    m_Font.nWidth=wide;   
    m_Font.CreateNewFont();   
   
}   
   
void CShape::SwtFontHeight(int Height)   
{   
    if(Height<=0) return;   
    m_Font.nHeight=Height;   
    m_Font.CreateNewFont();   
   
}   
   
void CShape::SetFontAngle(double Angle)   
{   
    if(Angle<=0) return;   
    m_Font.nAngle=Angle;   
    m_Font.CreateNewFont();   
}   
   
void CShape::RestFont()   
{   
    m_Font.Rest();   
   
}   
   
   
void CShape::DrawLineTextH(CDC *pDC, POINT pos, CString str, COLORREF c)   
{   
    double oldang=m_Font.nAngle;   
    m_Font.nAngle=0;   
    m_Font.CreateNewFont();   
   
    CFont *old=pDC->SelectObject(&m_Font.m_font);   
    COLORREF oldColor=pDC->SetTextColor(c);   
    pDC->TextOut(pos.x,pos.y,str);   
    pDC->SelectObject(old);   
    pDC->SetTextColor(oldColor);   
   
    m_Font.nAngle=oldang;   
    m_Font.CreateNewFont();   
   
   
}   
void CShape::DrawLineTextV(CDC *pDC, POINT pos, CString str, COLORREF c)   
{   
    double oldang=m_Font.nAngle;   
    m_Font.nAngle=90;   
    m_Font.CreateNewFont();   
   
    CFont *old=pDC->SelectObject(&m_Font.m_font);   
    COLORREF oldColor=pDC->SetTextColor(c);   
    pDC->TextOut(pos.x,pos.y,str);   
    pDC->SelectObject(old);   
    pDC->SetTextColor(oldColor);   
   
    m_Font.nAngle=oldang;   
    m_Font.CreateNewFont();   
       
       
}   
void CShape::DrawLineText(CDC *pDC, POINT pos, CString str, COLORREF c)   
{   
    m_Font.CreateNewFont();   
    CFont *old=pDC->SelectObject(&m_Font.m_font);   
    COLORREF oldColor=pDC->SetTextColor(c);   
    pDC->TextOut(pos.x,pos.y,str);   
    pDC->SelectObject(old);   
    pDC->SetTextColor(oldColor);   
       
   
}   
void CShape::SetFontName(CString name)   
{   
    if (name.IsEmpty())   
    {   
        return;   
    }   
    m_Font.strName=name;   
    m_Font.CreateNewFont();   
}   
void CShape::SetFontDlg()   
{   
   
    m_Font.SetFontDlg();   
}   
void CShape::DrawCircleChineseText(CDC *pDC,POINT centerPoint,double r,double startAngToX,   
        CString str,COLORREF c,double m_nDis ,int style)   
{   
    double xTemp,yTemp;   
    double m_nAngle;   
    m_nAngle=360*m_nDis/r;   
    double arc;   
    arc = m_nAngle * pi/180.0;   
    POINT point=centerPoint;   
    CString st=str;   
    double oldAng=m_Font.nAngle;   
    COLORREF oldcolor=pDC->SetTextColor(c);   
   
    char cha[120][4];    
    char* temp;   
    char* p;   
       
    int nCha = strlen(st)/2;   
    temp = st.GetBuffer(0);   
    p = temp;   
	int i = 0;
    for(; i < nCha; i ++)          
    {   
        //将单个字保存在数组中   
        memcpy(cha[i], p, 2);   
        cha[i][3] = 0;   
        p += 2;   
    }      
   
    CFont *oldFont;   
    if (style==FONT_UNCLOCKWISE)   
        for( i = 0; i < st.GetLength()/2; i++)   
        {      
        xTemp = point.x + r * cos(startAngToX/180.0*pi+ double(i) * arc);   
        yTemp = point.y - r * sin(startAngToX/180.0*pi + double(i) * arc);   
        m_Font.nAngle= startAngToX+i * m_nAngle-90;   
        m_Font.CreateNewFont();   
        oldFont=pDC->SelectObject(&m_Font.m_font);      
        pDC->TextOut((int) xTemp, (int)yTemp, cha[i]);   
        pDC->SelectObject(oldFont);   
        }   
    else   
        for( i = 0; i < st.GetLength()/2; i++)   
        {      
            xTemp = point.x + r * cos(startAngToX/180.0*pi- double(i) * arc);   
            yTemp = point.y - r * sin(startAngToX/180.0*pi - double(i) * arc);   
            m_Font.nAngle=startAngToX-i * m_nAngle-90;   
            m_Font.CreateNewFont();   
            oldFont=pDC->SelectObject(&m_Font.m_font);      
            pDC->TextOut((int) xTemp, (int)yTemp, cha[i]);   
            pDC->SelectObject(oldFont);   
       
        }   
   
     m_Font.nAngle=oldAng;   
     pDC->SetTextColor(oldcolor);   
     m_Font.CreateNewFont();        
}   
void CShape::DrawCircleABCText(CDC *pDC,POINT centerPoint,double r,double startAngToX,   
        CString str,COLORREF c,double m_nDis ,int style)   
{   
    double xTemp,yTemp;   
    double m_nAngle;   
    m_nAngle=360*m_nDis/r;   
    double arc;   
    arc = m_nAngle * pi/180.0;   
    POINT point=centerPoint;   
    CString st=str,str1="1";   
    double oldAng=m_Font.nAngle;   
    COLORREF oldcolor=pDC->SetTextColor(c);   
       
    char cha[120][4];    
    char* temp;   
    char* p;   
       
    int nCha = strlen(st);   
    temp = st.GetBuffer(0);   
    p = temp; 
	int i = 0;
    for(; i < nCha; i ++)          
    {   
        //将单个字保存在数组中   
        memcpy(cha[i], p, 1);   
        cha[i][2] = 0;   
        p += 1;   
    }      
       
    CFont *oldFont;   
    if (style==FONT_UNCLOCKWISE)   
        for( i = 0; i < st.GetLength(); i++)   
        {      
            xTemp = point.x + r * cos(startAngToX/180.0*pi+ double(i) * arc);   
            yTemp = point.y - r * sin(startAngToX/180.0*pi + double(i) * arc);   
            m_Font.nAngle= startAngToX+i * m_nAngle-90;   
            m_Font.CreateNewFont();   
            oldFont=pDC->SelectObject(&m_Font.m_font);      
            pDC->TextOut((int) xTemp, (int)yTemp, cha[i]);   
            pDC->SelectObject(oldFont);   
        }   
        else   
            for( i = 0; i < st.GetLength(); i++)   
            {      
                xTemp = point.x + r * cos(startAngToX/180.0*pi- double(i) * arc);   
                yTemp = point.y - r * sin(startAngToX/180.0*pi - double(i) * arc);   
                m_Font.nAngle=startAngToX-i * m_nAngle-90;   
                m_Font.CreateNewFont();   
                oldFont=pDC->SelectObject(&m_Font.m_font);   
            //  str1.SetAt(0, cha[i]);   
                pDC->TextOut((int) xTemp, (int)yTemp, cha[i]);   
                pDC->SelectObject(oldFont);   
                   
            }   
               
            m_Font.nAngle=oldAng;   
            pDC->SetTextColor(oldcolor);   
     m_Font.CreateNewFont();        
   
}   
void CShape::DrawBkColor(CDC *pDC,CRect R,COLORREF c)   
{   
       
    CBrush *OLD,B(c);   
    OLD=pDC->SelectObject(&B);   
    pDC->Rectangle(R);   
    pDC->SelectObject(OLD);   
    B.DeleteObject();   
   
       
}  