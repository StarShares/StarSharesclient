#pragma once
#include "shadebuttonst.h"
#include "listctrlcl.h"
#include "ycombox.h"
#include "RollDlg.h"


// CWDZCDlg �Ի���
#define  USE_TOPINDEX_BUTTON

class CWDZCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWDZCDlg)

public:
	CWDZCDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWDZCDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_WDZC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	HBITMAP				m_pBmp;

public:
	void SetBkBmpNid( UINT nBitmapIn );
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	CShadeButtonST m_sBtnZCIn;
	CShadeButtonST m_sBtnExportExcel;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnZcIn();
	CListCtrlCl m_lstWDZC;

	LRESULT OnOutAsset(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButExeclExport();
	CYComBox m_ycomboAsset;
	afx_msg void OnBnClickedBtnSearch();
	CShadeButtonST m_sbtnSearch;

	void InitCombox();

	void OnShowListCtrol(string appId);

public:
	string m_appid;
	string GetAppID(string AppName);

	afx_msg void OnCbnSelchangeComboAssetlist();

public:
	map<string,LISTASSET_t> m_MapMyAssetList;			//������Ӧ�ѷ����ʲ�ID�б�

	static int m_coulum;
	static int m_index;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
