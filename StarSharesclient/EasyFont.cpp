// EasyFont.cpp: implementation of the CEasyFont class.   
//   
//////////////////////////////////////////////////////////////////////   
/************************************************************************/   
/*   
* Copyright (c) 2009* All rights reserved. visualsan  
  
* AUTHOR:           ׯ����  
* ADDRESS:          �Ͼ����պ����ѧ��Դ�ڶ���ѧԺ  
* CONTECT:          visualsan@yahoo.cn    
* BUILD DATA:       20/7/2009  
* COMPLETION DATE:  22/7/2009  
* PRE-VERSION:      NONE  
* PRE-AUTHOR:       NONE  
* PRE-COMPLETION DATE:    
* NOTE:             һ��������ķ�װ��ʹCFont��ʹ�ø��ӷ���.  
                    ʹ�÷���Ϊ���ȸ���Ա������ֵ�������ָ߶�nHeight=20��  
                    Ȼ�����CreateNewFont()��֮�󼴿ɽ�m_font����pDC.                                                                    */   
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
    strName="����";   
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
    CFontDialog dlg(&LogFont); //��ʼ��������Ϣ   
    if (dlg.DoModal()==IDOK)   
    {   
        LOGFONT temp;   
        dlg.GetCurrentFont(&temp);    
        m_font.DeleteObject();//��ȡ��ǰ������Ϣ   
        m_font.CreateFontIndirect(&temp); //ֱ�Ӵ�������   
          //��������   
   
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
    strName="����";   
    CreateNewFont();   
       
}  