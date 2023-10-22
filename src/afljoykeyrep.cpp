//
//	AFL Repeat Joykey Class by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//
//	afJoykey
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinput.h"
#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	リピート対応ジョイキーオブジェクト構築
//	引値	なし

afJoykeyRep::afJoykeyRep()
{
	FWait=0;
	SWait=0;
	Count=-1;
}

//	引値	int		最初のウェイト
//			int		２回目以降のウェイト

afJoykeyRep::afJoykeyRep(int f,int s)
{
	FWait=f;
	SWait=s;
	Count=-1;
}

///////////////////////////////////////////////////////////
//	キーの状態を更新

void	afJoykeyRep::UpdateJoykey()
{
	int	x,y;

	Count++;
	if(Count>=FWait+SWait)	Count=FWait;

	afJoykey::GetJoykey(&x,&y);
	if(x==0 && y==0)	Count=-1;
}

///////////////////////////////////////////////////////////
//	キーの状態を初期化

void	afJoykeyRep::ResetJoykey()
{
	Count=-1;
}

///////////////////////////////////////////////////////////
//	リピートウェイトを設定
//	引値	int		最初のウェイト
//			int		２回目以降のウェイト

void	afJoykeyRep::SetWait(int f,int s)
{
	FWait=f;
	SWait=s;
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得
//	引値	なし
//	返値	int		キー番号(0 - 8)

int	afJoykeyRep::GetJoykey()
{
	int	n=0;

	if(Count<=0 || Count==FWait)
	{
		n=afJoykey::GetJoykey();
	}

	return	n;
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得
//	引値	int*	左右の状態を格納する変数へのポインタ
//			int*	上下の状態を格納する変数へのポインタ

void	afJoykeyRep::GetJoykey(int *x,int*y)
{
	if(x!=NULL)	*x=0;
	if(y!=NULL)	*y=0;

	if(Count<=0 || Count==FWait)
	{
		afJoykey::GetJoykey(x,y);
	}
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得(4方向)
//	引値	なし
//	返値	int		キー番号(0 - 4)

int	afJoykeyRep::GetJoykey4()
{
	int		n=0;

	if(Count<=0 || Count==FWait)
	{
		n=afJoykey::GetJoykey4();
	}

	return	n;
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得(4方向)
//	引値	int*	左右の状態を格納する変数のアドレス
//			int*	上下の状態を格納する変数のアドレス

void	afJoykeyRep::GetJoykey4(int *x,int *y)
{
	if(x!=NULL)	*x=0;
	if(y!=NULL)	*y=0;

	if(Count<=0 || Count==FWait)
	{
		afJoykey::GetJoykey4(x,y);
	}
}
