//
//	AFL Main Program by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//

///////////////////////////////////////////////////////////
//	インクルード

#define INITGUID

#include <aflinside.h>
#include <aflfunction.h>
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	関数宣言

static LRESULT CALLBACK _af_WindowProc(HWND,UINT,WPARAM,LPARAM);

static bool _af_InitApp(HINSTANCE,HINSTANCE,LPSTR,int);
static void _af_ExitApp();
static bool _af_Init();
static void _af_Exit();

bool afInit();
void afMain();

///////////////////////////////////////////////////////////
//	ファイル変数定義

static const char _af_sWndClsName[]="AFLAPPWNDCLS";
static const char _af_sDefAppName[]="AFL Application";

static char *_af_psCmdLine=0;
static char *_af_psAppName=0;

static bool (*_af_fpInitAppProc)(HINSTANCE,HINSTANCE,char*,int)=NULL;
static void (*_af_fpExitAppProc)()=NULL;

static bool (*_af_fpWindowProc)(HWND,UINT,WPARAM,LPARAM)=NULL;
static bool (*_af_fpExitProc)()=NULL;

static HINSTANCE _af_hInstance=NULL;
static HWND		 _af_hWnd=NULL;
static bool		 _af_fActive=false;
static bool		 _af_fClose=false;
static char		 _af_sMciBuffer[32];

///////////////////////////////////////////////////////////
//	メインルーチン

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,char *psCmdLine,int nCmdShow)
{
	//	変数
	WNDCLASS	wc;
	MSG			msg;
	time_t		tm;
	int			w,h;

	//	データ初期化
	_af_hInstance=hInstance;
	CharLower(psCmdLine);

	//	システム初期化
	WINNLSEnableIME(NULL,FALSE);
	srand((unsigned)time(&tm));

	//	アプリケーション 初期化
	if(!_af_InitApp(hInstance,hPrevInstance,psCmdLine,nCmdShow)) return 0;

	//	ウィンドウクラス作成
	wc.style=CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	wc.lpfnWndProc=_af_WindowProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(hInstance,"APPICON");
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=GetStockBrush(BLACK_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=_af_sWndClsName;
	RegisterClass(&wc);

	//	ウィンドウ作成
	w=GetSystemMetrics(SM_CXSCREEN);
	h=GetSystemMetrics(SM_CYSCREEN);
	_af_hWnd=CreateWindowEx(0,_af_sWndClsName,_af_psAppName,
						WS_POPUP|WS_SYSMENU,
						0,0,w,h,NULL,NULL,hInstance,NULL);
	if(_af_hWnd==NULL) return 0;

	ShowWindow(_af_hWnd,nCmdShow);
	UpdateWindow(_af_hWnd);

	//	AFL 初期化
	if(!_af_Init()) PostMessage(_af_hWnd,WM_CLOSE,0,0);

	//	メインループ
	while(TRUE)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message==WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if(_af_fActive)
			{
				_af_fClose=false;
				_coreGraphics::RestoreGraphics();

				afMain();
			}
			else
			{
				WaitMessage();
			}
		}
	}

	//	アプリケーション終了処理
	_af_ExitApp();

	return msg.wParam;
}

///////////////////////////////////////////////////////////
//	ウィンドウプロシージャ

LRESULT CALLBACK _af_WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//	カスタムプロシージャ
	if(_af_fpWindowProc!=NULL)
	{
		if(_af_fpWindowProc(hwnd,msg,wParam,lParam)) return 0;
	}

	//	メッセージ処理
	switch(msg)
	{
		//	キー処理
		case WM_KEYDOWN:
		{
			if(wParam==VK_ESCAPE)
			{
				PostMessage(hwnd,WM_CLOSE,0,0);
				return 0;
			}
			break;
		}

		//	アクティブ・非アクティブ処理
		case WM_ACTIVATEAPP:
		{
			if(!wParam)	_af_fActive=false;
			else		_af_fActive=true;
			return 0;
		}

		//	カーソル処理
		case WM_SETCURSOR:
		{
			SetCursor(NULL);
			return TRUE;
		}

		//	システムキー処理
		case WM_SYSKEYDOWN:
		{
			return 0;
		}

		//	システムコマンド処理
		case WM_SYSCOMMAND:
		{
			if(wParam==SC_SCREENSAVE) return 0;
			break;
		}

		//	MIDI 処理
		case MM_MCINOTIFY:
		{
			if(wParam!=MCI_NOTIFY_SUCCESSFUL) break;
			if(!_coreMusic::fPlay)			  break;

			mciSendString("status midi mode",_af_sMciBuffer,32,NULL);
			if(_af_sMciBuffer[0]=='s' && _af_sMciBuffer[1]=='t')
			{
				_coreMusic::Replay();
			}

			return 0;
		}

		//	終了処理
		case WM_CLOSE:
		{
			if(_af_fClose) return 0;
			_af_fClose=true;

			_af_Exit();
			return 0;
		}

		//	破棄処理
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}

///////////////////////////////////////////////////////////
//	アプリケーション 初期化

bool _af_InitApp(HINSTANCE hInstance,HINSTANCE hPrevInstance,char *psCmdLine,int nCmdShow)
{
	//	コマンドラインを保存
	if(strlen(psCmdLine)>0)
	{
		_af_psCmdLine=new char[strlen(psCmdLine)+1];
		strcpy(_af_psCmdLine,psCmdLine);
	}

	//	アプリケーション名設定
	if(_af_psAppName==0)
	{
		_af_psAppName=new char[strlen(_af_sDefAppName)+1];
		strcpy(_af_psAppName,_af_sDefAppName);
	}

	//	初期化プロシージャ
	if(_af_fpInitAppProc==NULL)	return true;

	return _af_fpInitAppProc(hInstance,hPrevInstance,psCmdLine,nCmdShow);
}

///////////////////////////////////////////////////////////
//	アプリケーション 終了処理

void _af_ExitApp()
{
	//	各種終了処理
	delete[] _af_psCmdLine;
	delete[] _af_psAppName;
	_af_psCmdLine=0;
	_af_psAppName=0;
	_af_hWnd=NULL;

	//	終了プロシージャ
	if(_af_fpExitAppProc!=NULL)
	{
		_af_fpExitAppProc();
	}
}

///////////////////////////////////////////////////////////
//	AFL 初期化

bool _af_Init()
{
	//	各種初期化
	InitTriFunc();

	//	初期化関数
	return afInit();
}

///////////////////////////////////////////////////////////
//	AFL 終了処理

void _af_Exit()
{
	//	終了プロシージャ
	if(_af_fpExitProc!=NULL)
	{
		if(!(_af_fpExitProc)())	return;
	}

	//	終了処理
	_coreGraphics::DestroyGraphics();
	_coreMusic::DestroyMusic();
	_coreMusic2::DestroyMusic();
	_coreSound::DestroySound();

	//	ウィンドウ破棄
	DestroyWindow(_af_hWnd);
}

///////////////////////////////////////////////////////////
//
//	Inside Interface Fanction
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	アプリケーション名を設定
//	引値	char*	アプリケーション名へのポインタ
//	返値	bool	true	設定
//					false	未設定

bool SetAppName(const char *psAppName)
{
	delete[] _af_psAppName;
	_af_psAppName=0;

	if(psAppName==NULL) return false;

	_af_psAppName=new char[strlen(psAppName)+1];
	strcpy(_af_psAppName,psAppName);

	return true;
}

///////////////////////////////////////////////////////////
//	アプリケーション初期化プロシージャを設定
//	引値	bool(*)(HINSTANCE,HINSTANCE,char*,int)	関数へのポインタ
//	返値	bool	true	設定
//					false	未設定

bool SetInitAppProc(bool (*ip)(HINSTANCE,HINSTANCE,char*,int))
{
	_af_fpInitAppProc=ip;

	if(ip==NULL) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	アプリケーション終了プロシージャを設定
//	引値	void(*)()	関数へのポインタ
//	返値	bool	true	設定
//					false	未設定

bool SetExitAppProc(void (*ep)())
{
	_af_fpExitAppProc=ep;

	if(ep==NULL) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	ウィンドウプロシージャを設定
//	引値	bool(*)(HWND,UINT,WPARAM,LPARAM)	関数へのポインタ

void SetWindowProc(bool (*wp)(HWND,UINT,WPARAM,LPARAM))
{
	_af_fpWindowProc=wp;
}

///////////////////////////////////////////////////////////
//	AFL終了プロシージャを設定
//	引値	bool(*)()	関数へのポインタ

void SetExitProc(bool (*ep)())
{
	_af_fpExitProc=ep;
}

///////////////////////////////////////////////////////////
//	AFLを終了
//	引値	なし

void ExitProgram()
{
	PostMessage(_af_hWnd,WM_CLOSE,0,0);
}

///////////////////////////////////////////////////////////
//	コマンドラインを取得
//	引値	char*	文字列バッファのアドレス
//	返値	true	コマンドラインあり
//			false	コマンドラインなし

bool GetCommandLine(char *str)
{
	if(_af_psCmdLine==0)
	{
		str[0]='\0';
		return false;
	}

	strcpy(str,_af_psCmdLine);
	return true;
}

///////////////////////////////////////////////////////////
//	インスタンスハンドルを取得
//	引値	なし
//	返値	HINSTANCE	インスタンスハンドル

HINSTANCE GetInstanceHandle()
{
	return _af_hInstance;
}

///////////////////////////////////////////////////////////
//	ウィンドウハンドルを取得
//	引値	なし
//	返値	HWND	ウィンドウハンドル

HWND GetWindowHandle()
{
	return _af_hWnd;
}

///////////////////////////////////////////////////////////
//	ウィンドウハンドルを設定
//	引値	HWND	ウィンドウハンドル
//	返値	HWND	直前のウィンドウハンドル
//	注意	使用後は必ずもとのハンドルに戻してください

HWND SetWindowHandle(HWND h)
{
	HWND	old=_af_hWnd;

	_af_hWnd=h;
	return old;
}

///////////////////////////////////////////////////////////
//	DirectDrawオブジェクトを取得
//	引値	なし
//	返値	LPDIRECTDRAW	DirectDrawオブジェクトへのポインタ

LPDIRECTDRAW GetDDObject()
{
	return _coreGraphics::pDDObject;
}
