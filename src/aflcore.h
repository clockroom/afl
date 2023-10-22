//
//	AFL Core by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//

#ifndef	_AFLCORE_H_
#define	_AFLCORE_H_

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	定数定義

#define _CS_MAX_POLY	10

///////////////////////////////////////////////////////////
//	クラス宣言

class _coreGraphics;
class _coreSound;
class _coreMusic;
class _coreMusic2;

///////////////////////////////////////////////////////////
//	グラフィックコアクラス

class _coreGraphics
{
	private:
		struct _tBITMAP
		{
			LPDIRECTDRAWSURFACE	pDDSurface;
			COLORREF	ColorKey;
			char		*psBmpName;
			bool		fLost;
		};

	public:
		static bool	InitGraphics(int,int);
		static void	DestroyGraphics();
		static void	RestoreGraphics();

		static int	CreateBitmap(int,int,bool);
		static int	LoadBitmap(const char*,bool);
		static void	ReloadBitmap(int);
		static void	ReleaseBitmap(int);

		static void	SetDrawArea(int,int,int,int);
		static void	SetColorKey(int,COLORREF);
		static void	SetColorKey(int);

		static void	Put(int,int,int,int,int,int,int);
		static void	Opaque(int,int,int,int,int,int,int);
		static void	Stretch(int,int,int,int,int,int,int,int,int);
		static void	BlendA(int,int,int,int,int,int,int);
		static void BlendB(int,int,int,int,int,int,int);
//		static void BlendC(int,int,int,int,int,int,int);
		static void	Blend(int,int,int,int,int,int,int,int);
		static void	Blend(int,int,int,int,int,int,int,int,int,int);
		static void	Add(int,int,int,int,int,int,int);
		static void	AddBright(int,int,int,int,int,int,int,int);
		static void	Subtract(int,int,int,int,int,int,int);
		static void	SubBright(int,int,int,int,int,int,int,int);
		static void	Multiply(int,int,int,int,int,int,int);
		static void	BrightA(int,int,int,int,int,int,int,int);
		static void	BrightB(int,int,int,int,int,int,int,int);
		static void	BrightOpaqueA(int,int,int,int,int,int,int,int);
		static void	BrightOpaqueB(int,int,int,int,int,int,int,int);
		static void	Bright(int,int,int,int,int,int,int,int,int,int);
		static void	BrightOpaque(int,int,int,int,int,int,int,int,int,int);

	private:
		static LPDIRECTDRAWSURFACE	_CreateBitmapSurface(LPDIRECTDRAW,const char*,bool);
		static HBITMAP	_LoadBitmap(const char*);
		static HRESULT	_CopyBitmapToSurface(LPDIRECTDRAWSURFACE,HBITMAP);
		static DWORD	_ColorMatch(LPDIRECTDRAWSURFACE,COLORREF);
		static HRESULT	_SetColorKey(LPDIRECTDRAWSURFACE,COLORREF);

	public:
		static LPDIRECTDRAW			pDDObject;
		static LPDIRECTDRAWSURFACE	pDDSFront;
		static LPDIRECTDRAWSURFACE	pDDSBack;
		static _tBITMAP				dBitmap[];

		static bool	fCanStretch;
		static int	PixelSize;

		static int	AreaX1,AreaY1,AreaX2,AreaY2;

		static int		ShiftR,ShiftG,ShiftB;
		static int		BitCountR,BitCountG,BitCountB,BitCountRGB;
		static DWORD	MaskR,MaskG,MaskB,MaskRGB;
		static DWORD	BitR,BitG,BitB;

	private:
		static DWORD	_MaskHalfBlend;
};

///////////////////////////////////////////////////////////
//	サウンドコアクラス

class _coreSound
{
	private:
		struct _tSOUND
		{
			LPDIRECTSOUNDBUFFER	dpDSBuffer[_CS_MAX_POLY];
			bool	fEnable;
			int		Poly;
			int		nPlay;
			DWORD	DefPitch;
		};

	public:
		static void	InitSound();
		static void	DestroySound();

		static void	SetSoundQuality(int);

		static int	LoadSound(const char*,int,bool);
		static void	ReleaseSound(int);

		static void	SetPitch(int,int);
		static void	SetPan(int,int);
		static void	SetVolume(int,int);
		static bool	IsPlaying(int);

		static void	Play(int);
		static void	Loop(int);
		static void	Stop(int);

	private:
		static bool	_ReadSoundFile(const char*,UINT*,WAVEFORMATEX**,BYTE**);

	public:
		static LPDIRECTSOUND		pDSObject;
		static LPDIRECTSOUNDBUFFER	pDSBuffer;
		static _tSOUND				dSound[];

		static bool		fOK;
};

///////////////////////////////////////////////////////////
//	ミュージックコアクラス

class _coreMusic
{
	public:
		static void	InitMusic();
		static void	DestroyMusic();

		static void	Play(const char*);
		static void	Stop();
		static void	Replay();

	public:
		static bool	fPlay;
		static bool	fRepeat;
};

///////////////////////////////////////////////////////////
//	ミュージックコアクラス (DM)

class _coreMusic2
{
	private:
		struct _tMUSIC2
		{
			IDirectMusicSegment	*pDMSegment;
		};

	public:
		static void	InitMusic();
		static void	DestroyMusic();

		static void	SetMasterVolume(long);
		static void	SetMasterExpression(long);

		static int	LoadMusic(const char*);
		static void	ReleaseMusic(int);

		static void	SetStartPoint(int,DWORD);
		static void	SetLoopPoint(int,DWORD,DWORD);
		static void	SetRepeat(int,bool);
		static bool	IsPlaying(int);

		static void	Play(int);
		static void	Stop();

	private:
		static void	FailInit();

	public:
		static IDirectMusic				*pDMObject;
		static IDirectMusicPort			*pDMPort;
		static IDirectMusicPerformance	*pDMPerformance;
		static IDirectMusicLoader		*pDMLoader;
		static LPDIRECTSOUNDBUFFER		pDSBuffer;
		static _tMUSIC2	dMusic[];

		static bool	fEnable;
};

#endif	//	_AFLCORE_H_
