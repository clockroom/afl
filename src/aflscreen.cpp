//
//	AFL Screen Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afScreen
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"
#include "aflcore.h"
#include "afldialog.h"

///////////////////////////////////////////////////////////
//	静的クラス変数定義

int afScreen::ScrnW=0;
int afScreen::ScrnH=0;

LPDIRECTDRAWSURFACE afScreen::pWork=NULL;

///////////////////////////////////////////////////////////
//	スクリーンオブジェクト構築
//	引値	なし

afScreen::afScreen()
{
}

///////////////////////////////////////////////////////////
//	画面を作成
//	引値	int		幅
//			int		高さ
//	プログラム中2回以上呼ばないでください

bool afScreen::CreateScreen(int w,int h)
{
	ScrnW=w;
	ScrnH=h;

	if(!_coreGraphics::InitGraphics(w,h)) return false;
	pWork=_coreGraphics::pDDSBack;

	return true;
}

///////////////////////////////////////////////////////////
//	フルカラーの画面を作成
//	引値	int		幅
//			int		高さ
//	プログラム中2回以上呼ばないでください

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
//	ビットマップの表示可能範囲を画面サイズに設定
//	引値	なし

void afScreen::SetDrawArea()
{
	_coreGraphics::SetDrawArea(0,0,ScrnW,ScrnH);
}

///////////////////////////////////////////////////////////
//	ビットマップの表示可能範囲を設定
//	引値	int		左上X座標
//			int		左上Y座標
//			int		右下X座標
//			int		右下Y座標

void afScreen::SetDrawArea(int x1,int y1,int x2,int y2)
{
	_coreGraphics::SetDrawArea(x1,y1,x2,y2);
}

///////////////////////////////////////////////////////////
//	画面サイズ取得
//	引値	int*	幅を格納する変数へのポインタ
//			int*	高さを格納する変数へのポインタ

void afScreen::GetScreenSize(int *w,int *h)
{
	if(w!=NULL) *w=ScrnW;
	if(h!=NULL) *h=ScrnH;
}

///////////////////////////////////////////////////////////
//	ピクセルフォーマットを取得
//	引値	AFPIXELFORMAT*	データを格納するAFPIXELFORMAT構造体の
//							アドレス

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
//	バックバッファのDCを取得
//	引値	afDC*	DCを格納するafDCオブジェクトのアドレス

void afScreen::GetDC(afDC *pdc)
{
	_coreGraphics::pDDSBack->GetDC(&(pdc->hDC));
}

///////////////////////////////////////////////////////////
//	バックバッファのDCを解放
//	引値	afDC*	DCを格納したafDCオブジェクトへのポインタ

void afScreen::ReleaseDC(afDC *pdc)
{
	_coreGraphics::pDDSBack->ReleaseDC(pdc->hDC);
}

///////////////////////////////////////////////////////////
//	バックバッファをロックする
//	引値	afPixelData*	ピクセルデータを格納する変数のアドレス

void afScreen::Lock(afPixelData *pPD)
{
	DDSURFACEDESC	ddsd;
	WORD	d;

	ddsd.dwSize=sizeof(DDSURFACEDESC);
	_coreGraphics::pDDSBack->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);

	pPD->pPixel=(WORD*)ddsd.lpSurface;
	pPD->Pitch =ddsd.lPitch/2;

	//	DirectDrawキャッシュ(?)リセット
	d=*(pPD->pPixel);
	d=*(pPD->pPixel+1);
}

///////////////////////////////////////////////////////////
//	バックバッファのロックを解除する
//	引値	afPixelData*	ピクセルデータを格納した変数へのポインタ

void afScreen::Unlock(afPixelData *pPD)
{
	_coreGraphics::pDDSBack->Unlock(pPD->pPixel);
}

///////////////////////////////////////////////////////////
//	バックバッファのサーフェスを取得
//	引値	なし
//	返値	LPDIRECTDRAWSURFACE	サーフェスへのポインタ

LPDIRECTDRAWSURFACE afScreen::GetDDBackSurface()
{
	return _coreGraphics::pDDSBack;
}

///////////////////////////////////////////////////////////
//	作業スクリーンを設定
//	引値	afBitmap*	ビットマップへのポインタ
//	注意	使用後はRestoreWorkScreen()関数を呼んでください

void afScreen::SetWorkScreen(afBitmap *bmp)
{
	_coreGraphics::pDDSBack=bmp->GetDDSurface();
}

///////////////////////////////////////////////////////////
//	作業スクリーンを復旧する
//	引値	なし

void afScreen::RestoreWorkScreen()
{
	_coreGraphics::pDDSBack=pWork;
}

///////////////////////////////////////////////////////////
//	全画面を消去
//	引値	なし

void afScreen::Clear()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0;

	_coreGraphics::pDDSBack->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	指定範囲を消去
//	引値	int		左上X座標
//			int		左上Y座標
//			int		右下X座標
//			int		右下Y座標

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
//	画面を白で全消去
//	引値	なし

void afScreen::ClearWhite()
{
	DDBLTFX	col;

	col.dwSize=sizeof(col);
	col.dwFillColor=0x0000FFFF;

	_coreGraphics::pDDSBack->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&col);
}

///////////////////////////////////////////////////////////
//	画面を更新
//	引値	なし

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
//	fpsを表示
//	引値	なし

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
