// VEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "VEdit.h"


// CVEdit

IMPLEMENT_DYNAMIC(CVEdit, CEdit)

CVEdit::CVEdit()
{
	m_nFontSize = 90;
	m_csFontName = _T("微软雅黑");
	m_pFont = new CFont;
	m_pFont->CreatePointFont(m_nFontSize, m_csFontName);
	m_bItalic = FALSE;
	m_bBold = FALSE;
	m_bUnderLine = FALSE;
	m_clrText = RGB(0, 0, 0);
	m_clrBk = RGB(255, 255, 255);
	m_bkBrush.CreateSolidBrush(m_clrBk);

}

CVEdit::~CVEdit()
{
	if(m_pFont)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
		m_pFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CVEdit, CEdit)
	ON_WM_NCCALCSIZE()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CVEdit 消息处理程序




void CVEdit::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(!m_pFont)
	{
		CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);
		return ;
	}

	// 用来计算的样本数据
	CString csTest = _T("编辑框VCenterAlign");
	SIZE sz;

	// 创建DC，设置参照计算的字体
	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(m_pFont);
	// 计算 m_Font 字体的字符高宽
	GetTextExtentPoint32(pDC->GetSafeHdc(), csTest, csTest.GetLength(), &sz);
	pDC->SelectObject(pOldFont);

	// 编辑框的上下左右边框，默认各为2像素，下面的高度计算中需要减去上下边框高度
	//int nFrame = 2*2;
	// 编辑框默认可编辑区顶部也有1个像素边框
	int nTextTopFrame = 1;

	double dTemp =  (lpncsp->rgrc[0].bottom-lpncsp->rgrc[0].top-sz.cy)/2.0 ;
	if(dTemp>(int)dTemp)
		dTemp = (double)( (int)dTemp+1 );

	int nBorder = (int)dTemp -nTextTopFrame;
	if(nBorder<0)
		nBorder = 0;

	lpncsp->rgrc[0].top += nBorder;
	//lpncsp[0].rgrc->bottom = lpncsp[0].rgrc->top + sz.cy + nBorder;

	CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CVEdit::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	SetFont(m_pFont);
	SetFontHelper();
	CEdit::PreSubclassWindow();
}

void CVEdit::SetNewFont( int nFontSize, CString csFontName/* = _T("微软雅黑")*/ )
{
	m_nFontSize = nFontSize;
	m_csFontName = csFontName;
	SetFontHelper();
}

void CVEdit::SetFontHelper()
{
	if(m_pFont)
	{
		if(m_pFont->m_hObject)
			m_pFont->DeleteObject();

		delete m_pFont;
		m_pFont = NULL;
	}

	m_pFont = new CFont;

	CDC* pDC = this->GetDC();
	LOGFONT lgFont;
	lgFont.lfCharSet = DEFAULT_CHARSET;
	lgFont.lfClipPrecision = 0;
	lgFont.lfEscapement = 0;
	_tcscpy_s(lgFont.lfFaceName, m_csFontName);
	lgFont.lfHeight = m_nFontSize;
	lgFont.lfItalic = m_bItalic;
	lgFont.lfOrientation = 0;
	lgFont.lfOutPrecision = 0;
	lgFont.lfPitchAndFamily = 2;
	lgFont.lfQuality = 0;
	lgFont.lfStrikeOut = 0;
	lgFont.lfUnderline = m_bUnderLine;
	lgFont.lfWidth = 0;
	if(m_bBold)
		lgFont.lfWeight = FW_BOLD;
	else
		lgFont.lfWeight = FW_NORMAL;

	m_pFont->CreatePointFontIndirect(&lgFont);
	SetFont(m_pFont);

	// 通过 MoveWindow 触发 WM_NCCALCSIZE 消息的发送，需注意必须窗口大小有变化时才能触发成功
	CRect rcClient;
	GetWindowRect(&rcClient);
	GetParent()->ScreenToClient(&rcClient);
	// 改变窗口大小，触发 WM_NCCALCSIZE
	MoveWindow(rcClient.left, rcClient.top, rcClient.Width()+1, rcClient.Height());
	// 恢复窗口大小，也触发了 WM_NCCALCSIZE
	MoveWindow(rcClient.left, rcClient.top, rcClient.Width()-1, rcClient.Height()); 

}

void CVEdit::SetFontStyle( BOOL bBold/*=TRUE*/, BOOL bItalic/*=FALSE*/, BOOL bUnderLine/*=FALSE*/ )
{
	m_bBold = bBold;
	m_bItalic = bItalic;
	m_bUnderLine = bUnderLine;
	// 重建字体
	SetFontHelper();
}


HBRUSH CVEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  在此更改 DC 的任何特性

	DrawBkAndFrame();
	pDC->SetTextColor(m_clrText);
	//pDC->SetBkColor(m_clrBk);
	pDC->SetBkMode(TRANSPARENT);

	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
	return m_bkBrush;
}

void CVEdit::SetTextColor( COLORREF clrText )
{
	m_clrText = clrText;
}

void CVEdit::SetBkColor( COLORREF clrBk )
{
	m_clrBk = clrBk;
	// 重建背景画刷
	if(m_bkBrush.m_hObject)
	{
		m_bkBrush.DeleteObject();
	}
	m_bkBrush.CreateSolidBrush(m_clrBk);
}

void CVEdit::DrawBkAndFrame()
{
	CRect rcClient, rcWnd;
	CDC* pDC = this->GetDC();
	GetClientRect(&rcClient);
	GetWindowRect(&rcWnd);
	ScreenToClient(&rcWnd);

	CRect rcFill;
	rcFill = rcWnd;
	rcFill.bottom = rcClient.top;
	pDC->FillRect(rcFill, &m_bkBrush);

	rcFill = rcWnd;
	rcFill.top = rcClient.bottom;
	pDC->FillRect(rcFill, &m_bkBrush);

	pDC->FrameRect(rcWnd, &m_bkBrush);


	ReleaseDC(pDC);
}
