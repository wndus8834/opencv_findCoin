#pragma once


// CThreshDlg dialog

class CThreshDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThreshDlg)

public:
	CThreshDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CThreshDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THRESHOLD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_ucThresh;
	int m_nType;
	int m_nOptimal;
};
