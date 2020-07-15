#pragma comment(lib, "fmodvc.lib")

#include <afxwin.h>
#include <afxmt.h>
//#include <mmsystem.h>

#include "math.h"
#include "fmod.h"						
										
#include<windows.h>


#define U_	1
#define D_	2
#define L_	3
#define R_	4
#define namewin	 "Прыг-Скок"
#define rectwin	  -3,-32,maxX+3,maxY
#define winW 800
#define winH 600

#define KOL	1100 
#define SPEED	4
#define ONEPLAYER  1
#define TWOPLAYERS 2
int visota=0;


#define PIOVER180 0.017453292

#define SONG_NAME  "Sound\\ACIDBATH.WAV"
#define SONG_NAME2 "Sound\\BOING!.WAV"
#define SONG_NAME3 "Sound\\SH.WAV"

int GameMode = 1;
//int maxX,maxY,PX,PY;

bool upkey=false,W_key=false;
bool downkey=false,S_key=false;
bool leftkey=false,A_key=false;
bool rightkey=false,D_key=false;
bool shiftkey=false,Ctrl_key=false;


bool jumping1;
bool jumping2;
int jc=0;
//bool vverh=0;
bool dobroY1=0;
bool dobroY2=0;
int fixi1;
int fixi2;
int t1=0;
int t2=0;
int speedX1; 
int speedH1; 
int speedX2; 
int speedH2; 

float lavaY1=0;
float lavaY2=0;
bool UnderLava1=0;
bool UnderLava2=0;

double prirost=0.00;
int counter=0; 

CPen penWhite(PS_SOLID,5,RGB(255,255,255));  

CPen penBlack(PS_SOLID,3,RGB(0,0,0));  
CPen penSvetSer(PS_SOLID,1,RGB(120,120,120));
CPen penSer(PS_SOLID,1,RGB(220,220,220));  
CPen penBlue(PS_SOLID,2,RGB(0,0,255));  
CPen penLava(PS_SOLID,1,RGB(150,200,150)); 
CPen penLava2(PS_SOLID,1,RGB(200,255,200)); 
CBrush brLava(RGB(200,255,200)); 
CBrush brLavaPoverh(RGB(190,240,190)); 
CBrush brWhite(RGB(255,255,255));
CBrush brBlack(RGB(0,0,0));
int EEE;

FSOUND_SAMPLE *pSound;					// Указатель на композицию
FSOUND_SAMPLE *pSound2;					// Указатель на композицию
FSOUND_SAMPLE *pSound3;					// Указатель на композицию
int soundChannel[3]={0,1,2};				// Звуковой канал композиции



double SIN(double d)
{static bool predvarit=true;
 static double massiv[3600];
 if(predvarit) 
 {for(int i=0;i<3600;i++)
  massiv[i]=sin((double)i/10);
  predvarit=false;
 }
 return massiv[(int)(d*10)];
}

double COS(double d)
{static bool predvarit=true;
 static double massiv[3600];
 if(predvarit) 
 {for(int i=0;i<3600;i++)
  massiv[i]=cos((double)i/10);
  predvarit=false;
 }
 return massiv[(int)(d*10)];
}


#include "m.h"
#include "myclasses.h"

HWND hwnd;
#include "threads.h"

//#include "resource.h"


//char str[50];




BOOL CDemoApp::InitInstance()                    
{CDemoWnd *pW=new CDemoWnd();
m_pMainWnd=pW;
m_pMainWnd->ShowWindow(m_nCmdShow);
return TRUE;
}

CDemoWnd::~CDemoWnd()
{
	FSOUND_StopSound(soundChannel[0]);
	FSOUND_StopSound(soundChannel[1]);
	FSOUND_StopSound(soundChannel[2]);
	FSOUND_Close();
}


CDemoWnd::CDemoWnd()
{	CBrush b(RGB(0,0,0));
	HINSTANCE__ * p;	
//	maxX=GetSystemMetrics(SM_CXSCREEN);
//	maxY=GetSystemMetrics(SM_CYSCREEN);
 
	Create(AfxRegisterWndClass(0,0,NULL,LoadIcon(NULL,"ID_ICON")),namewin,WS_VISIBLE,CRect(800/2-400,600/2-300,800/2+400,600/2+300));

	hwnd=GetSafeHwnd();

	srand( (unsigned)time( NULL ) );
	CClientDC dc(this);
	memDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc,800,600);
	memDC.SelectObject(&bmp);
	ShowCursor(0);
	memDC.Rectangle(CRect(0,0,800,600));	
	memDC.TextOut(400-100,300-200,"Игра ''Прыг-Скок'' (alpha-версия)");
	memDC.TextOut(400-100,300-170,"Автор - Евгений Усейнов");
	memDC.TextOut(470,300-170,(char)169);
	memDC.TextOut(400-100,300-130,"Цель игры:");
	memDC.TextOut(400-100,300-110,"прыгая по чёрным платформам,");
	memDC.TextOut(400-100,300-90,"добраться до синей платформы,");
	memDC.TextOut(400-100,300-70,"расположенной где-то наверху.");


	memDC.TextOut(400-100,300,   "[1]      ->  1 игрок");
	memDC.TextOut(400-100,300+25,"[2]      ->  2 игрока");
	memDC.TextOut(400-100,300+50,"[Esc]  ->  выход");

	memDC.TextOut(10,600-80,"Каждый раз при старте, компьютер размещает платформы случайным образом,");

//	Invalidate(0);

}

 
void CDemoWnd::OnPaint()
{
	  CPaintDC dc(this);
	  dc.BitBlt(0,0,800,600,&memDC,0,0,SRCCOPY);  
}


void CDemoWnd::MyPaint()
{	 

}
 static bool dmode=true;
afx_msg void CDemoWnd::OnKeyDown(UINT nChar,UINT nRepCnt, UINT nFlags )
{   


 
   if ((nChar=='1' || nChar=='2') && dmode)
   {dmode=false;
    memDC.Rectangle(CRect(0,0,800,600));
	 switch(nChar)
	 {case '1': GameMode=ONEPLAYER; 
		 wsprintf(str,"%d",GameMode);
		 memDC.TextOut(400-5,300,str);
		 memDC.TextOut(400+7,300,"игрок");
		 break;	
	  case '2': GameMode=TWOPLAYERS; 
		  wsprintf(str,"%d",GameMode); 
		  memDC.TextOut(400-5,300+25,str);
		  memDC.TextOut(400+7,300+25,"игрока");
		  break;	 
	 }
   
		memDC.SetBkMode(TRANSPARENT);

		kvadrat= new Nechto(800/(2*GameMode)-20,300,this);
 		kvadrat->X2-=100;


		if(GameMode==TWOPLAYERS)
		{	treug= new Nechto2(800/4-20,300,this);
			treug->X2+=100;
			pw2=new CWndPlayerOne;
			pw2->Create(NULL,"2", WS_VISIBLE|WS_BORDER,CRect(400,0,800,600),this,22);
			pw2->ShowWindow(SW_SHOW);
		}

		pol[0]= new Pol(0,winW/(2*GameMode)-25+50,2*winH/3,2+100,this);
		pol[1]= new Pol(0,winW/(2*GameMode)-25-50,2*winH/3,2+100,this);

		for(int i=2;i<KOL/20;i++)
		pol[i]= new Pol(i,-700/GameMode+rand()%(800/GameMode+1400/GameMode),rand()%4000-4000+700,2+rand()%500,this);


		for(i=KOL/20;i<KOL;i++)
			pol[i]= new Pol(i,-800/GameMode+rand()%(800/GameMode+1600/GameMode),rand()%12000-12000+700,3+rand()%60,this);	  
		

		int temp=0;
		for(i=1;i<KOL;i++)
		{
		  if(pol[i]->y1<temp)
		  {temp=pol[i]->y1;
		   EEE=i; 
		   pol[i]->wigth=100;
		  }  
		}

		for(i=0;i<KOL;i++) 
		{pol[i]->x1+=50;
		 pol[i]->x2-=50;
		}

		doska=new DDD(this);


		pw1=new CWndPlayerOne;
		pw1->Create(NULL,"1", WS_VISIBLE,CRect(0 ,0,800/GameMode,600),this,11);
		pw1->ShowWindow(SW_SHOW);

		mainthread=AfxBeginThread(MainThread,this);
   
}
		
	if (nChar== VK_UP)	upkey=true;	
	if (nChar== VK_DOWN) downkey=true;  	
    if (nChar== VK_LEFT) leftkey=true;  	
	if (nChar== VK_RIGHT) rightkey=true;	

	
if(GameMode==1)	
{	if (nChar==VK_CONTROL && (!dobroY1 || UnderLava1))
	{jumping1=true;
	 t1=0;
	}
}
else
{	if (nChar==VK_SPACE && (!dobroY1 || UnderLava1))
	{jumping1=true;
	 t1=0;
	}
	if (nChar== VK_CONTROL && (!dobroY2 || UnderLava2) )
	{jumping2=true;
	 if(!UnderLava2)soundChannel[1] = FSOUND_PlaySound(FSOUND_FREE,pSound2);
	 t2=0;
	}
	if (nChar== 'W') W_key=1;	
	if (nChar== 'S') S_key=1;  	
    if (nChar== 'A') A_key=1;  	
	if (nChar== 'D') D_key=1; 
}

}


afx_msg void CDemoWnd::OnKeyUp(UINT nChar,UINT nRepCnt, UINT nFlags )  
{
/////////////////_1_
	if (nChar== VK_UP)	upkey=false;	
	if (nChar== VK_DOWN) downkey=false;  	
    if (nChar== VK_LEFT) leftkey=false;  	
	if (nChar== VK_RIGHT) rightkey=false; 	

	if(GameMode==1)
	{	if (nChar== VK_CONTROL &&jumping1)
		{jumping1=false;
		 t1=0;
		 speedH1=0;
		 prirost+=0.01;
		 jc++;
		}
	}
	else
	{	if (nChar== VK_SPACE &&jumping1)
		{jumping1=false;
		 t1=0;
		 speedH1=0;
		}
	}
///////////////////_2_
	if(GameMode==2)	
	{	if (nChar== 'W') W_key=false;	
		if (nChar== 'S') S_key=false;  	
		if (nChar== 'A') A_key=false;  	
		if (nChar== 'D') D_key=false; 
		
		if (nChar==VK_CONTROL &&  jumping2)
		{jumping2=false;
		 t2=0;
		 speedH2=0;
		}
	}
	if (nChar== VK_ESCAPE)  
	{
	//	delete  mem_fon;
	//	delete  memDC;
		FSOUND_StopSound(soundChannel[0]);
		FSOUND_StopSound(soundChannel[1]);
		FSOUND_StopSound(soundChannel[2]);
		FSOUND_Close();
		 SendMessage(WM_CLOSE);
	}

}

bool lb;
bool rb;
void  CDemoWnd::OnMouseMove(UINT,CPoint p)
{

	static int x0=0;
	static int y0=0;
	
	if(lb) 
	{//tt+=p.x-x0;
	 //ff-=p.y-y0;
	 //Invalidate(false);
	}

	x0=p.x;
	y0=p.y;
}

afx_msg void  CDemoWnd::OnLButtonDown(UINT,CPoint p){ lb=true;}
afx_msg void  CDemoWnd::OnLButtonUp(UINT,CPoint p){   lb=false;}
afx_msg void  CDemoWnd::OnRButtonDown(UINT,CPoint p){ rb=true;}
afx_msg void  CDemoWnd::OnRButtonUp(UINT,CPoint p){ rb=false;}

CDemoApp app;



