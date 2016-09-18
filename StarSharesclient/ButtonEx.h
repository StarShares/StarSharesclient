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
	int				m_nFontSize;			// 字体大小
	CString			m_strFontName;			// 字体名称
	COLORREF		m_clrText;				//文本颜色
	COLORREF		m_clrBkColor;			//按钮背景色
	BOOL			m_bUnderLine;			//下划线
	CFont			m_pFont;
	CFont			m_FontUnder;
	CFont           m_FontNormal;

	LOGFONT			m_lf;
	LOGFONT			m_lfUnder;

public:
	void SetTextColor(COLORREF clrTextColor);	// 设置文本颜色
	void SetBkColor(COLORREF clrBkColor);		//设置背景颜色

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
//	int				m_nFontSize;			// 字体大小
//	CString			m_strFontName;			// 字体名称
//	COLORREF		m_clrText;				//文本颜色
//	BOOL			m_bUnderLine;			//下划线
//
//
//public:
//	void SetTextColor(COLORREF clrText); // 设置文本颜色
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
	ADD_APP_DATA m_pData;         //按钮带的用户自定义数据

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
};
