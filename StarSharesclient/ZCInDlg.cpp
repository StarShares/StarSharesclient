// ZCInDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "ZCInDlg.h"
#include "afxdialogex.h"
#include "SqliteDeal.h"


// CZCInDlg 对话框

IMPLEMENT_DYNAMIC(CZCInDlg, CDialogEx)

CZCInDlg::CZCInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZCInDlg::IDD, pParent)
{
	m_pBmp = NULL ;
	bExist = FALSE;
	m_btnWDZCEx.LoadBitmaps(IDB_BITMAP_ZC_BLACK, IDB_BITMAP_ZC_BLUE, IDB_BITMAP_ZC_BLUE, IDB_BITMAP_ZC_BLACK);

	m_rBtnZCIn.LoadBitmaps(IDB_BITMAP_ZCIN);
	
}

CZCInDlg::~CZCInDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}

}

void CZCInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_WOZC, m_btnWDZCEx);
	DDX_Control(pDX, IDC_BTN_WOZC_IN, m_rBtnZCIn);
	//DDX_Control(pDX, IDC_EDIT_ZC_NAME, m_veditZCName);
	DDX_Control(pDX, IDC_EDIT_RECV_ADDR, m_veditRecvAddr);
	DDX_Control(pDX, IDC_BTN_IN_TRADE, m_sBtnInTrade);
	DDX_Control(pDX, IDC_LIST_IN_DETAIL, m_lstInDetail);
	DDX_Control(pDX, IDC_BTN_NEWADDR, m_sBtnRecvAddr);
	DDX_Control(pDX, IDC_COMBO_WOZC, m_ycomInAsset);
}


BEGIN_MESSAGE_MAP(CZCInDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_WOZC, &CZCInDlg::OnBnClickedBtnWozc)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_IN_TRADE, &CZCInDlg::OnBnClickedBtnInTrade)
	ON_MESSAGE( WM_BN_CLICK, OnCopyAcct)
	ON_BN_CLICKED(IDC_BTN_NEWADDR, &CZCInDlg::OnBnClickedBtnNewaddr)
	ON_CBN_SELCHANGE(IDC_COMBO_WOZC, &CZCInDlg::OnCbnSelchangeComboWozc)
	ON_MESSAGE(MSG_USER_TRANSRECORD_UI , &CZCInDlg::OnShowListCtrl )
	ON_MESSAGE(MSG_USER_ASSET_RECV_UI, &CZCInDlg::OnShowListaddrData)
	ON_WM_TIMER()
END_MESSAGE_MAP()

	
// CZCInDlg 消息处理程序

void CZCInDlg::SetBkBmpNid( UINT nBitmapIn ) 
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


BOOL CZCInDlg::OnEraseBkgnd(CDC* pDC)
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


BOOL CZCInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBkBmpNid(IDB_BITMAP_WDZC_IN_BK);
	SetTimer(TIMER_RECVTRANSTION, 5000, NULL);

	struct LISTCol {
		CString		name ;
		UINT		size ;
	} listcol[6]  = {
		{"序号" ,      60},
		{"资产名称" ,      110}, 
		{"接收账号" ,  280},
		{"转入状态", 80},
		{"人气星数量", 123},
		{"",50}
	};
	m_lstInDetail.SetBkColor(RGB(255, 255,255));       
	m_lstInDetail.SetRowHeigt(30);               
	m_lstInDetail.SetHeaderHeight(1.5);         
	m_lstInDetail.SetHeaderFontHW(15,0);
	m_lstInDetail.SetHeaderBKColor(87, 101, 112, 0); 
	m_lstInDetail.SetHeaderTextColor(RGB(255,255,255)); 
	m_lstInDetail.SetTextColor(RGB(0,0,0));  
	for( int i = 0 ; i <6 ; i++  ) {
		m_lstInDetail.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
	}
	m_lstInDetail.SetExtendedStyle(LVS_EX_FULLROWSELECT |  LVS_EX_HEADERDRAGDROP );


	m_veditRecvAddr.SetNewFont(100);
	m_veditRecvAddr.SetTextColor(RGB(121, 122, 122));
	m_veditRecvAddr.SetBkColor(RGB(238,238,238));

	m_sBtnRecvAddr.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 0) , IDB_BITMAP_BUT1 , RGB(255, 255, 255) );
	m_sBtnRecvAddr.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_sBtnRecvAddr.SetWindowText("获取接收账号") ;
	m_sBtnRecvAddr.SetFontEx(-12 , _T("微软雅黑"));
	m_sBtnRecvAddr.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_sBtnRecvAddr.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_sBtnRecvAddr.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_sBtnRecvAddr.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_sBtnRecvAddr.SizeToContent();

	m_sBtnInTrade.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 0) , IDB_BITMAP_BUT1 , RGB(255, 255, 255) );
	m_sBtnInTrade.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_sBtnInTrade.SetWindowText("复制资产信息") ;
	m_sBtnInTrade.SetFontEx(-12 , _T("微软雅黑"));
	m_sBtnInTrade.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_sBtnInTrade.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_sBtnInTrade.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_sBtnInTrade.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_sBtnInTrade.SizeToContent();

	CRect rcComb2;
	m_ycomInAsset.GetWindowRect(&rcComb2);
	ScreenToClient(&rcComb2);
	m_ycomInAsset.MoveWindow(35 , 110, 200, rcComb2.Height());	
	m_ycomInAsset.SetEdtNewFont(100);
	m_ycomInAsset.SetListNewFont(100);
	m_ycomInAsset.SetEdtTextColor(RGB(121, 122, 122));
	m_ycomInAsset.SetListTextColor(RGB(118, 192, 50));
	m_ycomInAsset.SetItemHeight(1, 35);
	m_ycomInAsset.AotuAdjustDroppedWidth();
	m_ycomInAsset.SetEdtFrameColor(RGB(238,238,238));
	m_ycomInAsset.SetFrameStyle(CYComBox::ONLYONE);


	//AddListaddrDataBox();
	InitCombox();
	/*m_ycomInAsset.SetCurSel(0);
	int sel =m_ycomInAsset.GetCurSel();
	if (sel != -1)
	{
	CString curText =_T("");
	m_ycomInAsset.GetLBText(sel,curText);
	string appname =strprintf("%s",curText);
	m_appid = GetAppID(appname);
	}*/
	OninitializeList();
	theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_TRANSRECORD_UI ) ;
	theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_ASSET_RECV_UI ) ;
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT  CZCInDlg::OnShowListCtrl(  WPARAM wParam, LPARAM lParam )
{
	int type = (int)wParam;
	switch(type)
	{
	case WM_INSERT:
		{
			m_lstInDetail.DeleteAllItems();
			OninitializeList();
		}
		break;
	case WM_REMOVETX:
		{
			m_lstInDetail.DeleteAllItems();
			OninitializeList();
		}
		break;
	default:
		break;

	}

	return 1;
}

LRESULT CZCInDlg::OnShowListaddrData( WPARAM wParam, LPARAM lParam )
{
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

void  CZCInDlg::OninitializeList()
{
	ShowComboxCotent();
}

void    CZCInDlg::ShowComboxCotent()
{
	uistruct::ASSETDEALLIST AssetInList;

	int operate = 0;
	string condtion = "1=1 order by confirmed_time DESC";
	uistruct::TRANSRECORDLIST pListInfo;

	string strCond0 =  condtion;
	string tempConditon;

	tempConditon = "confirm_height=0 and state = 2 and ";
	tempConditon += strprintf("tx_type = '%s' and ", "CONTRACT_TX");
	tempConditon += strCond0;
	strCond0 = tempConditon;

	theApp.m_SqliteDeal.GetTransactionList(strCond0, &pListInfo); 

	uistruct::TRANSRECORDLIST pListInfo1;
	string strCond;
	strCond = "confirm_height!=0 and state = 2 and ";
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
				if(0 == strcmp(const_it->first.c_str(), strRegID.c_str()))
				{
					ASSET_SEND userInfo;
					ASSET_PUBLISH publishInfo;

					ASSETDEAL_t assetIn;

					CSoyPayHelp::getInstance()->GetAppPublishInfo(pListInfo[i].Contract, publishInfo);

					if(publishInfo.type != 0x01)
					{
						CSoyPayHelp::getInstance()->GetAppFreezedAccountInfo(pListInfo[i].Contract, userInfo);

						assetIn.AssetID = const_it->second.AssetID;
						assetIn.AssetName = const_it->second.AssetName;
						assetIn.strRecvAssetAddr = strprintf("%s",userInfo.address);
						assetIn.popNum = userInfo.mMoney;
						assetIn.confirmedHeight = pListInfo[i].confirmedHeight;
						assetIn.iState = pListInfo[i].state;

						AssetInList.push_back(assetIn);
					}
				}
			}
		}
	}

	OnShowListCtrl(AssetInList);
}

void  CZCInDlg::OnShowListCtrl(uistruct::ASSETDEALLIST pListInfo)
{
	m_lstInDetail.DeleteAllItems();
	m_lstInDetail.release();

	string strCommand,strShowData ="";

	int index = 0;
	int iRow = 0;
	INT64 nMoney = 0;
	for(unsigned int i =0;i<pListInfo.size();i++)
	{
		int nSubIdx = 0;
		string strOrder ="";
		strOrder= strprintf("%d", index+1);
		m_lstInDetail.InsertItem(iRow,strOrder.c_str());


		m_lstInDetail.SetItemText( iRow , ++nSubIdx, pListInfo[i].AssetName.c_str()) ;

		m_lstInDetail.SetItemText(iRow, ++nSubIdx, pListInfo[i].strRecvAssetAddr.c_str());

		if(pListInfo[i].confirmedHeight == 0)
		{
			if(pListInfo[i].iState == 3)
			{
				m_lstInDetail.SetItemText(iRow , ++nSubIdx , "(平账)确认中" );
			}
			if(pListInfo[i].iState == 2)
			{
				m_lstInDetail.SetItemText(iRow, ++nSubIdx, "(转入)确认中");
			}

		}
		if(pListInfo[i].confirmedHeight > 0)
		{
			if(pListInfo[i].iState == 3)
			{
				m_lstInDetail.SetItemText(iRow , ++nSubIdx , "(平账)接收成功" ) ;
			}
			if(pListInfo[i].iState == 2)
			{
				m_lstInDetail.SetItemText(iRow, ++nSubIdx, "(转入)接收成功");
			}
		}

		strShowData = strprintf("%.3f",(pListInfo[i].popNum)*1.0/COIN);
		m_lstInDetail.SetItemText(iRow , ++nSubIdx , strShowData.c_str() ) ;

		m_lstInDetail.CreateItemButton(iRow, ++nSubIdx, this->GetSafeHwnd(), _T("复制账号"));
		iRow++;
		index++;
	}
}

void CZCInDlg::InitCombox()
{
	string strCondition = "Status = 5 and Result = 1";
	theApp.m_SqliteDeal.GetAssetList(strCondition, (&m_MapMyAssetList));
	map<string,LISTASSET_t>::iterator it= m_MapMyAssetList.begin();
	for(;it != m_MapMyAssetList.end();it++)
	{
		LISTASSET_t data=it->second;
		CString temp;
		temp.Format(_T("%s"),data.AssetName.c_str());	

		m_ycomInAsset.AddString(temp);
	}

}

string CZCInDlg::GetAppID(string AppName)
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

void CZCInDlg::OnBnClickedBtnWozc()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);

	::SendMessage(GetParent()->m_hWnd, WM_INBACK_MYASSERT, CWDZCDlg::IDD, 0);

}

void CZCInDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != GetSafeHwnd() ) {
		CRect rect ; 

		int curWidth = 0;

		CWnd *pst = (CWnd*)GetDlgItem(IDC_BTN_WOZC);
		if( NULL != pst ) {
			pst->GetWindowRect(&rect);
			pst->SetWindowPos( NULL ,30 , 18,rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ;

			curWidth += 30 + rect.Width();
		}

		pst = (CWnd*)GetDlgItem(IDC_BTN_WOZC_IN);
		if( NULL != pst ) {
			pst->GetWindowRect(&rect);
			pst->SetWindowPos( NULL ,curWidth + 25 , 18,rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}
		pst = (CWnd*)GetDlgItem(IDC_EDIT_RECV_ADDR);
		if( NULL != pst ) {
			pst->GetWindowRect(&rect);
			pst->SetWindowPos( NULL ,265 , 105, 310, 43,SWP_SHOWWINDOW ) ; 
		}

		pst = (CWnd*)GetDlgItem(IDC_BTN_NEWADDR);
		if( NULL != pst ) {
			pst->GetWindowRect(&rect);
			pst->SetWindowPos( NULL ,610 , 105, rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		

		pst = (CWnd*)GetDlgItem(IDC_BTN_IN_TRADE);
		if( NULL != pst ) {
			pst->GetWindowRect(&rect);
			pst->SetWindowPos( NULL ,35 , 160, rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}

		pst = (CWnd*)GetDlgItem(IDC_LIST_IN_DETAIL);
		if( NULL != pst ) {
			pst->GetWindowRect(&rect);
			pst->SetWindowPos( NULL ,35 , 240, 720, 185,SWP_SHOWWINDOW ) ; 
		}


	}
}


void CZCInDlg::OnBnClickedBtnInTrade()
{
	// TODO: 在此添加控件通知处理程序代码

	string StrShow;

	/*CString str;
	GetDlgItem(IDC_EDIT_ZC_NAME)->GetWindowText(str);*/

	CString str;

	m_ycomInAsset.GetWindowText(str);

	CString str1;
	GetDlgItem(IDC_EDIT_RECV_ADDR)->GetWindowText(str1);

	if(str == "")
	{
		StrShow = _T("请输入资产名称");

		UiFun::MessageBoxEx(StrShow.c_str() , _T("提示") ,MFB_OK|MFB_TIP );

		return;
	}

	if(str1 == "")
	{
		StrShow = _T("请输入接收账号");

		UiFun::MessageBoxEx(StrShow.c_str() , _T("提示") ,MFB_OK|MFB_TIP );

		return;
	}

	//uistruct::LISTADDR_t * pDbbetData = (uistruct::LISTADDR_t*)m_listCtrl.GetItemData(nRow) ;
	CString source  = _T("资产名称:");
	source += str;

	source += ";";
	source += _T("接收账号:");
	source += str1;

	//文本内容保存在source变量中
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
		StrShow = _T("地址已复制到剪贴板");

		UiFun::MessageBoxEx(StrShow.c_str() , _T("提示") ,MFB_OK|MFB_TIP );
	}
}

LRESULT CZCInDlg::OnCopyAcct(WPARAM wParam, LPARAM lParam)
{
	int nItem = (int)wParam;
	int nSubItem = (int)lParam;
	nSubItem--;
	string StrShow;

#ifdef USE_TOPINDEX_BUTTON
	int iTopIndex = m_lstInDetail.GetTopIndex();
	nItem = iTopIndex + nItem;
#endif

	CString szItemText = m_lstInDetail.GetItemText( nItem, 2 );

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

BOOL CZCInDlg::AddListaddrDataBox()
{

	//theApp.m_SqliteDeal.GetMyAssetList(_T(" 1=1 "), &m_mapAssetInfo);

	if ( 0 == m_mapAssetInfo.size() ) return FALSE ;

	//清除ComBox控件
	((CComboBox*)GetDlgItem(IDC_COMBO_WOZC))->ResetContent();
	//加载到ComBox控件
	int nItem = 0;
	std::map<string,uistruct::LISTMYASSET_t>::const_iterator const_it;
	for ( const_it = m_mapAssetInfo.begin() ; const_it != m_mapAssetInfo.end() ; const_it++ ) {

		((CComboBox*)GetDlgItem(IDC_COMBO_WOZC))->InsertString(nItem , const_it->second.assetName.c_str() );
		//((CComboBox*)GetDlgItem(IDC_COMBO_ADDR_OUT))->SetItemData(nItem, (DWORD_PTR)&(*const_it));
		nItem++;
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_WOZC))->SetCurSel(0);

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


void CZCInDlg::OnBnClickedBtnNewaddr()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str;
	m_ycomInAsset.GetWindowText(str);
	if (str == _T(""))
	{
		UiFun::MessageBoxEx(_T("请输入指定的资产") ,  _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	map<string,uistruct::LISTASSET_t>::const_iterator const_it;
	for(const_it = m_MapMyAssetList.begin(); const_it != m_MapMyAssetList.end(); const_it++)
	{
		if(0 == strcmp(const_it->second.AssetName.c_str(),str))
		{
			bExist = TRUE;
			break;
		}
	}

	if(!bExist)
	{
		UiFun::MessageBoxEx(_T("资产不存在!"),_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	int nSubIdx = 0 , i = 0 ;
	string strShowData = _T("");
	Json::Reader reader;  
	Json::Value root;

	string strCommand = strprintf("%s %s", "getassets", m_appid);
	CSoyPayHelp::getInstance()->SendRpc(strCommand,root);
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,strShowData))
	{
		TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
		return;
	}
	if (!reader.parse(strShowData, root)) 
		return ;

	Json::Value valuearray = root["Lists"];
	Json::Value value;

	if(0 == valuearray.size())
	{
		if(MFB_OK == UiFun::MessageBoxEx(_T("该资产没有对应的账户,是否创建新的接收账户!"),_T("提示") ,MFB_OK|MFB_TIP ))
		{
			if (theApp.IsLockWallet())
			{
				return;
			}
			string strCommand;
			int nCold = 0;
			strCommand = strprintf("%s",_T("getnewaddress true"));
			nCold = 1;

			string strShowData ;
			Json::Value root; 
			if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
			{
				TRACE("OnBnClickedButtonScdz rpccmd getnewaddress error");
				return;
			}

			string addr = root["addr"].asString();

			GetDlgItem(IDC_EDIT_RECV_ADDR)->SetWindowText(addr.c_str());

			uistruct::LISTADDR_t newaddr; 
			newaddr.address = addr;
			newaddr.nColdDig = nCold;

			string strSourceData;
			double money = 0.0;
			strSourceData =strprintf("'%s' , '%s' , '%.8f' , '%d' ,'%d','%s'" , addr.c_str() ,"",money ,nCold ,0,"") ;
			uistruct::DATABASEINFO_t   pDatabase;
			pDatabase.strSource = strSourceData;
			pDatabase.strcutjson = newaddr.ToJson();
			pDatabase.strTabName =  _T("t_wallet_address");
			CPostMsg postmsg(MSG_USER_INSERT_DATA,0);
			string  strTemp = pDatabase.ToJson();
			postmsg.SetData(strTemp.c_str());
			theApp.m_msgQueue.push(postmsg);


			strCommand = strprintf("%s:\n%s\n%s",_T("恭喜生成新地址") ,addr ,_T("重新备份钱包或者重新导出私钥") );

			UiFun::MessageBoxEx( strCommand.c_str() , _T("提示"), MFB_OK|MFB_TIP );

			return;
		}
	}

	
	GetDlgItem(IDC_EDIT_RECV_ADDR)->SetWindowText(valuearray[0]["Address"].asString().c_str());
	

}


void CZCInDlg::OnCbnSelchangeComboWozc()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel =m_ycomInAsset.GetCurSel();
	if (sel != -1)
	{
		CString curText =_T("");
		m_ycomInAsset.GetLBText(sel,curText);
		string appname =strprintf("%s",curText);
		m_appid = GetAppID(appname);
	}
}


void CZCInDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nIDEvent)
	{
	case TIMER_RECVTRANSTION:
		{
			string strCommand = strprintf("%s", "getrawmempool false");
			Json::Value root;
			if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
			{
				TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
				break;
			}

			int nCount = root.size();

			for(int i = 0; i < nCount; i++)
			{
				int nItem = 0;
				int nItem1 = 0;
				string strHash = root[i].asString();

				string strCond;
				strCond = strprintf(" hash='%s' ", strHash.c_str());
				nItem =  theApp.m_SqliteDeal.GetTableCountItem(_T("t_transaction") , strCond) ;

				string strCommand,strShowData;
				strCommand = strprintf("%s %s",_T("gettxdetail") ,strHash.c_str() );
				Json::Value root; 
				if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
				{
					TRACE("InsertTransaction rpccmd gettxdetail error");
					return;
				}

				uistruct::REVTRANSACTION_t transcion;
				if (transcion.JsonToStruct(root.toStyledString()))
				{
					
					ASSET_SEND userInfo;
			
					CSoyPayHelp::getInstance()->GetAppFreezedAccountInfo(transcion.Contract, userInfo);
					strCond = strprintf(" address='%s' ", userInfo.address);
					nItem1 = theApp.m_SqliteDeal.GetTableCountItem(_T("t_wallet_address"), strCond);
				}

				if ( (0 == nItem) && (0 != nItem1)) {
					CPostMsg postmsg(MSG_USER_GET_UPDATABASE,WM_REVTRANSACTION);
					postmsg.SetData(strHash);
					theApp.m_msgQueue.push(postmsg);
				}
			}
			OninitializeList();
		}
		break;
	default:
		{
			break;
		}
	}
}
