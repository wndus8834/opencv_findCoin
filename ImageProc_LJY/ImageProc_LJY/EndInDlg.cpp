// EndInDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProc_LJY.h"
#include "EndInDlg.h"
#include "afxdialogex.h"


// CEndInDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEndInDlg, CDialogEx)

CEndInDlg::CEndInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_fLow(0)
	, m_fHigh(0)
{

}

CEndInDlg::~CEndInDlg()
{
}

void CEndInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOW, m_fLow);
	DDX_Text(pDX, IDC_EDIT_HIGH, m_fHigh);
}


BEGIN_MESSAGE_MAP(CEndInDlg, CDialogEx)
END_MESSAGE_MAP()


// CEndInDlg 메시지 처리기입니다.
