#pragma once

#include "afxwin.h"
#include "StaticPic.h"
#include "circleprogressctl.h"
#include   <dwmapi.h> 
#include "vedit.h"
#include "roundbutton.h"
#include "statictrans.h"
#include "ycombox.h"
#pragma comment (lib , "dwmapi.lib" ) 

// CShowPageDlg 对话框

class CShowPageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowPageDlg)

public:
	CShowPageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowPageDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOWPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_brush;

public:
	HBITMAP		     m_pBmp; 

public:
	virtual BOOL OnInitDialog();
	void SetCtrlFocus();
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//CStatic m_staEdge;
	CStaticPic m_staPic;
	CRect m_rcOrigPic;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CCircleProgressCtl m_staProgress;
	void SetBkBmpNid( UINT nBitmapIn );

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// //支持的人气星数量
	//CVEdit m_editSupport;
	// //确认支付
	CShadeButtonST m_rBtnConfirmed;
	afx_msg void OnBnClickedBtnPayConfirm();

public:
	uistruct::LISTADDR_t m_AddrMaxInfo;

public:
	void ActAssetAddr(string &strAssetAddr);
//	afx_msg void OnPaint();
//	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnChangeEditSupport();
	// 资产名称
	CStaticTrans m_stAssetName;
	// 发行方
	CStaticTrans m_stIssuer;
	// 众筹上限
	CStaticTrans m_stMax;
	// 众筹下限
	CStaticTrans m_stMin;
	// 发行日期
	CStaticTrans m_stDate;
	// 剩余天数
	CStaticTrans m_stDay;

	CStaticTrans m_stNum;
	CYComBox m_combBuy;
	afx_msg void OnCbnSelchangeComboSupport();
	CStaticTrans m_staAmount;
};
