// ZCOutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "ZCOutDlg.h"
#include "afxdialogex.h"
#include "SignAccountsDlg.h"
#include "StarSharesclientDlg.h"

// CZCOutDlg 对话框

IMPLEMENT_DYNAMIC(CZCOutDlg, CDialogEx)

CZCOutDlg::CZCOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZCOutDlg::IDD, pParent)
{
	m_pBmp = NULL ;
	m_rbtnWDZC.LoadBitmaps(IDB_BITMAP_ZC_BLACK, IDB_BITMAP_ZC_BLUE, IDB_BITMAP_ZC_BLUE, IDB_BITMAP_ZC_BLACK);

	m_rBtnZCOut.LoadBitmaps(IDB_BITMAP_ZCOUT);
}

CZCOutDlg::~CZCOutDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}

void CZCOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MY_ASSET, m_rbtnWDZC);
	DDX_Control(pDX, IDC_BTN_OUT_ASSET, m_rBtnZCOut);
	DDX_Control(pDX, IDC_EDIT_OUT_POP_NUM, m_veditPopOut);
	DDX_Control(pDX, IDC_EDIT_DEST_ADDR, m_veditDestAddr);
	DDX_Control(pDX, IDC_BTN_OUT, m_sBtnOut);
	DDX_Control(pDX, IDC_COMBO_ASSET_SELECT, m_ycomAsset);
	DDX_Control(pDX, IDC_LIST_OUT_DETAIL, m_lstOutDetail);
}


BEGIN_MESSAGE_MAP(CZCOutDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_MY_ASSET, &CZCOutDlg::OnBnClickedBtnMyAsset)
	ON_MESSAGE( WM_BN_CLICK, OnCopyAcct)
	ON_BN_CLICKED(IDC_BTN_OUT, &CZCOutDlg::OnBnClickedBtnOut)
	ON_CBN_SELCHANGE(IDC_COMBO_ASSET_SELECT, &CZCOutDlg::OnCbnSelchangeComboAssetSelect)

	ON_MESSAGE(MSG_USER_TRANSRECORD_UI , &CZCOutDlg::OnShowListCtrl )
	ON_MESSAGE(MSG_USER_ASSET_SEND_UI, &CZCOutDlg::OnShowListaddrData)
END_MESSAGE_MAP()


// CZCOutDlg 消息处理程序
LRESULT CZCOutDlg::OnShowListaddrData( WPARAM wParam, LPARAM lParam ) 
{
	//更新数据
	int type = (int)wParam;
	switch(type)
	{
	case WM_UP_ADDRESS:
		{
			CPostMsg postmsg;
			if (!theApp.m_msgUIAssetOutDlgQueue.pop(postmsg))
			{
				break;
			}

			uistruct::LISTADDR_t addr; 
			string strTemp = postmsg.GetData();
			addr.JsonToStruct(strTemp.c_str());


			if(m_mapAddrInfo.count(addr.address)<=0)
			{
				TRACE("map ModifyComboxItem error");
				break;
			}
			m_mapAddrInfo[addr.address]=addr;
		}
		break;
	case WM_UP_NEWADDRESS:
		{
			CPostMsg postmsg;
			if (!theApp.m_msgUIAssetOutDlgQueue.pop(postmsg))
			{
				break;
			}

			uistruct::LISTADDR_t addr; 
			string strTemp = postmsg.GetData();
			addr.JsonToStruct(strTemp.c_str());


			if(m_mapAddrInfo.count(addr.address)>0)
			{
				TRACE("map InsertComboxIitem error");
				break;
			}
			m_mapAddrInfo[addr.address]=addr;
		}
		break;
	default:
		break;

	}
	return 0 ;
}

void CZCOutDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CZCOutDlg::OnEraseBkgnd(CDC* pDC)
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

	m_lstOutDetail.ShowScrollBar(SB_HORZ, FALSE);

	return 1;
}


BOOL CZCOutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBkBmpNid(IDB_BITMAP_WDZC_OUT_BK);
	theApp.m_SqliteDeal.GetWalletAddressList(_T(" 1=1 "), &m_mapAddrInfo);

	struct LISTCol {
		CString		name ;
		UINT		size ;
	} listcol[6]  = {
		{"序号" ,      60},
		{"资产名称" ,      110}, 
		{"转出账号" ,  280},
		{"转出状态", 80},
		{"红人秀数量", 123},
		{"", 50}
	};
	m_lstOutDetail.SetBkColor(RGB(255, 255,255));       
	m_lstOutDetail.SetRowHeigt(30);               
	m_lstOutDetail.SetHeaderHeight(1.5);         
	m_lstOutDetail.SetHeaderFontHW(15,0);
	m_lstOutDetail.SetHeaderBKColor(/*224,65,18,*/ 87, 101, 112, 0); 
	m_lstOutDetail.SetHeaderTextColor(RGB(255,255,255)); 
	m_lstOutDetail.SetTextColor(RGB(0,0,0));  
	for( int i = 0 ; i <6 ; i++  ) {
		m_lstOutDetail.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
	}
	m_lstOutDetail.SetExtendedStyle(LVS_EX_FULLROWSELECT |  LVS_EX_HEADERDRAGDROP );

	m_lstOutDetail.SetBkColor(RGB(255, 255,255));       
	m_lstOutDetail.SetRowHeigt(30);               
	m_lstOutDetail.SetHeaderHeight(1.5);         
	m_lstOutDetail.SetHeaderFontHW(15,0);
	m_lstOutDetail.SetHeaderBKColor(/*224,65,18,*/ 87, 101, 112, 0); 
	m_lstOutDetail.SetHeaderTextColor(RGB(255,255,255)); 
	m_lstOutDetail.SetTextColor(RGB(0,0,0));  
	for( int i = 0 ; i <5 ; i++  ) {
		m_lstOutDetail.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
	}
	m_lstOutDetail.SetExtendedStyle(LVS_EX_FULLROWSELECT |  LVS_EX_HEADERDRAGDROP );

	m_veditPopOut.SetNewFont(100);
	m_veditPopOut.SetTextColor(RGB(121, 122, 122));
	m_veditPopOut.SetBkColor(RGB(238,238,238));


	m_veditDestAddr.SetNewFont(100);
	m_veditDestAddr.SetTextColor(RGB(121, 122, 122));
	m_veditDestAddr.SetBkColor(RGB(238,238,238));

	m_sBtnOut.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 0) , IDB_BITMAP_BUT1 , RGB(255, 255, 255) );
	m_sBtnOut.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_sBtnOut.SetWindowText("确认转出") ;
	m_sBtnOut.SetFontEx(-12 , _T("微软雅黑"));
	m_sBtnOut.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_sBtnOut.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_sBtnOut.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_sBtnOut.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_sBtnOut.SizeToContent();


	CRect rcComb2;
	m_ycomAsset.GetWindowRect(&rcComb2);
	ScreenToClient(&rcComb2);
	m_ycomAsset.MoveWindow(30 , 100, 240, rcComb2.Height());	
	m_ycomAsset.SetEdtNewFont(100);
	m_ycomAsset.SetListNewFont(100);
	m_ycomAsset.SetEdtTextColor(RGB(121, 122, 122));
	m_ycomAsset.SetListTextColor(RGB(118, 192, 50));
	//m_YCombox1.SetItemHeight(-1, 50); // 不用此函数设编辑框高度，让它根据字体自动调整
	m_ycomAsset.SetItemHeight(1, 35);
	m_ycomAsset.AotuAdjustDroppedWidth();
	m_ycomAsset.SetEdtFrameColor(RGB(238,238,238));
	m_ycomAsset.SetFrameStyle(CYComBox::ONLYONE);



	AddListaddrDataBox();
	InitCombox();
	m_ycomAsset.SetCurSel(0);
	int sel =m_ycomAsset.GetCurSel();
	if (sel != -1)
	{
	CString curText =_T("");
	m_ycomAsset.GetLBText(sel,curText);
	string appname =strprintf("%s",curText);
	m_appid = GetAppID(appname);
	}

	OninitializeList();

	theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_TRANSRECORD_UI ) ;
	theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_ASSET_SEND_UI ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CZCOutDlg::InitCombox()
{
	string strCondition = "Status = 5 and Result = 1";
	theApp.m_SqliteDeal.GetAssetList(strCondition, (&m_MapMyAssetList));
	map<string,LISTASSET_t>::iterator it= m_MapMyAssetList.begin();
	for(;it != m_MapMyAssetList.end();it++)
	{
		LISTASSET_t data=it->second;
		CString temp;
		temp.Format(_T("%s"),data.AssetName.c_str());	

		m_ycomAsset.AddString(temp);
	}

}


void CZCOutDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect ; 

	int curWidth = 0;

	CWnd *pst = (CWnd*)GetDlgItem(IDC_BTN_MY_ASSET);
	if( NULL != pst ) {
		pst->GetWindowRect(&rect);
		pst->SetWindowPos( NULL ,30 , 18,rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ;

		curWidth += 30 + rect.Width();
	}

	pst = (CWnd*)GetDlgItem(IDC_BTN_OUT_ASSET);
	if( NULL != pst ) {
		pst->GetWindowRect(&rect);
		pst->SetWindowPos( NULL ,curWidth + 25 , 18,rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
	}

	pst = (CWnd*)GetDlgItem(IDC_EDIT_OUT_POP_NUM);
	if( NULL != pst ) {
		pst->GetWindowRect(&rect);
		pst->SetWindowPos( NULL ,285 , 95, 240, 40,SWP_SHOWWINDOW ) ; 
	}

	pst = (CWnd*)GetDlgItem(IDC_EDIT_DEST_ADDR);
	if( NULL != pst ) {
		pst->GetWindowRect(&rect);
		pst->SetWindowPos( NULL ,30 , 175, 310, 40,SWP_SHOWWINDOW ) ; 
	}

	pst = (CWnd*)GetDlgItem(IDC_BTN_OUT);
	if( NULL != pst ) {
		pst->GetWindowRect(&rect);
		pst->SetWindowPos( NULL ,360 , 175, rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
	}

	pst = (CWnd*)GetDlgItem(IDC_LIST_OUT_DETAIL);
	if( NULL != pst ) {
		pst->GetWindowRect(&rect);
		pst->SetWindowPos( NULL ,30 , 255, 720, 165,SWP_SHOWWINDOW ) ; 
	}

	


}

BOOL CZCOutDlg::AddListaddrDataBox()
{

	/*theApp.m_SqliteDeal.GetMyAssetList(_T(" 1=1 "), &m_mapAssetInfo);

	if ( 0 == m_mapAssetInfo.size() ) return FALSE ;

	//清除ComBox控件
	((CComboBox*)GetDlgItem(IDC_COMBO_ASSET_SELECT))->ResetContent();
	//加载到ComBox控件
	int nItem = 0;
	std::map<string,uistruct::LISTMYASSET_t>::const_iterator const_it;
	for ( const_it = m_mapAssetInfo.begin() ; const_it != m_mapAssetInfo.end() ; const_it++ ) {

		((CComboBox*)GetDlgItem(IDC_COMBO_ASSET_SELECT))->InsertString(nItem , const_it->second.assetName.c_str() );
		//((CComboBox*)GetDlgItem(IDC_COMBO_ADDR_OUT))->SetItemData(nItem, (DWORD_PTR)&(*const_it));
		nItem++;
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_ASSET_SELECT))->SetCurSel(0);*/

	//CString address;
	//int sel = m_ycomAsset.GetCurSel();
	//if (sel < 0)
	//{
	//	return FALSE;
	//}
	//m_ycomAsset.GetLBText(sel,address);
	//string strAddr =strprintf("%s",address);
	//std::map<string,uistruct::LISTMYASSET_t>::const_iterator item = m_mapAssetInfo.find(strAddr);

	//if (m_mapAssetInfo.count(strAddr)>0 ) {
	//	uistruct::LISTMYASSET_t assetStruc = m_mapAssetInfo[strAddr];
	//	string strshow;
	//	strshow = strprintf("%.8f",assetStruc.fMoney);
	//	//m_strTx1.SetWindowText(strshow.c_str());
	//	Invalidate();
	//}
	return TRUE ;
}


void CZCOutDlg::OnBnClickedBtnMyAsset()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);

	::SendMessage(GetParent()->m_hWnd, WM_OUTBACK_MYASSERT, CWDZCDlg::IDD, 0);
}

LRESULT CZCOutDlg::OnCopyAcct(WPARAM wParam, LPARAM lParam)
{
	int nItem = (int)wParam;
	int nSubItem = (int)lParam;
	nSubItem--;
	string StrShow;

#ifdef USE_TOPINDEX_BUTTON
	int iTopIndex = m_lstOutDetail.GetTopIndex();
	nItem = iTopIndex + nItem;
#endif

	CString szItemText = m_lstOutDetail.GetItemText( nItem, 2 );

	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, szItemText.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(szItemText));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
		StrShow = _T("地址已复制到剪贴板");

		UiFun::MessageBoxEx(StrShow.c_str() , _T("提示") ,MFB_OK|MFB_TIP );
	}

	return 0;
}


void CZCOutDlg::OnBnClickedBtnOut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString curText =_T("");															//对应资产
	CString strAmount = _T("");															//资产转移金额
	CString strRecvAddr = _T("");														//资产转移的接收地址
	uistruct::LISTADDR_t data;															//地址信息

	m_ycomAsset.GetWindowText(curText);
	if(curText == "")
	{
		UiFun::MessageBoxEx(_T("请输入资产名称!"), _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	string appname =strprintf("%s",curText);
	m_appid = GetAppID(appname);														//资产ID
	if("" == m_appid)
	{
		UiFun::MessageBoxEx(_T("资产不存在!"), _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	GetDlgItem(IDC_EDIT_OUT_POP_NUM)->GetWindowText(strAmount);
	if("" == strAmount)
	{
		UiFun::MessageBoxEx(_T("请输入转出资产数量!"), _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	GetDlgItem(IDC_EDIT_DEST_ADDR)->GetWindowText(strRecvAddr);
	if("" == strRecvAddr)
	{
		UiFun::MessageBoxEx(_T("请输入资产转出的接收地址!"), _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	string strRevAddr = strRecvAddr;

	if (theApp.IsLockWallet())
	{
		return ;
	}

	Json::Reader reader;  
	Json::Value root;

	string strCommand;																//RPC命令
	string  strShowData;															//RPC结果

	strCommand = strprintf("%s %s", "getassets", m_appid);							//获取当前钱包响应的资产信息
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,strShowData))
	{
		TRACE("rpccmd getassets error when btnclick out asset\r\n");
		return;
	}
	if(!reader.parse(strShowData, root))
	{
		return ;
	}

	UINT64 ullTotal = 0;															//对应资产的总和
	UINT64 ullMax = 0;																//钱包地址中含有对应资产最多的值
	Json::Value valArray;															//资产具体所在地址数组
	Json::Value val;																//具体地址的资产信息

	string strAssetSendAddr;														//资产的发送地址
	double dMoney = 0.0;															//发送地址中的资产数量

	string strContractData = _T("");

	valArray = root["Lists"];
	ullTotal = root["TotalAssets"].asUInt64();

	if(0 == valArray.size())
	{
		UiFun::MessageBoxEx(_T("钱包中该资产余额为零!"),_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	int iCurIndex = 0;
	for(int i = 0; i < valArray.size(); i++)
	{
		if(ullMax > valArray[i]["FreeValues"].asUInt64())
		{

		}else
		{
			ullMax = valArray[i]["FreeValues"].asUInt64();
			val = valArray[i];
		}
	}

	strAssetSendAddr = val["Address"].asString();
	dMoney = val["FreeValues"].asUInt64()*1.0/COIN;

	if(0 == strcmp(strAssetSendAddr.c_str(), strRecvAddr))
	{
		if(MFB_OK == UiFun::MessageBoxEx("资产的发送地址和接收地址相同, 是否所有归集资产到该地址",_T("提示") ,MFB_OK|MFB_CANCEL|MFB_TIP ))
		{
			strCommand = strprintf("%s %s %s %d", "notionalpoolingasset", m_appid, strAssetSendAddr, 1);
			if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,strShowData))
			{
				TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
				return;
			}
		}
		return;
	}

	double dSendMoney = strtod(strAmount,NULL);
	if(dSendMoney > dMoney || ( dMoney>-0.0000001 && dMoney< 0.000001 )) 
	{
		if(MFB_OK == UiFun::MessageBoxEx(_T("资产余额不足,是否进行资产归集") , _T("提示") ,MFB_OK|MFB_TIP ))
		{
			strCommand = strprintf("%s %s %s %d", "notionalpoolingasset", m_appid, strAssetSendAddr, 1);
			if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,strShowData))
			{
				TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
				return;
			}
		}
		return;
	}

	if(strAssetSendAddr!=_T(""))
	{
		strAssetSendAddr =UiFun::trimleft(strAssetSendAddr);
		strAssetSendAddr =UiFun::trimright(strAssetSendAddr);
		if(m_mapAddrInfo.count(strAssetSendAddr)<=0)
		{
			UiFun::MessageBoxEx(_T("发送地址不是钱包地址") , _T("提示") ,MFB_OK|MFB_TIP );
			return;
		}
		data = m_mapAddrInfo[strAssetSendAddr];
	}

	if(!data.bSign) 
	{
		strShowData = _T("发送地址");
		strShowData += strAssetSendAddr;
		strShowData += _T("未激活");
		UiFun::MessageBoxEx(strShowData.c_str(),  _T("提示"),MFB_OK|MFB_TIP );
		return;
	}

	strContractData = CSoyPayHelp::getInstance()->GetAppAccountSend(strRevAddr, (UINT64)REAL_MONEY(dSendMoney));
	string strData = CSoyPayHelp::getInstance()->CreateContractTx( m_appid,strAssetSendAddr,strContractData,0,(INT64)REAL_MONEY(0.01),0);
	CSoyPayHelp::getInstance()->SendContacrRpc(strData,strShowData);
	if (strShowData =="")
	{
		return;
	}

	//strContractData=CSoyPayHelp::getInstance()->GetAppAccountTransferSome(strRevAddr, 0, (UINT64)REAL_MONEY(dSendMoney));
	//strCommand = CSoyPayHelp::getInstance()->CreateContractTx( m_appid,strAssetSendAddr,strContractData,0,(INT64)REAL_MONEY(0.01),0);			//源地址
	//CSoyPayHelp::getInstance()->SendContacrRpc(strCommand,strShowData);
	//if (strShowData =="")
	//{
	//	return;
	//}

	if (!reader.parse(strShowData, root)) 
		return  ;
	BOOL bRes = FALSE ;
	string strTip;
	int pos = strShowData.find("hash");
	if ( pos >=0 ) {
		bRes = TRUE ;
		strTip = strprintf("%s\n%s" , _T("转移部分资产成功!"),root["hash"].asCString() ) ;

		//插入到数据库
		string strHash = root["hash"].asString() ;
		string strCond;
		strCond = strprintf(" hash='%s' ", strHash.c_str());
		int nItem =  theApp.m_SqliteDeal.GetTableCountItem(_T("t_transaction") , strCond) ;

		if ( 0 == nItem ) {

			CPostMsg postmsg(MSG_USER_GET_UPDATABASE,WM_REVTRANSACTION);
			postmsg.SetData(strHash);
			theApp.m_msgQueue.push(postmsg);
		}

	}else{
		strTip = _T("转移部分资产失败") ;
	}

	UiFun::MessageBoxEx(strTip.c_str(),_T("提示") ,MFB_OK|MFB_TIP );
}


void CZCOutDlg::ActAssetAddr(string &strAssetAddr)
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

		/*m_accountDlg->SetShowAddr(pDbbetData->address);
		CRect rcWindow;
		GetWindowRect(&rcWindow);
		m_accountDlg->MoveWindow(rcWindow.right/2+50,rcWindow.top+200,400,rcWindow.Height()/2);
		m_accountDlg->ShowWindow(SW_SHOW);*/
	
}


void CZCOutDlg::OnCbnSelchangeComboAssetSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel =m_ycomAsset.GetCurSel();
	if (sel != -1)
	{
		CString curText =_T("");
		m_ycomAsset.GetLBText(sel,curText);
		string appname =strprintf("%s",curText);
		m_appid = GetAppID(appname);
	}
}


string CZCOutDlg::GetAppID(string AppName)
{
	map<string,LISTASSET_t>::iterator it= m_MapMyAssetList.begin();
	for(;it != m_MapMyAssetList.end();it++)
	{
		if (strcmp(it->second.AssetName.c_str(),AppName.c_str()) ==0)
		{
			return it->second.AssetID;
		}
	}
	return "";
}

LRESULT  CZCOutDlg::OnShowListCtrl(  WPARAM wParam, LPARAM lParam )
{
	int type = (int)wParam;
	switch(type)
	{
	case WM_INSERT:
		{
			
			m_lstOutDetail.DeleteAllItems();
			OninitializeList();
		}
		break;
	case WM_REMOVETX:
		{
			OninitializeList();

		}
		break;
	default:
		break;

	}

	return 1;
}

void  CZCOutDlg::OninitializeList()
{
	ShowComboxCotent();
}

void    CZCOutDlg::ShowComboxCotent()
{
	uistruct::ASSETDEALLIST AssetOutList;

	int operate = 0;
	string condtion = "1=1 order by confirmed_time DESC";
	uistruct::TRANSRECORDLIST pListInfo;

	string strCond0 =  condtion;
	string tempConditon;
	
	tempConditon = "confirm_height=0 and state = 1 and ";
	tempConditon += strprintf("tx_type = '%s' and ", "CONTRACT_TX");
	tempConditon += strCond0;
	strCond0 = tempConditon;

	theApp.m_SqliteDeal.GetTransactionList(strCond0, &pListInfo); 

	uistruct::TRANSRECORDLIST pListInfo1;
	string strCond;
	strCond = "confirm_height!=0 and state = 1 and ";
	strCond += strprintf("tx_type = '%s' and ", "CONTRACT_TX");
	strCond += condtion;

	theApp.m_SqliteDeal.GetTransactionList(strCond, &pListInfo1); 

	pListInfo.insert(pListInfo.end(),pListInfo1.begin(),pListInfo1.end());

	uistruct::TRANSRECORDLIST pListInfo2;

	strCond0 =  condtion;

	tempConditon = "confirm_height=0 and state = 3 and ";
	tempConditon += strprintf("tx_type = '%s' and ", "CONTRACT_TX");
	tempConditon += strCond0;
	strCond0 = tempConditon;

	theApp.m_SqliteDeal.GetTransactionList(strCond0, &pListInfo2); 

	uistruct::TRANSRECORDLIST pListInfo3;
	strCond = "confirm_height!=0 and state = 3 and ";
	strCond += strprintf("tx_type = '%s' and ", "CONTRACT_TX");
	strCond += condtion;

	theApp.m_SqliteDeal.GetTransactionList(strCond, &pListInfo3); 

	pListInfo2.insert(pListInfo2.end(),pListInfo3.begin(),pListInfo3.end());

	pListInfo.insert(pListInfo.end(),pListInfo2.begin(),pListInfo2.end());



	
	string strShowData;
	for(int i = 0; i < pListInfo.size(); i++)
	{
		condtion = strprintf("%s %s", "getaccountinfo", pListInfo[i].desaddr);
		Json::Value root; 
		if(!CSoyPayHelp::getInstance()->SendRpc(condtion,root))
		{
			TRACE("OnShowListCtrol rpccmd getappaccinfo error");
			return;
		}
		strShowData = root.toStyledString();

		int pos = strShowData.find("RegID");
		string strRegID;
		if (pos >0)
		{
			strRegID = root["RegID"].asString() ;

			map<string,LISTASSET_t>::const_iterator const_it;
			for(const_it = m_MapMyAssetList.begin(); const_it != m_MapMyAssetList.end(); const_it++)
			{
				if(0 == strcmp(const_it->second.AssetID.c_str(), strRegID.c_str()))
				{
					ASSET_SEND userInfo;
					ASSET_PUBLISH publishInfo;

					memset(&userInfo, 0, sizeof(ASSET_SEND));

					ASSETDEAL_t assetOut;

					CSoyPayHelp::getInstance()->GetAppPublishInfo(pListInfo[i].Contract, publishInfo);

					if(publishInfo.type != 0x01)
					{
						CSoyPayHelp::getInstance()->GetAppFreezedAccountInfo(pListInfo[i].Contract, userInfo);

						assetOut.AssetID = const_it->second.AssetID;
						assetOut.AssetName = const_it->second.AssetName;
						assetOut.strSendAssetAddr = const_it->second.AssetAddr;
						assetOut.popNum = userInfo.mMoney;
						assetOut.confirmedHeight = pListInfo[i].confirmedHeight;
						assetOut.iState = pListInfo[i].state;

						AssetOutList.push_back(assetOut);
					}
				}
			}
		}
	}

	OnShowListCtrl(AssetOutList);
}

void  CZCOutDlg::OnShowListCtrl(uistruct::ASSETDEALLIST pListInfo)
{
	m_lstOutDetail.DeleteAllItems();
	m_lstOutDetail.release();
	string strCommand,strShowData ="";

	int index = 0;
	int iRow = 0;
	INT64 nMoney = 0;
	for(unsigned int i =0;i<pListInfo.size();i++)
	{
		int nSubIdx = 0;
		string strOrder ="";
		strOrder= strprintf("%d", index+1);
		m_lstOutDetail.InsertItem(iRow,strOrder.c_str());


		m_lstOutDetail.SetItemText( iRow , ++nSubIdx, pListInfo[i].AssetName.c_str()) ;

		m_lstOutDetail.SetItemText(iRow, ++nSubIdx, pListInfo[i].strSendAssetAddr.c_str());

		if(pListInfo[i].confirmedHeight == 0)
		{
			if(pListInfo[i].iState == 3)
			{
				m_lstOutDetail.SetItemText(iRow , ++nSubIdx , "(平账)确认中" );
			}
			if(pListInfo[i].iState == 1)
			{
				m_lstOutDetail.SetItemText(iRow, ++nSubIdx, "(转出)确认中");
			}

		}
		if(pListInfo[i].confirmedHeight > 0)
		{
			if(pListInfo[i].iState == 3)
			{
				m_lstOutDetail.SetItemText(iRow , ++nSubIdx , "(平账)发送成功" ) ;
			}
			if(pListInfo[i].iState == 1)
			{
				m_lstOutDetail.SetItemText(iRow, ++nSubIdx, "(转出)发送成功");
			}
		}

		strShowData = strprintf("%.3f",(pListInfo[i].popNum)*1.0/COIN);
		m_lstOutDetail.SetItemText(iRow , ++nSubIdx , strShowData.c_str());

		m_lstOutDetail.CreateItemButton(iRow, ++nSubIdx, this->GetSafeHwnd(), _T("复制账号"));

		iRow++;
		index++;
	}
}