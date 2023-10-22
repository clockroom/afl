//
//	AFL Pattern Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	(afGrpObject)
//		afPattern
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	�p�^�[���I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afPattern::afPattern()
{
	pBitmap=NULL;
	X=0;
	Y=0;
	W=0;
	H=0;
}

///////////////////////////////////////////////////////////
//	�p�^�[���쐬
//	���l	afBitmap*	afBitmap�I�u�W�F�N�g�ւ̃|�C���^
//			int			X���W
//			int			Y���W
//			int			��
//			int			����

void afPattern::CreatePattern(afBitmap *p,int x,int y,int w,int h)
{
	pBitmap=p;
	X=x;
	Y=y;
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	�p�^�[����ݒ�
//	���l	afBitmap*	afBitmap�I�u�W�F�N�g�ւ̃|�C���^
//			int			X���W
//			int			Y���W
//			int			��
//			int			����

void afPattern::SetPattern(afBitmap *p,int x,int y,int w,int h)
{
	pBitmap=p;
	X=x;
	Y=y;
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	�p�^�[����ݒ�
//	���l	int		X���W
//			int		Y���W
//			int		��
//			int		����

void afPattern::SetPattern(int x,int y,int w,int h)
{
	X=x;
	Y=y;
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	�p�^�[���̈ʒu��ݒ�
//	���l	int		X���W
//			int		Y���W

void afPattern::SetPatternPos(int x,int y)
{
	X=x;
	Y=y;
}

///////////////////////////////////////////////////////////
//	�p�^�[���T�C�Y��ݒ�
//	���l	int		��
//			int		����

void afPattern::SetPatternSize(int w,int h)
{
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	�p�^�[���̈ʒu�𑊑Έړ�
//	���l	int		X�ړ���
//			int		Y�ړ���

void afPattern::MovePattern(int x,int y)
{
	X+=x;
	Y+=y;
}

///////////////////////////////////////////////////////////
//	�p�^�[����\��
//	���l	int		X���W
//			int		Y���W

void afPattern::Put(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Put(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[���𓧖��F�𖳎����ĕ\��
//	���l	int		X���W
//			int		Y���W

void afPattern::Opaque(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Opaque(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[���𔼓����ŕ\��
//	���l	int		X���W
//			int		Y���W

void afPattern::Blend(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Blend(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[�������Z�������ŕ\��
//	���l	int		X���W
//			int		Y���W

void afPattern::Add(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Add(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[�������Z�����ŕ\��
//	���l	int		X���W
//			int		Y���W
//			int		������

void afPattern::AddBright(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->AddBright(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[�������Z�������ŕ\��
//	���l	int		X���W
//			int		Y���W

void afPattern::Subtract(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Subtract(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[�������Z�����ŕ\��
//	���l	int		X���W
//			int		Y���W
//			int		������

void afPattern::SubBright(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->SubBright(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[������Z�������ŕ\��
//	���l	int		X���W
//			int		Y���W
//			int		������

void afPattern::Multiply(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Multiply(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[���𒲌��ŕ\��
//	���l	int		X���W
//			int		Y���W
//			int		������

void afPattern::Bright(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Bright(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[���𓧖��F�����Œ����\��
//	���l	int		X���W
//			int		Y���W
//			int		������

void afPattern::BrightOpaque(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->BrightOpaque(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[�����g�k�\��
//	���l	int		X���W
//			int		Y���W
//			int		��
//			int		����

void afPattern::Stretch(int x,int y,int w,int h)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Stretch(x,y,w,h,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	�p�^�[���𓧖��F�𖳎����ĂȂ�ׂĕ\��
//	���l	int		X���W
//			int		Y���W
//			int		��
//			int		����

void afPattern::TileOpaque(int x,int y,int w,int h)
{
	afGrpGroup	*p;
	int	i,j,a,b;

	p=pBitmap->SetGroup(pGroup);
	for(j=0;j<h;j+=H)
		for(i=0;i<w;i+=W)
		{
			a=(w<i+W)?w%W:W;
			b=(h<j+H)?h%H:H;
			pBitmap->Opaque(x+i,y+j,X,Y,a,b);
		}
	pBitmap->SetGroup(p);
}
