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
//	�C���N���[�h

#include "afltimer.h"

///////////////////////////////////////////////////////////
//	�I�V���[�^�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afOscillator::afOscillator()
{
	StartTime=GetTickCount();
	ErrorTime=0xFFFF;
	BaseTime =0;
	TempTime =0;
}

///////////////////////////////////////////////////////////
//	�I�V���[�^�I�u�W�F�N�g�\�z
//	���l	WORD	�����i�~���b�j

afOscillator::afOscillator(WORD t)
{
	StartTime=GetTickCount();
	ErrorTime=0xFFFF;
	BaseTime =t;
	TempTime =t;
}

///////////////////////////////////////////////////////////
//	�I�V���[�^�I�u�W�F�N�g�\�z
//	���l	WORD	�����i�~���b�j
//			WORD	���e�덷�i�~���b�j

afOscillator::afOscillator(WORD t,WORD e)
{
	StartTime=GetTickCount();
	ErrorTime=e;
	BaseTime =t;
	TempTime =t;
}

///////////////////////////////////////////////////////////
//	������ݒ�
//	���l	WORD	�����i�~���b�j

void afOscillator::SetTimingFrequency(WORD t)
{
	BaseTime=t;
	TempTime=t;
}

///////////////////////////////////////////////////////////
//	���e�덷��ݒ�
//	���l	WORD	���e�덷�i�~���b�j

void afOscillator::SetAcceptableError(WORD e)
{
	ErrorTime=e;
}

///////////////////////////////////////////////////////////
//	���U�̗L�����擾
//	���l	�Ȃ�
//	�Ԓl	bool	true	���U
//					false	���U

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
//	���Z�b�g
//	���l	�Ȃ�

void afOscillator::ResetOscillator()
{
	StartTime=GetTickCount();
	TempTime=BaseTime;
}

///////////////////////////////////////////////////////////
//	�L���X�g�I�y���[�^
//	���l	�Ȃ�
//	�Ԓl	bool	true	���U
//					false	���U

afOscillator::operator bool()
{
	return IsSignal();
}
