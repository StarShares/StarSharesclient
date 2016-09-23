// WDZCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "WDZCDlg.h"
#include "afxdialogex.h"
#include "AppsDlg.h"
#include "CApplication.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "StarSharesclientDlg.h"
#include "RollDlg.h"


// CWDZCDlg 对话框

IMPLEMENT_DYNAMIC(CWDZCDlg, CDialogEx)

int CWDZCDlg::m_coulum = 0;
int CWDZCDlg::m_index = 0;

CWDZCDlg::CWDZCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWDZCDlg::IDD, pParent)
{
	m_pBmp = NULL ;
}

CWDZCDlg::~CWDZCDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}

void CWDZCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ZC_IN, m_sBtnZCIn);
	DDX_Control(pDX, IDC_BUT_EXECL_EXPORT, m_sBtnExportExcel);
	DDX_Control(pDX, IDC_LIST_WDZC, m_lstWDZC);

	DDX_Control(pDX, IDC_COMBO_ASSETLIST, m_ycomboAsset);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_sbtnSearch);
}


BEGIN_MESSAGE_MAP(CWDZCDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_ZC_IN, &CWDZCDlg::OnBnClickedBtnZcIn)
	ON_MESSAGE( WM_BN_CLICK, OnOutAsset)
	ON_BN_CLICKED(IDC_BUT_EXECL_EXPORT, &CWDZCDlg::OnBnClickedButExeclExport)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CWDZCDlg::OnBnClickedBtnSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_ASSETLIST, &CWDZCDlg::OnCbnSelchangeComboAssetlist)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CWDZCDlg 消息处理程序

void CWDZCDlg::SetBkBmpNid( UINT nBitmapIn ) 
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


BOOL CWDZCDlg::OnEraseBkgnd(CDC* pDC)
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


BOOL CWDZCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//SetBkBmpNid(IDB_BITMAP_WDZC_BK);

	CRect rect;
	GetDlgItem(IDC_LIST_WDZC)->GetWindowRect(&rect);

	m_lstWDZC.MoveWindow(30 , 100, 740, 320, SWP_SHOWWINDOW);

	int i = rect.Width();

	struct LISTCol {
		CString		name ;
		UINT		size ;
	} listcol[6]  = {
		{"序号" ,      100},
		{"资产名称" ,      150}, 
		{"发行方" ,  150},
		{"红人秀数量", 150},
		{"解冻高度",90},
		{"转出", 63}
	};
	m_lstWDZC.SetBkColor(RGB(255, 255,255));       
	m_lstWDZC.SetRowHeigt(30);               
	m_lstWDZC.SetHeaderHeight(1.5);         
	m_lstWDZC.SetHeaderFontHW(15,0);
	m_lstWDZC.SetHeaderBKColor(87, 101, 112, 0); 
	m_lstWDZC.SetHeaderTextColor(RGB(255,255,255)); 
	m_lstWDZC.SetTextColor(RGB(0,0,0));  
	for( int i = 0 ; i <6 ; i++  ) {
		m_lstWDZC.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
	}
	m_lstWDZC.SetExtendedStyle(LVS_EX_FULLROWSELECT |  LVS_EX_HEADERDRAGDROP );


	m_sBtnZCIn.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 0) , IDB_BITMAP_BUT1 , RGB(255, 255, 0) );
	m_sBtnZCIn.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_sBtnZCIn.SetWindowText("资产转入") ;
	m_sBtnZCIn.SetFontEx(-14 , _T("微软雅黑"));
	m_sBtnZCIn.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
	m_sBtnZCIn.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_sBtnZCIn.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255,255,255));
	m_sBtnZCIn.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
	m_sBtnZCIn.SizeToContent();

	m_sBtnExportExcel.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 0) , IDB_BITMAP_BUT1 , RGB(255, 255, 0) );
	m_sBtnExportExcel.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_sBtnExportExcel.SetWindowText("导出excel") ;
	m_sBtnExportExcel.SetFontEx(-14 , _T("微软雅黑"));
	m_sBtnExportExcel.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
	m_sBtnExportExcel.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_sBtnExportExcel.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255,255,255));
	m_sBtnExportExcel.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
	m_sBtnExportExcel.SizeToContent();
	
	m_sbtnSearch.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 0) , IDB_BITMAP_BUT1 , RGB(255, 255, 0) );
	m_sbtnSearch.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_sbtnSearch.SetWindowText("查询") ;
	m_sbtnSearch.SetFontEx(-14 , _T("微软雅黑"));
	m_sbtnSearch.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
	m_sbtnSearch.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
	m_sbtnSearch.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255,255,255));
	m_sbtnSearch.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
	m_sbtnSearch.SizeToContent();

	m_ycomboAsset.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_ycomboAsset.SetEdtNewFont(100);
	m_ycomboAsset.SetListNewFont(100);
	m_ycomboAsset.SetEdtTextColor(RGB(121, 122, 122));
	m_ycomboAsset.SetListTextColor(RGB(118, 192, 50));
	m_ycomboAsset.SetItemHeight(1, 30);
	m_ycomboAsset.AotuAdjustDroppedWidth();
	m_ycomboAsset.SetEdtFrameColor(RGB(238,238,238));
	m_ycomboAsset.SetFrameStyle(CYComBox::ONLYONE);

	InitCombox();

	SetTimer(0x10, 30000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

string CWDZCDlg::GetAppID(string AppName)
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

LRESULT CWDZCDlg::OnOutAsset(WPARAM wParam, LPARAM lParam)
{
	int nItem = (int)wParam;
	int nSubItem = (int)lParam;
	nSubItem--;

#ifdef USE_TOPINDEX_BUTTON
	int iTopIndex = m_lstWDZC.GetTopIndex();
	nItem = iTopIndex + nItem;
#endif

	CString szItemText = m_lstWDZC.GetItemText( nItem, nSubItem );

	CAppsDlg *pAppsDlg = (CAppsDlg *)GetParent();

	pAppsDlg->m_pZCOutBar->m_strCurAsset = m_lstWDZC.GetItemText(nItem, 1);
	pAppsDlg->m_pZCOutBar->m_ycomAsset.SetWindowText(pAppsDlg->m_pZCOutBar->m_strCurAsset.c_str());
	pAppsDlg->ActiveDlg(CZCOutDlg::IDD);
	
	return 0;
}


void CWDZCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if(NULL != GetSafeHwnd())
	{
		CRect rc;
		GetClientRect(rc);

		int curwith = 0;

		CWnd *pst = GetDlgItem(IDC_BTN_ZC_IN);
		if(NULL != pst){
			CRect rect;
			pst->GetClientRect(rect);
			pst->SetWindowPos( NULL ,30 ,36  , rect.Width(), rect.Height(),SWP_SHOWWINDOW ); 
			curwith += rect.Width() + 20 + 30;
		}

		pst = GetDlgItem(IDC_BUT_EXECL_EXPORT);
		if(NULL != pst)
		{
			CRect rect;
			pst->GetClientRect(rect);
			pst->SetWindowPos( NULL ,curwith , 36, rect.Width(), rect.Height(),SWP_SHOWWINDOW ); 

		}

		pst = GetDlgItem(IDC_LIST_WDZC);
		if(NULL != pst)
		{
			CRect rect;
			pst->GetClientRect(rect);
			pst->SetWindowPos( NULL ,30 , 100, 720, 320,SWP_SHOWWINDOW ); 
		}

		pst = GetDlgItem(IDC_COMBO_ASSETLIST);
		if(NULL != pst)
		{
			CRect rect;
			pst->GetClientRect(rect);
			pst->SetWindowPos( NULL ,(rc.Width()/100)*60 ,42, rect.Width(), rect.Height(),SWP_SHOWWINDOW ); 
		}

		pst = GetDlgItem(IDC_BTN_SEARCH);
		if(NULL != pst)
		{
			CRect rect;
			pst->GetClientRect(rect);
			pst->SetWindowPos( NULL ,(rc.Width()/100)*83 ,36, rect.Width(), rect.Height(),SWP_SHOWWINDOW ); 
		}
	}
}


void CWDZCDlg::OnBnClickedBtnZcIn()
{
	// TODO: 在此添加控件通知处理程序代码

	CAppsDlg *pAppsDlg = (CAppsDlg *)GetParent();

	
	pAppsDlg->ActiveDlg(CZCInDlg::IDD);
}


void CWDZCDlg::OnBnClickedButExeclExport()
{
	// TODO: 在此添加控件通知处理程序代码
	int count = m_lstWDZC.GetItemCount();
	if (count == 0)
	{
		UiFun::MessageBoxEx(_T("没有记录可以导出！") ,_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	CFileDialog dlg(FALSE,NULL,_T("接收记录"),OFN_HIDEREADONLY|OFN_FILEMUSTEXIST ,"文件 (*.xls)|*.xls||");
	if (IDOK != dlg.DoModal())
	{
		return;
	}

	CString strFile = dlg.GetPathName();
	if (!((CStarSharesclientDlg*)(theApp.m_pMainWnd))->GetFileName(strFile,_T(".xls")))
	{
		return;
	}

	struct LISTCol {
		string		name ;
		UINT		size ;
	} listheadr[5]  = {
		{_T("序号") ,      50},
		{_T("资产名称") ,    30},
		{_T("发行方") ,    40},
		{_T("红人秀数量") ,    10},
		{_T("解冻高度") ,  40}
	};

	COleVariant

		covTrue((short)TRUE),

		covFalse((short)FALSE),

		covOptional((long)DISP_E_PARAMNOTFOUND,   VT_ERROR);

	CApplication   app;

	CWorkbooks   books;

	CWorkbook   book;

	CWorksheets   sheets;

	CWorksheet   sheet;

	CRange   range;

	CFont0   font;

	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		UiFun::MessageBoxEx(_T("可能是没有装office 导致创建失败！") , _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	//Get   a   new   workbook.

	books = app.get_Workbooks();

	book = books.Add(covOptional);

	sheets = book.get_Worksheets();

	sheet = sheets.get_Item(COleVariant((short)1));

	int   iCol;

	int   m_cols   =   5;

	int   m_rows = count;

	HDITEM   hdi;

	TCHAR     lpBuffer[256];

	bool       fFound   =   false;

	hdi.mask   =   HDI_TEXT;

	hdi.pszText   =   lpBuffer;

	hdi.cchTextMax   =   256;

	CString   colname;

	CString strTemp;

	for(iCol=0;   iCol <m_cols;   iCol++)//将列表的标题头写入EXCEL
	{
		UiFun::GetCellName(1 ,iCol + 1, colname);

		range   =   sheet.get_Range(COleVariant(colname),COleVariant(colname));

		//pmyHeaderCtrl-> GetItem(iCol,   &hdi);

		range.put_Value2(COleVariant(listheadr[iCol].name.c_str()));

		int   nWidth   = listheadr[iCol].size;  //m_listCtrl.GetColumnWidth(iCol)/6;

		//得到第iCol+1列  

		range.AttachDispatch(range.get_Item(_variant_t((long)(iCol+1)),vtMissing).pdispVal,true);  

		//设置列宽 

		range.put_ColumnWidth(_variant_t((long)nWidth));

	}

	range   =   sheet.get_Range(COleVariant( _T("A1 ")),   COleVariant(colname));

	range.put_RowHeight(_variant_t((long)50));//设置行的高度

	font = range.get_Font();

	font.put_Bold(covTrue);

	range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108



	COleSafeArray   saRet;

	DWORD   numElements[]={m_rows,m_cols};       //5x2   element   array

	saRet.Create(VT_BSTR,   2,   numElements);

	range   =   sheet.get_Range(COleVariant( _T("A2 ")),covOptional);

	range = range.get_Resize(COleVariant((short)m_rows),COleVariant((short)m_cols));

	long   index[2];

	range   =   sheet.get_Range(COleVariant( _T("A2 ")),covOptional);

	range   =   range.get_Resize(COleVariant((short)m_rows),COleVariant((short)m_cols));

	for(int i = 0; i < count; i++)
	{
		CString strNo = m_lstWDZC.GetItemText(i, 0);
		BSTR   bstr   =   strNo.AllocSysString();
		index[0] = i;
		index[1] = 0;
		saRet.PutElement(index,bstr);

		SysFreeString(bstr);

		CString strLabel = m_lstWDZC.GetItemText(i, 1);
		bstr   =   strLabel.AllocSysString();
		index[0] = i;
		index[1] = 1;
		saRet.PutElement(index,bstr);

		SysFreeString(bstr);

		CString strAddress = m_lstWDZC.GetItemText(i, 2);
		bstr   =   strAddress.AllocSysString();
		index[0] = i;
		index[1] = 2;
		saRet.PutElement(index,bstr);

		SysFreeString(bstr);

		CString strActive = m_lstWDZC.GetItemText(i, 3);
		bstr   =   strActive.AllocSysString();
		index[0] = i;
		index[1] = 3;
		saRet.PutElement(index,bstr);

		SysFreeString(bstr);
		CString strMoney = m_lstWDZC.GetItemText(i, 4);
		bstr   =   strMoney.AllocSysString();
		index[0] = i;
		index[1] = 4;
		saRet.PutElement(index,bstr);

		SysFreeString(bstr);
	}



	range.put_Value2(COleVariant(saRet));


	saRet.Detach();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	book.SaveCopyAs(COleVariant(strFile));

	//       cellinterior.ReleaseDispatch();

	book.put_Saved(true);

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();

	//book.ReleaseDispatch();  

	//books.ReleaseDispatch();  
	book.Close (covOptional, covOptional,covOptional);// 关闭Workbook对象
	books.Close(); 
	app.Quit();

	app.ReleaseDispatch();

}

void CWDZCDlg::InitCombox()
{
	m_MapMyAssetList.clear();
	while(m_ycomboAsset.GetCount() != 0)
	{
		m_ycomboAsset.DeleteString(0);
	}

	string strCondition = "Status = 5 and Result = 1";
	theApp.m_SqliteDeal.GetAssetList(strCondition, (&m_MapMyAssetList));
	map<string,LISTASSET_t>::iterator it= m_MapMyAssetList.begin();

	m_ycomboAsset.InsertString(0, _T("全部"));

	int i = 1;
	for(;it != m_MapMyAssetList.end();it++)
	{
		LISTASSET_t data=it->second;
		CString temp;
		temp.Format(_T("%s"),data.AssetName.c_str());	
		m_ycomboAsset.InsertString(i, temp);

		i++;
	}
}


void CWDZCDlg::OnBnClickedBtnSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	m_lstWDZC.DeleteAllItems();
	m_lstWDZC.release();

	m_coulum = 0;
	m_index = 0;

	CString strAssetName;
	GetDlgItem(IDC_COMBO_ASSETLIST)->GetWindowText(strAssetName);
	if(strAssetName == "")
	{
		UiFun::MessageBoxEx(_T("请输入有效的资产名称!"),_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	map<string,LISTASSET_t>::const_iterator const_it;

	if(0 == strcmp(strAssetName, _T("全部")))
	{
		for(const_it = m_MapMyAssetList.begin(); const_it != m_MapMyAssetList.end(); const_it++)
		{
			m_appid = const_it->first.c_str();

			OnShowListCtrol(m_appid);
		}

		return;
	}
	
	for(const_it = m_MapMyAssetList.begin(); const_it != m_MapMyAssetList.end(); const_it++)
	{
		if(0 == strcmp(const_it->second.AssetName.c_str(), strAssetName))
		{
			string appId = const_it->first.c_str();

			m_appid = appId;
			break;
		}
	}
	
	OnShowListCtrol(m_appid);
}

void CWDZCDlg::OnShowListCtrol(string appId)
{
	string strCommand,strShowData ="";
	Json::Reader reader;
	Json::Value root;
	strCommand = strprintf("%s %s", "getassets", m_MapMyAssetList[m_appid].AssetID);
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,strShowData))
	{
		TRACE("getassets rpccmd error\r\n");
		return;
	}
	if (!reader.parse(strShowData, root)) 
		return ;

	INT64 total = root["TotalAssets"].asInt64();

	Json::Value valuearray = root["Lists"];
	Json::Value value;

	if(0 == valuearray.size())
	{
		//UiFun::MessageBoxEx(_T("该资产账户为0"),_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	INT64 dFreeMoney = 0;
	INT64 FreezedFund = 0;
	int iCurIndex = 0;
	for(int i = 0; i < valuearray.size(); i++)
	{
		dFreeMoney += valuearray[i]["FreeValues"].asInt64();
	}

	double money = 0.0;
	
	if (dFreeMoney != 0)
	{
		money = (dFreeMoney*1.0/COIN);
		
		string strOrder ="";
		int nSubIdx = 0;
		strOrder= strprintf("%d", m_coulum + 1);
		m_lstWDZC.InsertItem(m_coulum,strOrder.c_str());

		m_lstWDZC.SetItemText(m_coulum, 1, m_MapMyAssetList[m_appid].AssetName.c_str());
		m_lstWDZC.SetItemText(m_coulum, 2, m_MapMyAssetList[m_appid].AssetIssuer.c_str());
		strShowData = strprintf("%.8f",money);
		m_lstWDZC.SetItemText( m_coulum , 3, strShowData.c_str()) ;
		strOrder= "0";
		m_lstWDZC.SetItemText(m_coulum ,4 , strOrder.c_str() ) ;

		m_lstWDZC.CreateItemButton(m_coulum, 5, this->GetSafeHwnd(), "资产转出");
		m_coulum++;
		m_index++;
	}

	for(int i = 0; i < valuearray.size(); i++)
	{
		if(valuearray[i]["FreezedFund"].asInt64() !=0)
		{
			strCommand =strprintf("%s %s %s","getappaccinfo" , m_MapMyAssetList[m_appid].AssetID ,valuearray[i]["Address"].asString().c_str());
			if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
			{
				TRACE("OnShowListCtrol rpccmd getappaccinfo error");
				return;
			}
			strShowData = root.toStyledString();

			Json::Value valuearray = root["vFreezedFund"]; 
			for(unsigned int i =0;i<valuearray.size();i++)
			{
				int nSubIdx = 0;
				string strOrder ="";
				strOrder= strprintf("%d", m_index+1);
				m_lstWDZC.InsertItem(m_coulum,strOrder.c_str());

				m_lstWDZC.SetItemText(m_coulum, 1, m_MapMyAssetList[m_appid].AssetName.c_str());
				m_lstWDZC.SetItemText(m_coulum, 2, m_MapMyAssetList[m_appid].AssetIssuer.c_str());

				FreezedFund = valuearray[i]["value"].asInt64() ;
				money = (FreezedFund*1.0/COIN);
				strShowData = strprintf("%.8f",money);
				m_lstWDZC.SetItemText( m_coulum , 3, strShowData.c_str()) ;

				strShowData =strprintf("%d" , valuearray[i]["nHeight"].asInt()) ;
				m_lstWDZC.SetItemText(m_coulum , 4 , strShowData.c_str() ) ;
				m_lstWDZC.SetItemText(m_coulum, 5, "无法转出");

				m_coulum++;
				m_index++;
			}
		}
	}
}


void CWDZCDlg::OnCbnSelchangeComboAssetlist()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel =m_ycomboAsset.GetCurSel();
	if (sel != -1)
	{
		CString curText =_T("");
		m_ycomboAsset.GetLBText(sel,curText);
		string appname =strprintf("%s",curText);
		//m_appid = GetAppID(appname);
	}
}


void CWDZCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 0x10:
		{
			InitCombox();
			break;
		}
	default:
		break;
	}
	

	CDialogEx::OnTimer(nIDEvent);
}
