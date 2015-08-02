
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
<<<<<<< HEAD
	afx_msg void OnLevel3colors();
	afx_msg void OnUpdateLevel3colors(CCmdUI *pCmdUI);
	afx_msg void OnLevel4colors();
	afx_msg void OnUpdateLevel4colors(CCmdUI *pCmdUI);
	afx_msg void OnLevel5colors();
	afx_msg void OnUpdateLevel5colors(CCmdUI *pCmdUI);
	afx_msg void OnLevel6colors();
	afx_msg void OnUpdateLevel6colors(CCmdUI *pCmdUI);
	afx_msg void OnLevel7colors();
	afx_msg void OnUpdateLevel7colors(CCmdUI *pCmdUI);

private:
	void ChangeNumColors(int num);
public:
	afx_msg void OnSetupBlockcount();
	afx_msg void OnSetupBlocksize();
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
=======
>>>>>>> 1981c913e5baf2d3842c2b1ef1a4211cd16999de
};

#ifndef _DEBUG  // debug version in BlockCrushView.cpp
inline CBlockCrushDoc* CBlockCrushView::GetDocument() const
   { return reinterpret_cast<CBlockCrushDoc*>(m_pDocument); }
#endif

