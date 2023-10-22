//
//	AFL Message Box Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afMsgBox
//

///////////////////////////////////////////////////////////
//	インクルード

#include "afldialog.h"
#include "afldefine.h"
#include "aflinside.h"

///////////////////////////////////////////////////////////
//	メッセージボックスオブジェクト構築
//	引値	int		スタイル
//						MB_INFOMATION	情報用
//						MB_QUESTION		質問用

afMsgBox::afMsgBox(int s)
{
	switch(s)
	{
	case MB_INFORMATION:
		nStyle=MB_OK|MB_ICONINFORMATION|MB_APPLMODAL;
		break;
	case MB_QUESTION:
		nStyle=MB_YESNO|MB_ICONQUESTION|MB_APPLMODAL;
		break;
	}
	dTitle=PNULL;
	dMessage=PNULL;
}

///////////////////////////////////////////////////////////
//	メッセージボックスオブジェクト破棄
//	引値	なし

afMsgBox::~afMsgBox()
{
	delete[] dTitle;
	delete[] dMessage;
}

///////////////////////////////////////////////////////////
//	タイトル設定
//	引値	char*	文字列へのポインタ

void afMsgBox::SetTitle(const char *s)
{
	delete[] dTitle;
	if(s==NULL)
	{
		dTitle=PNULL;
		return;
	}
	dTitle=new char[strlen(s)+1];
	strcpy(dTitle,s);
}

///////////////////////////////////////////////////////////
//	メッセージを設定
//	引値	char*	文字列へのポインタ

void afMsgBox::SetMessage(const char *s)
{
	delete[] dMessage;
	if(s==NULL)
	{
		dMessage=PNULL;
		return;
	}
	dMessage=new char[strlen(s)+1];
	strcpy(dMessage,s);
}

///////////////////////////////////////////////////////////
//	メッセージボックスを開く
//	引値	なし
//	返値	int		結果	IDOK	[OK]	が押された
//							IDYES	[はい]	が押された
//							IDNO	[いいえ]が押された

int afMsgBox::OpenBox()
{
	LPDIRECTDRAW	ddobj=GetDDObject();
	HWND			hwnd=GetWindowHandle();
	int		ret;
	char	ttl[128];
	char	msg[2048];

	if(dTitle==PNULL) strcpy(ttl,"メッセージ");
	else			  strcpy(ttl,dTitle);

	if(dMessage==PNULL) strcpy(msg,"メッセージはありません。");
	else				strcpy(msg,dMessage);

	if(ddobj!=NULL) ddobj->FlipToGDISurface();

	ret=MessageBox(hwnd,msg,ttl,nStyle);

	SetCursor(NULL);

	return	ret;
}
