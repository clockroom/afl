//
//	AFL Timer Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afTimer
//

///////////////////////////////////////////////////////////
//	インクルード

#include "afltimer.h"

///////////////////////////////////////////////////////////
//	タイマーオブジェクト構築
//	引値	なし

afTimer::afTimer()
{
	StartTime=GetTickCount();
	AlarmTime=0;
}

///////////////////////////////////////////////////////////
//	タイマーオブジェクト構築
//	引値	DWORD	アラーム時間(ミリ秒)

afTimer::afTimer(DWORD a)
{
	StartTime=GetTickCount();
	AlarmTime=a;
}

///////////////////////////////////////////////////////////
//	タイマーをリセット
//	引値	なし

void	afTimer::ResetTimer()
{
	StartTime=GetTickCount();
}

///////////////////////////////////////////////////////////
//	アラーム時間を設定する
//	引値	DWORD	アラーム時間(ミリ秒)

void	afTimer::SetAlarm(DWORD a)
{
	AlarmTime=a;
}

///////////////////////////////////////////////////////////
//	現在の経過時間を取得
//	引値	なし
//	返値	DWORD	現在の経過時間(ミリ秒)

DWORD	afTimer::GetTime()
{
	DWORD	t;

	t=GetTickCount()-StartTime;
	return	t;
}

///////////////////////////////////////////////////////////
//	アラームが作動したかどうかを取得
//	引値	なし
//	返値	bool	状態(true=作動 or false=未作動)
//	(trueを返すとタイマーを初期化します。)

bool	afTimer::GetAlarm()
{
	DWORD	t;

	t=GetTickCount()-StartTime;
	if(t<AlarmTime)	return	false;

	StartTime=GetTickCount();
	return	true;
}

///////////////////////////////////////////////////////////
//	アラームが作動したかどうかを取得
//	引値	DWORD	アラーム時間(ミリ秒)
//	返値	bool	状態(true=作動 or false=未作動)
//	(trueを返してもタイマーを初期化しません。)

bool	afTimer::GetAlarm(DWORD a)
{
	DWORD	t;

	t=GetTickCount()-StartTime;
	if(t>=a)	return	true;
	else		return	false;
}
