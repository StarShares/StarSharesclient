// ZCOutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "ZCOutDlg.h"
#include "afxdialogex.h"
#include "SignAccountsDlg.h"
#include "StarSharesclientDlg.h"

// CZCOutDlg �Ի���

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


// CZCOutDlg ��Ϣ�������
LRESULT CZCOutDlg::OnShowListaddrData( WPARAM wParam, LPARAM lParam ) 
{
	//��������
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

	m_lstOutDetail.ShowScrollBar(SB_HORZ, FALSE);

	return 1;
}


BOOL CZCOutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBkBmpNid(IDB_BITMAP_WDZC_OUT_BK);
	theApp.m_SqliteDeal.GetWalletAddressList(_T(" 1=1 "), &m_mapAddrInfo);

	struct LISTCol {
		CString		name ;
		UINT		size ;
	} listcol[6]  = {
		{"���" ,      60},
		{"�ʲ�����" ,      110}, 
		{"ת���˺�" ,  280},
		{"ת��״̬", 80},
		{"����������", 123},
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
	m_sBtnOut.SetWindowText("ȷ��ת��") ;
	m_sBtnOut.SetFontEx(-12 , _T("΢���ź�"));
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
	//m_YCombox1.SetItemHeight(-1, 50); // ���ô˺�����༭��߶ȣ��������������Զ�����
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
	// �쳣: OCX ����ҳӦ���� FALSE
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

	// TODO: �ڴ˴������Ϣ����������
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

	//���ComBox�ؼ�
	((CComboBox*)GetDlgItem(IDC_COMBO_ASSET_SELECT))->ResetContent();
	//���ص�ComBox�ؼ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		StrShow = _T("��ַ�Ѹ��Ƶ�������");

		UiFun::MessageBoxEx(StrShow.c_str() , _T("��ʾ") ,MFB_OK|MFB_TIP );
	}

	return 0;
}


void CZCOutDlg::OnBnClickedBtnOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString curText =_T("");															//��Ӧ�ʲ�
	CString strAmount = _T("");															//�ʲ�ת�ƽ��
	CString strRecvAddr = _T("");														//�ʲ�ת�ƵĽ��յ�ַ
	uistruct::LISTADDR_t data;															//��ַ��Ϣ

	m_ycomAsset.GetWindowText(curText);
	if(curText == "")
	{
		UiFun::MessageBoxEx(_T("�������ʲ�����!"), _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}
	string appname =strprintf("%s",curText);
	m_appid = GetAppID(appname);														//�ʲ�ID
	if("" == m_appid)
	{
		UiFun::MessageBoxEx(_T("�ʲ�������!"), _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}

	GetDlgItem(IDC_EDIT_OUT_POP_NUM)->GetWindowText(strAmount);
	if("" == strAmount)
	{
		UiFun::MessageBoxEx(_T("������ת���ʲ�����!"), _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}

	GetDlgItem(IDC_EDIT_DEST_ADDR)->GetWindowText(strRecvAddr);
	if("" == strRecvAddr)
	{
		UiFun::MessageBoxEx(_T("�������ʲ�ת���Ľ��յ�ַ!"), _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}
	string strRevAddr = strRecvAddr;

	if (theApp.IsLockWallet())
	{
		return ;
	}

	Json::Reader reader;  
	Json::Value root;

	string strCommand;																//RPC����
	string  strShowData;															//RPC���

	strCommand = strprintf("%s %s", "getassets", m_appid);							//��ȡ��ǰǮ����Ӧ���ʲ���Ϣ
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,strShowData))
	{
		TRACE("rpccmd getassets error when btnclick out asset\r\n");
		return;
	}
	if(!reader.parse(strShowData, root))
	{
		return ;
	}

	UINT64 ullTotal = 0;															//��Ӧ�ʲ����ܺ�
	UINT64 ullMax = 0;																//Ǯ����ַ�к��ж�Ӧ�ʲ�����ֵ
	Json::Value valArray;															//�ʲ��������ڵ�ַ����
	Json::Value val;																//�����ַ���ʲ���Ϣ

	string strAssetSendAddr;														//�ʲ��ķ��͵�ַ
	double dMoney = 0.0;															//���͵�ַ�е��ʲ�����

	string strContractData = _T("");

	valArray = root["Lists"];
	ullTotal = root["TotalAssets"].asUInt64();

	if(0 == valArray.size())
	{
		UiFun::MessageBoxEx(_T("Ǯ���и��ʲ����Ϊ��!"),_T("��ʾ") ,MFB_OK|MFB_TIP );
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
		if(MFB_OK == UiFun::MessageBoxEx("�ʲ��ķ��͵�ַ�ͽ��յ�ַ��ͬ, �Ƿ����й鼯�ʲ����õ�ַ",_T("��ʾ") ,MFB_OK|MFB_CANCEL|MFB_TIP ))
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
		if(MFB_OK == UiFun::MessageBoxEx(_T("�ʲ�����,�Ƿ�����ʲ��鼯") , _T("��ʾ") ,MFB_OK|MFB_TIP ))
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
			UiFun::MessageBoxEx(_T("���͵�ַ����Ǯ����ַ") , _T("��ʾ") ,MFB_OK|MFB_TIP );
			return;
		}
		data = m_mapAddrInfo[strAssetSendAddr];
	}

	if(!data.bSign) 
	{
		strShowData = _T("���͵�ַ");
		strShowData += strAssetSendAddr;
		strShowData += _T("δ����");
		UiFun::MessageBoxEx(strShowData.c_str(),  _T("��ʾ"),MFB_OK|MFB_TIP );
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
	//strCommand = CSoyPayHelp::getInstance()->CreateContractTx( m_appid,strAssetSendAddr,strContractData,0,(INT64)REAL_MONEY(0.01),0);			//Դ��ַ
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
		strTip = strprintf("%s\n%s" , _T("ת�Ʋ����ʲ��ɹ�!"),root["hash"].asCString() ) ;

		//���뵽���ݿ�
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
		strTip = _T("ת�Ʋ����ʲ�ʧ��") ;
	}

	UiFun::MessageBoxEx(strTip.c_str(),_T("��ʾ") ,MFB_OK|MFB_TIP );
}


void CZCOutDlg::ActAssetAddr(string &strAssetAddr)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if (!theApp.m_bIsSyncBlock)
	{
		
		UiFun::MessageBoxEx(_T("ͬ��δ���,���ܷ��ͼ����"),_T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}
	
	CStarSharesclientDlg* pPopDlg = (CStarSharesclientDlg*)AfxGetApp()->m_pMainWnd;

	CString StrShow;

		if(!pPopDlg->m_pSendDlg->m_mapAddrInfo.count(strAssetAddr))
			{
					TRACE("ERROR");
				StrShow.Format(_T("��ַ������"));
				
				UiFun::MessageBoxEx(StrShow ,_T("��ʾ") ,MFB_OK|MFB_TIP );
				return;
		   }
		uistruct::LISTADDR_t te =  pPopDlg->m_pSendDlg->m_mapAddrInfo[strAssetAddr];
		//uistruct::LISTADDR_t * pAddrItem = (uistruct::LISTADDR_t*)m_listCtrl.GetItemData(nRow) ;
		if (te.fMoney <=0)
		{
			StrShow.Format(_T("�˻����Ϊ��,���ܼ���!"));
			
			UiFun::MessageBoxEx(StrShow ,_T("��ʾ") ,MFB_OK|MFB_TIP );
			return;
		}
		if(te.bSign) 
		{
			StrShow.Format(_T("�˻��Ѽ���!"));
			
			UiFun::MessageBoxEx(StrShow, _T("��ʾ") ,MFB_OK|MFB_TIP );
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
				m_lstOutDetail.SetItemText(iRow , ++nSubIdx , "(ƽ��)ȷ����" );
			}
			if(pListInfo[i].iState == 1)
			{
				m_lstOutDetail.SetItemText(iRow, ++nSubIdx, "(ת��)ȷ����");
			}

		}
		if(pListInfo[i].confirmedHeight > 0)
		{
			if(pListInfo[i].iState == 3)
			{
				m_lstOutDetail.SetItemText(iRow , ++nSubIdx , "(ƽ��)���ͳɹ�" ) ;
			}
			if(pListInfo[i].iState == 1)
			{
				m_lstOutDetail.SetItemText(iRow, ++nSubIdx, "(ת��)���ͳɹ�");
			}
		}

		strShowData = strprintf("%.3f",(pListInfo[i].popNum)*1.0/COIN);
		m_lstOutDetail.SetItemText(iRow , ++nSubIdx , strShowData.c_str());

		m_lstOutDetail.CreateItemButton(iRow, ++nSubIdx, this->GetSafeHwnd(), _T("�����˺�"));

		iRow++;
		index++;
	}
}