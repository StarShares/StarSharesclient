// AppsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "AppsDlg.h"


// CAppsDlg

IMPLEMENT_DYNAMIC(CAppsDlg, CDialogBar)

CAppsDlg::CAppsDlg()
{
	m_pBmp = NULL ;

	m_pYYYEBar = NULL;
	m_pRGZCBar = NULL;
	m_pWDZCBar = NULL;
	m_pZCInBar = NULL;
	m_pZCOutBar = NULL;
}

CAppsDlg::~CAppsDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}

	if(NULL != m_pYYYEBar)
	{
		delete m_pYYYEBar;
	}
	if(NULL != m_pRGZCBar)
	{
		delete m_pRGZCBar;
	}
	if(NULL != m_pWDZCBar)
	{
		delete m_pWDZCBar;
	}
	if(NULL != m_pZCInBar)
	{
		delete m_pZCInBar;
	}

	if(NULL != m_pZCOutBar)
	{
		delete m_pZCOutBar;
	}
}


BEGIN_MESSAGE_MAP(CAppsDlg, CDialogBar)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()

	ON_MESSAGE(WM_INBACK_MYASSERT, OnInBackToMyAssert)
	ON_MESSAGE(WM_OUTBACK_MYASSERT, OnOutBackToMyAssert)


	ON_BN_CLICKED(IDC_BTN_YYYE, &CAppsDlg::OnBnClickedBtnYyye)
	//ON_BN_CLICKED(IDC_BTN_FXZC, &CAppsDlg::OnBnClickedBtnFxzc)
	ON_BN_CLICKED(IDC_BTN_RGZC, &CAppsDlg::OnBnClickedBtnRgzc)
	ON_BN_CLICKED(IDC_BTN_WDZC, &CAppsDlg::OnBnClickedBtnWdzc)
END_MESSAGE_MAP()



// CAppsDlg 消息处理程序


void CAppsDlg::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogBar::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_YYYE	, m_rBtnYYYE );
	DDX_Control(pDX, IDC_BTN_RGZC	, m_rBtnRGZC );
	DDX_Control(pDX, IDC_BTN_WDZC	, m_rBtnWDZC );

}

void CAppsDlg::SetBkBmpNid( UINT nBitmapIn ) 
{
	if( NULL != m_pBmp ) {
		::DeleteObject( m_pBmp ) ;
		m_pBmp = NULL ;
	}
	m_pBmp	= NULL ;
	HINSTANCE	hInstResource = NULL;	
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmapIn), RT_BITMAP);
	if( NULL != hInstResource ) {
		m_pBmp = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapIn), IMAGE_BITMAP, 0, 0, 0);
	}
}

BOOL CAppsDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect   rect; 
	GetClientRect(&rect); 

	if(m_pBmp   !=   NULL) { 
		BITMAP   bm; 
		CDC   dcMem; 
		::GetObject(m_pBmp,sizeof(BITMAP),   (LPVOID)&bm); 
		dcMem.CreateCompatibleDC(NULL); 
		HBITMAP     pOldBitmap   =(HBITMAP   )   dcMem.SelectObject(m_pBmp); 
		pDC-> StretchBlt(rect.left,rect.top-1,rect.Width(),rect.Height(),   &dcMem,   0,   0,bm.bmWidth-1,bm.bmHeight-1,   SRCCOPY); 

		dcMem.SelectObject(pOldBitmap);
		dcMem.DeleteDC();
	} else  
		CWnd::OnEraseBkgnd(pDC); 

	return 1;
}

int CAppsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetBkBmpNid( IDB_BITMAP_YYBAR ) ;
	CRect rect ;
	GetParent()->GetClientRect( rect ) ;
	if( NULL == m_pYYYEBar ){
		m_pYYYEBar = new CYYYEDlg ;
		m_pYYYEBar->Create(CYYYEDlg::IDD, this);
		m_pYYYEBar->ShowWindow(SW_HIDE);

		m_pYYYEBar->SetWindowPos(NULL, 120, 0, rect.Width() - 120, rect.Height() - 100 - 40, SWP_SHOWWINDOW);
	}
	if(NULL == m_pRGZCBar)
	{
		m_pRGZCBar = new CRGZCDlg;
		m_pRGZCBar->Create(CRGZCDlg::IDD, this);
		m_pRGZCBar->ShowWindow(SW_HIDE);

		m_pRGZCBar->SetWindowPos(NULL, 120, 0, rect.Width() - 120, rect.Height() - 100 - 40, SWP_SHOWWINDOW);
	}
	if(NULL == m_pWDZCBar)
	{
		m_pWDZCBar = new CWDZCDlg;
		m_pWDZCBar->Create(CWDZCDlg::IDD, this);
		m_pWDZCBar->ShowWindow(SW_HIDE);

		m_pWDZCBar->SetWindowPos(NULL, 120, 0, rect.Width() - 120, rect.Height() - 100 - 40, SWP_SHOWWINDOW);
	}

	if(NULL == m_pZCInBar)
	{
		m_pZCInBar = new CZCInDlg;
		m_pZCInBar->Create(CZCInDlg::IDD, this);
		m_pZCInBar->ShowWindow(SW_HIDE);

		m_pZCInBar->SetWindowPos(NULL, 120, 0, rect.Width() - 120, rect.Height() - 100 - 40, SWP_SHOWWINDOW);
	}

	if(NULL == m_pZCOutBar)
	{
		m_pZCOutBar = new CZCOutDlg;
		m_pZCOutBar->Create(CZCOutDlg::IDD, this);
		m_pZCOutBar->ShowWindow(SW_HIDE);

		m_pZCOutBar->SetWindowPos(NULL, 120, 0, rect.Width() - 120, rect.Height() - 100 - 40, SWP_SHOWWINDOW);
	}

	return 0;
}


void CAppsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != GetSafeHwnd() ) {
		CRect rect ; 

		CButton *p_Button = (CButton*)GetDlgItem(IDC_BTN_YYYE);
		if( NULL != p_Button ) {
			p_Button->GetWindowRect(&rect);
			p_Button->SetWindowPos( NULL ,12 , 50,rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}
		p_Button = (CButton*)GetDlgItem(IDC_BTN_RGZC);
		if( NULL != p_Button ) {
			p_Button->GetWindowRect(&rect);
			p_Button->SetWindowPos( NULL ,12 , 100 , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		p_Button = (CButton*)GetDlgItem(IDC_BTN_WDZC);
		if( NULL != p_Button ) {
			p_Button->GetWindowRect(&rect);
			p_Button->SetWindowPos( NULL ,12 , 150 , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
	}

	ActiveDlg(CYYYEDlg::IDD);
}


BOOL CAppsDlg::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类

	BOOL bRes =  CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if ( bRes ) {
		

		m_rBtnYYYE.LoadBitmaps(IDB_BITMAP_YYYE1);
		m_rBtnRGZC.LoadBitmaps(IDB_BITMAP_RGZC1);
		m_rBtnWDZC.LoadBitmaps(IDB_BITMAP_WDZC1);

		UpdateData(FALSE);	
	}
	return bRes ;
}

LRESULT CAppsDlg::OnInBackToMyAssert(WPARAM wParam, LPARAM lParam)
{
	ActiveDlg((int)wParam);
	return 0;
}

LRESULT CAppsDlg::OnOutBackToMyAssert(WPARAM wParam, LPARAM lParam)
{
	ActiveDlg((int)wParam);

	return 0;
}



void CAppsDlg::MobileTip(UINT nButtonID , BOOL bFlag )
{
	if ( m_nButtonID == nButtonID  && !bFlag ) {
		return ;
	}
	InitBtStatus(m_nButtonID);
	switch(nButtonID)
	{
	case CYYYEDlg::IDD:
		m_rBtnYYYE.LoadBitmaps(IDB_BITMAP_YYYE2);
		 break;
	case CRGZCDlg::IDD:
		m_rBtnRGZC.LoadBitmaps(IDB_BITMAP_RGZC2);
		break;

	case CZCInDlg::IDD:
	case CZCOutDlg::IDD:
	case CWDZCDlg::IDD:
		m_rBtnWDZC.LoadBitmaps(IDB_BITMAP_WDZC2);
		break;
	
	}
	m_nButtonID = nButtonID ;

	this->Invalidate();

	
}

void CAppsDlg::InitBtStatus(UINT nButtonID) {
	switch(nButtonID) 
	{
	case CYYYEDlg::IDD:
		m_rBtnYYYE.LoadBitmaps(IDB_BITMAP_YYYE1);
		break;
	case CRGZCDlg::IDD:
		m_rBtnRGZC.LoadBitmaps(IDB_BITMAP_RGZC1);
		break;
	case CZCInDlg::IDD:
	case CZCOutDlg::IDD:
	case CWDZCDlg::IDD:
		m_rBtnWDZC.LoadBitmaps(IDB_BITMAP_WDZC1);
	}
}

BOOL CAppsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN) 
	{  

		switch(pMsg->wParam) 
		{  

		case VK_RETURN: //回车   
			return TRUE;  

		case VK_ESCAPE: //ESC  
			return TRUE;  

		}  

	}  
	return CDialogBar::PreTranslateMessage(pMsg);
}

void CAppsDlg::OnBnClickedBtnYyye()
{
	
	// TODO: 在此添加控件通知处理程序代码
	
	ActiveDlg(CYYYEDlg::IDD);


}


void CAppsDlg::OnBnClickedBtnFxzc()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CAppsDlg::OnBnClickedBtnRgzc()
{
	// TODO: 在此添加控件通知处理程序代码
	
	ActiveDlg(CRGZCDlg::IDD);
}


void  CAppsDlg::ActiveDlg(UINT nDlgID)
{
	m_pYYYEBar->ShowWindow(SW_HIDE);
	m_pRGZCBar->ShowWindow(SW_HIDE);
	m_pWDZCBar->ShowWindow(SW_HIDE);
	m_pZCInBar->ShowWindow(SW_HIDE);
	m_pZCOutBar->ShowWindow(SW_HIDE);

	switch(nDlgID)
	{
	case CYYYEDlg::IDD:
		{
			MobileTip(CYYYEDlg::IDD, TRUE);
			m_pYYYEBar->ShowWindow(SW_SHOW);
			break;
		}
	case CRGZCDlg::IDD:
		{
			MobileTip(CRGZCDlg::IDD, TRUE);
			m_pRGZCBar->ShowWindow(SW_SHOW);
			break;
		}
	case CWDZCDlg::IDD:
		{
			MobileTip(CWDZCDlg::IDD, TRUE);
			m_pWDZCBar->ShowWindow(SW_SHOW);
			break;
		}
	case CZCInDlg::IDD:
		{
			MobileTip(CZCInDlg::IDD, TRUE);
			m_pZCInBar->ShowWindow(SW_SHOW);
			break;
		}
	case CZCOutDlg::IDD:
		{
			MobileTip(CZCOutDlg::IDD, TRUE);
			m_pZCOutBar->ShowWindow(SW_SHOW);
			break;
		}

		/*default:
		{
		MobileTip(CWDZCDlg::IDD, TRUE);
		}*/
	
	}
}

void CAppsDlg::OnBnClickedBtnWdzc()
{
	// TODO: 在此添加控件通知处理程序代码
	ActiveDlg(CWDZCDlg::IDD);
}
