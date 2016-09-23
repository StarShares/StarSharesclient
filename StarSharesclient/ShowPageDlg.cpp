// ShowPageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "ShowPageDlg.h"
#include "afxdialogex.h"
#include "SignAccountsDlg.h"
#include "StarSharesclientDlg.h"
#include "RollDlg.h"


// CShowPageDlg 对话框

IMPLEMENT_DYNAMIC(CShowPageDlg, CDialogEx)

BOOL   CheckNum(CString   str) 
{ 
	bool   bNumFlag   =   true; 
	bool   bFloatFlag   =   false; 
	for(int i=0;i <str.GetLength();i++) 
	{ 
		if(((int)str.GetAt(i)>=48 &&(int)str.GetAt(i) <=57))continue; 
		else   if(str.GetAt(i)== '.') 
		{ 
			if(bFloatFlag) 
			{ 
				bNumFlag   =   false; 
				break;   
			} 
			else 
			{ 
				bFloatFlag   =   true; 
				continue; 
			} 

		} 
		else 
		{ 
			bNumFlag   =   false; 
			break; 
		} 
	} 
	return   bNumFlag; 
}

CShowPageDlg::CShowPageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowPageDlg::IDD, pParent)
{
	m_pBmp = NULL;
}

CShowPageDlg::~CShowPageDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}

	m_brush.DeleteObject();
}

void CShowPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_NUM, m_stNum);
	DDX_Control(pDX, IDC_STATIC_PIC, m_staPic);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_staProgress);
	DDX_Control(pDX, IDC_BTN_PAY_CONFIRM, m_rBtnConfirmed);

	DDX_Control(pDX, IDC_STATIC_ZC_NAME, m_stAssetName);
	DDX_Control(pDX, IDC_STATIC_ISSUER, m_stIssuer);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_stMax);
	DDX_Control(pDX, IDC_STATIC_BASELINE, m_stMin);
	DDX_Control(pDX, IDC_STATIC_DATE, m_stDate);
	DDX_Control(pDX, IDC_STATIC_DAY_REMAIN, m_stDay);
	DDX_Control(pDX, IDC_COMBO_SUPPORT, m_combBuy);
	DDX_Control(pDX, IDC_STATIC_AMOUNT, m_staAmount);
}


BEGIN_MESSAGE_MAP(CShowPageDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_PAY_CONFIRM, &CShowPageDlg::OnBnClickedBtnPayConfirm)
//ON_EN_CHANGE(IDC_EDIT_SUPPORT, &CShowPageDlg::OnChangeEditSupport)
ON_CBN_SELCHANGE(IDC_COMBO_SUPPORT, &CShowPageDlg::OnCbnSelchangeComboSupport)
END_MESSAGE_MAP()


// CShowPageDlg 消息处理程序

#define TRANSPARENT_COLOR     RGB (255, 255, 255)

BOOL CShowPageDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

	LONG lWindowLong = GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED; 
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, lWindowLong); 

	//SetLayeredWindowAttributes (TRANSPARENT_COLOR , 0, LWA_ALPHA );

	// TODO:  在此添加额外的初始化

	//m_strTx1.SetFont(100, _T("微软雅黑"));				//设置显示字体和大小
	//m_strTx1.SetTextColor(RGB(184, 39, 18));
	//m_strTx1.SetWindowText(_T(""));

	m_stAssetName.SetFont(100,_T("微软雅黑"));
	m_stAssetName.SetTextColor(RGB(138,138,138));

	m_stIssuer.SetFont(100,_T("微软雅黑"));
	m_stIssuer.SetTextColor(RGB(138,138,138));

	m_stNum.SetFont(100,_T("微软雅黑"));
	m_stNum.SetTextColor(RGB(138,138,138));

	m_stMax.SetFont(100,_T("微软雅黑"));
	m_stMax.SetTextColor(RGB(138,138,138));

	m_stMin.SetFont(100,_T("微软雅黑"));
	m_stMin.SetTextColor(RGB(138,138,138));

	m_stDate.SetFont(100,_T("微软雅黑"));
	m_stDate.SetTextColor(RGB(138,138,138));

	m_stDay.SetFont(100,_T("微软雅黑"));
	m_stDay.SetTextColor(RGB(138,138,138));

	m_staAmount.SetFont(100,_T("微软雅黑"));
	m_staAmount.SetTextColor(RGB(138,138,138));

	m_brush.CreateSolidBrush(RGB(255,255,255));
	m_staPic.GetWindowRect(m_rcOrigPic);

	m_rBtnConfirmed.SetBitmaps( IDB_BITMAP_QR , RGB(255, 255, 0) , IDB_BITMAP_QR , RGB(255, 255, 255) );
	m_rBtnConfirmed.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnConfirmed.SetWindowText("确认支付") ;
	m_rBtnConfirmed.SetFontEx(-12 , _T("微软雅黑"));
	m_rBtnConfirmed.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
	m_rBtnConfirmed.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_rBtnConfirmed.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255,255));
	m_rBtnConfirmed.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));

	CRect rect;
	m_combBuy.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_combBuy.SetEdtReadOnly();
	m_combBuy.SetEdtNewFont(90);
	m_combBuy.SetListNewFont(90);
	m_combBuy.SetEdtTextColor(RGB(121, 122, 122));
	m_combBuy.SetListTextColor(RGB(118, 192, 50));
	m_combBuy.AotuAdjustDroppedWidth();
	m_combBuy.SetEdtFrameColor(RGB(238,238,238));
	m_combBuy.SetFrameStyle(CYComBox::ONLYONE);

	m_rBtnConfirmed.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CShowPageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != GetSafeHwnd() ) {
		CRect rc ; 
		this->GetWindowRect(rc);

		CWnd *pst = GetDlgItem( IDC_STATIC_ZC_NAME ) ;
		if ( NULL != pst ) {
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,250 , 12 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_PIC);
		if(NULL != pst)
		{
			CRect rect;
			pst->GetClientRect(rect);
			pst->SetWindowPos( NULL ,1 , 1 , 150, rc.Height()-2,SWP_SHOWWINDOW ) ;
		}

		pst = GetDlgItem( IDC_STATIC_ISSUER ) ;
		if ( NULL != pst ) {
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,250 , 36 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_NUM);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,250 , 65 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_PRICE);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,250 , 90 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_BASELINE);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,250 , 118 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_DATE);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,250 , 145 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_DAY_REMAIN);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,250 , 170 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_BTN_PAY_CONFIRM);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,500 , 105 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_COMBO_SUPPORT);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,500 , 75 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_AMOUNT);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,420 , 164, 60, rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem(IDC_STATIC_PROGRESS);
		if(NULL != pst){
			CRect rect;
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,370 , 30 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}
		
	}
}

void CShowPageDlg::SetCtrlFocus()
{
	GetDlgItem(IDC_BTN_PAY_CONFIRM)->SetFocus();
}

HBRUSH CShowPageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor   == CTLCOLOR_DLG)  
		return   m_brush;   //返加红色刷子 
	
	if(nCtlColor   == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CShowPageDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CShowPageDlg::OnEraseBkgnd(CDC* pDC)
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


int CShowPageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetBkBmpNid( IDB_BITMAP_ROLLPAGE ) ;

	return 0;
}


void CShowPageDlg::OnBnClickedBtnPayConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	if (theApp.IsLockWallet())
	{
		return;
	}

	LISTASSET_t assetInfo;

	CRollDlg *pDlg = (CRollDlg*)GetParent();
	if(NULL == pDlg)
	{
		return;
	}

	uistruct::ASSETLIST::const_iterator const_it;
	int iIndex = 0;


	pDlg->RefreshCurPage();

	for(const_it = pDlg->m_VecAssetList.begin(); const_it != pDlg->m_VecAssetList.end(); const_it++)
	{
		if(iIndex == (pDlg->m_nCurAssetIndex))
		{
			assetInfo = *const_it;

			break;
		}

		iIndex++;
	}

	if( 3 != assetInfo.status)
	{
		UiFun::MessageBoxEx(_T("该资产已经停止认购,请到网站查询详细信息!") ,_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	CString strMoney;
	GetDlgItem(IDC_COMBO_SUPPORT)->GetWindowText(strMoney);

	pDlg->LayoutDlg(pDlg->m_nCurAssetIndex);

	theApp.m_SqliteDeal.GetWalletAddressItem(_T(" 1=1 order by money desc limit 1"), &m_AddrMaxInfo);

	string conditon = _T("");
	double dSendMoney = strtod(strMoney,NULL);							//支持的人气币
	if(_T("") == strMoney.GetString() || (dSendMoney >-0.0000001 && dSendMoney< 0.000001))
	{
		UiFun::MessageBoxEx(_T("发送金额不能为0") ,_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	if(dSendMoney > m_AddrMaxInfo.fMoney || ( m_AddrMaxInfo.fMoney>-0.0000001 && m_AddrMaxInfo.fMoney< 0.000001 )) 
	{
		double dmoney =  theApp.m_SqliteDeal.GetTableItemSum(_T("t_wallet_address") ,_T("money"), _T(" 1=1 "));

		if(dSendMoney > dmoney || ( dmoney >-0.0000001 && dmoney < 0.000001 )) 
		{
			UiFun::MessageBoxEx(_T("账户余额不足！") , _T("提示") ,MFB_OK|MFB_TIP );
			return;
		}
		if(IDYES == UiFun::MessageBoxEx(_T("单独账户余额不足,是否进行钱包归集！") ,  _T("提示") ,MFB_YESNO|MFB_TIP ))
		{
			Json::Reader reader;  
			Json::Value root;
			Json::Value value;
			CString strShowData;
			string strRet;

			conditon = strprintf("%s %s %f","notionalpoolingbalance" ,m_AddrMaxInfo.address, 1 );

			if(!CSoyPayHelp::getInstance()->SendRpc(conditon,strRet))
			{
				TRACE("notionalpoolingbalance rpccmd error");
				return ;
			}

			if (!reader.parse(strRet, root)) 
				return ;

			value = root["Tx"];
			if( 0 == value.size())
			{
				strShowData.Format(_T("没有可以转到目的地址的钱"));
				UiFun::MessageBoxEx(strShowData , _T("提示") ,MFB_YESNO|MFB_TIP );
				return;
			}else
			{
				strShowData.Format(_T("钱包归集成功"));
				UiFun::MessageBoxEx(strShowData , _T("提示") ,MFB_YESNO|MFB_TIP );
			}
		}
		else
		{
			return;
		}
	}

	if(!m_AddrMaxInfo.bSign) 
	{
		if(IDYES == UiFun::MessageBoxEx(_T("发送地址未激活") ,  _T("提示"),MFB_YESNO|MFB_TIP ))
		{
			ActAssetAddr(m_AddrMaxInfo.address);
		}
		return;
	}

	Json::Value root;
	string strCommand;
	string strShowData;
	strCommand = strprintf("%s %s %s %lld","sendtoaddress" ,m_AddrMaxInfo.address.c_str() ,assetInfo.AssetAddr ,REAL_MONEY(dSendMoney));

	CString strDisplay;
	strDisplay.Format(_T("%s%.4lfPOP%s%s"),_T("转账"), dSendMoney, _T("至") ,assetInfo.AssetAddr.c_str());

	if (IDCANCEL == UiFun::MessageBoxEx(strDisplay , _T("提示") , MFB_OKCANCEL|MFB_TIP ) )
	{
		return;
	}

	strShowData = _T("");
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
	{
		TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
		return;
	}
	BOOL bRes = FALSE ;
	strShowData = root.toStyledString();
	int pos = strShowData.find("hash");
	if ( pos >=0 ) {
		string strHash = root["hash"].asString() ;
		string strCond;
		strCond = strprintf(" hash='%s' ", strHash.c_str());
		int nItem =  theApp.m_SqliteDeal.GetTableCountItem(_T("t_transaction") , strCond) ;

		if ( 0 == nItem ) {

			CPostMsg postmsg(MSG_USER_GET_UPDATABASE,WM_REVTRANSACTION);
			postmsg.SetData(strHash);
			theApp.m_msgQueue.push(postmsg);
		}
	}

	string strData;
	if ( pos >=0 ) {
		strData = strprintf(" %s\n\n %s:%s\n\n %s:%s\n\n %s：%.4lf\n  hash:%s",_T("转账交易发送成功"),_T("源地址"), m_AddrMaxInfo.address.c_str(),_T("目的地址"),assetInfo.AssetAddr,_T("金额"), dSendMoney,root["hash"].asCString()) ;
	}else{
		strData = _T("转账失败!");
	}
	UiFun::MessageBoxEx(strData.c_str() , _T("") ,MFB_OK|MFB_TIP );
	
}

void CShowPageDlg::ActAssetAddr(string &strAssetAddr)
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (!theApp.m_bIsSyncBlock)
	{
		
		UiFun::MessageBoxEx(_T("同步未完成,不能发送激活交易"),_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	
	CStarSharesclientDlg* pPopDlg = (CStarSharesclientDlg*)AfxGetApp()->m_pMainWnd;

	CString StrShow;

		if(!pPopDlg->m_pSendDlg->m_mapAddrInfo.count(strAssetAddr))
			{
					TRACE("ERROR");
				StrShow.Format(_T("地址不存在"));
				
				UiFun::MessageBoxEx(StrShow ,_T("提示") ,MFB_OK|MFB_TIP );
				return;
		   }
		uistruct::LISTADDR_t te =  pPopDlg->m_pSendDlg->m_mapAddrInfo[strAssetAddr];
		//uistruct::LISTADDR_t * pAddrItem = (uistruct::LISTADDR_t*)m_listCtrl.GetItemData(nRow) ;
		if (te.fMoney <=0)
		{
			StrShow.Format(_T("账户余额为零,不能激活!"));
			
			UiFun::MessageBoxEx(StrShow ,_T("提示") ,MFB_OK|MFB_TIP );
			return;
		}
		if(te.bSign) 
		{
			StrShow.Format(_T("账户已激活!"));
			
			UiFun::MessageBoxEx(StrShow, _T("提示") ,MFB_OK|MFB_TIP );
			return;
		}
		theApp.m_strAddress.Format(_T("%s") ,te.address.c_str() ) ;

		CSignAccountsDlg dlg;
		dlg.DoModal();
}

BOOL CShowPageDlg::PreTranslateMessage(MSG* pMsg)
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


void CShowPageDlg::OnChangeEditSupport()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strMoney = "";
	string strGet;
	//GetDlgItem(IDC_EDIT_SUPPORT)->GetWindowText(strMoney);

	if(!CheckNum(strMoney))
	{
		UiFun::MessageBoxEx(_T("请输入纯数字!") ,_T("提示") ,MFB_OK|MFB_TIP );
	}

	if(strMoney == "")
	{
		strGet = strprintf("%.3f", 0.0);
		GetDlgItem(IDC_STATIC_AMOUNT)->SetWindowText(strGet.c_str());
		return;
	}
	double dSendMoney = strtod(strMoney,NULL);

	LISTASSET_t assetInfo;
	CRollDlg *pDlg = (CRollDlg*)GetParent();			
	uistruct::ASSETLIST::const_iterator const_it;
	int iIndex = 0;
	for(const_it = pDlg->m_VecAssetList.begin(); const_it != pDlg->m_VecAssetList.end(); const_it++)
	{
		if(iIndex == (pDlg->m_nCurAssetIndex))
		{
			assetInfo = *const_it;
			break;
		}
		iIndex++;
	}

	double dGet = (dSendMoney / (assetInfo.CurAmount + dSendMoney)) * assetInfo.PopNum;

	strGet = strprintf("%0.3f", dGet);

	GetDlgItem(IDC_STATIC_AMOUNT)->SetWindowText(strGet.c_str());
}


void CShowPageDlg::OnCbnSelchangeComboSupport()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strMoney = "";
	int sel =m_combBuy.GetCurSel();
	if (sel != -1)
	{
		m_combBuy.GetLBText(sel,strMoney);
	}

	string strGet;

	if(!CheckNum(strMoney))
	{
		UiFun::MessageBoxEx(_T("请输入纯数字!") ,_T("提示") ,MFB_OK|MFB_TIP );
	}

	if(strMoney == "")
	{
		strGet = strprintf("%.3f", 0.0);
		GetDlgItem(IDC_STATIC_AMOUNT)->SetWindowText(strGet.c_str());
		return;
	}
	double dSendMoney = strtod(strMoney,NULL);

	LISTASSET_t assetInfo;
	CRollDlg *pDlg = (CRollDlg*)GetParent();			
	uistruct::ASSETLIST::const_iterator const_it;
	int iIndex = 0;
	for(const_it = pDlg->m_VecAssetList.begin(); const_it != pDlg->m_VecAssetList.end(); const_it++)
	{
		if(iIndex == (pDlg->m_nCurAssetIndex))
		{
			assetInfo = *const_it;
			break;
		}
		iIndex++;
	}

	double dGet = (dSendMoney / (assetInfo.CurAmount + dSendMoney)) * assetInfo.PopNum;

	strGet = strprintf("%0.3f", dGet);

	GetDlgItem(IDC_STATIC_AMOUNT)->SetWindowText(strGet.c_str());

}
