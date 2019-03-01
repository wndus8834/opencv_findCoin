
// ImageProc_LJYView.h : interface of the CImageProc_LJYView class
//

#pragma once
#include "atltypes.h"


class CImageProc_LJYView : public CView
{
protected: // create from serialization only
	CImageProc_LJYView();
	DECLARE_DYNCREATE(CImageProc_LJYView)

// Attributes
public:
	CImageProc_LJYDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CImageProc_LJYView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DisplayImage(Mat& image, CDC* pDC, CRect rect);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	void ImageShow(Mat& image);
	afx_msg void OnRgb2bgr();
	afx_msg void OnUpdateRgb2bgr(CCmdUI *pCmdUI);
	afx_msg void OnRgb2hsi();
	afx_msg void OnUpdateRgb2hsi(CCmdUI *pCmdUI);
	afx_msg void OnRgb2ycrcb();
	afx_msg void OnUpdateRgb2ycrcb(CCmdUI *pCmdUI);
	afx_msg void OnRgb2yuv();
	afx_msg void OnUpdateRgb2yuv(CCmdUI *pCmdUI);
	afx_msg void OnAddConst();
	afx_msg void OnSubConst();
	afx_msg void OnMulConst();
	afx_msg void OnDivConst();
	afx_msg void OnReverseImg();
	afx_msg void OnGammaCorrection();
	afx_msg void OnBinaryThreshold();
	afx_msg void OnAdaptativeThreshold();
	afx_msg void OnHistogram();
	afx_msg void OnHistEqualDirect();
	afx_msg void OnHistEqualFunc();
	afx_msg void OnHistSpec();
	afx_msg void OnNone();
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnUpdateNone(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	int m_nDrawType;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	CPoint m_ptStart;
	CPoint m_ptPrev;
	bool m_bMouseMove;
	bool m_bLButtonDown;
	COLORREF m_colorPen;
public:
	afx_msg void OnHistBackProject();
	afx_msg void OnUpdateHistBackProject(CCmdUI *pCmdUI);
	afx_msg void OnContStretching();
	afx_msg void OnEiContStretching();
	afx_msg void FindCoin1();
	afx_msg void FindCoin2();
};

#ifndef _DEBUG  // debug version in ImageProc_LJYView.cpp
inline CImageProc_LJYDoc* CImageProc_LJYView::GetDocument() const
   { return reinterpret_cast<CImageProc_LJYDoc*>(m_pDocument); }
#endif

