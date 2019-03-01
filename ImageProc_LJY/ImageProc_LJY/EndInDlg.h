#pragma once


// CEndInDlg 대화 상자입니다.

class CEndInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEndInDlg)

public:
	CEndInDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEndInDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fLow;
	float m_fHigh;
};
