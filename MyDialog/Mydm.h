#pragma once 
#include "Cdmsoft.h"
#include <functional>
struct Mydm
{
public:
	Idmsoft*  dm;
	long SetDict ( long index, _bstr_t dict_name );
	long FindPic ( long x1, long y1, long x2, long y2, _bstr_t pic_name, _bstr_t delta_color, double sim, long dir, VARIANT * x, VARIANT * y );
	_bstr_t Ver ( );
	long FindWindowEx ( long parent, _bstr_t class_name, _bstr_t title_name );


	long Capture (
		long x1,
		long y1,
		long x2,
		long y2,
		_bstr_t file );
	long KeyPress (
		long vk );
	long KeyDown (
		long vk );
	long KeyUp (
		long vk );
	long LeftClick ( );
	long RightClick ( );
	long MiddleClick ( );
	long LeftDoubleClick ( );
	long LeftDown ( );
	long LeftUp ( );
	long RightDown ( );
	long RightUp ( );
	long MoveTo (
		long x,
		long y );

	long CapturePng (
		long x1,
		long y1,
		long x2,
		long y2,
		_bstr_t file );

	long WheelUp ( );
	long WheelDown ( );

	long UseDict (
		long index );
	  long UnBindWindow ( );
	  long IsDisplayDead (
		  long x1,
		  long y1,
		  long x2,
		  long y2,
		  long t );

	  long BindWindowEx (
		  long hwnd,
		  _bstr_t display,
		  _bstr_t mouse,
		  _bstr_t keypad,
		  _bstr_t public_desc,
		  long mode );

	  long ForceUnBindWindow (
		  long hwnd );
	  long FindInputMethod (
		  _bstr_t id );
	  long ActiveInputMethod (
		  long hwnd,
		  _bstr_t id );
	  long CheckInputMethod (
		  long hwnd,
		  _bstr_t id );

	VARIANT   X1,Y1;
	Mydm(void);
	~Mydm(void);
	//////////////////////////////////////////////////////////////////////////
	VARIANT  tx,ty;
	RECT  GameRect;
	long  m_hwnd;
	bool Isreg;
	bool  Init();
	bool MyReg();
	void Uninit(); 
	bool  FindDic_AndMoto(long x1, long y1, long x2, long y2, LPCTSTR str, LPCTSTR color, double sim,std::function<void()> IFFind ,std::function<void()> IFNOFIND);

	void SetDic1();
	bool BindWindows1();
		bool BindWindows2();
	void   Ret_MousePos();
	void  MOVE_DBCLICK(long x  ,  long y,int SleepTime);
	void  MOVE_RDBCLICK(long x  ,  long y,int SleepTime);
 void   MOVE_CLICK(long x , long y,int SleepTime);
bool FindStr_forEach(long x1, long y1, long x2, long y2, LPCTSTR str, LPCTSTR color, double sim, VARIANT * x, VARIANT * y,int FindChout);
bool Mydm::FindPic_forEach(long x1, long y1, long x2, long y2, LPCTSTR str, LPCTSTR color, double sim, VARIANT * x, VARIANT * y,int FindChout);
void Sendstring_(char *  str);
int FindPic2(long x1, long y1, long x2, long y2, LPCTSTR pic_name, LPCTSTR delta_color="222222", double sim=0.9f, long dir=0 );
};