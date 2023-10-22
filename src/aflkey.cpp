//
//	AFL	Key Class by ClockRoom 2000
//	Program by Y.Kumagai ColckRoom 2000
//
//	afKey
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinput.h"
#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	キーオブジェクト構築
//	引値	int		仮想キーコード

afKey::afKey(int c)
{
	nCode =c;
	nState=KEY_FREE;
	fInvalidate=false;
}

///////////////////////////////////////////////////////////
//	キーの状態を更新
//	引値	なし

void	afKey::UpdateKey()
{
	short	k;

	k=GetKeyState(nCode)&0x80;
	if(k==0x80)
	{
		if(nState==KEY_HOLD)	nState=KEY_HOLD;
		if(nState==KEY_PUSH)	nState=KEY_HOLD;
		if(nState==KEY_FREE)	nState=KEY_PUSH;
		if(nState==KEY_PULL)	nState=KEY_PUSH;
	}
	else
	{
		if(nState==KEY_FREE)	nState=KEY_FREE;
		if(nState==KEY_PULL)	nState=KEY_FREE;
		if(nState==KEY_HOLD)	nState=KEY_PULL;
		if(nState==KEY_PUSH)	nState=KEY_PULL;
	}

	if(nState==KEY_FREE)	fInvalidate=false;
}

///////////////////////////////////////////////////////////
//	キーが離されるまで無効化
//	引値	なし

void	afKey::InvalidateKey()
{
	fInvalidate=true;
}

///////////////////////////////////////////////////////////
//	キーの状態を初期化
//	引値	なし

void	afKey::ResetKey()
{
	nState=KEY_FREE;
}

///////////////////////////////////////////////////////////
//	キーコードを設定
//	引値	int		仮想キーコード

void	afKey::SetKeyCode(int c)
{
	nCode=c;
	nState=KEY_FREE;
}

///////////////////////////////////////////////////////////
//	キーの状態を取得
//	引値	なし
//	返値	int		キーの状態
//						KEY_FREE=離されている
//						KEY_PUSH=押された
//						KEY_HOLD=押されている
//						KEY_PULL=離された

int		afKey::GetKey()
{
	if(fInvalidate)	return KEY_FREE;
	return nState;
}

///////////////////////////////////////////////////////////
//	(int)変換演算子
//	引値	なし
//	返値	int		キーの状態
//						KEY_FREE=離されている
//						KEY_PUSH=押された
//						KEY_HOLD=押されている
//						KEY_PULL=離された

afKey::operator int()
{
	if(fInvalidate)	return KEY_FREE;
	return nState;
}
