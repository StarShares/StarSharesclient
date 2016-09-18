// SetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "SetDlg.h"
#include "afxdialogex.h"
#include "StarSharesclientDlg.h"
#include "EncryptWallet.h"
#include "ChangPassWord.h"


// CSetDlg

IMPLEMENT_DYNAMIC(CSetDlg, CDialogBar)

CSetDlg::CSetDlg()
{
	m_pBmp = NULL ;
}

CSetDlg::~CSetDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_RPC , m_rBtnRpc);
	DDX_Control(pDX, IDC_BUTTON_QBJM , m_rBtnQbjm);
	DDX_Control(pDX, IDC_BUTTON_XGMM , m_rBtnXgmm);
	DDX_Control(pDX, IDC_BUTTON_QBSD , m_rBtnQbsd);
	DDX_Control(pDX, IDC_BUTTON_QBBF , m_rBtnQbbf);
	DDX_Control(pDX, IDC_BUTTON_DCSY , m_rBtnDcsy);
	DDX_Control(pDX, IDC_BUTTON_DRSY , m_rBtnDrsy);
	DDX_Control(pDX, IDC_BUTTON_HFMRSZ , m_rBtnFfmrsz);
	DDX_Control(pDX, IDC_BUTTON_GBTS , m_rBtnGbts);
}

BEGIN_MESSAGE_MAP(CSetDlg, CDialogBar)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_RPC, &CSetDlg::OnBnClickedButtonPrc)
	ON_BN_CLICKED(IDC_BUTTON_QBJM, &CSetDlg::OnBnClickedButtonQbjm)
	ON_BN_CLICKED(IDC_BUTTON_XGMM, &CSetDlg::OnBnClickedButtonXgmm)
	ON_BN_CLICKED(IDC_BUTTON_QBSD, &CSetDlg::OnBnClickedButtonQbsd)
	ON_BN_CLICKED(IDC_BUTTON_QBBF, &CSetDlg::OnBnClickedButtonQbbf)
	ON_BN_CLICKED(IDC_BUTTON_DCSY, &CSetDlg::OnBnClickedButtonDcsy)
	ON_BN_CLICKED(IDC_BUTTON_DRSY, &CSetDlg::OnBnClickedButtonDrsy)
	ON_BN_CLICKED(IDC_BUTTON_HFMRSZ, &CSetDlg::OnBnClickedButtonHfmrsz)
	ON_BN_CLICKED(IDC_BUTTON_GBTS, &CSetDlg::OnBnClickedButtonGbts)
END_MESSAGE_MAP()



// CSetDlg 消息处理程序
void CSetDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CSetDlg::OnEraseBkgnd(CDC* pDC)
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


int CSetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetBkBmpNid( IDB_BITMAP_BG ) ;

	return 0;
}


void CSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != GetSafeHwnd() ) {
		CRect rc  ;
		GetClientRect( rc ) ;

		CWnd *pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_RPC);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72 , 80 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_QBJM);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72+167*1, 80 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_XGMM);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72+167*2, 80 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_QBSD);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72+167*3, 80 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_QBBF);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72+167*4, 80 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}

		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_DCSY);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72, 208+44*1 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_DRSY);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72+167*1, 208+44*1 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_HFMRSZ);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72+167*2, 208+44*1 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTON_GBTS);
		if ( NULL != pWnd ) {
			pWnd->SetWindowPos( NULL ,72+167*3, 208+44*1 , 100, 130  ,SWP_SHOWWINDOW ) ; 
		}
	}
}


BOOL CSetDlg::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类

	BOOL bRes = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if ( bRes ) {
		HCURSOR cur = ::LoadCursor(NULL, IDC_HAND);
		UpdateData(FALSE);
		m_rBtnRpc.SetBitmaps( IDB_BITMAP_SETRPC , RGB(255, 255, 0) , IDB_BITMAP_SETRPC_CLK , RGB(255, 255, 255) );
		m_rBtnRpc.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnRpc.SetWindowText("") ;
		m_rBtnRpc.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnRpc.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnRpc.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnRpc.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnRpc.SetCursor(cur);
		m_rBtnRpc.SizeToContent();

		m_rBtnQbjm.SetBitmaps( IDB_BITMAP_SETQB , RGB(255, 255, 0) , IDB_BITMAP_SETQB_CLK , RGB(255, 255, 255) );
		m_rBtnQbjm.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnQbjm.SetWindowText("") ;
		m_rBtnQbjm.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnQbjm.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnQbjm.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnQbjm.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnQbjm.SetCursor(cur);
		m_rBtnQbjm.SizeToContent();

		m_rBtnXgmm.SetBitmaps( IDB_BITMAP_SETPASS , RGB(255, 255, 0) , IDB_BITMAP_SETPASS_CLK , RGB(255, 255, 255) );
		m_rBtnXgmm.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnXgmm.SetWindowText("") ;
		m_rBtnXgmm.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnXgmm.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnXgmm.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnXgmm.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnXgmm.SetCursor(cur);
		m_rBtnXgmm.SizeToContent();

		m_rBtnQbsd.SetBitmaps( IDB_BITMAP_SETQBSD , RGB(255, 255, 0) , IDB_BITMAP_SETQBSD_CLK , RGB(255, 255, 255) );
		m_rBtnQbsd.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnQbsd.SetWindowText("") ;
		m_rBtnQbsd.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnQbsd.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnQbsd.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnQbsd.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnQbsd.SetCursor(cur);
		m_rBtnQbsd.SizeToContent();

		m_rBtnQbbf.SetBitmaps( IDB_BITMAP_SETQBBF , RGB(255, 255, 0) , IDB_BITMAP_SETQBBF_CLK , RGB(255, 255, 255) );
		m_rBtnQbbf.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnQbbf.SetWindowText("") ;
		m_rBtnQbbf.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnQbbf.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnQbbf.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnQbbf.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnQbbf.SetCursor(cur);
		m_rBtnQbbf.SizeToContent();

		m_rBtnDcsy.SetBitmaps( IDB_BITMAP_SETDCSY , RGB(255, 255, 0) , IDB_BITMAP_SETDCSY_CLK , RGB(255, 255, 255) );
		m_rBtnDcsy.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnDcsy.SetWindowText("") ;
		m_rBtnDcsy.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnDcsy.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnDcsy.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnDcsy.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnDcsy.SetCursor(cur);
		m_rBtnDcsy.SizeToContent();

		m_rBtnDrsy.SetBitmaps( IDB_BITMAP_SETDRSY , RGB(255, 255, 0) , IDB_BITMAP_SETDRSY_CLK , RGB(255, 255, 255) );
		m_rBtnDrsy.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnDrsy.SetWindowText("") ;
		m_rBtnDrsy.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnDrsy.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnDrsy.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnDrsy.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnDrsy.SetCursor(cur);
		m_rBtnDrsy.SizeToContent();


		m_rBtnFfmrsz.SetBitmaps( IDB_BITMAP_SETMRSZ , RGB(255, 255, 0) , IDB_BITMAP_SETMRSZ_CLK , RGB(255, 255, 255) );
		m_rBtnFfmrsz.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnFfmrsz.SetWindowText("") ;
		m_rBtnFfmrsz.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnFfmrsz.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnFfmrsz.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnFfmrsz.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnFfmrsz.SetCursor(cur);
		m_rBtnFfmrsz.SizeToContent();

		m_rBtnGbts.SetBitmaps( IDB_BITMAP_SETGBTS , RGB(255, 255, 0) , IDB_BITMAP_SETGBTS_CLK , RGB(255, 255, 255) );
		m_rBtnGbts.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnGbts.SetWindowText("") ;
		m_rBtnGbts.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
		m_rBtnGbts.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnGbts.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
		m_rBtnGbts.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
		m_rBtnGbts.SetCursor(cur);
		m_rBtnGbts.SizeToContent();
	}
	return bRes ;
}


bool CSetDlg::GetFileName(CString &fileName,CString strexe )
{
	int spcace = fileName.Find(" ");
	if (spcace >=0)
	{
		UiFun::MessageBoxEx(_T("路径不能为空") , _T("提示") ,MFB_OK|MFB_TIP );
		return false;
	}
	int pos = fileName.Find(".",0);
	if (pos <0)
	{
		fileName.AppendFormat(strexe);
	}
	pos = fileName.Find(".",0);
	fileName = fileName.Left(pos);
	fileName.AppendFormat(strexe);
	if(PathFileExistsA(fileName)){
		CString strDisplay;
		strDisplay=_T("此文件已经存在是否要覆盖");
		if (IDOK == UiFun::MessageBoxEx(strDisplay , _T("提示")  , MFB_OKCANCEL|MFB_TIP ) )
		{
			return TRUE;
		}
	}

	return TRUE;
}


void CSetDlg::OnBnClickedButtonPrc()
{
	// TODO: 在此添加控件通知处理程序代码
	CStarSharesclientDlg *pDlg = (CStarSharesclientDlg*)AfxGetMainWnd();
	if(!pDlg) {
		return;
	}

	CRect rcWindow;
	pDlg->GetWindowRect(&rcWindow);
	if ( NULL != pDlg->m_pRPCDlg ){
		pDlg->m_pRPCDlg->MoveWindow(rcWindow.right,rcWindow.top,300,rcWindow.Height()-8);
		pDlg->m_pRPCDlg->ShowWindow(SW_SHOW);
	}
}


void CSetDlg::OnBnClickedButtonQbjm()
{
	// TODO: 在此添加控件通知处理程序代码

	if (theApp.m_bIsHaveLocked)
	{
		UiFun::MessageBoxEx(_T("已经加过密")  , _T("提示")  ,MFB_OK|MFB_TIP );
		return;
	}


	CEncryptWallet enwalletdlg;
	if (enwalletdlg.DoModal() ==IDOK)
	{
		return;
	}
}


void CSetDlg::OnBnClickedButtonXgmm()
{
	// TODO: 在此添加控件通知处理程序代码
	CChangPassWord changwalletdlg;
	if (changwalletdlg.DoModal() ==IDOK)
	{
		return;
	}
}


void CSetDlg::OnBnClickedButtonQbsd()
{
	// TODO: 在此添加控件通知处理程序代码

	if (!theApp.m_bIsHaveLocked)
	{
		UiFun::MessageBoxEx(_T("钱包没有加锁") , _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}

	string strCommand;
	strCommand = strprintf("%s",_T("walletlock"));

	Json::Value root;
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
	{
		TRACE("UpdateAddressData rpccmd listaddr error");
		return;
	}


	bool isEntryp = root["walletlock"].asBool();
	if (!isEntryp)
	{
		UiFun::MessageBoxEx(_T("钱包锁定失败")  , _T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
}


void CSetDlg::OnBnClickedButtonQbbf()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE,"dat","wallet",OFN_HIDEREADONLY|OFN_FILEMUSTEXIST ,_T("*.dat||"));
	if (IDOK == dlg.DoModal())
	{
		CString strPath = dlg.GetPathName();
		if (!GetFileName(strPath,_T(".dat")))
		{
			return;
		}

		//strPath.AppendFormat(_T(".dat"));
		string strCommand;
		strCommand = strprintf("%s %s",_T("backupwallet"),strPath);
		string strSendData;
		CSoyPayHelp::getInstance()->SendRpc(strCommand,strSendData);

		CString strShowData;
		strShowData.Format(_T("%s:%s"),_T("钱包备份成功"),strPath);
		UiFun::MessageBoxEx(strShowData, _T("提示") ,MFB_OK|MFB_TIP );
	}
}

void CSetDlg::AddImportWalletAndBookAddr(CString fileName)
{
	string fiename =strprintf("%s",fileName);
	string strFile = CJsonConfigHelp::getInstance()->GetConfigRootStr(fiename);
	if (strFile == _T(""))
	{
		return;
	}
	Json::Reader reader;  
	Json::Value root; 

	if (!reader.parse(strFile, root)) 
		return;
	/// 自己钱包地址保存  walletaddr
	Json::Value walletaddr; 
	map<string,uistruct::LISTADDR_t> pListInfo;
	theApp.m_SqliteDeal.GetWalletAddressList(_T(" 1=1 "), (&pListInfo));
	if (pListInfo.size() != 0)
	{
		Json::Value Array;
		Json::Value itemValue;
		map<string,uistruct::LISTADDR_t>::iterator item = pListInfo.begin();
		for (;item != pListInfo.end();item++)
		{
			if (item->second.Label.length() != 0)
			{
				itemValue["addr"]=item->second.address;
				itemValue["label"] = item->second.Label;
				itemValue["reg_id"] = item->second.RegID;
				itemValue["money"] = item->second.fMoney;
				itemValue["cold_dig"] = item->second.nColdDig;
				itemValue["sign"] = item->second.bSign;
				Array.append(itemValue);
			}
		}
		root["walletaddr"] = Array;
	}

	map<string,uistruct::ADDRBOOK_t> pAddrBookMap;
	theApp.m_SqliteDeal.GetAddressBookList(_T(" 1=1 "),(&pAddrBookMap));

	if (pAddrBookMap.size() != 0)
	{
		Json::Value Array;
		Json::Value itemValue;
		map<string,uistruct::ADDRBOOK_t>::iterator item = pAddrBookMap.begin();
		for (;item != pAddrBookMap.end();item++)
		{
			//if (item->second.label != _T(""))
			{
				itemValue["addr"]=item->second.address;
				itemValue["label"] = item->second.label;
				Array.append(itemValue);
			}
		}
		root["wbookaddr"] = Array;
	}

	/// 保存到文件
	CStdioFile  File;
	File.Open(fileName,CFile::modeWrite | CFile::modeCreate); 
	string strfile = root.toStyledString();
	File.WriteString(strfile.c_str());
	File.Close();

}


void CSetDlg::OnBnClickedButtonDcsy()
{
	// TODO: 在此添加控件通知处理程序代码
	if (theApp.IsLockWallet())
	{
		return ;
	}
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_FILEMUSTEXIST ,_T("*.STS||"));
	if (IDOK == dlg.DoModal())
	{
		CString strPath = dlg.GetPathName();
		if (!GetFileName(strPath,_T(".STS")))
		{
			return;
		}
		//strPath.AppendFormat(_T(".smc"));
		string strCommand;
		strCommand = strprintf("%s %s","dumpwallet",strPath);
		string strSendData;
		CSoyPayHelp::getInstance()->SendRpc(strCommand,strSendData);
		CString strShowData;
		strShowData.Format(_T("%s:%s"),_T("导出私钥成功"),strPath);
		AddImportWalletAndBookAddr(strPath);
		UiFun::MessageBoxEx(strShowData , _T("提示") ,MFB_OK|MFB_TIP );
	}
}


void CSetDlg::WriteExportWalletAndBookAddr(CString fileName)
{
	string fiename =strprintf("%s",fileName);
	string strFile = CJsonConfigHelp::getInstance()->GetConfigRootStr(fiename);
	if (strFile == _T(""))
	{
		return;
	}
	Json::Reader reader;  
	Json::Value root; 

	if (!reader.parse(strFile, root)) 
		return;

	int pos = strFile.find("walletaddr");
	if ( pos>=0)
	{
		Json::Value addrValue = root["walletaddr"]; 
		for(int i =0;i<(int)addrValue.size();i++){
			Json::Value obj = addrValue[i];

			CString addr = obj["addr"].asCString();
			CString label =obj["label"].asCString();
			CString regid = obj["reg_id"].asCString();
			double money = obj["money"].asDouble();
			int cold = obj["cold_dig"].asInt();
			int sig = obj["sign"].asInt();

			string conditon = _T("");
			conditon = strprintf("address = '%s'",addr);
			uistruct::LISTADDR_t pAddr;
			theApp.m_SqliteDeal.GetWalletAddressItem(conditon,&pAddr);
			if (pAddr.address.length() == 0)
			{
				string strSourceData= "";
				strSourceData = strprintf("'%s' , '%s' , '%.8f' , '%d' ,'%d','%s'" , addr ,regid ,money ,cold ,sig,label ) ;
				if (!theApp.m_SqliteDeal.InsertTableItem(_T("t_wallet_address") ,strSourceData ) )
				{
					TRACE("Insert t_wallet_address error!\n");
				}

			}else{
				string strSourceData,strWhere;
				strSourceData = strprintf("label = '%s'" ,label) ;
				strWhere= strprintf("address = '%s'" , addr ) ;
				if ( !theApp.m_SqliteDeal.UpdateTableItem(_T("t_wallet_address") , strSourceData , strWhere ) ){
					TRACE(_T("Update t_wallet_address failed!") );
				}
			}
		}
	}
	pos = strFile.find("wbookaddr");
	if (pos >=0)
	{
		Json::Value addrValue = root["bookaddr"]; 
		for(int i =0;i<(int)addrValue.size();i++){
			Json::Value obj = addrValue[i];
			CString addr = obj["addr"].asCString();
			CString label =obj["label"].asCString();
			string conditon = _T("");
			conditon = strprintf("address = '%s'",addr);
			uistruct::ADDRBOOK_t  pAddr;
			theApp.m_SqliteDeal.GetAddressBookItem(conditon,&pAddr);
			if (pAddr.address.length() == 0)
			{
				string strSourceData= "";
				strSourceData= strprintf("'%s' , '%s' "  ,label, addr) ;
				if (!theApp.m_SqliteDeal.InsertTableItem(_T("t_address_book") ,strSourceData ) )
				{
					TRACE("Insert t_wallet_address error!\n");
				}

			}else{
				string strSourceData,strWhere;
				strSourceData=strprintf("Label = '%s'",label) ;
				strWhere= strprintf("address = '%s'", addr ) ;
				if ( !theApp.m_SqliteDeal.UpdateTableItem(_T("t_address_book") , strSourceData , strWhere ) ){
					TRACE(_T("Update t_wallet_address failed!") );
				}
			}
		}
	}
}

void CSetDlg::OnBnClickedButtonDrsy()
{
	// TODO: 在此添加控件通知处理程序代码
	if (theApp.IsLockWallet())
	{
		return ;
	}
	OPENFILENAME ofn;
	char szFile[MAX_PATH];
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = TEXT('\0'); 
	ofn.nMaxFile = sizeof(szFile); 

	ofn.lpstrFilter =  "All Files(*.STS)\0*.STS\0All Files(*.*)\0*.*\0\0"; 
	ofn.nFilterIndex = 1; 
	ofn.lpstrFileTitle = NULL; 
	ofn.nMaxFileTitle = 0; 
	ofn.lpstrInitialDir = NULL;	ofn.hwndOwner = m_hWnd; 
	ofn.Flags = OFN_EXPLORER |OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (::GetOpenFileName(&ofn))
	{
		CString strPath = ofn.lpstrFile;
		string strCommand;
		strCommand = strprintf("%s %s",_T("importwallet"),strPath);
		Json::Value root;

		if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
		{
			TRACE("UpdateAddressData rpccmd listaddr error");
			return;
		}

		int size = root["imorpt key size"].asInt();
		if (size > 0)
		{
			WriteExportWalletAndBookAddr(strPath);
			UiFun::MessageBoxEx(_T("导入钱包成功请重新启动钱包") , _T("提示") ,MFB_OK|MFB_TIP );
			//ClosWallet();
			//((CDacrsUIDlg*)(this->GetParent()))->Close();
			((CStarSharesclientDlg*)(theApp.m_pMainWnd))->ClosWalletWind();
		}else{
			UiFun::MessageBoxEx(_T("导入钱包失败") , _T("提示") ,MFB_OK|MFB_TIP );
		}
	}
}


void CSetDlg::OnBnClickedButtonHfmrsz()
{
	// TODO: 在此添加控件通知处理程序代码
	if (PathFileExistsA(theApp.m_strInsPath.c_str()))
	{
		string configpath = "";
		configpath = strprintf("%s",theApp.m_strInsPath);
		configpath+= strprintf("\\%s","StarSharesclient.conf");
		string strFile = CJsonConfigHelp::getInstance()->GetConfigRootStr(configpath);
		if (strFile == _T(""))
		{
			return;
		}
		Json::Reader reader;  
		Json::Value root; 

		if (!reader.parse(strFile, root)) 
			return;

		int pos =strFile.find("closeconf");
		if (pos>=0)
		{
			Json::Value setclose = root["closeconf"];
			ASSERT(!setclose.isNull());
			setclose["colse"]= 0;
			setclose["tip"]= true;
			root["closeconf"]=setclose;
		}

		CStdioFile  File;
		string strpath = theApp.m_strInsPath;
		strpath+="\\StarSharesclient.conf";
		File.Open((LPCTSTR)(LPSTR)strpath.c_str(),CFile::modeWrite | CFile::modeCreate); 
		string strfile = root.toStyledString();
		File.WriteString(strfile.c_str());
		File.Close();
	}

	theApp.ParseUIConfigFile(theApp.m_strInsPath);

	CPostMsg p2ppmsg(MSG_USER_P2P_UI,WM_UP_ADDRESS);
	theApp.m_msgQueue.push(p2ppmsg);

	CPostMsg redmsg(MSG_USER_REDPACKET_UI,WM_UP_ADDRESS);
	theApp.m_msgQueue.push(redmsg);
	UiFun::MessageBoxEx(_T("恢复默认设置成功") ,  _T("提示") ,MFB_OK|MFB_TIP );
}

//关闭提示
void CSetDlg::OnBnClickedButtonGbts()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.m_poptips = !theApp.m_poptips ;
	UiFun::WriteClosConfig(theApp.m_poptips,theApp.m_strInsPath);
}


BOOL CSetDlg::PreTranslateMessage(MSG* pMsg)
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
	return CDialogBar::PreTranslateMessage(pMsg);
}



