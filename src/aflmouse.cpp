//
//	AFL Mouse Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afMouse
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinput.h"
#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	マウスオブジェクト構築
//	引値	なし

afMouse::afMouse():KeyL(VK_LBUTTON),KeyR(VK_RBUTTON)
{
	pPatMos=NULL;
}

///////////////////////////////////////////////////////////
//	カーソルパターンを設定
//	引値	afPattern*	パターンへのポインタ

void afMouse::SetPattern(afPattern *p)
{
	pPatMos=p;
}

///////////////////////////////////////////////////////////
//	ホットスポットを設定
//	引値	int		X座標
//			int		Y座標

void afMouse::SetHotSpot(int x,int y)
{
	HX=x;
	HY=y;
}

///////////////////////////////////////////////////////////
//	カーソル位置を取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void afMouse::GetPos(int *x,int *y)
{
	POINT	cp;
	GetCursorPos(&cp);
	if(x!=NULL)	*x=cp.x;
	if(y!=NULL)	*y=cp.y;
}

///////////////////////////////////////////////////////////
//	左ボタンの状態を取得
//	引値	なし
//	返値	int		状態	KEY_PUSH	押された
//							KEY_HOLD	押されている
//							KEY_PULL	離された
//							KEY_FREE	離されている

int afMouse::GetKeyL()
{
	return	KeyL.GetKey();
}

///////////////////////////////////////////////////////////
//	右ボタンの状態を取得
//	引値	なし
//	返値	int		状態	KEY_PUSH	押された
//							KEY_HOLD	押されている
//							KEY_PULL	離された
//							KEY_FREE	離されている

int afMouse::GetKeyR()
{
	return	KeyR.GetKey();
}

///////////////////////////////////////////////////////////
//	ボタンの状態を取得
//	引値	なし
//	返値	int		状態	ML_... | MR_...
//							ML_PUSH		左ボタンが押された
//							ML_HOLD		左ボタンが押されている
//							ML_PULL		左ボタンが離された
//							ML_FREE		左ボタンが離されている
//							MR_PUSH		右ボタンが押された
//							MR_HOLD		右ボタンが押されている
//							MR_PULL		右ボタンが離された
//							MR_FREE		右ボタンが離されている

int afMouse::GetKey()
{
	int	l,r;

	l=KeyL<<8;
	r=KeyR;

	return	l|r;
}

///////////////////////////////////////////////////////////
//	ボタンの状態を取得
//	引値	int*	左ボタンの状態を格納する変数のアドレス
//			int*	右ボタンの状態を格納する変数のアドレス

void afMouse::GetKey(int *l,int *r)
{
	if(l!=NULL)	*l=KeyL.GetKey();
	if(r!=NULL)	*r=KeyR.GetKey();
}

///////////////////////////////////////////////////////////
//	ボタンの状態を更新
//	引値	なし

void afMouse::UpdateKey()
{
	KeyL.UpdateKey();
	KeyR.UpdateKey();
}

///////////////////////////////////////////////////////////
//	左ボタンの状態を更新
//	引値	なし

void afMouse::UpdateKeyL()
{
	KeyL.UpdateKey();
}

///////////////////////////////////////////////////////////
//	右ボタンの状態を更新
//	引値	なし

void afMouse::UpdateKeyR()
{
	KeyR.UpdateKey();
}

///////////////////////////////////////////////////////////
//	ボタンが離されるまで無効化
//	引値	なし

void afMouse::InvalidateKey()
{
	KeyL.InvalidateKey();
	KeyR.InvalidateKey();
}

///////////////////////////////////////////////////////////
//	左ボタンが離されるまで無効化
//	引値	なし

void afMouse::InvalidateKeyL()
{
	KeyL.InvalidateKey();
}

///////////////////////////////////////////////////////////
//	右ボタンが離されるまで無効化
//	引値	なし

void afMouse::InvalidateKeyR()
{
	KeyR.InvalidateKey();
}

///////////////////////////////////////////////////////////
//	ボタンの状態を初期化
//	引値	なし

void afMouse::ResetKey()
{
	KeyL.ResetKey();
	KeyR.ResetKey();
}

///////////////////////////////////////////////////////////
//	左ボタンの状態を初期化
//	引値	なし

void afMouse::ResetKeyL()
{
	KeyL.ResetKey();
}

///////////////////////////////////////////////////////////
//	右ボタンの状態を初期化
//	引値	なし

void afMouse::ResetKeyR()
{
	KeyR.ResetKey();
}

///////////////////////////////////////////////////////////
//	マウスカーソルを表示
//	引値	なし

void afMouse::Show()
{
	POINT	cp;

	GetCursorPos(&cp);
	pPatMos->Put(cp.x-HX,cp.y-HY);
}

///////////////////////////////////////////////////////////
//	(int)変換演算子
//	引値	なし
//	返値	int		状態	ML_... | MR_...
//							ML_PUSH		左ボタンが押された
//							ML_HOLD		左ボタンが押されている
//							ML_PULL		左ボタンが離された
//							ML_FREE		左ボタンが離されている
//							MR_PUSH		右ボタンが押された
//							MR_HOLD		右ボタンが押されている
//							MR_PULL		右ボタンが離された
//							MR_FREE		右ボタンが離されている

afMouse::operator int()
{
	int	l,r;

	l=KeyL<<8;
	r=KeyR;

	return	l|r;
}
