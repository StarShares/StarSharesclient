#pragma once
#include "ShadeButtonST.h"
#include "config.h"

// CButtonEx

class CButtonEx : public CShadeButtonST
{
	DECLARE_DYNAMIC(CButtonEx)
public:
	CButtonEx();
	CButtonEx( int nItem, int nSubItem, CRect rect, HWND hParent );
	virtual ~CButtonEx();

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	int m_inItem;
	int m_inSubItem;
	CRect m_rect;
	HWND m_hParent;
	BOOL bEnable;

public:
	int				m_nFontSize;			// �����С
	CString			m_strFontName;			// ��������
	COLORREF		m_clrText;				//�ı���ɫ
	COLORREF		m_clrBkColor;			//��ť����ɫ
	BOOL			m_bUnderLine;			//�»���
	CFont			m_pFont;
	CFont			m_FontUnder;
	CFont           m_FontNormal;

	LOGFONT			m_lf;
	LOGFONT			m_lfUnder;

public:
	void SetTextColor(COLORREF clrTextColor);	// �����ı���ɫ
	void SetBkColor(COLORREF clrBkColor);		//���ñ�����ɫ

};


//class CButtonExEx : public CButton
//{
//	DECLARE_DYNAMIC(CButtonExEx);
//
//public:
//	CButtonExEx();
//	CButtonExEx( int nItem, int nSubItem, CRect rect, HWND hParent );
//	virtual ~CButtonExEx();
//
//	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//
//protected:
//	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnBnClicked();
//	int m_inItem;
//	int m_inSubItem;
//	CRect m_rect;
//	HWND m_hParent;
//	BOOL bEnable;
//
//
//public:
//	int				m_nFontSize;			// �����С
//	CString			m_strFontName;			// ��������
//	COLORREF		m_clrText;				//�ı���ɫ
//	BOOL			m_bUnderLine;			//�»���
//
//
//public:
//	void SetTextColor(COLORREF clrText); // �����ı���ɫ
//	virtual void PreSubclassWindow();
//};



class CButtonCtrl : public CShadeButtonST
{
	DECLARE_DYNAMIC(CButtonCtrl)
public:
	CButtonCtrl();
	CButtonCtrl( int nItem, int nSubItem, CRect rect, HWND hParent ,void*pData);
	virtual ~CButtonCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	int m_inItem;
	int m_inSubItem;
	CRect m_rect;
	HWND m_hParent;
	BOOL bEnable;
	ADD_APP_DATA m_pData;         //��ť�����û��Զ�������

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
};
