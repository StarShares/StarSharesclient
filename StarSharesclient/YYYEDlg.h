#pragma once
#include "listctrlcl.h"
#include "shadebuttonst.h"
#include "cjflatcombobox.h"
#include "VEdit.h"
#include "YComBox.h"


// CYYYEDlg

class CYYYEDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYYYEDlg)

public:
	CYYYEDlg(CWnd* pParent = NULL);
	virtual ~CYYYEDlg();

	enum {IDD = IDD_DIALOG_YYYE};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

public:
	HBITMAP				m_pBmp;

public:
	virtual BOOL OnInitDialog();

public:
	void SetBkBmpNid( UINT nBitmapIn );
	double GetFreeMoney(CString addr);
	void OnShowListCtrol(CString addr);
	string GetAppID(string AppName);
	void InitCombox();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	

	

public:
	CListCtrlCl m_lstApp;
	CShadeButtonST m_rBtnDraw;
	CShadeButtonST m_rBtnSelect;
	CYComBox m_combApp;
	CVEdit		 m_editAcct;

public:
	string             m_appid;
	CP2PBetHelp		   m_P2PBetHelp;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnExtract();
	afx_msg void OnCbnSelchangeComboAppid();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};


