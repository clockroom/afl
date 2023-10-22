//
//	AFL Rect Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afRect
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflfigure.h"

///////////////////////////////////////////////////////////
//	�l�p�`�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afRect::afRect()
{
	left=0;
	right=0;
	top=0;
	bottom=0;
}

///////////////////////////////////////////////////////////
//	�l�p�`�I�u�W�F�N�g�\�z
//	���l	int		X���W
//			int		Y���W
//			int		��
//			int		����

afRect::afRect(int x,int y,int w,int h)
{
	left=x;
	right=x+w;
	top=y;
	bottom=y+h;
}

///////////////////////////////////////////////////////////
//	�l�p�`�ݒ�
//	���l	int		X���W
//			int		Y���W
//			int		��
//			int		����

void afRect::SetRect(int x,int y,int w,int h)
{
	left=x;
	right=x+w;
	top=y;
	bottom=y+h;
}

///////////////////////////////////////////////////////////
//	�l�p�`�擾
//	���l	int*	X���W���i�[����ϐ��ւ̃|�C���^
//			int*	Y���W���i�[����ϐ��ւ̃|�C���^
//			int*	�����i�[����ϐ��ւ̃|�C���^
//			int*	�������i�[����ϐ��ւ̃|�C���^

void afRect::GetRect(int *px,int *py,int *pw,int *ph)
{
	if(px!=NULL) *px=left;
	if(py!=NULL) *py=top;
	if(pw!=NULL) *pw=right-left;
	if(ph!=NULL) *ph=bottom-top;
}

///////////////////////////////////////////////////////////
//	�l�p�`���ړ�
//	���l	int		X�ړ���
//			int		Y�ړ���

void afRect::Move(int mx,int my)
{
	left+=mx;
	right+=mx;
	top+=my;
	bottom+=my;
}
