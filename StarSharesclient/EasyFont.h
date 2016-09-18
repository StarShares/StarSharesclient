// EasyFont.h: interface for the CEasyFont class. 
// 
////////////////////////////////////////////////////////////////////// 
/************************************************************************/ 
/*  
* Copyright (c) 2009* All rights reserved. visualsan 
 
* AUTHOR:			ׯ���� 
* ADDRESS:          �Ͼ����պ����ѧ��Դ�ڶ���ѧԺ 
* CONTECT:			visualsan@yahoo.cn	 
* BUILD DATA:		20/7/2009 
* COMPLETION DATE:	22/7/2009 
* PRE-VERSION:		NONE 
* PRE-AUTHOR:		NONE 
* PRE-COMPLETION DATE:	 
* NOTE:	            һ��������ķ�װ��ʹCFont��ʹ�ø��ӷ���. 
                    ʹ�÷���Ϊ���ȸ���Ա������ֵ�������ָ߶�nHeight=20�� 
					Ȼ�����CreateNewFont()��֮�󼴿ɽ�m_font����pDC.                                                                    */ 
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
 
	int nHeight;//���ָ߶� 
	int nWidth;//���ָ߶� 
	double nAngle;//���ֽǶ� 
	int nWeight;//���ֺ�� 
	CString strName;// 
 
	 
 
}; 
 
#endif // !defined(AFX_EASYFONT_H__472EF77E_586B_4EF6_9076_1B905487E6C6__INCLUDED_) 