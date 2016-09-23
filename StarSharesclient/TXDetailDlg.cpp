// TXDetailDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "TXDetailDlg.h"
#include "afxdialogex.h"
#include "StarSharesclientDlg.h"
#include "CApplication.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "ShowSingleTxDlg.h"


// CTXDetailDlg

IMPLEMENT_DYNAMIC(CTXDetailDlg, CDialogBar)

CTXDetailDlg::CTXDetailDlg()
{
	m_pBmp = NULL ;
	m_seteditcolor = TRUE;
	
}

CTXDetailDlg::~CTXDetailDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}


void CTXDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TXDETAIL, m_listCtrl);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_condition);
	DDX_Control(pDX, IDC_COMBO_TIME, m_time);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_editAddr);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_rBtnSearch);
}

BEGIN_MESSAGE_MAP(CTXDetailDlg, CDialogBar)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_TIME, &CTXDetailDlg::OnCbnSelchangeComboTime)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CTXDetailDlg::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TXDETAIL, &CTXDetailDlg::OnNMDblclkList)
	ON_MESSAGE(MSG_USER_TRANSRECORD_UI , &CTXDetailDlg::OnShowListCtrl )
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTXDetailDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()



// CTXDetailDlg ��Ϣ�������

void CTXDetailDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CTXDetailDlg::OnEraseBkgnd(CDC* pDC)
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

	m_listCtrl.ShowScrollBar(SB_HORZ, FALSE);

	return 1;
}


int CTXDetailDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//SetBkBmpNid( IDB_BITMAP_SHADE_BLACK ) ;
	return 0;
}


void CTXDetailDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if( NULL != GetSafeHwnd() ) {
		CRect rect ; 
		this->GetWindowRect(rect);

		CWnd *pst = NULL;

		pst = GetDlgItem( IDC_LIST_TXDETAIL ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,30 , 100 , 840, 330,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_COMBO_TIME ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,30 , 42 , 128, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_COMBO_TYPE ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,20+128+20 , 42 , 128, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_EDIT_SEARCH ) ;
		if ( NULL != pst ) {
			pst->GetWindowRect( rect ) ;
			pst->SetWindowPos( NULL ,15+15+20+128+128+20 , 36 , 310, 40  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_BUTTON_SEARCH);
		if(NULL != pst)
		{
			CRect btnRect;
			pst->GetWindowRect(&btnRect);
			pst->SetWindowPos(NULL, 15+15+20+128+128+320+20, 36, btnRect.Width(), btnRect.Height(), SWP_SHOWWINDOW);
		}
	}

}

void  CTXDetailDlg::OninitializeList()
{
	ShowComboxCotent();
}

void    CTXDetailDlg::ShowComboxCotent()
{
	int operate = 0;
	string condtion = GetConditonStr(operate);
	uistruct::TRANSRECORDLIST pListInfo;

	string strCond0 =  condtion;

	string tempConditon = "confirm_height=0 and ";
	tempConditon +=strCond0;
	strCond0 = tempConditon;

	theApp.m_SqliteDeal.GetTransactionList(strCond0, &pListInfo); 

	uistruct::TRANSRECORDLIST pListInfo1;
	string strCond = " confirm_height!=0 and "+ condtion;// + _T(" LIMIT 17 OFFSET 0") ;

	theApp.m_SqliteDeal.GetTransactionList(strCond, &pListInfo1); 
	
	pListInfo.insert(pListInfo.end(),pListInfo1.begin(),pListInfo1.end());
	Invalidate();

	OnShowListCtrl(pListInfo);
}


//��
void CTXDetailDlg::OnShowListCtrl(uistruct::TRANSRECORDLIST pListInfo){

	m_listCtrl.DeleteAllItems();
	if (pListInfo.size() == 0)
	{
		return;
	}

	m_pListInfo.clear();
	m_pListInfo.insert(m_pListInfo.begin(),pListInfo.begin(),pListInfo.end());

	int nSubIdx = 0 , i = 0 ;
	string strShowData = "";
	//TRACE("333333333333333333333\n");
	std::vector<uistruct::REVTRANSACTION_t>::const_iterator const_it;
	for ( const_it = pListInfo.begin() ; const_it != pListInfo.end() ; const_it++ ) {

		nSubIdx = 0;
		strShowData = strprintf("%d", i);
		m_listCtrl.InsertItem(i, strShowData.c_str());					//���

		string txtype = const_it->txtype;
		if (!strcmp(txtype.c_str(),"REWARD_TX"))
		{
			strShowData = _T("�ڿ�");
		}else if (!strcmp(txtype.c_str(),"REG_ACCT_TX"))
		{
			strShowData= _T("����") ;
		}else if (!strcmp(txtype.c_str(),"COMMON_TX"))
		{
			if (const_it->state == 3)
			{
				strShowData= _T("ת��<ƽ>");
			}else if (const_it->state == 2)
			{
				strShowData= _T("ת��<��>");
			}else if (const_it->state == 1)
			{
				strShowData= _T("ת��<��>") ;
			}else
			{
				strShowData= _T("ת��") ;
			}
		}else if (!strcmp(txtype.c_str(),"CONTRACT_TX"))
		{
			strShowData= _T("��Լ");
		}else if (!strcmp(txtype.c_str(),"REG_APP_TX"))
		{
			strShowData= _T("ע��") ;
		}
		m_listCtrl.SetItemText( i , ++nSubIdx, strShowData.c_str());   //��������


		m_listCtrl.SetItemText(i , ++nSubIdx , const_it->addr.c_str() );   //Դ��ַ

		strShowData= strprintf("%.2f" , const_it->money ) ;
		m_listCtrl.SetItemText(i , ++nSubIdx , strShowData.c_str() );   //���׽��

		m_listCtrl.SetItemText(i , ++nSubIdx , const_it->desaddr.c_str() );   //Ŀ�ĵ�ַ


		string txhash= const_it->txhash.substr(0,25)+"...";
		strShowData = strprintf("%s", txhash.c_str()); 
		m_listCtrl.SetItemText(i , ++nSubIdx , strShowData.c_str() );  //����hash


		i++;
	}
}

//��
string CTXDetailDlg::GetConditonStr(int &operate)
{
	string condtion ="";
	string temp ="";

	temp = GetConditonTxType(operate);
	if (temp !="")
	{
		condtion = GetConditonTxType(operate);
	}

	if (condtion !="")
	{
		temp = GetConditonTime();
		if (temp !=_T(""))
		{
			condtion+=strprintf( " and %s",temp.c_str());
		}


	}else{
		temp = GetConditonTime();
		if (temp != _T(""))
		{
			condtion += strprintf( " %s",temp.c_str());
		}
	}

	if (condtion !=_T(""))
	{
		temp = Getaddr();
		if (temp != _T(""))
		{
			if (operate == 1)   ///  ����Ǯ�ĵ�ַ
			{
				condtion+=strprintf( " and des_addr = '%s'",temp.c_str());
			}else if (operate == 2)
			{
				condtion+=strprintf( " and src_addr = '%s'",temp.c_str());
			}else{
				condtion+=strprintf( " and (src_addr = '%s' or des_addr = '%s')",temp.c_str(),temp.c_str());
			}

		}

	}else{
		temp = Getaddr();
		if (temp != "")
		{
			if (operate == 1)
			{
				condtion+=strprintf( "des_addr = '%s'",temp.c_str());
			}else if (operate == 2)
			{
				condtion+=strprintf( "src_addr = '%s'",temp.c_str());
			}else{
				condtion+=strprintf( " src_addr = '%s' or des_addr = '%s'",temp.c_str(),temp.c_str());
			}
		}

	}
	if (condtion =="")
	{
		condtion ="1=1";
	}
	condtion+=" order by confirmed_time DESC";
	return condtion;
}

//��
string CTXDetailDlg::GetConditonTime(){
	SYSTEMTIME curTime ;
	memset( &curTime , 0 , sizeof(SYSTEMTIME) ) ;
	GetLocalTime( &curTime ) ;
	string strSendTime;
	strSendTime = strprintf("%04d-%02d-%02d %02d:%02d:%02d",curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);
	INT64 maxcurtime = UiFun::SystemTimeToTimet(curTime);

	CString text;
	int sel = m_time.GetCurSel();
	if (sel < 0)
	{
		return _T("");
	}
	m_time.GetLBText(sel,text);
	uistruct::TRANSRECORDLIST pListInfo;

	string conditon;

	if (strcmp(text,  _T("ȫ��") ) == 0)
	{
		return _T("");
	}else if (strcmp(text, _T("����") ) == 0)
	{
		curTime.wHour = 0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon = strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon += strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text, _T("����") ) == 0)
	{
		curTime.wHour = 0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = 0;
		if (curTime.wDayOfWeek == 0)
		{
			mincurtime = UiFun::SystemTimeToTimet(curTime);
		}else{
			INT64 differ = 86400*curTime.wDayOfWeek;
			mincurtime = UiFun::SystemTimeToTimet(curTime);
			mincurtime = maxcurtime -mincurtime;
			mincurtime = maxcurtime - (differ+mincurtime);
		}

		conditon =strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("����")) == 0)
	{
		curTime.wDay =1;
		curTime.wHour = 0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon = strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("����")) == 0)
	{
		INT64 maxcurtime = 0;
		INT64 mincurtime = 0;
		curTime.wDay =1;
		curTime.wHour=0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		maxcurtime = UiFun::SystemTimeToTimet(curTime);
		if (curTime.wMonth == 1)
		{
			curTime.wMonth = 12;
			curTime.wYear -=1;

		}else{
			curTime.wMonth -= 1;
		}
		mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon= strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("����")) == 0)
	{
		curTime.wMonth =1;
		curTime.wDay=1;
		curTime.wHour=0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon =strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon+=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("����")) == 0)
	{
		curTime.wHour=0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 maxcurtime = UiFun::SystemTimeToTimet(curTime);
		INT64 mincurtime = maxcurtime - 24*60*60;

		conditon=strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}
	return _T("");
}
//��
string CTXDetailDlg::GetConditonTxType(int &operate){
	CString text;
	int sel = m_condition.GetCurSel();
	if (sel < 0)
	{
		return _T("");
	}
	m_condition.GetLBText(sel,text);
	uistruct::TRANSRECORDLIST pListInfo;

	string conditon;

	if (strcmp(text,_T("ȫ��")) == 0)
	{
		return _T("");
	}else if (strcmp(text,"����") == 0)
	{
		operate = 1;

		conditon=" tx_type='COMMON_TX' and (state =2 or state =3)";
		return conditon;
	}else if (strcmp(text,_T("����")) == 0)
	{
		operate = 2;
		conditon=" tx_type='COMMON_TX' and (state =1 or state =3)";
		return conditon;
	}else if (strcmp(text,_T("�ڿ�����")) == 0)
	{
		conditon=" tx_type='REWARD_TX'";
		return conditon;
	}else if (strcmp(text,_T("��Լ")) == 0)
	{
		conditon=" tx_type='CONTRACT_TX'";
		return conditon;
	}else if (strcmp(text,_T("����")) == 0)
	{
		conditon=" tx_type='REG_ACCT_TX'";
		return conditon;
	}
	return "";
}

//��
string CTXDetailDlg::Getaddr(){

	CString ret = _T("");
	GetDlgItem(IDC_EDIT_SEARCH)->GetWindowText(ret);
	if (strcmp(ret,_T("�������ַ��������")) == 0)
	{
		ret = "";
	}
	string stret =strprintf("%s",ret);
	return stret;
}

BOOL CTXDetailDlg::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL bRes = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if ( bRes ) {
		UpdateData(FALSE);
		struct LISTCol {
			CString		name ;
			UINT		size ;
		} listcol[5]  = {
			{"���" ,      50},
			{"��������" ,      122},
			{"Դ�˺�" ,      265},
			{"���" ,      120}, 
			{"Ŀ���˺�" ,       265}
		};
		m_listCtrl.SetBkColor(RGB(255,255,255));       
		m_listCtrl.SetRowHeigt(30);               
		m_listCtrl.SetHeaderHeight(1.5);         
		m_listCtrl.SetHeaderFontHW(15,0);
		m_listCtrl.SetHeaderBKColor(/*224,65,18,*/ 87, 101, 112, 0); 
		m_listCtrl.SetHeaderTextColor(RGB(255,255,255)); 
		m_listCtrl.SetTextColor(RGB(0,0,0));  
		for( int i = 0 ; i <5 ; i++  ) {
			m_listCtrl.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
		}
		m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP );// |LVS_SINGLESEL  );

		m_rBtnSearch.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 0) , IDB_BITMAP_BUT1 , RGB(255, 255, 255) );
		m_rBtnSearch.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnSearch.SetWindowText("����") ;
		m_rBtnSearch.SetFontEx(-12 , _T("΢���ź�"));
		m_rBtnSearch.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
		m_rBtnSearch.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
		m_rBtnSearch.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255,255));
		m_rBtnSearch.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
		m_rBtnSearch.SizeToContent();

		m_condition.InsertString(0,_T("ȫ��"));
		m_condition.InsertString(1,_T("����"));
		m_condition.InsertString(2,_T("����"));
		m_condition.InsertString(3,_T("�ڿ�����"));
		m_condition.InsertString(4,_T("��Լ"));
		m_condition.InsertString(5,_T("����"));

		m_time.InsertString(0,_T("ȫ��"));
		m_time.InsertString(1,_T("����"));
		m_time.InsertString(2,_T("����"));
		m_time.InsertString(3,_T("����"));
		m_time.InsertString(4,_T("����"));
		m_time.InsertString(5,_T("����"));
		m_time.InsertString(6,_T("����"));

		CRect rect;
		m_time.GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_time.SetEdtNewFont(120);
		m_time.SetListNewFont(120);
		m_time.SetEdtTextColor(RGB(121, 122, 122));
		m_time.SetListTextColor(RGB(118, 192, 50));
		m_time.AotuAdjustDroppedWidth();
		m_time.SetEdtFrameColor(RGB(238,238,238));
		m_time.SetFrameStyle(CYComBox::ONLYONE);

		m_condition.GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_condition.SetEdtNewFont(120);
		m_condition.SetListNewFont(120);
		m_condition.SetEdtTextColor(RGB(121, 122, 122));
		m_condition.SetListTextColor(RGB(118, 192, 50));
	
		m_condition.AotuAdjustDroppedWidth();
		m_condition.SetEdtFrameColor(RGB(238,238,238));
		m_condition.SetFrameStyle(CYComBox::ONLYONE);

		m_condition.SetCurSel(0);
		m_time.SetCurSel(0);

		m_colorEditText = RGB(159,161,164);

		m_editAddr.SetWindowText(_T("�������ַ��������"));
		m_editAddr.SetNewFont(100);
		
		OninitializeList();

		theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_TRANSRECORD_UI ) ;
	}
	return bRes ;
}


void CTXDetailDlg::OnCbnSelchangeComboTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowComboxCotent();
}


void CTXDetailDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	ShowComboxCotent();
}

//��
void CTXDetailDlg::ShowAddrConditon()
{
	int operate;
	string condtion = GetConditonStr(operate);

	uistruct::TRANSRECORDLIST pListInfo;
	theApp.m_SqliteDeal.GetTransactionList(condtion, &pListInfo); 
	OnShowListCtrl(pListInfo);
}

BOOL CTXDetailDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)  
	{   
		if (GetDlgItem(IDC_EDIT_SEARCH) == this->GetFocus())
		{
			ShowAddrConditon();
			return TRUE;
		}
	}  
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SEARCH);
	ASSERT(pEdit && pEdit->GetSafeHwnd());
	if(WM_LBUTTONDOWN == pMsg->message && pEdit->GetSafeHwnd() == pMsg->hwnd)
	{
		CString strTemp = _T("");
		m_editAddr.GetWindowText(strTemp);
		if (strcmp(strTemp, _T("�������ַ��������")) == 0)
		{
			GetDlgItem(IDC_EDIT_SEARCH)->SetWindowText("");
			pEdit->SetFocus();
			pEdit->SetSel(1,1,FALSE);
			return TRUE;
		}

	}
	if (pMsg->message == WM_KEYDOWN &&pEdit->GetSafeHwnd() == pMsg->hwnd &&(pMsg->wParam != VK_RETURN))
	{
		CString strTemp = _T("");
		m_editAddr.GetWindowText(strTemp);
		if (((pMsg->wParam >=48 && pMsg->wParam <=57) 
			|| (pMsg->wParam >=65 && pMsg->wParam <=90)
			|| (pMsg->wParam >=0x60 && pMsg->wParam <=0x69)) && strcmp(strTemp,_T("�������ַ��������")) == 0)
		{
			m_editAddr.SetWindowText(_T(""));
			m_seteditcolor = FALSE;
		}
	}

	if ( pMsg->message == WM_KEYDOWN &&pEdit->GetSafeHwnd() == pMsg->hwnd &&(pMsg->wParam == VK_BACK) )
	{
		CString strTemp = _T("");
		m_editAddr.GetWindowText(strTemp);
		if (strTemp.GetLength() ==  1)
		{
			m_editAddr.SetWindowText(_T("�������ַ��������"));
			m_seteditcolor = TRUE;
		}
	}

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


void CTXDetailDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(-1 != pNMItemActivate->iItem) 
	{  
		int nRow = pNMItemActivate->iItem;

		if (nRow <0 || nRow > (int)m_pListInfo.size())
		{
			return ;
		}
		uistruct::REVTRANSACTION_t  txdetail =m_pListInfo.at(nRow);

		if (txdetail.txhash != _T(""))
		{
			theApp.m_strAddress.Format(_T("%s") ,txdetail.ToJson().c_str() ) ;
		}else
		{		
			theApp.m_strAddress =_T("");
		}

		CShowSingleTxDlg dlg;
		dlg.DoModal();
	}  
	*pResult = 0;
}


HBRUSH CTXDetailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (CTLCOLOR_EDIT == nCtlColor && m_seteditcolor && pWnd->GetDlgCtrlID() == IDC_EDIT_SEARCH)
	{
		pDC->SetTextColor(m_colorEditText);
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{

		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));

	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

LRESULT CTXDetailDlg::OnShowListCtrl(  WPARAM wParam, LPARAM lParam )
{
	int type = (int)wParam;
	switch(type)
	{
	case WM_INSERT:
		{
			//InsertItemData();
			m_listCtrl.DeleteAllItems();
			OninitializeList();
			
		}
		break;
	case WM_REMOVETX:
		{
			m_listCtrl.DeleteAllItems();
			OninitializeList();
			
		}
		break;
	default:
		break;
	}
	return 0;
}

//��
void CTXDetailDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowAddrConditon();
}

