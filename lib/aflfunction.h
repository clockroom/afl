//
//	AFL Function by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef _AFLFUNC_H_
#define _AFLFUNC_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class afApp;

///////////////////////////////////////////////////////////
//	型定義

typedef void (afApp::*FPAPPFUNC)();

///////////////////////////////////////////////////////////
//	マクロ定義

//	乱数を返す
#define RND(a)		randr(a)
#define RNDE(a,b)	randr(a,b,true)		//	0の許可
#define RNDEZ(a,b)	randr(a,b,false)	//	0の不許可

///////////////////////////////////////////////////////////
//	システム系関数

//	情報系
bool IsWindowsNT();

///////////////////////////////////////////////////////////
//	アプリケーション系関数

//	設定系
void SetActiveApp(afApp*,int);
void SetActiveApp(afApp*,FPAPPFUNC);
void SetActiveApp(void(*)());

//	処理系
bool CallActiveApp();

///////////////////////////////////////////////////////////
//	ファイル処理系関数

bool SearchFile(const char*);

///////////////////////////////////////////////////////////
//	文字列系関数

//	取得系
void GetFullPathFileName(char*,const char*);
void GetFileName(char*,const char*);
void GetPath(char*,const char*);

///////////////////////////////////////////////////////////
//	数学系関数

//	乱数系
int randr(int);
int randr(int,int,bool);

//	三角関数系
void InitTriFunc();
int  isin(int);
int  icos(int);

///////////////////////////////////////////////////////////
//	便利系関数

void OpenDebugBox(bool,const char*,...);
void OpenDebugBox(const char*,...);

#endif	//	_AFLFUNC_H_
