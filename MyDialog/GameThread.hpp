

jmp_buf  HELP_JMP;

void Wait3(int timewait)
{

	for (int i =0 ; i<timewait ; i++)
	{
		
		if (theApp.is_endHelp == true)
		{ 
			longjmp(HELP_JMP ,0);
		}
		Sleep(1);
	}
}


bool  IsGameOver2(Mydm* dm)
{
	//467,553,569,582
	if (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʤ��.BMP")!=-1)
	{
		dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 1000);
		while (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʤ��.BMP")!=-1)
		{
			dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 1000);
		}
		OutputDebugStringA("��Ϸ���  Thread"); 
		return true ;
	}else if (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʧ��.BMP")!=-1)
	{
		dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 1000);
		while (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʧ��.BMP")!=-1)
		{
			dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 1000);
		}
		OutputDebugStringA("��Ϸ���  THREAD"); 
		return true ;
	}

	return false;
}


bool Check_HP2(Mydm* dm)
{ 
 
	//310,619,728,752   HP���ķ�Χ

	if (dm->FindPic2(310,619,728,752,".\\res\\sub\\hp.bmp") == -1)
	{
		OutputDebugStringA("fun Thread Check_HP"); 
		return false;
	}

	return   true  ;
}

static  void  HelpThrad(int lp)
{
	theApp.is_endHelp =false;
	theApp.dm_Help.Init();
	
	theApp.dm_Help.BindWindows2();
	setjmp(HELP_JMP);
	if (theApp.is_endHelp == true)
	{
		OutputDebugStringA(" T1");
		theApp.is_endHelp =false;
		theApp.dm_Help.Uninit();
		return ;
	}
	while (1)
	{
		OutputDebugStringA("11111");
		if (IsGameOver2(&theApp.dm_Help))
		{
			OutputDebugStringA("thread  GameOver");
			theApp.IsEndGame_SUB =true;
			break;
		}
				OutputDebugStringA("22222");
		if (	::IsWindow((HWND)theApp.dm_Help.m_hwnd) ==false)
		{
			if (theApp.Code != -1)
			{
				OutputDebugStringA("game windows  end");
					system("taskkill /f /im LolClient.exe   & taskkill /f /im LolClient.exe   & taskkill /f /im BsSndRpt.exe & lol.launcher_tencent.exe & exit");
				theApp.IsEndGame_SUB =true;
				theApp.IsEndGame=true;
			}
			
			break;
		}


		if (::FindWindowA("#32770","Error Report") != 0)
		{
			 
				OutputDebugStringA("game windows  end");
				system("taskkill /f /im LolClient.exe   & taskkill /f /im LolClient.exe   & taskkill /f /im BsSndRpt.exe & lol.launcher_tencent.exe & exit");
				theApp.IsEndGame_SUB =true;
				theApp.IsEndGame=true;
		 
			break;
		}
				OutputDebugStringA("333333");

			/*	if (theApp.Code !=1)
				{
					if (Check_HP2(&theApp.dm_Help) == false)
					{

						OutputDebugStringA("HelpCheckThread NoHP");
						theApp.Code =1 ;
						for (int x=0; x<20 ;x++ )
						{
							if (IsGameOver2(&theApp.dm_Help))
							{
								OutputDebugStringA("thread  GameOver");
								theApp.IsEndGame_SUB =true;
								theApp.is_endHelp =true;
								Wait3(1);
							}
					 
							if (	::IsWindow((HWND)theApp.dm_Help.m_hwnd) ==false)
							{
								if (theApp.Code != -1)
								{
									OutputDebugStringA("game windows  end");
									system("taskkill /f /im LolClient.exe   & taskkill /f /im LolClient.exe");
									theApp.IsEndGame_SUB =true;
									theApp.IsEndGame=true;
									theApp.IsEndGame_SUB =true;
									theApp.is_endHelp =true;
									Wait3(1);
								} 
							}
								Wait3(1000);
						}
					
					}
				}*/
	while(theApp.dm_Help.FindPic2(730,29,1013,348,".\\RES\\SUB\\XX.BMP")!=-1)
	{
		OutputDebugStringA("XX");
		theApp.dm_Help.MOVE_CLICK(theApp.dm_Help.X1.lVal, theApp.dm_Help.Y1.lVal,100);
	}
		OutputDebugStringA(  "one");
		Wait3(500);

	}
		OutputDebugStringA(" T1  END");
		theApp.dm_Help.Uninit();
		return ;
}

void  CMyDialogApp::CreateHelpThread()
{
	theApp.Thread_GameThread_Sub_Help= AfxBeginThread(AFX_THREADPROC(HelpThrad),this);

}

void CMyDialogApp::Wait(int Mseconds)
{
	//long sTime = clock();
	boost::shared_ptr <long> sTime(new long);
	*sTime =clock();
	while(clock() - *sTime < Mseconds){

		if (IsEndGame==TRUE)
		{
			isBind_RomWindow =false;
			OutputDebugStringA("to jmp 1");
			longjmp(theApp.JMP1,0);
		}
		Sleep(1);

	}
}

void CMyDialogApp::Wait2(int Mseconds)
{
 if (Code == 1)
 {
	  Code =0;
	 Paolu(&dm_game);
	
 }else  if(Code == 2)
 {
	 	 Code =0;
	 	longjmp(theApp.JMP2,0);

 }
	boost::shared_ptr <long> sTime(new long);
	*sTime =clock();
	while(clock() -*sTime < Mseconds){

		if (IsEndGame==true ||   IsEndGame_SUB  ==true)
		{
			OutputDebugStringA("to jmp");
			longjmp(theApp.JMP2,0);
		}
		Sleep(1);

	}
}

static int  BeginGames_sub(LPVOID adr)
{
 theApp.MessageBoxTimeoutA(0,"����10���ڲ�Ҫ��������,�����������һЩδ֪�����⡣","��ʾ:",0,0,3000);

	theApp.IS_FIRST_GO =TRUE;
	theApp.dm_game.Init();
	theApp.dm_game.MyReg();
	theApp.dm_game.BindWindows2();
	setjmp(theApp.JMP2);
	if (theApp.IsEndGame_SUB  ==  true  ||  theApp.IsEndGame == true)
	{
		//theApp.IsEndGame = false ;
		theApp.dm_game.Uninit();
		return 0 ;
	}
	//////////////////////////////////////////////////////////////////////////

/*
	theApp.BaySome(&theApp.dm_game ,"��ܿ���");
	theApp.dm_game.Uninit();
	return 0;*/
	//////////////////////////////////////////////////////////////////////////
	if (theApp.Wait_GameFun(&theApp.dm_game))
	{	
 
	//	AfxMessageBox("end  wait");
		theApp.Check_ShiJiao(&theApp.dm_game);
		{
		
			theApp.DaGuai2(&theApp.dm_game);
		}
		
	}

	theApp.dm_game.Uninit();
	return 0;
}


static int  BeginGames(LPVOID adr)
{

	theApp.IsEndGame =false;
	theApp.IsEndGame_SUB = false;
	theApp.dm.Init();
	
	OutputDebugStringA(theApp.dm.Ver());
	setjmp(theApp.JMP1);  
	if (theApp.IsEndGame  ==  true)
	{
		theApp.IsEndGame = false ;
		theApp.dm.Uninit();
		return 0 ;
	}

	if (!theApp.dm.MyReg())
	{
		theApp.dm.Uninit();
		return 0 ;

	}
	theApp.dm.SetDic1();
	while (theApp.Isgame_Begin(&theApp.dm)  ==false)
	{
	
				OutputDebugStringA("��Ϸû����");
				if (theApp.FastDengLu(&theApp.dm_denglu))
				{
					OutputDebugStringA("��¼���");
					theApp.Wait(10000);
				}else
				{
					OutputDebugStringA("��Ϸ�޷���¼��  ԭ��δ֪ �뱨������,лл��");
					theApp.IsEndGame =true;
					theApp.Wait(500);
				}
				
	}
	

	while(1)
	{
		 if (		theApp. Isgame_Begin(&theApp.dm) ==false)
		 {
			 theApp.IsEndGame =true;
			 theApp.Wait(100);
			 return  false;
		 }

		OutputDebugStringA("game  is  bigin");
		while (theApp.IF_GameBegin(&theApp.dm) ==false)
		{
			theApp.IsEndGame =true; 
			theApp.Wait(1000);
			OutputDebugStringA("IF_GameBegin  ==  FALSE");

		}
		theApp.IsEndGame_SUB =false ;
		theApp.Code = 0;
		theApp.Thread_GameThread_Sub=AfxBeginThread(AFX_THREADPROC(BeginGames_sub),&theApp);
		theApp.IsEndGame_SUB =false ;
		theApp.Code = -1;
		theApp.Wait(1000); 
		::WaitForSingleObject(theApp.Thread_GameThread_Sub->m_hThread,INFINITE);
		OutputDebugStringA("end BeginGames_sub");
		theApp.Wait(10000);
	}
	theApp.dm.Uninit();
	OutputDebugStringA("	theApp.dm.Uninit();");
	return 0;
}

static bool  Onece =false;//��ֹ�ظ�����
static  void  WaitBeginGames(int lp)
{
	if (Onece == true)
	{
		AfxMessageBox("�����ظ����б�����");
		return ;
	}
	Onece = true ;
	try
	{
		while (1)
		{
			theApp.isBind_RomWindow =false ;
			OutputDebugStringA("����һ��");
			theApp.Thread_GameThread=AfxBeginThread(AFX_THREADPROC(BeginGames),&theApp);
			Sleep(1000); 
			::WaitForSingleObject(theApp.Thread_GameThread->m_hThread,INFINITE);
			system("taskkill /f /im LolClient.exe   & taskkill /f /im LolClient.exe   & taskkill /f /im BsSndRpt.exe & lol.launcher_tencent.exe & exit");
			OutputDebugStringA("CHECK  ONE");
		}
	}
	catch (...)
	{
		

	}
	 
}



bool  CMyDialogApp::Isgame_Begin(Mydm* dm)
{
	boost::shared_ptr <long> wnd(new long);
	*wnd =  dm->FindWindowEx(0,"","PVP.net");

/*
	long	m_hwnd =  dm->FindWindowEx(0,"RiotWindowClass","League");
	if (m_hwnd> 2)
	{
		OutputDebugStringA("��Ϸ��ǰ����");
		return true ;
	}*/


	if (*wnd != 0)
	{
		OutputDebugStringA("find Rom window");
 
		if (isBind_RomWindow ==false)
		{
				OutputDebugStringA("����Ϸ����");
			if ( dm->BindWindows1() == false)
			{
				OutputDebugStringA("No  bind");
				return false ;
			}
			isBind_RomWindow =true;
		}else
		{
			OutputDebugStringA("��Ϸ�����Ѿ��� �����ظ�");
		}
			
 

	 
	   
		dm->SetDic1();

		::GetWindowRect((HWND)*wnd , &dm->GameRect);
		return  true;
	}
	long	m_hwnd =  dm->FindWindowEx(0,"RiotWindowClass","League");
	if (m_hwnd> 2)
	{
		OutputDebugStringA("��Ϸ��ͼ��ǰ����");
		return true ;
	}

	return false ;
}
bool Is_ReSel =false;
bool  CMyDialogApp::IF_GameBegin(Mydm* dm)
{

	long	m_hwnd =  dm->FindWindowEx(0,"RiotWindowClass","League");
	if (m_hwnd> 2)
	{
		OutputDebugStringA("��Ϸ��ǰ����");
		return true ;
	}
	Is_ReSel = false;
	dm->Ret_MousePos();
	Wait(200);
	dm->UseDict(0);
	Wait(500);
	for (int x = 0 ; x< 30 ;x++)
	{
			theApp.CloseOtherWindow(dm);
		if (x==29)
		{
			OutputDebugStringA("time out 1");
			return  false;
		}
		

			if (dm->FindPic(509 -20,400 -20,608 +20,417 +20,".\\res\\sub\\��������.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
			{
				OutputDebugStringA("��������");
				dm->MoveTo(Tmx3.lVal , Tmy3.lVal);
				Wait(500);
				dm->LeftDoubleClick();
				Wait(500);

				while (dm->FindPic(509 -20,400 -20,608 +20,417 +20,".\\res\\sub\\��������.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
				{
					OutputDebugStringA("��������");
					dm->MoveTo(Tmx3.lVal , Tmy3.lVal);
					Wait(1000);
					dm->LeftDoubleClick();
					Wait(500);
			 
				}
				Wait(20000);
				return  true ;
			}
		if (dm->FindPic(29,22,220,124,".\\res\\ROM\\IM.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
		{
			OutputDebugStringA("IN  ROM 1");

			break ;
		}

							dm->FindDic_AndMoto(484,4,657,70,
											"PLAY","31.30.91-20.20.20",
											     0.9,
												[=](){
													OutputDebugStringA("PLAY");
																Wait(500);
																dm->LeftDoubleClick();
																Wait(200);
							},	
																	[=](){
																	OutputDebugStringA("CANT FIND  STR1");
																		}
					);
					dm->Ret_MousePos();
					if (dm->FindPic(164,580,409,699,".\\RES\\��ҳ.BMP","222222",0.9,0,&Tmx,&Tmy)!= -1)
					{
						if (dm->FindPic(552,26,596,42,".\\RES\\play_en.BMP","222222",0.9,0,&Tmx4,&Tmy4)!= -1)
						{
											OutputDebugStringA("��ҳ");
											OutputDebugStringA("find");
											//dm->MOVE_DBCLICK(Tmx.lVal,Tmy.lVal-490,200);//�˻���ս��λ��
	 
											Sub_Slect_LeiXin(dm,Tmx.lVal,Tmy.lVal,gm_struct.DuizhanMoshi+1);
											Sub_Slect_Moshi(dm,Tmx.lVal,Tmy.lVal,gm_struct.YouxiMoshi + 1);//�˻���ս����Ϸģʽ�ľ����սλ��
	 
										 Sub_Slect_Ditu(dm,Tmx.lVal,Tmy.lVal,1);//�˻���ս����Ϸģʽ���ٻ�ʦϿ�ȵ�λ��
 
										 Sub_Slect_Nandu(dm,Tmx.lVal,Tmy.lVal,gm_struct.nandu +1);
										 //ֻ����ٻ�ʦϿ��
										 dm->Ret_MousePos();
											if (	dm->FindPic_forEach(215,297,442,358,".\\res\\�ٻ�ʦϿ��.bmp","222222",0.9,&Tmx2,&Tmy2,4) == true)
											{
												OutputDebugStringA("�ٻ�Ͽ��"); 
												Sub_Slect_begin(dm,Tmx.lVal,Tmy.lVal);
						
							 
											}
						}
					
				
	
					}	
					 dm->Ret_MousePos();
					 if (dm->FindPic(0,0,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\��ʼ.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
					 {
						 if (dm->FindPic(0,0,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\��ʼ3.bmp","222222",0.9,0,&Tmx4,&Tmy4)!= -1)
						 {
							 OutputDebugStringA("��ʼ1");
							 dm->MOVE_DBCLICK(Tmx3.lVal, Tmy3.lVal,100);
							 Wait(888);
						 }

					 }

					 if (dm->FindPic(0,0,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\re3.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
					 {	 
						 if (dm->FindPic(Tmx3.lVal-20,Tmy3.lVal+20,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\re2.bmp","222222",0.9,0,&Tmx4,&Tmy4)!= -1)
						 {
							 if (dm->FindPic(Tmx3.lVal-20,Tmy3.lVal+20,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\re1.bmp","222222",0.9,0,&Tmx4,&Tmy4)!= -1)
							 {
								 OutputDebugStringA("��ʼ3  �Ѿ���ʼ��");
								 dm->MOVE_DBCLICK(Tmx4.lVal, Tmy4.lVal,100);
								 Wait(888);
							 }

						 }
					 }
				
					if (x>28)
					{
						OutputDebugStringA("cant find PLAY");
						return false ;
					}
					Wait(1000);
	}
	if (WaitBegin(dm))
	{
				CurYingXiong.Empty();


/*
	for (auto iter1 = mapYx.begin() ; iter1!=mapYx.end() ; iter1 ++)
		{*/
 for(int i =0; strlen(yingxiongStru[i].yingxiongName)>3 ; i++)
 {
 
			if (Is_ReSel ==true)
			{
				Is_ReSel =false;
				i=0;
				/*iter1 = mapYx.begin();*/

			}
		   /* CurYingXiong = iter1->first; */
			 CurYingXiong = yingxiongStru[i].yingxiongName;
			if (	Sel_Yingxiong(CurYingXiong.GetBuffer(0)/*"ţͷ"*/,dm))
			{
				GetZhuangBeiList(CurYingXiong.GetBuffer(0));
				OutputDebugStringA("Ӣ��ѡ��OK"); 
				long GameWnd=0;
				 
				for (int x = 0  ; x< 90 ; x++)
				{
					if (dm->FindPic(0,0,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\��ʼ.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
					{
						if (dm->FindPic(0,0,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\��ʼ3.bmp","222222",0.9,0,&Tmx4,&Tmy4)!= -1)
						{
							x=0;
							OutputDebugStringA("��Ϸ��;ֹͣ ���¿�ʼ");
							dm->MOVE_DBCLICK(Tmx3.lVal, Tmy3.lVal,100);
							Wait(888);
							Is_ReSel = true ;
							break; 
						}

					}
					GameWnd=dm->FindWindowEx(0,"RiotWindowClass","League of Legends (TM) Client");
					if (GameWnd>1)
					{
						Wait(20000);
						OutputDebugStringA("GAME  BEGIN");
						return true;
					}
					Wait(1500);
				}

			}
		} 
	}else
	{
		OutputDebugStringA("out 2");
		return false;
	}
		 
 
	return  false  ;
}



void CMyDialogApp::Sub_Slect_Moshi(Mydm* dm,int x , int y , int index )
{
	// +  251  515 
	if (index  ==  1)
	{
				dm->MOVE_DBCLICK(x+179,y-515,200);
	}else  if(index  == 2)
	{
		dm->MOVE_DBCLICK(x+179,y-515 + 30,200);
	}

}


void CMyDialogApp::Sub_Slect_LeiXin(Mydm* dm,int x , int y , int index )
{
	dm->MOVE_DBCLICK(Tmx.lVal,Tmy.lVal-490,200);//�˻���ս��λ��
	// +  251  515 
	if (index  ==  1)
	{
		dm->MOVE_DBCLICK(x,y-540,200);
	}else  if(index  == 2)
	{
	dm->MOVE_DBCLICK(x,y-490,200);
	}

}





void CMyDialogApp::Sub_Slect_Ditu(Mydm* dm,int x , int y , int index )
{
	// +  251  515 
	if (index  ==  1)
	{
		dm->MOVE_DBCLICK(x+365,y-515,200);
	}else  if(index  == 2)
	{
		dm->MOVE_DBCLICK(x+365,y-515 + 30,200);
	}

}




void CMyDialogApp::Sub_Slect_Nandu(Mydm* dm,int x , int y , int index )
{
	// +  251  515 
	if (index  ==  1)
	{
		dm->MOVE_DBCLICK(x+527,y-515,200);
	}else  if(index  == 2)
	{
		dm->MOVE_DBCLICK(x+527,y-515 + 30,200);
	}else  if(index  == 3)
	{
		dm->MOVE_DBCLICK(x+527,y-515 + 30 + 30,200);
	}

}




void CMyDialogApp::Sub_Slect_begin(Mydm* dm,int x , int y  )
{
	 
	OutputDebugStringA("Sub_Slect_begin");
		dm->MOVE_CLICK(x+450,y,200);
	 
}


bool CMyDialogApp::WaitBegin(Mydm* dm)
{
	 for (int x = 0  ;x < 30 ; x++)
	 {		
		 if (dm->FindPic(29,22,220,124,".\\res\\ROM\\IM.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
		 {
			 OutputDebugStringA("IN  ROM");

			  return true ;
		 }
		 if (dm->FindPic(0,0,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\��ʼ.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
		 {
			 if (dm->FindPic(0,0,dm->GameRect.right - dm->GameRect.left , dm->GameRect.bottom- dm->GameRect.top,".\\res\\��ʼ3.bmp","222222",0.9,0,&Tmx4,&Tmy4)!= -1)
			 {
				OutputDebugStringA("��ʼ2");
			 dm->MOVE_DBCLICK(Tmx3.lVal, Tmy3.lVal,100);
			 Wait(888);
			 }
		
		 }

		 Wait(888);
	 }


	 return  false;
}


bool CMyDialogApp::Sel_Yingxiong(char* Name,Mydm* dm)
{

	dm->Ret_MousePos();
	if (dm->FindPic(29,22,220,124,".\\res\\ROM\\IM.bmp","222222",0.9,0,&Tmx3,&Tmy3)!= -1)
	{
		OutputDebugStringA("ѡ��Ӣ��");

		dm->MOVE_DBCLICK(Tmx3.lVal+730 , Tmy3.lVal + 90,100);
		Wait(123);
		dm->Sendstring_(Name);
		Wait(1000);
		dm->MOVE_DBCLICK(Tmx3.lVal+210 , Tmy3.lVal + 160,100);
		if (dm->FindPic_forEach(0,0,dm->GameRect.right - dm->GameRect .left  , dm->GameRect.bottom - dm->GameRect.top,".\\RES\\ROM\\ȷ��.BMP","222222",0.9,&Tmx,&Tmy,2)!= false)
		{
			dm->MOVE_DBCLICK(Tmx.lVal , Tmy.lVal,1000);

			while (dm->FindPic_forEach(0,0,dm->GameRect.right - dm->GameRect .left  , dm->GameRect.bottom - dm->GameRect.top,".\\RES\\ROM\\ȷ��.BMP","222222",0.9,&Tmx,&Tmy,1)!= false)
			{
				dm->MOVE_CLICK(Tmx.lVal , Tmy.lVal,1000);
			}
			return true;
		} 
	}
/*

	 char  Picname[256]={0};
	 sprintf_s(Picname,256,".\\res\\Ӣ��\\%s.bmp",Name);

	 if (dm->FindPic_forEach(0,0,dm->GameRect.right - dm->GameRect .left  , dm->GameRect.bottom - dm->GameRect.top,Picname,"222222",0.9,&Tmx,&Tmy,20)!= -1)
	 {
		 dm->MOVE_DBCLICK(Tmx.lVal , Tmy.lVal,1000);

		 if (dm->FindPic_forEach(0,0,dm->GameRect.right - dm->GameRect .left  , dm->GameRect.bottom - dm->GameRect.top,".\\RES\\ROM\\ȷ��.BMP","222222",0.9,&Tmx,&Tmy,20)!= -1)
		 {
			 dm->MOVE_DBCLICK(Tmx.lVal , Tmy.lVal,1000);

			 while (dm->FindPic_forEach(0,0,dm->GameRect.right - dm->GameRect .left  , dm->GameRect.bottom - dm->GameRect.top,".\\RES\\ROM\\ȷ��.BMP","222222",0.9,&Tmx,&Tmy,20)!= -1)
			 {
				 dm->MOVE_DBCLICK(Tmx.lVal , Tmy.lVal,1000);
			 }
			  return true;
		 }
	
	 }
	*/
	 return  false ;
}



bool CMyDialogApp::Wait_GameFun(Mydm* dm)
{
/*
	while (theApp.dm_game.FindPic_forEach(0,0,1024,768,".\\RES\\SUB\\С��ʾ.BMP","222222",0.9,&Tmx,&Tmy,5))
	{
		AfxMessageBox("find");
		Wait2(1000);
	}*/
	std::shared_ptr<CString> STR(new CString); 
	std::shared_ptr<CString> STR_sub(new CString); 
 
	for (int x = 1 ; x <6 ;x++)
	{
		STR->Empty();
		STR->Format(".\\res\\sub\\״̬%d.BMP",x);
		while (dm->FindPic(0,0,1024,768,STR->GetBuffer(0) ,"222222",0.9,0,&Tmx,&Tmy) == -1)
		{
			Wait2(1000);
			OutputDebugStringA(STR->GetBuffer(0));

		}
		

	}
 
		return  true;
}


void CMyDialogApp::Check_ShiJiao(Mydm* dm)
{
	dm->Ret_MousePos();
	for (int i =0; i<10 ;i ++)
	{
		if (dm->FindPic(988,553,1009,573,".\\RES\\SUB\\�ӽ�.BMP","222222",0.9,0,&Tmx,&Tmy) == -1)
		{
			break;
		}else{

			OutputDebugStringA("check");
			dm->MoveTo(995,562);
			Wait2(200);
			dm->LeftClick();
			Wait2(200); 
			dm->Ret_MousePos();
			Wait2(1000);

		}
		if (i>8)
		{
			OutputDebugStringA("���°�");
			dm->UnBindWindow();
			dm->BindWindows2();
		}
	}
/*
	while (dm->FindPic(988,553,1009,573,".\\RES\\SUB\\�ӽ�.BMP","222222",0.9,0,&Tmx,&Tmy) != -1)
	{
		OutputDebugStringA("check");
		dm->MoveTo(995,562);
		Wait2(200);
		dm->LeftClick();
		Wait2(200); 
		dm->Ret_MousePos();
		Wait2(1000);

	} */

}


bool   CMyDialogApp::GetYingxiongList()
{
	int zero1=0;
	CString tmp1;
//	memset(yingxiongStru ,0 , 255*sizeof(Yingxiong));
	mapYx.clear();
	 for (int x = 1 ; x< m_dlg_yingxiong.m_Grid.GetRowCount() ; x++)
	 {
		tmp1  = m_dlg_yingxiong.m_Grid.GetItemText(x,1);

		 if (tmp1.GetLength() >= 2)
		 {
			 mapYx[m_dlg_yingxiong.m_Grid.GetItemText(x,1)] = m_dlg_yingxiong.m_Grid.GetItemText(x,2);
 
		//	strcpy_s(yingxiongStru[zero1].yingxiongName ,255 ,tmp1.GetBuffer(0));

		 }
	 // AfxMessageBox( YingXiongList[m_dlg_yingxiong.m_Grid.GetItemText(x,1)]);
	 }

 
	 for (auto it = mapYx.begin() ; it!=mapYx.end() ; it++)
	 {
		// AfxMessageBox(  it->second); 
  
	 } 
	 return  true  ;
}


bool   CMyDialogApp::GetYingxiongArray()
{
	int zero1=0;
	CString tmp1;
 memset(yingxiongStru ,0 , 255*sizeof(Yingxiong)); 
	for (int x = 1 ; x< m_dlg_yingxiong.m_Grid.GetRowCount() ; x++)
	{
		tmp1  = m_dlg_yingxiong.m_Grid.GetItemText(x,1);

		if (tmp1.GetLength() >= 2)
		{
			 
		   strcpy_s(yingxiongStru[zero1].yingxiongName ,255 ,tmp1.GetBuffer(0));
		   zero1++;
		}
		// AfxMessageBox( YingXiongList[m_dlg_yingxiong.m_Grid.GetItemText(x,1)]);
	}
		
	for (int i =0 ; i<255 ;i++)
	{
		if (strlen(yingxiongStru[i].yingxiongName) >3)
		{
			break; 
		}
		AfxMessageBox(yingxiongStru[i].LuxianName);
	}

	 
	return  true  ;
}


void  CMyDialogApp::Init_Ta()
{
	memset(HONG_Ta_shang,0,sizeof(YingxiongTa) * 20);
	memset(HONG_Ta_zhong,0,sizeof(YingxiongTa) * 20);
	memset(HONG_Ta_xia,0,sizeof(YingxiongTa) * 20);

	memset(LAN_Ta_shang,0,sizeof(YingxiongTa) * 20);
	memset(LAN_Ta_zhong,0,sizeof(YingxiongTa) * 20);
	memset(LAN_Ta_xia,0,sizeof(YingxiongTa) * 20);

	strcpy_s(LAN_Ta_xia[0].TaPicName ,255 ,".\\RES\\SUB\\����1.BMP");
	LAN_Ta_xia[0].TaXY.x = 920 ;
	LAN_Ta_xia[0].TaXY.y = 743 ;
	//643,421,685,460
	LAN_Ta_xia[0].PIC_RECT.left= 643 -20 ;
	LAN_Ta_xia[0].PIC_RECT.right= 685 +20 ;
	LAN_Ta_xia[0].PIC_RECT.top= 421 -20;
	LAN_Ta_xia[0].PIC_RECT.bottom= 460  +20;


	strcpy_s(LAN_Ta_xia[1].TaPicName ,255 ,".\\RES\\SUB\\����2.BMP");
	LAN_Ta_xia[1].TaXY.x = 962 ;
	LAN_Ta_xia[1].TaXY.y = 750 ;
	//821,362,861,402
	LAN_Ta_xia[1].PIC_RECT.left= 821 -20;
	LAN_Ta_xia[1].PIC_RECT.right= 861  +20;
	LAN_Ta_xia[1].PIC_RECT.top= 362  -20;
	LAN_Ta_xia[1].PIC_RECT.bottom= 407  +20;

 
	strcpy_s(LAN_Ta_xia[2].TaPicName ,255 ,".\\RES\\SUB\\������1.BMP");
	LAN_Ta_xia[2].TaXY.x = 1014 ;
	LAN_Ta_xia[2].TaXY.y = 688 ;
	//426,48,497,102
	LAN_Ta_xia[2].PIC_RECT.left= 426 -20 ;
	LAN_Ta_xia[2].PIC_RECT.right= 497  + 20;
	LAN_Ta_xia[2].PIC_RECT.top= 48  -20 ;
	LAN_Ta_xia[2].PIC_RECT.bottom= 102  +20 ;
}



bool  Need_Huicheng=false;
int  DianNao_ret;
int CMyDialogApp::DaGuai(Mydm*  dm)
{
	Need_Huicheng = false ;
	for (int z =0 ; z< 10 ;z++)
	{
		dm->WheelDown();
		Wait2(50);
	}
	int Tax,Tay;
	for (int x =0  ; x < 20  ; x++)
	{
		if (dm_game.FindPic2(280,260,347,314,".\\RES\\SUB\\��������.BMP")!=-1)
		{
			OutputDebugStringA("����");
			x = 0;
		}
		if (Need_Huicheng == true)
		{
			Need_Huicheng =false ;
			if (Check_HP(dm) == false)
			{
				Tax = LAN_Ta_xia[0].TaXY.x;
				Tay = LAN_Ta_xia[0].TaXY.y;
				dm->MOVE_RDBCLICK(Tax,Tay,500);
				dm->MOVE_RDBCLICK(Tax,Tay,500);
				Wait2(10000);
				dm->KeyPress('B');
				Wait2(15000);
				x=0; 
				continue;

				
			}
			x=0; 
			continue;
		}
		OutputDebugStringA("ONE  FOR");
		if (strlen(LAN_Ta_xia[x].TaPicName) <2)
		{
			if (x>1)
			{
				OutputDebugStringA("x = 0");
				x=x-2;
			}else
			{
				OutputDebugStringA("RET  -1");
					return   -1;
			}
		//����-1   ��ʾûͼ
		}
		Tax = LAN_Ta_xia[x].TaXY.x;
		Tay = LAN_Ta_xia[x].TaXY.y;
		dm->MOVE_RDBCLICK(Tax,Tay,500);

		for (int i =0 ; i <400 ; i++)
		{
			if (Need_Huicheng == true)
			{
				break;
			}
			add_jineng(dm);
			dm->MOVE_RDBCLICK(Tax,Tay,500);
			if (i > 390)
			{
				AfxMessageBox("ȥ����ʱ��!");
			}
			//�жϵ���ָ��������
				OutputDebugStringA(LAN_Ta_xia[x].TaPicName);
			if (	dm->FindPic2(LAN_Ta_xia[x].PIC_RECT.left,
				LAN_Ta_xia[x].PIC_RECT.top,
				LAN_Ta_xia[x].PIC_RECT.right,
				LAN_Ta_xia[x].PIC_RECT.bottom,
				LAN_Ta_xia[x].TaPicName) != -1)
			{ 
				OutputDebugStringA("FIND  TA");
				break;
			}else{
				OutputDebugStringA("NO PIC");
			}
			//ȥ���Ĺ���˳���жϹ���
			while(1)
			{
				 OutputDebugStringA("WIHILE 1 :3");
					DaXiaoGuai(&dm_game) ;

					DianNao_ret = Check_DianNao(dm);

					while (DianNao_ret == 1)
					{
						DianNao_ret = Check_DianNao(dm);
						OutputDebugStringA("һֱ�����");
						if (Check_HP(dm) ==false)
						{
							OutputDebugStringA("��Ѫ1");
							DianNao_ret = -1 ; //���� -1   �ô���س�
							break;
						}

					}
					if (DianNao_ret == -1) //Ӣ�۶� ��Ҫ����
					{
						OutputDebugStringA("Need_Huicheng1");
						Need_Huicheng = true;
						break; 
					}
		 
			
			
				if (DaXiaoGuai(&dm_game)  == false)//ûС��
				{
					break; 
				}
				Wait2(100);
				OutputDebugStringA("ONE");
			}
			Wait2(100);
			if(theApp.dm_game.IsDisplayDead(LAN_Ta_xia[x].PIC_RECT.left,
				LAN_Ta_xia[x].PIC_RECT.top,
				LAN_Ta_xia[x].PIC_RECT.right,
				LAN_Ta_xia[x].PIC_RECT.bottom,
				5) ==1)
			{
				OutputDebugStringA("ͼ��һֱû�仯 ˵��������");
				break;
			}
		}

	 

		while(1)
		{
			OutputDebugStringA("WIHILE 1 :2");
			add_jineng(dm);

			{
				DaXiaoGuai(&dm_game) ;
				DianNao_ret = Check_DianNao(dm);

				while (DianNao_ret == 1)
				{
					if (Need_Huicheng == true)
					{
						break;
					}

					DianNao_ret = Check_DianNao(dm);
					OutputDebugStringA("һֱ�����");
					if (Check_HP(dm) ==false)
					{
						OutputDebugStringA("��Ѫ 2");
						DianNao_ret = -1 ; //���� -1   �ô���س�
						break;
					}

				}
				if (DianNao_ret == -1) //Ӣ�۶� ��Ҫ����
				{
					OutputDebugStringA("Need_Huicheng 2");
					Need_Huicheng = true;
					break; 
				}
			}

			if (DaXiaoGuai(&dm_game)  == false)//ûС��
			{
				break; 
			}
			Wait2(100);
			OutputDebugStringA("ONE");
		} 
	}
}


 
int CMyDialogApp::DaGuai2(Mydm* dm)
{ 
/*
			if (IS_FIRST_GO ==true)
			{
				AfxMessageBox("�״�  30��");
				IS_FIRST_GO =false; 
				Wait2(30000); 
			}*/
	is_endHelp =false;
	OutputDebugStringA("B  THREAD");
	CreateHelpThread();
	if (mapYx[CurYingXiong]=="��·")
	{
		OutputDebugStringA("��·");
		xialu.InitXialu();
	}else if (mapYx[CurYingXiong]=="��·")
	{
		OutputDebugStringA("��·");
		xialu.InitZhongLu();
	}else{
		OutputDebugStringA("ǿ����·");
		xialu.InitShangLu();
	}
		 xialu.Check_ShiJiao(dm,true);
	add_jineng(dm);
	Bay();
	int CUR =0;
	while (1)
	{
		 
			Wait2(1);
		for (int z =0 ; z< 10 ;z++)
		{
			dm->WheelDown();
			Wait2(50);
		}

		OutputDebugStringA("WIHILE 1 :1");
		if (CUR>2)
		{
			CUR =0 ;
		} 
		xialu.SetCurTA(CUR);
		while (xialu.GotoTA_SUB(dm)  == false)
		{
			 
				Wait2(1);
 
				OutputDebugStringA("WIHILE 1 :2");

			while (Check_DianNao(dm)  ==1)
			{
				 
					Wait2(1);
					OutputDebugStringA("WIHILE 1 :4");
				OutputDebugStringA("��  SUB");
			} 
			while (DaXiaoGuai(dm))
			{ 
				 
					Wait2(1);
					OutputDebugStringA("WIHILE 1 :3");
				OutputDebugStringA("��С��"); 
			}	
		
	 
		}
		//////////////////////////////////////////////////////////////////////////
		while (1)
		{ 
		 
				Wait2(1);
		 add_jineng(dm);
			while (DaXiaoGuai(dm))
			{
 
					Wait2(1);
 
					OutputDebugStringA("WIHILE 1 :5");
				OutputDebugStringA("��С�� 2");
			}	

			while (Check_DianNao(dm) ==1)
			{
		 
					Wait2(1);
					OutputDebugStringA("WIHILE 1 :6"); 
			} 
			if ( DaXiaoGuai(dm) ==false)
			{
	 
				while (xialu.GotoTA_SUB_gongji(dm)  == false)
				{ 
						Wait2(1);
						OutputDebugStringA("WIHILE 1 :7");
					while (Check_DianNao(dm)  ==1)
					{
						Wait2(1);
							OutputDebugStringA("WIHILE 1 :8"); 
					} 
					while (DaXiaoGuai(dm))
					{
			 
				 	Wait2(1); 
						OutputDebugStringA("��С��");
					}	
			 
				}
				if (xialu.IsTA_GONGJI_OVER(dm))
				{
					CUR++;
				
				}
				break; 
			}
		}

	}
		//////////////////////////////////////////////////////////////////////////
/*

		xialu.SetCurTA(1);
		while (xialu.GotoTA_SUB(dm)  == false)
		{
			DaXiaoGuai(dm);
		}
		while (1)
		{
			if ( DaXiaoGuai(dm) ==false)
			{
				while (xialu.GotoTA_SUB_gongji(dm)  == false)
				{
					DaXiaoGuai(dm);
				}
				if (xialu.IsTA_GONGJI_OVER(dm))
				{
				    OutputDebugStringA("111111");
				}
			}
		}
	}*/
}


void CMyDialogApp::MoveToMyXiaoGuai(Mydm* dm)
{
	//С������������� �����߷�·
	if (dm->FindPic2(1,0,1022,253,".\\res\\sub\\�ҷ���Ѫ.BMP")!=-1)
	{
		OutputDebugStringA("�����ҷ�С�� �ƶ���ȥ");
		dm->MOVE_RDBCLICK(dm->X1.lVal , dm->Y1.lVal - 10 , 500);
	}
}
bool CMyDialogApp::IsDear(Mydm* dm)
{
	
		// 71,469,129,510 ����1
	if (dm_game.FindPic2(590-20,403-20,677+20,477+20,".\\RES\\SUB\\����1.BMP")!=-1)
	{
		xialu.SetCurTA(0);
		//xialu.Check_ShiJiao(dm,true);
		OutputDebugStringA("�ڰ�ȫ��");
		 return true;
	}
	return false ;
}
	int Tax,Tay;
void CMyDialogApp::Paolu(Mydm* dm)
{
	OutputDebugStringA("��·");
	xialu.SetCurTA(0);


	Tax = xialu.PaoluXY.x;
	Tay = xialu.PaoluXY.y;
	dm->MOVE_RDBCLICK(Tax,Tay,500);
	dm->MOVE_RDBCLICK(Tax,Tay,500);
			//xialu.Check_ShiJiao(dm,true);
	//�����Ͳ����س���
	if (IsDear(dm) == true)
	{
			OutputDebugStringA("����");
		 Bay(); 
		return ;
	}



 

	for (int x =0 ; x<8;x++)
	{
		Wait2(1000);
		if (IsDear(dm) == true)
		{
			OutputDebugStringA("����");
			Bay();
			return ;
		}


		if(Check_HP(dm) ==true)
		{
					//С������������� �����߷�·
			if (dm->FindPic2(1,0,1022,253,".\\res\\sub\\�ҷ���Ѫ.BMP")!=-1)
			{
				OutputDebugStringA("�����ҷ�С�� �ƶ���ȥ ��");
				dm->MOVE_RDBCLICK(dm->X1.lVal , dm->Y1.lVal - 10 , 500);

			}
			Wait2(2000);
			return  ;
		}
	}
	if (IsDear(dm) == true)
	{
		OutputDebugStringA("����");
		Bay(); 
		return ;
	}
	dm->KeyPress('B');
	for (int x=0; x<10;x++)
	{
		if (IsDear(dm) == true)
		{
			OutputDebugStringA("����");
			Bay(); 
			return ;
		}
		Sleep(1500);
	} 
	Bay();
}

int Jineng=0;
bool  CMyDialogApp::DaXiaoGuai(Mydm* dm)
{

	OutputDebugStringA("fun daxiaoguai");
		add_jineng(dm);
	if (dm->FindPic(0,0,1024,768,".\\RES\\SUB\\����Ѫ.BMP","222222",0.9,3,&Tmx,&Tmy)!=-1)
	{
	// //xialu.Check_ShiJiao(dm,false);
		while (1)
		{
		 
				Wait2(1);
				if (dm->FindPic(0,0,1024,768,".\\RES\\SUB\\����Ѫ.BMP","222222",0.9,3,&Tmx,&Tmy)!=-1)
				{
					dm->MoveTo(Tmx.lVal +15 ,  Tmy.lVal + 35);
					Wait2(20);
					dm->LeftClick();
					Wait2(20);
						//41,6,195,28
					if (dm->FindPic(41,6,195,28,".\\RES\\SUB\\HP2.BMP","222222",0.9,0,&Tmx2,&Tmy2) ==-1)
					{
						OutputDebugStringA("NO GUAI_WU HP");
						return true ;
					}
	 
				if (dm->FindPic2(54 ,0,1024 ,Tmy.lVal +200,".\\RES\\SUB\\�ҷ���Ѫ.BMP","222222") == -1)
				{
							Wait2(1);
					//	 //xialu.Check_ShiJiao(dm,true);
					OutputDebugStringA("�е��� ����2");
					xialu.SetCurTA(0);
					 Paolu(dm);
					return  -1;
				}

				if (Jineng >3)
				{
					Jineng  =0;
				}

				OutputDebugStringA("IN");
				dm->KeyDown(VK_SHIFT);
				Wait2(40);
				dm->MoveTo(Tmx.lVal +15 ,  Tmy.lVal + 35);
				theApp.Wait2(20);
				dm->KeyUp(VK_SHIFT);
				Wait2(40);
				dm->KeyPress('Q');
				dm->KeyPress('W');
				dm->KeyPress('E');
				dm->KeyPress('R');
				theApp.Wait2(20);

				dm->RightClick(); 
				OutputDebugStringA("BEGIN DA");
				for (int x =0 ; x<200 ;x++)
				{
					if(Check_HP(dm) ==false)
					{
						Paolu(dm);
						return  FALSE ;
					}
					if (dm->FindPic(41,6,195,28,".\\RES\\SUB\\HP2.BMP","222222",0.9,0,&Tmx2,&Tmy2) ==-1)
					{
						OutputDebugStringA("NO GUAI_WU HP");
						return true ;
					} 	 
					theApp.Wait2(20);
					dm->KeyPress('Q');
					dm->KeyPress('W');
					dm->KeyPress('E');
					dm->KeyPress('R');
					theApp.Wait2(20);

				}
				OutputDebugStringA("END DA");
				 
			}else
			{
			//	//xialu.Check_ShiJiao(dm,true);
				OutputDebugStringA("NO  GW");
				return  true ; 
			}
			
			
		}
} 
	return false;
}

  bool CMyDialogApp::IsWeiXian(Mydm* dm)
  {
	  //ֻ���ǰ��
	  if (dm->FindPic2(0,0,2000,2000,".\\res\\sub\\�ҷ���Ѫ.BMP") ==-1)
	  {
		  if (Check_DianNao(dm) != 0)
		  {
			  	return  true;
		  }
				 
	  }
	  return  false ;
  }
int CMyDialogApp::Check_DianNao(Mydm* dm)
{ 
	OutputDebugStringA("������");
			Wait2(1);
	add_jineng(dm);
			Wait2(1);
	if (dm->FindPic(0,0,1024,768,".\\RES\\SUB\\����.BMP","222222",0.9,3,&Tmx,&Tmy)!=-1)
	{
		// //xialu.Check_ShiJiao(dm,false);
		while (1)
		{
	 
			if(Check_HP(dm) ==false)
			{
				Paolu(dm);
				return  FALSE ;
			}

			Wait2(1);
			if (dm->FindPic(0,0,1024,768,".\\RES\\SUB\\����.BMP","222222",0.9,3,&Tmx,&Tmy)!=-1)
			{
				dm->MoveTo(Tmx.lVal - 20 ,  Tmy.lVal + 80);
				Wait2(20);
				dm->LeftClick();
				Wait2(20);
				//41,6,195,28
				if (dm->FindPic(41,6,195,28,".\\RES\\SUB\\HP2.BMP","222222",0.9,0,&Tmx2,&Tmy2) ==-1)
				{
					OutputDebugStringA("����� ���ֵ���ûѪ");
					return true ;
				}

				if (dm->FindPic2(54 ,0,1024 ,Tmy.lVal +200,".\\RES\\SUB\\�ҷ���Ѫ.BMP","222222") == -1)
				{
					//	 //xialu.Check_ShiJiao(dm,true);
					OutputDebugStringA("������е��� ����");
					xialu.SetCurTA(0);
					Paolu(dm);
					return  -1;
				}

				if (Jineng >3)
				{
					Jineng  =0;
				}

				OutputDebugStringA("�����Է�����");
				dm->MoveTo(Tmx.lVal -20,  Tmy.lVal + 80); 
				theApp.Wait2(20);
				dm->KeyPress('Q');
				dm->KeyPress('W');
				dm->KeyPress('E');
				dm->KeyPress('R');
				theApp.Wait2(20);


				OutputDebugStringA("IN");
				dm->KeyDown(VK_SHIFT);
				Wait2(40);
				dm->RightClick(); 
				Wait2(40);
				dm->KeyUp(VK_SHIFT);
				Wait2(40);
				OutputDebugStringA("��ʼѭ�������");
				for (int x =0 ; x<200 ;x++)
				{
					if (dm->FindPic(41,6,195,28,".\\RES\\SUB\\HP2.BMP","222222",0.9,0,&Tmx2,&Tmy2) ==-1)
					{
						OutputDebugStringA("����Ѫû��");
						return true ;
					} 		 

					if(Check_HP(dm) ==false)
					{
						Paolu(dm);
						return  FALSE ;
					}
					Wait2(10);

				}
				OutputDebugStringA("ѭ������Խ���");

			}else
			{
				//	//xialu.Check_ShiJiao(dm,true);
				OutputDebugStringA("�Ҳ���������");
				return  true ; 
			}


		}
	} 
	return false;
}
 
int JinengSet=0;
void  CMyDialogApp::add_jineng(Mydm* dm)
{
			Wait2(1);
	if (dm->FindPic2(390,620,633,673,".\\res\\sub\\����.BMP") !=-1)
	{
		if (JinengSet >2)
		{
			JinengSet =0;
		}
		dm->KeyDown(VK_CONTROL);
		Wait2(50);
		if (JinengSet == 0)
		{
			dm->KeyPress('R');
			dm->KeyPress('E');
			dm->KeyPress('W');
			dm->KeyPress('Q');
		}else if (JinengSet == 1)
		{
			dm->KeyPress('Q');
			dm->KeyPress('W');
			dm->KeyPress('E');
			dm->KeyPress('R');
		}else if (JinengSet == 2)
		{
			dm->KeyPress('E');
			dm->KeyPress('Q');
			dm->KeyPress('R');
			dm->KeyPress('W');
		}
		
		Wait2(50);
		dm->KeyUp(VK_CONTROL);
		Wait2(50);
		JinengSet ++;
	}
	 
}


bool CMyDialogApp::Check_HP(Mydm* dm)
{
 
		Wait2(1);
	//310,619,728,752   HP���ķ�Χ

	if (dm->FindPic2(310,619,728,752,".\\res\\sub\\hp.bmp") == -1)
	{
			OutputDebugStringA("fun Check_HP");
		xialu.SetCurTA(0);
		return false;
	}

	return   true  ;
}


void CMyDialogApp::Bay()
{
 	Wait2(1);
	//return ;
	for (auto i= map_ZhuangBei.begin() ; i!=map_ZhuangBei.end() ; i ++)
	{
		if (i->second == false)
		{
					Tmps1.Empty();
					Tmps1 = i->first;
					if (BaySome(&dm_game , Tmps1.GetBuffer(0)))
					{
						OutputDebugStringA("�ɹ�����1��");
						i->second = true;
					}
			break;
		}
	}
	for (int i =0; i<5 ;i++)
	{
		if (theApp.dm_game.FindPic2(193,10,961,121,".\\res\\sub\\�̵�\\����.BMP" ) !=-1)
		{
	 
			dm_game.KeyPress(VK_ESCAPE);
			Wait2(1000);
		}
	}

	 
}

bool CMyDialogApp::BaySome(Mydm* dm , char* Name)
{
	 	Wait2(1);
	dm->KeyPress('P');
	Wait2(400);  
	for (int i = 0 ; i < 6 ;  i++)
	{
		if (i==5)
		{
			OutputDebugStringA("�Ҳ����̵�");
			return false;
		}
		if (dm->FindPic2(193,10,961,121,".\\res\\sub\\�̵�\\����.BMP" ) !=-1)
		{
			
			break;
		}
		dm->KeyPress('P');
		Wait2(400); 
	}
	dm->MoveTo(dm->X1.lVal,dm->Y1.lVal + 105);
	Wait2(100);
	dm->LeftDoubleClick();
	Wait2(100);

	dm->Sendstring_(Name);
	//	AfxMessageBox(Name);
	Wait2(100);
	dm->KeyPress(VK_RETURN);
	Wait2(200);
	dm->MoveTo(dm->X1.lVal -400,dm->Y1.lVal +   143);
	Wait2(100);
	dm->LeftClick();
	Wait2(300);
	//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////ʶ��
	//�����ҵ�λ��
	long x1;
	long y1;
	  x1 = dm->X1.lVal;
	  y1 = dm->Y1.lVal;
	//////////////////////////////////////////////////////////////////////////
		dm->CapturePng(x1+390,y1+380,x1+535,y1+460,".\\��������λ��.png");
	if (	dm->FindPic2(x1+390,y1+380,x1+535,y1+460 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9) != -1)
{
	dm->MoveTo(dm->X1.lVal , dm->Y1.lVal);
	Wait2(200);
	for (int i =0 ; i<5 ;i++)
	{
		dm->LeftDoubleClick();
		Wait2(20);
	}
	OutputDebugStringA("�ҵ���װ��");
	return true;
}

/*
Ҫ�����װ��λ��:
	���λ��X + 160*2  Y+165  ����λ��X+160+410,Y+217

��Ҫ�ϳɵ�װ��ɢ��λ��:
��ʼλ��:
	X+160,Y+217
		����X+160+410,Y+391*/
	int Need_X1= x1 + 340  ;
	int Need_X2= x1 + 540  ;
	int Need_Y1= y1 + 170 ;
	int Need_Y2= y1 + 235  ;

	dm->CapturePng(Need_X1,Need_Y1,Need_X2,Need_Y2,".\\Ҫ���λ��.png");

	int Hecheng_X1= x1 + 188 ;
	int Hecheng_X2= x1 + 535  ;
	int Hecheng_Y1= y1 + 240 ;
	int Hecheng_Y2= y1 + 380 ;
		dm->CapturePng(Hecheng_X1,Hecheng_Y1,Hecheng_X2,Hecheng_Y2,".\\Ҫ���ɢ��λ��.png");
	LONG  LRESUT =dm->FindPic2(Need_X1,Need_Y1,Need_X2,Need_Y2 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9); 
	if (LRESUT != -1 )
	{
		
	OutputDebugStringA("�ҵ���װ�� 2");
		dm->MoveTo(dm->X1.lVal , dm->Y1.lVal);
		Wait2(2000);
		dm->LeftDoubleClick();
		Wait2(200);
		LRESUT =dm->FindPic2(Need_X1,Need_Y1,Need_X2,Need_Y2 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9);
		for (int x =0; x<4;x++)
		{
			OutputDebugStringA("������ 2");
			dm->MoveTo(dm->X1.lVal , dm->Y1.lVal);
			Wait2(200);
			dm->LeftDoubleClick();
			Wait2(200);
			LRESUT =dm->FindPic2(Need_X1,Need_Y1,Need_X2,Need_Y2 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9);
			if (LRESUT == -1)
			{
				break;
			}
     	} 
		return  true ;
	}



	LONG LRESUT2 =dm->FindPic2(Hecheng_X1,Hecheng_Y1,Hecheng_X2,Hecheng_Y2 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9);
 
		for (int x =0; x<4;x++)
		{
			Wait2(1);
			dm->CapturePng(dm->X1.lVal + 5, dm->Y1.lVal -10,dm->X1.lVal + 50 ,dm->Y1.lVal + 10 ,".\\�Ƿ�����.png");

			if (		dm->FindPic(dm->X1.lVal + 5, dm->Y1.lVal -10,dm->X1.lVal + 50 ,dm->Y1.lVal + 10 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9,0,&Tmx,&Tmy) != -1)
			{
				OutputDebugStringA("��װ�������");
				break;
			}
			OutputDebugStringA("������ɢ��");
			dm->MoveTo(dm->X1.lVal , dm->Y1.lVal);
			Wait2(200);
			dm->LeftDoubleClick();
			Wait2(2000);
			LRESUT2 =dm->FindPic2(Hecheng_X1,Hecheng_Y1,Hecheng_X2,Hecheng_Y2 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9);
			if (LRESUT2 == -1)
			{
				return false;
			}
 
			

	}

 //////////////////////////////////////////////////////////////////////////

	LONG  LRESUT3 =dm->FindPic2(Need_X1,Need_Y1,Need_X2,Need_Y2 ,".\\RES\\SUB\\�̵�\\����2.BMP","222222",0.9); 
	if (LRESUT3 != -1 )
	{
		OutputDebugStringA("�ҵ���װ��1");
		dm->MoveTo(dm->X1.lVal , dm->Y1.lVal);
		Wait2(2000);
		dm->LeftDoubleClick();
		Wait2(200);
 	LRESUT3 =dm->FindPic2(Need_X1,Need_Y1,Need_X2,Need_Y2 ,".\\RES\\SUB\\�̵�\\����2.BMP","222222",0.9);
	

		if(LRESUT3 != -1)
		{
			
			OutputDebugStringA("��������װ��1");
			dm->MoveTo(dm->X1.lVal , dm->Y1.lVal);
			Wait2(200);
			dm->LeftDoubleClick();
			Wait2(200);
			LRESUT3 =dm->FindPic2(Need_X1,Need_Y1,Need_X2,Need_Y2 ,".\\RES\\SUB\\�̵�\\����2.BMP","222222",0.9);

		}
		//AfxMessageBox("����������װ��1");
		return  true ;
	}



	LONG LRESUT4 =dm->FindPic2(Hecheng_X1,Hecheng_Y1,Hecheng_X2,Hecheng_Y2 ,".\\RES\\SUB\\�̵�\\����2.BMP","222222",0.9);
	if(LRESUT4 != -1)
	{
			Wait2(1);
		dm->CapturePng(dm->X1.lVal + 5, dm->Y1.lVal -10,dm->X1.lVal + 50 ,dm->Y1.lVal + 10 ,".\\�Ƿ�����.png");

		if (		dm->FindPic(dm->X1.lVal + 5, dm->Y1.lVal -10,dm->X1.lVal + 50 ,dm->Y1.lVal + 10 ,".\\RES\\SUB\\�̵�\\����.BMP","222222",0.9,0,&Tmx,&Tmy) != -1)
		{
			OutputDebugStringA("��װ������� 2");
			 return false;
		}
		OutputDebugStringA("������ɢ�� 2");
		dm->MoveTo(dm->X1.lVal , dm->Y1.lVal);
		Wait2(200);
		dm->LeftDoubleClick();
		Wait2(2000);
		LRESUT4=dm->FindPic2(Hecheng_X1,Hecheng_Y1,Hecheng_X2,Hecheng_Y2 ,".\\RES\\SUB\\�̵�\\����2.BMP","222222",0.9);
		if (LRESUT4 == -1)
		{
			return false;
		}

	}
	return false ;
}



bool CMyDialogApp::GetZhuangBeiList(char* YingxiongName)
{
	MyGrid*  LuxianGrid;
	map_ZhuangBei.clear();
	LuxianGrid = & m_dlg_yingxiong.m_Grid_Luxian;
	  indexx=-1;
	indexx = m_dlg_yingxiong.m_luxian_box.FindString(0,YingxiongName);
	if (indexx != -1)
	{
		theApp.m_dlg_yingxiong.m_luxian_box.SetCurSel(indexx);
		theApp.m_dlg_yingxiong.OnCbnSelchangeCombo1();
		for (int i = 1; i<LuxianGrid->GetRowCount() ; i++)
		{
			Tmps1.Empty();
			Tmps1 =	LuxianGrid->GetItemText(i,1);
			if (Tmps1.IsEmpty() == false   && Tmps1.GetLength() > 2)
			{
				map_ZhuangBei.insert(make_pair(Tmps1,false));
				//map_ZhuangBei[Tmps1]=false;
			}
		}

		return  true;
	}

	return false;
}



bool CMyDialogApp::IsGameOver(Mydm* dm)
{
	//467,553,569,582
	if (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʤ��.BMP")!=-1)
	{
		dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 500);
		while (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʤ��.BMP")!=-1)
		{
			dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 500);
		}
		OutputDebugStringA("��Ϸ���");
		is_endHelp =true;
		IsEndGame_SUB =true;
		Wait2(1);
		return true ;
	}else if (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʧ��.BMP")!=-1)
	{
		dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 500);
		while (dm->FindPic2(447,533,589,600,".\\res\\sub\\��Ϸʧ��.BMP")!=-1)
		{
			dm->MOVE_DBCLICK(dm->X1.lVal , dm->Y1.lVal , 500);
		}
		OutputDebugStringA("��Ϸ���");
			is_endHelp =true;
		IsEndGame_SUB =true;
		Wait2(1);
		return true ;
	}

	return false;
}




void CMyDialogApp::WriteLog(char* str)
{

}


bool  CMyDialogApp::FastDengLu(Mydm* dm)
{
	 m_dlg_youximoshi.m_lujin.GetWindowTextA(GamePath,255);
	 WinExec(GamePath,SW_SHOW);
	 for (int i =0 ; i<20 ; i++)
	 {
		 if (i == 19)
		 {
			 return false ;
		 }
		 Sleep(1000);
		 if (::FindWindowA(NULL , "Ӣ�����˵�¼����") != 0)
		 {
			 OutputDebugStringA("OK");
			 break;
		 }
	 }
 
	 ::SetWindowPos(::FindWindowA(NULL , "Ӣ�����˵�¼����") ,HWND_NOTOPMOST,0,0,1280,768,SWP_NOMOVE);
	 dm_denglu.BindWindowEx((long)::FindWindowA(NULL , "Ӣ�����˵�¼����") ,"normal","normal","normal","",101);

 

 
		 dm_denglu.Ret_MousePos(); 

		 Sleep(1000);
	  
		 for (int i =0 ; i<60 ; i++)
		 {
			 if (i == 59)
			 {
				 return false;
			 }
			 dm_denglu.Ret_MousePos();
			 Sleep(500);
			 if (  dm_denglu.FindPic2(920,409,1133,610,".\\res\\fast\\����.BMP") !=-1)
			 {

				 dm_denglu.MoveTo(dm_denglu.X1.lVal,dm_denglu.Y1.lVal+ 50);
				 Sleep(500);
				 dm_denglu.LeftClick();
				 Sleep(1000);
				 dm_denglu.Ret_MousePos();
				 Sleep(500);
				 while (  dm_denglu.FindPic2(920,409,1133,610,".\\res\\fast\\����.BMP") !=-1)
				 {

					 dm_denglu.MoveTo(dm_denglu.X1.lVal,dm_denglu.Y1.lVal +50);
					 Sleep(50);
					 dm_denglu.LeftClick();
					 Sleep(1000);
					 dm_denglu.Ret_MousePos();
					 Sleep(500);
				 }
 
			 }


			 if (  dm_denglu.FindPic2(920,409,1133,610,".\\res\\fast\\ȷ����¼.BMP") !=-1)
			 {

				 dm_denglu.MoveTo(dm_denglu.X1.lVal,dm_denglu.Y1.lVal);
				 Sleep(500);
				 dm_denglu.LeftClick();
				 Sleep(1000);
				 dm_denglu.Ret_MousePos();
				 Sleep(500);
				 while (  dm_denglu.FindPic2(920,409,1133,610,".\\res\\fast\\ȷ����¼.BMP") !=-1)
				 {

					 dm_denglu.MoveTo(dm_denglu.X1.lVal,dm_denglu.Y1.lVal);
					 Sleep(50);
					 dm_denglu.LeftClick();
					 Sleep(1000);
					 dm_denglu.Ret_MousePos();
					 Sleep(500);
				 } 
			 }




			 if (  dm_denglu.FindPic2(1039,95,1112,151,".\\res\\fast\\QT.BMP") !=-1)
			 {

				 dm_denglu.MoveTo(dm_denglu.X1.lVal +10,dm_denglu.Y1.lVal +10);
				 Sleep(500);
				 dm_denglu.LeftClick();
				 Sleep(1000);
				 dm_denglu.Ret_MousePos();
				 Sleep(500);
				 while (  dm_denglu.FindPic2(1039,95,1112,151,".\\res\\fast\\QT.BMP") !=-1)
				 {

					 dm_denglu.MoveTo(dm_denglu.X1.lVal +10 ,dm_denglu.Y1.lVal +10);
					 Sleep(50);
					 dm_denglu.LeftClick();
					 Sleep(1000);
					 dm_denglu.Ret_MousePos();
					 Sleep(500);
				 }

			 }




			 if (  dm_denglu.FindPic2(797,657,857,717,".\\res\\fast\\GO.BMP") !=-1)
			 {

				 dm_denglu.MoveTo(dm_denglu.X1.lVal +120,dm_denglu.Y1.lVal);
				 Sleep(500);
				 dm_denglu.LeftClick();
				 Sleep(1000);
				 dm_denglu.Ret_MousePos();
				 Sleep(500);
				 while (  dm_denglu.FindPic2(797,657,857,717,".\\res\\fast\\GO.BMP") !=-1)
				 {

					 dm_denglu.MoveTo(dm_denglu.X1.lVal +120,dm_denglu.Y1.lVal);
					 Sleep(50);
					 dm_denglu.LeftClick();
					 Sleep(1000);
					 dm_denglu.Ret_MousePos();
					 Sleep(500);
				 } 
				 break;
			 }

			 Sleep(1000);
		 }

		 	 boost::shared_ptr <long> wnd(new long);
		 for (int i =0 ; i <50; i++)
		 {
		
			 *wnd =  dm->FindWindowEx(0,"","PVP.net");
			 if (*wnd != 0)
			 {
				 return  true;
			 }
			 Sleep(1000);
		 }
	 return   false;
}



#include "CEyLoginSoft.h"
bool  CMyDialogApp::Reg_YiYou()
{
	
	::CoInitialize(NULL);
	CEyLoginSoft  yy;
 
	 
	yy.CreateDispatch("Eylogin.Eyloginsoft");
	yy.SetAppKey("C5804C1CBB204BC090FEE1EDE34635E1");
//	AfxMessageBox(yy.Ver());

/*
	long UserLoginSingle(userCode,aVer,UserMac) 

��������:

	userCode �ַ���: �û�ע����

		aVer �ַ���: �汾�� ע��: �˰汾�ŷǲ���汾��,��Ҫ�ں�ͷ�����б� �汾���������Լ����.

		UserMac �ַ���: �û�Ψһ��ʾ,�󶨵��Կ��������ָ���û���ʾ�� (���û�п��������󶨿��Էſ�!)
*/

	if (	yy.UserLoginSingle("MD3EFAF8D86309664006E380490202FF","10",yy.GetCpuID())!=1)
	{
		int rrt= theApp.MessageBoxTimeoutA(0,yy.GetLastMessages().GetBuffer(0),"3�����ʧ",0,0,3000);
 
 
	}
	yy.AutoUpdate("10");
	return  true;
}


void  CMyDialogApp::CloseOtherWindow(Mydm* dm)
{
		 long  m_hwnd =  dm->FindWindowEx(0,"TXGuiFoundation","");
		 if (m_hwnd>2)
		 {
			 ::SendMessageA((HWND)m_hwnd ,WM_CLOSE ,0,0);
		 }
}