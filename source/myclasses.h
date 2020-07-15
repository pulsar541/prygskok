
class DDD
{public: 
 CDemoWnd *pW;
 CWndPlayerOne *pw1;
 int x1,y1;
 int x2,y2;
 DDD(CFrameWnd *pFW)
 {
	 pW=(CDemoWnd*) pFW;
	 x1=200;y1=200;x2=300;y2=250;
 }

void draw()
 {
   pW->pw1->memDC.MoveTo(x1,y1);
   pW->pw1->memDC.LineTo(x2,y2);	
 }
};



class Pol 
{public:
 CDemoWnd *pW;
 CWndPlayerOne *pw1;
 int x1,y1,x2,y2,wigth;
 int x1end,x2end,x1seredina,x2seredina,polov;
 int myNum;
 short nestabil;
// bool izchez;

 Pol(int myNump,int xp,int yp,int wigthp,CFrameWnd *pFW)
 { pW=(CDemoWnd*) pFW;
	 x1=x2=xp;
	 y1=y2=yp;
	 wigth=wigthp;
	 myNum=myNump;
	 nestabil=0;
//	 izchez=0;

	 if(y1<-3000) 
	 {nestabil=1;
	 }
	 if(y1<-5000) 
	 {nestabil=2; wigth+=5;
	 }
	 if(y1<-6000) 
	 {nestabil=4; wigth+=5;
	 }
	 if(y1<-7000) 
	 {nestabil=6; wigth+=5;
	 }
	 if(y1<-8000) 
	 {nestabil=8; //wigth+=5;
//	  izchez=1; 
	 } 

	 polov=wigth*0.5;

 }
 void draw()
 {	
	 
	 x1end=x1+wigth;
	 x1seredina=x1+polov;
	

	 static int tempx;

	 if(nestabil && GameMode==2) 
		 {tempx=(rand()%(1+nestabil+nestabil))-nestabil;
		  x1+=tempx;
		  x2+=tempx;
		 }

	 if(y1>-600 && y1<1200)
	 {
 	 static bool d=1;
	 if(nestabil && GameMode==1) 
		 {tempx=(rand()%(1+nestabil+nestabil))-nestabil;
		  x1+=tempx;
		  x2+=tempx;
	//	  if(izchez)
	//	  { if(tempx>0) d=1;
	//	    else		d=0;
	//	  }
		 }

	  if(myNum==EEE) pW->pw1->memDC.SelectObject(&penBlue);
	  else 
	  { if(y1<lavaY1+600) pW->pw1->memDC.SelectObject(&penSer);
		else  pW->pw1->memDC.SelectObject(&penLava);
	  }
	  if(GameMode==1 || myNum==EEE)
	  {
	   pW->pw1->memDC.MoveTo(x1seredina,y1);
	   pW->pw1->memDC.LineTo(x1seredina*0.25+145*(3-GameMode),y1*0.25+220 );

  }
	  if(myNum==EEE)	
	  {pW->pw1->memDC.MoveTo(x1,y1);
	   pW->pw1->memDC.LineTo(x1seredina,y1-15);
	   pW->pw1->memDC.LineTo(x1end,y1);
	  }
	  if(myNum!=EEE) pW->pw1->memDC.SelectObject(&penBlack);
//	  if(d)
//	  {
	   pW->pw1->memDC.MoveTo(x1,y1);
	   pW->pw1->memDC.LineTo(x1end,y1);
//	  }
//	  pW->pw1->memDC.MoveTo(x1+nestabil+1,y1+2);
//	  pW->pw1->memDC.LineTo(x1+nestabil+1,y1+3);
//	  pW->pw1->memDC.MoveTo(x1+wigth-nestabil,y1+2);
//	  pW->pw1->memDC.LineTo(x1+wigth-nestabil,y1+3);
  	  pW->pw1->memDC.SelectObject(&penBlack);
	 }

	if(GameMode==TWOPLAYERS)
	{ x2seredina=x2+polov;
	  x2end=x2+wigth;
		
		if(y2>-600 && y2<1200)
	 {
	   if(myNum==EEE)pW->pw2->memDC.SelectObject(&penBlue);
	   else pW->pw2->memDC.SelectObject(&penSer);
	   if(myNum==EEE)	  
	   {pW->pw2->memDC.MoveTo(x2seredina,y2);
	    pW->pw2->memDC.LineTo(x2seredina*0.25+145,y2*0.25+220);
		pW->pw2->memDC.MoveTo(x2,y2);
	    pW->pw2->memDC.LineTo(x2seredina,y2-15);
	    pW->pw2->memDC.LineTo(x2end,y2);
	   }
	   if(myNum!=EEE) pW->pw2->memDC.SelectObject(&penWhite);
	   pW->pw2->memDC.MoveTo(x2,y2);
	   pW->pw2->memDC.LineTo(x2end,y2);
	   pW->pw2->memDC.SelectObject(&penBlack);
		}
	}
	 if(GameMode==1)
	 {
	  if(leftkey) x1+=speedX1; 
	  if(rightkey)x1-=speedX1; 
	 }
	else
	 {if(A_key)	  x1+=speedX1; 
	  if(D_key)	  x1-=speedX1; 
	  if(leftkey) x2+=speedX2; 
	  if(rightkey)x2-=speedX2; 
	 } 

 }
};

char str[5];
char str2[5];

class Nechto 
{public:
 CDemoWnd *pW;
 int X1,X2,Y1,Y2,W,H;
 double healt;

 Nechto(int xp,int yp,CFrameWnd *pFW)
 { 
	 pW=(CDemoWnd*) pFW;
	 X1=X2=xp;
	 Y1=Y2=yp;
	 W=35;
	 H=40-5*(GameMode==2);
	 speedX1=SPEED+2; 
  	 speedH1=0; 
	 healt=100;

 } 
 char str3[100];
 int ochki;

 void draw()
 {
	 pW->pw1->memDC.SetTextColor(RGB(150,150,150));

	 sprintf(str3,"- - - -  %d см  - - - -",pW->pol[EEE]->y1+12000);// Возвращает загрузку процессора
 
	 pW->pw1->memDC.TextOut(100,ppp,str3);


	 if(GameMode==TWOPLAYERS)
	 {
	 pW->pw1->memDC.TextOut(5,40,"[A]     <-");
	 pW->pw1->memDC.TextOut(5,60,"[D]     ->");	 
	 pW->pw1->memDC.TextOut(5,80,"[====]  прыжок");
	 }

	if(GameMode==ONEPLAYER)
	{//if(Y1>lavaY1+600) 
	 pW->pw1->memDC.SelectObject(&brWhite);
	 pW->pw1->memDC.Rectangle(CRect(X1-5*leftkey,Y1,X1+W+5*rightkey,Y1-H+5*(leftkey+rightkey-jumping1)));	 
	}
//	pW->pw1->memDC.TextOut(X1-12,Y1-H-25,"+");
	
	pW->pw1->memDC.SetTextColor(RGB(255*(healt<=50),255*(healt>50),0));
	pW->pw1->memDC.TextOut(X1-5,Y1-H-25,str);

//	pW->pw2->memDC.SelectObject(&penBlack);
	if(GameMode==TWOPLAYERS)
	{	pW->pw1->memDC.SetTextColor(RGB(0,0,0));
	  pW->pw1->memDC.Rectangle(CRect(X1-5*A_key,Y1,X1+W+5*D_key,Y1-H+5*(D_key+A_key-jumping1)));	 
	  pW->pw2->memDC.Rectangle(CRect(X2-5*A_key,Y2,X2+W+5*D_key,Y2-H+5*(D_key+A_key)));
	 
	}
 }
};



class Nechto2 
{public:
 CDemoWnd *pW;

 double X1,X2,Y1,Y2,W,H;
 double healt;
 Nechto2(int xp,int yp,CFrameWnd *pFW)
 { 
	 pW=(CDemoWnd*) pFW;
	 X1=X2=xp;
	 Y1=Y2=yp;
	 W=30;
	 H=45;
	 speedX2=SPEED; 
  	 speedH2=0; 
	 healt=100;

 } 
 void draw()
 {  
	
	  pW->pw2->memDC.SelectObject(&penWhite);
	 pW->pw2->memDC.MoveTo(X1,Y1);
	 pW->pw2->memDC.LineTo(X1+W/2-leftkey*7+rightkey*7,Y1-H-jumping2*5);
	 pW->pw2->memDC.LineTo(X1+W,Y1);
	 pW->pw2->memDC.LineTo(X1,Y1);

	 pW->pw2->memDC.SetTextColor(RGB(255,255,255));
	 pW->pw2->memDC.TextOut(5,40,"с. влево  - <<");
	 pW->pw2->memDC.TextOut(5,60,"с. вправо - >>");
	 pW->pw2->memDC.TextOut(5,80,"с. вверх  - прыжок");


	 pW->pw1->memDC.SelectObject(&penBlack);
	 pW->pw1->memDC.MoveTo(X2,Y2);
	 pW->pw1->memDC.LineTo(X2+W/2-leftkey*7+rightkey*7,Y2-H-jumping2*5);
	 pW->pw1->memDC.LineTo(X2+W,Y2);
	 pW->pw1->memDC.LineTo(X2,Y2);

	 pW->pw2->memDC.SetTextColor(RGB(255*(healt<=50),255*(healt>50),0));
	 pW->pw2->memDC.TextOut(X1-5,Y1-H-25,str2);
	


 }
};

