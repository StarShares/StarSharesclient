// NewSendAddr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "NewSendAddr.h"
#include "afxdialogex.h"


// CNewSendAddr �Ի���

IMPLEMENT_DYNAMIC(CNewSendAddr, CBaseDlg)

CNewSendAddr::CNewSendAddr(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CNewSendAddr::IDD, pParent)
{

}

CNewSendAddr::~CNewSendAddr()
{
}

void CNewSendAddr::DoDataExchange(CDataExchange* pDX)
{
	CBaseDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL, m_label);
	DDX_Control(pDX, IDC_ADDR, m_addr);	
	DDX_Control(pDX, IDC_HEAD, m_headText);	
	DDX_Control(pDX, IDC_CLOSE, m_rBtnClose);
	DDX_Control(pDX, IDCANCEL, m_rBtnCancel);
	DDX_Control(pDX, IDOK, m_rBtnOk);
}


BEGIN_MESSAGE_MAP(CNewSendAddr, CBaseDlg)
	ON_BN_CLICKED(IDOK, &CNewSendAddr::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CLOSE, &CNewSendAddr::OnBnClickedClose)
	ON_BN_CLICKED(IDCANCEL, &CNewSendAddr::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNewSendAddr ��Ϣ��������


void CNewSendAddr::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CString label =_T("");
	CString addr  = _T("");
	GetDlgItem(IDC_EDIT_LABEL)->GetWindowText(label);
	GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(addr);
	if (addr == _T(""))
	{
		UiFun::MessageBoxEx(_T("��ַ����Ϊ��") , _T("��ʾ")  ,MFB_OK|MFB_TIP );
		return;
	}
	uistruct::ADDRBOOK_t sAddrBookItem;
	string strCond;
	strCond = strprintf(" address='%s' ", addr);
	
	int  item = theApp.m_SqliteDeal.GetAddressBookItem(strCond, &sAddrBookItem);
	if (sAddrBookItem.address != _T(""))
	{
		UiFun::MessageBoxEx(_T("��ַ�����Ѵ��ڴ˵�ַ") , _T("��ʾ")  ,MFB_OK|MFB_TIP );
		return;
	}
	m_selectAddr.label = label;
	m_selectAddr.address = addr;
	CBaseDlg::OnOK();
}
void CNewSendAddr::GetAddrbook(uistruct::ADDRBOOK_t &addr)
{
	addr = m_selectAddr;
}
BOOL CNewSendAddr::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	m_headText.SetWindowText(_T("�½����͵�ַ"));
	m_headText.SetFont(90, _T("΢���ź�"));
	m_headText.SetTextColor(RGB(255,255,255));	
	m_headText.SetWindowPos( NULL , 5 , 4 , 150, 25  ,SWP_SHOWWINDOW ) ; 
	
	m_rBtnClose.SetBitmaps( IDB_BITMAP_TC_CLOSE1 , RGB(0, 0, 0) , IDB_BITMAP_TC_CLOSE2 , RGB(0, 0, 0) );
	m_rBtnClose.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnClose.SetWindowText("") ;
	m_rBtnClose.SetFontEx(-12 , _T("΢���ź�"));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0, 0, 0));
	m_rBtnClose.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0, 0, 0));
	m_rBtnClose.SizeToContent();

	CRect rect ;
	m_rBtnClose.GetClientRect(rect);

	RECT ret;
	GetWindowRect(&ret);
	m_rBtnClose.SetWindowPos(NULL ,(ret.right-ret.left)-rect.Width() - 4, 2 , 0 , 0 , SWP_NOSIZE); 

	m_rBtnOk.SetBitmaps( IDB_BITMAP_TC_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_TC_BUT2 , RGB(255, 255, 255) );
	m_rBtnOk.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnOk.SetWindowText(_T("ȷ��")) ;
	
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_rBtnOk.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_rBtnOk.SizeToContent();

	m_rBtnCancel.SetBitmaps( IDB_BITMAP_TC_BUT1 , RGB(255, 255, 0) , IDB_BITMAP_TC_BUT2 , RGB(255, 255, 255) );
	m_rBtnCancel.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
	m_rBtnCancel.SetWindowText(_T("ȡ��")) ;
	
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	m_rBtnCancel.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
	m_rBtnCancel.SizeToContent();

	GetDlgItem(IDC_LABEL)->SetWindowText(_T("��ǩ:"));
	GetDlgItem(IDC_ADDR)->SetWindowText(_T("��ַ:"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CNewSendAddr::OnBnClickedClose()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CBaseDlg::OnCancel();
}


void CNewSendAddr::OnBnClickedCancel()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CBaseDlg::OnCancel();
}