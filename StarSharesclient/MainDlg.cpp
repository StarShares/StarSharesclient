// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "StarSharesclientDlg.h"
#include "TXDetailDlg.h"
#include "afxinet.h"


// CMainDlg

IMPLEMENT_DYNAMIC(CMainDlg, CDialogBar)

CMainDlg::CMainDlg()
{
	m_pBmp = NULL;
}

CMainDlg::~CMainDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogBar)
	ON_BN_CLICKED(IDC_BTN_TXDETAIL, &CMainDlg::OnBnClickedTxDetail)
	ON_MESSAGE(MSG_USER_MAIN_UI , &CMainDlg::OnShowListCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_MORE_INFO, &CMainDlg::OnBnClickedBtnMoreInfo)
END_MESSAGE_MAP()

// CMainDlg ��Ϣ�������

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogBar::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ST_BALANCE , m_strBalance);
	DDX_Control(pDX, IDC_ST_CONFIRMING , m_strConfirming);
	DDX_Control(pDX, IDC_ST_TRANSACTION_NUMBER , m_strTransactionNumber);

	DDX_Control(pDX, IDC_ST_SRCADDR1 , m_strSrcAddr1);
	DDX_Control(pDX, IDC_ST_DESADDR1 , m_strDesAddr1);
	DDX_Control(pDX, IDC_ST_AMOUNT1 , m_strAmount1);

	DDX_Control(pDX, IDC_ST_SRCADDR2 , m_strSrcAddr2);
	DDX_Control(pDX, IDC_ST_DESADDR2 , m_strDesAddr2);
	DDX_Control(pDX, IDC_ST_AMOUNT2 , m_strAmount2);

	DDX_Control(pDX, IDC_ST_SRCADDR3, m_strSrcAddr3);
	DDX_Control(pDX, IDC_ST_DESADDR3, m_strDesAddr3);
	DDX_Control(pDX, IDC_ST_AMOUNT3, m_strAmount3);

	DDX_Control(pDX, IDC_BTN_TXDETAIL, m_rBtnTxdetail);
	DDX_Control(pDX, IDC_BTN_MORE_INFO, m_rBtnMoreInfo);

	DDX_Control(pDX, IDC_LINK1, m_vlinkCtrl1);
	DDX_Control(pDX, IDC_LINK2, m_vlinkCtrl2);
	DDX_Control(pDX, IDC_LINK3, m_vlinkCtrl3);
	DDX_Control(pDX, IDC_LINK4, m_vlinkCtrl4);
}


void CMainDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

void CMainDlg::ClearCtrlText()
{
	GetDlgItem(IDC_ST_BALANCE)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_TRANSACTION_NUMBER)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR1)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR1)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT1)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR2)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR2)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT2)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR3)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR3)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT3)->SetWindowText(_T(""));
}

void CMainDlg::InitializeLinkCtrl()
{
	m_vlinkCtrl1.SetWindowText(_T(""));
	m_vlinkCtrl1.EnableWindow(FALSE);
	m_vlinkCtrl2.SetWindowText(_T(""));
	m_vlinkCtrl2.EnableWindow(FALSE);
	m_vlinkCtrl3.SetWindowText(_T(""));
	m_vlinkCtrl3.EnableWindow(FALSE);
	m_vlinkCtrl4.SetWindowText(_T(""));
	m_vlinkCtrl4.EnableWindow(FALSE); 	

	HCURSOR cur = ::LoadCursor(NULL, IDC_HAND);

	int i = 1;
	map<CString,CString>::iterator it;
	for(it=m_mapUrl.begin();it!=m_mapUrl.end();++it)
	{
		if(it->first.IsEmpty())
		{
			continue;
		}
		if (i == 1)
		{
			m_vlinkCtrl1.SetWindowText(it->first);
			m_vlinkCtrl1.SetColors(RGB(109, 109, 109), RGB(26, 64, 140));
			m_vlinkCtrl1.SetUnderline(FALSE);
			m_vlinkCtrl1.SetCursor(cur);
			m_vlinkCtrl1.SetURL(it->second);
			m_vlinkCtrl1.EnableWindow(TRUE);
		}
		if (i == 2)
		{
			m_vlinkCtrl2.SetWindowText(it->first);
			m_vlinkCtrl2.SetColors(RGB(109, 109, 109), RGB(26, 64, 140));
			m_vlinkCtrl2.SetUnderline(FALSE);
			m_vlinkCtrl2.SetCursor(cur);
			m_vlinkCtrl2.SetURL(it->second);
			m_vlinkCtrl2.EnableWindow(TRUE);
		}
		if (i == 3)
		{
			m_vlinkCtrl3.SetWindowText(it->first);
			m_vlinkCtrl3.SetColors(RGB(109, 109, 109), RGB(26, 64, 140));
			m_vlinkCtrl3.SetUnderline(FALSE);
			m_vlinkCtrl3.SetCursor(cur);
			m_vlinkCtrl3.SetURL(it->second);
			m_vlinkCtrl3.ShowWindow(SW_HIDE);
			m_vlinkCtrl3.EnableWindow(TRUE);
		}
		if (i == 4)
		{
			m_vlinkCtrl4.SetWindowText(it->first);
			m_vlinkCtrl4.SetColors(RGB(109,109,109), RGB(26, 64, 140));
			m_vlinkCtrl4.SetUnderline(FALSE);
			m_vlinkCtrl4.SetCursor(cur);
			m_vlinkCtrl4.SetURL(it->second);
			m_vlinkCtrl4.ShowWindow(SW_HIDE);
			m_vlinkCtrl4.EnableWindow(TRUE);
			break;
		}
		i++;
	}
}


void CMainDlg::OnBnClickedTxDetail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStarSharesclientDlg* pDlg = (CStarSharesclientDlg*)GetParent();
	if ( NULL != pDlg ) {
		pDlg->ShowDialog(CTXDetailDlg::IDD);
		pDlg->ShowStateTip(CTXDetailDlg::IDD);
	}
}


LRESULT CMainDlg::OnShowListCtrl(WPARAM wParam, LPARAM lParam)
{
	
		//��������
		if (wParam == WM_UPWALLET)
		{
			//����"Ǯ������ͬ��"static
//			GetDlgItem(IDC_STATIC_WALLET)->ShowWindow(SW_HIDE);
		}else{
			SetCtrlText();
		}
		return 0 ;
}

void CMainDlg::SetCtrlText() 
{
	ClearCtrlText();
	CPostMsg postmsg;
	if (!theApp.m_msgUIMainDlgQueue.pop(postmsg))
	{
		LogPrint("INFO","m_UiManDlgQueue Emptry\r\n");
		return ;
	}

	uistruct::MINDLG_T maindlg; 
	string strTemp = postmsg.GetData();
	maindlg.JsonToStruct(strTemp.c_str());


	string strCommand,strShowData;

	string strMoneyBal = "";
	string strMoneyConf = ""; 
	
	strMoneyBal = strprintf("%s",maindlg.money.c_str());//)= _T(maindlg.money.c_str());
	strMoneyBal = CSoyPayHelp::getInstance()->DisPlayMoney(strMoneyBal);
	GetDlgItem(IDC_ST_BALANCE)->SetWindowText(strMoneyBal.c_str());
	//strMoney = _T(maindlg.unconfirmmoney.c_str());
	strMoneyConf = strprintf("%s",maindlg.unconfirmmoney.c_str());
	strMoneyConf = CSoyPayHelp::getInstance()->DisPlayMoney(strMoneyConf);
	GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(strMoneyConf.c_str());

	m_strTransactionNumber.SetWindowText(maindlg.itemcount.c_str()) ;

	string strDes = "";
	string addr1 = maindlg.addr1;
	uistruct::REVTRANSACTION_t temp;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);

		strCommand =strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR1)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR1)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT1)->SetWindowText(strCommand.c_str()) ;
	}

	addr1 = maindlg.addr2;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);

		strCommand = strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR2)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR2)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT2)->SetWindowText(strCommand.c_str()) ;
	}

	addr1 = maindlg.addr3;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);

		strCommand = strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR3)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR3)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT3)->SetWindowText(strCommand.c_str()) ;

	}

	Invalidate();
}


bool CMainDlg::GetUrlServer()
{
	m_mapUrl.clear();
	CString url(_T("http://47.90.49.128/UpData/forumupdata.json"));    
	CInternetSession session;


	std::string strHtml;
	try
	{
		CHttpFile* pfile = (CHttpFile*)session.OpenURL(url,1,INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD,NULL,0);

		DWORD dwStatusCode;    
		pfile->QueryInfoStatusCode(dwStatusCode);    
		if(dwStatusCode == HTTP_STATUS_OK)    
		{    
			char strBuff[1025] = {0};
			while ((pfile->Read((void*)strBuff, 1024)) > 0) 
			{ 
				strHtml += strBuff; 
			} 
		}
		else
		{
			pfile->Close();    
			delete pfile;    
			session.Close();

			return false;
		}

		pfile->Close();    
		delete pfile;    
		session.Close();
	}
	catch (CException* e)
	{
		e;//��������
		return false;
	}

	if (strHtml.empty())
	{
		CStdioFile myFile;
		CString strLine; 
		string strpath = theApp.m_strInsPath;
		strpath +="\\StarSharesUpdate.json";
		if(myFile.Open((LPCTSTR)(LPSTR)strpath.c_str(), CFile::modeRead))
		{
			while(myFile.ReadString(strLine))
			{
				strHtml +=strprintf("%s",strLine);
			}
			//��ȡ
			myFile.Close();
		}else{
			return false;
		}
	}else{
		//����
		CStdioFile  File;
		string strpath = theApp.m_strInsPath;
		strpath +="\\StarSharesUpdate.json";
		File.Open((LPCTSTR)(LPSTR)strpath.c_str(),CFile::modeWrite | CFile::modeCreate);  
		File.WriteString(strHtml.c_str());
		File.Close();
	}


	Json::Reader reader;  
	Json::Value root; 

	if (reader.parse(strHtml, root))
	{
		if (!root.isObject())
		{
			return false;
		}
		Json::Value rootcn = root["Chinese"];
		if (rootcn.isNull()&& !rootcn.isArray())
		{
			return false;
		}
		int index = rootcn.size();
		for (int i = 0;i <index;i++)
		{
			Json::Value  msgroot = rootcn[i];
			Json::Value value = msgroot["msn"];
			if (value.isNull())
			{
				return false;
			}
			CString key = msgroot["msn"].asCString();
			value = msgroot["url"];
			if (value.isNull())
			{
				return false;
			}
			CString valuetemp = msgroot["url"].asCString();
			m_mapUrl[key] = valuetemp;
		}
		return true;
	}
	return false;
}

BOOL CMainDlg::OnEraseBkgnd(CDC* pDC)
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

void CMainDlg::OnInitialCtrlText() 
{
	ClearCtrlText();

	string strCommand,strShowData;
	strCommand  = "0";

	double dmoney =  theApp.m_SqliteDeal.GetTableItemSum(_T("t_wallet_address") ,_T("money"), _T(" 1=1 "));

	string strMoney;
	if (-1 == dmoney)
	{
		m_strBalance.SetWindowText(_T("0.0")) ;
	}else{
		strMoney = strprintf("%.3lf", dmoney);
		strMoney = CSoyPayHelp::getInstance()->DisPlayMoney(strMoney);
		m_strBalance.SetWindowText(strMoney.c_str()) ;
	}

	string strCond;
	strCond=" confirm_height = 0 ";

	dmoney =  theApp.m_SqliteDeal.GetTableItemSum("t_transaction" , _T("money") , strCond) ;


	if (dmoney<0)
	{
		GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(_T("0.0")) ;
	}else{
		string strMoney;
		strMoney = strprintf("%.3lf", dmoney);
		GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(strMoney.c_str()) ;
	}

	int nItem =  theApp.m_SqliteDeal.GetTableCountItem(_T("t_transaction"), _T(" 1=1 ")) ;


	strCommand = strprintf("%d",nItem);
	m_strTransactionNumber.SetWindowText(strCommand.c_str()) ;

	uistruct::TRANSRECORDLIST pTransaction;
	string strSource;
	strCond=" tx_type='COMMON_TX' order by confirmed_time desc limit 6";
	theApp.m_SqliteDeal.GetTransactionList(strCond,&pTransaction);

	int i = 1;
	strCommand=strprintf("IDC_TX%d",nItem);

	int item = IDC_ST_SRCADDR1;
	int item1 = IDC_ST_AMOUNT1;
	int desitem = IDC_ST_DESADDR1;

	string desStr ="";
	if (pTransaction.size() != 0  ) {
		int nSubIdx = 0 , i = 0 ;
		string strShowaddr ;
		std::vector<uistruct::REVTRANSACTION_t>::const_iterator const_it;
		for (const_it = pTransaction.begin() ; const_it != pTransaction.end()&&i<4 ; const_it++ ) {

			strSource = strprintf("%.4f",const_it->money);
			strShowaddr= strprintf("%s",const_it->addr.c_str());
			desStr = strprintf("%s",const_it->desaddr.c_str());
			
			if(item <=IDC_ST_SRCADDR3)
			{
				GetDlgItem(item)->SetWindowText(strShowaddr.c_str()) ;
				GetDlgItem(item + 2)->SetWindowText(strSource.c_str()) ;
				GetDlgItem(item + 1)->SetWindowText(desStr.c_str());
			}
			item += 3;
		}
	}
}


int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetBkBmpNid( IDB_BITMAP_MAIN);		

	m_strBalance.SetFont(20 , _T("΢���ź�"));				//������ʾ����ʹ�С
	m_strConfirming.SetFont(20 , _T("΢���ź�"));	   
	m_strTransactionNumber.SetFont(20 , _T("΢���ź�"));

	/*
	if (m_vlinkCtrl1 == NULL)
	{
		m_vlinkCtrl1 = new CHyperLink;
		m_vlinkCtrl1->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 80, 50), 
			this, 
			IDC_MFCLINK1);
	}

	if (m_vlinkCtrl2 == NULL)
	{
		m_vlinkCtrl2 = new CHyperLink;
		m_vlinkCtrl2->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 80, 50), 
			this, 
			IDC_MFCLINK2);
	}

	if (m_vlinkCtrl3 == NULL)
	{
		m_vlinkCtrl3 = new CHyperLink;
		m_vlinkCtrl3->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 80, 50), 
			this, 
			IDC_MFCLINK3);
	}

	if (m_vlinkCtrl4 == NULL)
	{
		m_vlinkCtrl4 = new CHyperLink;
		m_vlinkCtrl4->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 80, 50), 
			this, 
			IDC_MFCLINK4);
	}
	
	if (m_vlinkCtrlQQ == NULL)
	{
		m_vlinkCtrlQQ = new CMFCLinkCtrl;
		m_vlinkCtrlQQ->Create(_T(""), 
			WS_CHILD, 
			CRect(5, 5, 30, 50), 
			this, 
			IDC_MFCLINK_QQ);
	}

	if (m_vlinkCtrlBlock == NULL)
	{
		m_vlinkCtrlBlock = new CMFCLinkCtrl;
		m_vlinkCtrlBlock->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 30, 50), 
			this, 
			IDC_MFCLINK_BLOCK);
	}
	*/
	return 0;
}


BOOL CMainDlg::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���
	BOOL bRet = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if (bRet) {
		HCURSOR cur = ::LoadCursor(NULL, IDC_HAND);
		m_rBtnTxdetail.LoadBitmaps(IDB_BITMAP_ALLTRADE, IDB_BITMAP_ALLTRADE1, IDB_BITMAP_ALLTRADE1, IDB_BITMAP_ALLTRADE);
		m_rBtnMoreInfo.LoadBitmaps(IDB_BITMAP_MOREINFO, IDB_BITMAP_MOREINFO1, IDB_BITMAP_MOREINFO1, IDB_BITMAP_MOREINFO);
		//m_btnUnit.LoadBitmaps(IDB_BITMAP_UNIT, IDB_BITMAP_UNIT, IDB_BITMAP_UNIT,IDB_BITMAP_UNIT);
		//m_btnCommunity.LoadBitmaps(IDB_BITMAP_COMMUNITY, IDB_BITMAP_COMMUNITY,IDB_BITMAP_COMMUNITY,IDB_BITMAP_COMMUNITY);

		m_rBtnTxdetail.SetCursor(cur);
		m_rBtnMoreInfo.SetCursor(cur);
		m_btnUnit.SetCursor(cur);
		m_btnCommunity.SetCursor(cur);

		UpdateData(FALSE);
		OnInitialCtrlText();
		GetUrlServer();
		InitializeLinkCtrl();

		m_strBalance.SetFont(110 , _T("΢���ź�"));
		m_strConfirming.SetFont(110 , _T("΢���ź�"));
		m_strTransactionNumber.SetFont(110 , _T("΢���ź�"));
		m_strBalance.SetTextColor(RGB(102,102,102));
		m_strConfirming.SetTextColor(RGB(102,102,102));
		m_strTransactionNumber.SetTextColor(RGB(102,102,102));

		m_strAmount1.SetFont(90 , _T("΢���ź�"));
		m_strAmount2.SetFont(90 , _T("΢���ź�"));
		m_strAmount3.SetFont(90 , _T("΢���ź�"));
		


		m_strDesAddr1.SetFont(90 , _T("΢���ź�"));
		m_strDesAddr2.SetFont(90 , _T("΢���ź�"));
		m_strDesAddr3.SetFont(90 , _T("΢���ź�"));
		


		m_strSrcAddr1.SetFont(90 , _T("΢���ź�"));
		m_strSrcAddr2.SetFont(90 , _T("΢���ź�"));
		m_strSrcAddr3.SetFont(90 , _T("΢���ź�"));

		theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_MAIN_UI );
	}
	return bRet;
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if( NULL != GetSafeHwnd() ) {
		const int div = 100 ;

		CRect rc ;
		GetClientRect( rc ) ;
		//�������λ��
		CWnd *pst = GetDlgItem( IDC_ST_BALANCE ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect );    
			pst->SetWindowPos( NULL ,(276 - rect.Width())/ 2 + 80 ,(rc.Height()/100)*13 , /*rect.Width()*/rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//����ȷ�����λ��
		pst = GetDlgItem( IDC_ST_CONFIRMING ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,/*(rc.Width()/100)*50*/404 + 30 ,(rc.Height()/100)*13  , /*rect.Width()*/292, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//���ý�����
		pst = GetDlgItem( IDC_ST_TRANSACTION_NUMBER) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,/*(int)((rc.Width()/100)*88 + 10)*/696 + 30 ,(rc.Height()/100)*13 , /*rect.Width()*/292, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////����������̬������λ��/////////////////////////////////
		pst = GetDlgItem( IDC_LINK1 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,52 ,(rc.Height()/100)*49  , 294, 20  ,SWP_SHOWWINDOW ) ; 
		}


		pst = GetDlgItem( IDC_LINK2 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,52 ,(rc.Height()/100)*58 , 294, 20  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_LINK3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			//pst->SetWindowPos( NULL ,52 ,(rc.Height()/100)*57, 294, 20  ,SWP_SHOWWINDOW ) ; 
		}


		pst = GetDlgItem( IDC_LINK4 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			//pst->SetWindowPos( NULL ,52 ,(rc.Height()/100)*63, 294, 20 ,SWP_SHOWWINDOW ) ; 
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	 
		//�����������1�������λ��
		pst = GetDlgItem( IDC_ST_SRCADDR1 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,52 ,(rc.Height()/100)*84  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_DESADDR1 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*50 ,(rc.Height()/100)*84  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_AMOUNT1) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*93 ,(rc.Height()/100)*84  , rc.Width()/100*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//�����������2�������λ��
		pst = GetDlgItem( IDC_ST_SRCADDR2 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,52 ,(rc.Height()/100)*94, (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_DESADDR2) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*50 ,(rc.Height()/100)*94 , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_AMOUNT2 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*93 ,(rc.Height()/100)*94 , rc.Width()/100*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//�����������3�������λ��
		pst = GetDlgItem( IDC_ST_SRCADDR3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,52 ,rc.Height() - 40 , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_DESADDR3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*50 ,rc.Height() - 40  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_AMOUNT3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*93 ,rc.Height() - 40  , (rc.Width()/100)*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		//������תȫ����������λ��	
		pst = GetDlgItem( IDC_BTN_TXDETAIL ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*91 + 46, rc.Height()/100*60 + 58, rect.Width(), rect.Height(), SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_BTN_MORE_INFO ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*91 + 45, rc.Height()/100*35 + 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW ) ; 
		}
	}
}


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
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


void CMainDlg::OnBnClickedBtnMoreInfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR key[MAX_PATH + MAX_PATH];     

	// First try ShellExecute()     
	HINSTANCE result = ShellExecute(NULL, _T("open"), "http://www.starshares.org/", NULL,NULL, SW_SHOW);     

	// If it failed, get the .htm regkey and lookup the program     
	if ((UINT)result <= HINSTANCE_ERROR) {     

		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {     
			lstrcat(key, _T("\\shell\\open\\command"));     

			if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {     
				TCHAR *pos;     
				pos = _tcsstr(key, _T("\"%1\""));     
				if (pos == NULL) {                       // No quotes found     
					pos = strstr(key, _T("%1"));       // Check for %1, without quotes      
					if (pos == NULL)                   // No parameter at all...     
						pos = key+lstrlen(key)-1;     
					else    
						*pos = '\0';                 // Remove the parameter     
				}     
				else    
					*pos = '\0';                       // Remove the parameter     

				lstrcat(pos, _T(" "));     
				lstrcat(pos, "http://www.starshares.org/");     
				result = (HINSTANCE) WinExec(key,SW_SHOW);     
			}     
		}     
	}     

}

LONG CMainDlg::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)     
{     
	HKEY hkey;     
	LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);     

	if (retval == ERROR_SUCCESS) {     
		long datasize = MAX_PATH;     
		TCHAR data[MAX_PATH];     
		RegQueryValue(hkey, NULL, data, &datasize);     
		lstrcpy(retdata,data);     
		RegCloseKey(hkey);     
	}     

	return retval;     
} 

