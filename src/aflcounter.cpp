//
//	AFL Counter Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afCounter
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "afltimer.h"

///////////////////////////////////////////////////////////
//	�J�E���^�[�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afCounter::afCounter()
{
	cCounter=0;
	Alarm=0;
}

///////////////////////////////////////////////////////////
//	�J�E���^�[�I�u�W�F�N�g�\�z
//	���l	DWORD	�A���[���J�E���g

afCounter::afCounter(DWORD a)
{
	cCounter=0;
	Alarm=a;
}

///////////////////////////////////////////////////////////
//	�A���[����ݒ�
//	���l	DWORD	�A���[���J�E���g

void	afCounter::SetAlarm(DWORD a)
{
	Alarm=a;
}

///////////////////////////////////////////////////////////
//	���݂̃J�E���g���擾
//	���l	�Ȃ�
//	�Ԓl	DWORD	���݂̃J�E���g��

DWORD	afCounter::GetCount()
{
	return	cCounter;
}

///////////////////////////////////////////////////////////
//	�A���[�����쓮�������ǂ������擾
//	���l	�Ȃ�
//	�Ԓl	int		���	0	���쓮	(<�A���[��)
//							1	�쓮	(=�A���[��)
//							2	�쓮	(>�A���[��)
//	(1�ȏ��Ԃ����ꍇ�J�E���^�[�����������܂�)

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
//	�A���[�����쓮�������ǂ������擾
//	���l	DWORD	�A���[���J�E���g
//	�Ԓl	int		0	���쓮	(<�A���[��)
//					1	�쓮	(=�A���[��)
//					2	�쓮	(>�A���[��)
//	(1�ȏ��Ԃ��Ă��J�E���^�[�����������܂���)

int	afCounter::GetAlarm(DWORD a)
{
	int	r;

	if(a>cCounter)	return	0;
	if(a==cCounter)	r=1;
	if(a<cCounter)	r=2;

	return	r;
}

///////////////////////////////////////////////////////////
//	�A���[�����쓮�������ǂ������擾
//	���l	DWORD	�ŏ��l
//			DWORD	�ő�l
//	�Ԓl	bool	���	true	�쓮
//							false	���쓮
//	(true��Ԃ��Ă��J�E���^�[�����������܂���)

bool	afCounter::GetAlarm(DWORD min,DWORD max)
{
	if(min<=cCounter&&cCounter<=max)	return	true;
	return	false;
}

///////////////////////////////////////////////////////////
//	�J�E���^�[������������
//	���l	�Ȃ�

void	afCounter::ResetCount()
{
	cCounter=0;
}

///////////////////////////////////////////////////////////
//	�J�E���^�[��i�߂�
//	���l	�Ȃ�

void	afCounter::UpdateCount()
{
	cCounter++;
}

///////////////////////////////////////////////////////////
//	(DWORD)�ϊ����Z�q
//	���l	�Ȃ�

afCounter::operator DWORD()
{
	return	cCounter;
}
