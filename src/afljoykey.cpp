//
//	AFL Joykey Class by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//
//	afJoykey
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinput.h"
#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	ジョイキーオブジェクト構築
//	引値	なし

afJoykey::afJoykey()
{
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得
//	引値	なし
//	返値	int		キー番号(0 - 8)

int	afJoykey::GetJoykey()
{
	int		n=0;
	short	l,r,u,d;

	l=GetKeyState(VK_LEFT)&0x80;
	r=GetKeyState(VK_RIGHT)&0x80;
	u=GetKeyState(VK_UP)&0x80;
	d=GetKeyState(VK_DOWN)&0x80;

	if(u==0x80&&r==0x00&&d==0x00&&l==0x00)	n=1;
	if(u==0x80&&r==0x80&&d==0x00&&l==0x00)	n=2;
	if(u==0x00&&r==0x80&&d==0x00&&l==0x00)	n=3;
	if(u==0x00&&r==0x80&&d==0x80&&l==0x00)	n=4;
	if(u==0x00&&r==0x00&&d==0x80&&l==0x00)	n=5;
	if(u==0x00&&r==0x00&&d==0x80&&l==0x80)	n=6;
	if(u==0x00&&r==0x00&&d==0x00&&l==0x80)	n=7;
	if(u==0x80&&r==0x00&&d==0x00&&l==0x80)	n=8;

	return	n;
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得
//	引値	int*	左右の状態を格納する変数へのポインタ
//			int*	上下の状態を格納する変数へのポインタ

void	afJoykey::GetJoykey(int *x,int*y)
{
	short	l,r,u,d;

	l=GetKeyState(VK_LEFT)&0x80;
	r=GetKeyState(VK_RIGHT)&0x80;
	u=GetKeyState(VK_UP)&0x80;
	d=GetKeyState(VK_DOWN)&0x80;

	if(x!=NULL)
	{
		*x=0;
		if(l==0x80)	*x=-1;
		if(r==0x80)	*x= 1;
	}
	if(y!=NULL)
	{
		*y=0;
		if(u==0x80)	*y=-1;
		if(d==0x80)	*y= 1;
	}
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得(4方向)
//	引値	なし
//	返値	int		キー番号(0 - 4)

int	afJoykey::GetJoykey4()
{
	int		n=0;
	short	l,r,u,d;

	l=GetKeyState(VK_LEFT)&0x80;
	r=GetKeyState(VK_RIGHT)&0x80;
	u=GetKeyState(VK_UP)&0x80;
	d=GetKeyState(VK_DOWN)&0x80;

	if(u==0x80&&r==0x00&&d==0x00&&l==0x00)	n=1;
	if(u==0x00&&r==0x80&&d==0x00&&l==0x00)	n=2;
	if(u==0x00&&r==0x00&&d==0x80&&l==0x00)	n=3;
	if(u==0x00&&r==0x00&&d==0x00&&l==0x80)	n=4;

	return	n;
}

///////////////////////////////////////////////////////////
//	十字キーの状態を取得(4方向)
//	引値	int*	左右の状態を格納する変数のアドレス
//			int*	上下の状態を格納する変数のアドレス

void	afJoykey::GetJoykey4(int *x,int *y)
{
	short	l,r,u,d;

	l=GetKeyState(VK_LEFT)&0x80;
	r=GetKeyState(VK_RIGHT)&0x80;
	u=GetKeyState(VK_UP)&0x80;
	d=GetKeyState(VK_DOWN)&0x80;

	if(x!=NULL)
	{
		*x=0;
		if(l==0x80)	*x=-1;
		if(r==0x80)	*x= 1;
	}
	if(y!=NULL)
	{
		*y=0;
		if(u==0x80)	*y=-1;
		if(d==0x80)	*y= 1;
	}
	if(x!=NULL && y!=NULL)
	{
		if((*x)!=0 && (*y)!=0)
		{
			*x=0;
			*y=0;
		}
	}
}
