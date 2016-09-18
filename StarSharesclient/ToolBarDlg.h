#pragma once
#include "MainDlg.h"		
#include "PayDlg.h"
#include "RecvDlg.h"
#include "TXDetailDlg.h"
#include "AppsDlg.h"
#include "SetDlg.h"
#include "roundbutton.h"


// CToolBarDlg

class CToolBarDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CToolBarDlg)

public:
	CToolBarDlg();
	virtual ~CToolBarDlg();

//对话框数据
	enum {IDD = IDD_DIALOG_TOOLBAR};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

public:
	HBITMAP				m_pBmp;
public:
	CRoundButton     m_rBtnMain;
	CRoundButton	 m_rBtnSend; 
	CRoundButton     m_rBtnRece;
	CRoundButton     m_rBtnDeal;
	CRoundButton     m_rBtnApp;
	CRoundButton     m_rBtnSet;
	CRoundButton     m_rBtnClose;
	CRoundButton     m_rBtnMin;
public:
	UINT             m_nButtonID                   ; //当前点击的button
	void             MobileTip(UINT nButtonID , BOOL bFlag );

	void          InitBtStatus(UINT nButtonID); //原先按钮状态归为初始状态
public:
	afx_msg LRESULT OnShowStateTip(  WPARAM wParam	, LPARAM lParam ) ;
public:
	void		  SetBkBmpNid( UINT nBitmapIn ) ;
	afx_msg BOOL  OnEraseBkgnd(CDC* pDC);
	afx_msg int   OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void  OnSize(UINT nType, int cx, int cy);
	virtual BOOL  Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};



