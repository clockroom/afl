//
//	AFL Oscillator Class ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/22
//	Last  Edition 2002/02/18
//
//	afOscillator
//

///////////////////////////////////////////////////////////
//	インクルード

#include "afltimer.h"

///////////////////////////////////////////////////////////
//	オシレータオブジェクト構築
//	引値	なし

afOscillator::afOscillator()
{
	StartTime=GetTickCount();
	ErrorTime=0xFFFF;
	BaseTime =0;
	TempTime =0;
}

///////////////////////////////////////////////////////////
//	オシレータオブジェクト構築
//	引値	WORD	周期（ミリ秒）

afOscillator::afOscillator(WORD t)
{
	StartTime=GetTickCount();
	ErrorTime=0xFFFF;
	BaseTime =t;
	TempTime =t;
}

///////////////////////////////////////////////////////////
//	オシレータオブジェクト構築
//	引値	WORD	周期（ミリ秒）
//			WORD	許容誤差（ミリ秒）

afOscillator::afOscillator(WORD t,WORD e)
{
	StartTime=GetTickCount();
	ErrorTime=e;
	BaseTime =t;
	TempTime =t;
}

///////////////////////////////////////////////////////////
//	周期を設定
//	引値	WORD	周期（ミリ秒）

void afOscillator::SetTimingFrequency(WORD t)
{
	BaseTime=t;
	TempTime=t;
}

///////////////////////////////////////////////////////////
//	許容誤差を設定
//	引値	WORD	許容誤差（ミリ秒）

void afOscillator::SetAcceptableError(WORD e)
{
	ErrorTime=e;
}

///////////////////////////////////////////////////////////
//	発振の有無を取得
//	引値	なし
//	返値	bool	true	発振
//					false	無振

bool afOscillator::IsSignal()
{
	DWORD	mt=GetTickCount();
	int		ft=mt-StartTime;
	int		er=ft-BaseTime;

	if(ft<TempTime) return false;

	if(abs(er)<ErrorTime)
	{
		TempTime-=er;
		if(TempTime<0) TempTime=0;
	}
	else
	{
		TempTime=BaseTime;
	}

	StartTime=mt;

	return true;
}

///////////////////////////////////////////////////////////
//	リセット
//	引値	なし

void afOscillator::ResetOscillator()
{
	StartTime=GetTickCount();
	TempTime=BaseTime;
}

///////////////////////////////////////////////////////////
//	キャストオペレータ
//	引値	なし
//	返値	bool	true	発振
//					false	無振

afOscillator::operator bool()
{
	return IsSignal();
}
