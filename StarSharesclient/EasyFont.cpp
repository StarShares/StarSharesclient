// EasyFont.cpp: implementation of the CEasyFont class.   
//   
//////////////////////////////////////////////////////////////////////   
/************************************************************************/   
/*   
* Copyright (c) 2009* All rights reserved. visualsan  
  
* AUTHOR:           庄三少  
* ADDRESS:          南京航空航天大学能源于动力学院  
* CONTECT:          visualsan@yahoo.cn    
* BUILD DATA:       20/7/2009  
* COMPLETION DATE:  22/7/2009  
* PRE-VERSION:      NONE  
* PRE-AUTHOR:       NONE  
* PRE-COMPLETION DATE:    
* NOTE:             一个文字类的封装，使CFont的使用更加方便.  
                    使用方法为：先给成员变量赋值，如文字高度nHeight=20，  
                    然后调用CreateNewFont()，之后即可将m_font载入pDC.                                                                    */   
/************************************************************************/   
#include "stdafx.h"   
#include "EasyFont.h"   
   
#ifdef _DEBUG   
#undef THIS_FILE   
static char THIS_FILE[]=__FILE__;   
#define new DEBUG_NEW   
#endif   
   
//////////////////////////////////////////////////////////////////////   
// Construction/Destruction   
//////////////////////////////////////////////////////////////////////   
   
CEasyFont::CEasyFont()   
{   
    nHeight=15;   
    nWidth=10;   
    nAngle=0;   
    nWeight=FW_NORMAL;   
    strName="宋体";   
    CreateNewFont();   
}   
   
CEasyFont::~CEasyFont()   
{   
    m_font.DeleteObject();   
   
}   
   
void CEasyFont::CreateNewFont()   
{   
    m_font.DeleteObject();   
    m_font.CreateFont(nHeight,nWidth,nAngle*10,0,nWeight,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,   
            CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_ROMAN,strName);   
   
}   
   
   
   
void CEasyFont::SetFontDlg()   
{   
       
    LOGFONT LogFont;   
    m_font.GetLogFont(&LogFont);   
    CFontDialog dlg(&LogFont); //初始化字体信息   
    if (dlg.DoModal()==IDOK)   
    {   
        LOGFONT temp;   
        dlg.GetCurrentFont(&temp);    
        m_font.DeleteObject();//获取当前字体信息   
        m_font.CreateFontIndirect(&temp); //直接创建字体   
          //设置字体   
   
        strName.Format("%c",temp.lfFaceName);   
        nAngle=temp.lfEscapement/10.0;   
        nHeight=temp.lfHeight;   
        nWidth=temp.lfWidth;   
        nWeight=temp.lfWeight;   
    }   
   
   
}   
void CEasyFont::Rest()   
{   
    nHeight=15;   
    nWidth=10;   
    nAngle=0;   
    nWeight=FW_NORMAL;   
    strName="宋体";   
    CreateNewFont();   
       
}  