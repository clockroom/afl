//
//	AFL Bitmap Class by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//
//	(afGrpObject)
//		afBitmap
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	ビットマップオブジェクト構築
//	引値	なし

afBitmap::afBitmap()
{
	nBitmap=NULL;
}

///////////////////////////////////////////////////////////
//	ビットマップオブジェクト破棄
//	引値	なし

afBitmap::~afBitmap()
{
	ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	空ビットマップをRAMに作成
//	引値	int		幅
//			int		高さ

void afBitmap::CreateBitmap(int w,int h)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::CreateBitmap(w,h,false);
	ClearBitmap();
}

///////////////////////////////////////////////////////////
//	空ビットマップを作成
//	引値	int		幅
//			int		高さ
//			bool	false	RAM
//					true	VRAM or RAM

void afBitmap::CreateBitmap(int w,int h,bool f)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::CreateBitmap(w,h,f);
	ClearBitmap();
}

///////////////////////////////////////////////////////////
//	ビットマップをRAMにロード
//	引値	char*	ファイル名

void afBitmap::LoadBitmap(const char *ps)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::LoadBitmap(ps,false);
}

///////////////////////////////////////////////////////////
//	ビットマップをロード
//	引値	char*	ファイル名
//			bool	false	RAM
//					true	VRAM or RAM

void afBitmap::LoadBitmap(const char *ps,bool f)
{
	ReleaseBitmap();
	nBitmap=_coreGraphics::LoadBitmap(ps,f);
}

///////////////////////////////////////////////////////////
//	ビットマップを解放
//	引値	なし

void afBitmap::ReleaseBitmap()
{
	if(nBitmap==NULL) return;
	_coreGraphics::ReleaseBitmap(nBitmap);
	nBitmap=NULL;
}

///////////////////////////////////////////////////////////
//	ビットマップを黒で消去
//	引値	なし

void afBitmap::ClearBitmap()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0;

	_coreGraphics::dBitmap[nBitmap].pDDSurface->
		Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	ビットマップを白で消去
//	引値	なし

void afBitmap::ClearWhiteBitmap()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0x0000FFFF;

	_coreGraphics::dBitmap[nBitmap].pDDSurface->
		Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	画面のビットマップをバッファに転送
//	引値	int		X座標
//			int		Y座標
//			int		幅
//			int		高さ

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
//	ビットマップの左上を透明色に設定
//	引値	無し

void afBitmap::SetColorKey()
{
	_coreGraphics::SetColorKey(nBitmap);
}

///////////////////////////////////////////////////////////
//	ビットマップの透明色を設定
//	引値	COLORREF	透明色(RGB(赤,緑,青))

void afBitmap::SetColorKey(COLORREF col)
{
	_coreGraphics::SetColorKey(nBitmap,col);
}

///////////////////////////////////////////////////////////
//	ビットマップのサーフェスを取得
//	引値	なし
//	返値	LPDIRECTDRAWSURFACE	サーフェスへのポインタ

LPDIRECTDRAWSURFACE afBitmap::GetDDSurface()
{
	return	_coreGraphics::dBitmap[nBitmap].pDDSurface;
}

///////////////////////////////////////////////////////////
//	ビットマップが損失しているかどうかを取得
//	引値	なし

bool afBitmap::IsLost()
{
	bool f=_coreGraphics::dBitmap[nBitmap].fLost;

	_coreGraphics::dBitmap[nBitmap].fLost=false;
	return f;
}

///////////////////////////////////////////////////////////
//	デバイスコンテキストを取得
//	引値	afDC*	DCを格納するafDCオブジェトのアドレス

void afBitmap::GetDC(afDC *pdc)
{
	_coreGraphics::dBitmap[nBitmap].pDDSurface->GetDC(&(pdc->hDC));
}

///////////////////////////////////////////////////////////
//	デバイスコンテキストを解放
//	引値	afDC	DCを格納したafDCオブジェクトへのポインタ

void afBitmap::ReleaseDC(afDC *pdc)
{
	_coreGraphics::dBitmap[nBitmap].pDDSurface->ReleaseDC(pdc->hDC);
}

///////////////////////////////////////////////////////////
//	ビットマップをロックする
//	引値	afPixelData*	ピクセルデータを格納する変数のアドレス

void afBitmap::Lock(afPixelData *pPD)
{
	DDSURFACEDESC	ddsd;
	WORD	d;

	ddsd.dwSize=sizeof(DDSURFACEDESC);
	_coreGraphics::dBitmap[nBitmap].pDDSurface->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);

	pPD->pPixel=(WORD*)ddsd.lpSurface;
	pPD->Pitch =ddsd.lPitch/2;

	//	DirectDrawキャッシュ(?)リセット
	d=*(pPD->pPixel);
	d=*(pPD->pPixel+1);
}

///////////////////////////////////////////////////////////
//	ビットマップのロックを解除する
//	引値	afPixelData*	ピクセルデータを格納した変数へのポインタ

void afBitmap::Unlock(afPixelData *pPD)
{
	_coreGraphics::dBitmap[nBitmap].pDDSurface->Unlock(pPD->pPixel);
}

///////////////////////////////////////////////////////////
//	ビットマップの表示
//	引値	int		X座標
//			int		Y座標
//			int		データでのX座標
//			int		データでのY座標
//			int		幅
//			int		高さ

void afBitmap::Put(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Put(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	ビットマップを指定のサーフェスに表示
//	引値	afBitmap*	サーフェスオブジェクトへのポインタ
//			int			X座標
//			int			Y座標
//			int			データのX座標
//			int			データのY座標
//			int			幅
//			int			高さ

void afBitmap::Put(afBitmap *bmp,int dx,int dy,int sx,int sy,int sw,int sh)
{
	LPDIRECTDRAWSURFACE	ddsfc1;
	LPDIRECTDRAWSURFACE	ddsfc2;
	RECT	rect1,rect2;

	//	サーフェス設定
	ddsfc1=_coreGraphics::dBitmap[bmp->nBitmap].pDDSurface;
	ddsfc2=_coreGraphics::dBitmap[nBitmap].pDDSurface;

	//	座標設定
	rect1.left	=dx;
	rect1.top	=dy;
	rect1.right	=dx+sw;
	rect1.bottom=dy+sh;

	rect2.left	=sx;
	rect2.top	=sy;
	rect2.right	=sx+sw;
	rect2.bottom=sy+sh;

	//	表示
	ddsfc1->Blt(&rect1,ddsfc2,&rect2,DDBLT_KEYSRC|DDBLT_WAIT,NULL);
}

///////////////////////////////////////////////////////////
//	ビットマップを透明色を無視して表示
//	引値	int		X座標
//			int		Y座標
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

void afBitmap::Opaque(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Opaque(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	ビットマップを指定のビットマップに透明色を無視して表示
//	引値	afBitmap*	サーフェスオブジェクトへのポインタ
//			int			X座標
//			int			Y座標
//			int			データのX座標
//			int			データのY座標
//			int			幅
//			int			高さ

void afBitmap::Opaque(afBitmap *bmp,int dx,int dy,int sx,int sy,int sw,int sh)
{
	LPDIRECTDRAWSURFACE	ddsfc1;
	LPDIRECTDRAWSURFACE	ddsfc2;
	RECT	rect1,rect2;

	//	サーフェス設定
	ddsfc1=_coreGraphics::dBitmap[bmp->nBitmap].pDDSurface;
	ddsfc2=_coreGraphics::dBitmap[nBitmap].pDDSurface;

	//	座標設定
	rect1.left	=dx;
	rect1.top	=dy;
	rect1.right	=dx+sw;
	rect1.bottom=dy+sh;

	rect2.left	=sx;
	rect2.top	=sy;
	rect2.right	=sx+sw;
	rect2.bottom=sy+sh;

	//	表示
	ddsfc1->Blt(&rect1,ddsfc2,&rect2,DDBLT_WAIT,NULL);
}

///////////////////////////////////////////////////////////
//	ビットマップを50%混合表示
//	引値	int		X座標
//			int		Y座標
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップを比率指定で混合表示
//	引値	int		X座標
//			int		Y座標
//			int		混合(0 - 32)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップをRGB比率指定で混合表示
//	引値	int		X座標
//			int		Y座標
//			int		R混合(0 - 32)
//			int		G混合(0 - 32)
//			int		B混合(0 - 32)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップを加算合成表示
//	引値	int		X座標
//			int		Y座標
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

void afBitmap::Add(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Add(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	ビットマップを加算調光合成表示
//	引値	int		X座標
//			int		Y座標
//			int		明度(0 - 32)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップを減算合成表示
//	引値	int		X座標
//			int		Y座標
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

void afBitmap::Subtract(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Subtract(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	ビットマップを減算調光合成表示
//	引値	int		X座標
//			int		Y座標
//			int		明度(0 - 32)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップを乗算合成表示
//	引値	int		X座標
//			int		Y座標
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

void afBitmap::Multiply(int dx,int dy,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Multiply(gx+dx,gy+dy,nBitmap,sx,sy,sw,sh);
}

///////////////////////////////////////////////////////////
//	ビットマップを比率指定で調光表示
//	引値	int		X座標
//			int		Y座標
//			int		明度(0 - 32 - 64)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップをRGB比率指定で調光表示
//	引値	int		X座標
//			int		Y座標
//			int		R明度(0 - 32 - 64)
//			int		G明度(0 - 32 - 64)
//			int		B明度(0 - 32 - 64)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップを比率指定で不透明調光表示
//	引値	int		X座標
//			int		Y座標
//			int		明度(0 - 32 - 64)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップをRGB比率指定で不透明調光表示
//	引値	int		X座標
//			int		Y座標
//			int		R明度(0 - 32 - 64)
//			int		G明度(0 - 32 - 64)
//			int		B明度(0 - 32 - 64)
//			int		データのX座標
//			int		データのY座標
//			int		幅
//			int		高さ

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
//	ビットマップを拡大縮小表示
//	引値	int		X座標
//			int		Y座標
//			int		幅
//			int		高さ
//			int		データのX座標
//			int		データのY座標
//			int		データの幅
//			int		データの高さ

void afBitmap::Stretch(int dx,int dy,int dw,int dh,int sx,int sy,int sw,int sh)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	_coreGraphics::Stretch(gx+dx,gy+dy,dw,dh,nBitmap,sx,sy,sw,sh);
}
