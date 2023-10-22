//
//	AFL Graphic Object Class ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/30
//	Last  Edition 2001/09/30
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	�O���t�B�b�N�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afGrpObject::afGrpObject()
{
	pGroup=NULL;
}

///////////////////////////////////////////////////////////
//	�O���t�B�b�N�I�u�W�F�N�g�j��

afGrpObject::~afGrpObject()
{
}

///////////////////////////////////////////////////////////
//	�����O���[�v��ݒ�
//	���l	afGrpGroup*	�O���[�v�I�u�W�F�N�g�̃A�h���X
//	�Ԓl	afGrpGroup*	�ݒ�O�̃O���[�v�I�u�W�F�N�g�̃A�h���X

afGrpGroup *afGrpObject::SetGroup(afGrpGroup *p)
{
	afGrpGroup	*pold=pGroup;

	pGroup=p;

	return pold;
}

///////////////////////////////////////////////////////////
//	�����O���[�v�̈ʒu���擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void afGrpObject::GetGroupPos(int *px,int *py)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetPos(px,py);
}

///////////////////////////////////////////////////////////
//	�����O���[�v�̈ʒu���X�N���[�����W�Ŏ擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void afGrpObject::GetGroupPosByScreen(int *px,int *py)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetPosByScreen(px,py);
}

///////////////////////////////////////////////////////////
//	���[�g�O���[�v�̈ʒu���擾
//
//	���l int*	X���W���i�[����ϐ��̃A�h���X
//		 int*	Y���W���i�[����ϐ��̃A�h���X
//
//	�Ԓl �Ȃ�

void afGrpObject::GetRootGroupPos(int* px,int* py)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
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

void afGrpObject::GetMarkedGroupPos(int *px,int *py,int n)
{
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

void afGrpObject::GetMarkedGroupPosByScreen(int *px,int *py,int n)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetMarkedGroupPosByScreen(px,py,n);
}
