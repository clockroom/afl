//
//	AFL File Dialog Box Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afFileBox
//

///////////////////////////////////////////////////////////
//	インクルード

#include "afldialog.h"
#include "aflinside.h"

///////////////////////////////////////////////////////////
//	ファイルボックスオブジェクト構築
//	引値	int		スタイル
//						FB_OPEN	ファイルを開く
//						FB_SAVE	名前をつけて保存

afFileBox::afFileBox(int n)
{
	nStyle=n;
	dTitle=0;
	dFilter=0;
	dDefExt=0;
	dInitDir=0;
	dFileName=new char[512];
	dFileName[0]=NULL;
}

///////////////////////////////////////////////////////////
//	ファイルボックスオブジェクト破棄
//	引値	なし

afFileBox::~afFileBox()
{
	delete[] dTitle;
	delete[] dFilter;
	delete[] dDefExt;
	delete[] dInitDir;
	delete[] dFileName;
}

///////////////////////////////////////////////////////////
//	タイトルを設定
//	引値	char*	タイトルの文字列

void afFileBox::SetTitle(const char *s)
{
	delete[] dTitle;
	if(s==NULL)
	{
		dTitle=0;
		return;
	}
	dTitle=new char[strlen(s)+1];
	strcpy(dTitle,s);
}

///////////////////////////////////////////////////////////
//	フィルターを追加
//	引値	char*	フィルタの説明の文字列
//			char*	フィルタの文字列

void afFileBox::AddFilter(const char *i,const char *f)
{
	char	buf[1024];

	buf[0]=NULL;
	if(dFilter!=0)
	{
		strcpy(buf,dFilter);
	}

	delete[] dFilter;
	if(i==NULL||f==NULL)
	{
		dFilter=0;
		return;
	}
	strcat(buf,i);
	strcat(buf,"|");
	strcat(buf,f);
	strcat(buf,"|");
	dFilter=new char[strlen(buf)+1];
	strcpy(dFilter,buf);
}

///////////////////////////////////////////////////////////
//	初期拡張子を設定
//	引値	char*	拡張子の文字列

void afFileBox::SetDefExt(const char *s)
{
	delete[] dDefExt;
	if(s==NULL)
	{
		dDefExt=0;
		return;
	}
	dDefExt=new char[strlen(s)+1];
	strcpy(dDefExt,s);
}

///////////////////////////////////////////////////////////
//	初期ディレクトリを取得
//	引値	char*	初期ディレクトリの文字列

void afFileBox::SetInitialDir(const char *s)
{
	delete[] dInitDir;
	if(s==NULL)
	{
		dInitDir=0;
		return;
	}
	dInitDir=new char[strlen(s)+1];
	strcpy(dInitDir,s);
}

///////////////////////////////////////////////////////////
//	ファイル名を取得する
//	引値	char*	ファイル名を格納するバッファのアドレス

void afFileBox::GetFileName(char *b)
{
	strcpy(b,dFileName);
}

///////////////////////////////////////////////////////////
//	ファイルボックスを開く
//	引値	なし
//	返値	int		入力結果
//						IDOK		実行
//						IDCANCEL	キャンセル

int afFileBox::OpenBox()
{
	LPDIRECTDRAW	ddobj=GetDDObject();
	HWND			hwnd=GetWindowHandle();
	OPENFILENAME	ofn;
	int		i,n;
	int		ret;
	char	buf[1024];

	if(dFilter!=0)
	{
		strcpy(buf,dFilter);
		strcat(buf,"|");
		n=strlen(buf);
		for(i=0;i<n;i++)
		{
			if(buf[i]=='|') buf[i]=NULL;
		}
	}
	dFileName[0]=NULL;

	ofn.lStructSize		 =sizeof(OPENFILENAME);
	ofn.hwndOwner		 =hwnd;
	ofn.lpstrFilter		 =(dFilter!=0)?buf:NULL;
	ofn.lpstrCustomFilter=NULL;
	ofn.nFilterIndex	 =0;
	ofn.lpstrFile		 =dFileName;
	ofn.nMaxFile		 =512;
	ofn.lpstrFileTitle	 =NULL;
	ofn.lpstrInitialDir	 =(dInitDir!=0)?dInitDir:NULL;
	ofn.lpstrTitle		 =(dTitle!=0)?dTitle:NULL;
	ofn.Flags			 =OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT;
	ofn.nFileOffset		 =0;
	ofn.nFileExtension	 =0;
	ofn.lpstrDefExt		 =(dDefExt!=0)?dDefExt:NULL;

	if(ddobj!=NULL) ddobj->FlipToGDISurface();

	switch(nStyle)
	{
	case FB_OPEN:ret=GetOpenFileName(&ofn);break;
	case FB_SAVE:ret=GetSaveFileName(&ofn);break;
	}

	SetCursor(NULL);

	return	ret?IDOK:IDCANCEL;
}
