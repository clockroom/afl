//
//	AFL Point Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afPoint
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflfigure.h"

///////////////////////////////////////////////////////////
//	�_�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afPoint::afPoint()
{
	x=0;
	y=0;
}

///////////////////////////////////////////////////////////
//	�_�I�u�W�F�N�g�\�z
//	���l	int		X���W
//			int		Y���W

afPoint::afPoint(int a,int b)
{
	x=a;
	y=b;
}

///////////////////////////////////////////////////////////
//	�_�ݒ�
//	���l	int		X���W
//			int		Y���W

void afPoint::SetPoint(int a,int b)
{
	x=a;
	y=b;
}

///////////////////////////////////////////////////////////
//	�_�擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void afPoint::GetPoint(int *px,int *py)
{
	if(px!=NULL) *px=x;
	if(py!=NULL) *py=y;
}

///////////////////////////////////////////////////////////
//	�_�𑊑Έړ�
//	���l	int		X�ړ���
//			int		Y�ړ���

void afPoint::Move(int mx,int my)
{
	x+=mx;
	y+=my;
}
