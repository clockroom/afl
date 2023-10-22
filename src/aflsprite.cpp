//
//	AFL Sprite Class by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	(afGrpGroup)
//		afSprite
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	�X�v���C�g�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afSprite::afSprite()
{
	int	i;

	pPattern=NULL;

	MX=0;
	MY=0;
	OX=0;
	OY=0;

	nOrigin=ORG_LEFTTOP;
	nStyle =SPR_NORMAL;

	for(i=0;i<8;i++) dParam[i]=0;

	fShow=false;
}

///////////////////////////////////////////////////////////
//	�X�v���C�g�쐬
//	���l	afPattern*	afPattern�I�u�W�F�N�g�ւ̃|�C���^
//			int			����X���W
//			int			����Y���W

void afSprite::CreateSprite(afPattern *p,int x,int y)
{
	int	i;

	pPattern=p;

	SetPos(x,y);
	MX=0;
	MY=0;
	OX=0;
	OY=0;

	nOrigin=ORG_LEFTTOP;
	nStyle =SPR_NORMAL;

	for(i=0;i<8;i++) dParam[i]=0;

	fShow=true;
}

///////////////////////////////////////////////////////////
//	�p�^�[���ݒ�
//	���l	afPattern*	afPattern�I�u�W�F�N�g�ւ̃|�C���^

void afSprite::SetPattern(afPattern *p)
{
	pPattern=p;
}

///////////////////////////////////////////////////////////
//	�\���ݒ�
//	���l	bool	true	�\��
//					false	��\��

void afSprite::SetShow(bool f)
{
	fShow=f;
}

///////////////////////////////////////////////////////////
//	�\�����@�ݒ�
//	���l	int		�\�����@
//						SPR_NORMAL		�m�[�}��
//						SPR_OPAQUE		�����F����
//						SPR_BLEND50		50%����
//						SPR_BLEND		�䗦�w�荬��
//							P1=����(0-64)
//						SPR_BLENDRGB	RGB�䗦�w�荬��
//							P1=R����(0-64)
//							P2=G����(0-64)
//							P3=B����(0-64)
//						SPR_ADD			���Z����
//						SPR_SUBTRACT	���Z����
//						SPR_STRETCH		�g��k��
//							P1=�ϊ���W
//							P2=�ϊ���H
//						SPR_ADDBRIGHT	���Z��������
//							P1=����(0 - 64)
//						SPR_SUBBRIGHT	���Z��������
//							P1=����(0 - 64)
//	(P1,P2,P3 �� afSprite::SetParam() �֐��Őݒ�)

void afSprite::SetStyle(int s)
{
	nStyle=s;
}

///////////////////////////////////////////////////////////
//	�p�����[�^�ݒ�
//	���l	int		�p�����[�^1
//			int		�p�����[�^2(�ȗ�=0)
//			int		�p�����[�^3(�ȗ�=0)
//			int		�p�����[�^4(�ȗ�=0)

void afSprite::SetParam(int a,int b,int c,int d)
{
	dParam[0]=a;
	dParam[1]=b;
	dParam[2]=c;
	dParam[3]=d;
}

///////////////////////////////////////////////////////////
//	�p�����[�^�ݒ�
//	���l	int		�C���f�b�N�X(0-7)
//			int		�p�����[�^

void afSprite::SetParam(int n,int p)
{
	dParam[n]=p;
}

///////////////////////////////////////////////////////////
//	�p�����[�^���Z
//	���l	int		�p�����[�^1
//			int		�p�����[�^2(�ȗ�=0)
//			int		�p�����[�^3(�ȗ�=0)
//			int		�p�����[�^4(�ȗ�=0)

void afSprite::AddParam(int a,int b,int c,int d)
{
	dParam[0]+=a;
	dParam[1]+=b;
	dParam[2]+=c;
	dParam[3]+=d;
}

///////////////////////////////////////////////////////////
//	�p�����[�^���Z
//	���l	int		�C���f�b�N�X
//			int		�p�����[�^

void afSprite::AddParam(int n,int p)
{
	dParam[n]+=p;
}

///////////////////////////////////////////////////////////
//	�ړ��ʐݒ�
//	���l	int		X�ړ���
//			int		Y�ړ���

void afSprite::SetMove(int x,int y)
{
	MX=x;
	MY=y;
}

///////////////////////////////////////////////////////////
//	�ړ��ʉ��Z
//	���l	int		X�ړ���
//			int		Y�ړ���

void afSprite::AddMove(int x,int y)
{
	MX+=x;
	MY+=y;
}

///////////////////////////////////////////////////////////
//	�t�����ړ��ݒ�
//	���l	bool	X�ړ��ʋt�]	false	�ێ�
//								true	�t�]
//			bool	Y�ړ��ʋt�]	false	�ێ�
//								true	�t�]

void afSprite::ReverseMove(bool fx,bool fy)
{
	MX*=(fx?-1:1);
	MY*=(fy?-1:1);
}

///////////////////////////////////////////////////////////
//	���_��ݒ�
//	���l	int		�
//						ORG_LEFTTOP			������
//						ORG_LEFTCENTER		���������
//						ORG_LEFTBOTTOM		�������
//						ORG_RIGHTTOP		�E����
//						ORG_RIGHTCENTER		�E�������
//						ORG_RIGHTBOTTM		�E�����
//						ORG_CENTERTOP		��������
//						ORG_CENTER			�������
//						ORG_CENTERBOTTOM	���������
//			int		������X���W
//			int		������Y���W

void afSprite::SetOrigin(int n,int x,int y)
{
	nOrigin=n;
	OX=x;
	OY=y;
}

///////////////////////////////////////////////////////////
//	�X�v���C�g�̍���̈ʒu���擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void	afSprite::GetPosLeftTop(int *px,int *py)
{
	int	x,y;
	int	w,h;

	if(pPattern==NULL)
	{
		GetPos(px,py);
		return;
	}

	w=pPattern->W;
	h=pPattern->H;

	switch(nOrigin)
	{
	case ORG_LEFTTOP:		x=0;		y=0;		break;
	case ORG_LEFTCENTER:	x=0;		y=(h>>1);	break;
	case ORG_LEFTBOTTOM:	x=0;		y=h;		break;
	case ORG_RIGHTTOP:		x=w;		y=0;		break;
	case ORG_RIGHTCENTER:	x=w;		y=(h>>1);	break;
	case ORG_RIGHTBOTTOM:	x=w;		y=h;		break;
	case ORG_CENTERTOP:		x=(w>>1);	y=0;		break;
	case ORG_CENTER:		x=(w>>1);	y=(h>>1);	break;
	case ORG_CENTERBOTTOM:	x=(w>>1);	y=h;		break;
	}

	if(px!=NULL) *px=X-x-OX;
	if(py!=NULL) *py=Y-y-OY;
}

///////////////////////////////////////////////////////////
//	�X�v���C�g�̍���̈ʒu���X�N���[�����W�Ŏ擾
//	���l	int*	X���W���i�[����ϐ��̃A�h���X
//			int*	Y���W���i�[����ϐ��̃A�h���X

void afSprite::GetPosLeftTopByScreen(int *px,int *py)
{
	int	gx,gy;

	GetPosLeftTop(px,py);
	GetGroupPosByScreen(&gx,&gy);

	if(px!=NULL) *px+=gx;
	if(py!=NULL) *py+=gy;
}

///////////////////////////////////////////////////////////
//	�X�v���C�g�̕\����Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	bool	true	�\��
//					false	��\��

bool afSprite::IsShow()
{
	return fShow;
}

///////////////////////////////////////////////////////////
//	�p�����[�^���擾
//	���l	int*	�p�����[�^1���i�[����ϐ��̃A�h���X
//			int*	�p�����[�^2���i�[����ϐ��̃A�h���X
//			int*	�p�����[�^3���i�[����ϐ��̃A�h���X
//			int*	�p�����[�^4���i�[����ϐ��̃A�h���X

void afSprite::GetParam(int *pa,int *pb,int *pc,int *pd)
{
	if(pa!=NULL) *pa=dParam[0];
	if(pb!=NULL) *pb=dParam[1];
	if(pc!=NULL) *pc=dParam[2];
	if(pd!=NULL) *pd=dParam[3];
}

///////////////////////////////////////////////////////////
//	�p�����[�^�擾
//	���l	int*	�p�����[�^���i�[����ϐ��̃A�h���X
//			int		�C���f�b�N�X

void afSprite::GetParam(int *p,int n)
{
	if(p!=NULL) *p=dParam[n];
}

///////////////////////////////////////////////////////////
//	�p�����[�^�擾
//	���l	�Ȃ�
//	�Ԓl	�p�����[�^�z��ւ̃|�C���^

int *afSprite::GetParam()
{
	return dParam;
}

///////////////////////////////////////////////////////////
//	�ړ��ʂ����ړ�
//	���l	�Ȃ�

void afSprite::Move()
{
	X+=MX;
	Y+=MY;
}

///////////////////////////////////////////////////////////
//	�w��ʂ������Έړ�
//	���l	int		X�ړ���
//			int		Y�ړ���

void afSprite::Move(int x,int y)
{
	X+=x;
	Y+=y;
}

///////////////////////////////////////////////////////////
//	�X�v���C�g��\��
//	���l	�Ȃ�

void afSprite::Show()
{
	afGrpGroup	*pg;
	afBitmap	*pb;

	int	dx,dy;
	int	sx,sy,sw,sh;

	int	a=dParam[0];
	int	b=dParam[1];
	int	c=dParam[2];

	if(!fShow)		   return;
	if(pPattern==NULL) return;

	pb=pPattern->pBitmap;

	if(pb==NULL) return;

	sx=pPattern->X;
	sy=pPattern->Y;
	sw=pPattern->W;
	sh=pPattern->H;

	GetPosLeftTop(&dx,&dy);

	pg=pb->SetGroup(pGroup);
	switch(nStyle)
	{
	case SPR_NORMAL:   pb->Put      (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_BLEND50:  pb->Blend    (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_BLEND:	   pb->Blend    (dx,dy,a    ,sx,sy,sw,sh);break;
	case SPR_BLENDRGB: pb->Blend    (dx,dy,a,b,c,sx,sy,sw,sh);break;
	case SPR_ADD:	   pb->Add      (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_SUBTRACT: pb->Subtract (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_STRETCH:  pb->Stretch  (dx,dy,a,b  ,sx,sy,sw,sh);break;
	case SPR_OPAQUE:   pb->Opaque   (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_ADDBRIGHT:pb->AddBright(dx,dy,a    ,sx,sy,sw,sh);break;
	case SPR_SUBBRIGHT:pb->SubBright(dx,dy,a    ,sx,sy,sw,sh);break;
	case SPR_MULTIPLY: pb->Multiply (dx,dy      ,sx,sy,sw,sh);break;
	}
	pb->SetGroup(pg);
}
