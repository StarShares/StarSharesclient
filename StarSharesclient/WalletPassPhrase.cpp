// WalletPassPhrase.cpp : 实现文件
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "WalletPassPhrase.h"
#include "afxdialogex.h"


// CWalletPassPhrase 对话框

IMPLEMENT_DYNAMIC(CWalletPassPhrase, CBaseDlg)

CWalletPassPhrase::CWalletPassPhrase(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CWalletPassPhrase::IDD, pParent)
{

}

CWalletPassPhrase::~CWalletPassPhrase()
{
}

void CWalletPassPhrase::DoDataExchange(CDataExchange* pDX)
{
	CBaseDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PASSWORD, m_password);
	DDX_Control(pDX, IDC_TIMEOUT, m_timeout);	
	DDX_Control(pDX, IDC_MINUE, m_minue);	
	DDX_Control(pDX, IDC_HEAD, m_headText);	
	DDX_Control(pDX, IDC_CLOSE, m_rBtnClose);
	DDX_Control(pDX, IDCANCEL, m_rBtnCancel);
	DDX_Control(pDX, IDOK, m_rBtnOk);
}


BEGIN_MESSAGE_MAP(CWalletPassPhrase, CBaseDlg)
	ON_BN_CLICKED(IDOK, &CWalletPassPhrase::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWalletPassPhrase::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CLOSE, &CWalletPassPhrase::OnBnClickedClose)
END_MESSAGE_MAP()


// CWalletPassPhrase 消息处理程序


void CWalletPassPhrase::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString PassWord= _T("");
	CString passtime = _T("");
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(PassWord);
	GetDlgItem(IDC_EDIT_ITEM)->GetWindowText(passtime);
	if (PassWord == _T(""))
	{
		
		UiFun::MessageBoxEx(_T("请输入密码")  , _T("提示")  ,MFB_OK|MFB_TIP );
		return;
	}
	if (passtime == _T(""))
	{
		
		UiFun::MessageBoxEx(_T("请输入时间") , _T("提示")  ,MFB_OK|MFB_TIP );
		return;
	}
	if (!IsAllDigtal(passtime))
	{
		
		UiFun::MessageBoxEx(_T("时间必须是数字")  , _T("提示")  ,MFB_OK|MFB_TIP );
		return;
	}
	
	string strCommand;
	strCommand = strprintf("%s %s %d","walletpassphrase",PassWord,(atoi(passtime)*60));
	string strShowData =_T("");
	Json::Value root; 
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
	{
		TRACE(" rpccmd walletpassphrase error");
		UiFun::MessageBoxEx(_T("输入密码不正确,请重新输入") ,_T("提示")  ,MFB_OK|MFB_TIP );
		return;
	}


	bool isEntryp = root["passphrase"].asBool();
	if (!isEntryp)
	{
		UiFun::MessageBoxEx(_T("输入密码不正确,请重新输入"), _T("提示")  ,MFB_OK|MFB_TIP );
		return;
	}else{
		UiFun::MessageBoxEx(_T("恭喜钱包解锁成功") , _T("提示")  ,MFB_OK|MFB_TIP );
	}

	theApp.m_bIsPassLock = TRUE;
	CBaseDlg::OnOK();
}


BOOL CWalletPassPhrase::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	m_headText.SetWindowText(_T("解锁钱包"));
	m_headText.SetFont(100, _T("微软雅黑"));
	m_headText.SetTextColor(RGB(255,255,255));	
	m_headText.SetWindowPos( NULL , 5 , 4 , 100, 25  ,SWP_SHOWWINDOW ) ; 
	
	m_rBtnClose.SetBitmaps( IDB_BITMAP_TC_CLOSE2 , RGB(0, 0, 0) , IDB_BITMAP_TC_CLOSE1 , RGB(0, 0, 0) );
	m_rBtnClose.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnClose.SetWindowText("") ;
	m_rBtnClose.SetFontEx(-12 , _T("微软雅黑"));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	m_rBtnClose.SizeToContent();
	/*
	m_rBtnClose.SetIcon(IDI_ICON_CLOSE3, 0, 0, IDI_ICON_CLOSE1, 0, 0);
	m_rBtnClose.DrawBorder(FALSE); 
	m_rBtnClose.DrawTransparent(TRUE);
	m_rBtnClose.SizeToContent();
	*/
	CRect rect ;
	m_rBtnClose.GetClientRect(rect);

	RECT ret;
	GetWindowRect(&ret);
	m_rBtnClose.SetWindowPos(NULL ,(ret.right-ret.left)-rect.Width() - 4 , 2 , 0 , 0 , SWP_NOSIZE); 

	m_rBtnOk.SetBitmaps( IDB_BITMAP_TC_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_TC_BUT2 , RGB(255, 255, 255) );
	m_rBtnOk.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnOk.SetWindowText(_T("确认")) ;
	m_rBtnOk.SetFontEx(-12 , _T("微软雅黑"));
	/*
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	*/
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_rBtnOk.SizeToContent();

	m_rBtnCancel.SetBitmaps( IDB_BITMAP_TC_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_TC_BUT2 , RGB(255, 255, 255) );
	m_rBtnCancel.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnCancel.SetWindowText(_T("取消")) ;
	m_rBtnCancel.SetFontEx(-12 , _T("微软雅黑"));
	/*
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	*/
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_rBtnCancel.SizeToContent();
	// TODO:  在此添加额外的初始化
	theApp.m_bIsPassLock = FALSE;
	GetDlgItem(IDC_EDIT_ITEM)->SetWindowText(_T("60"));
	GetDlgItem(IDC_PASSWORD)->SetWindowText(_T("密码:"));
	GetDlgItem(IDC_TIMEOUT)->SetWindowText(_T("解锁时间:"));
	GetDlgItem(IDC_MINUE)->SetWindowText(_T("分"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CWalletPassPhrase::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.m_bIsPassLock = TRUE;
	CBaseDlg::OnCancel();
}


void CWalletPassPhrase::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.m_bIsPassLock = TRUE;
	CBaseDlg::OnCancel();
}
