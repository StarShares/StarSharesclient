// EasyFont.h: interface for the CEasyFont class. 
// 
////////////////////////////////////////////////////////////////////// 
/************************************************************************/ 
/*  
* Copyright (c) 2009* All rights reserved. visualsan 
 
* AUTHOR:			庄三少 
* ADDRESS:          南京航空航天大学能源于动力学院 
* CONTECT:			visualsan@yahoo.cn	 
* BUILD DATA:		20/7/2009 
* COMPLETION DATE:	22/7/2009 
* PRE-VERSION:		NONE 
* PRE-AUTHOR:		NONE 
* PRE-COMPLETION DATE:	 
* NOTE:	            一个文字类的封装，使CFont的使用更加方便. 
                    使用方法为：先给成员变量赋值，如文字高度nHeight=20， 
					然后调用CreateNewFont()，之后即可将m_font载入pDC.                                                                    */ 
/************************************************************************/ 
#if !defined(AFX_EASYFONT_H__472EF77E_586B_4EF6_9076_1B905487E6C6__INCLUDED_) 
#define AFX_EASYFONT_H__472EF77E_586B_4EF6_9076_1B905487E6C6__INCLUDED_ 
 
#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
 
class CEasyFont   
{ 
public: 
	void SetFontDlg(); 
	void CreateNewFont(); 
	void Rest(); 
	CEasyFont(); 
	virtual ~CEasyFont(); 
	CFont m_font; 
 
	int nHeight;//文字高度 
	int nWidth;//文字高度 
	double nAngle;//文字角度 
	int nWeight;//文字厚度 
	CString strName;// 
 
	 
 
}; 
 
#endif // !defined(AFX_EASYFONT_H__472EF77E_586B_4EF6_9076_1B905487E6C6__INCLUDED_) 