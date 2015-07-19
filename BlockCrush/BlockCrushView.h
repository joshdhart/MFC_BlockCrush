
// BlockCrushView.h : interface of the CBlockCrushView class
//

#pragma once


class CBlockCrushView : public CView
{
protected: // create from serialization only
	CBlockCrushView();
	DECLARE_DYNCREATE(CBlockCrushView)

// Attributes
public:
	CBlockCrushDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:

	void ResizeWindow();

	virtual ~CBlockCrushView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in BlockCrushView.cpp
inline CBlockCrushDoc* CBlockCrushView::GetDocument() const
   { return reinterpret_cast<CBlockCrushDoc*>(m_pDocument); }
#endif

