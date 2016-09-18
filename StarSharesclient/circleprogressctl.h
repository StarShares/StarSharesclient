

#if !defined(AFX_MATRIXSTATIC_H__EA81982F_BB69_4A1A_870D_E62D412FB448__INCLUDED_)
#define AFX_MATRIXSTATIC_H__EA81982F_BB69_4A1A_870D_E62D412FB448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//

#include "Shape.h"

/////////////////////////////////////////////////////////////////////////////

class CCircleProgressCtl : public CStatic
{
// Construction
public:

	CCircleProgressCtl();


// Attributes
public:

// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixStatic)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CCircleProgressCtl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMatrixStatic)
	// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	int GetProgress();
	void SetProgress(int percent);
private:
	//CShape m_shape;
	COLORREF	roundColor;
	COLORREF	roundProgressColor;
	int roundWidth;
	int max;
	int progress;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXSTATIC_H__EA81982F_BB69_4A1A_870D_E62D412FB448__INCLUDED_)
