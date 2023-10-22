//
//	AFL Screen Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afScreen
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"
#include "aflcore.h"
#include "afldialog.h"

///////////////////////////////////////////////////////////
//	�ÓI�N���X�ϐ���`

int afScreen::ScrnW=0;
int afScreen::ScrnH=0;

LPDIRECTDRAWSURFACE afScreen::pWork=NULL;

///////////////////////////////////////////////////////////
//	�X�N���[���I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afScreen::afScreen()
{
}

///////////////////////////////////////////////////////////
//	��ʂ��쐬
//	���l	int		��
//			int		����
//	�v���O������2��ȏ�Ă΂Ȃ��ł�������

bool afScreen::CreateScreen(int w,int h)
{
	ScrnW=w;
	ScrnH=h;

	if(!_coreGraphics::InitGraphics(w,h)) return false;
	pWork=_coreGraphics::pDDSBack;

	return true;
}

///////////////////////////////////////////////////////////
//	�t���J���[�̉�ʂ��쐬
//	���l	int		��
//			int		����
//	�v���O������2��ȏ�Ă΂Ȃ��ł�������

bool afScreen::CreateFullColorScreen(int w,int h)
{
	ScrnW=w;
	ScrnH=h;

	_coreGraphics::PixelSize=3;
	if(!_coreGraphics::InitGraphics(w,h)) return false;
	pWork=_coreGraphics::pDDSBack;

	return true;
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�̕\���\�͈͂���ʃT�C�Y�ɐݒ�
//	���l	�Ȃ�

void afScreen::SetDrawArea()
{
	_coreGraphics::SetDrawArea(0,0,ScrnW,ScrnH);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�̕\���\�͈͂�ݒ�
//	���l	int		����X���W
//			int		����Y���W
//			int		�E��X���W
//			int		�E��Y���W

void afScreen::SetDrawArea(int x1,int y1,int x2,int y2)
{
	_coreGraphics::SetDrawArea(x1,y1,x2,y2);
}

///////////////////////////////////////////////////////////
//	��ʃT�C�Y�擾
//	���l	int*	�����i�[����ϐ��ւ̃|�C���^
//			int*	�������i�[����ϐ��ւ̃|�C���^

void afScreen::GetScreenSize(int *w,int *h)
{
	if(w!=NULL) *w=ScrnW;
	if(h!=NULL) *h=ScrnH;
}

///////////////////////////////////////////////////////////
//	�s�N�Z���t�H�[�}�b�g���擾
//	���l	AFPIXELFORMAT*	�f�[�^���i�[����AFPIXELFORMAT�\���̂�
//							�A�h���X

void afScreen::GetPixelFormat(AFPIXELFORMAT *pf)
{
	pf->ShiftR=_coreGraphics::ShiftR;
	pf->ShiftG=_coreGraphics::ShiftG;
	pf->ShiftB=_coreGraphics::ShiftB;

	pf->BitCountR  =_coreGraphics::BitCountR;
	pf->BitCountG  =_coreGraphics::BitCountG;
	pf->BitCountB  =_coreGraphics::BitCountB;
	pf->BitCountRGB=_coreGraphics::BitCountRGB;

	pf->BitR=_coreGraphics::BitR;
	pf->BitG=_coreGraphics::BitG;
	pf->BitB=_coreGraphics::BitB;

	pf->MaskR  =_coreGraphics::MaskR;
	pf->MaskG  =_coreGraphics::MaskG;
	pf->MaskB  =_coreGraphics::MaskB;
	pf->MaskRGB=_coreGraphics::MaskRGB;
}

///////////////////////////////////////////////////////////
//	�o�b�N�o�b�t�@��DC���擾
//	���l	afDC*	DC���i�[����afDC�I�u�W�F�N�g�̃A�h���X

void afScreen::GetDC(afDC *pdc)
{
	_coreGraphics::pDDSBack->GetDC(&(pdc->hDC));
}

///////////////////////////////////////////////////////////
//	�o�b�N�o�b�t�@��DC�����
//	���l	afDC*	DC���i�[����afDC�I�u�W�F�N�g�ւ̃|�C���^

void afScreen::ReleaseDC(afDC *pdc)
{
	_coreGraphics::pDDSBack->ReleaseDC(pdc->hDC);
}

///////////////////////////////////////////////////////////
//	�o�b�N�o�b�t�@�����b�N����
//	���l	afPixelData*	�s�N�Z���f�[�^���i�[����ϐ��̃A�h���X

void afScreen::Lock(afPixelData *pPD)
{
	DDSURFACEDESC	ddsd;
	WORD	d;

	ddsd.dwSize=sizeof(DDSURFACEDESC);
	_coreGraphics::pDDSBack->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);

	pPD->pPixel=(WORD*)ddsd.lpSurface;
	pPD->Pitch =ddsd.lPitch/2;

	//	DirectDraw�L���b�V��(?)���Z�b�g
	d=*(pPD->pPixel);
	d=*(pPD->pPixel+1);
}

///////////////////////////////////////////////////////////
//	�o�b�N�o�b�t�@�̃��b�N����������
//	���l	afPixelData*	�s�N�Z���f�[�^���i�[�����ϐ��ւ̃|�C���^

void afScreen::Unlock(afPixelData *pPD)
{
	_coreGraphics::pDDSBack->Unlock(pPD->pPixel);
}

///////////////////////////////////////////////////////////
//	�o�b�N�o�b�t�@�̃T�[�t�F�X���擾
//	���l	�Ȃ�
//	�Ԓl	LPDIRECTDRAWSURFACE	�T�[�t�F�X�ւ̃|�C���^

LPDIRECTDRAWSURFACE afScreen::GetDDBackSurface()
{
	return _coreGraphics::pDDSBack;
}

///////////////////////////////////////////////////////////
//	��ƃX�N���[����ݒ�
//	���l	afBitmap*	�r�b�g�}�b�v�ւ̃|�C���^
//	����	�g�p���RestoreWorkScreen()�֐����Ă�ł�������

void afScreen::SetWorkScreen(afBitmap *bmp)
{
	_coreGraphics::pDDSBack=bmp->GetDDSurface();
}

///////////////////////////////////////////////////////////
//	��ƃX�N���[���𕜋�����
//	���l	�Ȃ�

void afScreen::RestoreWorkScreen()
{
	_coreGraphics::pDDSBack=pWork;
}

///////////////////////////////////////////////////////////
//	�S��ʂ�����
//	���l	�Ȃ�

void afScreen::Clear()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0;

	_coreGraphics::pDDSBack->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	�w��͈͂�����
//	���l	int		����X���W
//			int		����Y���W
//			int		�E��X���W
//			int		�E��Y���W

void afScreen::Clear(int x1,int y1,int x2,int y2)
{
	DDBLTFX	col;
	RECT	r;

	r.left	=x1;
	r.top	=y1;
	r.right	=x2;
	r.bottom=y2;

	col.dwSize=sizeof(col);
	col.dwFillColor=0;

	_coreGraphics::pDDSBack->Blt(&r,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	��ʂ𔒂őS����
//	���l	�Ȃ�

void afScreen::ClearWhite()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0x0000FFFF;

	_coreGraphics::pDDSBack->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	��ʂ��X�V
//	���l	�Ȃ�

void afScreen::Refresh()
{
	LPDIRECTDRAWSURFACE	f=_coreGraphics::pDDSFront;
	LPDIRECTDRAWSURFACE	b=_coreGraphics::pDDSBack;
	RECT	rc;

	rc.left		=0;
	rc.top		=0;
	rc.right	=ScrnW;
	rc.bottom	=ScrnH;

	f->Blt(&rc,b,&rc,DDBLT_WAIT,NULL);
}

///////////////////////////////////////////////////////////
//	fps��\��
//	���l	�Ȃ�

void afScreen::ShowFPS()
{
	static int		c=0;
	static int		fps=0;
	static DWORD	start=0;

	char	buf[64];
	HDC		hDC;

	if(start+1000<=GetTickCount())
	{
		start=GetTickCount();
		fps=c;
		c=0;
	}
	else
	{
		c++;
	}

	sprintf(buf,"%04d [frame/sec]",fps);
	_coreGraphics::pDDSBack->GetDC(&hDC);
	TextOut(hDC,0,0,buf,strlen(buf));
	_coreGraphics::pDDSBack->ReleaseDC(hDC);
}
