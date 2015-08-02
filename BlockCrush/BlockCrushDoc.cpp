
// BlockCrushDoc.cpp : implementation of the CBlockCrushDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BlockCrush.h"
#endif

#include "BlockCrushDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBlockCrushDoc

IMPLEMENT_DYNCREATE(CBlockCrushDoc, CDocument)

BEGIN_MESSAGE_MAP(CBlockCrushDoc, CDocument)
END_MESSAGE_MAP()


// CBlockCrushDoc construction/destruction

CBlockCrushDoc::CBlockCrushDoc() :
	m_clickCount(0)
{
	m_board = new CBlockCrushBoard();
}

CBlockCrushDoc::~CBlockCrushDoc()
{
	// Delete the current game board
	delete m_board;
	// Delete everything from the undo stack
	ClearUndo();
	// Delete everything from the redo stack
	ClearRedo();
}

BOOL CBlockCrushDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Set (or reset) the game board
	m_board->SetupBoard();

	// Clear the undo/redo stacks
	ClearUndo();
	ClearRedo();

	return TRUE;
}


void CBlockCrushDoc::SetNumColors(int nColors)
{
	// Set the number of colors
	m_board->SetNumColors(nColors);
	// Reset the game board
	m_board->SetupBoard();
}


int CBlockCrushDoc::DeleteBlocks(int row, int col)
{
	// Save the current board in the undo stack
	m_undo.push(new CBlockCrushBoard(*m_board));
	// Empty out the redo stack
	ClearRedo();
	// Delete the blocks
	int blocks = m_board->DeleteBlocks(row, col);
	// Clear the undo stack at the end of a game
	if (m_board->IsGameOver()) {
		m_clickCount = m_undo.size();
		ClearUndo();
	}

	// Return the number of blocks
	return blocks;
}


void CBlockCrushDoc::UndoLast()
{
	// Make sure that there is a move to undo
	if (m_undo.empty())
		return;
	// Take the current board and put it on the redo
	m_redo.push(m_board);
	// Take the top undo and make it the current
	m_board = m_undo.top();
	m_undo.pop();
}

bool CBlockCrushDoc::CanUndo()
{
	// Can undo if the undo stack isn't empty
	return !m_undo.empty();
}

void CBlockCrushDoc::RedoLast()
{
	// Make sure that there is a move to redo
	if (m_redo.empty())
		return;
	// Take the current board and put it on the undo
	m_undo.push(m_board);
	// Take the top redo and make it the current
	m_board = m_redo.top();
	m_redo.pop();
}

bool CBlockCrushDoc::CanRedo()
{
	// Can redo if the redo stack isn't empty
	return !m_redo.empty();
}


void CBlockCrushDoc::ClearUndo()
{
	// Delete everything from the undo stack
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CBlockCrushDoc::ClearRedo()
{
	// Delete everything from the redo stack
	while (!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}


// CBlockCrushDoc serialization

void CBlockCrushDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CBlockCrushDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CBlockCrushDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBlockCrushDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBlockCrushDoc diagnostics

#ifdef _DEBUG
void CBlockCrushDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBlockCrushDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBlockCrushDoc commands
