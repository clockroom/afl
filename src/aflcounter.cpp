//
//	AFL Counter Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afCounter
//

///////////////////////////////////////////////////////////
//	インクルード

#include "afltimer.h"

///////////////////////////////////////////////////////////
//	カウンターオブジェクト構築
//	引値	なし

afCounter::afCounter()
{
	cCounter=0;
	Alarm=0;
}

///////////////////////////////////////////////////////////
//	カウンターオブジェクト構築
//	引値	DWORD	アラームカウント

afCounter::afCounter(DWORD a)
{
	cCounter=0;
	Alarm=a;
}

///////////////////////////////////////////////////////////
//	アラームを設定
//	引値	DWORD	アラームカウント

void	afCounter::SetAlarm(DWORD a)
{
	Alarm=a;
}

///////////////////////////////////////////////////////////
//	現在のカウントを取得
//	引値	なし
//	返値	DWORD	現在のカウント数

DWORD	afCounter::GetCount()
{
	return	cCounter;
}

///////////////////////////////////////////////////////////
//	アラームが作動したかどうかを取得
//	引値	なし
//	返値	int		状態	0	未作動	(<アラーム)
//							1	作動	(=アラーム)
//							2	作動	(>アラーム)
//	(1以上を返した場合カウンターを初期化します)

int	afCounter::GetAlarm()
{
	int	r;

	if(Alarm>cCounter)	return	0;
	if(Alarm==cCounter)	r=1;
	if(Alarm<cCounter)	r=2;
	cCounter=0;

	return	r;
}

///////////////////////////////////////////////////////////
//	アラームが作動したかどうかを取得
//	引値	DWORD	アラームカウント
//	返値	int		0	未作動	(<アラーム)
//					1	作動	(=アラーム)
//					2	作動	(>アラーム)
//	(1以上を返してもカウンターを初期化しません)

int	afCounter::GetAlarm(DWORD a)
{
	int	r;

	if(a>cCounter)	return	0;
	if(a==cCounter)	r=1;
	if(a<cCounter)	r=2;

	return	r;
}

///////////////////////////////////////////////////////////
//	アラームが作動したかどうかを取得
//	引値	DWORD	最小値
//			DWORD	最大値
//	返値	bool	状態	true	作動
//							false	未作動
//	(trueを返してもカウンターを初期化しません)

bool	afCounter::GetAlarm(DWORD min,DWORD max)
{
	if(min<=cCounter&&cCounter<=max)	return	true;
	return	false;
}

///////////////////////////////////////////////////////////
//	カウンターを初期化する
//	引値	なし

void	afCounter::ResetCount()
{
	cCounter=0;
}

///////////////////////////////////////////////////////////
//	カウンターを進める
//	引値	なし

void	afCounter::UpdateCount()
{
	cCounter++;
}

///////////////////////////////////////////////////////////
//	(DWORD)変換演算子
//	引値	なし

afCounter::operator DWORD()
{
	return	cCounter;
}
