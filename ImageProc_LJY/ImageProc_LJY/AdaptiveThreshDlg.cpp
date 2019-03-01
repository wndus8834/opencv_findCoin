// AdaptiveThreshDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProc_LJY.h"
#include "AdaptiveThreshDlg.h"
#include "afxdialogex.h"


// CAdaptiveThreshDlg dialog

IMPLEMENT_DYNAMIC(CAdaptiveThreshDlg, CDialogEx)

CAdaptiveThreshDlg::CAdaptiveThreshDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADAPTIVE_THRESHOLD, pParent)
	, m_nMethod(0)
	, m_nType(0)
{

}

CAdaptiveThreshDlg::~CAdaptiveThreshDlg()
{
}

void CAdaptiveThreshDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_METHOD, m_nMethod);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
}


BEGIN_MESSAGE_MAP(CAdaptiveThreshDlg, CDialogEx)
END_MESSAGE_MAP()


// CAdaptiveThreshDlg message handlers
