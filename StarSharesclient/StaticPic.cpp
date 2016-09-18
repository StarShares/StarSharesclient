// StaticPic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StarSharesclient.h"
#include "StaticPic.h"


// CStaticPic

IMPLEMENT_DYNAMIC(CStaticPic, CStatic)

CStaticPic::CStaticPic()
{
	m_pStmImage = NULL;
	m_hMem = NULL;
}

CStaticPic::~CStaticPic()
{
}


BEGIN_MESSAGE_MAP(CStaticPic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CStaticPic ��Ϣ�������

void CStaticPic::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(rc);

	dc.FillSolidRect(&rc, RGB(255, 255, 255));
	if(NULL != m_pStmImage)
	{
		Graphics graphics(dc);
		Image image(m_pStmImage);

		int snapShotVisibleWidth = m_WndImageRect.right-m_WndImageRect.left;
		int snapShotVisibleHeight = m_WndImageRect.bottom-m_WndImageRect.top;
		graphics.DrawImage(&image, 0, 0,150,210);
	}
}

BOOL CStaticPic::DownloadServerFile( LPCTSTR url )
{
	
	if(NULL != m_pStmImage)
	{
		HGLOBAL hTemp = GlobalFree(m_hMem);
		m_pStmImage->Release();
		m_pStmImage = NULL;
	}
	if(IsWindow(m_hWnd))  
	{  
		GetClientRect(&m_WndImageRect);
		  
		DWORD dwLen=0;  
		BOOL ret = FALSE;  
		CInternetSession Sess(_T("lpload"));
		Sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT     , 5000); //5������ӳ�ʱ
		Sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT        , 5000); //5��ķ��ͳ�ʱ
		Sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT     , 5000); //5��Ľ��ճ�ʱ
		Sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT   , 5000); //5��ķ��ͳ�ʱ
		Sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 5000); //5��Ľ��ճ�ʱ
		DWORD dwFlag = INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD ;

		CHttpFile* cFile   = NULL;
		int        nBufLen = 0   ;
		char *pData = NULL;

		do {
			try{
				cFile = (CHttpFile*)Sess.OpenURL((CString)url,1,dwFlag);
				DWORD dwStatusCode;
				cFile->QueryInfoStatusCode(dwStatusCode); 
				if (dwStatusCode == HTTP_STATUS_OK) {

					DWORD nLen=0;
					cFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, nLen);
					if (nLen <= 0) break;
					m_hMem=GlobalAlloc(GMEM_MOVEABLE, nLen); 
					char szBuf[RECVPACK_SIZE] = {0};
					if(m_hMem)  
					{  
						pData = (char *)GlobalLock(m_hMem);
						nBufLen = nLen;
						int dwReaded = 0;

						while (nLen>0) 
						{
							DWORD dwReaded=0; 
							if(pData)  
							{  

								dwReaded = cFile->Read(szBuf,(nLen<RECVPACK_SIZE)?nLen:RECVPACK_SIZE);
								memcpy(pData, szBuf, dwReaded); 
								pData += dwReaded;
							}  

							if (dwReaded <= 0)
							{
								break;
							}
							nLen -= dwReaded ; //ʣ�೤�ȵݼ�

						}
						GlobalUnlock(m_hMem);
						CreateStreamOnHGlobal(m_hMem, TRUE, &m_pStmImage);
						break;
					}
				}
			} catch(...) {
				break;
			}

		} while(0);

		if (cFile) {
			cFile->Close();
			delete cFile;  
			Sess.Close();
		}

	}

	Invalidate();

	return 0;
}


BOOL CStaticPic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	CWnd::OnEraseBkgnd(pDC);

	return 1;
}

