// RGZCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "RGZCDlg.h"
#include "afxdialogex.h"
#include "StarSharesclientDlg.h"


// CRGZCDlg �Ի���

IMPLEMENT_DYNAMIC(CRGZCDlg, CDialogEx)

CRGZCDlg::CRGZCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRGZCDlg::IDD, pParent)
{
	m_pBmp = NULL;

	m_pRollDlg = NULL;
}

CRGZCDlg::~CRGZCDlg()
{
	if( NULL != m_pBmp ) {
		::DeleteObject( m_pBmp ) ;
		m_pBmp = NULL ;
	}

	if(NULL != m_pRollDlg)
	{
		delete m_pRollDlg;
	}
}

void CRGZCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOUGHT_ASSET, m_lstBoughtAsset);
}


BEGIN_MESSAGE_MAP(CRGZCDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(MSG_USER_TRANSRECORD_UI , &CRGZCDlg::OnShowListCtrl )
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRGZCDlg ��Ϣ�������


BOOL CRGZCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBkBmpNid(IDB_BITMAP_RGZC_BLACK);

	struct LISTCol {
		CString		name ;
		UINT		size ;
	} listcol[6]  = {
		{"�ʲ�����" ,      150},
		{"���з�" ,      150},
		{"Ŀǰ�ۼ��ʽ�" ,      120}, 
		{"�Ϲ�����" ,       90},
		{"�Ϲ�״̬", 80},
		{"����֧��(STS)", 113}
	};
	m_lstBoughtAsset.SetBkColor(RGB(255,255,255));       
	m_lstBoughtAsset.SetRowHeigt(30);               
	m_lstBoughtAsset.SetHeaderHeight(1.5);         
	m_lstBoughtAsset.SetHeaderFontHW(15,0);
	m_lstBoughtAsset.SetHeaderBKColor(87, 101, 112, 0); 
	m_lstBoughtAsset.SetHeaderTextColor(RGB(255,255,255)); 
	m_lstBoughtAsset.SetTextColor(RGB(0,0,0));  
	for( int i = 0 ; i <6 ; i++  ) {
		m_lstBoughtAsset.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
	}
	m_lstBoughtAsset.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP );

	OninitializeList();

	theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_TRANSRECORD_UI ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CRGZCDlg::SetBkBmpNid( UINT nBitmapIn ) 
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


BOOL CRGZCDlg::OnEraseBkgnd(CDC* pDC)
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

	m_lstBoughtAsset.ShowScrollBar(SB_HORZ, FALSE);

	return 1;
}


int CRGZCDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect ;
	GetParent()->GetClientRect( rect );
	if( NULL == m_pRollDlg ){
		m_pRollDlg = new CRollDlg ;
		m_pRollDlg->Create(CRollDlg::IDD, this);
		m_pRollDlg->ShowWindow(SW_HIDE);

		m_pRollDlg->SetWindowPos(NULL, 27, 30, 724, 208, SWP_SHOWWINDOW);
	}

	SetTimer(0x10, 60000, NULL);

	return 0;
}


void CRGZCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(NULL != GetSafeHwnd()){
		CRect rect;
		this->GetWindowRect(rect);

		CWnd *pst = NULL;
		pst = GetDlgItem(IDC_LIST_BOUGHT_ASSET);
		if(NULL != pst)
		{
			pst->SetWindowPos(NULL, 32, 290, 716, 126, SWP_SHOWWINDOW);
		}
	}
}

LRESULT CRGZCDlg::OnShowListCtrl(  WPARAM wParam, LPARAM lParam )
{
	int type = (int)wParam;
	switch(type)
	{
	case WM_INSERT:
		{
			m_lstBoughtAsset.DeleteAllItems();
			OninitializeList();

		}
		break;
	case WM_REMOVETX:
		{
			m_lstBoughtAsset.DeleteAllItems();
			OninitializeList();

		}
		break;
	default:
		break;
	}
	return 0;
}

void  CRGZCDlg::OninitializeList()
{
	ShowComboxCotent();
}

void CRGZCDlg::ShowComboxCotent()
{
	uistruct::BOUGHTASSETLIST bougthAssetList;
	m_AllAssetList.clear();

	string strCondition = "1 = 1 order by ID ASC";
	theApp.m_SqliteDeal.GetAssetList(strCondition, (&m_AllAssetList));

	int operate = 0;
	string condtion = "1=1 order by confirmed_time DESC";
	uistruct::TRANSRECORDLIST pListInfo;

	string strCond0 =  condtion;

	string tempConditon = "confirm_height=0 and state != 1 ";
	tempConditon +=strCond0;
	strCond0 = tempConditon;

	theApp.m_SqliteDeal.GetTransactionList(strCond0, &pListInfo); 

	uistruct::TRANSRECORDLIST pListInfo1;
	string strCond = " confirm_height!=0 and state != 2 "+ condtion;

	theApp.m_SqliteDeal.GetTransactionList(strCond, &pListInfo1); 

	pListInfo.insert(pListInfo.end(),pListInfo1.begin(),pListInfo1.end());

	uistruct::ASSETLIST::const_iterator const_it;
	for(const_it = m_AllAssetList.begin(); const_it != m_AllAssetList.end(); const_it++)
	{
		uistruct::BOUGHTASSET boughtAsset;

		string strCond;
		string strShowData;
		if(const_it->AssetAddr != "")
		{
			Json::Value root;

			strCond = strprintf("%s %s", "validateaddress", const_it->AssetAddr.c_str());
			if(!CSoyPayHelp::getInstance()->SendRpc(strCond,root))
			{
				TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
				//return;
				continue;
			}

			strShowData = root["ret"].toStyledString();

			if( 0 ==  strncmp(strShowData.c_str(), "false", strlen("false")))
			{
				TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
				//return;
				continue;
			}
		
			strCond = strprintf( "des_addr = '%s' and state != 2",const_it->AssetAddr.c_str());
			double dmoney = theApp.m_SqliteDeal.GetTableItemSum(_T("t_transaction"), _T("money"), strCond);

			if(dmoney > 0 )
			{
				boughtAsset.AssetID = const_it->AssetID;
				boughtAsset.AssetName = const_it->AssetName;
				boughtAsset.AssetIssuer = const_it->AssetIssuer;
				boughtAsset.CurAmount = const_it->CurAmount;
				boughtAsset.BProgress = atoi(const_it->buyProgress.c_str());
				boughtAsset.iState = const_it->status;
				boughtAsset.bResult = const_it->bResult;
				boughtAsset.SupportAmount = dmoney;

				bougthAssetList.push_back(boughtAsset);
			}
		}
	}

	OnShowListCtrl(bougthAssetList);
}

void CRGZCDlg::OnShowListCtrl(uistruct::BOUGHTASSETLIST pListInfo){

	m_lstBoughtAsset.DeleteAllItems();
	if (pListInfo.size() == 0)
	{
		return;
	}

	m_bougthAssetList.clear();
	m_bougthAssetList.insert(m_bougthAssetList.begin(),pListInfo.begin(),pListInfo.end());

	int nSubIdx = 0 , i = 0 ;
	string strShowData = "";
	std::vector<uistruct::BOUGHTASSET_t>::const_iterator const_it;
	for ( const_it = pListInfo.begin() ; const_it != pListInfo.end() ; const_it++ ) {

		nSubIdx = 0;

		m_lstBoughtAsset.InsertItem(i, const_it->AssetName.c_str());				 //�ʲ�����
		m_lstBoughtAsset.SetItemText(i , ++nSubIdx ,  const_it->AssetIssuer.c_str() );   //���з�
		strShowData= strprintf("%.3f" , const_it->CurAmount ) ;
		m_lstBoughtAsset.SetItemText(i , ++nSubIdx , strShowData.c_str() );   //��ǰ�ۼ��ʽ�

		strShowData = strprintf("%d", const_it->BProgress);
		m_lstBoughtAsset.SetItemText(i, ++nSubIdx, strShowData.c_str());

		if( 1 == const_it->iState)
		{
			m_lstBoughtAsset.SetItemText(i, ++nSubIdx, _T("����"));
		}else if(2 == const_it->iState)
		{
			m_lstBoughtAsset.SetItemText(i, ++nSubIdx, _T("�ѷ���"));
		}else if(3 == const_it->iState)
		{
			m_lstBoughtAsset.SetItemText(i, ++nSubIdx, _T("�ڳ���"));
		}else if(4 == const_it->iState)
		{
			m_lstBoughtAsset.SetItemText(i, ++nSubIdx, _T("��ͣ"));
		}else if(5 == const_it->iState)
		{
			if(const_it->bResult)
			{
				m_lstBoughtAsset.SetItemText(i, ++nSubIdx, _T("�Ϲ��ɹ�"));
			}else
			{
				m_lstBoughtAsset.SetItemText(i, ++nSubIdx, _T("�Ϲ�ʧ��"));
			}
		}
																					//�Ϲ�״̬
		strShowData= strprintf("%.3f" , const_it->SupportAmount ) ;
		m_lstBoughtAsset.SetItemText(i , ++nSubIdx , strShowData.c_str() );  //֧�ֽ��

		i++;
	}
}

void CRGZCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 0x10:
		{
			if(0 == m_pRollDlg->m_VecAssetList.size())
			{
				return;
			}

			m_pRollDlg->RefreshCurPage();

			CStarSharesclientDlg* pPopDlg = (CStarSharesclientDlg*)AfxGetApp()->m_pMainWnd;
			if(NULL != pPopDlg)
			{
				pPopDlg->LoadAllAsset();
			}

			OninitializeList();

			m_pRollDlg->ClearControl();
			m_pRollDlg->LayoutDlg(m_pRollDlg->m_nCurAssetIndex);
		}
		break;
	default:
		break;
	}


	CDialogEx::OnTimer(nIDEvent);
}
