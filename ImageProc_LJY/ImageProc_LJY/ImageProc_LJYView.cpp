
// ImageProc_LJYView.cpp : implementation of the CImageProc_LJYView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageProc_LJY.h"
#endif

#include "ImageProc_LJYDoc.h"
#include "ImageProc_LJYView.h"
#include "GammaDlg.h"
#include "ThreshDlg.h"
#include "AdaptiveThreshDlg.h"
#include "EndInDlg.h"
#define DRAW_NONE 0
#define DRAW_LINE 1
#define DRAW_RECTANGLE 2

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProc_LJYView

IMPLEMENT_DYNCREATE(CImageProc_LJYView, CView)

BEGIN_MESSAGE_MAP(CImageProc_LJYView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_COPY, &CImageProc_LJYView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CImageProc_LJYView::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CImageProc_LJYView::OnUpdateEditPaste)
	ON_COMMAND(IDM_RGB2BGR, &CImageProc_LJYView::OnRgb2bgr)
	ON_UPDATE_COMMAND_UI(IDM_RGB2BGR, &CImageProc_LJYView::OnUpdateRgb2bgr)
	ON_COMMAND(IDM_RGB2HSI, &CImageProc_LJYView::OnRgb2hsi)
	ON_UPDATE_COMMAND_UI(IDM_RGB2HSI, &CImageProc_LJYView::OnUpdateRgb2hsi)
	ON_COMMAND(IDM_RGB2YCrCb, &CImageProc_LJYView::OnRgb2ycrcb)
	ON_UPDATE_COMMAND_UI(IDM_RGB2YCrCb, &CImageProc_LJYView::OnUpdateRgb2ycrcb)
	ON_COMMAND(IDM_RGB2YUV, &CImageProc_LJYView::OnRgb2yuv)
	ON_UPDATE_COMMAND_UI(IDM_RGB2YUV, &CImageProc_LJYView::OnUpdateRgb2yuv)
	ON_COMMAND(IDM_ADD_CONST, &CImageProc_LJYView::OnAddConst)
	ON_COMMAND(IDM_SUB_CONST, &CImageProc_LJYView::OnSubConst)
	ON_COMMAND(IDM_MUL_CONST, &CImageProc_LJYView::OnMulConst)
	ON_COMMAND(IDM_DIV_CONST, &CImageProc_LJYView::OnDivConst)
	ON_COMMAND(IDM_REVERSE_IMG, &CImageProc_LJYView::OnReverseImg)
	ON_COMMAND(IDM_GAMMA_CORRECTION, &CImageProc_LJYView::OnGammaCorrection)
	ON_COMMAND(IDM_BINARY_THRESHOLD, &CImageProc_LJYView::OnBinaryThreshold)
	ON_COMMAND(IDM_ADAPTATIVE_THRESHOLD, &CImageProc_LJYView::OnAdaptativeThreshold)
	ON_COMMAND(IDM_HISTOGRAM, &CImageProc_LJYView::OnHistogram)
	ON_COMMAND(IDM_HIST_EQUAL_DIRECT, &CImageProc_LJYView::OnHistEqualDirect)
	ON_COMMAND(IDM_HIST_EQUAL_FUNC, &CImageProc_LJYView::OnHistEqualFunc)
	ON_COMMAND(IDM_HIST_SPEC, &CImageProc_LJYView::OnHistSpec)
	ON_COMMAND(IDM_NONE, &CImageProc_LJYView::OnNone)
	ON_COMMAND(IDM_LINE, &CImageProc_LJYView::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CImageProc_LJYView::OnRectangle)
	ON_UPDATE_COMMAND_UI(IDM_NONE, &CImageProc_LJYView::OnUpdateNone)
	ON_UPDATE_COMMAND_UI(IDM_LINE, &CImageProc_LJYView::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(IDM_RECTANGLE, &CImageProc_LJYView::OnUpdateRectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_HIST_BACK_PROJECT, &CImageProc_LJYView::OnHistBackProject)
	ON_UPDATE_COMMAND_UI(IDM_HIST_BACK_PROJECT, &CImageProc_LJYView::OnUpdateHistBackProject)
	ON_COMMAND(IDM_CONT_STRETCHING, &CImageProc_LJYView::OnContStretching)
	ON_COMMAND(IDM_EI_CONT_STRETCHING, &CImageProc_LJYView::OnEiContStretching)
	ON_COMMAND(ID__1, &CImageProc_LJYView::FindCoin1)
	ON_COMMAND(ID__2, &CImageProc_LJYView::FindCoin2)
END_MESSAGE_MAP()

// CImageProc_LJYView construction/destruction

CImageProc_LJYView::CImageProc_LJYView()
	: m_nDrawType(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	, m_bMouseMove(false)
	, m_bLButtonDown(false)
{
	// TODO: add construction code here

}

CImageProc_LJYView::~CImageProc_LJYView()
{
}

BOOL CImageProc_LJYView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CImageProc_LJYView drawing

void CImageProc_LJYView::OnDraw(CDC* pDC)
{
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect clientRect;
	
/*	clientRect.left = 0;
	clientRect.top = 0;
	clientRect.right = pDoc->m_srcImage.cols;
	clientRect.bottom = pDoc->m_srcImage.rows;
	*/
	
	GetClientRect(&clientRect);
	if (!pDoc->m_srcImage.empty()) {
		DisplayImage(pDoc->m_srcImage, pDC, clientRect);

		// 그리기 추가
		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 1, m_colorPen);
		oldPen = pDC->SelectObject(&pen);
		pDC->SelectObject(GetStockObject(NULL_BRUSH));
		pDC->SetROP2(R2_COPYPEN);
		if (m_nDrawType == DRAW_RECTANGLE)
			pDC->Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		else if (m_nDrawType == DRAW_LINE) {
			pDC->MoveTo(m_ptStart.x, m_ptStart.y);
			pDC->LineTo(m_ptPrev.x, m_ptPrev.y);
		}
		else {
			m_ptStart = m_ptPrev = 0;
		}
		pDC->SelectObject(oldPen);
		pen.DeleteObject();
		//
	}
}


// CImageProc_LJYView printing

BOOL CImageProc_LJYView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageProc_LJYView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageProc_LJYView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CImageProc_LJYView diagnostics

#ifdef _DEBUG
void CImageProc_LJYView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProc_LJYView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProc_LJYDoc* CImageProc_LJYView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc_LJYDoc)));
	return (CImageProc_LJYDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc_LJYView message handlers


void CImageProc_LJYView::DisplayImage(Mat& image, CDC* pDC, CRect rect)
{
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression = BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter = 100;
	bitmapinfo.bmiHeader.biYPelsPerMeter = 100;
	bitmapinfo.bmiHeader.biClrUsed = 0;
	bitmapinfo.bmiHeader.biClrImportant = 0;
	bitmapinfo.bmiHeader.biSizeImage = 0;
	bitmapinfo.bmiHeader.biWidth = image.cols;
	bitmapinfo.bmiHeader.biHeight = -image.rows;

	Mat tempImage;
	const int depth = 8;

	if (image.channels() == 3) {
		tempImage = image.clone();
	}
	else if (image.channels() == 1) {
		tempImage.create(image.size(), CV_8UC3);
		cvtColor(image, tempImage, CV_GRAY2BGR);
	}
	bitmapinfo.bmiHeader.biBitCount = tempImage.channels()*depth;

	int dst_step = WIDTHBYTES(bitmapinfo.bmiHeader.biBitCount*tempImage.cols);
	int src_step = tempImage.cols*tempImage.channels();

	BYTE *imgData = new BYTE[tempImage.rows*dst_step];
	for (int i = 0; i < tempImage.rows; i++) {
		memcpy(imgData + i*dst_step, tempImage.data + i*src_step, src_step);
	}

	if (!tempImage.empty()) {
		pDC->SetStretchBltMode(COLORONCOLOR);
		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom,
			0, 0, tempImage.cols, tempImage.rows, imgData, &bitmapinfo,
			DIB_RGB_COLORS, SRCCOPY);
	}
	delete[]imgData;

}


void CImageProc_LJYView::OnEditCopy()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_srcImage.empty())
		return;
	pDoc->CopyClipboard(pDoc->m_srcImage);

}


void CImageProc_LJYView::OnEditPaste()
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProc_LJYView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_DIB));
}


void CImageProc_LJYView::ImageShow(Mat& image)
{
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// 클립보드에 복사
	pDoc->CopyClipboard(image);
	// OnNewDocument 함수 호출
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProc_LJYView::OnRgb2bgr()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<Mat> planes;
	split(pDoc->m_srcImage, planes);
	for (uint i = 0; i < planes.size(); i++) {
		ImageShow(planes[i]);
	}
}


void CImageProc_LJYView::OnUpdateRgb2bgr(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here.
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->m_srcImage.channels() == 3);
}


void CImageProc_LJYView::OnRgb2hsi()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat dstImg;
	cvtColor(pDoc->m_srcImage, dstImg, CV_BGR2HSV);
	vector<Mat> planes;
	split(dstImg, planes);
	for (uint i = 0; i < planes.size(); i++) {
		ImageShow(planes[i]);
	}
}


void CImageProc_LJYView::OnUpdateRgb2hsi(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->m_srcImage.channels() == 3);
}


void CImageProc_LJYView::OnRgb2ycrcb()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat dstImg;
	cvtColor(pDoc->m_srcImage, dstImg, CV_BGR2YCrCb);
	vector<Mat> planes;
	split(dstImg, planes);
	for (uint i = 0; i < planes.size(); i++) {
		ImageShow(planes[i]);
	}
}


void CImageProc_LJYView::OnUpdateRgb2ycrcb(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->m_srcImage.channels() == 3);
}


void CImageProc_LJYView::OnRgb2yuv()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat dstImg;
	cvtColor(pDoc->m_srcImage, dstImg, CV_BGR2YUV);
	vector<Mat> planes;
	split(dstImg, planes);
	for (uint i = 0; i < planes.size(); i++) {
		ImageShow(planes[i]);
	}
}


void CImageProc_LJYView::OnUpdateRgb2yuv(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->m_srcImage.channels() == 3);
}


void CImageProc_LJYView::OnAddConst()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<Mat> planes;

	split(pDoc->m_srcImage, planes);
	uchar val = 50;
	for (uint i = 0; i < planes.size(); i++) {
		for (int y = 0; y < planes[i].rows; y++) {
			for (int x = 0; x < planes[i].cols; x++) {
				planes[i].at<uchar>(y, x) =
					CLIP(planes[i].at<uchar>(y, x) + val, 0, 255);
			}
		}
	}
	Mat dstImage;
	merge(planes, dstImage);
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnSubConst()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<Mat> planes;
	split(pDoc->m_srcImage, planes); // 각각의 채널로 분리한다.
	uchar val = 50;
	for (uint i = 0; i < planes.size(); i++) {
		for (int y = 0; y < planes[i].rows; y++) {
			for (int x = 0; x < planes[i].cols; x++) {
				planes[i].at<uchar>(y, x) =
					CLIP(planes[i].at<uchar>(y, x) - val, 0, 255);
			}
		}
	}
	Mat dstImage;
	merge(planes, dstImage); // 각각의 채널을 합친다.
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnMulConst()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<Mat> planes;
	split(pDoc->m_srcImage, planes); // 각각의 채널로 분리한다.
	float val = 1.5;
	for (uint i = 0; i < planes.size(); i++) {
		for (int y = 0; y < planes[i].rows; y++) {
			for (int x = 0; x < planes[i].cols; x++) {
				planes[i].at<uchar>(y, x) =
					CLIP(planes[i].at<uchar>(y, x) * val, 0, 255);
			}
		}
	}
	Mat dstImage;
	merge(planes, dstImage); // 각각의 채널을 합친다.
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnDivConst()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<Mat> planes;
	split(pDoc->m_srcImage, planes); // 각각의 채널로 분리한다.
	float val = 1.5;
	for (uint i = 0; i < planes.size(); i++) {
		for (int y = 0; y < planes[i].rows; y++) {
			for (int x = 0; x < planes[i].cols; x++) {
				planes[i].at<uchar>(y, x) =
					CLIP(planes[i].at<uchar>(y, x) / val, 0, 255);
			}
		}
	}
	Mat dstImage;
	merge(planes, dstImage); // 각각의 채널을 합친다.
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnReverseImg()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<Mat> planes;
	split(pDoc->m_srcImage, planes); // 각각의 채널로 분리한다.
	for (uint i = 0; i < planes.size(); i++) {
		for (int y = 0; y < planes[i].rows; y++) {
			for (int x = 0; x < planes[i].cols; x++) {
				planes[i].at<uchar>(y, x) =
					255 - planes[i].at<uchar>(y, x);
			}
		}
	}
	Mat dstImage;
	merge(planes, dstImage); // 각각의 채널을 합친다.
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnGammaCorrection()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CGammaDlg dlg;
	if (dlg.DoModal() == IDOK) {
		vector<Mat> planes;
		split(pDoc->m_srcImage, planes); // 각각의 채널로 분리한다.
		double val;
		for (uint i = 0; i < planes.size(); i++) {
			for (int y = 0; y < planes[i].rows; y++) {
				for (int x = 0; x < planes[i].cols; x++) {
					val = pow(planes[i].at<uchar>(y, x) / 255.0,
						1.0 / dlg.m_fGamma) * 255;
					planes[i].at<uchar>(y, x) = CLIP(val, 0, 255);
				}
			}
		}
		Mat dstImage;
		merge(planes, dstImage); // 각각의 채널을 합친다.
		ImageShow(dstImage);
	}
}


void CImageProc_LJYView::OnBinaryThreshold()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CThreshDlg dlg;
	if (dlg.DoModal() == IDOK) {
		Mat srcImage, dstImage;
		// 컬러인 경우는 흑백 영상으로 변환한다.
		if (pDoc->m_srcImage.channels() == 3)
			cvtColor(pDoc->m_srcImage, srcImage, CV_BGR2GRAY);
		else
			srcImage = pDoc->m_srcImage;
		int nType = THRESH_BINARY;
		int nOptimal = 0;
		switch (dlg.m_nType) {
		case 0:
			nType = THRESH_BINARY;
			break;
		case 1:
			nType = THRESH_BINARY_INV;
			break;
		case 2:
			nType = THRESH_TRUNC;
			break;
		case 3:
			nType = THRESH_TOZERO;
			break;
		case 4:
			nType = THRESH_TOZERO_INV;
		}
		switch (dlg.m_nOptimal) {
		case 1:
			nOptimal = THRESH_OTSU;
			break;
		case 2:
			nOptimal = THRESH_TRIANGLE;
		}
		threshold(srcImage, dstImage, dlg.m_ucThresh, 255, nType + nOptimal);
		ImageShow(dstImage);
	}
}


void CImageProc_LJYView::OnAdaptativeThreshold()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CAdaptiveThreshDlg dlg;
	if (dlg.DoModal() == IDOK) {
		Mat srcImage, dstImage;
		// 컬러인 경우는 흑백 영상으로 변환한다.
		if (pDoc->m_srcImage.channels() == 3)
			cvtColor(pDoc->m_srcImage, srcImage, CV_BGR2GRAY);
		else
			srcImage = pDoc->m_srcImage;
		int nMethod = ADAPTIVE_THRESH_MEAN_C;
		int nType = THRESH_BINARY;
		switch (dlg.m_nMethod) {
		case 0:
			nMethod = ADAPTIVE_THRESH_MEAN_C;
			break;
		case 1:
			nMethod = ADAPTIVE_THRESH_GAUSSIAN_C;
		}
		switch (dlg.m_nType) {
		case 0:
			nType = THRESH_BINARY;
			break;
		case 1:
			nType = THRESH_BINARY_INV;
		}
		adaptiveThreshold(srcImage, dstImage, 255, nMethod, nType, 21, 5);
		ImageShow(dstImage);
	}
}


void CImageProc_LJYView::OnHistogram()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat srcImage, dstImage;
	// 컬러인 경우는 흑백 영상으로 변환한다.
	if (pDoc->m_srcImage.channels() == 3)
		cvtColor(pDoc->m_srcImage, srcImage, CV_BGR2GRAY);
	else
		srcImage = pDoc->m_srcImage;
	int histSize = 256;
	float valueRange[] = { 0,256 };
	const float* ranges[] = { valueRange };
	int channels = 0;
	int dims = 1;
	// 히스토그램 구하기
	Mat hist;
	calcHist(&srcImage, 1, &channels, Mat(), hist, 1, &histSize, ranges);
	// 화면크기에 맞게 정규화 하기
	Mat histImage(256, 256, CV_8U);
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, CV_32F);
	// 히스토그램 그리기
	histImage = Scalar(255);
	int binW = cvRound((double)histImage.cols / histSize);
	int x1, y1, x2, y2;
	for (int i = 0; i < histSize; i++) {
		x1 = i*binW;
		y1 = histImage.rows;
		x2 = (i + 1)*binW;
		y2 = histImage.rows - cvRound(hist.at<float>(i));
		rectangle(histImage, Point(x1, y1), Point(x2, y2), Scalar(0), -1);
	}
	ImageShow(histImage);
}


void CImageProc_LJYView::OnHistEqualDirect()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	const int L = 256;
	Mat srcImage, dstImage;
	vector<Mat> planes;
	// RGB 컬러인 경우는 YUV로 변환한 후 Y 영상만을 취한다.
	if (pDoc->m_srcImage.channels() == 3) {
		cvtColor(pDoc->m_srcImage, dstImage, CV_BGR2YUV);
		split(dstImage, planes);
		srcImage = planes[0];
	}
	else
		srcImage = pDoc->m_srcImage;
	int histSize[] = { L };
	float valueRange[] = { 0,L };
	const float* ranges[] = { valueRange };
	int channels[] = { 0 };
	int dims = 1;
	// 히스토그램 구하기
	Mat hist;
	calcHist(&srcImage, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	// 0 ~ L-1로 정규화하기
	Mat pdf;
	normalize(hist, pdf, L - 1, 0, NORM_L1); // sum of pdf = L-1
											 // 누적 분포값 구하기
	Mat cdf(pdf.size(), pdf.type());
	cdf.at<float>(0) = pdf.at<float>(0); // (0,0)
	for (int i = 1; i < pdf.rows; i++)
		cdf.at<float>(i) = cdf.at<float>(i - 1) + pdf.at<float>(i); //(i,0)
																	// 룩업 테이블 만들기
	Mat table(cdf.size(), CV_8U);
	table.at<uchar>(0) = 0;
	for (int i = 1; i < pdf.rows; i++)
		table.at<uchar>(i) = cvRound(cdf.at<float>(i)); //(i,0)
														// 결과영상 구하기
	Mat dstGrayImg;
	LUT(srcImage, table, dstGrayImg);
	if (pDoc->m_srcImage.channels() == 3) {
		planes[0] = dstGrayImg;
		merge(planes, dstImage);
		cvtColor(dstImage, dstImage, CV_YUV2BGR);
	}
	else
		dstImage = dstGrayImg;
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnHistEqualFunc()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat srcImage, dstImage;
	vector<Mat> planes;
	// RGB 컬러인 경우는 YUV로 변환한 후 Y 영상만을 취한다.
	if (pDoc->m_srcImage.channels() == 3) {
		cvtColor(pDoc->m_srcImage, dstImage, CV_BGR2YUV);
		split(dstImage, planes);
		srcImage = planes[0];
	}
	else
		srcImage = pDoc->m_srcImage;
	// 히스토그램 평활화 수행
	Mat dstGrayImg;
	equalizeHist(srcImage, dstGrayImg);
	// Y 영상에 대한 계산 결과를 합친 후 BGR 영상으로 변환한다.
	if (pDoc->m_srcImage.channels() == 3) {
		planes[0] = dstGrayImg;
		merge(planes, dstImage);
		cvtColor(dstImage, dstImage, CV_YUV2BGR);
	}
	else
		dstImage = dstGrayImg;
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnHistSpec()
{
	// TODO: Add your command handler code here
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// 히스토그램을 지정할 영상 입력
	AfxMessageBox(_T("지정할 영상을 입력합니다"));
	CString szFilter = _T("이미지 파일 (*.BMP,*.JPG, *.GIF) | *.BMP;*.JPG;*.GIF | 모든 파일(*.*) | *.* | ");
		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		Mat specImage = imread((String)dlg.GetPathName(), IMREAD_UNCHANGED);
		if (specImage.empty()) {
			CString str;
			str.Format(_T("Can't find %s"), dlg.GetPathName());
			AfxMessageBox(str);
			return;
		}
		Mat specGray;
		vector<Mat> planes;
		if (specImage.channels() == 3) {
			Mat yuvImage;
			cvtColor(specImage, yuvImage, COLOR_BGR2YUV);
			split(yuvImage, planes);
			specGray = planes[0];
		}
		else {
			specGray = specImage;
		}
		// 지정 영상의 히스토그램 계산.
		int histSize = 256;
		float hValue[] = { 0,histSize };
		const float* ranges[] = { hValue };
		int channels = 0;
		int dims = 1;
		Mat hist;
		calcHist(&specGray, 1, &channels, Mat(), hist, dims, &histSize, ranges);
		// 지정 히스토그램의 정규화된 합 계산
		Mat pdf;
		normalize(hist, pdf, histSize - 1, 0, NORM_L1);
		Mat cdf(pdf.size(), pdf.type());
		cdf.at<float>(0) = pdf.at<float>(0);
		for (int i = 1; i < pdf.rows; i++)
			cdf.at<float>(i) = cdf.at<float>(i - 1) + pdf.at<float>(i);
		// 역 변환 테이블 만들기
		Mat table(cdf.size(), CV_8U);
		int difference, min;
		for (int i = 0; i < histSize; i++) {
			difference = abs((int)(i - cdf.at<float>(0)));
			min = 0;
			for (int j = 0; j < histSize; j++) {
				if (abs((int)(i - cdf.at<float>(j))) < difference) {
					difference = abs((int)(i - cdf.at<float>(j)));
					min = j;
				}
			}
			table.at<uchar>(i) = (BYTE)min;
		}
		// 원 영상의 히스토그램 평활화
		// RGB 컬러인 경우는 YUV로 변환한 후 Y 영상만을 취한다.
		Mat srcImage, dstImage;
		if (pDoc->m_srcImage.channels() == 3) {
			cvtColor(pDoc->m_srcImage, dstImage, CV_BGR2YUV);
			split(dstImage, planes);
			srcImage = planes[0];
		}
		else
			srcImage = pDoc->m_srcImage;
		// 원 그레이 영상의 히스토그램 평활화 수행
		Mat dstGrayImg;
		equalizeHist(srcImage, dstGrayImg);
		// 역변환 테이블을 이용한 변환
		LUT(dstGrayImg, table, dstGrayImg);
		if (pDoc->m_srcImage.channels() == 3) {
			// Y 영상에 대한 계산 결과를 합친 후 BGR 영상으로 변환한다.
			planes[0] = dstGrayImg;
			merge(planes, dstImage);
			cvtColor(dstImage, dstImage, CV_YUV2BGR);
		}
		else
			dstImage = dstGrayImg;
		ImageShow(dstImage);
	}

}


void CImageProc_LJYView::OnNone()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawType = DRAW_NONE;
}


void CImageProc_LJYView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawType = DRAW_LINE;
}


void CImageProc_LJYView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawType = DRAW_RECTANGLE;
}


void CImageProc_LJYView::OnUpdateNone(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawType == DRAW_NONE);
}


void CImageProc_LJYView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawType == DRAW_LINE);
}


void CImageProc_LJYView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawType == DRAW_RECTANGLE);
}


void CImageProc_LJYView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptStart = m_ptPrev = point;
	m_bLButtonDown = true;
	RECT rectClient;
	SetCapture();
	GetClientRect(&rectClient);
	ClientToScreen(&rectClient);
	::ClipCursor(&rectClient);
	CView::OnLButtonDown(nFlags, point);
}


void CImageProc_LJYView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bLButtonDown) {
		m_bLButtonDown = false;
		ReleaseCapture();
		::ClipCursor(NULL);
		Invalidate(true);
	}
	CView::OnLButtonUp(nFlags, point);
}


void CImageProc_LJYView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	CPen pen, *oldPen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);
	oldPen = dc.SelectObject(&pen);
	dc.SetROP2(R2_NOTXORPEN);
	if (m_bLButtonDown) {
		if (m_nDrawType == DRAW_RECTANGLE) {
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);
		}
		else if (m_nDrawType == DRAW_LINE) {
			dc.MoveTo(m_ptStart.x, m_ptStart.y);
			dc.LineTo(m_ptPrev.x, m_ptPrev.y);
			dc.MoveTo(m_ptStart.x, m_ptStart.y);
			dc.LineTo(point.x, point.y);
		}
		m_ptPrev = point;
	}
	dc.SelectObject(oldPen);
	pen.DeleteObject();
	CView::OnMouseMove(nFlags, point);
}


void CImageProc_LJYView::OnHistBackProject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// 컬러정보를 갖는 Hue 영상 추출
	Mat hsvImage;
	cvtColor(pDoc->m_srcImage, hsvImage, COLOR_BGR2HSV);
	vector<Mat> planes;
	split(hsvImage, planes);
	Mat hueImage = planes[0];
	// 사각형 영역을 구한다.
	int xStart, yStart, width, height;
	if (m_ptStart.x <= m_ptPrev.x)
		xStart = m_ptStart.x;
	else
		xStart = m_ptPrev.x;
	if (m_ptStart.y <= m_ptPrev.y)
		yStart = m_ptStart.y;
	else
		yStart = m_ptPrev.y;
	width = abs(m_ptStart.x - m_ptPrev.x);
	height = abs(m_ptStart.y - m_ptPrev.y);
	if (width == 0 || height == 0) {
		AfxMessageBox(_T("사각형 영역을 설정하세요."));
		return;
	}
	// 관심 영역(ROI) 추출
	Rect roi(xStart, yStart, width, height);
	Mat roiImage = hueImage(roi);
	// 관심 영역에 대한 히스토그램 구하기
	int histSize = 256;
	float hValue[] = { 0,histSize };
	const float* ranges[] = { hValue };
	int channels = 0;
	int dims = 1;
	Mat hist;
	calcHist(&roiImage, 1, &channels, Mat(), hist, dims, &histSize, ranges);
	// 역투영 구하기
	Mat hueImage2;
	hueImage.convertTo(hueImage2, CV_32F);
	Mat backProject;
	calcBackProject(&hueImage2, 1, &channels, hist, backProject, ranges);
	// 역투영 결과 정규화
	Mat backProject2;
	normalize(backProject, backProject2, 0, 255, NORM_MINMAX, CV_8U);
	ImageShow(backProject2);
}


void CImageProc_LJYView::OnUpdateHistBackProject(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->m_srcImage.channels() == 3);
}


void CImageProc_LJYView::OnContStretching()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat srcImage;
	vector<Mat> planes;
	if (pDoc->m_srcImage.channels() == 3) {
		Mat yuvImage;
		cvtColor(pDoc->m_srcImage, yuvImage, COLOR_BGR2YUV);
		split(yuvImage, planes);
		srcImage = planes[0];
	}
	else {
		srcImage = pDoc->m_srcImage;
	}
	// 최대, 최소 구하기
	double minVal, maxVal;
	minMaxLoc(srcImage, &minVal, &maxVal);
	// 룩업테이블 만들기
	Mat table(256, 1, CV_8U);
	for (int i = 0; i < minVal; i++)
		table.at<uchar>(i) = 0;
	for (int i = 255; i > maxVal; i--)
		table.at<uchar>(i) = 255;
	double scale_factor = 255.0 / (maxVal - minVal);
	for (int i = minVal; i <= maxVal; i++)
		table.at<uchar>(i) = (BYTE)((i - minVal)*scale_factor);
	// 변환수행
	Mat stretchImage;
	LUT(srcImage, table, stretchImage);
	Mat dstImage;
	if (pDoc->m_srcImage.channels() == 3) {
		planes[0] = stretchImage;
		merge(planes, dstImage);
		cvtColor(dstImage, dstImage, CV_YUV2BGR);
	}
	else {
		dstImage = stretchImage;
	}
	ImageShow(dstImage);
}


void CImageProc_LJYView::OnEiContStretching()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CEndInDlg dlg;
	if (dlg.DoModal() == IDOK) {
		Mat srcImage;
		vector<Mat> planes;
		if (pDoc->m_srcImage.channels() == 3) { // 컬러
			Mat yuvImage;
			cvtColor(pDoc->m_srcImage, yuvImage, COLOR_BGR2YUV);
			split(yuvImage, planes);
			srcImage = planes[0];
		}
		else { // 그레이
			srcImage = pDoc->m_srcImage;
		}
		// 지정 영상의 히스토그램 계산.
		int histSize = 256;
		float hValue[] = { 0,histSize };
		const float* ranges[] = { hValue };
		int channels = 0;
		int dims = 1;
		Mat hist;
		calcHist(&srcImage, 1, &channels, Mat(), hist, dims, &histSize, ranges);
		Mat pdf;
		normalize(hist, pdf, 1, 0, NORM_L1);
		// 낮은 문턱값 찾기
		double minVal, maxVal, runSum;
		minVal = runSum = 0;
		for (int i = 0; i < 256; i++) {
			runSum += pdf.at<float>(i);
			if (runSum*100.0 >= dlg.m_fLow) {
				minVal = i;
				break;
			}
		}
		// 높은 문턱값 찾기
		runSum = 0;
		maxVal = 255;
		for (int i = 255; i >= 0; i--) {
			runSum += pdf.at<float>(i);
			if (runSum * 100 >= dlg.m_fHigh) {
				maxVal = i;
				break;
			}
		}
		// 룩업테이블 만들기
		Mat table(256, 1, CV_8U);
		for (int i = 0; i < minVal; i++)
			table.at<uchar>(i) = 0;
		for (int i = 255; i > maxVal; i--)
			table.at<uchar>(i) = 255;
		double scale_factor = 255.0 / (maxVal - minVal);
		for (int i = minVal; i <= maxVal; i++)
			table.at<uchar>(i) = (BYTE)((i - minVal)*scale_factor);
		// 변환수행
		Mat stretchImage;
		LUT(srcImage, table, stretchImage);
		Mat dstImage;
		if (pDoc->m_srcImage.channels() == 3) { // 컬러
			planes[0] = stretchImage;
			merge(planes, dstImage);
			cvtColor(dstImage, dstImage, CV_YUV2BGR);
		}
		else { // 그레이
			dstImage = stretchImage;
		}
		ImageShow(dstImage);
	}
}


void CImageProc_LJYView::FindCoin1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat srcImage, dstImage;

	//컬러인 경우 흑백으로 변환한다
	if (pDoc->m_srcImage.channels() == 3)
		cvtColor(pDoc->m_srcImage, srcImage, CV_BGR2GRAY);
	else
		srcImage = pDoc->m_srcImage;

	vector<Vec3f> circles;
	HoughCircles(srcImage, circles, CV_HOUGH_GRADIENT, 1, 1, 200, 100, 1, 100);
	vector<Vec3f>::const_iterator itc = circles.begin();
	while (itc != circles.end()) {
		rectangle(srcImage, Point((*itc)[0] - (*itc)[2], (*itc)[1] + (*itc)[2]),
			Point((*itc)[0] + (*itc)[2], (*itc)[1] - (*itc)[2]), Scalar(0, 255, 255), 8, 0);
		++itc;
	}

	ImageShow(srcImage);
}


void CImageProc_LJYView::FindCoin2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProc_LJYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat img_gray, img_color, img_binary;
	img_gray = pDoc->m_srcImage;

	threshold(img_gray, img_binary, 80, 255, THRESH_BINARY);
	cvtColor(img_gray, img_color, COLOR_GRAY2BGR);

	Mat img_labels, stats, centroids;
	int numOfLabels = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);


	//라벨링된 이미지중 특정 라벨을 컬러로 표현해주기  
	for (int y = 0; y < img_labels.rows; ++y) {
		int *label = img_labels.ptr<int>(y);
		Vec3b* pixel = img_color.ptr<Vec3b>(y);

		for (int x = 0; x < img_labels.cols; ++x) {
			if (label[x] == 3) {
				pixel[x][2] = 0;
				pixel[x][1] = 255;
				pixel[x][0] = 0;
			}
		}
	}

	//라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
	for (int j = 1; j < numOfLabels; j++) {
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		rectangle(img_binary, Point(left, top), Point(left + width, top + height),
			Scalar(255, 255, 0), 1);

	}

	ImageShow(img_binary);
}
