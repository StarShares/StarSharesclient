#pragma once
#include "YYYEDlg.h"
#include "RGZCDlg.h"
#include "WDZCDlg.h"
#include "roundbutton.h"
#include "ZCInDlg.h"
#include "ZCOutDlg.h"


// CAppsDlg


class CAppsDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CAppsDlg)

public:
	CAppsDlg();
	virtual ~CAppsDlg();

//对话框数据
	enum {IDD = IDD_DIALOG_APPS};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

public:
	HBITMAP				m_pBmp;

public:
	CRoundButton     m_rBtnYYYE;
	//CRoundButton     m_rBtnFXZC;
	CRoundButton     m_rBtnRGZC;
	CRoundButton	 m_rBtnWDZC;


	CYYYEDlg		 *m_pYYYEBar;
	CRGZCDlg		 *m_pRGZCBar;
	CWDZCDlg		 *m_pWDZCBar;
	CZCInDlg		 *m_pZCInBar;
	CZCOutDlg		 *m_pZCOutBar;

public:
	UINT			m_nButtonID;							//当前点击的Button
	void			MobileTip(UINT nButtonID, BOOL bFlag);
	void            InitBtStatus(UINT nButtonID);

public:
	void  ActiveDlg(UINT nDlgID);

public:
	void		  SetBkBmpNid( UINT nBitmapIn ) ;
	afx_msg BOOL  OnEraseBkgnd(CDC* pDC);
	afx_msg int   OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void  OnSize(UINT nType, int cx, int cy);
	virtual BOOL  Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnYyye();
	afx_msg void OnBnClickedBtnFxzc();
	afx_msg void OnBnClickedBtnRgzc();
	
	afx_msg void OnBnClickedBtnWdzc();

	afx_msg LRESULT OnInBackToMyAssert(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnOutBackToMyAssert(WPARAM wParam, LPARAM lParam); 
};



