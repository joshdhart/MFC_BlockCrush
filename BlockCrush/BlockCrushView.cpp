
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
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBlockCrushView

IMPLEMENT_DYNCREATE(CBlockCrushView, CView)

BEGIN_MESSAGE_MAP(CBlockCrushView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()

	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LEVEL_3COLORS, &CBlockCrushView::OnLevel3colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3COLORS, &CBlockCrushView::OnUpdateLevel3colors)
	ON_COMMAND(ID_LEVEL_4COLORS, &CBlockCrushView::OnLevel4colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4COLORS, &CBlockCrushView::OnUpdateLevel4colors)
	ON_COMMAND(ID_LEVEL_5COLORS, &CBlockCrushView::OnLevel5colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5COLORS, &CBlockCrushView::OnUpdateLevel5colors)
	ON_COMMAND(ID_LEVEL_6COLORS, &CBlockCrushView::OnLevel6colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6COLORS, &CBlockCrushView::OnUpdateLevel6colors)
	ON_COMMAND(ID_LEVEL_7COLORS, &CBlockCrushView::OnLevel7colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7COLORS, &CBlockCrushView::OnUpdateLevel7colors)
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CBlockCrushView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CBlockCrushView::OnSetupBlocksize)
	ON_COMMAND(ID_EDIT_REDO, &CBlockCrushView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CBlockCrushView::OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, &CBlockCrushView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CBlockCrushView::OnUpdateEditUndo)
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
			int numClicks = pDoc->GetNumClicks();
			CString message;
			if (remaining == 0)
			{
				message.Format(_T("You WON!!!!!\nBlocks remaining: %d\nClicks used: %d"),
					remaining, numClicks);
			}
			else
			{
				message.Format(_T("No more moves left\nBlocks remaining: %d\nClicks used: %d"),
					remaining, numClicks);
			}
			// Display the results to the user
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}

	// Default OnLButtonDown
	CView::OnLButtonDown(nFlags, point);
}


void CBlockCrushView::OnLevel3colors()
{
	ChangeNumColors(3);
}


void CBlockCrushView::OnUpdateLevel3colors(CCmdUI *pCmdUI)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 3);
}


void CBlockCrushView::OnLevel4colors()
{
	ChangeNumColors(4);
}


void CBlockCrushView::OnUpdateLevel4colors(CCmdUI *pCmdUI)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 4);
}


void CBlockCrushView::OnLevel5colors()
{
	ChangeNumColors(5);
}


void CBlockCrushView::OnUpdateLevel5colors(CCmdUI *pCmdUI)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 5);
}


void CBlockCrushView::OnLevel6colors()
{
	ChangeNumColors(6);
}


void CBlockCrushView::OnUpdateLevel6colors(CCmdUI *pCmdUI)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 6);
}


void CBlockCrushView::OnLevel7colors()
{
	ChangeNumColors(7);
}


void CBlockCrushView::OnUpdateLevel7colors(CCmdUI *pCmdUI)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 7);
}


void CBlockCrushView::ChangeNumColors(int num)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Set the number of colors
	pDoc->SetNumColors(num);
	// Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CBlockCrushView::OnSetupBlockcount()
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Create the options dialog
	COptionsDialog dlg(true, this);
	// Set the row and column values
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	// Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		// Delete the board
		pDoc->DeleteBoard();
		// Get the user selected values
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		// Update the board
		pDoc->SetupBoard();
		// Resize the view
		ResizeWindow();
	}
}


void CBlockCrushView::OnSetupBlocksize()
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Create the options dialog
	COptionsDialog dlg(false, this);
	// Set the width and height values
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	// Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		// Delete the board
		pDoc->DeleteBoard();
		// Get the user selected values
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		// Update the board
		pDoc->SetupBoard();
		// Resize the view
		ResizeWindow();
	}
}


void CBlockCrushView::OnEditRedo()
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Call undo on the document
	pDoc->RedoLast();
	// Force the view to redraw
	Invalidate();
	UpdateWindow();
}


void CBlockCrushView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Enable option if it is available
	pCmdUI->Enable(pDoc->CanRedo());
}


void CBlockCrushView::OnEditUndo()
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Call undo on the document
	pDoc->UndoLast();
	// Force the view to redraw
	Invalidate();
	UpdateWindow();
}


void CBlockCrushView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// Get a pointer to the document
	CBlockCrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Enable option if it is available
	pCmdUI->Enable(pDoc->CanUndo());
}
