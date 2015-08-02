/* ------------------------------------------------------------
-	Name: Josh Hartwell
-	Class: CST 405 - Directed Study of MFC
-
-	File: BlockCrushBoard.h
-		Provide class functionality to create the
-		game board.
------------------------------------------------------------ */

#pragma once
class CBlockCrushBoard
{
public:
	// Default Constructor
	CBlockCrushBoard();
<<<<<<< HEAD
	// Copy Constructor
	CBlockCrushBoard(const CBlockCrushBoard& board);
=======
>>>>>>> 1981c913e5baf2d3842c2b1ef1a4211cd16999de
	// Destructor
	~CBlockCrushBoard();
	// Function to randomly setup the board
	void SetupBoard(void);
	// Get the color at a particular location
	COLORREF GetBoardSpace(int row, int col);
	// Accessor functions to get board size information
	int GetWidth(void) const { return m_nWidth; }
<<<<<<< HEAD
	void SetWidth(int nWidth) { m_nWidth = (nWidth >= 3) ? nWidth : 3; }
	int GetHeight(void) const { return m_nHeight; }
	void SetHeight(int nHeight) { m_nHeight = (nHeight >= 3) ? nHeight : 3; }
	int GetColumns(void) const { return m_nColumns; }
	void SetColumns(int nColumns) { m_nColumns = (nColumns >= 5) ? nColumns : 5; }
	int GetRows(void) const { return m_nRows; }
	void SetRows(int nRows) { m_nRows = (nRows >= 5) ? nRows : 5; }
=======
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }
>>>>>>> 1981c913e5baf2d3842c2b1ef1a4211cd16999de
	// Function to delete the board and free memory
	void DeleteBoard(void);

	// Is the game over?
	bool IsGameOver(void) const;
	// Get the number of blocks remaining
	int GetRemainingCount(void) const { return m_nRemaining; }
	// Function to delete all adjacent blocks
	int DeleteBlocks(int row, int col);
<<<<<<< HEAD
	// Functions to get and set the number of colors
	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors)
	{
		m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors;
	}
=======
>>>>>>> 1981c913e5baf2d3842c2b1ef1a4211cd16999de

private:
	// Function to create the board and allocate memory
	void CreateBoard(void);

	// Direction enumeration for deleting blocks
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};
	// Recursive helper function for deleting blocks
	int DeleteNeighborBlocks(int row, int col, int color,
		Direction direction);
	// Function to compact the board after blocks are eliminated
	void CompactBoard(void);

	// 2D array pointer
	int** m_arrBoard;
<<<<<<< HEAD
	// List of colors, 0 is background and 1-7 are piece colors
	COLORREF m_arrColors[8];
=======
	// List of colors, 0 is background and 1-3 are piece colors
	COLORREF m_arrColors[4];
>>>>>>> 1981c913e5baf2d3842c2b1ef1a4211cd16999de
	// Board size information
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	// Number of blocks remaining
	int m_nRemaining;
<<<<<<< HEAD
	// Number of colors
	int m_nColors;
=======
>>>>>>> 1981c913e5baf2d3842c2b1ef1a4211cd16999de
};

