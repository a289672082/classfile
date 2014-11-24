#include "stdafx.h"
#include "Xialu.h"

void CXialu::InitXialu()
{

	CurIndex = 0;
	memset(TA , 0 ,sizeof(MyStructTa)*20);
	 

	PaoluXY.x = ::GetPrivateProfileIntA("X","SAFEX",0,".\\ÅäÖÃ.INI"); 
	PaoluXY.y = ::GetPrivateProfileIntA("X","SAFEY",0,".\\ÅäÖÃ.INI"); 

	PaoluXY.x = ::GetPrivateProfileIntA("X","SAFEX",0,".\\ÅäÖÃ.INI"); 
	PaoluXY.y = ::GetPrivateProfileIntA("X","SAFEY",0,".\\ÅäÖÃ.INI"); 

	TA[0].ArrayFangYu.x = ::GetPrivateProfileIntA("X","SX_0",0,".\\ÅäÖÃ.INI"); 
	TA[0].ArrayFangYu.y = ::GetPrivateProfileIntA("X","SY_0",0,".\\ÅäÖÃ.INI");  

	TA[0].ArrayGongJi.x = ::GetPrivateProfileIntA("X","GX_0",0,".\\ÅäÖÃ.INI"); 
	TA[0].ArrayGongJi.y = ::GetPrivateProfileIntA("X","GY_0",0,".\\ÅäÖÃ.INI");   

	TA[0].x1 = ::GetPrivateProfileIntA("X","P0_X1",0,".\\ÅäÖÃ.INI") -20;   
	TA[0].y1 = ::GetPrivateProfileIntA("X","P0_Y1",0,".\\ÅäÖÃ.INI") -20;   
	TA[0].x2 = ::GetPrivateProfileIntA("X","P0_X2",0,".\\ÅäÖÃ.INI")  +20;   
	TA[0].y2 = ::GetPrivateProfileIntA("X","P0_Y2",0,".\\ÅäÖÃ.INI")  +20;    
	strcpy_s(TA[0].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t1g.bmp" );

	// µÚ2²ã 

	TA[1].ArrayFangYu.x = ::GetPrivateProfileIntA("X","SX_1",0,".\\ÅäÖÃ.INI"); 
	TA[1].ArrayFangYu.y = ::GetPrivateProfileIntA("X","SY_1",0,".\\ÅäÖÃ.INI");  

	TA[1].ArrayGongJi.x = ::GetPrivateProfileIntA("X","GX_1",0,".\\ÅäÖÃ.INI"); 
	TA[1].ArrayGongJi.y = ::GetPrivateProfileIntA("X","GY_1",0,".\\ÅäÖÃ.INI");   

	TA[1].x1 = ::GetPrivateProfileIntA("X","P1_X1",0,".\\ÅäÖÃ.INI") -20;   
	TA[1].y1 = ::GetPrivateProfileIntA("X","P1_Y1",0,".\\ÅäÖÃ.INI") -20;   
	TA[1].x2 = ::GetPrivateProfileIntA("X","P1_X2",0,".\\ÅäÖÃ.INI")  +20;   
	TA[1].y2 = ::GetPrivateProfileIntA("X","P1_Y2",0,".\\ÅäÖÃ.INI")  +20;     
	strcpy_s(TA[1].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t2g.bmp" );


	//////////////////////////////////////µÚÈý²ã////////////////////////////////////


	TA[2].ArrayFangYu.x = ::GetPrivateProfileIntA("X","SX_2",0,".\\ÅäÖÃ.INI"); 
	TA[2].ArrayFangYu.y = ::GetPrivateProfileIntA("X","SY_2",0,".\\ÅäÖÃ.INI");  

	TA[2].ArrayGongJi.x = ::GetPrivateProfileIntA("X","GX_2",0,".\\ÅäÖÃ.INI"); 
	TA[2].ArrayGongJi.y = ::GetPrivateProfileIntA("X","GY_2",0,".\\ÅäÖÃ.INI");   

	TA[2].x1 = ::GetPrivateProfileIntA("X","P2_X1",0,".\\ÅäÖÃ.INI") -20;   
	TA[2].y1 = ::GetPrivateProfileIntA("X","P2_Y1",0,".\\ÅäÖÃ.INI") -20;   
	TA[2].x2 = ::GetPrivateProfileIntA("X","P2_X2",0,".\\ÅäÖÃ.INI")  +20;   
	TA[2].y2 = ::GetPrivateProfileIntA("X","P2_Y2",0,".\\ÅäÖÃ.INI")  +20;   

	strcpy_s(TA[1].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t3g.bmp" );

	 

}



void CXialu::InitZhongLu()
{

	CurIndex = 0;
	memset(TA , 0 ,sizeof(MyStructTa)*20);
	 
	

	 PaoluXY.x = ::GetPrivateProfileIntA("Z","SAFEX",0,".\\ÅäÖÃ.INI"); 
	 PaoluXY.y = ::GetPrivateProfileIntA("Z","SAFEY",0,".\\ÅäÖÃ.INI"); 

	 TA[0].ArrayFangYu.x = ::GetPrivateProfileIntA("Z","SX_0",0,".\\ÅäÖÃ.INI"); 
	 TA[0].ArrayFangYu.y = ::GetPrivateProfileIntA("Z","SY_0",0,".\\ÅäÖÃ.INI");  

	 TA[0].ArrayGongJi.x = ::GetPrivateProfileIntA("Z","GX_0",0,".\\ÅäÖÃ.INI"); 
	 TA[0].ArrayGongJi.y = ::GetPrivateProfileIntA("Z","GY_0",0,".\\ÅäÖÃ.INI");   

	 TA[0].x1 = ::GetPrivateProfileIntA("Z","P0_X1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[0].y1 = ::GetPrivateProfileIntA("Z","P0_Y1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[0].x2 = ::GetPrivateProfileIntA("Z","P0_X2",0,".\\ÅäÖÃ.INI")  +20;   
	 TA[0].y2 = ::GetPrivateProfileIntA("Z","P0_Y2",0,".\\ÅäÖÃ.INI")  +20;    
	 strcpy_s(TA[0].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t1g_Z.bmp" );

	 // µÚ2²ã 

	 TA[1].ArrayFangYu.x = ::GetPrivateProfileIntA("Z","SX_1",0,".\\ÅäÖÃ.INI"); 
	 TA[1].ArrayFangYu.y = ::GetPrivateProfileIntA("Z","SY_1",0,".\\ÅäÖÃ.INI");  

	 TA[1].ArrayGongJi.x = ::GetPrivateProfileIntA("Z","GX_1",0,".\\ÅäÖÃ.INI"); 
	 TA[1].ArrayGongJi.y = ::GetPrivateProfileIntA("Z","GY_1",0,".\\ÅäÖÃ.INI");   

	 TA[1].x1 = ::GetPrivateProfileIntA("Z","P1_X1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[1].y1 = ::GetPrivateProfileIntA("Z","P1_Y1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[1].x2 = ::GetPrivateProfileIntA("Z","P1_X2",0,".\\ÅäÖÃ.INI")  +20;   
	 TA[1].y2 = ::GetPrivateProfileIntA("Z","P1_Y2",0,".\\ÅäÖÃ.INI")  +20;     
	 strcpy_s(TA[1].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t2g_Z.bmp" );


	 //////////////////////////////////////µÚÈý²ã////////////////////////////////////


	 TA[2].ArrayFangYu.x = ::GetPrivateProfileIntA("Z","SX_2",0,".\\ÅäÖÃ.INI"); 
	 TA[2].ArrayFangYu.y = ::GetPrivateProfileIntA("Z","SY_2",0,".\\ÅäÖÃ.INI");  

	 TA[2].ArrayGongJi.x = ::GetPrivateProfileIntA("Z","GX_2",0,".\\ÅäÖÃ.INI"); 
	 TA[2].ArrayGongJi.y = ::GetPrivateProfileIntA("Z","GY_2",0,".\\ÅäÖÃ.INI");   

	 TA[2].x1 = ::GetPrivateProfileIntA("Z","P2_X1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[2].y1 = ::GetPrivateProfileIntA("Z","P2_Y1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[2].x2 = ::GetPrivateProfileIntA("Z","P2_X2",0,".\\ÅäÖÃ.INI")  +20;   
	 TA[2].y2 = ::GetPrivateProfileIntA("Z","P2_Y2",0,".\\ÅäÖÃ.INI")  +20;   

	 strcpy_s(TA[1].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t3g_Z.bmp" );
}



void CXialu::InitShangLu()
{

	CurIndex = 0;
	memset(TA , 0 ,sizeof(MyStructTa)*20);



/*
	 [S]
	 SAFEX=864
		 SAFEY=671
		 SX_0=862
		 SY_0=606
		 GX_0=876
		 GY_0=597
		 P0_X1=814
		 P0_Y1=137
		 P0_X2=837
		 P0_Y2=156*/
	PaoluXY.x = ::GetPrivateProfileIntA("S","SAFEX",0,".\\ÅäÖÃ.INI"); 
	PaoluXY.y = ::GetPrivateProfileIntA("S","SAFEY",0,".\\ÅäÖÃ.INI"); 

	TA[0].ArrayFangYu.x = ::GetPrivateProfileIntA("S","SX_0",0,".\\ÅäÖÃ.INI"); 
	TA[0].ArrayFangYu.y = ::GetPrivateProfileIntA("S","SY_0",0,".\\ÅäÖÃ.INI");  

	TA[0].ArrayGongJi.x = ::GetPrivateProfileIntA("S","GX_0",0,".\\ÅäÖÃ.INI"); 
	TA[0].ArrayGongJi.y = ::GetPrivateProfileIntA("S","GY_0",0,".\\ÅäÖÃ.INI");   

		TA[0].x1 = ::GetPrivateProfileIntA("S","P0_X1",0,".\\ÅäÖÃ.INI") -20;   
		TA[0].y1 = ::GetPrivateProfileIntA("S","P0_Y1",0,".\\ÅäÖÃ.INI") -20;   
		TA[0].x2 = ::GetPrivateProfileIntA("S","P0_X2",0,".\\ÅäÖÃ.INI")  +20;   
		TA[0].y2 = ::GetPrivateProfileIntA("S","P0_Y2",0,".\\ÅäÖÃ.INI")  +20;    
	 strcpy_s(TA[0].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t1g_s.bmp" );

	// µÚ2²ã 

	 TA[1].ArrayFangYu.x = ::GetPrivateProfileIntA("S","SX_1",0,".\\ÅäÖÃ.INI"); 
	 TA[1].ArrayFangYu.y = ::GetPrivateProfileIntA("S","SY_1",0,".\\ÅäÖÃ.INI");  
																									   
	 TA[1].ArrayGongJi.x = ::GetPrivateProfileIntA("S","GX_1",0,".\\ÅäÖÃ.INI"); 
	 TA[1].ArrayGongJi.y = ::GetPrivateProfileIntA("S","GY_1",0,".\\ÅäÖÃ.INI");   

	 TA[1].x1 = ::GetPrivateProfileIntA("S","P1_X1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[1].y1 = ::GetPrivateProfileIntA("S","P1_Y1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[1].x2 = ::GetPrivateProfileIntA("S","P1_X2",0,".\\ÅäÖÃ.INI")  +20;   
	 TA[1].y2 = ::GetPrivateProfileIntA("S","P1_Y2",0,".\\ÅäÖÃ.INI")  +20;     
	 strcpy_s(TA[1].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t2g_s.bmp" );


	 //////////////////////////////////////µÚÈý²ã////////////////////////////////////


	 TA[2].ArrayFangYu.x = ::GetPrivateProfileIntA("S","SX_2",0,".\\ÅäÖÃ.INI"); 
	 TA[2].ArrayFangYu.y = ::GetPrivateProfileIntA("S","SY_2",0,".\\ÅäÖÃ.INI");  
 
	 TA[2].ArrayGongJi.x = ::GetPrivateProfileIntA("S","GX_2",0,".\\ÅäÖÃ.INI"); 
	 TA[2].ArrayGongJi.y = ::GetPrivateProfileIntA("S","GY_2",0,".\\ÅäÖÃ.INI");   
	 
	 TA[2].x1 = ::GetPrivateProfileIntA("S","P2_X1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[2].y1 = ::GetPrivateProfileIntA("S","P2_Y1",0,".\\ÅäÖÃ.INI") -20;   
	 TA[2].x2 = ::GetPrivateProfileIntA("S","P2_X2",0,".\\ÅäÖÃ.INI")  +20;   
	 TA[2].y2 = ::GetPrivateProfileIntA("S","P2_Y2",0,".\\ÅäÖÃ.INI")  +20;   
	  
	 strcpy_s(TA[2].TA_NO_END_PIC ,256 ,".\\RES\\SUB\\t3g_s.bmp" );

	  

}





CXialu::CXialu(void)
{
	CurIndex = 0;
	memset(TA , 0 ,sizeof(MyStructTa)*20);
	 
}


 
CXialu::~CXialu(void)
{
}



void CXialu::SetCurTA(int index)
{
	CurIndex = index ;
	CurTA_XY = TA[CurIndex];
}

bool CXialu::IsTA_GONGJI_OVER(Mydm* dm)
{
	OutputDebugStringA("ÐèÒªÕÒµÄÍ¼Æ¬ÊÇ:");
		OutputDebugStringA(CurTA_XY.TA_NO_END_PIC);
	if (dm->FindPic2(CurTA_XY.x1 , CurTA_XY.y1 ,CurTA_XY.x2 ,CurTA_XY.y2,CurTA_XY.TA_NO_END_PIC)!=-1 )
	{
	
		if (dm->FindPic2(0,0,1024,768,".\\res\\sub\\¹ÖÎïÑª.BMP")==-1 )
		{
			OutputDebugStringA("¶ÔÃæËþÍêµ°ÁË");
			return true;
		}
	}

	OutputDebugStringA("¶ÔÃæËþ»¹ÔÚ");
	return false;
}
CString  tmpx;
bool  CXialu::GotoTA_SUB(Mydm* dm)
{
			dm->KeyPress(VK_SPACE);
/*
	if (this->IsTA_GONGJI_OVER(dm))
	{
		OutputDebugStringA("Ä£Ê½Ö® GotoTA_SUB ");
		// 
		return  true;
	}*/
	
			tmpx.Format("µ±Ç°Ç°Íù·ÀÊØÇøÓò:%dºÅ  ×ø±ê:%d %d",CurIndex,CurTA_XY.ArrayFangYu.x , CurTA_XY.ArrayFangYu.y);
			OutputDebugStringA(tmpx.GetBuffer(0));
	
	dm->KeyPress(VK_SPACE);
	Sleep(30);
	dm->KeyDown(VK_SHIFT);
	Sleep(40);
	dm->MOVE_RDBCLICK(CurTA_XY.ArrayFangYu.x , CurTA_XY.ArrayFangYu.y, 500);
	Sleep(40);
	dm->KeyUp(VK_SHIFT);
	Sleep(30);
	
	if (dm->IsDisplayDead(474,431,579,523,1) != 1)
	{
	 
		dm->MOVE_RDBCLICK(CurTA_XY.ArrayFangYu.x , CurTA_XY.ArrayFangYu.y, 500);
		OutputDebugStringA("Ã»µ½Ä¿µÄµØ");
		return false ;
	}
	OutputDebugStringA("´ïµ½Ä¿µÄµØ");
	return true ;
}


bool  CXialu::GotoTA_SUB_gongji(Mydm* dm)
{
	tmpx.Format("µ±Ç°Ç°Íù¹¥»÷ÇøÓò:%dºÅ  ×ø±ê:%d %d",CurIndex,CurTA_XY.ArrayGongJi.x , CurTA_XY.ArrayGongJi.y);
	OutputDebugStringA(tmpx.GetBuffer(0));
			dm->KeyPress(VK_SPACE);
			Sleep(30);
			dm->KeyDown(VK_SHIFT);
			Sleep(40);
	dm->MOVE_RDBCLICK(CurTA_XY.ArrayGongJi.x , CurTA_XY.ArrayGongJi.y, 500);
	Sleep(40);
	dm->KeyUp(VK_SHIFT);
	Sleep(30);
	if (dm->IsDisplayDead(324,344,379,386,1) != 1)
	{
		dm->MOVE_RDBCLICK(CurTA_XY.ArrayGongJi.x , CurTA_XY.ArrayGongJi.y, 500);
		OutputDebugStringA("Ã»µ½Ä¿µÄµØ¹¥»÷");
		return false ;
	}
	OutputDebugStringA("´ïµ½Ä¿µÄµØ¹¥»÷");
	return true ;
}




void CXialu::Check_ShiJiao(Mydm* dm,bool OFF)
{
 
	if (OFF)
	{
		OutputDebugStringA("ÇÐ»»ÊÓ½ÇÖÐ ×Ô¼ºÎªÖÐÐÄÄ£Ê½  Ç°×à");
		dm->KeyPress(VK_SPACE);
		Sleep(500);
		while (dm->FindPic2(915,549,1013,580,".\\RES\\SUB\\ÊÓ½Ç.BMP") != -1)
		{
			OutputDebugStringA("ÇÐ»»ÊÓ½ÇÖÐ ×Ô¼ºÎªÖÐÐÄÄ£Ê½");
			
				dm->KeyPress('Y');
				Sleep(100);
				dm->KeyPress(VK_SPACE);
				Sleep(500);

		}
	}else
	{
		while (dm->FindPic2(915,549,1013,580,".\\RES\\SUB\\ÊÓ½Ç.BMP") == -1)
		{
			OutputDebugStringA("ÇÐ»»ÊÓ½ÇÖÐ Æ½ÃæÄ£Ê½");
/*
			dm->MoveTo(931,669);
			Sleep(100);
			dm->LeftDown();
			Sleep(200);
			dm->LeftUp();
			Sleep(200);*/
			dm->KeyPress('Y');
			Sleep(80);
			dm->KeyPress(VK_SPACE);
			Sleep(80);
			//	dm->MOVE_CLICK(995,562,100); 
			Sleep(80);

		}

	}

	//	AfxMessageBox("END SHIJIAO");

}