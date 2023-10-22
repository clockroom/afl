//
//	AFL Graphic Group Class ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/30
//	Last  Edition 2001/09/30
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	�O���t�B�b�N�O���[�v�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afGrpGroup::afGrpGroup()
{
	X=0;
	Y=0;
	nMarker=NULL;
}

///////////////////////////////////////////////////////////
//	�ʒu�ݒ�
//	���l	int		X���W
//			int		Y���W

void afGrpGroup::SetPos(int x,int y)
{
	X=x;
	Y=y;
}

///////////////////////////////////////////////////////////
//	�}�[�J��ݒ�
//
//	���l int	�}�[�J
//
//	�Ԓl �Ȃ�

void afGrpGroup::SetMarker(int n)
{
	nMarker=n;
}

///////////////////////////////////////////////////////////
//	�ʒu�擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void afGrpGroup::GetPos(int *px,int *py)
{
	if(px!=NULL) *px=X;
	if(py!=NULL) *py=Y;
}

///////////////////////////////////////////////////////////
//	�w��I�u�W�F�N�g����Ƃ����ʒu�擾
//	���l	int*		X���W���i�[����ϐ��̃A�h���X
//			int*		Y���W���i�[����ϐ��̃A�h���X
//			afGrpGroup*	��I�u�W�F�N�g�փ|�C���^

void afGrpGroup::GetPos(int *px,int *py,afGrpGroup *pg)
{
	int	ax,ay,bx,by;

	GetPosByScreen(&ax,&ay);
	if(pg!=NULL) {pg->GetPosByScreen(&bx,&by);}
	else		 {bx=0; by=0;}

	if(px!=NULL) *px=ax-bx;
	if(py!=NULL) *py=ay-by;
}

///////////////////////////////////////////////////////////
//	�I�u�W�F�N�g�̈ʒu���X�N���[�����W�Ŏ擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void afGrpGroup::GetPosByScreen(int *px,int *py)
{
	GetGroupPosByScreen(px,py);
	if(px!=NULL) *px+=X;
	if(py!=NULL) *py+=Y;
}

///////////////////////////////////////////////////////////
//	���[�g�O���[�v�̈ʒu���擾
//
//	���l int*	X���W���i�[����ϐ��̃A�h���X
//		 int*	Y���W���i�[����ϐ��̃A�h���X
//
//	�Ԓl �Ȃ�

void afGrpGroup::GetRootGroupPos(int* px,int* py)
{
	if(pGroup==NULL || nMarker==MARKER_ROOTGROUP)
	{
		GetPosByScreen(px,py);
		return;
	}

	pGroup->GetRootGroupPos(px,py);
}

///////////////////////////////////////////////////////////
//	�}�[�N���ꂽ�O���[�v�̈ʒu���擾
//
//	���l int*	�w���W���i�[����ϐ��̃A�h���X
//		 int*	�x���W���i�[����ϐ��̃A�h���X
//		 int	�}�[�J
//
//	�Ԓl �Ȃ�

void afGrpGroup::GetMarkedGroupPos(int *px,int *py,int n)
{
	if(nMarker==n)
	{
		GetPos(px,py);
		return;
	}

	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetMarkedGroupPos(px,py,n);
}

///////////////////////////////////////////////////////////
//	�}�[�N���ꂽ�O���[�v�̈ʒu���X�N���[�����W�Ŏ擾
//
//	���l int*	�w���W���i�[����ϐ��̃A�h���X
//		 int*	�x���W���i�[����ϐ��̃A�h���X
//		 int	�}�[�J
//
//	�Ԓl �Ȃ�

void afGrpGroup::GetMarkedGroupPosByScreen(int *px,int *py,int n)
{
	if(nMarker==n)
	{
		GetPosByScreen(px,py);
		return;
	}

	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetMarkedGroupPosByScreen(px,py,n);
}
