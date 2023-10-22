//
//	AFL Function by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef _AFLFUNC_H_
#define _AFLFUNC_H_

///////////////////////////////////////////////////////////
//	�N���X�錾

class afApp;

///////////////////////////////////////////////////////////
//	�^��`

typedef void (afApp::*FPAPPFUNC)();

///////////////////////////////////////////////////////////
//	�}�N����`

//	������Ԃ�
#define RND(a)		randr(a)
#define RNDE(a,b)	randr(a,b,true)		//	0�̋���
#define RNDEZ(a,b)	randr(a,b,false)	//	0�̕s����

///////////////////////////////////////////////////////////
//	�V�X�e���n�֐�

//	���n
bool IsWindowsNT();

///////////////////////////////////////////////////////////
//	�A�v���P�[�V�����n�֐�

//	�ݒ�n
void SetActiveApp(afApp*,int);
void SetActiveApp(afApp*,FPAPPFUNC);
void SetActiveApp(void(*)());

//	�����n
bool CallActiveApp();

///////////////////////////////////////////////////////////
//	�t�@�C�������n�֐�

bool SearchFile(const char*);

///////////////////////////////////////////////////////////
//	������n�֐�

//	�擾�n
void GetFullPathFileName(char*,const char*);
void GetFileName(char*,const char*);
void GetPath(char*,const char*);

///////////////////////////////////////////////////////////
//	���w�n�֐�

//	�����n
int randr(int);
int randr(int,int,bool);

//	�O�p�֐��n
void InitTriFunc();
int  isin(int);
int  icos(int);

///////////////////////////////////////////////////////////
//	�֗��n�֐�

void OpenDebugBox(bool,const char*,...);
void OpenDebugBox(const char*,...);

#endif	//	_AFLFUNC_H_
