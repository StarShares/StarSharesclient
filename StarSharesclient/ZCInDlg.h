#pragma once
#include "buttonex.h"
#include "roundbutton.h"
#include "VEdit.h"
#include "YComBox.h"
#include "shadebuttonst.h"
#include "WDZCDlg.h"
#include "listctrlcl.h"
#include "NewAddressDlg.h"


// CZCInDlg �Ի���
#define WM_INBACK_MYASSERT	1001
#define TIMER_RECVTRANSTION 1009

class CZCInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZCInDlg)

public:
	CZCInDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZCInDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ZC_IN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void SetBkBmpNid( UINT nBitmapIn );

public:
	HBITMAP				m_pBmp;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	// ��ť��������ҵ��ʲ�

	CRoundButton m_btnWDZCEx;
	CRoundButton m_rBtnZCIn;

public:
	afx_msg void OnBnClickedBtnWozc();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnBnClickedBtnInTrade();
	//CVEdit m_veditZCName;
	CVEdit m_veditRecvAddr;
	CYComBox		m_ycomInAsset;
	CShadeButtonST	m_sBtnInTrade;
	CListCtrlCl		m_lstInDetail;

public:
	map<string,uistruct::LISTMYASSET_t> m_mapAssetInfo;
	

public:
	LRESULT OnCopyAcct(WPARAM wParam, LPARAM lParam);
	// ��ȡ�����˺�
	CShadeButtonST m_sBtnRecvAddr;
	afx_msg void OnBnClickedBtnNewaddr();
	BOOL AddListaddrDataBox();

public:
	void InitCombox();
	map<string,LISTASSET_t> m_MapMyAssetList;			//������Ӧ�ѷ����ʲ�ID�б�
	string GetAppID(string AppName);
	string m_appid;
	
	afx_msg void OnCbnSelchangeComboWozc();

	BOOL bExist;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	LRESULT  OnShowListCtrl(  WPARAM wParam, LPARAM lParam );
	void  OnShowListCtrl(uistruct::ASSETDEALLIST pListInfo);
	void  OninitializeList();
	void  ShowComboxCotent();
	LRESULT OnShowListaddrData( WPARAM wParam, LPARAM lParam );
	map<string,uistruct::LISTADDR_t> m_mapAddrInfo;
};
