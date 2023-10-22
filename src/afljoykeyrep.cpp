//
//	AFL Repeat Joykey Class by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//
//	afJoykey
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflinput.h"
#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	���s�[�g�Ή��W���C�L�[�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afJoykeyRep::afJoykeyRep()
{
	FWait=0;
	SWait=0;
	Count=-1;
}

//	���l	int		�ŏ��̃E�F�C�g
//			int		�Q��ڈȍ~�̃E�F�C�g

afJoykeyRep::afJoykeyRep(int f,int s)
{
	FWait=f;
	SWait=s;
	Count=-1;
}

///////////////////////////////////////////////////////////
//	�L�[�̏�Ԃ��X�V

void	afJoykeyRep::UpdateJoykey()
{
	int	x,y;

	Count++;
	if(Count>=FWait+SWait)	Count=FWait;

	afJoykey::GetJoykey(&x,&y);
	if(x==0 && y==0)	Count=-1;
}

///////////////////////////////////////////////////////////
//	�L�[�̏�Ԃ�������

void	afJoykeyRep::ResetJoykey()
{
	Count=-1;
}

///////////////////////////////////////////////////////////
//	���s�[�g�E�F�C�g��ݒ�
//	���l	int		�ŏ��̃E�F�C�g
//			int		�Q��ڈȍ~�̃E�F�C�g

void	afJoykeyRep::SetWait(int f,int s)
{
	FWait=f;
	SWait=s;
}

///////////////////////////////////////////////////////////
//	�\���L�[�̏�Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	int		�L�[�ԍ�(0 - 8)

int	afJoykeyRep::GetJoykey()
{
	int	n=0;

	if(Count<=0 || Count==FWait)
	{
		n=afJoykey::GetJoykey();
	}

	return	n;
}

///////////////////////////////////////////////////////////
//	�\���L�[�̏�Ԃ��擾
//	���l	int*	���E�̏�Ԃ��i�[����ϐ��ւ̃|�C���^
//			int*	�㉺�̏�Ԃ��i�[����ϐ��ւ̃|�C���^

void	afJoykeyRep::GetJoykey(int *x,int*y)
{
	if(x!=NULL)	*x=0;
	if(y!=NULL)	*y=0;

	if(Count<=0 || Count==FWait)
	{
		afJoykey::GetJoykey(x,y);
	}
}

///////////////////////////////////////////////////////////
//	�\���L�[�̏�Ԃ��擾(4����)
//	���l	�Ȃ�
//	�Ԓl	int		�L�[�ԍ�(0 - 4)

int	afJoykeyRep::GetJoykey4()
{
	int		n=0;

	if(Count<=0 || Count==FWait)
	{
		n=afJoykey::GetJoykey4();
	}

	return	n;
}

///////////////////////////////////////////////////////////
//	�\���L�[�̏�Ԃ��擾(4����)
//	���l	int*	���E�̏�Ԃ��i�[����ϐ��̃A�h���X
//			int*	�㉺�̏�Ԃ��i�[����ϐ��̃A�h���X

void	afJoykeyRep::GetJoykey4(int *x,int *y)
{
	if(x!=NULL)	*x=0;
	if(y!=NULL)	*y=0;

	if(Count<=0 || Count==FWait)
	{
		afJoykey::GetJoykey4(x,y);
	}
}
