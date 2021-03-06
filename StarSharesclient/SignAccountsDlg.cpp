// SignAccountsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "SignAccountsDlg.h"
#include "afxdialogex.h"


// CSignAccountsDlg 对话框

IMPLEMENT_DYNAMIC(CSignAccountsDlg, CBaseDlg)

CSignAccountsDlg::CSignAccountsDlg(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CSignAccountsDlg::IDD, pParent)
{
}
CSignAccountsDlg::~CSignAccountsDlg()
{

}

void CSignAccountsDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SA_CLOSE, m_rBtnClose);
	DDX_Control(pDX, IDC_BUTTON_SA_SEND, m_rBtnSend);
	DDX_Control(pDX, IDC_ST_ADDR, m_addr);
	DDX_Control(pDX, IDC_FEE, m_fee);
	DDX_Control(pDX, IDC_HEAD, m_headText);	
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cboUnit);
}


BEGIN_MESSAGE_MAP(CSignAccountsDlg, CBaseDlg)
	ON_BN_CLICKED(IDC_BUTTON_SA_SEND, &CSignAccountsDlg::OnBnClickedButtonSend)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SA_CLOSE, &CSignAccountsDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()



void CSignAccountsDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (theApp.IsLockWallet())
	{
		return ;
	}

	CString address;
	GetDlgItem(IDC_EDIT_SA_ADDRESS)->GetWindowText(address);
	if ( _T("") != address ) {
		string strCommand , strShowData;CString strFee ;

		Json::Reader reader;  
		Json::Value root; 
		//if (!reader.parse(strShowData.GetString(), root)) 
		//	return  ;


		GetDlgItem(IDC_EDIT_FEE)->GetWindowText(strFee);
		strCommand = strprintf("%s %s %lld","registaccounttx" ,address  , (INT64)REAL_MONEY(strtod(strFee,NULL)) );

		if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
		{
			TRACE("OnBnClickedButtonSend rpccmd registaccounttx error");
			return;
		}

		strShowData = root.toStyledString();
		string strData;
		int pos = strShowData.find("hash");

		if ( pos >=0 ) {
			//插入到数据库
			string strHash;
			strHash =root["hash"].asString();
			string strCond;
			strCond = strprintf(" hash = '%s' ", (LPSTR)(LPCTSTR)strHash.c_str());
			int nItem =  theApp.m_SqliteDeal.GetTableCountItem(_T("t_transaction") , strCond) ;

			if ( 0 == nItem ) {

				CPostMsg postmsg(MSG_USER_GET_UPDATABASE,WM_REVTRANSACTION);
				postmsg.SetData(strHash);
				theApp.m_msgQueue.push(postmsg);

			}
		}

		if ( pos >=0 ) {
			strData = strprintf("%s\n%s" , _T("激活交易发送成功，请等待1-2分钟确认激活交易") ,root["hash"].asCString() ) ;
		}else{
			strData= _T("激活账户失败") ;
		}
		if ( IDOK == UiFun::MessageBoxEx(strData.c_str(), _T("提示") , MFB_OK|MFB_TIP ) ){
			EndDialog(IDOK);
		}
	}

}
void CSignAccountsDlg::SetShowAddr(CString addr)
{
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(0);
	GetDlgItem(IDC_EDIT_SA_ADDRESS)->SetWindowText(addr);
}



BOOL CSignAccountsDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	m_headText.SetWindowText(_T("激活地址"));
	m_headText.SetFont(90, _T("微软雅黑"));
	m_headText.SetTextColor(RGB(255,255,255));	
	m_headText.SetWindowPos( NULL , 5 , 4 , 100, 25  ,SWP_SHOWWINDOW ) ; 
	// TODO:  在此添加额外的初始化
	
	m_rBtnClose.SetBitmaps( IDB_BITMAP_TC_CLOSE1 , RGB(0, 0, 0) , IDB_BITMAP_TC_CLOSE2 , RGB(0, 0, 0) );
	m_rBtnClose.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnClose.SetWindowText("") ;
	m_rBtnClose.SetFontEx(-12 , _T("微软雅黑"));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	m_rBtnClose.SizeToContent();
	
	CRect rect ;
	m_rBtnClose.GetClientRect(rect);

	RECT ret;
	GetWindowRect(&ret);
	m_rBtnClose.SetWindowPos(NULL ,(ret.right-ret.left)-rect.Width() - 4 , 2 , 0 , 0 , SWP_NOSIZE); 

	m_rBtnSend.SetBitmaps( IDB_BITMAP_TC_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_TC_BUT2 , RGB(255, 255, 255) );
	m_rBtnSend.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnSend.SetWindowText(_T("激  活")) ;
	m_rBtnSend.SetFontEx(-12 , _T("微软雅黑"));
	/*
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	*/
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_rBtnSend.SizeToContent();

	SetShowAddr( theApp.m_strAddress);

	m_fontGrid.CreatePointFont(100,_T("新宋体"));

	GetDlgItem(IDC_EDIT_FEE)->SetWindowTextA("0.0001");

	//GetDlgItem(IDC_FEE)->SetWindowText(_T("提示"));
	//GetDlgItem(IDC_ST_ADDR)->SetWindowText(_T("地址:"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CSignAccountsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//if (nCtlColor == CTLCOLOR_STATIC)
	//{
	//	pDC->SetBkMode(TRANSPARENT);
	//	pDC->SelectObject(&m_fontGrid);
	//	hbr = (HBRUSH)CreateSolidBrush(RGB(240,240,240));
	//}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CSignAccountsDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDOK);
}

