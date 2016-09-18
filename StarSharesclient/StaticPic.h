#pragma once


// CStaticPic
#define RECVPACK_SIZE 2048

class CStaticPic : public CStatic
{
	DECLARE_DYNAMIC(CStaticPic)

public:
	CStaticPic();
	virtual ~CStaticPic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:

	BOOL DownloadServerFile( LPCTSTR url );

	IStream *m_pStmImage;
	HGLOBAL m_hMem;
	CRect m_WndImageRect;

};


