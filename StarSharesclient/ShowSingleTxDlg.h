#pragma once
#include "BaseDlg.h"
#include "StaticTrans.h"
#include "BmpBtn.h"
#include "ShadeButtonST.h"

// CShowSingleTxDlg �Ի���

class CShowSingleTxDlg : public CBaseDlg
{
	DECLARE_DYNAMIC(CShowSingleTxDlg)

public:
	CShowSingleTxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowSingleTxDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOW_SINGLETX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void ShowTxDetail(CString jsontx);
	string GetContacrDetail(uistruct::REVTRANSACTION_t tx);
	virtual BOOL OnInitDialog();

public:

	CStaticTrans     m_headText;
	CShadeButtonST   m_rBtnClose;
	CShadeButtonST   m_rBtnOk;
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
