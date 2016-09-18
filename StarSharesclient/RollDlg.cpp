// RollDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RollDlg.h"
#include "afxdialogex.h"
#include "ShowPageDlg.h"
#include <afxinet.h>
#include "SynchronousSocket.h"
#include "CommonStruct.h"


// CRollDlg 对话框

IMPLEMENT_DYNAMIC(CRollDlg, CDialogEx)

void long2time(unsigned long nTime, CString& strTime)
{ 
	CTime objTime(nTime);    
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", objTime.GetYear(), objTime.GetMonth(), objTime.GetDay(),
		objTime.GetHour(), objTime.GetMinute(), objTime.GetSecond());
}

CRollDlg::CRollDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRollDlg::IDD, pParent)
{
	m_pBmp = NULL;
	m_pShowPageDlg = NULL;

	m_btnPrev.LoadBitmaps(IDB_BITMAP_LEFT1);
	m_btnNext.LoadBitmaps(IDB_BITMAP_RIGHT1);
	m_nCurAssetIndex = 0;
}

CRollDlg::~CRollDlg()
{
	if(NULL != m_pShowPageDlg)
	{
		delete m_pShowPageDlg;
		m_pShowPageDlg = NULL;
	}
}

void CRollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_PREV, m_btnPrev);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btnNext);
}


BEGIN_MESSAGE_MAP(CRollDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PREV, &CRollDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CRollDlg::OnBnClickedBtnNext)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRollDlg 消息处理程序

BOOL CRollDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBkBmpNid(IDB_BITMAP_BLACK);
	//此处发送RPC获取web发行的所有的资产ID存入m_MapAssetList中

	string strCondition = "Status = 3 order by ID ASC";
	theApp.m_SqliteDeal.GetAssetList(strCondition, (&m_VecAssetList));

	if(m_VecAssetList.size() == 0)
	{
		return TRUE;
	}
	else
	{
		m_pShowPageDlg = new CShowPageDlg;
		m_pShowPageDlg->Create(IDD_DIALOG_SHOWPAGE, this);
		m_pShowPageDlg->SetWindowPos(NULL, 37, 3, 650, 201, SWP_HIDEWINDOW);
		m_pShowPageDlg->ShowWindow(SW_SHOW);
	}

	InitLayout(m_nCurAssetIndex);														//一开始显示第一个资产，资产从下标0开始

	return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}

void CRollDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

void CRollDlg::InitLayout(int nShowNum)
{
	int nsize = m_VecAssetList.size();

	if(1 == nsize)
	{
		m_pShowPageDlg->GetWindowRect(&m_rcOrig);
		uistruct::ASSETLIST::const_iterator const_it;
		int iIndex = 0;
		for(const_it = m_VecAssetList.begin(); const_it != m_VecAssetList.end(); const_it++)
		{
			if(iIndex == (m_nCurAssetIndex))
			{
				string strCommand;
				CString strStartTime = "-";
				m_pShowPageDlg->GetDlgItem(IDC_STATIC_ZC_NAME)->SetWindowText(const_it->AssetName.c_str());
				m_pShowPageDlg->GetDlgItem(IDC_STATIC_ISSUER)->SetWindowText(const_it->AssetIssuer.c_str());

				strCommand = strprintf("%.3f", const_it->PopNum);
				m_pShowPageDlg->GetDlgItem(IDC_STATIC_NUM)->SetWindowText(strCommand.c_str());

				strCommand = strprintf("%.3f", const_it->MaxNum);
				m_pShowPageDlg->GetDlgItem(IDC_STATIC_PRICE)->SetWindowText(strCommand.c_str());
				strCommand = strprintf("%.3f",const_it->GoalNum);
				m_pShowPageDlg->GetDlgItem(IDC_STATIC_BASELINE)->SetWindowText(strCommand.c_str());

				time_t tStartDate = const_it->IssueStartTime / 1000;
				time_t tEndDate = const_it->issueEndTime / 1000;
				long2time(tStartDate, strStartTime);

				m_pShowPageDlg->GetDlgItem(IDC_STATIC_DATE)->SetWindowText(strStartTime);

				if(const_it->issueEndTime > const_it->IssueStartTime)
				{
					unsigned int iSecond =  tEndDate - tStartDate;

					unsigned int iDay = iSecond/(60*60*24);
					unsigned int iReminder = iSecond%(60*60*24);
					if(iReminder > 0)
					{
						iDay = iDay + 1;
						strCommand = strprintf("%d", iDay);
						m_pShowPageDlg->GetDlgItem(IDC_STATIC_DAY_REMAIN)->SetWindowText(strCommand.c_str());
					}

				}else
				{
					m_pShowPageDlg->GetDlgItem(IDC_STATIC_DAY_REMAIN)->SetWindowText("0");
				}
				strCommand = "http://";
				strCommand += theApp.m_webserverIp;
				strCommand += ":";
				strCommand += theApp.m_webserverPort;
				strCommand += const_it->strUrlPic;
				m_pShowPageDlg->m_staPic.DownloadServerFile(strCommand.c_str());
				m_pShowPageDlg->m_staPic.Invalidate(TRUE);
				m_pShowPageDlg->m_staProgress.SetProgress(atoi(const_it->buyProgress.c_str()));

				string strCondition = strprintf("ID = '%d'", const_it->itcfiid);
				theApp.m_SqliteDeal.GetAssetParamList(strCondition, (&m_VecAssetParamList));

				uistruct::ASSETPARAMLIST::iterator it= m_VecAssetParamList.begin();
				for(;it != m_VecAssetParamList.end();it++)
				{
					string strAmount = strprintf("%0.3f", it->damount);	

					m_pShowPageDlg->m_combBuy.AddString(strAmount.c_str());
				}
			}

			iIndex++;
		}

		m_btnPrev.EnableWindow(FALSE);
		m_btnNext.EnableWindow(FALSE);
	}
	
	else if(nsize > 1)
	{
		LayoutDlg(m_nCurAssetIndex);
	}
	else
	{
		m_btnPrev.EnableWindow(FALSE);
		m_btnNext.EnableWindow(FALSE);
	}
}

void CRollDlg::LayoutDlg(int nCurIndex)
{
	while(m_pShowPageDlg->m_combBuy.GetCount() != 0)
	{
		m_pShowPageDlg->m_combBuy.DeleteString(0);
	}

	vector<CShowPageDlg*> tmpVec;								//存储当前对话框的前一个和后一个

	uistruct::ASSETLIST::const_iterator const_it;

	int iIndex = 0;
	for(const_it = m_VecAssetList.begin(); const_it != m_VecAssetList.end(); const_it++)
	{
		if(iIndex == (m_nCurAssetIndex))
		{
			m_VecAssetParamList.clear();

			string strCommand;
			CString strStartTime = "-";
			m_pShowPageDlg->GetDlgItem(IDC_STATIC_ZC_NAME)->SetWindowText(const_it->AssetName.c_str());
			m_pShowPageDlg->GetDlgItem(IDC_STATIC_ISSUER)->SetWindowText(const_it->AssetIssuer.c_str());

			strCommand = strprintf("%.3f", const_it->PopNum);
			m_pShowPageDlg->GetDlgItem(IDC_STATIC_NUM)->SetWindowText(strCommand.c_str());

			strCommand = strprintf("%.3f", const_it->MaxNum);
			m_pShowPageDlg->GetDlgItem(IDC_STATIC_PRICE)->SetWindowText(strCommand.c_str());
			strCommand = strprintf("%.3f",const_it->GoalNum);
			m_pShowPageDlg->GetDlgItem(IDC_STATIC_BASELINE)->SetWindowText(strCommand.c_str());

			time_t tStartDate = const_it->IssueStartTime / 1000;
			time_t tEndDate = const_it->issueEndTime / 1000;
			long2time(tStartDate, strStartTime);
			
			m_pShowPageDlg->GetDlgItem(IDC_STATIC_DATE)->SetWindowText(strStartTime);

			if(const_it->issueEndTime > const_it->IssueStartTime)
			{
				unsigned int iSecond =  tEndDate - tStartDate;

				unsigned int iDay = iSecond/(60*60*24);
				unsigned int iReminder = iSecond%(60*60*24);
				if(iReminder > 0)
				{
					iDay = iDay + 1;
					strCommand = strprintf("%d", iDay);
					m_pShowPageDlg->GetDlgItem(IDC_STATIC_DAY_REMAIN)->SetWindowText(strCommand.c_str());
				}

			}else
			{
				m_pShowPageDlg->GetDlgItem(IDC_STATIC_DAY_REMAIN)->SetWindowText("0");
			}

			strCommand = "http://";
			strCommand += theApp.m_webserverIp;
			strCommand += ":";
			strCommand += theApp.m_webserverPort;
			strCommand += "/";
			strCommand += const_it->strUrlPic;
			m_pShowPageDlg->m_staPic.DownloadServerFile(strCommand.c_str());
			m_pShowPageDlg->m_staPic.Invalidate(TRUE);

			m_pShowPageDlg->m_staProgress.SetProgress(atoi(const_it->buyProgress.c_str()));
			m_pShowPageDlg->ShowWindow(SW_SHOW);

			string strCondition = strprintf("ID = '%d'", const_it->itcfiid);
			theApp.m_SqliteDeal.GetAssetParamList(strCondition, (&m_VecAssetParamList));

			uistruct::ASSETPARAMLIST::iterator it= m_VecAssetParamList.begin();
			for(;it != m_VecAssetParamList.end();it++)
			{
				string strAmount = strprintf("%0.3f", it->damount);	

				m_pShowPageDlg->m_combBuy.AddString(strAmount.c_str());
			}
		}

		iIndex++;
	}

	if(0 == m_nCurAssetIndex )
	{
		m_btnPrev.LoadBitmaps(IDB_BITMAP_LEFT1);
		m_btnPrev.EnableWindow(FALSE);
		
		CRect rectTemp;
	}
	else
	{
		m_btnPrev.LoadBitmaps(IDB_BITMAP_LEFT2);
		m_btnPrev.EnableWindow(TRUE);
		CRect rectTemp;
	}

	if(m_nCurAssetIndex == (m_VecAssetList.size() - 1))
	{
		m_btnNext.LoadBitmaps(IDB_BITMAP_RIGHT1);
		m_btnNext.EnableWindow(FALSE);

		CRect rectTemp;
	}
	else
	{
		m_btnNext.LoadBitmaps(IDB_BITMAP_RIGHT2);
		m_btnNext.EnableWindow(TRUE);
		CRect rectTemp;
	}

}

void CRollDlg::ClearControl()
{
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_ZC_NAME)->SetWindowText("");
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_ISSUER)->SetWindowText("");
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_NUM)->SetWindowText("");
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_PRICE)->SetWindowText("");
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_BASELINE)->SetWindowText("");
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_DATE)->SetWindowText("");
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_DAY_REMAIN)->SetWindowText("");
	//m_pShowPageDlg->GetDlgItem(IDC_EDIT_SUPPORT)->SetWindowText("");
	m_pShowPageDlg->GetDlgItem(IDC_STATIC_AMOUNT)->SetWindowText("");
}
void CRollDlg::OnBnClickedBtnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(m_nCurAssetIndex <= 0)
	{
		TRACE(_T("认购资产界面----当前位置为首位\r\n"));
		return;
	}
	--m_nCurAssetIndex;
	RefreshCurPage();
	ClearControl();
	LayoutDlg(m_nCurAssetIndex);
}


void CRollDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nCurAssetIndex >= m_VecAssetList.size())
	{
		TRACE(_T("认购资产界面----当前位置为末尾\r\n"));
		return;
	}

	++m_nCurAssetIndex;
	RefreshCurPage();
	ClearControl();
	LayoutDlg(m_nCurAssetIndex);
}

void CRollDlg::RefreshCurPage()
{
	if(m_VecAssetList.size() == 0)
	{
		return;
	}
	string strCommand = "";
	string strShowData ="";
	strCommand = "POST ";
	strCommand += theApp.m_webSinglePath;
	strCommand += "?";
	strCommand += strprintf("tcfiid=%d",m_VecAssetList[m_nCurAssetIndex].itcfiid );

	Json::Value root; 
	Json::Value arrRow;
	if(!CSoyPayHelp::getInstance()->SendWebRpc(strCommand,root))
	{
		TRACE("SyncAddrInfo rpccmd listaddr error");
		return;
	}

	m_VecAssetList[m_nCurAssetIndex].itcfiid			= root["tcfiid"].asInt();
	//发行AssetID					
	m_VecAssetList[m_nCurAssetIndex].AssetID			= root["tissue"].asString(); 
	//AssetName					  
	m_VecAssetList[m_nCurAssetIndex].AssetName			= root["tproject"].asString() ;
	//AssetIssuer				 
	m_VecAssetList[m_nCurAssetIndex].AssetIssuer		= root["tissuername"].asString() ;
	//PopNum			
	m_VecAssetList[m_nCurAssetIndex].PopNum				= root["tshare"].asDouble();
	//MaxNum					 
	m_VecAssetList[m_nCurAssetIndex].MaxNum				= root["tupperamount"].asDouble();
	//GoalNum					 
	m_VecAssetList[m_nCurAssetIndex].GoalNum			= root["tflooramount"].asDouble();
	//发行日期					  
	m_VecAssetList[m_nCurAssetIndex].IssueStartTime		= root["tstarttime"].asUInt64();											 
	m_VecAssetList[m_nCurAssetIndex].issueEndTime		= root["tendtime"].asUInt64();											  
	m_VecAssetList[m_nCurAssetIndex].strUrlPic			= root["tcrowdfundingimg"].asString();				
	m_VecAssetList[m_nCurAssetIndex].AssetAddr			= root["taccountaddress"].asString();	
	m_VecAssetList[m_nCurAssetIndex].CurAmount			= root["tcurrentamount"].asDouble();
	m_VecAssetList[m_nCurAssetIndex].buyProgress		= root["tprocessratio"].asString();
	m_VecAssetList[m_nCurAssetIndex].status				= root["tstatus"].asInt();
	m_VecAssetList[m_nCurAssetIndex].bResult			= root["tresult"].asBool();
	string str = root.toStyledString();

	string strSourceData,strWhere;
	strSourceData = strprintf("ID = '%d', AssetID = '%s' , AssetName = '%s', AssetIssuer = '%s', PopNum = '%.3f', MaxNum = '%.3f', GoalNum = '%.3f', IssueStartTime = '%llu', IssueEndTime = '%llu', strUrlPic = '%s', AssetAddr = '%s',CurrentAmount = '%.3f',BuyProgress = '%s',Status = '%d',Result = '%d'" ,\
		m_VecAssetList[m_nCurAssetIndex].itcfiid, m_VecAssetList[m_nCurAssetIndex].AssetID.c_str() ,\
		m_VecAssetList[m_nCurAssetIndex].AssetName.c_str(), m_VecAssetList[m_nCurAssetIndex].AssetIssuer.c_str(),\
		m_VecAssetList[m_nCurAssetIndex].PopNum,m_VecAssetList[m_nCurAssetIndex].MaxNum,\
		m_VecAssetList[m_nCurAssetIndex].GoalNum,m_VecAssetList[m_nCurAssetIndex].IssueStartTime,\
		m_VecAssetList[m_nCurAssetIndex].issueEndTime,m_VecAssetList[m_nCurAssetIndex].strUrlPic.c_str(),\
		m_VecAssetList[m_nCurAssetIndex].AssetAddr.c_str(),m_VecAssetList[m_nCurAssetIndex].CurAmount,\
		m_VecAssetList[m_nCurAssetIndex].buyProgress, m_VecAssetList[m_nCurAssetIndex].status, m_VecAssetList[m_nCurAssetIndex].bResult ) ;
	strWhere=strprintf("ID = %d" , m_VecAssetList[m_nCurAssetIndex].itcfiid  ) ;
	if(!theApp.m_SqliteDeal.UpdateTableItem(_T("t_asset") , strSourceData , strWhere))
	{
		TRACE("UPDATE t_wallet_address data failed!\n");
	}
}


BOOL CRollDlg::OnEraseBkgnd(CDC* pDC)
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
		pDC->StretchBlt(rect.left,rect.top-1,rect.Width(),rect.Height(),   &dcMem,   0,   0,bm.bmWidth-1,bm.bmHeight-1,   SRCCOPY); 

		dcMem.SelectObject(pOldBitmap);
		dcMem.DeleteDC();
	} else  
		CWnd::OnEraseBkgnd(pDC);

	return 1;
}


void CRollDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	CRect rt;
	GetWindowRect(&rt);
	if(NULL != GetSafeHwnd())
	{
		CWnd *pst = (CWnd *)GetDlgItem(IDC_BTN_PREV);
		if(NULL != pst)
		{
			CRect rect;
			pst->GetWindowRect(&rect);

			pst->SetWindowPos(NULL, (37 - rect.Width())/2, (rt.Height() - rect.Height())/2, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
		}

		pst = (CWnd *)GetDlgItem(IDC_BTN_NEXT);
		if(NULL != pst)
		{
			CRect rect;
			pst->GetWindowRect(&rect);

			pst->SetWindowPos(NULL, 716 - (37 - rect.Width())/2 - rect.Width()/2, (rt.Height() - rect.Height())/2, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
		}
	}
}


void CRollDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}

