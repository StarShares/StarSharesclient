// ButtonEx.cpp : 幚憰僼傽僀儖
//
#include "stdafx.h"
#include "afxdialogex.h"
#include "StarSharesclient.h"
#include "ButtonEx.h"


// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CShadeButtonST)

CButtonEx::CButtonEx()
{
	m_nFontSize = 90;
	m_clrText= RGB(184,184,184);
	m_clrBkColor = GetSysColor(COLOR_BTNFACE);
	m_bUnderLine = FALSE;

}

CButtonEx::CButtonEx( int nItem, int nSubItem, CRect rect, HWND hParent )
{
	m_inItem = nItem;
	m_inSubItem = nSubItem;
	m_rect = rect;
	m_hParent = hParent;
	bEnable = TRUE;

	m_nFontSize = 90;
	m_clrText= RGB(184,184,184);
	m_bUnderLine = FALSE;

	
	if (!(HFONT)m_FontUnder) {           // Create font only once.
			
            LOGFONT lf; 

			::ZeroMemory(&lf,sizeof(lf));  
			FromHandle(hParent)->GetFont()->GetLogFont(&lf);

            lf.lfUnderline = TRUE;  

            m_FontUnder.CreateFontIndirect(&lf);  
     } 

	if(!(HFONT)m_FontNormal) {
		LOGFONT lf;     
		::ZeroMemory(&lf,sizeof(lf));    
		FromHandle(hParent)->GetFont()->GetLogFont(&lf);

		lf.lfUnderline = FALSE;  

		m_FontNormal.CreateFontIndirect(&lf); 
	}
	
}

CButtonEx::~CButtonEx()
{
	
}


BEGIN_MESSAGE_MAP(CButtonEx, CShadeButtonST)
	ON_CONTROL_REFLECT(BN_CLICKED, &CButtonEx::OnBnClicked)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()



// CButtonEx 儊僢僙乕僕 僴儞僪儔 

void CButtonEx::SetBkColor(COLORREF clrBkColor)
{
	m_clrBkColor = clrBkColor;
}

void CButtonEx::OnBnClicked()
{
	::SendMessage( m_hParent, WM_BN_CLICK, m_inItem, m_inSubItem );
}

void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	//dc.

	if(m_bUnderLine)
		dc.SelectObject(&m_FontUnder);
	else
		dc.SelectObject(&m_FontNormal);
	dc.SetTextColor(m_clrText);
	dc.SetBkColor(m_clrBkColor);
	//dc.SetBkMode(TRANSPARENT);



	CString str;
	GetWindowText(str);
	dc.DrawText(str, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	dc.Detach();
}

void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//HCURSOR hCur = LoadCursor( NULL , IDC_HAND ) ;

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = m_hWnd;
	tme.dwFlags = TME_LEAVE | TME_HOVER;
	tme.dwHoverTime = 1;
	_TrackMouseEvent(&tme);	

	CShadeButtonST::OnMouseMove(nFlags, point);
}

void CButtonEx::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_clrText = RGB(56,165,250);
	m_bUnderLine = TRUE;

	Invalidate();

	CButton::OnMouseHover(nFlags, point);
}

void CButtonEx::OnMouseLeave()
{
	m_clrText = RGB(184,184,184);
	m_bUnderLine = FALSE;

	Invalidate();

	CButton::OnMouseLeave();

}


//IMPLEMENT_DYNAMIC(CButtonExEx, CButton)
//
//CButtonExEx::CButtonExEx()
//{
//	m_nFontSize = 90;
//	m_clrText= RGB(184,184,184);
//	m_bUnderLine = FALSE;
//}
//
//CButtonExEx::CButtonExEx( int nItem, int nSubItem, CRect rect, HWND hParent )
//{
//	m_inItem = nItem;
//	m_inSubItem = nSubItem;
//	m_rect = rect;
//	m_hParent = hParent;
//	bEnable = TRUE;
//
//	m_nFontSize = 90;
//	m_clrText= RGB(184,184,184);
//	m_bUnderLine = FALSE;
//}
//
//CButtonExEx::~CButtonExEx()
//{
//}
//
//
//BEGIN_MESSAGE_MAP(CButtonExEx, CButton)
//	ON_CONTROL_REFLECT(BN_CLICKED, &CButtonExEx::OnBnClicked)
//	ON_WM_MOUSEMOVE()
//	//ON_WM_MOUSELEAVE()
//END_MESSAGE_MAP()
//
//
//
//// CButtonEx 儊僢僙乕僕 僴儞僪儔
//
//void CButtonExEx::OnBnClicked()
//{
//	::SendMessage( m_hParent, WM_BN_CLICK, m_inItem, m_inSubItem );
//}
//
//void CButtonExEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	CDC dc;
//	dc.Attach(lpDrawItemStruct->hDC);
//
//	dc.SetTextColor(m_clrText);
//	dc.SetBkMode(TRANSPARENT);
//
//	CString str;
//	GetWindowText(str);
//	dc.DrawText(str, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//
//	dc.Detach();
//}
//
//void CButtonExEx::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	//HCURSOR hCur = LoadCursor( NULL , IDC_HAND ) ;
//
//	m_clrText = RGB(56,156,250);
//
//	UpdateData(FALSE);
//
//	CButton::OnMouseMove(nFlags, point);
//}



IMPLEMENT_DYNAMIC(CButtonCtrl, CShadeButtonST)

CButtonCtrl::CButtonCtrl()
{

}

CButtonCtrl::CButtonCtrl( int nItem, int nSubItem, CRect rect, HWND hParent ,void*pData)
{
	m_inItem = nItem;
	m_inSubItem = nSubItem;
	m_rect = rect;
	m_hParent = hParent;
	bEnable = TRUE;
	memcpy(&m_pData,pData,sizeof(ADD_APP_DATA));
}
CButtonCtrl::~CButtonCtrl()
{
	memset(&m_pData,0,sizeof(ADD_APP_DATA));
}


BEGIN_MESSAGE_MAP(CButtonCtrl, CShadeButtonST)
	ON_CONTROL_REFLECT(BN_CLICKED, &CButtonCtrl::OnBnClicked)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CButtonCtrl 消息



void CButtonCtrl::OnBnClicked()
{
	::SendMessage( m_hParent, WM_BN_CLICK, m_inItem, (LPARAM)this );
}




void CButtonCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//HCURSOR hCur = LoadCursor( NULL , IDC_HAND ) ;

	//SetCursor(hCur);
	CShadeButtonST::OnMouseMove(nFlags, point);
}





//void CButtonExEx::PreSubclassWindow()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	ModifyStyle(BS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);
//
//	CButton::PreSubclassWindow();
//}
