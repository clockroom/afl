//
//	AFL Error Message Box Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afErrorBox
//

///////////////////////////////////////////////////////////
//	インクルード

#include "afldialog.h"
#include "aflinside.h"

///////////////////////////////////////////////////////////
//	エラーボックスオブジェクト構築
//	引値	なし

afErrorBox::afErrorBox()
{
	dTitle=0;
	dFileName=0;
	dFunctionName=0;
	dMessage=0;
	dRepair=0;
}

///////////////////////////////////////////////////////////
//	エラーボックスオブジェクト破棄
//	引値	なし

afErrorBox::~afErrorBox()
{
	delete[] dTitle;
	delete[] dFileName;
	delete[] dFunctionName;
	delete[] dMessage;
	delete[] dRepair;
}

///////////////////////////////////////////////////////////
//	タイトルを設定
//	引値	char*	タイトルの文字列

void afErrorBox::SetTitle(const char *s)
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
//	ファイル名を設定
//	引値	char*	ファイル名の文字列

void afErrorBox::SetFileName(const char *s)
{
	delete[] dFileName;
	if(s==NULL)
	{
		dFileName=0;
		return;
	}
	dFileName=new char[strlen(s)+1];
	strcpy(dFileName,s);
}

///////////////////////////////////////////////////////////
//	関数名を設定
//	引値	char*	関数名の文字列

void afErrorBox::SetFunctionName(const char *s)
{
	delete[] dFunctionName;
	if(s==NULL)
	{
		dFunctionName=0;
		return;
	}
	dFunctionName=new char[strlen(s)+1];
	strcpy(dFunctionName,s);
}

///////////////////////////////////////////////////////////
//	エラーメッセージを設定
//	引値	char*	メッセージの文字列

void afErrorBox::SetMessage(const char *s)
{
	delete[] dMessage;
	if(s==NULL)
	{
		dMessage=0;
		return;
	}
	dMessage=new char[strlen(s)+1];
	strcpy(dMessage,s);
}

///////////////////////////////////////////////////////////
//	対処法を設定
//	引値	char*	対処法への文字列

void	afErrorBox::SetRepair(const char *s)
{
	delete[] dRepair;
	if(s==NULL)
	{
		dRepair=0;
		return;
	}
	dRepair=new char[strlen(s)+1];
	strcpy(dRepair,s);
}

///////////////////////////////////////////////////////////
//	エラーボックスを開く
//	引値	なし
//	返値	int		常に IDOK が返る

int afErrorBox::OpenBox()
{
	LPDIRECTDRAW	ddobj=GetDDObject();
	HWND			hwnd=GetWindowHandle();
	char	ttl[128];
	char	str[2048];

	if(dTitle==0) strcpy(ttl,"エラー発生");
	else		  strcpy(ttl,dTitle);

	str[0]='\0';
	if(dFileName!=0)
	{
		strcat(str,"ファイル名：\n");
		strcat(str,dFileName);
		strcat(str,"\n");
	}

	if(dFunctionName!=0)
	{
		strcat(str,"関数名：\n");
		strcat(str,dFunctionName);
		strcat(str,"\n");
	}

	if(dFileName!=0||dFunctionName!=0)
	{
		strcat(str,"\n");
	}

	strcat(str,"内容：\n");
	if(dMessage!=0)
	{
		strcat(str,dMessage);
	}
	else
	{
		strcat(str,"エラーが発生しました。");
	}

	if(dRepair!=0)
	{
		strcat(str,"\n\n");
		strcat(str,"対処法：\n");
		strcat(str,dRepair);
	}

	if(ddobj!=NULL) ddobj->FlipToGDISurface();

	MessageBox(hwnd,str,ttl,MB_OK|MB_ICONEXCLAMATION|MB_SYSTEMMODAL);

	SetCursor(NULL);

	return IDOK;
}
