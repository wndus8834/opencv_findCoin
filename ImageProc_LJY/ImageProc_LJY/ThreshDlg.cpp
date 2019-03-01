// ThreshDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProc_LJY.h"
#include "ThreshDlg.h"
#include "afxdialogex.h"


// CThreshDlg dialog

IMPLEMENT_DYNAMIC(CThreshDlg, CDialogEx)

CThreshDlg::CThreshDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_THRESHOLD, pParent)
	, m_ucThresh(0)
	, m_nType(0)
	, m_nOptimal(0)
{

}

CThreshDlg::~CThreshDlg()
{
}

void CThreshDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THRESH, m_ucThresh);
	DDX_CBIndex(pDX, IDC_COMBO_THRESH, m_nType);
	DDX_CBIndex(pDX, IDC_COMBO_OPTIMAL, m_nOptimal);
}


BEGIN_MESSAGE_MAP(CThreshDlg, CDialogEx)
END_MESSAGE_MAP()


// CThreshDlg message handlers
