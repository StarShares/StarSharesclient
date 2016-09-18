// YYYEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "YYYEDlg.h"


// CYYYEDlg

IMPLEMENT_DYNAMIC(CYYYEDlg, CDialogEx)

CYYYEDlg::CYYYEDlg(CWnd* pParent)
{
	m_pBmp = NULL ;
}

CYYYEDlg::~CYYYEDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}

void CYYYEDlg::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_YYYE, m_lstApp);
	DDX_Control(pDX, IDC_BTN_EXTRACT, m_rBtnDraw);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_rBtnSelect);
	DDX_Control(pDX, IDC_COMBO_APPID, m_combApp);
	DDX_Control(pDX, IDC_EDIT_ACCT, m_editAcct);
}



BEGIN_MESSAGE_MAP(CYYYEDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CYYYEDlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_EXTRACT, &CYYYEDlg::OnBnClickedBtnExtract)
	ON_CBN_SELCHANGE(IDC_COMBO_APPID, &CYYYEDlg::OnCbnSelchangeComboAppid)
END_MESSAGE_MAP()



// CYYYEDlg 消息处理程序


void CYYYEDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CYYYEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBkBmpNid(IDB_BITMAP_YYYE);

	//CWnd *pWnd = (CWnd *)GetDlgItem(IDC_LIST_WDZC);

	struct LISTCol {
		CString		name ;
		UINT		size ;
	} listcol[3]  = {
		{"序号" ,      100},
		{"金额" ,      403}, 
		{"解冻高度" ,  200}
	};
	m_lstApp.SetBkColor(RGB(255, 255,255));       
	m_lstApp.SetRowHeigt(23);               
	m_lstApp.SetHeaderHeight(1.5);         
	m_lstApp.SetHeaderFontHW(15,0);
	m_lstApp.SetHeaderBKColor(/*224,65,18,*/ 87, 101, 112, 0); 
	m_lstApp.SetHeaderTextColor(RGB(255,255,255)); 
	m_lstApp.SetTextColor(RGB(0,0,0));  
	for( int i = 0 ; i <3 ; i++  ) {
		m_lstApp.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
	}
	m_lstApp.SetExtendedStyle(LVS_EX_FULLROWSELECT |  LVS_EX_HEADERDRAGDROP );

	m_rBtnSelect.SetBitmaps( IDB_BITMAP_YYYE_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_YYYE_BUT2 , RGB(255, 255, 255) );
	m_rBtnSelect.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnSelect.SetWindowText("查询") ;
	m_rBtnSelect.SetFontEx(-12 , _T("微软雅黑"));
	m_rBtnSelect.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
	m_rBtnSelect.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_rBtnSelect.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255,255));
	m_rBtnSelect.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
	m_rBtnSelect.SizeToContent();

	m_rBtnDraw.SetBitmaps( IDB_BITMAP_YYYE_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_YYYE_BUT2 , RGB(255, 255, 255) );
	m_rBtnDraw.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnDraw.SetWindowText("提现") ;
	m_rBtnDraw.SetFontEx(-12 , _T("微软雅黑"));
	m_rBtnDraw.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
	m_rBtnDraw.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_rBtnDraw.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255,255));
	m_rBtnDraw.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
	m_rBtnDraw.SizeToContent();


	m_editAcct.SetNewFont(100);
	m_editAcct.SetTextColor(RGB(121, 122, 122));
	m_editAcct.SetBkColor(RGB(246, 248, 249));


	CRect rect;
	m_combApp.GetWindowRect(&rect);
	ScreenToClient(&rect);
	//m_time.MoveWindow(30 , 45 , 128, rect.Height());	
	m_combApp.SetEdtNewFont(120);
	m_combApp.SetListNewFont(120);
	m_combApp.SetEdtTextColor(RGB(121, 122, 122));
	m_combApp.SetListTextColor(RGB(118, 192, 50));
	//m_time.SetItemHeight(-1, 180); // 不用此函数设编辑框高度，让它根据字体自动调整
	//m_time.SetItemHeight(1, 35);
	m_combApp.AotuAdjustDroppedWidth();
	m_combApp.SetEdtFrameColor(RGB(238,238,238));
	m_combApp.SetFrameStyle(CYComBox::ONLYONE);

	//m_time.SetNewFont(100);
	//m_time.SetTextColor(RGB(121, 122, 122));
	//m_time.SetBkColor(RGB(246, 248, 249));


	InitCombox();
	m_combApp.SetCurSel(0);
	int sel =m_combApp.GetCurSel();
	if (sel != -1)
	{
		CString curText =_T("");
		m_combApp.GetLBText(sel,curText);
		string appname =strprintf("%s",curText);
		m_appid = GetAppID(appname);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CYYYEDlg::InitCombox()
{
	map<string,CONFIG_APP_DATA>::iterator it= theApp.m_listapp.begin();
	for(;it != theApp.m_listapp.end();it++)
	{
		CONFIG_APP_DATA data=it->second;
		CString temp;

		temp.Format(_T("%s"),data.appname.c_str());	

		m_combApp.AddString(temp);
	}

}

string CYYYEDlg::GetAppID(string AppName)
{
	map<string,CONFIG_APP_DATA>::iterator it= theApp.m_listapp.begin();
	for(;it != theApp.m_listapp.end();it++)
	{
		CONFIG_APP_DATA data=it->second;
		if (strcmp(data.appname.c_str(),AppName.c_str()) ==0)
		{
			return data.appid;
		}
	}
	return "";
}

void CYYYEDlg::OnCbnSelchangeComboAppid()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel =m_combApp.GetCurSel();
	if (sel != -1)
	{
		CString curText =_T("");
		m_combApp.GetLBText(sel,curText);
		string appname =strprintf("%s",curText);
		m_appid = GetAppID(appname);
	}
}

BOOL CYYYEDlg::OnEraseBkgnd(CDC* pDC)
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

	m_lstApp.ShowScrollBar(SB_HORZ, FALSE);

	return 1;
}

void CYYYEDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != GetSafeHwnd() ) {

		CRect rc ;
		GetClientRect( rc ) ;
		
		int curwith = 0;
		CWnd *pst = GetDlgItem( IDC_EDIT_ACCT ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,73 ,46 , 290, 43,SWP_SHOWWINDOW ); 
			curwith = (rc.Width()/100)*8+5+(rc.Width()/100)*40 + 20;
		}
		pst = GetDlgItem( IDC_COMBO_APPID ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,curwith + 55 ,55  , rect.Width(), rect.Height(),SWP_SHOWWINDOW ); 
		}

		pst = GetDlgItem( IDC_BTN_SEARCH ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetWindowRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*83 ,46, rect.Width(), rect.Height(), SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_BTN_EXTRACT ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect(rect) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*97 - 15 ,46, rect.Width(), rect.Height(), SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_LIST_YYYE ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,30 , 140 , 720, 290,SWP_SHOWWINDOW ) ; 
		}
	}
}


void CYYYEDlg::OnBnClickedBtnSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CString addr;
	GetDlgItem(IDC_EDIT_ACCT)->GetWindowText(addr);
	if (addr == _T(""))
	{
		UiFun::MessageBoxEx(_T("地址不能为空") ,  _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	OnShowListCtrol(addr);
}


void CYYYEDlg::OnBnClickedBtnExtract()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( IDCANCEL  == UiFun::MessageBoxEx(_T("是否确认要提现") , _T("提示") , MFB_OKCANCEL|MFB_TIP ) )
		return;

	if (!CheckRegIDValid( m_appid )) return ;

	string  strShowData = _T("");

	CString addr;
	GetDlgItem(IDC_EDIT_ACCT)->GetWindowText(addr);
	if (addr == _T(""))
	{
		UiFun::MessageBoxEx(_T("地址不能为空") ,  _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	string strCond;
	strCond = strprintf(" address='%s' or  reg_id='%s'", addr,m_appid);
	uistruct::LISTADDR_t pAddr;
	int nItem =  theApp.m_SqliteDeal.GetWalletAddressItem(strCond, &pAddr) ;
	if (pAddr.address == "")
	{
		UiFun::MessageBoxEx(_T("此地址不是钱包地址,不能提现") , _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	if (pAddr.bSign == 0 )
	{
		UiFun::MessageBoxEx(_T("此地址没有注册,不能提现") ,  _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	double dmoney = GetFreeMoney(addr);
	if (dmoney <=0.0)
	{
		UiFun::MessageBoxEx(_T("此地址没有可提现的金额") ,  _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	string strContractData ="";
	if (CheckRegIDValid( addr.GetString() )){
		strContractData=m_P2PBetHelp.GetAppAccountMoneyContract(addr.GetString(),1,1,REAL_MONEY(dmoney));
	}else{
		strContractData=m_P2PBetHelp.GetAppAccountMoneyContract(addr.GetString(),1,2,REAL_MONEY(dmoney));
	}


	CString strTxFee;
	INT64 minFee = theApp.m_AppBalanceCfg.WithdrawFee;
	double dnum = (minFee*1.0/COIN);
	strTxFee.Format(_T("%.8f"),dnum);

	if (  (INT64)REAL_MONEY(strtod(strTxFee,NULL)) < 10000  ) {
		UiFun::MessageBoxEx(_T("小费不足") ,  _T("提示") ,MFB_OK|MFB_TIP );
		return ;
	}

	string strData = CSoyPayHelp::getInstance()->CreateContractTx( m_appid,addr.GetString(),strContractData,0,(INT64)REAL_MONEY((strtod(strTxFee,NULL))),0);
	CSoyPayHelp::getInstance()->SendContacrRpc(strData,strShowData);

	if (strShowData =="")
	{
		return;
	}
	Json::Reader reader;  
	Json::Value root;
	if (!reader.parse(strShowData, root)) 
		return  ;
	BOOL bRes = FALSE ;
	string strTip;
	int pos = strShowData.find("hash");

	if ( pos >=0 ) {
		//插入到交易记录数据库
		string strHash = root["hash"].asString();
		CPostMsg postmsg(MSG_USER_GET_UPDATABASE,WM_REVTRANSACTION);
		postmsg.SetData(strHash);
		theApp.m_msgQueue.push(postmsg);
	}

	if ( pos >=0 ) {
		bRes = TRUE ;
		strTip = strprintf("%s\n%s" , _T("恭喜提现成功!"),root["hash"].asCString() ) ;
	}else{
		strTip = _T("提现失败") ;
	}
	UiFun::MessageBoxEx(strTip.c_str() , _T("提示") ,MFB_OK|MFB_TIP );
}

void CYYYEDlg::OnShowListCtrol(CString addr)
{
	string strCommand,strShowData ="";
	strCommand =strprintf("%s %s %s","getappaccinfo" , m_appid ,addr);
	Json::Value root; 
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
	{
		TRACE("OnShowListCtrol rpccmd getappaccinfo error");
		return;
	}
	strShowData = root.toStyledString();

	m_lstApp.DeleteAllItems();

	int pos = strShowData.find("FreeValues");
	INT64 nMoney = 0;
	if (pos >0)
	{
		nMoney = root["FreeValues"].asInt64() ;
	}
	double money = 0.0;
	int coulum = 0;
	int index = 0;
	if (nMoney != 0)
	{
		money = (nMoney*1.0/COIN);
		strShowData = strprintf("%.8f",money);
		string strOrder ="";
		int nSubIdx = 0;
		strOrder= strprintf("%d", 1);
		m_lstApp.InsertItem(coulum,strOrder.c_str());
		m_lstApp.SetItemText( coulum , ++nSubIdx, strShowData.c_str()) ;
		strOrder= "0";
		m_lstApp.SetItemText(coulum , ++nSubIdx , strOrder.c_str() ) ;
		coulum = 1;
		index =1;
	}


	Json::Value valuearray = root["vFreezedFund"]; 
	for(unsigned int i =0;i<valuearray.size();i++)
	{
		int nSubIdx = 0;
		string strOrder ="";
		strOrder= strprintf("%d", index+1);
		m_lstApp.InsertItem(coulum,strOrder.c_str());

		nMoney = valuearray[i]["value"].asInt64() ;
		money = (nMoney*1.0/COIN);
		strShowData = strprintf("%.8f",money);
		m_lstApp.SetItemText( coulum , ++nSubIdx, strShowData.c_str()) ;

		strShowData =strprintf("%d" , valuearray[i]["nHeight"].asInt()) ;
		m_lstApp.SetItemText(coulum , ++nSubIdx , strShowData.c_str() ) ;
		coulum++;
		index++;
	}
}

double CYYYEDlg::GetFreeMoney(CString addr)
{
	string strCommand,strShowData ="";
	strCommand =strprintf("%s %s %s","getappaccinfo" , m_appid ,addr);
	Json::Value root; 
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
	{
		TRACE("GetFreeMoney rpccmd getappaccinfo error");
		return 0.0;
	}

	INT64 nMoney = 0;

	nMoney = root["FreeValues"].asInt64() ;

	double money = (nMoney*1.0/COIN);
	return money;
}

BOOL CYYYEDlg::PreTranslateMessage(MSG* pMsg)
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

	return CDialogEx::PreTranslateMessage(pMsg);
}
