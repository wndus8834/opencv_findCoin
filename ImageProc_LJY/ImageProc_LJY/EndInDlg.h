#pragma once


// CEndInDlg ��ȭ �����Դϴ�.

class CEndInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEndInDlg)

public:
	CEndInDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEndInDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	float m_fLow;
	float m_fHigh;
};
