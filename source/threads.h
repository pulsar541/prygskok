UINT CDemoWnd::MainThread(LPVOID p)
{ CDemoWnd *pW=(CDemoWnd*) p;
  static int k=0;
 
 // pW->mem_fon.CreateCompatibleDC(&pW->memDC);
//  pW->image_fon.LoadBitmap(ID_FIELD);
 // pW->mem_fon.SelectObject(&pW->image_fon);


	FSOUND_GetVersion();
	FSOUND_Init(44100, 32, FSOUND_INIT_GLOBALFOCUS);
	pSound = FSOUND_Sample_Load(FSOUND_FREE,SONG_NAME,0,0);
	pSound2 = FSOUND_Sample_Load(FSOUND_FREE,SONG_NAME2,0,0);
	pSound3 = FSOUND_Sample_Load(FSOUND_FREE,SONG_NAME3,0,0);

   wsprintf(str,"%d %%",(int)pW->kvadrat->healt);
   if(GameMode==TWOPLAYERS)
	   wsprintf(str2,"%d %%",(int)pW->treug->healt);


  int dt=4;
  int dt2=4;
	bool sh=true;
  int i;
  
  static CRect rect(0,0,800,600);
  //static CPen superpen(PS_SOLID,800,RGB(255,255,255));
  while(1)
  {
	  pW->pw1->memDC.SelectObject(&brWhite);
	pW->pw1->memDC.Rectangle(rect);	
	if(GameMode==2)
	{  pW->pw2->memDC.SelectObject(&brBlack);
		pW->pw2->memDC.Rectangle(rect);	

	}
	static int pp1=pW->pol[0]->x1-1000;
 if(GameMode==2)
	{if(A_key) pp1+=speedX1;
     if(D_key) pp1-=speedX1;
	}
else
	{if(leftkey) pp1+=speedX1;
	 if(rightkey) pp1-=speedX1;
	}
	static int pp2=pW->pol[0]->x2-1000;
    if(leftkey) pp2+=speedX2;
    if(rightkey) pp2-=speedX2;

	 


 	 if(A_key) 
	 {pW->kvadrat->X2-=speedX1; 
	  if(GameMode==TWOPLAYERS)
		  pW->treug->X2+=speedX1;

	 }
	 if(D_key)  
	 {pW->kvadrat->X2+=speedX1;
	  if(GameMode==TWOPLAYERS)
		  pW->treug->X2-=speedX1;
	 }

	 if(leftkey) 
	 {
	  if(GameMode==TWOPLAYERS)
	    pW->treug->X2-=speedX2; 
	  pW->kvadrat->X2+=speedX2;
	 }
	 if(rightkey) 
	 { if(GameMode==TWOPLAYERS)
	     pW->treug->X2+=speedX2;
	   pW->kvadrat->X2-=speedX2;
	 }

 
  //ðèñóåì æèäêîñòü
	 
	 static int lavaFarY1;
	 static int lavaNearY1;
    static int lavaX1=pW->kvadrat->X1;

	 lavaNearY1=600+lavaY1;
	 lavaFarY1=lavaNearY1*0.25+220;

 if(GameMode==1)
 {
 

   if(lavaFarY1<600)
   {
	   pW->pw1->memDC.SelectObject(&penLava);	
	   pW->pw1->memDC.SelectObject(&brLava);
	   pW->pw1->memDC.Rectangle(CRect(0,lavaFarY1,800,600));
	   if(lavaFarY1<lavaNearY1) 
	   {   pW->pw1->memDC.SelectObject(&brLavaPoverh);
	       pW->pw1->memDC.Rectangle(CRect(0,lavaFarY1,800,lavaNearY1));
	   
	   } 
	   else 
	   {
	    pW->pw1->memDC.TextOut(((lavaX1+=rightkey*2)-=leftkey*2)+rand()%2,lavaNearY1+35+rand()%2,"Ê è Ñ ë Î ò À");
	    for(i=0;i<100;i++)
 			{ pW->pw1->memDC.MoveTo(i*50-1400+pp1,lavaNearY1);
 			  pW->pw1->memDC.LineTo(430+i*10-400+pp1*0.2,lavaFarY1);
			}
	   }

	  pW->pw1->memDC.MoveTo(0,lavaNearY1);
	  pW->pw1->memDC.LineTo(800,lavaNearY1); 
	  pW->pw1->memDC.SelectObject(&brWhite);
	   
   }
 }

 	 static int lavaNearY2;
	 lavaNearY2=600+lavaY2;

   if(GameMode==TWOPLAYERS)
   { 

	pW->pw2->memDC.SelectObject(&brLava);  
	pW->pw2->memDC.SelectObject(&penLava);
   
	if(lavaNearY2<600)
		pW->pw2->memDC.Rectangle(CRect(0,lavaNearY2,800,600));
	pW->pw2->memDC.SelectObject(&brWhite);  
	pW->pw2->memDC.SelectObject(&penBlack);
	/////////////////
	pW->pw1->memDC.SelectObject(&brLava);  
	pW->pw1->memDC.SelectObject(&penLava);
   
	if(lavaNearY1<600)
		pW->pw1->memDC.Rectangle(CRect(0,lavaNearY1,800,600));
	pW->pw1->memDC.SelectObject(&brWhite);  
	pW->pw1->memDC.SelectObject(&penBlack);
   }
 


  
   pW->doska->draw();



   for(i=0;i<KOL;i++)
   {pW->pol[i]->draw();
    if(pW->pol[i]->y1>lavaNearY1 && i!=EEE) 
		{  if(pW->pol[i]->y1<2000)
			pW->pol[i]->y1++;
		}
    if(pW->pol[i]->y2>lavaNearY2 && i!=EEE) 
		{  if(pW->pol[i]->y2<2000)
			pW->pol[i]->y2++;
		}
   }
   pW->kvadrat->draw();
   if(GameMode==TWOPLAYERS) pW->treug->draw();
  
  
 if(ppp>600) ppp=-25;
	 if (jumping1)
		{t1+=dt;	 
		
		 speedH1=COS(t1*PIOVER180)*12;

		 ppp+=3;

		 for(int i=0;i<KOL;i++)
		 { pW->pol[i]->y1+=speedH1;

		 }

		 pW->kvadrat->Y2-=speedH1-speedH2;
		 sh=true;
	
		 lavaY1+=speedH1;
		 if(t1>90) {t1=0;  jumping1=false; }
		}
	else
	  {
		  if(dobroY1)
		  {if(t1<90) t1+=dt;
		   speedH1=SIN(t1*PIOVER180)*(12-7*UnderLava1);
		   for(int i=0;i<KOL;i++)
		   { pW->pol[i]->y1-=speedH1;

		   }
			pW->kvadrat->Y2+=speedH1-speedH2;
			
		  }
		  else
		  {t1=0;
		   jumping1=false;
		   pW->kvadrat->Y2=pW->pol[fixi1]->y2;
		   if(fixi1==EEE) 
		   {ShowCursor(true);
			 if(GameMode==2)
				pW->MessageBox("Êâàäðàò âûéãðàë","Êâàäðàò âûéãðàë",MB_OK);
			  else 
				pW->MessageBox("ÂÛ ÂÛÉÃÐÀËÈ !!!","ÂÛ ÂÛÉÃÐÀËÈ !!!",MB_OK);
			  pW->SendMessage(WM_CLOSE);
			 } 
		    speedH1=0;
		  }	
		  
		  lavaY1-=speedH1;
		}

    if(pW->kvadrat->Y1>lavaNearY1) 
		UnderLava1=true;
	else		
		UnderLava1=false;
 

	 static bool bulk=false;
    if(UnderLava1)
	{
		
	pW->kvadrat->healt-=0.3;
	 pW->kvadrat->W=10+(pW->kvadrat->healt/4);
	 pW->kvadrat->H=10+(pW->kvadrat->healt/3.333);

//	 wsprintf(str,"%d %%",(int)pW->kvadrat->healt);
	 if(!bulk)
	 { soundChannel[0] = FSOUND_PlaySound(FSOUND_FREE,pSound);
	  bulk=true;
	 }
	 if(pW->kvadrat->healt<=0) 
		{ShowCursor(true);
		  if(GameMode==2)
			pW->MessageBox("Òðåóãîëüíèê âûéãðàë","Òðåóãîëüíèê âûéãðàë",MB_OK);
		  else
		  { wsprintf(str,"ÂÛ ÄÎÑÒÈÃËÈ ÂÛÑÎÒÛ  %d ì ",(pW->pol[EEE]->y1+12000)/100);
			pW->MessageBox(str,"Game Over",MB_OK);
		  }
		  pW->SendMessage(WM_CLOSE);
		 }

	}
	else  {bulk=false; }

	if(pW->kvadrat->healt<100)
	
	pW->kvadrat->healt+=0.005;

	wsprintf(str,"%d %%",(int)pW->kvadrat->healt);



	if(GameMode==TWOPLAYERS)
	{if (jumping2)
		{t2+=dt2;
		 speedH2=COS(t2*PIOVER180)*12;
		 for(int i=0;i<KOL;i++)
			 pW->pol[i]->y2+=speedH2;
		 pW->treug->Y2-=speedH2-speedH1;
	
		 lavaY2+=speedH2;
		 if(t2>90) {t2=0;  jumping2=false;}
		}
	  else
		{ 
		  if(dobroY2)
		  {if(t2<90) t2+=dt2;
		  speedH2=SIN(t2*PIOVER180)*(12-8*UnderLava2);
		   for(int i=0;i<KOL;i++)
			   pW->pol[i]->y2-=speedH2;
			 pW->treug->Y2+=speedH2-speedH1;
		  }
		  else
		  {t2=0;
		   jumping2=false;
	   
		   if(fixi2==EEE) 
		   { ShowCursor(true);
			 pW->MessageBox("Òðåóãîëüíèê âûéãðàë","Òðåóãîëüíèê âûéãðàë",MB_OK);
			  pW->SendMessage(WM_CLOSE);
			 } 

		   pW->treug->Y2=pW->pol[fixi2]->y1;
		   speedH2=0;
		  }	 
		  lavaY2-=speedH2;
		}
	   
		if(pW->treug->Y1>(600+lavaY2)) 
			UnderLava2=true;
		else		
			UnderLava2=false;
	static bool bulk2;
	  if(UnderLava2) 
		{pW->treug->healt-=0.3;
		 pW->treug->W=8+pW->treug->healt/4.54;
		 pW->treug->H=10+pW->treug->healt/2.85;
		 if(!bulk2)
		 {soundChannel[0] = FSOUND_PlaySound(FSOUND_FREE,pSound);
		  bulk2=true;
		 }
		 wsprintf(str2,"%d %%",(int)pW->treug->healt);
		 if(pW->treug->healt<=0) 
		 {ShowCursor(true);
		  pW->MessageBox("Êâàäðàò âûéãðàë","Êâàäðàò âûéãðàë",MB_OK);
		  pW->SendMessage(WM_CLOSE);
		 }
		pW->pw2->memDC.SetTextColor(RGB(200*(pW->treug->healt<50),0,0));
		}
	  else 	bulk2=false;
		
	  
	}





	for(dobroY1=true,i=0;i<KOL;i++)
	{	
		if(fabs((pW->kvadrat->Y1)-(pW->pol[i]->y1))<=speedH1 &&
				(pW->kvadrat->X1+pW->kvadrat->W)>(pW->pol[i]->x1) &&
				 pW->kvadrat->X1<(pW->pol[i]->x1+pW->pol[i]->wigth) &&
				!jumping1
		  ) 
		  {dobroY1=false;
		   fixi1=i;
		   break;
		  }
	}

	static bool f;
	if(!dobroY1 && f) 
	{f=false; soundChannel[2] = FSOUND_PlaySound(FSOUND_FREE,pSound3);
	}

	if(jumping1) f=true;


 if(GameMode==TWOPLAYERS)
	for(dobroY2=true,i=0;i<KOL;i++)
	{	
		if(fabs((pW->treug->Y1)-(pW->pol[i]->y2))<=speedH2 &&
				(pW->treug->X1+pW->treug->W)>(pW->pol[i]->x2) &&
				 pW->treug->X1<(pW->pol[i]->x2+pW->pol[i]->wigth) &&
				!jumping2
		  ) 
		  {dobroY2=false;
		   fixi2=i;	
		   break;
		  }
		
	}


	if(counter<160*GameMode)counter++; 
	else
	{lavaY1-=0.7+prirost*(GameMode==1);
	 lavaY2-=0.7; 
	
	 if(GameMode==2)
	 {
	  pW->pw1->memDC.TextOut(800/4-20,600+lavaY1+35,"ÊèÑëÎòÀ");
	  pW->pw2->memDC.TextOut(800/4-20,600+lavaY2+35,"ÊèÑëÎòÀ");
	 }
	}  

	static char str3[30];

	pW->pw1->memDC.TextOut(0,0,str3);

	pW->pw1->Invalidate(0);
     if(GameMode==TWOPLAYERS)
	{  	pW->pw2->Invalidate(0);
	}


   Sleep(10);
  }
 
 
return 0;
}
