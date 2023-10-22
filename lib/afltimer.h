//
//	AFL Timer by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//

#ifndef	_AFLTIMER_H_
#define	_AFLTIMER_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	�N���X�錾

class afTimer;
class afCounter;
class afOscillator;

///////////////////////////////////////////////////////////
//	�^�C�}�[�N���X

class afTimer
{
	public:
		//	�\�z
		afTimer();
		afTimer(DWORD);

		//	�ݒ�n
		void	SetAlarm(DWORD);

		//	�擾�n
		DWORD	GetTime();
		bool	GetAlarm();
		bool	GetAlarm(DWORD);

		//	�X�V�n
		void	ResetTimer();

	private:
		//	�ϐ�
		DWORD	StartTime;
		DWORD	AlarmTime;
};

///////////////////////////////////////////////////////////
//	�J�E���^�[�N���X

class afCounter
{
	public:
		//	�\�z
		afCounter();
		afCounter(DWORD);

		//	�ݒ�n
		void	SetAlarm(DWORD);

		//	�擾�n
		DWORD	GetCount();
		int		GetAlarm();
		int		GetAlarm(DWORD);
		bool	GetAlarm(DWORD,DWORD);

		//	�X�V�n
		void	ResetCount();
		void	UpdateCount();

		//	���Z�q
		operator DWORD();

		//	�ϐ�
		DWORD	cCounter;

	private:
		//	�ϐ�
		DWORD	Alarm;
};

///////////////////////////////////////////////////////////
//	�I�V���[�^�N���X

class afOscillator
{
	public:
		//	�\�z�n
		afOscillator();
		afOscillator(WORD);
		afOscillator(WORD,WORD);

		//	�ݒ�n
		void	SetTimingFrequency(WORD);
		void	SetAcceptableError(WORD);

		//	�擾�n
		bool	IsSignal();

		//	�X�V�n
		void	ResetOscillator();

		//	�I�y���[�^
		operator bool();

	private:
		//	�ϐ�
		DWORD	StartTime;
		WORD	ErrorTime;
		int		BaseTime;
		int		TempTime;
};

#endif	//	_AFLTIMER_H_
