// EndInDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProc_LJY.h"
#include "EndInDlg.h"
#include "afxdialogex.h"


// CEndInDlg ��ȭ �����Դϴ�.

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


// CEndInDlg �޽��� ó�����Դϴ�.
