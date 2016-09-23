// ShowSingleTxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "ShowSingleTxDlg.h"
#include "afxdialogex.h"


// CShowSingleTxDlg 对话框

IMPLEMENT_DYNAMIC(CShowSingleTxDlg, CBaseDlg)

CShowSingleTxDlg::CShowSingleTxDlg(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CShowSingleTxDlg::IDD, pParent)
{

}

CShowSingleTxDlg::~CShowSingleTxDlg()
{
}

void CShowSingleTxDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HEAD, m_headText);	
	DDX_Control(pDX, IDC_CLOSE, m_rBtnClose);
	DDX_Control(pDX, IDOK, m_rBtnOk);
}


BEGIN_MESSAGE_MAP(CShowSingleTxDlg, CBaseDlg)
	ON_BN_CLICKED(IDC_CLOSE, &CShowSingleTxDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDOK, &CShowSingleTxDlg::OnBnClickedOk)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CShowSingleTxDlg 消息处理程序


BOOL CShowSingleTxDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_headText.SetFont(100, _T("微软雅黑"));
	m_headText.SetTextColor(RGB(255,255,255));	
	m_headText.SetWindowText("交易详情");

	m_rBtnClose.SetBitmaps( IDB_BITMAP_TC_CLOSE2 , RGB(0, 0, 0) , IDB_BITMAP_TC_CLOSE1 , RGB(0, 0, 0) );
	m_rBtnClose.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnClose.SetWindowText("") ;
	m_rBtnClose.SetFontEx(20 , _T("微软雅黑"));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	m_rBtnClose.SizeToContent();
	CRect rect ;
	m_rBtnClose.GetClientRect(rect);

	RECT ret;
	GetWindowRect(&ret);
	m_rBtnClose.SetWindowPos(NULL ,(ret.right-ret.left)-rect.Width()-5 , 2 , 0 , 0 , SWP_NOSIZE); 

	m_rBtnOk.SetBitmaps( IDB_BITMAP_TC_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_TC_BUT2 , RGB(255, 255, 255) );
	m_rBtnOk.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	m_rBtnOk.SizeToContent();
	// TODO:  在此添加额外的初始化
	ShowTxDetail(theApp.m_strAddress);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CShowSingleTxDlg::ShowTxDetail(CString jsontx)
{
	if (jsontx == _T(""))
	{
		string strShowData;
		strShowData+=strprintf("%s" ,_T("此交易不存在")) ;
		GetDlgItem(IDC_EDIT_TXDETAIL)->SetWindowText(strShowData.c_str());
		return;
	}
	//string txdetail = tx.ToJson();
	uistruct::REVTRANSACTION_t tx;
	tx.JsonToStruct(jsontx.GetString());
	string txdetail,strShowData;

	string txtype = tx.txtype;
	if (!strcmp(txtype.c_str(),"REWARD_TX"))
	{
		strShowData+=strprintf("%s" ,_T("挖矿奖励交易")) ;
	}else if (!strcmp(txtype.c_str(),"REG_ACCT_TX"))
	{
		strShowData+=strprintf("%s" ,_T("注册账户交易")) ;
	}else if (!strcmp(txtype.c_str(),"COMMON_TX"))
	{
		strShowData+=strprintf("%s" ,_T("转账交易")) ;
	}else if (!strcmp(txtype.c_str(),"CONTRACT_TX"))
	{
		strShowData+=strprintf("%s" ,_T("合约交易")) ;
	}else if (!strcmp(txtype.c_str(),"REG_APP_TX"))
	{
		strShowData+=strprintf("%s" ,_T("注册应用交易")) ;
	}
	txdetail=strprintf("%s: %s\r\n\r\n",_T("交易类型"),strShowData.c_str());
	txdetail+=strprintf("%s: %s\r\n\r\n",_T("交易ID"),tx.txhash);
	txdetail+=strprintf("%s:   %d\r\n\r\n",_T("版本号"),tx.ver);
	txdetail+=strprintf("%s:   %s\r\n\r\n",_T("源地址"),tx.addr.c_str());	
	if (tx.pubkey != "")
	{
		txdetail+=strprintf("%s:   %s\r\n\r\n",_T("公钥"),tx.pubkey.c_str());		
	}
	if (tx.miner_pubkey != "")
	{
		txdetail+=strprintf("%s:   %s\r\n\r\n",_T("冷挖矿公钥"),tx.miner_pubkey.c_str());
	}
	if (tx.fees != 0)
	{
		txdetail+=strprintf("%s:   %.8f\r\n\r\n",_T("小费"),tx.fees*COIN);
	}
	if (tx.height != 0)
	{
		int height = tx.height +250; 
		txdetail+=strprintf("%s:   %d\r\n\r\n",_T("交易超时高度"),height);
	}
	if (tx.desaddr != "")
	{
		txdetail+=strprintf("%s:   %s\r\n\r\n",_T("目的地址"),tx.desaddr.c_str() );
	}
	if (tx.money != 0)
	{
		txdetail+=strprintf("%s:   %.2f\r\n\r\n",_T("交易金额"),tx.money*COIN);
	}
	if (tx.Contract != "")
	{
		//txdetail.AppendFormat(_T("合约内容:   %d\r\n\r\n"),tx.Contract.c_str() );
		txdetail+=strprintf("%s",GetContacrDetail(tx).c_str());

	}

	if (tx.confirmedHeight != 0)
	{
		txdetail+=strprintf("%s:   %d\r\n\r\n",_T("确认高度"),tx.confirmedHeight );
	}
	if (tx.confirmedtime != 0)
	{
		SYSTEMTIME curTime = UiFun::Time_tToSystemTime(tx.confirmedtime);
		txdetail+=strprintf("%s:   %04d-%02d-%02d %02d:%02d:%02d\r\n\r\n",_T("确认时间"),curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);
	}
	if (tx.blockhash != "")
	{
		txdetail+=strprintf("%s:   %s\r\n\r\n",_T("确认blockHash"),tx.blockhash.c_str());
	}
	if ( theApp.blocktipheight != 0 && tx.confirmedHeight != 0)
	{
		unsigned int quredCount = theApp.blocktipheight - tx.confirmedHeight;
		if (quredCount >=0)
		{
			txdetail+=strprintf("%s:  %d\r\n\r\n",_T("确认数"),quredCount );
		}	
	}

	GetDlgItem(IDC_EDIT_TXDETAIL)->SetWindowText(txdetail.c_str());
}

string CShowSingleTxDlg::GetContacrDetail(uistruct::REVTRANSACTION_t tx)
{
	string strCommand,strShowData;
	strCommand = strprintf("%s %s","getaccountinfo" ,tx.desaddr.c_str() );
	CSoyPayHelp::getInstance()->SendRpc(strCommand,strShowData);

	if (strShowData  ==""){		
		return _T("");
	}
	Json::Reader reader;  
	Json::Value root; 

	if (reader.parse(strShowData, root)) {		

		if (strShowData.find("RegID") >0)
		{
			tx.desregid = root["RegID"].asString();
		}
	}

	string txdetail ="";
	string nValue = tx.Contract;
	std::vector<unsigned char> vTemp = CSoyPayHelp::getInstance()->ParseHex(nValue);

	string strContract = CSoyPayHelp::getInstance()->HexStr(vTemp);
	txdetail +=strprintf("%s:   %d\r\n\r\n",_T("合约") ,strContract.c_str() );

	
	return txdetail;
}

void CShowSingleTxDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	CBaseDlg::OnCancel();
}


void CShowSingleTxDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CBaseDlg::OnOK();
}


void CShowSingleTxDlg::OnSize(UINT nType, int cx, int cy)
{
	CBaseDlg::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
