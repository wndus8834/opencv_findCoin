
// ImageProc_LJYDoc.h : interface of the CImageProc_LJYDoc class
//


#pragma once
#include "opencv.hpp"
using namespace cv;
using namespace std;


class CImageProc_LJYDoc : public CDocument
{
protected: // create from serialization only
	CImageProc_LJYDoc();
	DECLARE_DYNCREATE(CImageProc_LJYDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CImageProc_LJYDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	Mat m_srcImage;
	void CopyClipboard(Mat& cpyImage);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
