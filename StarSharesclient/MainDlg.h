#pragma once
#include "HyperLink.h"
#include "statictrans.h"


// CMainDlg

class CMainDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg();
	virtual ~CMainDlg();

//对话框数据
	enum {IDD = IDD_DIALOG_MAIN };

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	HBITMAP		     m_pBmp; 
	CStaticTrans     m_strBalance;			//余额
	CStaticTrans     m_strConfirming;		//正在确认
	CStaticTrans     m_strTransactionNumber; //交易笔数

	//CStaticTrans	 m_strRecentTrade1;
	//CStaticTrans	 m_strRecentTrade2;
	//CStaticTrans	 m_strRecentTrade3;
	//CStaticTrans	 m_strRecentTrade4;

	CStaticTrans     m_strSrcAddr1;       //最近交易1源地址   
	CStaticTrans     m_strSrcAddr2;       //最近交易2源地址
	CStaticTrans     m_strSrcAddr3;       //最近交易3源地址
	//CStaticTrans     m_strSrcAddr4;       //最近交易4源地址


	CStaticTrans     m_strAmount1;        //最近交易1转账金额   
	CStaticTrans     m_strAmount2;        //最近交易2转账金额
	CStaticTrans     m_strAmount3;        //最近交易3转账金额
	//CStaticTrans     m_strAmount4;        //最近交易4转账金额


	CStaticTrans     m_strDesAddr1;       //最近交易1目的地址    
	CStaticTrans     m_strDesAddr2;       //最近交易2目的地址    
	CStaticTrans     m_strDesAddr3;       //最近交易3目的地址    
	//CStaticTrans     m_strDesAddr4;       //最近交易4目的地址    


	CHyperLink    m_vlinkCtrl1;         //社区动态超链接1
	CHyperLink    m_vlinkCtrl2;         //社区动态超链接2
	CHyperLink    m_vlinkCtrl3;         //社区动态超链接3
	CHyperLink    m_vlinkCtrl4;		    //社区动态超链接4
	CHyperLink    *m_vlinkCtrlQQ;        //官方客服QQ超链接
	CHyperLink    *m_vlinkCtrlBlock;     //官方区块浏览器

	CRoundButton     m_rBtnTxdetail;    //全部交易详情按钮
	CRoundButton     m_rBtnMoreInfo;

	CRoundButton			 m_btnUnit;
	CRoundButton          m_btnCommunity;

	map<CString, CString> m_mapUrl;     //社区动态URL链接

	//CStatic          m_stWalletSync;    //钱包尚未同步标志

public:
	void  SetBkBmpNid( UINT nBitmapIn );
	void  ClearCtrlText();				//清空所有控件数据
	void  InitializeLinkCtrl();			//初始化链接控件
	bool  GetUrlServer();
	void  OnBnClickedTxDetail();         //响应点击查看全部交易详情按钮
	LRESULT OnShowListCtrl(WPARAM wParam, LPARAM lParam);  //处理更新首页空间控件数据的消息
	void SetCtrlText();                  //重新设置各控件的数据
	void OnInitialCtrlText();            //初始化所有控件数据

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnMoreInfo();
	
};



