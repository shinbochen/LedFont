// LEDFontDlg.h : header file
//

#if !defined(AFX_LEDFONTDLG_H__51094159_58CA_4D72_9B95_35E9095D81F3__INCLUDED_)
#define AFX_LEDFONTDLG_H__51094159_58CA_4D72_9B95_35E9095D81F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLEDFontDlg dialog
class CLEDFontDlg : public CDialog
{
// Construction
public:
	CLEDFontDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLEDFontDlg)
	enum { IDD = IDD_LEDFONT_DIALOG };
	CString	m_strLED;
	CString	m_strStatus;
	//}}AFX_DATA
public:
	CDC		*m_pCDC;
public:
	void CLEDFontDlg::DrawLED( unsigned char *p, int  nLen, int x, int y );
	void CLEDFontDlg::RawBackGroup( unsigned char *pDest, int random);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLEDFontDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLEDFontDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLed();
	afx_msg void OnButtonLedFont();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEDFONTDLG_H__51094159_58CA_4D72_9B95_35E9095D81F3__INCLUDED_)
