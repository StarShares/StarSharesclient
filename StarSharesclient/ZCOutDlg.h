#pragma once
#include "roundbutton.h"
#include "vedit.h"
#include "YComBox.h"
#include "shadebuttonst.h"
#include "WDZCDlg.h"
#include "listctrlcl.h"


// CZCOutDlg 对话框
#define WM_OUTBACK_MYASSERT 1001

class CZCOutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZCOutDlg)

public:
	CZCOutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZCOutDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ZC_OUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();

public:
	void SetBkBmpNid( UINT nBitmapIn ) ;

public:
	HBITMAP				m_pBmp;
	CRoundButton m_rbtnWDZC;
	CRoundButton m_rBtnZCOut;
	CVEdit m_veditPopOut;
	CVEdit m_veditDestAddr;
	CYComBox		   m_ycomAsset;
	CShadeButtonST m_sBtnOut;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnMyAsset();
	CListCtrlCl m_lstOutDetail;

public:
	map<string,uistruct::LISTMYASSET_t> m_mapAssetInfo;

public:
	LRESULT OnCopyAcct(WPARAM wParam, LPARAM lParam);
	BOOL AddListaddrDataBox();
	afx_msg void OnBnClickedBtnOut();
	void ActAssetAddr(string &strAssetAddr);

	//默认资产
	string m_strCurAsset;

public:
	void InitCombox();

	map<string,LISTASSET_t> m_MapMyAssetList;			//索引对应已发行资产ID列表
	afx_msg void OnCbnSelchangeComboAssetSelect();
	string m_appid;
	string GetAppID(string AppName);

	LRESULT  OnShowListCtrl(  WPARAM wParam, LPARAM lParam );

	void  OninitializeList();
	void  ShowComboxCotent();

	void  OnShowListCtrl(uistruct::ASSETDEALLIST pListInfo);

public:
	LRESULT OnShowListaddrData( WPARAM wParam, LPARAM lParam );
	map<string,uistruct::LISTADDR_t> m_mapAddrInfo;
};
