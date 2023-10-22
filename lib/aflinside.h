//
//	AFL Inside Interface by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef	_AFLINSIDE_H_
#define	_AFLINSIDE_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <aflinclude.h>

///////////////////////////////////////////////////////////
//	�֐��錾

bool SetAppName(const char*);

bool SetInitAppProc(bool(*)(HINSTANCE,HINSTANCE,LPSTR,int));
bool SetExitAppProc(void(*)());

void SetWindowProc(bool(*)(HWND,UINT,WPARAM,LPARAM));
void SetExitProc(bool(*)());

void ExitProgram();

bool GetCommandLine(char*);

HINSTANCE GetInstanceHandle();
HWND	  GetWindowHandle();
HWND	  SetWindowHandle(HWND);

LPDIRECTDRAW GetDDObject();

#endif	//	_AFLINSIDE_H_
