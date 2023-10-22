//
//	AFL Bitmap Class by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//
//	(afGrpObject)
//		afBitmap
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflgraphics.h"
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afBitmap::afBitmap()
{
	nBitmap=NULL;
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�I�u�W�F�N�g�j��
//	���l	�Ȃ�

afBitmap::~afBitmap()
{
	ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	��r�b�g�}�b�v��RAM�ɍ쐬
//	���l	int		��
//			int		����

void afBitmap::CreateBitmap(int w,int h)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::CreateBitmap(w,h,false);
	ClearBitmap();
}

///////////////////////////////////////////////////////////
//	��r�b�g�}�b�v���쐬
//	���l	int		��
//			int		����
//			bool	false	RAM
//					true	VRAM or RAM

void afBitmap::CreateBitmap(int w,int h,bool f)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::CreateBitmap(w,h,f);
	ClearBitmap();
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��RAM�Ƀ��[�h
//	���l	char*	�t�@�C����

void afBitmap::LoadBitmap(const char *ps)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::LoadBitmap(ps,false);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����[�h
//	���l	char*	�t�@�C����
//			bool	false	RAM
//					true	VRAM or RAM

void afBitmap::LoadBitmap(const char *ps,bool f)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::LoadBitmap(ps,f);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����
//	���l	�Ȃ�

void afBitmap::ReleaseBitmap()
{
	if(nBitmap==NULL) return;
	_coreGraphics::ReleaseBitmap(nBitmap);
	nBitmap=NULL;
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����ŏ���
//	���l	�Ȃ�

void afBitmap::ClearBitmap()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0;

	_coreGraphics::dBitmap[nBitmap].pDDSurface->
		Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�𔒂ŏ���
//	���l	�Ȃ�

void afBitmap::ClearWhiteBitmap()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0x0000FFFF;

	_coreGraphics::dBitmap[nBitmap].pDDSurface->
		Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	��ʂ̃r�b�g�}�b�v���o�b�t�@�ɓ]��
//	���l	int		X���W
//			int		Y���W
//			int		��
//			int		����

void afBitmap::ClipScreen(int x,int y,int w,int h)
{
	RECT	r1,r2;

	r1.left		=0;
	r1.top		=0;
	r1.right	=w;
	r1.bottom	=h;

	r2.left		=x;
	r2.top		=y;
	r2.right	=x+w;
	r2.bottom	=y+h;

	_coreGraphics::dBitmap[nBitmap].pDDSurface->
		Blt(&r1,_coreGraphics::pDDSBack,&r2,DDBLT_WAIT,NULL);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�̍���𓧖��F�ɐݒ�
//	���l	����

void afBitmap::SetColorKey()
{
	_coreGraphics::SetColorKey(nBitmap);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�̓����F��ݒ�
//	���l	COLORREF	�����F(RGB(��,��,��))

void afBitmap::SetColorKey(COLORREF col)
{
	_coreGraphics::SetColorKey(nBitmap,col);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�̃T�[�t�F�X���擾
//	���l	�Ȃ�
//	�Ԓl	LPDIRECTDRAWSURFACE	�T�[�t�F�X�ւ̃|�C���^

LPDIRECTDRAWSURFACE afBitmap::GetDDSurface()
{
	return	_coreGraphics::dBitmap[nBitmap].pDDSurface;
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v���������Ă��邩�ǂ������擾
//	���l	�Ȃ�

bool afBitmap::IsLost()
{
	bool f=_coreGraphics::dBitmap[nBitmap].fLost;

	_coreGraphics::dBitmap[nBitmap].fLost=false;
	return f;
}

///////////////////////////////////////////////////////////
//	�f�o�C�X�R���e�L�X�g���擾
//	���l	afDC*	DC���i�[����afDC�I�u�W�F�g�̃A�h���X

void afBitmap::GetDC(afDC *pdc)
{
	_coreGraphics::dBitmap[nBitmap].pDDSurface->GetDC(&(pdc->hDC));
}

///////////////////////////////////////////////////////////
//	�f�o�C�X�R���e�L�X�g�����
//	���l	afDC	DC���i�[����afDC�I�u�W�F�N�g�ւ̃|�C���^

void afBitmap::ReleaseDC(afDC *pdc)
{
	_coreGraphics::dBitmap[nBitmap].pDDSurface->ReleaseDC(pdc->hDC);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����b�N����
//	���l	afPixelData*	�s�N�Z���f�[�^���i�[����ϐ��̃A�h���X

void afBitmap::Lock(afPixelData *pPD)
{
	DDSURFACEDESC	ddsd;
	WORD	d;

	ddsd.dwSize=sizeof(DDSURFACEDESC);
	_coreGraphics::dBitmap[nBitmap].pDDSurface->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);

	pPD->pPixel=(WORD*)ddsd.lpSurface;
	pPD->Pitch =ddsd.lPitch/2;

	//	DirectDraw�L���b�V��(?)���Z�b�g
	d=*(pPD->pPixel);
	d=*(pPD->pPixel+1);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�̃��b�N����������
//	���l	afPixelData*	�s�N�Z���f�[�^���i�[�����ϐ��ւ̃|�C���^

void afBitmap::Unlock(afPixelData *pPD)
{
	_coreGraphics::dBitmap[nBitmap].pDDSurface->Unlock(pPD->pPixel);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�̕\��
//	���l	int		X���W
//			int		Y���W
//			int		�f�[�^�ł�X���W
//			int		�f�[�^�ł�Y���W
//			int		��
//			int		����

void afBitmap::Put(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Put(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v���w��̃T�[�t�F�X�ɕ\��
//	���l	afBitmap*	�T�[�t�F�X�I�u�W�F�N�g�ւ̃|�C���^
//			int			X���W
//			int			Y���W
//			int			�f�[�^��X���W
//			int			�f�[�^��Y���W
//			int			��
//			int			����

void afBitmap::Put(afBitmap *bmp,int dx,int dy,int sx,int sy,int sw,int sh)
{
	LPDIRECTDRAWSURFACE	ddsfc1;
	LPDIRECTDRAWSURFACE	ddsfc2;
	RECT	rect1,rect2;

	//	�T�[�t�F�X�ݒ�
	ddsfc1=_coreGraphics::dBitmap[bmp->nBitmap].pDDSurface;
	ddsfc2=_coreGraphics::dBitmap[nBitmap].pDDSurface;

	//	���W�ݒ�
	rect1.left	=dx;
	rect1.top	=dy;
	rect1.right	=dx+sw;
	rect1.bottom=dy+sh;

	rect2.left	=sx;
	rect2.top	=sy;
	rect2.right	=sx+sw;
	rect2.bottom=sy+sh;

	//	�\��
	ddsfc1->Blt(&rect1,ddsfc2,&rect2,DDBLT_KEYSRC|DDBLT_WAIT,NULL);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�𓧖��F�𖳎����ĕ\��
//	���l	int		X���W
//			int		Y���W
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Opaque(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Opaque(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v���w��̃r�b�g�}�b�v�ɓ����F�𖳎����ĕ\��
//	���l	afBitmap*	�T�[�t�F�X�I�u�W�F�N�g�ւ̃|�C���^
//			int			X���W
//			int			Y���W
//			int			�f�[�^��X���W
//			int			�f�[�^��Y���W
//			int			��
//			int			����

void afBitmap::Opaque(afBitmap *bmp,int dx,int dy,int sx,int sy,int sw,int sh)
{
	LPDIRECTDRAWSURFACE	ddsfc1;
	LPDIRECTDRAWSURFACE	ddsfc2;
	RECT	rect1,rect2;

	//	�T�[�t�F�X�ݒ�
	ddsfc1=_coreGraphics::dBitmap[bmp->nBitmap].pDDSurface;
	ddsfc2=_coreGraphics::dBitmap[nBitmap].pDDSurface;

	//	���W�ݒ�
	rect1.left	=dx;
	rect1.top	=dy;
	rect1.right	=dx+sw;
	rect1.bottom=dy+sh;

	rect2.left	=sx;
	rect2.top	=sy;
	rect2.right	=sx+sw;
	rect2.bottom=sy+sh;

	//	�\��
	ddsfc1->Blt(&rect1,ddsfc2,&rect2,DDBLT_WAIT,NULL);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��50%�����\��
//	���l	int		X���W
//			int		Y���W
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Blend(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;
	int	w;

	GetGroupPosByScreen(&gx,&gy);

	w=sw;
	if(gx+dx+sw>_coreGraphics::AreaX2) w=_coreGraphics::AreaX2-(gx+dx);
	if(gx+dx<_coreGraphics::AreaX1)    w=sw-(_coreGraphics::AreaX1-(gx+dx));
	if(w<=0) return;

	if(w%2==0) _coreGraphics::BlendB(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
	else	   _coreGraphics::BlendA(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��䗦�w��ō����\��
//	���l	int		X���W
//			int		Y���W
//			int		����(0 - 32)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Blend(int dx,int dy,int p,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(p<= 0) return;
	if(p==16)
	{
		Blend(dx,dy,sx,sy,sw,sh);
		return;
	}
	if(p>=32)
	{
		Put(dx,dy,sx,sy,sw,sh);
		return;
	}

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Blend(gx+dx,gy+dy,p,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��RGB�䗦�w��ō����\��
//	���l	int		X���W
//			int		Y���W
//			int		R����(0 - 32)
//			int		G����(0 - 32)
//			int		B����(0 - 32)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Blend(int dx,int dy,int r,int g,int b,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(r<= 0 && g<= 0 && b<= 0)	return;
	if(r>=32 && g>=32 && b>=32)
	{
		Put(dx,dy,sx,sy,sw,sh);
		return;
	}

	if(r< 0) r=0;
	if(g< 0) g=0;
	if(b< 0) b=0;
	if(r>32) r=32;
	if(g>32) g=32;
	if(b>32) b=32;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Blend(gx+dx,gy+dy,r,g,b,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����Z�����\��
//	���l	int		X���W
//			int		Y���W
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Add(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Add(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����Z���������\��
//	���l	int		X���W
//			int		Y���W
//			int		���x(0 - 32)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::AddBright(int dx,int dy,int p,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(p<= 0) return;
	if(p>=32)
	{
		Add(dx,dy,sx,sy,sw,sh);
		return;
	}

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::AddBright(gx+dx,gy+dy,p,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����Z�����\��
//	���l	int		X���W
//			int		Y���W
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Subtract(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Subtract(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�����Z���������\��
//	���l	int		X���W
//			int		Y���W
//			int		���x(0 - 32)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::SubBright(int dx,int dy,int p,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(p<= 0) return;
	if(p>=32)
	{
		Subtract(dx,dy,sx,sy,sw,sh);
		return;
	}

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::SubBright(gx+dx,gy+dy,p,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v����Z�����\��
//	���l	int		X���W
//			int		Y���W
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Multiply(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Multiply(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��䗦�w��Œ����\��
//	���l	int		X���W
//			int		Y���W
//			int		���x(0 - 32 - 64)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Bright(int dx,int dy,int p,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(p==32)
	{
		Put(dx,dy,sx,sy,sw,sh);
		return;
	}

	if(p< 0) p= 0;
	if(p>64) p=64;

	GetGroupPosByScreen(&gx,&gy);
	if(p<32) _coreGraphics::BrightA(gx+dx,gx+dy,p   ,nBitmap,sx,sy,sw,sh);
	else	 _coreGraphics::BrightB(gx+dx,gy+dy,p-32,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��RGB�䗦�w��Œ����\��
//	���l	int		X���W
//			int		Y���W
//			int		R���x(0 - 32 - 64)
//			int		G���x(0 - 32 - 64)
//			int		B���x(0 - 32 - 64)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::Bright(int dx,int dy,int r,int g,int b,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(r==32 && g==32 && b==32)
	{
		Put(dx,dy,sx,sy,sw,sh);
		return;
	}

	if(r< 0) r= 0;
	if(g< 0) g= 0;
	if(b< 0) b= 0;
	if(r>64) r=64;
	if(g>64) g=64;
	if(b>64) b=64;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Bright(gx+dx,gy+dy,r,g,b,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��䗦�w��ŕs���������\��
//	���l	int		X���W
//			int		Y���W
//			int		���x(0 - 32 - 64)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::BrightOpaque(int dx,int dy,int p,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(p==32)
	{
		Opaque(dx,dy,sx,sy,sw,sh);
		return;
	}

	if(p< 0) p= 0;
	if(p>64) p=64;

	GetGroupPosByScreen(&gx,&gy);
	if(p<32) _coreGraphics::BrightOpaqueA(gx+dx,gy+dy,p   ,nBitmap,sx,sy,sw,sh);
	else	 _coreGraphics::BrightOpaqueB(gx+dx,gy+dy,p-32,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v��RGB�䗦�w��ŕs���������\��
//	���l	int		X���W
//			int		Y���W
//			int		R���x(0 - 32 - 64)
//			int		G���x(0 - 32 - 64)
//			int		B���x(0 - 32 - 64)
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		��
//			int		����

void afBitmap::BrightOpaque(int dx,int dy,int r,int g,int b,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	if(r==32 && g==32 && b==32)
	{
		Put(dx,dy,sx,sy,sw,sh);
		return;
	}

	if(r< 0) r= 0;
	if(g< 0) g= 0;
	if(b< 0) b= 0;
	if(r>64) r=64;
	if(g>64) g=64;
	if(b>64) b=64;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::BrightOpaque(gx+dx,gy+dy,r,g,b,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v���g��k���\��
//	���l	int		X���W
//			int		Y���W
//			int		��
//			int		����
//			int		�f�[�^��X���W
//			int		�f�[�^��Y���W
//			int		�f�[�^�̕�
//			int		�f�[�^�̍���

void afBitmap::Stretch(int dx,int dy,int dw,int dh,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Stretch(gx+dx,gy+dy,dw,dh,nBitmap,sx,sy,sw,sh);
}
