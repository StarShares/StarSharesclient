#pragma once


// CTXDetailDlg
#include "CJFlatComboBox.h"
#include "listctrlcl.h"
#include "VEdit.h"
#include "ycombox.h"

class CTXDetailDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CTXDetailDlg)

public:
	CTXDetailDlg();
	virtual ~CTXDetailDlg();

//对话框数据
	enum {IDD = IDD_DIALOG_SHOWTXDETAIL};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HBITMAP		     m_pBmp; 
public:
	CListCtrlCl				m_listCtrl;
	
	CShadeButtonST			m_rBtnSearch;
	
	CYComBox				m_condition;
	CYComBox				m_time;
	CVEdit					m_editAddr;		    
	COLORREF				m_colorEditText;
	bool					m_seteditcolor;
	uistruct::TRANSRECORDLIST m_pListInfo ;

public:
	void SetBkBmpNid( UINT nBitmapIn ) ;
	void  OninitializeList();
	void  ShowComboxCotent();
	string GetConditonStr(int &operate);
	string GetConditonTxType(int &operate);
	string GetConditonTime();
	string Getaddr();
	void OnShowListCtrl(uistruct::TRANSRECORDLIST pListInfo);
	void ShowAddrConditon();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	afx_msg void OnCbnSelchangeComboTime();
	afx_msg void OnCbnSelchangeCombo1();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnShowListCtrl(  WPARAM wParam, LPARAM lParam ) ;
	afx_msg void OnBnClickedButtonSearch();
	CListCtrlCl m_lstApp;
};


