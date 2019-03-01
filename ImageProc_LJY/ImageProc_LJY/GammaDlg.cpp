// GammaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProc_LJY.h"
#include "GammaDlg.h"
#include "afxdialogex.h"


// CGammaDlg dialog

IMPLEMENT_DYNAMIC(CGammaDlg, CDialogEx)

CGammaDlg::CGammaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GAMMA, pParent)
	, m_fGamma(1)
{

}

CGammaDlg::~CGammaDlg()
{
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GAMMA, m_fGamma);
}


BEGIN_MESSAGE_MAP(CGammaDlg, CDialogEx)
END_MESSAGE_MAP()


// CGammaDlg message handlers
