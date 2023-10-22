//
//	AFL Function by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

///////////////////////////////////////////////////////////
//	インクルード

#include <aflfunction.h>
#include <aflinclude.h>
#include <aflapp.h>
#include <afldialog.h>

///////////////////////////////////////////////////////////
//	ファイル変数定義

//	アプリケーション系関数
static afApp	 *_af_pActiveApp=NULL;
static FPAPPFUNC _af_fpActiveAppFunc=NULL;

//	数学系関数
static int _af_dSinTbl[256];
static int _af_dCosTbl[256];

///////////////////////////////////////////////////////////
//
//	システム系関数
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	ＮＴかどうか取得
//
//	引値 なし
//
//	返値 bool	true	NT
//				false	9x

bool IsWindowsNT()
{
	OSVERSIONINFO	ovi;

	ovi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&ovi);

	if(ovi.dwPlatformId==VER_PLATFORM_WIN32_NT) return true;

	return false;
}

///////////////////////////////////////////////////////////
//
//	アプリケーション系関数
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	アプリケーションを設定
//	引値	afApp*	アプリケーションオブジェクトへのポインタ
//			int		ルーチン	初期化	APP_INIT
//								終了	APP_FINAL
//								メイン	APP_MAIN

void SetActiveApp(afApp *pApp,int nFunc)
{
	_af_pActiveApp=pApp;
	_af_fpActiveAppFunc=*((FPAPPFUNC*)&nFunc);
}

///////////////////////////////////////////////////////////
//	アプリケーションを設定
//	引値	afApp*		アプリケーションオブジェクトへのポインタ
//			afApp::*	アプリケーションクラスメンバへのポインタ

void SetActiveApp(afApp *pApp,FPAPPFUNC fpFunc)
{
	_af_pActiveApp=pApp;
	_af_fpActiveAppFunc=fpFunc;
}

///////////////////////////////////////////////////////////
//	アプリケーションを設定
//	引値	void	(*)()	関数へのポインタ

void SetActiveApp(void (*fpFunc)())
{
	_af_pActiveApp=NULL;
	_af_fpActiveAppFunc=*((FPAPPFUNC*)&fpFunc);
}

///////////////////////////////////////////////////////////
//	アクティブアプリケーション呼び出し
//	引値	なし

bool CallActiveApp()
{
	if(_af_fpActiveAppFunc==NULL) return false;

	if(_af_pActiveApp==NULL)
	{
		(*((void(**)())&_af_fpActiveAppFunc))();
		return true;
	}

	if(_af_pActiveApp->AppSwitch(*((int*)&_af_fpActiveAppFunc))) return true;

	(_af_pActiveApp->*_af_fpActiveAppFunc)();

	return true;
}

///////////////////////////////////////////////////////////
//
//	ファイル処理系
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	ファイルの有無を確認
//	引値	char*	ファイル名へのポインタ
//	返値	bool	結果(true=発見 or false)

bool SearchFile(const char *file)
{
	FILE	*fp;

	if((fp=fopen(file,"rb"))==NULL) return false;
	fclose(fp);
	return true;
}

///////////////////////////////////////////////////////////
//
//	文字列系関数
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	ファイル名からフルパスファイル名を取得
//	引値	char*	フルパスファイル名を格納するバッファのアドレス
//			char*	ファイル名へのポインタ

void GetFullPathFileName(char *path,const char *file)
{
	char	buf[512];
	char	*p;

	//	フルパスファイル名が渡された場合
	if(strchr(file,':')!=NULL)
	{
		strcpy(path,file);
		return;
	}

	//	ファイル名が渡された場合
	GetModuleFileName(NULL,buf,512);
	p=strrchr(buf,'\\')+1;
	*p='\0';

	//	コピー
	strcat(buf,file);
	strcpy(path,buf);
}

///////////////////////////////////////////////////////////
//	パスファイル名からファイル名を取得
//	引値	char*	ファイル名を格納するバッファのアドレス
//			char*	パスファイル名へのポインタ

void GetFileName(char *file,const char *path)
{
	char	*p;

	p=strrchr(path,'\\');
	if(p!=NULL) strcpy(file,p+1);
	else		strcpy(file,path);
}

///////////////////////////////////////////////////////////
//	パスファイル名からパス名を取得
//	引値	char*	パス名を格納するバッファのアドレス
//			char*	パスファイル名へのポインタ

void GetPath(char *path,const char *file)
{
	char	*p;

	strcpy(path,file);
	p=strrchr(path,'\\');
	if(p!=NULL) *p='\0';
	else		path[0]='\0';
}

///////////////////////////////////////////////////////////
//
//	数学系関数
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	指定値までの乱数を返す
//	引値	int		最大値
//	返値	int		乱数

int randr(int n)
{
	return	rand()%(n+1);
}

///////////////////////////////////////////////////////////
//	指定範囲の乱数を返す
//	引値	int		最小値
//			int		最大値
//			bool	0の許可(true=許可 or false)
//	返値	int		乱数

int randr(int min,int max,bool z)
{
	int	r;
	int	a=(max-min)+1;

	do	r=rand()%a+min;	while(z==false&&r==0);

	return	r;
}

///////////////////////////////////////////////////////////
//	三角関数を初期化する
//	引値	なし

void InitTriFunc()
{
	int		i;
	double	a;

	for(i=0;i<256;i++)
	{
		a=3.141592*((double)i)/128.0;
		_af_dSinTbl[i]=(int)(sin(a)*256.0);
		_af_dCosTbl[i]=(int)(cos(a)*256.0);
	}
}

///////////////////////////////////////////////////////////
//	sin の値を固定小数表記で返す
//	引値	int		角度(256で一周)
//	返値	int		sin を256倍した値

int isin(int a)
{
	return	_af_dSinTbl[a&0x000000ff];
}

///////////////////////////////////////////////////////////
//	cos の値を固定小数表記で返す
//	引値	int		角度(256で一周)
//	返値	int		cos を256倍した値

int icos(int a)
{
	return	_af_dCosTbl[a&0x000000ff];
}

///////////////////////////////////////////////////////////
//
//	便利系関数
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	指定フォーマットの文字列をダイアログで表示
//	引値	bool	true	表示
//					false	非表示
//			char*	フォーマット
//			...		変数

void OpenDebugBox(bool f,const char *format,...)
{
	afErrorBox	eb;
	char	str[1024];

	if(!f) return;

	vsprintf(str,format,(char*)(&format+1));

	eb.SetTitle("デバッグ");
	eb.SetMessage(str);
	eb.OpenBox();
}

///////////////////////////////////////////////////////////
//	指定フォーマットの文字列をダイアログで表示
//	引値	char*	フォーマット
//			...		変数

void OpenDebugBox(const char *format,...)
{
	afErrorBox	eb;
	char	str[1024];

	vsprintf(str,format,(char*)(&format+1));

	eb.SetTitle("デバッグ");
	eb.SetMessage(str);
	eb.OpenBox();
}
