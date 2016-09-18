// ToolBarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "ToolBarDlg.h"
#include "afxdialogex.h"


// CToolBarDlg

IMPLEMENT_DYNAMIC(CToolBarDlg, CDialogBar)

CToolBarDlg::CToolBarDlg()
{
	m_pBmp = NULL ;
	m_nButtonID = CMainDlg::IDD ;
}

CToolBarDlg::~CToolBarDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}


BEGIN_MESSAGE_MAP(CToolBarDlg, CDialogBar)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(MSG_USER_MOBILE_TIP, &CToolBarDlg::OnShowStateTip )
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CToolBarDlg ��Ϣ�������


void CToolBarDlg::DoDataExchange(CDataExchange* pDX)
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogBar::DoDataExchange(pDX);

	
	DDX_Control(pDX, IDC_BTN_MAIN	, m_rBtnMain );
	DDX_Control(pDX, IDC_BTN_PAY, m_rBtnSend);
	DDX_Control(pDX, IDC_BTN_RECV	, m_rBtnRece );
	DDX_Control(pDX, IDC_BTN_TXDETAIL	, m_rBtnDeal );
	DDX_Control(pDX, IDC_BTN_APP	    , m_rBtnApp );
	DDX_Control(pDX, IDC_BTN_SET	    , m_rBtnSet );
	DDX_Control(pDX, IDC_BTN_CLOSE	, m_rBtnClose );
	DDX_Control(pDX, IDC_BTN_MIN	    , m_rBtnMin );
}

void CToolBarDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CToolBarDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


int CToolBarDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetBkBmpNid( IDB_BITMAP_TITLE_BAR ) ;

	
	return 0;
}


void CToolBarDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if( NULL != GetSafeHwnd() ) {
		CRect rect ; 
		this->GetWindowRect(rect);
		//CStatic *p_Logo = (CStatic*)GetDlgItem(IDC_STATIC_LOGO);
		//if ( NULL != p_Logo ) {
		//	p_Logo->SetWindowPos( NULL ,0 , 0 , 80, 30  ,SWP_SHOWWINDOW ) ; 
		//}

		//CStatic *p_LogoFont = (CStatic*)GetDlgItem(IDC_STATIC_FONT);
		//if ( NULL != p_Logo ) {
		//	p_Logo->SetWindowPos( NULL ,0 , 0 , 126, 30  ,SWP_SHOWWINDOW ) ; 
		//}
		//CButton *p_ButtonLogo = (CButton*)GetDlgItem(IDC_BUTTON_LOGO);
		//if( NULL != p_ButtonLogo ) {
		//	p_ButtonLogo->SetWindowPos( NULL ,0 , 0 , 130, 71  ,SWP_SHOWWINDOW ) ; 
		//}
		//
		//CButton *p_ButtonFont = (CButton*)GetDlgItem(IDC_BUTTON_FONT);
		//if( NULL != p_ButtonFont ) {
		//	p_ButtonFont->SetWindowPos( NULL ,130 , -1 , 80, 72  ,SWP_SHOWWINDOW ) ; 
		//}


		CButton *p_Button = (CButton*)GetDlgItem(IDC_BTN_MAIN);
		if( NULL != p_Button ) {
			p_Button->SetWindowPos( NULL ,234 , -1, 96,  100 ,SWP_SHOWWINDOW ) ; 
		}
		p_Button = (CButton*)GetDlgItem(IDC_BTN_PAY);
		if( NULL != p_Button ) {
			p_Button->SetWindowPos( NULL ,330 , -1 , 96, 100  ,SWP_SHOWWINDOW ) ; 
		}
		p_Button = (CButton*)GetDlgItem(IDC_BTN_RECV);
		if( NULL != p_Button ) {
			p_Button->SetWindowPos( NULL ,426 , -1 , 96, 100  ,SWP_SHOWWINDOW ) ; 
		}
		p_Button = (CButton*)GetDlgItem(IDC_BTN_TXDETAIL);
		if( NULL != p_Button ) {
			p_Button->SetWindowPos( NULL ,522 , -1 , 96, 100  ,SWP_SHOWWINDOW ) ; 
		}
		p_Button = (CButton*)GetDlgItem(IDC_BTN_APP);
		if( NULL != p_Button ) {
			p_Button->SetWindowPos( NULL ,618 , -1 , 96, 100  ,SWP_SHOWWINDOW ) ; 
		}
		p_Button = (CButton*)GetDlgItem(IDC_BTN_SET);
		if( NULL != p_Button ) {
			p_Button->SetWindowPos( NULL ,714 , -1 , 96, 100  ,SWP_SHOWWINDOW ) ; 
		}

		CButton *p_Close = (CButton*)GetDlgItem(IDC_BTN_CLOSE);
		if( NULL != p_Close ) {	
			p_Close->SetWindowPos(NULL ,900 - 27 - 7 + 5, 14 ,12 , 11 , SWP_SHOWWINDOW);
		}
		CButton * p_Min = (CButton*)GetDlgItem(IDC_BTN_MIN);
		if( NULL != p_Min ) {	
			p_Min->SetWindowPos(NULL ,900 - 54 - 7 - 5 + 5, 14 , 12 , 11 , SWP_SHOWWINDOW);
		}
	}
}


BOOL CToolBarDlg::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL bRes =  CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if ( bRes ) {
		
		m_rBtnMain.LoadBitmaps(IDB_BITMAP_LOGO_MAIN1 ,IDB_BITMAP_LOGO_MAIN2 , IDB_BITMAP_LOGO_MAIN2 , IDB_BITMAP_LOGO_MAIN1 );
		m_rBtnSend.LoadBitmaps(IDB_BITMAP_LOGO_PM1 ,IDB_BITMAP_LOGO_PM2 , IDB_BITMAP_LOGO_PM2 , IDB_BITMAP_LOGO_PM1 );
		m_rBtnRece.LoadBitmaps(IDB_BITMAP_LOGO_RECV1,  IDB_BITMAP_LOGO_RECV2, IDB_BITMAP_LOGO_RECV2, IDB_BITMAP_LOGO_RECV1);
		m_rBtnDeal.LoadBitmaps(IDB_BITMAP_LOGO_TXDETAIL1 ,IDB_BITMAP_LOGO_TXDETAIL2 , IDB_BITMAP_LOGO_TXDETAIL2 , IDB_BITMAP_LOGO_TXDETAIL1);
		m_rBtnApp.LoadBitmaps(IDB_BITMAP_LOGO_YUE1 ,IDB_BITMAP_LOGO_YUE2 , IDB_BITMAP_LOGO_YUE2 , IDB_BITMAP_LOGO_YUE1  );
		m_rBtnSet.LoadBitmaps(IDB_BITMAP_LOGO_SET1 ,IDB_BITMAP_LOGO_SET2 , IDB_BITMAP_LOGO_SET2 , IDB_BITMAP_LOGO_SET1);
		m_rBtnClose.LoadBitmaps(IDB_BITMAP_TOOL_CLOSE1, IDB_BITMAP_TOOL_CLOSE2, IDB_BITMAP_TOOL_CLOSE2, IDB_BITMAP_TOOL_CLOSE1);
		m_rBtnMin.LoadBitmaps(IDB_BITMAP_TOOL_HIDE1, IDB_BITMAP_TOOL_HIDE2, IDB_BITMAP_TOOL_HIDE2, IDB_BITMAP_TOOL_HIDE1);

		//m_rBtnClose.LoadBitmaps(IDB_BITMAP_CLOSE1 , IDB_BITMAP_CLOSE2 ,IDB_BITMAP_CLOSE3,IDB_BITMAP_CLOSE1);
		//m_rBtnMin.LoadBitmaps(IDB_BITMAP_MIN1 , IDB_BITMAP_MIN2  ,IDB_BITMAP_MIN3,IDB_BITMAP_MIN1);
		UpdateData(FALSE);

		//m_rBtnClose.SetIcon(IDI_ICON_CLOSE3, 0, 0, IDI_ICON_CLOSE1, 0, 0);
		
		//m_rBtnClose.DrawBorder(FALSE); 
		//m_rBtnClose.DrawTransparent(TRUE);

		/*m_rBtnMin.SetIcon(IDI_ICON_MIN3, 0, 0, IDI_ICON_MIN1, 0, 0);
		m_rBtnMin.DrawBorder(FALSE); 
		m_rBtnMin.DrawTransparent(TRUE);*/
		

		theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_MOBILE_TIP ) ; 
		MobileTip(CMainDlg::IDD , TRUE );
	}
	return bRes ;
}
LRESULT CToolBarDlg::OnShowStateTip( WPARAM wParam, LPARAM lParam )
{
	MobileTip( (UINT)wParam , (BOOL)lParam );
	return 1;
}

void CToolBarDlg::MobileTip(UINT nButtonID , BOOL bFlag )
{
	if ( bFlag ) { 

		m_rBtnMain.LoadBitmaps(IDB_BITMAP_LOGO_MAIN2 ,IDB_BITMAP_LOGO_MAIN2 , IDB_BITMAP_LOGO_MAIN2 , IDB_BITMAP_LOGO_MAIN1 );

		//HCURSOR cur = ::LoadCursor(NULL, IDC_HAND);
		//m_rBtnMain.LoadBitmaps(IDB_BITMAP_LOGO_MAIN1,IDB_BITMAP_LOGO_MAIN2);
		//m_rBtnMain.SetIcon(IDI_MAIN_LOGO_ICON2, 0, 0, IDI_MAIN_LOGO_ICON1, 0, 0);
		//m_rBtnMain.SetBitmaps(IDB_BITMAP_LOGO_MAIN1, 0, IDB_BITMAP_LOGO_MAIN2, 0);
		//m_rBtnMain.DrawBorder(FALSE); 
		//m_rBtnMain.DrawTransparent(TRUE);
		//m_rBtnMain.SetBtnCursor(IDC_CURSOR1);
		//m_rBtnMain.SetCursor(cur);
		
		/*m_rBtnSend.SetIcon(IDI_SEND_LOGO_ICON2, 0, 0, IDI_SEND_LOGO_ICON1, 0, 0);
		m_rBtnSend.DrawBorder(FALSE); 
		m_rBtnSend.DrawTransparent(TRUE);*/
		//m_rBtnSend.SetBtnCursor(IDC_CURSOR1);
		//m_rBtnSend.LoadBitmaps(IDB_BITMAP_LOGO_SEND2 ,IDB_BITMAP_LOGO_SEND1 , IDB_BITMAP_LOGO_SEND1 , IDB_BITMAP_LOGO_SEND2 );
		//m_rBtnSend.SetCursor(cur);
		
		/*m_rBtnRece.SetIcon(IDI_RECV_LOGO_ICON2, 0, 0, IDI_RECV_LOGO_ICON1, 0, 0);
		m_rBtnRece.DrawBorder(FALSE); 
		m_rBtnRece.DrawTransparent(TRUE);*/
		//m_rBtnRece.SetBtnCursor(IDC_CURSOR1);
		//m_rBtnRece.LoadBitmaps(IDB_BITMAP_LOGO_RECV2 ,IDB_BITMAP_LOGO_RECV1 , IDB_BITMAP_LOGO_RECV1 , IDB_BITMAP_LOGO_RECV2 );
		//m_rBtnRece.SetCursor(cur);
		
		/*m_rBtnDeal.SetIcon(IDI_TXDETAIL_ICON2, 0, 0, IDI_TXDETAIL_ICON1, 0, 0);
		m_rBtnDeal.DrawBorder(FALSE); 
		m_rBtnDeal.DrawTransparent(TRUE);*/
		//m_rBtnDeal.SetBtnCursor(IDC_CURSOR1);
		//m_rBtnDeal.LoadBitmaps(IDB_BITMAP_LOGO_TXDETAIL2, IDB_BITMAP_LOGO_TXDETAIL1, IDB_BITMAP_LOGO_TXDETAIL1, IDB_BITMAP_LOGO_TXDETAIL2);
		//m_rBtnDeal.SetCursor(cur);
		
		/*m_rBtnApp.SetIcon(IDI_YUE_ICON2, 0, 0, IDI_YUE_ICON1, 0, 0);
		m_rBtnApp.DrawBorder(FALSE); 
		m_rBtnApp.DrawTransparent(TRUE);*/
		//m_rBtnApp.SetBtnCursor(IDC_CURSOR1);
		//m_rBtnApp.LoadBitmaps(IDB_BITMAP_LOGO_YUE2, IDB_BITMAP_LOGO_YUE1, IDB_BITMAP_LOGO_YUE1,IDB_BITMAP_LOGO_YUE2);
		//m_rBtnApp.SetCursor(cur);
		
		/*m_rBtnSet.SetIcon(IDI_SET_ICON2, 0, 0, IDI_SET_ICON1, 0, 0);
		m_rBtnSet.DrawBorder(FALSE); 
		m_rBtnSet.DrawTransparent(TRUE);*/
		//m_rBtnSet.SetBtnCursor(IDC_CURSOR1);
		//m_rBtnSet.LoadBitmaps(IDB_BITMAP_LOGO_SET2, IDB_BITMAP_LOGO_SET1, IDB_BITMAP_LOGO_SET1,IDB_BITMAP_LOGO_SET2);
		//m_rBtnSet.SetCursor(cur);

//		m_rBtnMain.LoadBitmaps(IDB_BITMAP_MAIN3 ,IDB_BITMAP_MAIN2 , IDB_BITMAP_MAIN3 , IDB_BITMAP_MAIN1 );
	}
	if ( m_nButtonID == nButtonID  && !bFlag ) {
		return ;
	}
	//m_rBtnMain.SetIcon(IDI_MAIN_LOGO_ICON2);
	InitBtStatus(m_nButtonID);
	switch(nButtonID)
	{
	case CMainDlg::IDD:
		//m_rBtnMain.SetIcon(IDI_MAIN_LOGO_ICON2);
		//m_rBtnMain.SetBitmap(LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP_LOGO_MAIN2)));
		m_rBtnMain.LoadBitmaps(IDB_BITMAP_LOGO_MAIN2 ,IDB_BITMAP_LOGO_MAIN2 , IDB_BITMAP_LOGO_MAIN2 , IDB_BITMAP_LOGO_MAIN1 );
		 break;
	case CPayDlg::IDD:
		m_rBtnSend.LoadBitmaps(IDB_BITMAP_LOGO_PM2 ,IDB_BITMAP_LOGO_PM2 , IDB_BITMAP_LOGO_PM2 , IDB_BITMAP_LOGO_PM1 );
		break;
	case CRecvDlg::IDD:
		m_rBtnRece.LoadBitmaps(IDB_BITMAP_LOGO_RECV2 ,IDB_BITMAP_LOGO_RECV2 , IDB_BITMAP_LOGO_RECV2 , IDB_BITMAP_LOGO_RECV1);

		break;
	case CTXDetailDlg::IDD:
		m_rBtnDeal.LoadBitmaps(IDB_BITMAP_LOGO_TXDETAIL2 ,IDB_BITMAP_LOGO_TXDETAIL2 , IDB_BITMAP_LOGO_TXDETAIL2 , IDB_BITMAP_LOGO_TXDETAIL1  );
		break;
	case CAppsDlg::IDD:
		m_rBtnApp.LoadBitmaps(IDB_BITMAP_LOGO_YUE2 ,IDB_BITMAP_LOGO_YUE2 , IDB_BITMAP_LOGO_YUE2 , IDB_BITMAP_LOGO_YUE1 );
		break;
	case CSetDlg::IDD:	
		m_rBtnSet.LoadBitmaps(IDB_BITMAP_LOGO_SET2 ,IDB_BITMAP_LOGO_SET2 , IDB_BITMAP_LOGO_SET2 , IDB_BITMAP_LOGO_SET1 );
		break;
	}
	m_nButtonID = nButtonID ;

	this->Invalidate();
}

void CToolBarDlg::InitBtStatus(UINT nButtonID) {
	switch(nButtonID) 
	{
		case CMainDlg::IDD:
			//m_rBtnMain.SetIcon(IDI_MAIN_LOGO_ICON2, IDI_MAIN_LOGO_ICON1);
			//m_rBtnMain.SetBitmaps(IDB_BITMAP_LOGO_MAIN1, 0, IDB_BITMAP_LOGO_MAIN2, 0);
			m_rBtnMain.LoadBitmaps(IDB_BITMAP_LOGO_MAIN1, IDB_BITMAP_LOGO_MAIN2,IDB_BITMAP_LOGO_MAIN2, IDB_BITMAP_LOGO_MAIN1 );
			break;
		case CPayDlg::IDD:
			//m_rBtnSend.SetIcon(IDI_SEND_LOGO_ICON2, IDI_SEND_LOGO_ICON1);
			m_rBtnSend.LoadBitmaps(IDB_BITMAP_LOGO_PM1, IDB_BITMAP_LOGO_PM2, IDB_BITMAP_LOGO_PM2, IDB_BITMAP_LOGO_PM1);
			break;
		case CRecvDlg::IDD:
			m_rBtnRece.LoadBitmaps(IDB_BITMAP_LOGO_RECV1 ,IDB_BITMAP_LOGO_RECV2 , IDB_BITMAP_LOGO_RECV2 , IDB_BITMAP_LOGO_RECV1);
			break;
		case CTXDetailDlg::IDD:
			m_rBtnDeal.LoadBitmaps(IDB_BITMAP_LOGO_TXDETAIL1, IDB_BITMAP_LOGO_TXDETAIL2, IDB_BITMAP_LOGO_TXDETAIL2,IDB_BITMAP_LOGO_TXDETAIL1);
			break;
		case CAppsDlg::IDD:
			m_rBtnApp.LoadBitmaps(IDB_BITMAP_LOGO_YUE1, IDB_BITMAP_LOGO_YUE2, IDB_BITMAP_LOGO_YUE2, IDB_BITMAP_LOGO_YUE1);
			break;
		case CSetDlg::IDD:
			m_rBtnSet.LoadBitmaps(IDB_BITMAP_LOGO_SET1, IDB_BITMAP_LOGO_SET2, IDB_BITMAP_LOGO_SET2, IDB_BITMAP_LOGO_SET1);
				
			break;
	}
}


void CToolBarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetParent()->PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));
	CDialogBar::OnLButtonDown(nFlags, point);
}


BOOL CToolBarDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN) 
	{  

		switch(pMsg->wParam) 
		{  

		case VK_RETURN: //�س�   
			return TRUE;  

		case VK_ESCAPE: //ESC  
			return TRUE;  

		}  

	}  
	return CDialogBar::PreTranslateMessage(pMsg);
}
