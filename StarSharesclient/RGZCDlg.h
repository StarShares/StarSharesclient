#pragma once
#include "RollDlg.h"
#include "listctrlcl.h"

// CRGZCDlg �Ի���
#define TIMER_ASSETBUY 1009

class CRGZCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRGZCDlg)

public:
	CRGZCDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRGZCDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_RGZC };

public:
	HBITMAP				m_pBmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	void SetBkBmpNid( UINT nBitmapIn );
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:

	CRollDlg *m_pRollDlg;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// //�ѹ��ʲ��б�
	CListCtrlCl m_lstBoughtAsset;
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	string		 m_rpcPort;                //RPC�˿�
	string		 m_sendPreHeadstr;         //����RPC�����ͷ
	string		 m_sendEndHeadstr;         //����RPC�����β
	string       m_severIp;                //����Զ�̷�����IP
	string       m_rpcUser;                //RPC�����û�����Զ�̷���ʱ��Ҫ��
	string       m_rpcPassWord;			   //RPC��������(Զ�̷���ʱ��Ҫ)


public:
	LRESULT OnShowListCtrl(  WPARAM wParam, LPARAM lParam );
	void  OninitializeList();
	void  ShowComboxCotent();
	void  OnShowListCtrl(uistruct::BOUGHTASSETLIST pListInfo);

	uistruct::ASSETLIST m_AllAssetList;			//������Ӧ�ʲ��Ϲ�ID�б�

	string GetConditonStr(int &operate);

	uistruct::BOUGHTASSETLIST m_bougthAssetList;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
