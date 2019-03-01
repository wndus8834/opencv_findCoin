#pragma once


// CAdaptiveThreshDlg dialog

class CAdaptiveThreshDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdaptiveThreshDlg)

public:
	CAdaptiveThreshDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdaptiveThreshDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADAPTIVE_THRESHOLD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nMethod;
	int m_nType;
};
