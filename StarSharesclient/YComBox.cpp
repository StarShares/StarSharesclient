// LComBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "YComBox.h"

// CYComBox

IMPLEMENT_DYNAMIC(CYComBox, CComboBox)

CYComBox::CYComBox()
{
	m_pEdit = NULL;
	m_pListBox = NULL;
	m_pEdtFont = NULL;
	m_pListFont = NULL;
	m_nEdtFontPtSize = 0;
	m_nListFontPtSize = 0;
	m_csListFontName = _T("");
	m_csEdtFontName = _T("");
	m_clrEditText = RGB(0, 0, 0);
	m_clrListText = RGB(0, 0, 0);
	m_clrEditTextBg = RGB(255, 255, 255);
	m_clrListTextBg = RGB(255, 255, 255);
	m_bEditTextHasBgColor = FALSE;
	m_bListTextHasBgColor = FALSE;
	m_bReadOnly = FALSE;

	m_bBtnFlags = FALSE;
	m_bFocus = FALSE;
	m_bDown = FALSE;
	m_bPaint = FALSE;
	m_clrEdtFrame = RGB(148, 148, 148);

	m_clr3DHilight = RGB(181, 207, 231);
	m_clr3DShadow  = RGB(61, 123, 173);
	m_clr3DFace    = RGB(198, 201, 210);

	m_bDisableAC = FALSE;
	m_bAComplete = FALSE;

	m_bmButton.LoadBitmap(IDB_DROPBUTTON);

	m_fsFremeStyle = WIN7;
	// VC win7 ��Ͽ�Ĭ�ϱ߿���ɫֵ
	m_clrNormalCombFrameLeft = RGB( 226, 227, 234 );
	m_clrNormalCombFrameTop = RGB( 171, 173, 179);
	m_clrNormalCombFrameRight = RGB( 219, 223, 230);
	m_clrNormalCombFrameBottom = RGB( 227, 233, 239);
	m_clrFocusCombFrameLeft = RGB( 181, 207, 231);
	m_clrFocusCombFrameTop = RGB( 61, 123, 173);
	m_clrFocusCombFrameRight = RGB( 164, 201, 227);
	m_clrFocusCombFrameBottom = RGB( 183, 217, 237);
	// 
	m_clrNormalCombFrame = RGB( 233, 236, 240);
	m_clrFocusCombFrame = RGB( 119, 162, 192);
}

CYComBox::~CYComBox()
{
	if(m_pEdit)
		m_pEdit = NULL;

	if(m_pListBox)
		m_pListBox = NULL;

	if(m_pEdtFont)
	{
		m_pEdtFont->DeleteObject();
		delete m_pEdtFont;
		m_pEdtFont = NULL;
	}

	if(m_pListFont)
	{
		m_pListFont->DeleteObject();
		delete m_pListFont;
		m_pListFont = NULL;
	}

}


BEGIN_MESSAGE_MAP(CYComBox, CComboBox)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_CONTROL_REFLECT(CBN_DROPDOWN, &CYComBox::OnCbnDropdown)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, &CYComBox::OnCbnCloseup)
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetFocus)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillFocus)
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOLORCHANGE()
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, &CYComBox::OnCbnEditupdate)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


LRESULT CYComBox::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	CRect rcComboClient;
	GetClientRect(&rcComboClient);

	if(WM_CTLCOLORBTN==message)
	{
		HWND hWndBtn = (HWND)lParam;
		CButton* pButton = (CButton*)FromHandle(hWndBtn);
		CRect rcBtnClient;
		pButton->GetClientRect(&rcBtnClient);
		int i = 0;
	}

	if(WM_CTLCOLORSCROLLBAR==message)
	{
		HWND hWndBtn = (HWND)lParam;
		CScrollBar* pButton = (CScrollBar*)FromHandle(hWndBtn);
		CRect rcBtnClient;
		pButton->GetClientRect(&rcBtnClient);
		int i = 0;
	}

	if(WM_CTLCOLOREDIT==message)
	{
		HWND hWndEdit = (HWND)lParam;
		m_pEdit = (CEdit*)FromHandle(hWndEdit);
	}

	if(WM_CTLCOLORSTATIC==message)
	{
		HWND hWndStatic = (HWND)lParam;
		CStatic* pStatic = (CStatic*)FromHandle(hWndStatic);
		CRect rcStaticClient;
		pStatic->GetClientRect(&rcStaticClient);
	}

	if(WM_CTLCOLORLISTBOX==message)
	{
		HWND hWndListBox = (HWND)lParam;
		m_pListBox = (CListBox*)FromHandle(hWndListBox);
	}

	return CComboBox::WindowProc(message, wParam, lParam);
}


// CYComBox ��Ϣ�������

void CYComBox::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	// Ĭ������£������ͺ�ϵͳһ��������
	CFont* pFont = GetFont();
	LOGFONT lg;
	pFont->GetLogFont(&lg);
	m_nEdtFontPtSize = lg.lfHeight * 8;
	m_csEdtFontName = lg.lfFaceName;
	m_nListFontPtSize = m_nEdtFontPtSize;
	m_csListFontName = m_csEdtFontName;
	// ��������
	SetEdtFontHelper();
	SetListFontHelper();

	CComboBox::PreSubclassWindow();
}

HBRUSH CYComBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// ��Ͽ�ֻ��ʱ�ľ�̬�ı���ı���ɫ
	//if(nCtlColor==CTLCOLOR_EDIT)
	//{
	//	HBRUSH B = CreateSolidBrush(RGB(246, 248, 249));
	//	return (HBRUSH) B; //���ر�����ˢ���
	//}

	//// �༭������
	//if(nCtlColor==CTLCOLOR_EDIT)
	//{
	//	CFont* font = new CFont;
	//	font->CreatePointFont(m_nEdtFontPtSize, m_csEdtFontName);
	//	pDC->SelectObject(font);
	//	pDC->SetTextColor(m_clrEditText);
	//	
	//	if(m_bEditTextHasBgColor)
	//	pDC->SetBkColor(m_clrEditTextBg);
	//	else
	//		pDC->SetBkMode(TRANSPARENT);
	//	
	//	hbr = CreateSolidBrush(RGB(246, 248, 249));
	//	//return (HBRUSH) B; //���ػ�ˢ���
	//}

	//// �б������
	//if(nCtlColor==CTLCOLOR_LISTBOX)
	//{
	//	CFont* font = new CFont;
	//	font->CreatePointFont(m_nListFontPtSize, m_csListFontName);
	//	pDC->SelectObject(font);
	//	pDC->SetTextColor(m_clrListText);
	//	
	//	if(m_bListTextHasBgColor)
	//		pDC->SetBkColor(m_clrListTextBg);
	//	else
	//		pDC->SetBkMode(TRANSPARENT);

	//	pDC->SetBkColor(RGB(0, 255, 0));
	//	hbr = CreateSolidBrush(RGB(246, 248, 249));
	//	//return (HBRUSH) B; //���ػ�ˢ���
	//}

	//// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:
		{
			CFont* font = new CFont;
			font->CreatePointFont(m_nEdtFontPtSize, m_csEdtFontName);
			pDC->SelectObject(font);
			pDC->SetTextColor(m_clrEditText);

			if(m_bEditTextHasBgColor)
				pDC->SetBkColor(m_clrEditTextBg);
			else
				pDC->SetBkMode(TRANSPARENT);

			hbr = CreateSolidBrush(RGB(238,238,238));

			return hbr;
		}
	case CTLCOLOR_BTN:
	case CTLCOLOR_MSGBOX:
		{
			pDC->SetBkColor(RGB(238,238,238)); 
			hbr = ::CreateSolidBrush(RGB(238,238,238));  
		}
	}

	return hbr;
}

///////////////////////////////  ���ܺ���  ///////////////////////////////////////////

void CYComBox::SetEdtFontHelper()
{
	if(m_pEdtFont)
	{
		if(m_pEdtFont->m_hObject)
			m_pEdtFont->DeleteObject();

		delete m_pEdtFont;
		m_pEdtFont = NULL;
	}
	m_pEdtFont = new CFont;

	LOGFONT lgFont;
	lgFont.lfCharSet = DEFAULT_CHARSET;
	lgFont.lfClipPrecision = 0;
	lgFont.lfEscapement = 0;
	_tcscpy_s(lgFont.lfFaceName, m_csEdtFontName);
	lgFont.lfHeight = m_nEdtFontPtSize;
	lgFont.lfItalic = 0;
	lgFont.lfOrientation = 0;
	lgFont.lfOutPrecision = 0;
	lgFont.lfPitchAndFamily = 2;
	lgFont.lfQuality = 0;
	lgFont.lfStrikeOut = 0;
	lgFont.lfUnderline = 0;
	lgFont.lfWidth = 0;
	lgFont.lfWeight = FW_NORMAL;

	m_pEdtFont->CreatePointFontIndirect(&lgFont);
	SetFont(m_pEdtFont);
}

void CYComBox::SetListFontHelper()
{
	if(m_pListFont)
	{
		if(m_pListFont->m_hObject)
			m_pListFont->DeleteObject();

		delete m_pListFont;
		m_pListFont = NULL;
	}
	m_pListFont = new CFont;

	LOGFONT lgFont;
	lgFont.lfCharSet = DEFAULT_CHARSET;
	lgFont.lfClipPrecision = 0;
	lgFont.lfEscapement = 0;
	_tcscpy_s(lgFont.lfFaceName, m_csListFontName);
	lgFont.lfHeight = m_nListFontPtSize;
	lgFont.lfItalic = 0;
	lgFont.lfOrientation = 0;
	lgFont.lfOutPrecision = 0;
	lgFont.lfPitchAndFamily = 2;
	lgFont.lfQuality = 0;
	lgFont.lfStrikeOut = 0;
	lgFont.lfUnderline = 0;
	lgFont.lfWidth = 0;
	lgFont.lfWeight = FW_NORMAL;

	m_pListFont->CreatePointFontIndirect(&lgFont);
}

void CYComBox::SetCombNewFont( int nPtSize, CString csFontName/*=_T("΢���ź�")*/ )
{
	SetEdtNewFont(nPtSize, csFontName);
	SetListNewFont(nPtSize, csFontName);
}

void CYComBox::SetEdtNewFont( int nPtSize, CString csFontName/*=_T("΢���ź�")*/ )
{
	if(nPtSize>0)
		m_nEdtFontPtSize = nPtSize;
	m_csEdtFontName = csFontName;
	SetEdtFontHelper();
}

void CYComBox::SetListNewFont( int nPtSize, CString csFontName/*=_T("΢���ź�")*/ )
{
	if(nPtSize>0)
		m_nListFontPtSize = nPtSize;
	m_csListFontName = csFontName;
	SetListFontHelper();
}

void CYComBox::SetCombTextColor( COLORREF clrCombText )
{
	SetEdtTextColor(clrCombText);
	SetListTextColor(clrCombText);
}

void CYComBox::SetEdtTextColor( COLORREF clrEdtText )
{
	m_clrEditText = clrEdtText;
}

void CYComBox::SetListTextColor( COLORREF clrListText )
{
	m_clrListText = clrListText;
}

void CYComBox::SetEdtTextBgColor( BOOL bEditTextHasBgColor, COLORREF clrEditTextBg/*=RGB(255, 255, 255)*/ )
{
	m_bEditTextHasBgColor = bEditTextHasBgColor;
	if(bEditTextHasBgColor)
		m_clrEditTextBg = clrEditTextBg;
}

void CYComBox::SetListTextBgColor( BOOL bListTextHasBgColor, COLORREF clrListTextBg/*=RGB(255, 255, 255)*/ )
{
	m_bListTextHasBgColor = bListTextHasBgColor;
	if(bListTextHasBgColor)
		m_clrListTextBg = clrListTextBg;
}

void CYComBox::SetEdtReadOnly( BOOL bEdtReadOnly/*=TRUE*/ )
{
	m_bReadOnly = bEdtReadOnly;
	// ��ȡ��Ͽ��еı༭�򴰿�ָ�룬����ֻ������
	::CWnd *pWnd = this->GetWindow(GW_CHILD);
	while(pWnd)
	{
		TCHAR classname[256];
		::GetClassName(pWnd->m_hWnd, classname, 256);
		if(lstrcmpi(classname, _T("Edit")) == 0)
			break;
		if(pWnd)
			pWnd = pWnd->GetNextWindow();
	}
	CEdit *pEdit = (CEdit*)pWnd;
	m_pEdit = pEdit;
	m_pEdit->SetReadOnly(m_bReadOnly);
}

void CYComBox::AotuAdjustDroppedWidth()
{
	// ���������б�����
	CString csItem;
	int nWidth = 0; //GetDroppedWidth();
	CSize sz;

	CDC* pDC = this->GetDC();
	CFont* pOldFont = pDC->SelectObject(m_pListFont); // m_pListFont ��PreSubclassWindow ���Ѿ���ʼ���������Ч

	for(int i=0; i<GetCount(); i++)
	{
		GetLBText(i, csItem);
		sz = pDC->GetTextExtent(csItem);
		if(sz.cx>nWidth)
			nWidth = sz.cx;
	}

	// �����ֻ������Ԥ����ɾ�����Ŀ��
	if(m_bReadOnly)
		SetDroppedWidth(nWidth);
	else
		SetDroppedWidth(nWidth+21);

	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);
}

/////////////////////////////////  ��Ϣ����  /////////////////////////////////////////
void CYComBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CComboBox::OnPaint()

	//// ���Ʊ༭��߿�
	//CPen pen(PS_SOLID, 1, m_clrEdtFrame);
	//CPen* pOldPen = dc.SelectObject(&pen);
	//CRect rcClient;
	//this->GetClientRect(&rcClient);
	//rcClient.InflateRect(1, 1);
	//CPoint pt(5, 5);
	//dc.RoundRect(rcClient, pt);
	//dc.SelectObject(&pOldPen);

	OnNoFlickerPaint(&dc);

	COMBOBOXINFO combInfo;
	combInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&combInfo);
	if(combInfo.stateButton==8)
		m_bDown = TRUE;

	DrawBtnImg(&dc, combInfo.rcButton); // �����ұ�������ť

}

void CYComBox::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CComboBox::OnMouseMove(nFlags, point);
}

void CYComBox::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CComboBox::OnMouseHover(nFlags, point);
}

void CYComBox::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CComboBox::OnMouseLeave();
}

void CYComBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_bDown = TRUE;

	CComboBox::OnLButtonDown(nFlags, point);
}

void CYComBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_bDown = FALSE;
	Invalidate();

	CComboBox::OnLButtonUp(nFlags, point);
}

void CYComBox::OnCbnDropdown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bBtnFlags = TRUE;
	Invalidate(FALSE);
}

void CYComBox::OnCbnCloseup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bBtnFlags = FALSE;
	Invalidate(FALSE);
}

void CYComBox::OnKillFocus(/*CWnd* pNewWnd*/)
{
	//CComboBox::OnKillFocus(pNewWnd);
	
	// TODO: �ڴ˴������Ϣ����������

	m_bFocus = FALSE;
	CClientDC dc(this);
	DrawCombo(&dc, NORMAL, m_clr3DFace, m_clr3DFace);
	//DrawCombo(&dc, NORMAL, RGB(183, 217, 237), m_clr3DFace);
}

void CYComBox::OnSetFocus()
{
	//CComboBox::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������

	m_bFocus = TRUE;
	CClientDC dc(this);
	DrawCombo(&dc, RAISED, m_clr3DShadow, m_clr3DHilight);
	
}

BOOL CYComBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(message==WM_MOUSEMOVE)
	{
		CRect rcWnd;
		GetWindowRect(&rcWnd);
		if(rcWnd.PtInRect(GetCurrentMessage()->pt))
		{
			SetTimer(1, 10, NULL);
			OnTimer(1);
		}
	}

	return CComboBox::OnSetCursor(pWnd, nHitTest, message);
}

void CYComBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	UNREFERENCED_PARAMETER(nIDEvent);

	CClientDC dc(this);
	if(m_bDown)
	{
		KillTimer(1);
		if(m_bPaint)
		{
			DrawCombo(&dc, PRESSED, m_clr3DShadow, m_clr3DHilight);
			m_bPaint = FALSE;
		}
	}
	else if(!PointInRect() && !m_bFocus)
	{
		KillTimer(1);
		if(m_bPaint)
		{
			DrawCombo(&dc, PRESSED, m_clr3DFace, m_clr3DFace);
			//DrawCombo(&dc, NORMAL, RGB(183, 217, 237), m_clr3DFace);
			m_bPaint = FALSE;
		}
	}
	else
	{
		if(m_bPaint)
			return ;
		else
		{
			m_bPaint = TRUE;
			DrawCombo(&dc, PRESSED, m_clr3DShadow, m_clr3DHilight);
		}
	}

	CComboBox::OnTimer(nIDEvent);
}

BOOL CYComBox::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;

	return CComboBox::OnEraseBkgnd(pDC);
}

void CYComBox::OnSysColorChange()
{
	CComboBox::OnSysColorChange();

	//m_clr3DHilight = ::GetSysColor(COLOR_3DHILIGHT);
	//m_clr3DShadow  = ::GetSysColor(COLOR_3DSHADOW);
	//m_clr3DFace    = ::GetSysColor(COLOR_3DFACE);

	m_clr3DHilight = RGB(181, 207, 231);
	m_clr3DShadow  = RGB(61, 123, 173);
	m_clr3DFace    = RGB(226, 227, 234);
}

void CYComBox::OnCbnEditupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(m_bAComplete)
	{
		if (m_bDisableAC)
		{
			Default();
		}
		else
		{
			// Get the text in the edit box
			CString strItemTyped;
			GetWindowText(strItemTyped);
			int nLength = strItemTyped.GetLength();

			if (nLength >= 1)
			{
				// Currently selected range
				DWORD dwCurSel = GetEditSel();
				WORD dStart = LOWORD(dwCurSel);
				WORD dEnd   = HIWORD(dwCurSel);

				// Search for, and select in, and string in the combo box that is prefixed
				// by the text in the edit box
				if (SelectString(-1, strItemTyped) == CB_ERR)
				{
					SetWindowText(strItemTyped);     // No text selected, so restore what was there before
					if (dwCurSel != CB_ERR) {
						SetEditSel(dStart, dEnd);   //restore cursor postion
					}
				}

				// Set the text selection as the additional text that we have added
				if (dEnd < nLength && dwCurSel != CB_ERR) {
					SetEditSel(dStart, dEnd);
				}
				else {
					SetEditSel(nLength, -1);
				}
			}
		}
	}

}

BOOL CYComBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (m_bAComplete)
	{
		// Make sure that the keystrokes continue to the edit control.
		if (pMsg->message == WM_KEYDOWN || pMsg->message==WM_KEYUP)
		{
			if (pMsg->message == WM_KEYDOWN)
			{
				if (pMsg->wParam == VK_DELETE ||
					pMsg->wParam == VK_BACK)
				{
					m_bDisableAC = TRUE;
				}
			}

			if (pMsg->message == WM_KEYUP)
			{
				if (pMsg->wParam == VK_DELETE ||
					pMsg->wParam == VK_BACK)
				{
					m_bDisableAC = FALSE;
				}
			}

			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);

			return TRUE;
		}
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

/////////////////////////////  ���ܺ���  ///////////////////////////////////////

void CYComBox::SetAutoComplete( BOOL bAutoComplete )
{
	m_bAComplete = bAutoComplete;
}

void CYComBox::SetFrameStyle( FRAMESTYLE fsFrameStyle )
{
	m_fsFremeStyle = fsFrameStyle;
}

void CYComBox::Set3DFrameColor( COLORREF clr3Dface, COLORREF clr3DHilight, COLORREF clr3DShadow )
{
	m_clr3DFace = clr3Dface;
	m_clr3DHilight = clr3DHilight;
	m_clr3DShadow = clr3DShadow;
}

void CYComBox::Set3DFrameColorDefault()
{
	m_clr3DHilight = RGB(181, 207, 231);
	m_clr3DShadow  = RGB(61, 123, 173);
	m_clr3DFace    = RGB(198, 201, 210);
}

void CYComBox::SetEdtFrameColor( COLORREF clrEdtFrame/*=RGB(148, 148, 148)*/ )
{
	m_clrEdtFrame = clrEdtFrame;
	m_clr3DFace = clrEdtFrame;
	m_clr3DHilight = clrEdtFrame;
	m_clr3DShadow = clrEdtFrame;
}

void CYComBox::DrawBtnImg( CDC* pDC, CRect rcButton )
{
	CBitmap* pOldBitmap;
	CDC* pMemDC = new CDC;
	BITMAP bitmapBtn;
	m_bmButton.GetBitmap(&bitmapBtn); // ��ȡλͼ��Ϣ
	// ��Ա���ͼƬ���е��ض�����
	int nLeft = (rcButton.Width()-bitmapBtn.bmWidth/2)/2;
	int nTop = (rcButton.Height()-bitmapBtn.bmHeight/2)/2;

	// ��λͼ���ڴ�
	pMemDC->CreateCompatibleDC(pDC);
	pOldBitmap = pMemDC->SelectObject(&m_bmButton);
	// ���ݲ�ͬ��״̬��ȡͼƬ�Ĳ�ͬ���֣�������ֻ������
	//if(m_bDown || m_bFocus)
	if(PointInBtn())
		pDC->BitBlt(rcButton.left + nLeft, rcButton.top+nTop, rcButton.Width()/2, rcButton.Height(), pMemDC, 0, 0, SRCCOPY);
	else
		pDC->BitBlt(rcButton.left + nLeft, rcButton.top+nTop, rcButton.Width()/2, rcButton.Height(), pMemDC, 0, 0, SRCCOPY);

	pMemDC->SelectObject(pOldBitmap);

	// �ͷ��ڴ棬 ɾ��DC
	ReleaseDC(pMemDC);
	delete pMemDC;
	pMemDC = NULL;
}

void CYComBox::OnNoFlickerPaint(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CDC dcMem; // �ڴ��豸�����ģ�DC��
	dcMem.CreateCompatibleDC(pDC); // ���������豸DC
	dcMem.SetMapMode(pDC->GetMapMode()); // ����ӳ��ģʽ

	CBitmap bitmap; // ��������λͼ��ʹ����������������ͼ��
	bitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());

	CBitmap* pOldBitmap = dcMem.SelectObject(&bitmap); // ���ڴ�DCѡ��λͼ

	//dcMem.FillSolidRect(rcClient, m_clr3DFace);
	dcMem.FillSolidRect(rcClient, RGB(246,248,249));
	//rcClient.DeflateRect(1, 1);

	if(PointInRect() || m_bFocus)
		DrawCombo(&dcMem, RAISED, m_clr3DShadow, m_clr3DHilight);
	else
		DrawCombo(&dcMem, NORMAL, m_clr3DFace/*RGB(183, 217, 237)*/, m_clr3DFace);

	pDC->BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),
		&dcMem, rcClient.left, rcClient.top, SRCCOPY);

	dcMem.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	dcMem.DeleteDC();
}

void CYComBox::DrawCombo(CDC* pDC, STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	CRect rcItem;
	GetClientRect(&rcItem);
	if(m_fsFremeStyle==THREEDGR)
		pDC->Draw3dRect(rcItem, clrTopLeft, clrBottomRight);
	else if(m_fsFremeStyle==ONLYONE)
		pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
	else if(m_fsFremeStyle==TWO)
		pDC->Draw3dRect(rcItem, clrBottomRight, clrBottomRight);
	else if(m_fsFremeStyle==WIN7)
	{
		// ��ϵͳĬ����ɫ����
		// int nRound = 2;
		if(PointInRect() || m_bFocus)
		{
			CPen bgItemPen;
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrame);
			CPen* pOldPen = pDC->SelectObject(&bgItemPen);
			//pDC->RoundRect(&rcItem, CPoint(nRound, nRound));
			pDC->SelectObject(pOldPen);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameLeft);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.left, rcItem.bottom);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameTop);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.top);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameRight);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.right, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameBottom);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.bottom);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// ���ýǵ��������ɫ
			// ����
			pDC->SetPixel(CPoint(rcItem.left, rcItem.top), RGB(173, 196, 215));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top), RGB(92, 147, 188));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top+1), RGB(198, 222, 236));
			// ����
			pDC->SetPixel(CPoint(rcItem.right, rcItem.top), RGB(173, 196, 215));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top), RGB(92, 147, 188));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top+1), RGB(198, 222, 236));
			// ����
			pDC->SetPixel(CPoint(rcItem.left, rcItem.bottom), RGB( 218, 228, 237));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.bottom-1), RGB(198, 222, 238));
			// ����
			pDC->SetPixel(CPoint(rcItem.right, rcItem.bottom), RGB( 218, 228, 237));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.bottom-1), RGB(198, 222, 238));
		}
		else
		{
			CPen bgItemPen;
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrame);
			CPen* pOldPen = pDC->SelectObject(&bgItemPen);
			//pDC->RoundRect(&rcItem, CPoint(nRound, nRound));
			pDC->SelectObject(pOldPen);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameLeft);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.left, rcItem.bottom);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameTop);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.top);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameRight);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.right, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// ��
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameBottom);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.bottom);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// ���ýǵ��������ɫ
			// ����
			pDC->SetPixel(CPoint(rcItem.left, rcItem.top), RGB(214, 215, 217));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top), RGB(187, 189, 194));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top+1), RGB(233, 236, 240));
			// ����
			pDC->SetPixel(CPoint(rcItem.right, rcItem.top), RGB(214, 215, 217));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top), RGB(187, 189, 194));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top+1), RGB(233, 236, 240));
			// ����
			pDC->SetPixel(CPoint(rcItem.left, rcItem.bottom), RGB( 235, 235, 238));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.bottom-1), RGB(233, 236, 240));
			// ����
			pDC->SetPixel(CPoint(rcItem.right, rcItem.bottom), RGB( 235, 235, 238));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.bottom-1), RGB(233, 236, 240));
		}
	}

	// ������ǻ�������ť�ı߿��
	/*rcItem.DeflateRect(1, 1);

	if(!IsWindowEnabled())
	pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
	else
	pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
	*/
	/*rcItem.DeflateRect(1, 1);
	rcItem.left = rcItem.right - 18;
	pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);

	rcItem.DeflateRect(1, 1);
	pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);

	if(IsWindowEnabled())
	{
		rcItem.InflateRect(0, 1);
		switch(eState)
		{
		case NORMAL:
			{
				pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
				rcItem.left -= 1;
				pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
			}
			break;
		case RAISED:
			{
				pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
			}
			break;
		case PRESSED:
			{
				rcItem.OffsetRect(1, 1);
				pDC->Draw3dRect(rcItem, m_clr3DShadow, m_clr3DHilight);
			}
			break;
		default:
			break;
		}
	}*/
}

BOOL CYComBox::PointInRect()
{
	CPoint pt; 
	GetCursorPos(&pt); 
	CRect rcItem; 
	GetWindowRect(&rcItem); 
	return rcItem.PtInRect(pt);
}

BOOL CYComBox::PointInBtn()
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left = rcClient.right - 18;
	return rcClient.PtInRect(point);
}

void CYComBox::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CComboBox::OnDrawItem(nIDCtl, lpDrawItemStruct);


}
