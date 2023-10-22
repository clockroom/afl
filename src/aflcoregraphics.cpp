//
//	AFL Graphic Core by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	_coreGraphics
//

///////////////////////////////////////////////////////////
//	インクルード

#include <aflinside.h>
#include <aflfunction.h>
#include <afldialog.h>
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	定数定義

#define	_CG_MAX_BITMAP		1024

#define	_CG_BITMAP_ERROR	0
#define	_CG_BITMAP_WORK		0
#define	_CG_BITMAP_USER		1

///////////////////////////////////////////////////////////
//	静的変数定義

LPDIRECTDRAW		_coreGraphics::pDDObject=NULL;
LPDIRECTDRAWSURFACE _coreGraphics::pDDSFront=NULL;
LPDIRECTDRAWSURFACE _coreGraphics::pDDSBack =NULL;
_coreGraphics::_tBITMAP _coreGraphics::dBitmap[_CG_MAX_BITMAP];

int  _coreGraphics::PixelSize=2;
bool _coreGraphics::fCanStretch;

int _coreGraphics::AreaX1;
int _coreGraphics::AreaY1;
int _coreGraphics::AreaX2;
int _coreGraphics::AreaY2;

int   _coreGraphics::ShiftR;
int   _coreGraphics::ShiftG;
int   _coreGraphics::ShiftB;
int   _coreGraphics::BitCountR;
int   _coreGraphics::BitCountG;
int   _coreGraphics::BitCountB;
int   _coreGraphics::BitCountRGB;
DWORD _coreGraphics::MaskR;
DWORD _coreGraphics::MaskG;
DWORD _coreGraphics::MaskB;
DWORD _coreGraphics::MaskRGB;
DWORD _coreGraphics::BitR;
DWORD _coreGraphics::BitG;
DWORD _coreGraphics::BitB;

DWORD _coreGraphics::_MaskHalfBlend;

///////////////////////////////////////////////////////////
//	初期化

bool _coreGraphics::InitGraphics(int w,int h)
{
	DDSURFACEDESC	ddsd;
	DDPIXELFORMAT	format;
	DDCAPS	hal,hel;
	HRESULT	ret;
	DWORD	r,g,b;
	int		i;

	afErrorBox	eb;

	//	仮想画面の設定
	SetDrawArea(0,0,w,h);

	//	サーフェスの初期化
	for(i=_CG_BITMAP_USER;i<_CG_MAX_BITMAP;i++)
	{
		dBitmap[i].pDDSurface=NULL;
		dBitmap[i].ColorKey=RGB(0,0,0);
		dBitmap[i].psBmpName=0;
		dBitmap[i].fLost=false;
	}

	//	DirectDrawの呼び出し
	ret=DirectDrawCreate(NULL,&pDDObject,NULL);
	if(ret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("DirectDrawが使用できません。");
		eb.OpenBox();
		return false;
	}

	//	画面の切り換え
	ret=pDDObject->SetCooperativeLevel(GetWindowHandle(),DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT);
	if(ret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("フルスクリーンに設定できません。");
		eb.OpenBox();
		return false;
	}

	//	解像度の変更
	while(true)
	{
		ret=pDDObject->SetDisplayMode(w,h,PixelSize*8);
		if(ret==DD_OK)	 break;
		if(PixelSize!=3) break;
		PixelSize=4;
	}
	if(ret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("解像度が変更できません。");
		eb.OpenBox();
		return false;
	}

	//	フロントバッファの作成
	ZeroMemory(&ddsd,sizeof(DDSURFACEDESC));
	ddsd.dwSize =sizeof(DDSURFACEDESC);
	ddsd.dwFlags=DDSD_CAPS;
	ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE;
	ret=pDDObject->CreateSurface(&ddsd,&pDDSFront,NULL);
	if(ret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("プライマリサーフェスを作成できません。");
		eb.OpenBox();
		return false;
	}

	//	バックバッファの作成
	ZeroMemory(&ddsd,sizeof(DDSURFACEDESC));
	ddsd.dwSize =sizeof(DDSURFACEDESC);
	ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth =w;
	ddsd.dwHeight=h;
	ret=pDDObject->CreateSurface(&ddsd,&pDDSBack,NULL);
	if(ret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("バックバッファを作成できません。");
		eb.OpenBox();
		return false;
	}

	//	作業バッファの作成
	ZeroMemory(&ddsd,sizeof(DDSURFACEDESC));
	ddsd.dwSize =sizeof(DDSURFACEDESC);
	ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth =w;
	ddsd.dwHeight=h;
	ret=pDDObject->CreateSurface(&ddsd,&dBitmap[_CG_BITMAP_WORK].pDDSurface,NULL);
	if(ret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("作業バッファを作成できません。");
		eb.OpenBox();
		return false;
	}
	SetColorKey(_CG_BITMAP_WORK,RGB(0,0,0));

	//	拡大縮小機能のチェック
	ZeroMemory(&hal,sizeof(DDCAPS));
	ZeroMemory(&hel,sizeof(DDCAPS));
	hal.dwSize=sizeof(DDCAPS);
	hel.dwSize=sizeof(DDCAPS);
	pDDObject->GetCaps(&hal,&hel);
	if(hal.dwCaps&DDCAPS_BLTSTRETCH || hel.dwCaps&DDCAPS_BLTSTRETCH)
	{
		fCanStretch=true;
	}
	else
	{
		fCanStretch=false;
	}

	//	ピクセルフォーマット取得
	ZeroMemory(&format,sizeof(DDPIXELFORMAT));
	format.dwSize=sizeof(DDPIXELFORMAT);
	ret=pDDSBack->GetPixelFormat(&format);
	if(ret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("ピクセルフォーマットが取得できません。");
		eb.OpenBox();
		return false;
	}

	//	各フォーマット作成
	MaskR=BitR=format.dwRBitMask;
	MaskG=BitG=format.dwGBitMask;
	MaskB=BitB=format.dwBBitMask;
	MaskRGB=MaskR|MaskG|MaskB;

	for(ShiftR=0;!(BitR&0x0001);ShiftR++,BitR>>=1);
	for(ShiftG=0;!(BitG&0x0001);ShiftG++,BitG>>=1);
	for(ShiftB=0;!(BitB&0x0001);ShiftB++,BitB>>=1);

	for(BitCountR=0;BitR&(0x0001<<BitCountR);BitCountR++);
	for(BitCountG=0;BitG&(0x0001<<BitCountG);BitCountG++);
	for(BitCountB=0;BitB&(0x0001<<BitCountB);BitCountB++);
	BitCountRGB=BitCountR+BitCountG+BitCountB;

	//	内部使用フォーマット作成
	r=(BitR>>1)<<ShiftR;
	g=(BitG>>1)<<ShiftG;
	b=(BitB>>1)<<ShiftB;
	_MaskHalfBlend=r|g|b;

	//	他コア初期化
	_coreSound::InitSound();
	_coreMusic::InitMusic();

	return true;
}

///////////////////////////////////////////////////////////
//	破棄

void _coreGraphics::DestroyGraphics()
{
	int i;

	if(pDDObject==NULL)	return;

	for(i=0;i<_CG_MAX_BITMAP;i++)
	{
		if(dBitmap[i].pDDSurface!=NULL)
		{
			dBitmap[i].pDDSurface->Release();
			dBitmap[i].pDDSurface=NULL;
		}
		delete[] dBitmap[i].psBmpName;
		dBitmap[i].psBmpName=0;
	}

	if(pDDSBack!=NULL)
	{
		pDDSBack->Release();
		pDDSBack=NULL;
	}

	if(pDDSFront!=NULL)
	{
		pDDSFront->Release();
		pDDSFront=NULL;
	}

	pDDObject->RestoreDisplayMode();
	pDDObject->SetCooperativeLevel(GetWindowHandle(),DDSCL_NORMAL);

	pDDObject->Release();
	pDDObject=NULL;
}

///////////////////////////////////////////////////////////
//	グラフィックス復元

void _coreGraphics::RestoreGraphics()
{
	int		i;

	if(pDDSFront->IsLost()!=DD_OK) pDDSFront->Restore();
	if(pDDSBack ->IsLost()!=DD_OK) pDDSBack ->Restore();

	for(i=0;i<_CG_MAX_BITMAP;i++)
	{
		if(dBitmap[i].pDDSurface==NULL)			   continue;
		if(dBitmap[i].pDDSurface->IsLost()==DD_OK) continue;

		dBitmap[i].pDDSurface->Restore();
		dBitmap[i].fLost=true;
		ReloadBitmap(i);
	}
}

///////////////////////////////////////////////////////////
//	空ビットマップ作成

int _coreGraphics::CreateBitmap(int w,int h,bool fMemory)
{
	afErrorBox		eb;
	DDSURFACEDESC	ddsd;
	HRESULT	ddret;
	int		n;

	for(n=_CG_BITMAP_USER;n<_CG_MAX_BITMAP;n++)
	{
		if(dBitmap[n].psBmpName==0) break;
	}

	if(n>=_CG_MAX_BITMAP)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("ビットマップバッファが上限に達しました。");
		eb.SetRepair("ロードされたビットマップの数が多すぎます。");
		eb.OpenBox();

		return _CG_BITMAP_ERROR;
	}

	ZeroMemory(&ddsd,sizeof(DDSURFACEDESC));
	ddsd.dwSize=sizeof(DDSURFACEDESC);
    ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;
    ddsd.dwWidth =w;
    ddsd.dwHeight=h+1;
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	if(!fMemory) ddsd.ddsCaps.dwCaps|=DDSCAPS_SYSTEMMEMORY;

	ddret=pDDObject->CreateSurface(&ddsd,&dBitmap[n].pDDSurface,NULL);
	if(ddret!=DD_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("ビットマップを作成できません。");
		eb.SetRepair("次のいずれかの原因が考えられます。\n"
			"ビットマップが大きすぎる。\n"
			"メモリが不足している。");
		eb.OpenBox();

		return _CG_BITMAP_ERROR;
	}

	_SetColorKey(dBitmap[n].pDDSurface,RGB(0,0,0));
	dBitmap[n].ColorKey=RGB(0,0,0);

	dBitmap[n].psBmpName=new char[2];
	strcpy(dBitmap[n].psBmpName,"*");

	dBitmap[n].fLost=false;

	return n;
}

///////////////////////////////////////////////////////////
//	ビットマップ読み込み

int _coreGraphics::LoadBitmap(const char *psName,bool fMemory)
{
	afErrorBox	eb;
	int	n;

	for(n=_CG_BITMAP_USER;n<_CG_MAX_BITMAP;n++)
	{
		if(dBitmap[n].psBmpName==0) break;
	}

	if(n>=_CG_MAX_BITMAP)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("ビットマップバッファが上限に達しました。");
		eb.SetRepair("ロードされたビットマップの数が多すぎます。");
		eb.OpenBox();

		return _CG_BITMAP_ERROR;
	}

	dBitmap[n].pDDSurface=_CreateBitmapSurface(pDDObject,psName,fMemory);
	if(dBitmap[n].pDDSurface==NULL)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("ビットマップを読み込めません。");
		eb.SetRepair("次のいずれかの原因が考えられます。\n"
					 "ファイル名が間違っている。\n"
					 "ビットマップが大きすぎる。\n"
					 "メモリが不足している。");
		eb.OpenBox();

		return _CG_BITMAP_ERROR;
	}

	_SetColorKey(dBitmap[n].pDDSurface,RGB(0,0,0));
	dBitmap[n].ColorKey=RGB(0,0,0);

	dBitmap[n].psBmpName=new char[strlen(psName)+1];
	strcpy(dBitmap[n].psBmpName,psName);

	dBitmap[n].fLost=false;

	return n;
}

///////////////////////////////////////////////////////////
//	ビットマップを再読み込み

void _coreGraphics::ReloadBitmap(int n)
{
	HBITMAP	hbm;

	if(n<_CG_BITMAP_USER)			 return;
	if(dBitmap[n].psBmpName[0]=='*') return;

	hbm=_LoadBitmap(dBitmap[n].psBmpName);
	_CopyBitmapToSurface(dBitmap[n].pDDSurface,hbm);
	DeleteObject(hbm);

	_SetColorKey(dBitmap[n].pDDSurface,dBitmap[n].ColorKey);
}

///////////////////////////////////////////////////////////
//	ビットマップを解放

void _coreGraphics::ReleaseBitmap(int n)
{
	if(n<_CG_BITMAP_USER) return;

	if(dBitmap[n].pDDSurface!=NULL)
	{
		dBitmap[n].pDDSurface->Release();
		dBitmap[n].pDDSurface=NULL;
	}

	delete[] dBitmap[n].psBmpName;
	dBitmap[n].psBmpName=0;

	dBitmap[n].ColorKey=RGB(0,0,0);
	dBitmap[n].fLost=false;
}

///////////////////////////////////////////////////////////
//	仮想画面サイズ設定

void _coreGraphics::SetDrawArea(int x1,int y1,int x2,int y2)
{
	AreaX1=x1;
	AreaY1=y1;
	AreaX2=x2;
	AreaY2=y2;
}

///////////////////////////////////////////////////////////
//	透明色の変更

void _coreGraphics::SetColorKey(int n,COLORREF col)
{
	_SetColorKey(dBitmap[n].pDDSurface,col);
	dBitmap[n].ColorKey=col;
}

///////////////////////////////////////////////////////////
//	透明色を左上隅に設定

void _coreGraphics::SetColorKey(int n)
{
	_SetColorKey(dBitmap[n].pDDSurface,0xFFFFFFFF);
	dBitmap[n].ColorKey=0xFFFFFFFF;
}

///////////////////////////////////////////////////////////
//	ビットマップを描画

void _coreGraphics::Put(int dx,int dy,int n,int sx,int sy,int w,int h)
{
	RECT	rect;

	if(dx+w>AreaX2)	w=AreaX2-dx;
	if(dy+h>AreaY2)	h=AreaY2-dy;
	if(dx<AreaX1)	{sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1)	{sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0)	return;

	rect.left=sx;
	rect.top=sy;
	rect.right=sx+w;
	rect.bottom=sy+h;

	pDDSBack->BltFast(dx,dy,dBitmap[n].pDDSurface,&rect,DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
}

///////////////////////////////////////////////////////////
//	透明色を無視して描画

void _coreGraphics::Opaque(int dx,int dy,int n,int sx,int sy,int w,int h)
{
	RECT	rect;

	if(dx+w>AreaX2)	w=AreaX2-dx;
	if(dy+h>AreaY2)	h=AreaY2-dy;
	if(dx<AreaX1)	{sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1)	{sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0)	return;

	rect.left=sx;
	rect.top=sy;
	rect.right=sx+w;
	rect.bottom=sy+h;

	pDDSBack->BltFast(dx,dy,dBitmap[n].pDDSurface,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
}

///////////////////////////////////////////////////////////
//	拡縮描画

void _coreGraphics::Stretch(int dx,int dy,int dw,int dh,int n,int sx,int sy,int sw,int sh)
{
	RECT	rect1,rect2;
	HDC		hdc1,hdc2;

	if(!fCanStretch)
	{
		dBitmap[_CG_BITMAP_WORK].pDDSurface->GetDC(&hdc1);
		dBitmap[n].pDDSurface->GetDC(&hdc2);

		StretchBlt(hdc1,0,0,dw,dh,hdc2,sx,sy,sw,sh,SRCCOPY);

		dBitmap[_CG_BITMAP_WORK].pDDSurface->ReleaseDC(hdc1);
		dBitmap[n].pDDSurface->ReleaseDC(hdc2);

		Put(dx,dy,_CG_BITMAP_WORK,0,0,dw,dh);

		return;
	}

	rect2.left=sx;
	rect2.top=sy;
	rect2.right=sx+sw;
	rect2.bottom=sy+sh;

	if(AreaX1<=dx && dx+dw<=AreaX2 && AreaY1<=dy && dy+dh<=AreaY2)
	{
		rect1.left=dx;
		rect1.top=dy;
		rect1.right=dx+dw;
		rect1.bottom=dy+dh;

		pDDSBack->Blt(&rect1,dBitmap[n].pDDSurface,&rect2,DDBLT_KEYSRC|DDBLT_WAIT,NULL);

		return;
	}

	rect1.left=0;
	rect1.top=0;
	rect1.right=dw;
	rect1.bottom=dh;

	dBitmap[_CG_BITMAP_WORK].pDDSurface->Blt(&rect1,dBitmap[n].pDDSurface,&rect2,DDBLT_WAIT,NULL);
	Put(dx,dy,_CG_BITMAP_WORK,0,0,dw,dh);
}

///////////////////////////////////////////////////////////
//	５０％ブレンド描画

void _coreGraphics::BlendA(int dx,int dy,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		buf1,buf2;
	int		pitch1,pitch2;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf1=*(data1+x);
			if(buf1==0x0000) continue;

			buf1>>=1;
			buf2  =*(data2+x)>>1;
			buf1&=_MaskHalfBlend;
			buf2&=_MaskHalfBlend;

			*(data2+x)=buf1+buf2;
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	５０％ブレンド描画（高速）

void _coreGraphics::BlendB(int dx,int dy,int n,int sx,int sy,int sw,int sh)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	DWORD	mask;
	BYTE	*data1,*data2;
	int		pitch1,pitch2;
	int		y;

	//	描画領域の計算
	if(dx+sw>AreaX2) sw=AreaX2-dx;
	if(dy+sh>AreaY2) sh=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;sw-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;sh-=AreaY1-dy;dy=AreaY1;}
	if(sw<=0 || sh<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイトの取得
	pitch1=ddsd1.lPitch;
	pitch2=ddsd2.lPitch;

	//	ビットマップの先頭位置を取得
	data1=(BYTE*)ddsd1.lpSurface+sx*2+sy*pitch1;
	data2=(BYTE*)ddsd2.lpSurface+dx*2+dy*pitch2;

	//	データ設定
	mask=(_MaskHalfBlend<<16)|_MaskHalfBlend;
	sw*=2;

	//	データ転送
	__asm
	{
		mov esi,data1;	//	転送元アドレス	
		mov edi,data2;	//	転送先アドレス

		mov ebx,0;		//	Ｘ方向カウンタ
		mov eax,sh;
		mov y,eax;		//	Ｙ方向カウンタ

	LABEL_LOOP:

		//	転送元画素取得
		mov eax,[esi+ebx];

		//	透明色判定
		test eax,0ffffffffh;
		jz   LABEL_ENDOF_LOOP;
		test eax,0ffff0000h;
		jz   LABEL_PATTERN1;
		test eax,00000ffffh;
		jz   LABEL_PATTERN2;

	//////////	パターン０

		//	転送先画素取得
		mov edx,[edi+ebx];

		//	画素処理
		shr eax,1;
		shr edx,1;
		mov ecx,mask;
		and eax,ecx;
		and edx,ecx;
		add eax,edx;

		//	転送処理
		mov [edi+ebx],eax;

		jmp LABEL_ENDOF_LOOP;

	//////////	パターン１
	LABEL_PATTERN1:

		//	転送先画素取得
		mov edx,[edi+ebx];
		mov ecx,edx;

		//	画素処理
		shr eax,1;
		shr edx,1;
		and eax,mask;
		and edx,mask;
		add eax,edx;
		and eax,00000ffffh;

		//	転送処理
		and ecx,0ffff0000h;
		or  ecx,eax;
		mov [edi+ebx],ecx;

		jmp LABEL_ENDOF_LOOP;

	//////////	パターン２
	LABEL_PATTERN2:

		//	転送先画素取得
		mov edx,[edi+ebx];
		mov ecx,edx;

		//	画素処理
		shr eax,1;
		shr edx,1;
		and eax,mask;
		and edx,mask;
		add eax,edx;
		and eax,0ffff0000h;

		//	転送処理
		and ecx,00000ffffh;
		or  ecx,eax;
		mov [edi+ebx],ecx;

	//////////	ループ末端
	LABEL_ENDOF_LOOP:

		//	Ｘループ継続判定
		add ebx,4;
		mov eax,sw;
		cmp ebx,eax;
		jnz LABEL_LOOP;

		//	Ｙループ継続判定
		dec y;
		jz  LABEL_ENDOF_MAIN;

		mov eax,pitch1;
		mov edx,pitch2;
		add esi,eax;
		add edi,edx;
		mov ebx,0;
		jmp LABEL_LOOP;

	LABEL_ENDOF_MAIN:
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	任意値ブレンド描画

void _coreGraphics::Blend(int dx,int dy,int p,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;
	int		p2;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	ブレンド値の算出
	p2=32-p;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=(buf>>ShiftR)&BitR;
			g1=(buf>>ShiftG)&BitG;
			b1=(buf>>ShiftB)&BitB;

			buf=*(data2+x);

			r2=(buf>>ShiftR)&BitR;
			g2=(buf>>ShiftG)&BitG;
			b2=(buf>>ShiftB)&BitB;

			r1=(r1*p+r2*p2)>>5;
			g1=(g1*p+g2*p2)>>5;
			b1=(b1*p+b2*p2)>>5;

			*(data2+x)=(r1<<ShiftR)|(g1<<ShiftG)|(b1<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	ＲＧＢ単独ブレンド描画

void _coreGraphics::Blend(int dx,int dy,int pr,int pg,int pb,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;
	int		pr2,pg2,pb2;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	ブレンド値の算出
	pr2=32-pr;
	pg2=32-pg;
	pb2=32-pb;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=(buf>>ShiftR)&BitR;
			g1=(buf>>ShiftG)&BitG;
			b1=(buf>>ShiftB)&BitB;

			buf=*(data2+x);

			r2=(buf>>ShiftR)&BitR;
			g2=(buf>>ShiftG)&BitG;
			b2=(buf>>ShiftB)&BitB;

			r1=(r1*pr+r2*pr2)>>5;
			g1=(g1*pg+g2*pg2)>>5;
			b1=(b1*pb+b2*pb2)>>5;

			*(data2+x)=(r1<<ShiftR)|(g1<<ShiftG)|(b1<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	加算描画

void _coreGraphics::Add(int dx,int dy,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch>>1;
	pitch2=ddsd2.lPitch>>1;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=buf&MaskR;
			g1=buf&MaskG;
			b1=buf&MaskB;

			buf=*(data2+x);

			r2=buf&MaskR;
			g2=buf&MaskG;
			b2=buf&MaskB;

			r2+=r1;
			g2+=g1;
			b2+=b1;

			if((UINT)r2>MaskR) r2=MaskR;
			if((UINT)g2>MaskG) g2=MaskG;
			if((UINT)b2>MaskB) b2=MaskB;

			*(data2+x)=r2|g2|b2;
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	調光加算描画

void _coreGraphics::AddBright(int dx,int dy,int p,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch>>1;
	pitch2=ddsd2.lPitch>>1;

	// ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=buf&MaskR;
			g1=buf&MaskG;
			b1=buf&MaskB;

			buf=*(data2+x);

			r2=buf&MaskR;
			g2=buf&MaskG;
			b2=buf&MaskB;

			r2+=((r1*p)>>5)&MaskR;
			g2+=((g1*p)>>5)&MaskG;
			b2+=((b1*p)>>5)&MaskB;

			if((UINT)r2>MaskR) r2=MaskR;
			if((UINT)g2>MaskG) g2=MaskG;
			if((UINT)b2>MaskB) b2=MaskB;

			*(data2+x)=r2|g2|b2;
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	減算描画

void _coreGraphics::Subtract(int dx,int dy,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		x,y;
	int		buf,r1,g1,b1,r2,g2,b2;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=buf&MaskR;
			g1=buf&MaskG;
			b1=buf&MaskB;

			buf=*(data2+x);

			r2=buf&MaskR;
			g2=buf&MaskG;
			b2=buf&MaskB;

			r2-=r1;
			g2-=g1;
			b2-=b1;

			if(r2<0) r2=0;
			if(g2<0) g2=0;
			if(b2<0) b2=0;

			*(data2+x)=r2|g2|b2;
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	調光減算描画

void _coreGraphics::SubBright(int dx,int dy,int p,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=buf&MaskR;
			g1=buf&MaskG;
			b1=buf&MaskB;

			buf=*(data2+x);

			r2=buf&MaskR;
			g2=buf&MaskG;
			b2=buf&MaskB;

			r2-=((r1*p)>>5)&MaskR;
			g2-=((g1*p)>>5)&MaskG;
			b2-=((b1*p)>>5)&MaskB;

			if(r2<0) r2=0;
			if(g2<0) g2=0;
			if(b2<0) b2=0;

			*(data2+x)=r2|g2|b2;
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	乗算描画

void _coreGraphics::Multiply(int dx,int dy,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch>>1;
	pitch2=ddsd2.lPitch>>1;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if((DWORD)buf==MaskRGB) continue;

			r1=(buf>>ShiftR)&BitR;
			g1=(buf>>ShiftG)&BitG;
			b1=(buf>>ShiftB)&BitB;

			buf=*(data2+x);

			r2=buf&MaskR;
			g2=buf&MaskG;
			b2=buf&MaskB;

			r2=(((r1+1)*r2)>>BitCountR)&MaskR;
			g2=(((g1+1)*g2)>>BitCountG)&MaskG;
			b2=(((b1+1)*b2)>>BitCountB)&MaskB;

			*(data2+x)=r2|g2|b2;
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	調光描画

void _coreGraphics::BrightA(int dx,int dy,int p,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r,g,b;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r=(buf>>ShiftR)&BitR;
			g=(buf>>ShiftG)&BitG;
			b=(buf>>ShiftB)&BitB;

			r=(r*p)>>5;
			g=(g*p)>>5;
			b=(b*p)>>5;

			*(data2+x)=(r<<ShiftR)|(g<<ShiftG)|(b<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	調光描画（ホワイトアウト用）

void _coreGraphics::BrightB(int dx,int dy,int p,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		r1,g1,b1,r2,g2,b2;
	int		x,y;
	int		buf;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=(buf>>ShiftR)&BitR;
			g1=(buf>>ShiftG)&BitG;
			b1=(buf>>ShiftB)&BitB;

			r2=BitR-r1;
			g2=BitG-g1;
			b2=BitB-b1;

			r1+=(r2*p)>>5;
			g1+=(g2*p)>>5;
			b1+=(b2*p)>>5;

			*(data2+x)=(r1<<ShiftR)|(g1<<ShiftG)|(b1<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	不透明調光描画

void _coreGraphics::BrightOpaqueA(int dx,int dy,int p,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r,g,b;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			r=(buf>>ShiftR)&BitR;
			g=(buf>>ShiftG)&BitG;
			b=(buf>>ShiftB)&BitB;

			r=(r*p)>>5;
			g=(g*p)>>5;
			b=(b*p)>>5;

			*(data2+x)=(r<<ShiftR)|(g<<ShiftG)|(b<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	不透明調光描画（ホワイトアウト用）

void _coreGraphics::BrightOpaqueB(int dx,int dy,int p,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		r1,g1,b1,r2,g2,b2;
	int		x,y;
	int		buf;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			r1=(buf>>ShiftR)&BitR;
			g1=(buf>>ShiftG)&BitG;
			b1=(buf>>ShiftB)&BitB;

			r2=BitR-r1;
			g2=BitG-g1;
			b2=BitB-b1;

			r1+=(r2*p)>>5;
			g1+=(g2*p)>>5;
			b1+=(b2*p)>>5;

			*(data2+x)=(r1<<ShiftR)|(g1<<ShiftG)|(b1<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	ＲＧＢ単独調光描画

void _coreGraphics::Bright(int dx,int dy,int pr,int pg,int pb,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);
			if(buf==0x0000) continue;

			r1=(buf>>ShiftR)&BitR;
			if(pr<=32) {r1=(r1*pr)>>5;}
			else	   {r2=BitR-r1;r1+=(r2*(pr-32))>>5;}

			g1=(buf>>ShiftG)&BitG;
			if(pg<=32) {g1=(g1*pg)>>5;}
			else	   {g2=BitG-g1;g1+=(g2*(pg-32))>>5;}

			b1=(buf>>ShiftB)&BitB;
			if(pb<=32) {b1=(b1*pb)>>5;}
			else	   {b2=BitB-b1;b1+=(b2*(pb-32))>>5;}

			*(data2+x)=(r1<<ShiftR)|(g1<<ShiftG)|(b1<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	ＲＧＢ単独不透明調光描画

void _coreGraphics::BrightOpaque(int dx,int dy,int pr,int pg,int pb,int n,int sx,int sy,int w,int h)
{
	DDSURFACEDESC	ddsd1,ddsd2;
	HRESULT	ddret;
	WORD	*data1,*data2;
	int		pitch1,pitch2;
	int		buf,r1,g1,b1,r2,g2,b2;
	int		x,y;

	//	描画領域の計算
	if(dx+w>AreaX2) w=AreaX2-dx;
	if(dy+h>AreaY2) h=AreaY2-dy;
	if(dx<AreaX1) {sx+=AreaX1-dx;w-=AreaX1-dx;dx=AreaX1;}
	if(dy<AreaY1) {sy+=AreaY1-dy;h-=AreaY1-dy;dy=AreaY1;}
	if(w<=0 || h<=0) return;

	//	サーフェスのロック
	ddsd1.dwSize=sizeof(DDSURFACEDESC);
	ddsd2.dwSize=sizeof(DDSURFACEDESC);

	ddret=dBitmap[n].pDDSurface->Lock(NULL,&ddsd1,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK) return;

	ddret=pDDSBack->Lock(NULL,&ddsd2,DDLOCK_WAIT,NULL);
	if(ddret!=DD_OK)
	{
		dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
		return;
	}

	//	Ｙ方向への追加バイト数の取得
	pitch1=ddsd1.lPitch/2;
	pitch2=ddsd2.lPitch/2;

	//	ビットマップの先頭位置を取得
	data1=(WORD*)ddsd1.lpSurface+sx+sy*pitch1;
	data2=(WORD*)ddsd2.lpSurface+dx+dy*pitch2;

	//	データ転送
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			buf=*(data1+x);

			r1=(buf>>ShiftR)&BitR;
			if(pr<=32) {r1=(r1*pr)>>5;}
			else	   {r2=BitR-r1;r1+=(r2*(pr-32))>>5;}

			g1=(buf>>ShiftG)&BitG;
			if(pg<=32) {g1=(g1*pg)>>5;}
			else	   {g2=BitG-g1;g1+=(g2*(pg-32))>>5;}

			b1=(buf>>ShiftB)&BitB;
			if(pb<=32) {b1=(b1*pb)>>5;}
			else	   {b2=BitB-b1;b1+=(b2*(pb-32))>>5;}

			*(data2+x)=(r1<<ShiftR)|(g1<<ShiftG)|(b1<<ShiftB);
		}

		//	Ｙ方向に加算
		data1+=pitch1;
		data2+=pitch2;
	}

	//	ビットマップのロック解除
	dBitmap[n].pDDSurface->Unlock(ddsd1.lpSurface);
	pDDSBack->Unlock(ddsd2.lpSurface);
}

///////////////////////////////////////////////////////////
//	ビットマップサーフェスの作成

LPDIRECTDRAWSURFACE _coreGraphics::_CreateBitmapSurface(LPDIRECTDRAW pdd,const char *psName,bool fMemory)
{
	LPDIRECTDRAWSURFACE	pdds;
	DDSURFACEDESC		ddsd;
	HBITMAP	hbm=0;
	BITMAP	bm;

	hbm=_LoadBitmap(psName);
	if(hbm==NULL) return NULL;

	GetObject(hbm,sizeof(BITMAP),&bm);

	ZeroMemory(&ddsd,sizeof(DDSURFACEDESC));
	ddsd.dwSize	 =sizeof(DDSURFACEDESC);
	ddsd.dwFlags =DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;
	ddsd.dwWidth =bm.bmWidth;
	ddsd.dwHeight=bm.bmHeight;
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	if(!fMemory) ddsd.ddsCaps.dwCaps|=DDSCAPS_SYSTEMMEMORY;

	if(pdd->CreateSurface(&ddsd,&pdds,NULL)!=DD_OK) return NULL;

	_CopyBitmapToSurface(pdds,hbm);

	DeleteObject(hbm);

	return pdds;
}

///////////////////////////////////////////////////////////
//	ビットマップハンドルの取得

HBITMAP _coreGraphics::_LoadBitmap(const char *psName)
{
	HBITMAP	hbm;
	char	str[1024];

	hbm=(HBITMAP)LoadImage(GetModuleHandle(NULL),psName,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);
	if(hbm==NULL)
	{
		GetFullPathFileName(str,psName);
		hbm=(HBITMAP)LoadImage(NULL,str,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	}

	return hbm;
}

///////////////////////////////////////////////////////////
//	ビットマップをサーフェスへコピー

HRESULT _coreGraphics::_CopyBitmapToSurface(IDirectDrawSurface* pdds,HBITMAP hbm)
{
	DDSURFACEDESC	ddsd;
	BITMAP	bm;
	HDC		hdcImage;
	HDC		hdc;
	HRESULT	hr;
	int		w,h;

	if(hbm==NULL || pdds==NULL) return E_FAIL;

	pdds->Restore();

	hdcImage=CreateCompatibleDC(NULL);
	SelectObject(hdcImage,hbm);

	GetObject(hbm,sizeof(BITMAP),&bm);
	w=bm.bmWidth;
	h=bm.bmHeight;

	ddsd.dwSize=sizeof(DDSURFACEDESC);
	pdds->GetSurfaceDesc(&ddsd);

	if((hr=pdds->GetDC(&hdc))==DD_OK)
	{
		StretchBlt(hdc,0,0,ddsd.dwWidth,ddsd.dwHeight,hdcImage,0,0,w,h,SRCCOPY);
		pdds->ReleaseDC(hdc);
	}

	DeleteDC(hdcImage);

	return hr;
}

///////////////////////////////////////////////////////////
//	カラーマッチング

DWORD _coreGraphics::_ColorMatch(LPDIRECTDRAWSURFACE pdds,COLORREF col)
{
	DDSURFACEDESC	ddsd;
	COLORREF	temp;
	HRESULT		hres;
	HDC			hdc;
	DWORD		dw=CLR_INVALID;

	if(col!=CLR_INVALID && pdds->GetDC(&hdc)==DD_OK)
	{
		temp=GetPixel(hdc,0,0);
		SetPixel(hdc,0,0,col);
		pdds->ReleaseDC(hdc);
	}

	ddsd.dwSize=sizeof(DDSURFACEDESC);
	hres=pdds->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);

	if(hres==DD_OK)
	{
		dw =*(DWORD*)ddsd.lpSurface;
		dw&=(1<<ddsd.ddpfPixelFormat.dwRGBBitCount)-1;
		pdds->Unlock(NULL);
	}

	if(col!=CLR_INVALID && pdds->GetDC(&hdc)==DD_OK)
	{
		SetPixel(hdc,0,0,temp);
		pdds->ReleaseDC(hdc);
	}

	return dw;
}

///////////////////////////////////////////////////////////
//	カラーキー設定

HRESULT _coreGraphics::_SetColorKey(LPDIRECTDRAWSURFACE pdds,COLORREF col)
{
	DDCOLORKEY	ddck;

	ddck.dwColorSpaceLowValue =_ColorMatch(pdds,col);
	ddck.dwColorSpaceHighValue=ddck.dwColorSpaceLowValue;

	return pdds->SetColorKey(DDCKEY_SRCBLT,&ddck);
}
