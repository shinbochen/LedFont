// LEDFontDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LEDFont.h"
#include "LEDFontDlg.h"
#include "led.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		MAXSPACEX   9
#define		MAXSPACEY   9
#define		MAX_ROW	   72
#define		MAX_COL	   90

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLEDFontDlg dialog

CLEDFontDlg::CLEDFontDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLEDFontDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLEDFontDlg)
	m_strLED = _T("");
	m_strStatus = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCDC = NULL;
}

void CLEDFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLEDFontDlg)
	DDX_Text(pDX, IDC_EDIT_DATA, m_strLED);
	DDX_Text(pDX, IDC_STATUS, m_strStatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLEDFontDlg, CDialog)
	//{{AFX_MSG_MAP(CLEDFontDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LED, OnButtonLed)
	ON_BN_CLICKED(IDC_BUTTON_LED_FONT, OnButtonLedFont)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLEDFontDlg message handlers



//////////////////////////////////////////////////////////////////////////
//

bool  GetGBCodeToLedData( unsigned char *pDest,  unsigned char *pSrc){
	
	unsigned int	qh = 0;
	unsigned int	wh = 0;
	unsigned int    location;
	char			*p_chs16 = "CHS16";	
	char			*p_eng16 = "ASC16";	

	CFile			oFile;
	if( (pSrc == NULL) || (pDest == NULL) ){
		return FALSE;
	}

	if( *pSrc > 128 ){
		if( oFile.Open( p_chs16, CFile::modeRead ) ){
			
			qh = *pSrc - 0xA0;
			wh = *(pSrc + 1) - 0xA0;
			location = (94 * (qh - 1) + (wh - 1)) * 32;		
			oFile.Seek( location, CFile::begin);	
			oFile.Read( pDest, 32 );
			oFile.Close();
		}
	}
	else{
		if( oFile.Open( p_eng16, CFile::modeRead ) ){

			location = pSrc[0] << 4 ;		
			oFile.Seek( location, CFile::begin);	
			oFile.Read( pDest, 16 );
			oFile.Close();
		}	
	}
	return TRUE;
}

BOOL CLEDFontDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	int			 i = 0;
	CRect		 oRect;
	
	//GetDlgItem(IDC_STATIC_LED)->RedrawWindow( );
	//GetDlgItem(IDC_STATIC_LED)->GetClientRect( &oRect );
	m_pCDC= GetDlgItem(IDC_STATIC_LED)->GetDC();
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLEDFontDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLEDFontDlg::OnPaint() 
{
	OnButtonLed();
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLEDFontDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//////////////////////////////////////////////////////////////////////////
//
void CLEDFontDlg::OnButtonLed() 
{	
	int i = 0;
	CRect	 oRect;

	GetDlgItem(IDC_STATIC_LED)->RedrawWindow();
	CPen *pen=new CPen();
	LOGPEN logpen={PS_SOLID,2,RGB(255,0,0)};

	pen->CreatePenIndirect(&logpen);
	CPen * OldPen;
	OldPen = m_pCDC->SelectObject(pen);

	
	for(i=0 ;i<=MAX_ROW;i++)
	{
		m_pCDC->MoveTo( 0, i*MAXSPACEY);
		m_pCDC->LineTo( MAXSPACEX*MAX_COL, i*MAXSPACEY);
		//m_pCDC->MoveTo( 0, i*MAXSPACEY+3);
		//m_pCDC->LineTo( MAXSPACEX*MAX_COL, i*MAXSPACEY+3);
		//m_pCDC->MoveTo( 0, i*MAXSPACEY+6);
		//m_pCDC->LineTo( MAXSPACEX*MAX_COL, i*MAXSPACEY+6);
	}
	for(i=0 ;i<=MAX_COL;i++)
	{
		m_pCDC->MoveTo(i*MAXSPACEX,0);
		m_pCDC->LineTo(i*MAXSPACEX, MAXSPACEY*MAX_ROW);
	}
	delete pen;
	m_pCDC->SelectObject(OldPen);
}
//////////////////////////////////////////////////////////////////////////
//
void CLEDFontDlg::OnButtonLedFont(){

	
	SetTimer( IDC_TIMER, 100, NULL );


	UpdateData(TRUE);
	
}
//////////////////////////////////////////////////////////////////////////
//
void CLEDFontDlg::DrawLED( unsigned char *p, int  nLen, int  x, int y ){

	unsigned int	nCnt = 0;
	unsigned char	nTmp = 0;
	int				x1,y1;
	int				sumbit = 0;


	x1 = x;
	y1 = y;
	for ( nCnt = 0; nCnt < nLen; nCnt++ ){

		nTmp = *(p+nCnt);
		for ( int bit = 0; bit < 8; bit++, sumbit++ ){
			if( nTmp & BIT[bit]){
				
				CBrush *pBh = NULL;
				// B
				if( (sumbit%3) == 0){
					pBh=new CBrush(RGB(0,0,255));
				}
				// G
				else if( (sumbit%3) == 1){
					pBh=new CBrush(RGB(0,255,0));
				}
				// R
				else{
					pBh=new CBrush(RGB(255,0,0));
				}
				m_pCDC->FillRect( CRect(x1, y1, x1+MAXSPACEX, y1+MAXSPACEY) , pBh);
				delete pBh;
			}
			y1+=MAXSPACEY;
			if( y1>= 24*3*MAXSPACEY ){ 
				//TRACE( "return:%d\r\n",nCnt);
				x1 += MAXSPACEX;
				y1 = y;
			}
		}

/*		for ( int bit = 8; bit >0; bit-- ){
			if( nTmp & BIT[bit-1]){
				
				CBrush *pBh = NULL;
				pBh=new CBrush(RGB(255,255,0));
				m_pCDC->FillRect( CRect(x1, y1, x1+8, y1+8) , pBh);
				delete pBh;
			}
			x1+=8;
			if(x1>=320*8*8){
				x1 =x;
				y1 =y1+8;
			}
		}*/

		
	}	
}
void CLEDFontDlg::RawBackGroup(unsigned char*pDest, int random){

	CFile		oFile;
	ULONG		pos;

	if( oFile.Open( "bmp.bin", CFile::modeRead ) ){
		
		random = random%1758;
		pos = random*864;
		oFile.Seek( pos, CFile::begin);
		oFile.Read( pDest, 864 );
		oFile.Close();
	}
}
unsigned char	nTmp[864];

void CLEDFontDlg::OnTimer(UINT nIDEvent) 
{
	int				nLen = 0;
	static int		nbRandom = 0;
	static int		nfRandom = 0;

	
	// TODO: Add your message handler code here and/or call default
	if( nIDEvent == IDC_TIMER ){
		GetDlgItem(IDC_STATIC_LED)->RedrawWindow();

		nLen = TextOut( (unsigned char*)m_strLED.GetBuffer(0), m_strLED.GetLength(), LED_WHITE );
		m_strLED.ReleaseBuffer();
		RawBackGroup( &nVirtualLED[0][0], nbRandom);
		//memset( &nVirtualLED[0][0], 0, 864 );
		
		// 还没有显示完成所有
		if( nfRandom + 90 < nLen ){
			TextMove( &nVirtualLED[0][0], 0, 4, 90, 24, 
				&nTextPanel[0][0], nfRandom, 0, nLen,16, gFontColor );
			
			nfRandom++;
		}
		else if( nfRandom+90 == nLen ){

			if( nbRandom%3 ){
				TextMove( &nVirtualLED[0][0], 0, 4, 90, 24, 
					&nTextPanel[0][0], nfRandom, 0, nLen,16, gFontColor );
			}
			else{
			TextMove( &nVirtualLED[0][0], 0, 4, 90, 24, 
				&nTextPanel[0][0], nfRandom, 0, nLen,16, gFontColor );
			
				nfRandom++;
			}

		}
		else if(nfRandom==nLen) {
			nfRandom = 0;
		}
		else{
			
			TextMove( &nVirtualLED[0][0], 0, 4, 90, 24, 
				&nTextPanel[0][0], nfRandom, 0, nLen,16, gFontColor );
				nfRandom++;
			
		}

		nLen = HConvertV(nTmp, &nVirtualLED[0][0], 12, 24*3 );
		//OnButtonLed( );
		m_strStatus.Format( "%d", nbRandom );
		UpdateData( FALSE );
		
		DrawLED( nTmp, 810, 0, 0 );

	}
	nbRandom++;
	CDialog::OnTimer(nIDEvent);
}





















