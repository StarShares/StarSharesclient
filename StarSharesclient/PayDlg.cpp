// PayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "PayDlg.h"
#include "AddrBook.h"
#include "afxdialogex.h"


// CPayDlg

IMPLEMENT_DYNAMIC(CPayDlg, CDialogBar)

CPayDlg::CPayDlg()
{
	m_pBmp = NULL;
}

CPayDlg::~CPayDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}


void CPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PAY , m_rBtnSend);
	DDX_Control(pDX, IDC_STATIC_XM , m_strTx1);
	DDX_Control(pDX, IDC_COMBO_PAY_ADDRESS , m_addrbook);
	DDX_Control(pDX, IDC_BUTTON_SELECT , m_rBtnAddbook);
	DDX_Control(pDX, IDC_STATIC_UNIT , m_strTxUnit);

	DDX_Control(pDX, IDC_EDIT_AIM_ADDRESS, m_editRecvAddr);
	DDX_Control(pDX, IDC_EDIT_LABEL, m_editLabel);
	DDX_Control(pDX, IDC_EDIT_MONEY, m_editMoney);
}

BEGIN_MESSAGE_MAP(CPayDlg, CDialogBar)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CPayDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_PAY, &CPayDlg::OnBnClickedButtonSend)
	ON_CBN_SELCHANGE(IDC_COMBO_PAY_ADDRESS, &CPayDlg::OnCbnSelchangeComboPayAddress)
	ON_MESSAGE(MSG_USER_SEND_UI , &CPayDlg::OnShowListaddrData  )
END_MESSAGE_MAP()



// CPayDlg ��Ϣ�������
void CPayDlg::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CPayDlg::OnEraseBkgnd(CDC* pDC)
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

	return 1;
}


int CPayDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetBkBmpNid( IDB_BITMAP_PAY_BLACK ) ;
	return 0;
}


void CPayDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if( NULL != GetSafeHwnd() ) {
		CRect rect ; 
		this->GetWindowRect(rect);

		CWnd *pst = GetDlgItem( IDC_STATIC_XM ) ;
		if ( NULL != pst ) {
		pst->GetClientRect( rect ) ;
		pst->SetWindowPos( NULL ,  320 + 270 + 50 , 83 , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_EDIT_AIM_ADDRESS ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,270 , 130, 320, 40  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_BUTTON_SELECT ) ;
		if ( NULL != pst ) {
			pst->GetWindowRect( rect ) ;
			pst->SetWindowPos( NULL ,260 + 335  , 133 , rect.Width(), rect.Height(),SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_EDIT_LABEL ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,270 , 190 , 320, 40  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_EDIT_MONEY ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,270 , 250 , 268, 40  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_STATIC_UNIT ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,538 , 250 , 50, 40 ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_BUTTON_PAY ) ;
		if ( NULL != pst ) {
			pst->GetWindowRect(rect);
			pst->SetWindowPos( NULL ,270 , 340 , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
	}
}


BOOL CPayDlg::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL bRes = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if ( bRes ){

		m_rBtnAddbook.LoadBitmaps(IDB_BITMAP_ADDBOOK,IDB_BITMAP_ADDBOOK,IDB_BITMAP_ADDBOOK,IDB_BITMAP_ADDBOOK);
		UpdateData(0);
		m_strTx1.SetFont(100, _T("΢���ź�"));				//������ʾ����ʹ�С
		m_strTx1.SetTextColor(RGB(184, 39, 18));
		m_strTx1.SetWindowText(_T(""));
		AddListaddrDataBox();

		UpdateData(FALSE);
		m_rBtnSend.SetBitmaps( IDB_BITMAP_BUT2 , RGB(255, 255, 255) , IDB_BITMAP_BUT1 , RGB(255, 255, 255) );
		m_rBtnSend.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnSend.SetWindowText("����") ;
		m_rBtnSend.SetFontEx(-12 , _T("΢���ź�"));
		m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
		m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(255,255,255));
		m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
		m_rBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
		m_rBtnSend.SizeToContent();

		m_editRecvAddr.SetNewFont(100);
		m_editRecvAddr.SetTextColor(RGB(121, 122, 122));
		m_editRecvAddr.SetBkColor(RGB(238,238,238));


		m_editLabel.SetNewFont(100);
		m_editLabel.SetTextColor(RGB(121, 122, 122));
		m_editLabel.SetBkColor(RGB(238,238,238));


		m_editMoney.SetNewFont(100);
		m_editMoney.SetTextColor(RGB(121, 122, 122));
		m_editMoney.SetBkColor(RGB(238,238,238));

		CRect rect;
		m_addrbook.GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_addrbook.MoveWindow(270 , 80, 320, rect.Height());	
		m_addrbook.SetEdtNewFont(100);
		m_addrbook.SetListNewFont(100);
		m_addrbook.SetEdtTextColor(RGB(121, 122, 122));
		m_addrbook.SetListTextColor(RGB(118, 192, 50));
		//m_addrbook.SetEdtTextBgColor(RGB(238,238,238));
		//m_YCombox1.SetItemHeight(-1, 50); // ���ô˺�����༭��߶ȣ��������������Զ�����
		m_addrbook.SetItemHeight(1, 35);
		m_addrbook.AotuAdjustDroppedWidth();
		m_addrbook.SetEdtFrameColor(RGB(238,238,238));
		m_addrbook.SetFrameStyle(CYComBox::ONLYONE);

		m_strTxUnit.SetTextColor(RGB(121, 122, 122));
		m_strTxUnit.SetBackColor(RGB(238,238,238));
		m_strTxUnit.SetFont(100, _T("΢���ź�"));
		m_strTxUnit.ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);

		theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_SEND_UI ) ;
		GetDlgItem(IDC_STATIC_UNIT)->SetWindowText("STS");
	}
	return bRes ;
}

BOOL CPayDlg::AddListaddrDataBox(){

	theApp.m_SqliteDeal.GetWalletAddressList(_T(" 1=1 "), &m_mapAddrInfo);

	if ( 0 == m_mapAddrInfo.size() ) return FALSE ;

	//���ComBox�ؼ�
	((CComboBox*)GetDlgItem(IDC_COMBO_PAY_ADDRESS))->ResetContent();
	//���ص�ComBox�ؼ�
	int nItem = 0;
	std::map<string,uistruct::LISTADDR_t>::const_iterator const_it;
	for ( const_it = m_mapAddrInfo.begin() ; const_it != m_mapAddrInfo.end() ; const_it++ ) {

		((CComboBox*)GetDlgItem(IDC_COMBO_PAY_ADDRESS))->InsertString(nItem , const_it->first.c_str() );
		//((CComboBox*)GetDlgItem(IDC_COMBO_ADDR_OUT))->SetItemData(nItem, (DWORD_PTR)&(*const_it));
		nItem++;
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_PAY_ADDRESS))->SetCurSel(0);

	CString address;
	int sel = m_addrbook.GetCurSel();
	if (sel < 0)
	{
		return FALSE;
	}
	m_addrbook.GetLBText(sel,address);
	string strAddr =strprintf("%s",address);
	std::map<string,uistruct::LISTADDR_t>::const_iterator item = m_mapAddrInfo.find(strAddr);

	if (m_mapAddrInfo.count(strAddr)>0 ) {
		uistruct::LISTADDR_t addrstruc = m_mapAddrInfo[strAddr];
		string strshow;
		strshow = strprintf("%.8f",addrstruc.fMoney);
		m_strTx1.SetWindowText(strshow.c_str());
		Invalidate();
	}
	return TRUE ;
}


void CPayDlg::OnBnClickedButtonSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAddrBook addrbook;
	INT_PTR nResponse = addrbook.DoModal();
	if (nResponse == IDOK)
	{
		uistruct::ADDRBOOK_t addr;
		addrbook.GetAddrbook(addr);
		GetDlgItem(IDC_EDIT_AIM_ADDRESS)->SetWindowTextA(addr.address.c_str());
		GetDlgItem(IDC_EDIT_LABEL)->SetWindowTextA(addr.label.c_str());
	}
}


BOOL CPayDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (pMsg->message==WM_KEYDOWN)
	{
		BOOL bCtrl=::GetKeyState(VK_CONTROL)&0x8000;
		BOOL bShift=::GetKeyState(VK_SHIFT)&0x8000;

		// only gets here if CTRL key is pressed
		BOOL bAlt=::GetKeyState(VK_MENU)&0x8000;

		if(pMsg->message == WM_KEYDOWN) 
		{  

			switch(pMsg->wParam) 
			{  

			case VK_RETURN: //�س�   
				return TRUE;  

			case VK_ESCAPE: //ESC  
				return TRUE;  

			}  

		}  

		switch( pMsg->wParam )
		{
			if (GetDlgItem(IDC_COMBO_PAY_ADDRESS)->SetFocus() == this->GetFocus())
			{
				int b = 6;
			}
		case 'V':
			{
				if (GetDlgItem(IDC_EDIT_AIM_ADDRESS) == this->GetFocus())
				{
					HWND hWnd = GetSafeHwnd(); // ��ȡ��ȫ���ھ��
					::OpenClipboard(hWnd); // �򿪼�����
					HANDLE hClipMemory = ::GetClipboardData(CF_TEXT);// ��ȡ���������ݾ��
					DWORD dwLength = GlobalSize(hClipMemory); // ����ָ���ڴ�����ĵ�ǰ��С
					LPBYTE lpClipMemory = (LPBYTE)GlobalLock(hClipMemory); // �����ڴ�
					CString message = CString(lpClipMemory); // ����õ����ı�����
					GlobalUnlock(hClipMemory); // �ڴ����
					::CloseClipboard(); // �رռ�����
					if (bCtrl)
					{
						uistruct::ADDRBOOK_t addrBook;
						string strCond;
						strCond = strprintf(" address='%s' ", message);
						int nItem =  theApp.m_SqliteDeal.GetAddressBookItem( strCond, &addrBook) ;
						if (addrBook.label != _T(""))
						{
							GetDlgItem(IDC_EDIT_LABEL)->SetWindowText(addrBook.label.c_str());
						}

					}

				}else if (GetDlgItem(IDC_COMBO_PAY_ADDRESS)->SetFocus() == this->GetFocus())
				{
					HWND hWnd = GetSafeHwnd(); // ��ȡ��ȫ���ھ��
					::OpenClipboard(hWnd); // �򿪼�����
					HANDLE hClipMemory = ::GetClipboardData(CF_TEXT);// ��ȡ���������ݾ��
					DWORD dwLength = GlobalSize(hClipMemory); // ����ָ���ڴ�����ĵ�ǰ��С
					LPBYTE lpClipMemory = (LPBYTE)GlobalLock(hClipMemory); // �����ڴ�
					CString message = CString(lpClipMemory); // ����õ����ı�����
					GlobalUnlock(hClipMemory); // �ڴ����
					::CloseClipboard(); // �رռ�����
					if (bCtrl)
					{
						string addr = strprintf("%s",message);
						if(m_mapAddrInfo.count(addr)<=0)
						{
							MessageBox(_T("���Ƶĵ�ַ����"),_T("��ʾ"), MB_OK);
							//UiFun::MessageBoxEx(UiFun::UI_LoadString("SEND_MODULE" , "SEND_SOPY_ADDR_ERROR" ,theApp.gsLanguage) , UiFun::UI_LoadString("COMM_MODULE" , "COMM_TIP" ,theApp.gsLanguage) ,MFB_OK|MFB_TIP );
						}else{
							//uistruct::LISTADDR_t te = m_pListaddrInfo[text];
							CString strshow;
							strshow.Format(_T("%.8f"),m_mapAddrInfo[addr].fMoney);
							((CStatic*)GetDlgItem(IDC_STATIC_XM))->SetWindowText(strshow);
							Invalidate();
						}

					}
				}

			}
			break;
		}
	}

	return CDialogBar::PreTranslateMessage(pMsg);
}


void CPayDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (theApp.IsLockWallet())
	{
		return ;
	}

	if (m_mapAddrInfo.size() == 0)
	{
		UiFun::MessageBoxEx(_T("���͵�ַ������") , _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}
	CString text =_T("");
	m_addrbook.GetWindowText(text);
	if (text == _T(""))
	{
		UiFun::MessageBoxEx(_T("��ѡ���ַ��") , _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}
	uistruct::LISTADDR_t data;
	string strCommand  ;CString strMoney,strMaddress;
	string strShowData;
	if(text!=_T(""))
	{
		string strAddr =strprintf("%s",text);
		strAddr =UiFun::trimleft(strAddr);
		strAddr =UiFun::trimright(strAddr);
		if(m_mapAddrInfo.count(strAddr)<=0)
		{
			UiFun::MessageBoxEx(_T("���͵�ַ����Ǯ����ַ") , _T("��ʾ") ,MFB_OK|MFB_TIP );
			return;
		}
		data = m_mapAddrInfo[strAddr];

	}

	if(!data.bSign) 
	{
		UiFun::MessageBoxEx(_T("���͵�ַδ����") ,  _T("��ʾ"),MFB_OK|MFB_TIP );
		return;
	}

	GetDlgItem(IDC_EDIT_AIM_ADDRESS)->GetWindowTextA(strMaddress);
	if (strMaddress == _T(""))
	{
		UiFun::MessageBoxEx(_T("���ܵ�ַ����Ϊ��") , _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}
	if(!strcmp(strMaddress.GetString(), data.address.c_str()))
	{
		UiFun::MessageBoxEx(_T("���͵�ַ��Ŀ�ĵ�ַ������ͬ") , _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}

	GetDlgItem(IDC_EDIT_MONEY)->GetWindowTextA(strMoney);
	double dSendMoney = strtod(strMoney,NULL);
	if(dSendMoney > data.fMoney || ( data.fMoney>-0.0000001 && data.fMoney< 0.000001 )) 
	{
		UiFun::MessageBoxEx(_T("�˻�����") , _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}

	if(_T("") == strMoney.GetString() || (dSendMoney >-0.0000001 && dSendMoney< 0.000001))
	{
		UiFun::MessageBoxEx(_T("���ͽ���Ϊ0") ,_T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}

	if (!theApp.m_bIsSyncBlock )
	{
		UiFun::MessageBoxEx(_T("ͬ��δ���,���ܷ��ͽ���") , _T("��ʾ") ,MFB_OK|MFB_TIP );
		return;
	}

	//�ж�Ŀ�ĵ�ַ�Ƿ���Ч
	Json::Value root;

	strCommand = strprintf("%s %s", "validateaddress", strMaddress);
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
	{
		TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
		return;
	}

	strShowData = root["ret"].toStyledString();

	if( 0 ==  strncmp(strShowData.c_str(), "false", strlen("false")))
	{
		string strTip;
		strTip = "���յ�Ŀ�ĵ�ַ��Ч��";
		UiFun::MessageBoxEx(strTip.c_str(), _T("��ʾ") ,MFB_OK|MFB_TIP );

		return;
	}


	strCommand = strprintf("%s %s %s %lld","sendtoaddress" ,data.address.c_str() ,strMaddress ,REAL_MONEY(dSendMoney));

	CString strDisplay;
	strDisplay.Format(_T("%s%.4lfSTS%s%s"),_T("ת��"), dSendMoney, _T("��") ,strMaddress);

	if (IDCANCEL == UiFun::MessageBoxEx(strDisplay , _T("��ʾ") , MFB_OKCANCEL|MFB_TIP ) )
	{
		return;
	}

	strShowData = _T("");
	if(!CSoyPayHelp::getInstance()->SendRpc(strCommand,root))
	{
		TRACE("OnBnClickedSendtrnsfer rpccmd sendtoaddress error");
		return;
	}
	BOOL bRes = FALSE ;
	strShowData = root.toStyledString();
	int pos = strShowData.find("hash");
	if ( pos >=0 ) {
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
	}

	string strData;
	if ( pos >=0 ) {
		strData = strprintf(" %s\n\n %s:%s\n\n %s:%s\n\n %s��%.4lf\n  hash:%s",_T("ת�˽��׷��ͳɹ�"),_T("Դ��ַ"), data.address.c_str(),_T("Ŀ�ĵ�ַ"),strMaddress,_T("���"), dSendMoney,root["hash"].asCString()) ;
	}else{
		strData = _T("ת��ʧ��!");
	}
	UiFun::MessageBoxEx(strData.c_str() , _T("") ,MFB_OK|MFB_TIP );


	//// �������ݿ�,���տ�����ӵ���ַ��
	CString label;
	GetDlgItem(IDC_EDIT_LABEL)->GetWindowTextA(label);
	CPostMsg postmsg(MSG_USER_GET_UPDATABASE,WM_UP_ADDRBOOK);
	uistruct::ADDRBOOK_t addr;
	addr.address = strMaddress;
	addr.label = label;
	string temp =addr.ToJson();
	postmsg.SetData(temp);
	theApp.m_msgQueue.push(postmsg);

}


void CPayDlg::OnCbnSelchangeComboPayAddress()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_mapAddrInfo.size() == 0)
	{
		return;
	}
	CString text;
	int sel = m_addrbook.GetCurSel();
	if (sel < 0)
	{
		return ;
	}
	m_addrbook.GetLBText(sel,text);

	//m_addrbook.GetWindowText(text) ;
	string strAddr= strprintf("%s",text);
	if(text!=_T(""))
	{

		if(m_mapAddrInfo.count(strAddr)<=0)
		{
			TRACE("map OnCbnSelchangeCombo1 error");
			return;
		}
		//uistruct::LISTADDR_t te = m_pListaddrInfo[text];
		string strshow;
		strshow = strprintf("%.8f",m_mapAddrInfo[strAddr].fMoney);
		((CStatic*)GetDlgItem(IDC_STATIC_XM))->SetWindowText(strshow.c_str());
		Invalidate();
	}
}

void CPayDlg::ModifyComboxItem(){
	CPostMsg postmsg;
	if (!theApp.m_msgUISendDlgQueue.pop(postmsg))
	{
		return ;
	}

	uistruct::LISTADDR_t addr; 
	string strTemp = postmsg.GetData();
	addr.JsonToStruct(strTemp.c_str());


	if(m_mapAddrInfo.count(addr.address)<=0)
	{
		TRACE("map ModifyComboxItem error");
		return;
	}
	m_mapAddrInfo[addr.address]=addr;


}
void CPayDlg::InsertComboxIitem()
{
	CPostMsg postmsg;
	if (!theApp.m_msgUISendDlgQueue.pop(postmsg))
	{
		return ;
	}

	uistruct::LISTADDR_t addr; 
	string strTemp = postmsg.GetData();
	addr.JsonToStruct(strTemp.c_str());


	if(m_mapAddrInfo.count(addr.address)>0)
	{
		TRACE("map InsertComboxIitem error");
		return;
	}
	m_mapAddrInfo[addr.address]=addr;

	int item = m_addrbook.GetCount();
	m_addrbook.InsertString(item,addr.address.c_str());
}

LRESULT CPayDlg::OnShowListaddrData( WPARAM wParam, LPARAM lParam ) 
{
	//��������
	int type = (int)wParam;
	switch(type)
	{
	case WM_UP_ADDRESS:
		{
			ModifyComboxItem();
			OnCbnSelchangeComboPayAddress();
			break;
		}
		break;
	case WM_UP_NEWADDRESS:
		{
			InsertComboxIitem();
			break;
		}
		break;
	default:
		break;

	}
	return 0 ;
}



