//
//	AFL	Key Class by ClockRoom 2000
//	Program by Y.Kumagai ColckRoom 2000
//
//	afKey
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflinput.h"
#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	�L�[�I�u�W�F�N�g�\�z
//	���l	int		���z�L�[�R�[�h

afKey::afKey(int c)
{
	nCode =c;
	nState=KEY_FREE;
	fInvalidate=false;
}

///////////////////////////////////////////////////////////
//	�L�[�̏�Ԃ��X�V
//	���l	�Ȃ�

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
//	�L�[���������܂Ŗ�����
//	���l	�Ȃ�

void	afKey::InvalidateKey()
{
	fInvalidate=true;
}

///////////////////////////////////////////////////////////
//	�L�[�̏�Ԃ�������
//	���l	�Ȃ�

void	afKey::ResetKey()
{
	nState=KEY_FREE;
}

///////////////////////////////////////////////////////////
//	�L�[�R�[�h��ݒ�
//	���l	int		���z�L�[�R�[�h

void	afKey::SetKeyCode(int c)
{
	nCode=c;
	nState=KEY_FREE;
}

///////////////////////////////////////////////////////////
//	�L�[�̏�Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	int		�L�[�̏��
//						KEY_FREE=������Ă���
//						KEY_PUSH=�����ꂽ
//						KEY_HOLD=������Ă���
//						KEY_PULL=�����ꂽ

int		afKey::GetKey()
{
	if(fInvalidate)	return KEY_FREE;
	return nState;
}

///////////////////////////////////////////////////////////
//	(int)�ϊ����Z�q
//	���l	�Ȃ�
//	�Ԓl	int		�L�[�̏��
//						KEY_FREE=������Ă���
//						KEY_PUSH=�����ꂽ
//						KEY_HOLD=������Ă���
//						KEY_PULL=�����ꂽ

afKey::operator int()
{
	if(fInvalidate)	return KEY_FREE;
	return nState;
}
