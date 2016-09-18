#pragma once


// CRollDlg 对话框
#include "StarSharesclient.h"
#include <vector>
#include "afxwin.h"
#include "roundbutton.h"
using namespace std;

class CShowPageDlg;


class CRollDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRollDlg)

public:
	CRollDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRollDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SLIDE };

public:
	//vector<CShowPageDlg*> vecDlg;
	CShowPageDlg *m_pShowPageDlg;
	CRect m_rcOrig;
	CRect m_rcRegion;

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void LayoutDlg(int nCurIndex);
	void InitLayout(int nShowNum);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();

public:
	void SetBkBmpNid( UINT nBitmapIn );
public:
	HBITMAP				m_pBmp;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CRoundButton m_btnPrev;
	CRoundButton m_btnNext;
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:

	afx_msg void OnClose();

public:
	string       m_uiWebPort;                 //接受Web服务器推送消息端口
	string       m_severWebIp;                //访问Web服务器IP
	SOCKET       m_uiConnSocket;			  //UI与Web服务器端通讯socket
	CNoUiMsgBuffer m_noUiMsgBuffer;			  //接收服务端消息


	UINT         m_uReceiveWebThreadId;									//接收消息线程ID
	HANDLE       m_hReceiveWebThread;									//接收消息线程句柄
	//void		 StartWorkThread();										//启动数据处理线程
	//static UINT __stdcall ReceiveMessageFromWebServer(LPVOID pParam);   //接收消息从Web服务端

	uistruct::ASSETLIST m_VecAssetList;			//索引对应资产认购ID列表
	uistruct::ASSETPARAMLIST m_VecAssetParamList;	//
	int m_nCurAssetIndex;						//当前资产索引

public:
	void ClearControl();
	void RefreshCurPage();								//同步网站当前最新数据
};
