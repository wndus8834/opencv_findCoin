
// ImageProc_LJYDoc.cpp : implementation of the CImageProc_LJYDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageProc_LJY.h"
#endif

#include "ImageProc_LJYDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProc_LJYDoc

IMPLEMENT_DYNCREATE(CImageProc_LJYDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc_LJYDoc, CDocument)
END_MESSAGE_MAP()


// CImageProc_LJYDoc construction/destruction

CImageProc_LJYDoc::CImageProc_LJYDoc()
{
	// TODO: add one-time construction code here

}

CImageProc_LJYDoc::~CImageProc_LJYDoc()
{
}

BOOL CImageProc_LJYDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	::OpenClipboard(NULL);
	if (!IsClipboardFormatAvailable(CF_DIB))
		return FALSE;
	HGLOBAL hImage = ::GetClipboardData(CF_DIB);
	::CloseClipboard();
	LPSTR pDIB = (LPSTR)::GlobalLock((HGLOBAL)hImage);
	// BitmapInfo Header ����
	BITMAPINFOHEADER dibHi;
	memcpy(&dibHi, pDIB, sizeof(BITMAPINFOHEADER));
	int height = abs(dibHi.biHeight);
	int width = dibHi.biWidth;
	// ���� ���� 4�� ����� �ǵ��� ����
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);
	int type = (dibHi.biBitCount == 8) ? CV_8UC1 : CV_8UC3;
	int ch = (dibHi.biBitCount == 8) ? 1 : 3;
	int offset;
	if (dibHi.biBitCount == 8)
		offset = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256;
	else
		offset = sizeof(BITMAPINFOHEADER);
	// ����� Clipboard ������ srcImage�� ����
	Mat srcImage(Size(width, height), type);
	for (int i = 0; i < height; i++)
		memcpy(srcImage.data + i*width*ch, pDIB + offset + i*rwsize, width*ch);
	m_srcImage = srcImage;

	return TRUE;
}




// CImageProc_LJYDoc serialization

void CImageProc_LJYDoc::Serialize(CArchive& ar)
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
void CImageProc_LJYDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProc_LJYDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc_LJYDoc::SetSearchContent(const CString& value)
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

// CImageProc_LJYDoc diagnostics

#ifdef _DEBUG
void CImageProc_LJYDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc_LJYDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProc_LJYDoc commands


BOOL CImageProc_LJYDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	m_srcImage = imread(lpszPathName, IMREAD_UNCHANGED);
	if (m_srcImage.empty()) {
		CString str;
		str.Format(_T("Cat't find %s"), lpszPathName);
		AfxMessageBox(str);
		return FALSE;
	}

	//imshow("srcImage", m_srcImage);

	return TRUE;
}



void CImageProc_LJYDoc::CopyClipboard(Mat& cpyImage)
{
	// ������ ����
	BITMAPINFOHEADER dibCpyHi;
	dibCpyHi.biSize = sizeof(BITMAPINFOHEADER);
	dibCpyHi.biPlanes = 1;
	dibCpyHi.biCompression = BI_RGB;
	dibCpyHi.biXPelsPerMeter = 100;
	dibCpyHi.biYPelsPerMeter = 100;
	dibCpyHi.biClrUsed = (cpyImage.channels() == 1) ? 256 : 0;
	dibCpyHi.biClrImportant = (cpyImage.channels() == 1) ? 256 : 0;
	dibCpyHi.biSizeImage = cpyImage.rows*cpyImage.cols*cpyImage.elemSize();
	dibCpyHi.biWidth = cpyImage.cols;
	dibCpyHi.biHeight = -cpyImage.rows;
	dibCpyHi.biBitCount = cpyImage.channels() * 8;
	// BMP ������ ���� ũ�⸦ 4�� ����� �����, ��ü ������ ũ�� ���
	int rwsize = WIDTHBYTES(dibCpyHi.biBitCount*cpyImage.cols);
	int imgSize = cpyImage.rows*rwsize;
	DWORD dwSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 + imgSize;
	// �޸� �Ҵ�(���� ����� ���ܽ�Ų ����)
	HGLOBAL hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwSize);
	LPSTR pDIB = (LPSTR)::GlobalLock((HGLOBAL)hImage);
	memcpy(pDIB, &dibCpyHi, sizeof(BITMAPINFOHEADER));
	if (cpyImage.channels() == 1) { // �׷��� ������ ���
		RGBQUAD palRGB[256];
		for (int i = 0; i < 256; i++) {
			palRGB[i].rgbBlue = palRGB[i].rgbGreen = palRGB[i].rgbRed = i;
			palRGB[i].rgbReserved = 0;
		}
		// �ȷ�Ʈ ����
		memcpy(pDIB + sizeof(BITMAPINFOHEADER), palRGB, sizeof(RGBQUAD) * 256);
		// �̹��� ����
		for (int i = 0; i < cpyImage.rows; i++)
			memcpy(pDIB + sizeof(BITMAPINFOHEADER) +
				sizeof(RGBQUAD) * 256 + i*rwsize,
				cpyImage.data + i*cpyImage.cols, cpyImage.cols);
	}
	else { // �÷� ������ ���
		   // �̹��� ����
		for (int i = 0; i < cpyImage.rows; i++)
			memcpy(pDIB + sizeof(BITMAPINFOHEADER) + i*rwsize,
				cpyImage.data + i*cpyImage.cols*cpyImage.channels(),
				cpyImage.cols*cpyImage.channels());
	}
	// Ŭ������ ����
	::OpenClipboard(NULL);
	::SetClipboardData(CF_DIB, hImage);
	::CloseClipboard();
	::GlobalUnlock((HGLOBAL)hImage);
	::GlobalFree(hImage);

}


BOOL CImageProc_LJYDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	if (!m_srcImage.empty()) {
		imwrite(lpszPathName, m_srcImage);
	}

	return TRUE;
}
