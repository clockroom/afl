//
//	AFL Main Program by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#define INITGUID

#include <aflinside.h>
#include <aflfunction.h>
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	�֐��錾

static LRESULT CALLBACK _af_WindowProc(HWND,UINT,WPARAM,LPARAM);

static bool _af_InitApp(HINSTANCE,HINSTANCE,LPSTR,int);
static void _af_ExitApp();
static bool _af_Init();
static void _af_Exit();

bool afInit();
void afMain();

///////////////////////////////////////////////////////////
//	�t�@�C���ϐ���`

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
//	���C�����[�`��

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,char *psCmdLine,int nCmdShow)
{
	//	�ϐ�
	WNDCLASS	wc;
	MSG			msg;
	time_t		tm;
	int			w,h;

	//	�f�[�^������
	_af_hInstance=hInstance;
	CharLower(psCmdLine);

	//	�V�X�e��������
	WINNLSEnableIME(NULL,FALSE);
	srand((unsigned)time(&tm));

	//	�A�v���P�[�V���� ������
	if(!_af_InitApp(hInstance,hPrevInstance,psCmdLine,nCmdShow)) return 0;

	//	�E�B���h�E�N���X�쐬
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

	//	�E�B���h�E�쐬
	w=GetSystemMetrics(SM_CXSCREEN);
	h=GetSystemMetrics(SM_CYSCREEN);
	_af_hWnd=CreateWindowEx(0,_af_sWndClsName,_af_psAppName,
						WS_POPUP|WS_SYSMENU,
						0,0,w,h,NULL,NULL,hInstance,NULL);
	if(_af_hWnd==NULL) return 0;

	ShowWindow(_af_hWnd,nCmdShow);
	UpdateWindow(_af_hWnd);

	//	AFL ������
	if(!_af_Init()) PostMessage(_af_hWnd,WM_CLOSE,0,0);

	//	���C�����[�v
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

	//	�A�v���P�[�V�����I������
	_af_ExitApp();

	return msg.wParam;
}

///////////////////////////////////////////////////////////
//	�E�B���h�E�v���V�[�W��

LRESULT CALLBACK _af_WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//	�J�X�^���v���V�[�W��
	if(_af_fpWindowProc!=NULL)
	{
		if(_af_fpWindowProc(hwnd,msg,wParam,lParam)) return 0;
	}

	//	���b�Z�[�W����
	switch(msg)
	{
		//	�L�[����
		case WM_KEYDOWN:
		{
			if(wParam==VK_ESCAPE)
			{
				PostMessage(hwnd,WM_CLOSE,0,0);
				return 0;
			}
			break;
		}

		//	�A�N�e�B�u�E��A�N�e�B�u����
		case WM_ACTIVATEAPP:
		{
			if(!wParam)	_af_fActive=false;
			else		_af_fActive=true;
			return 0;
		}

		//	�J�[�\������
		case WM_SETCURSOR:
		{
			SetCursor(NULL);
			return TRUE;
		}

		//	�V�X�e���L�[����
		case WM_SYSKEYDOWN:
		{
			return 0;
		}

		//	�V�X�e���R�}���h����
		case WM_SYSCOMMAND:
		{
			if(wParam==SC_SCREENSAVE) return 0;
			break;
		}

		//	MIDI ����
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

		//	�I������
		case WM_CLOSE:
		{
			if(_af_fClose) return 0;
			_af_fClose=true;

			_af_Exit();
			return 0;
		}

		//	�j������
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}

///////////////////////////////////////////////////////////
//	�A�v���P�[�V���� ������

bool _af_InitApp(HINSTANCE hInstance,HINSTANCE hPrevInstance,char *psCmdLine,int nCmdShow)
{
	//	�R�}���h���C����ۑ�
	if(strlen(psCmdLine)>0)
	{
		_af_psCmdLine=new char[strlen(psCmdLine)+1];
		strcpy(_af_psCmdLine,psCmdLine);
	}

	//	�A�v���P�[�V�������ݒ�
	if(_af_psAppName==0)
	{
		_af_psAppName=new char[strlen(_af_sDefAppName)+1];
		strcpy(_af_psAppName,_af_sDefAppName);
	}

	//	�������v���V�[�W��
	if(_af_fpInitAppProc==NULL)	return true;

	return _af_fpInitAppProc(hInstance,hPrevInstance,psCmdLine,nCmdShow);
}

///////////////////////////////////////////////////////////
//	�A�v���P�[�V���� �I������

void _af_ExitApp()
{
	//	�e��I������
	delete[] _af_psCmdLine;
	delete[] _af_psAppName;
	_af_psCmdLine=0;
	_af_psAppName=0;
	_af_hWnd=NULL;

	//	�I���v���V�[�W��
	if(_af_fpExitAppProc!=NULL)
	{
		_af_fpExitAppProc();
	}
}

///////////////////////////////////////////////////////////
//	AFL ������

bool _af_Init()
{
	//	�e�평����
	InitTriFunc();

	//	�������֐�
	return afInit();
}

///////////////////////////////////////////////////////////
//	AFL �I������

void _af_Exit()
{
	//	�I���v���V�[�W��
	if(_af_fpExitProc!=NULL)
	{
		if(!(_af_fpExitProc)())	return;
	}

	//	�I������
	_coreGraphics::DestroyGraphics();
	_coreMusic::DestroyMusic();
	_coreMusic2::DestroyMusic();
	_coreSound::DestroySound();

	//	�E�B���h�E�j��
	DestroyWindow(_af_hWnd);
}

///////////////////////////////////////////////////////////
//
//	Inside Interface Fanction
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	�A�v���P�[�V��������ݒ�
//	���l	char*	�A�v���P�[�V�������ւ̃|�C���^
//	�Ԓl	bool	true	�ݒ�
//					false	���ݒ�

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
//	�A�v���P�[�V�����������v���V�[�W����ݒ�
//	���l	bool(*)(HINSTANCE,HINSTANCE,char*,int)	�֐��ւ̃|�C���^
//	�Ԓl	bool	true	�ݒ�
//					false	���ݒ�

bool SetInitAppProc(bool (*ip)(HINSTANCE,HINSTANCE,char*,int))
{
	_af_fpInitAppProc=ip;

	if(ip==NULL) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	�A�v���P�[�V�����I���v���V�[�W����ݒ�
//	���l	void(*)()	�֐��ւ̃|�C���^
//	�Ԓl	bool	true	�ݒ�
//					false	���ݒ�

bool SetExitAppProc(void (*ep)())
{
	_af_fpExitAppProc=ep;

	if(ep==NULL) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	�E�B���h�E�v���V�[�W����ݒ�
//	���l	bool(*)(HWND,UINT,WPARAM,LPARAM)	�֐��ւ̃|�C���^

void SetWindowProc(bool (*wp)(HWND,UINT,WPARAM,LPARAM))
{
	_af_fpWindowProc=wp;
}

///////////////////////////////////////////////////////////
//	AFL�I���v���V�[�W����ݒ�
//	���l	bool(*)()	�֐��ւ̃|�C���^

void SetExitProc(bool (*ep)())
{
	_af_fpExitProc=ep;
}

///////////////////////////////////////////////////////////
//	AFL���I��
//	���l	�Ȃ�

void ExitProgram()
{
	PostMessage(_af_hWnd,WM_CLOSE,0,0);
}

///////////////////////////////////////////////////////////
//	�R�}���h���C�����擾
//	���l	char*	������o�b�t�@�̃A�h���X
//	�Ԓl	true	�R�}���h���C������
//			false	�R�}���h���C���Ȃ�

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
//	�C���X�^���X�n���h�����擾
//	���l	�Ȃ�
//	�Ԓl	HINSTANCE	�C���X�^���X�n���h��

HINSTANCE GetInstanceHandle()
{
	return _af_hInstance;
}

///////////////////////////////////////////////////////////
//	�E�B���h�E�n���h�����擾
//	���l	�Ȃ�
//	�Ԓl	HWND	�E�B���h�E�n���h��

HWND GetWindowHandle()
{
	return _af_hWnd;
}

///////////////////////////////////////////////////////////
//	�E�B���h�E�n���h����ݒ�
//	���l	HWND	�E�B���h�E�n���h��
//	�Ԓl	HWND	���O�̃E�B���h�E�n���h��
//	����	�g�p��͕K�����Ƃ̃n���h���ɖ߂��Ă�������

HWND SetWindowHandle(HWND h)
{
	HWND	old=_af_hWnd;

	_af_hWnd=h;
	return old;
}

///////////////////////////////////////////////////////////
//	DirectDraw�I�u�W�F�N�g���擾
//	���l	�Ȃ�
//	�Ԓl	LPDIRECTDRAW	DirectDraw�I�u�W�F�N�g�ւ̃|�C���^

LPDIRECTDRAW GetDDObject()
{
	return _coreGraphics::pDDObject;
}
