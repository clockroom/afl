//
//	AFL DC Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	(afGrpObject)
//		afDC
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	DC�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afDC::afDC()
{
	hDC=NULL;
}

///////////////////////////////////////////////////////////
//	�N���b�p�[��S��ʂɐݒ�
//	���l	�Ȃ�

void afDC::SetClipper()
{
	SelectClipRgn(hDC,NULL);
}

///////////////////////////////////////////////////////////
//	�N���b�p�[��ݒ�
//	���l	int		����X���W
//			int		����Y���W
//			int		�E��X���W
//			int		�E��Y���W

void afDC::SetClipper(int x1,int y1,int x2,int y2)
{
	HRGN	hrgn;

	hrgn=CreateRectRgn(x1,y1,x2,y2);
	SelectClipRgn(hDC,hrgn);
}

///////////////////////////////////////////////////////////
//	�w����W�̐F���擾 (afScreen�ɂ͎g�p�s��)
//	���l	int			X���W
//			int			Y���W
//	�Ԓl	COLORREF	�F

COLORREF afDC::GetPixel(int x,int y)
{
	int	gx,gy;
	COLORREF	c;

	GetGroupPosByScreen(&gx,&gy);
	c=::GetPixel(hDC,gx+x,gy+y);

	return	c;
}

///////////////////////////////////////////////////////////
//	�w����W�ɓ_��\��
//	���l	int			X���W
//			int			Y���W
//			COLORREF	�F

void afDC::Pixel(int x,int y,COLORREF c)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	c=::SetPixel(hDC,gx+x,gy+y,c);
}

///////////////////////////////////////////////////////////
//	�������\��
//	���l	int			X���W
//			int			Y���W
//			char*		������ւ̃|�C���^
//			int			�����T�C�Y
//			bool		����(true=���� or false=�W��)
//			COLORREF	�����F

void afDC::Text(int x,int y,const char *str,int size,bool bold,COLORREF col)
{
	int		gx,gy;
	HFONT	hofont,hnfont;
	LOGFONT	lf;

	ZeroMemory(&lf,sizeof(LOGFONT));
	lf.lfHeight=size;
	lf.lfWidth=0;
	lf.lfCharSet=SHIFTJIS_CHARSET;
	strcpy(lf.lfFaceName,"�W���S�V�b�N");

	hnfont=CreateFontIndirect(&lf);
	hofont=(HFONT)SelectObject(hDC,hnfont);

	SetBkMode(hDC,TRANSPARENT);
	SetTextColor(hDC,col);
	GetGroupPosByScreen(&gx,&gy);

	TextOut(hDC,gx+x,gy+y,str,strlen(str));
	if(bold) TextOut(hDC,gx+x+1,gy+y,str,strlen(str));

	SelectObject(hDC,hofont);
	DeleteObject(hnfont);
}

///////////////////////////////////////////////////////////
//	�������\��(�e�t��)
//	���l	int			X���W
//			int			Y���W
//			char*		������ւ̃|�C���^
//			int			�����T�C�Y
//			bool		����(true=���� or false=�W��)
//			COLORREF	�����F
//			COLORREF	�e�F

void afDC::Text(int x,int y,const char *str,int size,bool bold,COLORREF col,COLORREF shc)
{
	int		gx,gy;
	HFONT	hofont,hnfont;
	LOGFONT	lf;

	ZeroMemory(&lf,sizeof(LOGFONT));
	lf.lfHeight=size;
	lf.lfWidth=0;
	lf.lfCharSet=SHIFTJIS_CHARSET;
	strcpy(lf.lfFaceName,"�W���S�V�b�N");

	hnfont=CreateFontIndirect(&lf);
	hofont=(HFONT)SelectObject(hDC,hnfont);

	SetBkMode(hDC,TRANSPARENT);
	GetGroupPosByScreen(&gx,&gy);

	SetTextColor(hDC,shc);
	TextOut(hDC,gx+x+1,gy+y+1,str,strlen(str));
	if(bold) TextOut(hDC,gx+x+2,gy+y+1,str,strlen(str));

	SetTextColor(hDC,col);
	TextOut(hDC,gx+x,gy+y,str,strlen(str));
	if(bold) TextOut(hDC,gx+x+1,gy+y,str,strlen(str));

	SelectObject(hDC,hofont);
	DeleteObject(hnfont);
}

///////////////////////////////////////////////////////////
//	������\��
//	���l	int			�J�nX���W
//			int			�J�nY���W
//			int			�I��X���W
//			int			�I��Y���W
//			int			���̑���
//			COLORREF	���̐F

void afDC::Line(int x1,int y1,int x2,int y2,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;

	hnpen=CreatePen(PS_SOLID,size,col);
	hopen=(HPEN)SelectObject(hDC,hnpen);

	GetGroupPosByScreen(&gx,&gy);
	MoveToEx(hDC,gx+x1,gy+y1,NULL);
	LineTo(hDC,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	DeleteObject(hnpen);
}

///////////////////////////////////////////////////////////
//	�~��\��
//	���l	int			����X���W
//			int			����Y���W
//			int			�E��X���W
//			int			�E��Y���W
//			int			���̑���
//			COLORREF	���̐F

void afDC::Circle(int x1,int y1,int x2,int y2,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=(HBRUSH)GetStockObject(NULL_BRUSH);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Ellipse(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	�~��\��
//	���l	int			����X���W
//			int			����Y���W
//			int			�E��X���W
//			int			�E��Y���W
//			int			���̑���
//			COLORREF	���̐F
//			COLORREF	���h��̐F

void afDC::Circle(int x1,int y1,int x2,int y2,int size,COLORREF col,COLORREF fill)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=CreateSolidBrush(fill);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Ellipse(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	�l�p�`��\��
//	���l	int			����X���W
//			int			����Y���W
//			int			�E��X���W
//			int			�E��Y���W
//			int			���̑���
//			COLORREF	���̐F

void afDC::Box(int x1,int y1,int x2,int y2,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=(HBRUSH)GetStockObject(NULL_BRUSH);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Rectangle(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	�l�p�`��\��
//	���l	int			����X���W
//			int			����Y���W
//			int			�E��X���W
//			int			�E��Y���W
//			int			���̑���
//			COLORREF	���̐F
//			COLORREF	���h��̐F

void afDC::Box(int x1,int y1,int x2,int y2,int size,COLORREF col,COLORREF fill)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=CreateSolidBrush(fill);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Rectangle(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	�O�p�`��\��
//	���l	int			��1X���W
//			int			��1Y���W
//			int			��2X���W
//			int			��2Y���W
//			int			��3X���W
//			int			��3Y���W
//			int			���̑���
//			COLORREF	���̐F

void afDC::Triangle(int x1,int y1,int x2,int y2,int x3,int y3,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;
	POINT	dpt[3];

	if(x1==y1 && x1==x2 && x1==y2 && x1==x3 && x1==y3)
	{
		Pixel(x1,y1,col);
		return;
	}

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=(HBRUSH)GetStockObject(NULL_BRUSH);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	dpt[0].x=gx+x1;
	dpt[0].y=gy+y1;
	dpt[1].x=gx+x2;
	dpt[1].y=gy+y2;
	dpt[2].x=gx+x3;
	dpt[2].y=gy+y3;
	Polygon(hDC,dpt,3);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	�O�p�`��\��
//	���l	int			��1X���W
//			int			��1Y���W
//			int			��2X���W
//			int			��2Y���W
//			int			��3X���W
//			int			��3Y���W
//			int			���̑���
//			COLORREF	���̐F
//			COLORREF	���h��̐F

void afDC::Triangle(int x1,int y1,int x2,int y2,int x3,int y3,int size,COLORREF col,COLORREF fill)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;
	POINT	dpt[3];

	if(x1==y1 && x1==x2 && x1==y2 && x1==x3 && x1==y3)
	{
		Pixel(x1,y1,col);
		return;
	}

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=CreateSolidBrush(fill);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	dpt[0].x=gx+x1;
	dpt[0].y=gy+y1;
	dpt[1].x=gx+x2;
	dpt[1].y=gy+y2;
	dpt[2].x=gx+x3;
	dpt[2].y=gy+y3;
	Polygon(hDC,dpt,3);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	(HDC)�ϊ����Z�q
//	���l	�Ȃ�

afDC::operator HDC()
{
	return	hDC;
}
