#pragma once
#include "RollDlg.h"
#include "listctrlcl.h"

// CRGZCDlg 对话框

class CRGZCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRGZCDlg)

public:
	CRGZCDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRGZCDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_RGZC };

public:
	HBITMAP				m_pBmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	void SetBkBmpNid( UINT nBitmapIn );
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:

	CRollDlg *m_pRollDlg;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// //已购资产列表
	CListCtrlCl m_lstBoughtAsset;
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	string		 m_rpcPort;                //RPC端口
	string		 m_sendPreHeadstr;         //发送RPC命令报文头
	string		 m_sendEndHeadstr;         //发送RPC命令报文尾
	string       m_severIp;                //访问远程服务器IP
	string       m_rpcUser;                //RPC访问用户名（远程访问时需要）
	string       m_rpcPassWord;			   //RPC访问密码(远程访问时需要)


public:
	LRESULT OnShowListCtrl(  WPARAM wParam, LPARAM lParam );
	void  OninitializeList();
	void  ShowComboxCotent();
	void  OnShowListCtrl(uistruct::BOUGHTASSETLIST pListInfo);

	uistruct::ASSETLIST m_AllAssetList;			//索引对应资产认购ID列表

	string GetConditonStr(int &operate);

	uistruct::BOUGHTASSETLIST m_bougthAssetList;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
