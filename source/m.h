

 int ppp=0;

class CDemoApp : public CWinApp
{public: 

  BOOL  InitInstance();

};

class Nechto;
class Nechto2;
class Pol;
class DDD;
class CWndPlayerOne;
class CDemoWnd:public CFrameWnd
{public :
  int x1,y1,dx1,dy1;
 CWndPlayerOne *pw1;
 CWndPlayerOne *pw2;


  Nechto *kvadrat;
  Nechto2 *treug;

  Pol *pol[KOL];
  DDD *doska;

  CBitmap bmp;
  CBitmap image_fon;
  CDC memDC;
  CDC mem_fon;
   CDemoWnd(); 
   ~CDemoWnd();
 
  CWinThread *mainthread;
  static UINT MainThread(LPVOID p);
    afx_msg void OnPaint();
  void MyPaint();
  afx_msg void OnKeyDown(UINT nChar,UINT nRepCnt, UINT nFlags );
  afx_msg void OnKeyUp(UINT nChar,UINT nRepCnt, UINT nFlags );
  afx_msg void OnMouseMove(UINT,CPoint p);
  afx_msg void OnLButtonDown(UINT,CPoint p);
  afx_msg void OnLButtonUp(UINT,CPoint p); 
 afx_msg void OnRButtonDown(UINT,CPoint p);
  afx_msg void OnRButtonUp(UINT,CPoint p);



  DECLARE_MESSAGE_MAP();
};



BEGIN_MESSAGE_MAP(CDemoWnd,CFrameWnd)
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_PAINT()
//ON_WM_MOUSEMOVE()
//ON_WM_LBUTTONDOWN()
//ON_WM_LBUTTONUP()
//ON_WM_RBUTTONDOWN()
//ON_WM_RBUTTONUP()
//ON_WM_TIMER()
END_MESSAGE_MAP()

class CWndPlayerOne : public CWnd
{ 
 public: 
    CDemoWnd *pW;
//	long maxX,maxY;	
	CDC memDC;
	long Y;
	CBitmap bmp;
	bool lp;
	void MyPaint();
	afx_msg void OnPaint();
	CWndPlayerOne();
DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CWndPlayerOne,CWnd)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_DESTROY()
END_MESSAGE_MAP ()


	int ww=800/GameMode;

CWndPlayerOne::CWndPlayerOne()
{//maxX=GetSystemMetrics(SM_CXSCREEN);
 //maxY=GetSystemMetrics(SM_CYSCREEN);
 
 srand( (unsigned)time( NULL ) );

	CClientDC dc(this);
	memDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc,ww,600);
	memDC.SelectObject(&bmp);
	memDC.SetBkMode(TRANSPARENT);
	ShowCursor(0);
}

void CWndPlayerOne::MyPaint()
{
Invalidate(0);
}

void CWndPlayerOne::OnPaint()
{ CPaintDC dc(this);
  dc.BitBlt(0,0,ww,600,&memDC,0,0,SRCCOPY);  
  
}


