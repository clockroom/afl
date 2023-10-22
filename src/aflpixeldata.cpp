//
//	AFL Pixel Data Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	(afGrpObject)
//		afPixelData
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	�s�N�Z���f�[�^�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afPixelData::afPixelData()
{
	pPixel=NULL;
	Pitch=0;
}

///////////////////////////////////////////////////////////
//	�w����W�Ɏw��̐F��ݒ�
//	���l	int		X���W
//			int		Y���W
//			WORD	�F

void afPixelData::SetPixel(int x,int y,WORD col)
{
	WORD	*p;
	int		gx,gy;

	if(pPixel==NULL)	return;

	GetGroupPosByScreen(&gx,&gy);
	p=pPixel+(gy+y)*Pitch+(gx+x);
	*p=col;
}

///////////////////////////////////////////////////////////
//	�f�[�^�̃A�h���X���擾
//	���l	WORD**	�A�h���X���i�[����|�C���^�̃A�h���X
//			int*	�s�b�`���i�[����ϐ��̃A�h���X

void afPixelData::GetAddress(WORD **add,int *pt)
{
	*add=pPixel;
	*pt	=Pitch;
}

///////////////////////////////////////////////////////////
//	�w����W�̐F���擾
//	���l	int		X���W
//			int		Y���W
//	�Ԓl	WORD	�F

WORD afPixelData::GetPixel(int x,int y)
{
	WORD	*p;
	int		gx,gy;

	if(pPixel==NULL)	return 0;

	GetGroupPosByScreen(&gx,&gy);
	p=pPixel+(gy+y)*Pitch+(gx+x);

	return *p;
}
