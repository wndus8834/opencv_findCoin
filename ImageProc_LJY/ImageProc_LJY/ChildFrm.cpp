
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "ImageProc_LJYDoc.h"
#include "ImageProc_LJY.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers


void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect, rectC;

	GetWindowRect(&rect);
	GetClientRect(&rectC);

	CSize sizeImg;

	sizeImg.cx = ((CImageProc_LJYDoc*)GetActiveDocument())->m_srcImage.cols;
	sizeImg.cy = ((CImageProc_LJYDoc*)GetActiveDocument())->m_srcImage.rows;

	int cx = sizeImg.cx + rect.Width() - rectC.Width() + 4;
	int cy = sizeImg.cy + rect.Height() - rectC.Height() + 4;

	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_SHOWWINDOW);

	CMDIChildWnd::ActivateFrame(nCmdShow);
}
