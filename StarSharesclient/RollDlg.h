#pragma once


// CRollDlg �Ի���
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
	CRollDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRollDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SLIDE };

public:
	//vector<CShowPageDlg*> vecDlg;
	CShowPageDlg *m_pShowPageDlg;
	CRect m_rcOrig;
	CRect m_rcRegion;

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	string       m_uiWebPort;                 //����Web������������Ϣ�˿�
	string       m_severWebIp;                //����Web������IP
	SOCKET       m_uiConnSocket;			  //UI��Web��������ͨѶsocket
	CNoUiMsgBuffer m_noUiMsgBuffer;			  //���շ������Ϣ


	UINT         m_uReceiveWebThreadId;									//������Ϣ�߳�ID
	HANDLE       m_hReceiveWebThread;									//������Ϣ�߳̾��
	//void		 StartWorkThread();										//�������ݴ����߳�
	//static UINT __stdcall ReceiveMessageFromWebServer(LPVOID pParam);   //������Ϣ��Web�����

	uistruct::ASSETLIST m_VecAssetList;			//������Ӧ�ʲ��Ϲ�ID�б�
	uistruct::ASSETPARAMLIST m_VecAssetParamList;	//
	int m_nCurAssetIndex;						//��ǰ�ʲ�����

public:
	void ClearControl();
	void RefreshCurPage();								//ͬ����վ��ǰ��������
};
