#pragma once


// CGammaDlg dialog

class CGammaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGammaDlg)

public:
	CGammaDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGammaDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAMMA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_fGamma;
};
