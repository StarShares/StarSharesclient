#pragma once


// CBaseDlg �Ի���

class CBaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseDlg)

public:
	CBaseDlg(UINT ID,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	CFont            m_fontGrid;//�������
	HBITMAP		     m_HeadBmp; 
	HBITMAP           m_pBmp;
	void		     SetBkBmpNid( UINT nBitmapIn ,HBITMAP &bmp) ;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};

