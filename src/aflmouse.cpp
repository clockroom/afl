//
//	AFL Mouse Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afMouse
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflinput.h"
#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	�}�E�X�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afMouse::afMouse():KeyL(VK_LBUTTON),KeyR(VK_RBUTTON)
{
	pPatMos=NULL;
}

///////////////////////////////////////////////////////////
//	�J�[�\���p�^�[����ݒ�
//	���l	afPattern*	�p�^�[���ւ̃|�C���^

void afMouse::SetPattern(afPattern *p)
{
	pPatMos=p;
}

///////////////////////////////////////////////////////////
//	�z�b�g�X�|�b�g��ݒ�
//	���l	int		X���W
//			int		Y���W

void afMouse::SetHotSpot(int x,int y)
{
	HX=x;
	HY=y;
}

///////////////////////////////////////////////////////////
//	�J�[�\���ʒu���擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void afMouse::GetPos(int *x,int *y)
{
	POINT	cp;
	GetCursorPos(&cp);
	if(x!=NULL)	*x=cp.x;
	if(y!=NULL)	*y=cp.y;
}

///////////////////////////////////////////////////////////
//	���{�^���̏�Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	int		���	KEY_PUSH	�����ꂽ
//							KEY_HOLD	������Ă���
//							KEY_PULL	�����ꂽ
//							KEY_FREE	������Ă���

int afMouse::GetKeyL()
{
	return	KeyL.GetKey();
}

///////////////////////////////////////////////////////////
//	�E�{�^���̏�Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	int		���	KEY_PUSH	�����ꂽ
//							KEY_HOLD	������Ă���
//							KEY_PULL	�����ꂽ
//							KEY_FREE	������Ă���

int afMouse::GetKeyR()
{
	return	KeyR.GetKey();
}

///////////////////////////////////////////////////////////
//	�{�^���̏�Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	int		���	ML_... | MR_...
//							ML_PUSH		���{�^���������ꂽ
//							ML_HOLD		���{�^����������Ă���
//							ML_PULL		���{�^���������ꂽ
//							ML_FREE		���{�^����������Ă���
//							MR_PUSH		�E�{�^���������ꂽ
//							MR_HOLD		�E�{�^����������Ă���
//							MR_PULL		�E�{�^���������ꂽ
//							MR_FREE		�E�{�^����������Ă���

int afMouse::GetKey()
{
	int	l,r;

	l=KeyL<<8;
	r=KeyR;

	return	l|r;
}

///////////////////////////////////////////////////////////
//	�{�^���̏�Ԃ��擾
//	���l	int*	���{�^���̏�Ԃ��i�[����ϐ��̃A�h���X
//			int*	�E�{�^���̏�Ԃ��i�[����ϐ��̃A�h���X

void afMouse::GetKey(int *l,int *r)
{
	if(l!=NULL)	*l=KeyL.GetKey();
	if(r!=NULL)	*r=KeyR.GetKey();
}

///////////////////////////////////////////////////////////
//	�{�^���̏�Ԃ��X�V
//	���l	�Ȃ�

void afMouse::UpdateKey()
{
	KeyL.UpdateKey();
	KeyR.UpdateKey();
}

///////////////////////////////////////////////////////////
//	���{�^���̏�Ԃ��X�V
//	���l	�Ȃ�

void afMouse::UpdateKeyL()
{
	KeyL.UpdateKey();
}

///////////////////////////////////////////////////////////
//	�E�{�^���̏�Ԃ��X�V
//	���l	�Ȃ�

void afMouse::UpdateKeyR()
{
	KeyR.UpdateKey();
}

///////////////////////////////////////////////////////////
//	�{�^�����������܂Ŗ�����
//	���l	�Ȃ�

void afMouse::InvalidateKey()
{
	KeyL.InvalidateKey();
	KeyR.InvalidateKey();
}

///////////////////////////////////////////////////////////
//	���{�^�����������܂Ŗ�����
//	���l	�Ȃ�

void afMouse::InvalidateKeyL()
{
	KeyL.InvalidateKey();
}

///////////////////////////////////////////////////////////
//	�E�{�^�����������܂Ŗ�����
//	���l	�Ȃ�

void afMouse::InvalidateKeyR()
{
	KeyR.InvalidateKey();
}

///////////////////////////////////////////////////////////
//	�{�^���̏�Ԃ�������
//	���l	�Ȃ�

void afMouse::ResetKey()
{
	KeyL.ResetKey();
	KeyR.ResetKey();
}

///////////////////////////////////////////////////////////
//	���{�^���̏�Ԃ�������
//	���l	�Ȃ�

void afMouse::ResetKeyL()
{
	KeyL.ResetKey();
}

///////////////////////////////////////////////////////////
//	�E�{�^���̏�Ԃ�������
//	���l	�Ȃ�

void afMouse::ResetKeyR()
{
	KeyR.ResetKey();
}

///////////////////////////////////////////////////////////
//	�}�E�X�J�[�\����\��
//	���l	�Ȃ�

void afMouse::Show()
{
	POINT	cp;

	GetCursorPos(&cp);
	pPatMos->Put(cp.x-HX,cp.y-HY);
}

///////////////////////////////////////////////////////////
//	(int)�ϊ����Z�q
//	���l	�Ȃ�
//	�Ԓl	int		���	ML_... | MR_...
//							ML_PUSH		���{�^���������ꂽ
//							ML_HOLD		���{�^����������Ă���
//							ML_PULL		���{�^���������ꂽ
//							ML_FREE		���{�^����������Ă���
//							MR_PUSH		�E�{�^���������ꂽ
//							MR_HOLD		�E�{�^����������Ă���
//							MR_PULL		�E�{�^���������ꂽ
//							MR_FREE		�E�{�^����������Ă���

afMouse::operator int()
{
	int	l,r;

	l=KeyL<<8;
	r=KeyR;

	return	l|r;
}
