//
//	AFL Timer Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afTimer
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "afltimer.h"

///////////////////////////////////////////////////////////
//	�^�C�}�[�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afTimer::afTimer()
{
	StartTime=GetTickCount();
	AlarmTime=0;
}

///////////////////////////////////////////////////////////
//	�^�C�}�[�I�u�W�F�N�g�\�z
//	���l	DWORD	�A���[������(�~���b)

afTimer::afTimer(DWORD a)
{
	StartTime=GetTickCount();
	AlarmTime=a;
}

///////////////////////////////////////////////////////////
//	�^�C�}�[�����Z�b�g
//	���l	�Ȃ�

void	afTimer::ResetTimer()
{
	StartTime=GetTickCount();
}

///////////////////////////////////////////////////////////
//	�A���[�����Ԃ�ݒ肷��
//	���l	DWORD	�A���[������(�~���b)

void	afTimer::SetAlarm(DWORD a)
{
	AlarmTime=a;
}

///////////////////////////////////////////////////////////
//	���݂̌o�ߎ��Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	DWORD	���݂̌o�ߎ���(�~���b)

DWORD	afTimer::GetTime()
{
	DWORD	t;

	t=GetTickCount()-StartTime;
	return	t;
}

///////////////////////////////////////////////////////////
//	�A���[�����쓮�������ǂ������擾
//	���l	�Ȃ�
//	�Ԓl	bool	���(true=�쓮 or false=���쓮)
//	(true��Ԃ��ƃ^�C�}�[�����������܂��B)

bool	afTimer::GetAlarm()
{
	DWORD	t;

	t=GetTickCount()-StartTime;
	if(t<AlarmTime)	return	false;

	StartTime=GetTickCount();
	return	true;
}

///////////////////////////////////////////////////////////
//	�A���[�����쓮�������ǂ������擾
//	���l	DWORD	�A���[������(�~���b)
//	�Ԓl	bool	���(true=�쓮 or false=���쓮)
//	(true��Ԃ��Ă��^�C�}�[�����������܂���B)

bool	afTimer::GetAlarm(DWORD a)
{
	DWORD	t;

	t=GetTickCount()-StartTime;
	if(t>=a)	return	true;
	else		return	false;
}
