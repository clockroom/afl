//
//	AFL Timer by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//

#ifndef	_AFLTIMER_H_
#define	_AFLTIMER_H_

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	クラス宣言

class afTimer;
class afCounter;
class afOscillator;

///////////////////////////////////////////////////////////
//	タイマークラス

class afTimer
{
	public:
		//	構築
		afTimer();
		afTimer(DWORD);

		//	設定系
		void	SetAlarm(DWORD);

		//	取得系
		DWORD	GetTime();
		bool	GetAlarm();
		bool	GetAlarm(DWORD);

		//	更新系
		void	ResetTimer();

	private:
		//	変数
		DWORD	StartTime;
		DWORD	AlarmTime;
};

///////////////////////////////////////////////////////////
//	カウンタークラス

class afCounter
{
	public:
		//	構築
		afCounter();
		afCounter(DWORD);

		//	設定系
		void	SetAlarm(DWORD);

		//	取得系
		DWORD	GetCount();
		int		GetAlarm();
		int		GetAlarm(DWORD);
		bool	GetAlarm(DWORD,DWORD);

		//	更新系
		void	ResetCount();
		void	UpdateCount();

		//	演算子
		operator DWORD();

		//	変数
		DWORD	cCounter;

	private:
		//	変数
		DWORD	Alarm;
};

///////////////////////////////////////////////////////////
//	オシレータクラス

class afOscillator
{
	public:
		//	構築系
		afOscillator();
		afOscillator(WORD);
		afOscillator(WORD,WORD);

		//	設定系
		void	SetTimingFrequency(WORD);
		void	SetAcceptableError(WORD);

		//	取得系
		bool	IsSignal();

		//	更新系
		void	ResetOscillator();

		//	オペレータ
		operator bool();

	private:
		//	変数
		DWORD	StartTime;
		WORD	ErrorTime;
		int		BaseTime;
		int		TempTime;
};

#endif	//	_AFLTIMER_H_
