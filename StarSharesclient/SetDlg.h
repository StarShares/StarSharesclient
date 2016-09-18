#pragma once


// CSetDlg

class CSetDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg();
	virtual ~CSetDlg();

//对话框数据
	enum {IDD = IDD_DIALOG_SET};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HBITMAP		     m_pBmp; 
public:
	CShadeButtonST         m_rBtnRpc;
	CShadeButtonST         m_rBtnQbjm;
	CShadeButtonST         m_rBtnXgmm;
	CShadeButtonST         m_rBtnQbsd;
	CShadeButtonST         m_rBtnQbbf;
	CShadeButtonST         m_rBtnDcsy;
	CShadeButtonST         m_rBtnDrsy;
	CShadeButtonST         m_rBtnSzyyid;
	CShadeButtonST         m_rBtnFfmrsz;
	CShadeButtonST         m_rBtnGbts;
public:
	void SetBkBmpNid( UINT nBitmapIn ) ;
	bool GetFileName(CString &fileName,CString strexe );
	void AddImportWalletAndBookAddr(CString fileName);
	void WriteExportWalletAndBookAddr(CString fileName);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	afx_msg void OnBnClickedButtonPrc();				//rpc命令
	afx_msg void OnBnClickedButtonQbjm();				//钱包加密
	afx_msg void OnBnClickedButtonXgmm();				//修改密码
	afx_msg void OnBnClickedButtonQbsd();				//钱包锁定
	afx_msg void OnBnClickedButtonQbbf();				//钱包备份
	afx_msg void OnBnClickedButtonDcsy();				//导出私钥
	afx_msg void OnBnClickedButtonDrsy();				//导入私钥
	afx_msg void OnBnClickedButtonHfmrsz();				//恢复默认设置
	afx_msg void OnBnClickedButtonGbts();				//关闭提示
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


