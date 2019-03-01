
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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	::OpenClipboard(NULL);
	if (!IsClipboardFormatAvailable(CF_DIB))
		return FALSE;
	HGLOBAL hImage = ::GetClipboardData(CF_DIB);
	::CloseClipboard();
	LPSTR pDIB = (LPSTR)::GlobalLock((HGLOBAL)hImage);
	// BitmapInfo Header 복사
	BITMAPINFOHEADER dibHi;
	memcpy(&dibHi, pDIB, sizeof(BITMAPINFOHEADER));
	int height = abs(dibHi.biHeight);
	int width = dibHi.biWidth;
	// 가로 길이 4의 배수가 되도록 조정
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);
	int type = (dibHi.biBitCount == 8) ? CV_8UC1 : CV_8UC3;
	int ch = (dibHi.biBitCount == 8) ? 1 : 3;
	int offset;
	if (dibHi.biBitCount == 8)
		offset = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256;
	else
		offset = sizeof(BITMAPINFOHEADER);
	// 복사된 Clipboard 영상을 srcImage로 복사
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
	// 데이터 복사
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
	// BMP 파일의 가로 크기를 4의 배수로 만들고, 전체 영상의 크기 계산
	int rwsize = WIDTHBYTES(dibCpyHi.biBitCount*cpyImage.cols);
	int imgSize = cpyImage.rows*rwsize;
	DWORD dwSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 + imgSize;
	// 메모리 할당(파일 헤더만 제외시킨 길이)
	HGLOBAL hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwSize);
	LPSTR pDIB = (LPSTR)::GlobalLock((HGLOBAL)hImage);
	memcpy(pDIB, &dibCpyHi, sizeof(BITMAPINFOHEADER));
	if (cpyImage.channels() == 1) { // 그레이 영상인 경우
		RGBQUAD palRGB[256];
		for (int i = 0; i < 256; i++) {
			palRGB[i].rgbBlue = palRGB[i].rgbGreen = palRGB[i].rgbRed = i;
			palRGB[i].rgbReserved = 0;
		}
		// 팔레트 복사
		memcpy(pDIB + sizeof(BITMAPINFOHEADER), palRGB, sizeof(RGBQUAD) * 256);
		// 이미지 복사
		for (int i = 0; i < cpyImage.rows; i++)
			memcpy(pDIB + sizeof(BITMAPINFOHEADER) +
				sizeof(RGBQUAD) * 256 + i*rwsize,
				cpyImage.data + i*cpyImage.cols, cpyImage.cols);
	}
	else { // 컬러 영상인 경우
		   // 이미지 복사
		for (int i = 0; i < cpyImage.rows; i++)
			memcpy(pDIB + sizeof(BITMAPINFOHEADER) + i*rwsize,
				cpyImage.data + i*cpyImage.cols*cpyImage.channels(),
				cpyImage.cols*cpyImage.channels());
	}
	// 클립보드 복사
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
