#pragma once


// CVEdit

class CVEdit : public CEdit
{
	DECLARE_DYNAMIC(CVEdit)

public:
	CVEdit();
	virtual ~CVEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void PreSubclassWindow();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT /*nCtlColor*/);

public:
	CFont* m_pFont; // 字体指针
	int m_nFontSize; // 字体大小
	CString m_csFontName; // 字体名称
	COLORREF m_clrText; // 文本颜色
	COLORREF m_clrBk; // 背景颜色
	BOOL m_bItalic; // 斜体
	BOOL m_bBold; // 粗体
	BOOL m_bUnderLine; // 下划线
	CBrush m_bkBrush; // 背景画刷

protected:
	void SetFontHelper(); // 重新创建并设置字体
	void DrawBkAndFrame(); // 画背景和边框

public:
	void SetTextColor(COLORREF clrText); // 设置文本颜色
	void SetBkColor(COLORREF clrBk); // 设置背景颜色
	void SetNewFont(int nFontSize, CString csFontName = _T("微软雅黑")); // 设置新字体
	void SetFontStyle(BOOL bBold=TRUE, BOOL bItalic=FALSE, BOOL bUnderLine=FALSE); // 设置字体样式

};


