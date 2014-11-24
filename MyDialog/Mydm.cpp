#include "stdafx.h"
#include "Mydm.h"


Mydm::Mydm(void)
{
	Isreg=false;
}


Mydm::~Mydm(void)
{
}


bool Mydm::Init()
{
/*
	if(Isreg==true)
	{
		OutputDebugStringA("已经注册,不再重复");
		return true;
	}*/

	CoInitialize(NULL);

	//dm->CreateDispatch("dm.dmsoft");
	return true;
}

void Mydm::Uninit()
{
/*	this->ReleaseDispatch(); */
	//	dm->Release();
	OutputDebugStringA("CoUninitialize");
	::CoUninitialize();
}
bool Mydm::MyReg()
{
	if(Isreg==true)
	{
		OutputDebugStringA("已经注册,不再重复");
		return true;
	}
	if (dm->Reg("a2896720827e5ca5910d57637aae1670b0c08fc61b","lol")!=1)
 {
	 AfxMessageBox("插件注册失败");
		return  false;
	}
	Isreg=true;
	return true;
}	


bool Mydm::FindDic_AndMoto(long x1, long y1, long x2, long y2, LPCTSTR str, LPCTSTR color, double sim,std::function<void()> IFFIND , std::function<void()> IFNOFIND)
{
	this->Ret_MousePos();
	Sleep(30);
	if (	dm->FindStrFast(x1,y1,x2,y2,str,color,sim,&tx,&ty) !=  -1)
	{
		dm->MoveTo(tx.lVal,ty.lVal);
		if(IFFIND!=nullptr)
		{
					IFFIND(); 
		}

		return true;
	}


	if(IFNOFIND!=nullptr)
	{
		IFNOFIND(); 
	}
	 
	return false ;
}


void Mydm::SetDic1()
{
	dm->SetDict(0,".\\Res\\t1.txt");

}


bool  Mydm::BindWindows1()
{


	   m_hwnd =  dm->FindWindowEx(0,"","PVP.net");
	if (m_hwnd<2)
	{
		OutputDebugStringA("Bindwindow 1  erro");
		return false ;
	}
	dm->ForceUnBindWindow(m_hwnd);
	Sleep(1000); 
	dm->SetWindowState(m_hwnd,12); 
   Sleep(1000);
/*
   ::MoveWindow((HWND)m_hwnd ,0,0,1152,720,true);
   AfxMessageBox("SET");
   //::SetWindowPos((HWND)m_hwnd ,HWND_NOTOPMOST,0,0,1152,720,SWP_NOMOVE);
   this->SetClientSize(m_hwnd,1152,720);
      AfxMessageBox("SET");*/
	while (dm->BindWindowEx(m_hwnd,"dx2","dx.mouse.position.lock.api|dx.mouse.position.lock.message|dx.mouse.clip.lock.api|dx.mouse.input.lock.api|dx.mouse.state.api|dx.mouse.api|dx.mouse.cursor","dx.keypad.input.lock.api|dx.keypad.state.api|dx.keypad.api","",101) != 1)
	{
		OutputDebugStringA("erro  bind 1");
		//return false ;
	}
	dm->SetWindowState(m_hwnd,12); 
	 Sleep(1000);
	dm->SetShowErrorMsg(0);
    dm->LockInput(1);
	return true ;
	}



bool  Mydm::BindWindows2()
{



	m_hwnd =  dm->FindWindowEx(0,"RiotWindowClass","League");
	if (m_hwnd<2)
	{
		AfxMessageBox("erro  wnd");
		return false ;
	}
/*
	this->ForceUnBindWindow(m_hwnd);
	Sleep(1000);*/

	dm->SetWindowState(m_hwnd,12); 
   Sleep(1000);
 ///this->BindWindowEx(m_hwnd, "dx2","dx.mouse.position.lock.api|dx.mouse.position.lock.message|dx.mouse.focus.input.api|dx.mouse.focus.input.message|dx.mouse.clip.lock.api|dx.mouse.input.lock.api|dx.mouse.state.api|dx.mouse.state.message|dx.mouse.api|dx.mouse.cursor|dx.mouse.raw.input|dx.mouse.input.lock.api2|dx.mouse.input.lock.api3","dx.keypad.input.lock.api|dx.keypad.state.api|dx.keypad.api","dx.public.active.api|dx.public.disable.window.position|dx.public.active.message|dx.public.hide.dll|dx.public.anti.api|dx.public.km.protect|dx.public.ori.proc|dx.public.focus.message",101)!= 1
 
	if (dm->BindWindowEx(m_hwnd,"dx2","dx.mouse.position.lock.api|dx.mouse.position.lock.message|dx.mouse.focus.input.api|dx.mouse.focus.input.message|dx.mouse.clip.lock.api|dx.mouse.state.api|dx.mouse.state.message|dx.mouse.api|dx.mouse.cursor","dx.keypad.input.lock.api|dx.keypad.state.api|dx.keypad.api","dx.public.active.api|dx.public.active.message|dx.public.disable.window.minmax",101)!= 1)
	{
			
		OutputDebugStringA("erro  bind 1");
		return false ;
	}
	Sleep(1000);
	dm->SetWindowState(m_hwnd,12); 
    Sleep(1000);
	dm->SetShowErrorMsg(0);
	//this->EnableFakeActive(1);
	dm->LockInput(1);
	return true ;
}

void Mydm::Ret_MousePos()
{
	dm->MoveTo(1,1);
}




void  Mydm::MOVE_DBCLICK(long x , long y,int SleepTime)
{
	dm->MoveTo(x,y);
	Sleep(SleepTime);
	dm->LeftDoubleClick();
	Sleep(SleepTime);
}

void  Mydm::MOVE_RDBCLICK(long x , long y,int SleepTime)
{
	dm->MoveTo(x,y);
	Sleep(SleepTime);
	dm->RightClick();
	Sleep(SleepTime);
	dm->RightClick();
	Sleep(SleepTime);
}


void  Mydm::MOVE_CLICK(long x , long y,int SleepTime)
{
	dm->MoveTo(x,y);
	Sleep(SleepTime);
	dm->LeftClick();
	Sleep(SleepTime);
}

bool Mydm::FindStr_forEach(long x1, long y1, long x2, long y2, LPCTSTR str, LPCTSTR color, double sim, VARIANT * x, VARIANT * y,int FindChout)
{
	for (int XX =0 ;XX< FindChout ;XX++)
	{
		if (dm->FindStrFast(x1,y1,x2,y2,str,color,sim,x,y) != -1)
		{
			return true;
		} 
		Sleep(1000);
	}
	
	return false ;

}





bool Mydm::FindPic_forEach(long x1, long y1, long x2, long y2, LPCTSTR str, LPCTSTR color, double sim, VARIANT * x, VARIANT * y,int FindChout)
{
	for (int XX =0 ;XX< FindChout ;XX++)
	{
		if (dm->FindPic(x1,y1,x2,y2,str,color,sim,0,x,y) != -1)
		{
			return true;
		} 
		Sleep(1000);
	}

	return false ;

}

VOID Mydm::Sendstring_(char * str)
{
	dm->SendString2(m_hwnd,str);
}


int Mydm::FindPic2(long x1, long y1, long x2, long y2, LPCTSTR pic_name, LPCTSTR delta_color/* ="222222" */, double sim/* =0.9f */, long dir/* =0 */ )
{ 
	return  dm->FindPic(x1,y1,x2,y2,pic_name,delta_color,sim,dir,&X1,&Y1);
}

//////////////////////////////////////////////////////////////////////////

long  Mydm::SetDict ( long index, _bstr_t dict_name )
{

	return dm->SetDict (  index,  dict_name );
}

long  Mydm::FindPic( long x1, long y1, long x2, long y2, _bstr_t pic_name, _bstr_t delta_color, double sim, long dir, VARIANT * x, VARIANT * y )
{


	return dm->FindPic( x1,  y1,  x2,  y2,  pic_name,  delta_color,  sim,  dir, x,  y)  ;
}

_bstr_t  Mydm::Ver ( )
{	
	return  dm->Ver();
}


 	long Mydm::FindWindowEx ( long parent, _bstr_t class_name, _bstr_t title_name )
	{
		return dm->FindWindowEx(parent,class_name,title_name);
	}



	long Mydm::Capture (
		long x1,
		long y1,
		long x2,
		long y2,
		_bstr_t file )
	{
		return dm->Capture(x1,y1,x2,y2,file);

	}
	long Mydm::KeyPress (
		long vk ){

			return dm->KeyPress(vk);
	}
	long Mydm::KeyDown (
		long vk ){
			return dm->KeyDown(vk);
	}


	long Mydm::KeyUp (
		long vk ){
			return dm->KeyUp(vk);
	}


	long Mydm::LeftClick ( ){

		return dm->LeftClick();
	}

	long Mydm::RightClick ( ){

		return dm->RightClick();
	}

	long Mydm::MiddleClick ( ){

		return dm->MiddleClick();
	}

	long Mydm::LeftDoubleClick ( ){
				return dm->LeftDoubleClick();
	}

	long Mydm::LeftDown ( ){

				return dm->LeftDown();
	}

	long Mydm::LeftUp ( ){
				return dm->LeftUp();
	}

	long Mydm::RightDown ( ){
				return dm->RightDown();
	}

	long Mydm:: RightUp ( ){
				return dm->RightUp();
	}

	long Mydm:: MoveTo (
		long x,
		long y ){
					return dm->MoveTo(x,y);
	}


	long Mydm::CapturePng (
		long x1,
		long y1,
		long x2,
		long y2,
		_bstr_t file )
	{
		return  dm->CapturePng(x1,y1,x2,y2,file);
	}


	long Mydm::WheelUp ( ){
		return dm->WheelUp();
	}
	long Mydm::WheelDown ( ){
	
		return dm->WheelDown();

	}






	long Mydm::UseDict (
		long index ){

			return  dm->UseDict(index);

	}
	long Mydm::UnBindWindow ( ){

		return dm->UnBindWindow();
	}
	long Mydm::IsDisplayDead (
		long x1,
		long y1,
		long x2,
		long y2,
		long t ){
			return dm->IsDisplayDead(x1,y1,x2,y2,t);
	}

	long Mydm::BindWindowEx (
		long hwnd,
		_bstr_t display,
		_bstr_t mouse,
		_bstr_t keypad,
		_bstr_t public_desc,
		long mode ){
			return dm->BindWindowEx(hwnd,display,mouse,keypad,public_desc,mode);
	}

	long Mydm::ForceUnBindWindow (
		long hwnd ){

				return dm->ForceUnBindWindow(hwnd);

	}
	long Mydm::FindInputMethod (
		_bstr_t id ){


				return dm->FindInputMethod(id);
	}
	long Mydm::ActiveInputMethod (
		long hwnd,
		_bstr_t id ){
				return dm->ActiveInputMethod(hwnd,id);


	}
	long Mydm::CheckInputMethod (
		long hwnd,
		_bstr_t id ){


				return dm->CheckInputMethod(hwnd,id);
	}