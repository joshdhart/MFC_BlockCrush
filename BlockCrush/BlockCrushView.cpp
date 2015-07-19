
// BlockCrushView.cpp : implementation of the CBlockCrushView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BlockCrush.h"
#endif

#include "BlockCrushDoc.h"
#include "BlockCrushView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBlockCrushView

IMPLEMENT_DYNCREATE(CBlockCrushView, CView)

BEGIN_MESSAGE_MAP(CBlockCrushView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CBlockCrushView construction/destruction

CBlockCrushView::CBlockCrushView()
{
	// TODO: add construction code here

}

CBlockCrushView::~CBlockCrushView()
{
}

BOOL CBlockCrushView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	// the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBlockCrushView drawing

void CBlockCrushView::OnDraw(CDC* pDC)
{
	// Pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Save the current state of the device context
	int nDCSave = pDC->SaveDC();
	// Get the client rectangle
	CRect rcClient;
	GetClientRect(&rcClient);
	// Get the background color of the board
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	//Draw the background first
	pDC->FillSolidRect(&rcClient, clr);
	// Create the brush for drawing
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	// Draw the squares
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			// Get the color for this board space
			clr = pDoc->GetBoardSpace(row, col);
			// Calculate the size and position of this space
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			// Fill in the block with the correct color
			pDC->FillSolidRect(&rcBlock, clr);
			// Draw the block outline
			pDC->Rectangle(&rcBlock);
		}
	}
	// Restore the device context settings
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// CBlockCrushView diagnostics

#ifdef _DEBUG
void CBlockCrushView::AssertValid() const
{
	CView::AssertValid();
}

void CBlockCrushView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBlockCrushDoc* CBlockCrushView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBlockCrushDoc)));
	return (CBlockCrushDoc*)m_pDocument;
}
#endif //_DEBUG


// CBlockCrushView message handlers


void CBlockCrushView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// Resize the window
	ResizeWindow();
}

void CBlockCrushView::ResizeWindow()
{
	// First get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	// Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	// Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	// The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CBlockCrushView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// First get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Get the row and column of the block that was clicked on
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	// Delete the blocks from the document
	int count = pDoc->DeleteBlocks(row, col);
	// Check if there were any blocks deleted
	if (count > 0)
	{
		// Force the view to redraw
		Invalidate();
		UpdateWindow();
		// Check if the game is over
		if (pDoc->IsGameOver())
		{
			// Get the count remaining
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"),
				remaining);
			// Display the results to the user
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}

	// Default OnLButtonDown
	CView::OnLButtonDown(nFlags, point);
}
