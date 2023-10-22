//
//	AFL Graphics by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//

#ifndef	_AFLGRAPHICS_H_
#define	_AFLGRAPHICS_H_

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	クラス宣言

class afScreen;
class afGrpObject;
class	afGrpGroup;
class		afSprite;
class	afDC;
class	afPixelData;
class	afBitmap;
class	afPattern;

struct AFPIXELFORMAT;

///////////////////////////////////////////////////////////
//	定数

#define MARKER_ROOTGROUP 0x40000000

#define	SPR_NORMAL	   0
#define	SPR_BLEND50    1
#define	SPR_BLEND	   2
#define	SPR_BLENDRGB   3
#define	SPR_ADD		   4
#define	SPR_SUBTRACT   5
#define	SPR_STRETCH    6
#define	SPR_OPAQUE	   8
#define	SPR_ADDBRIGHT  9
#define	SPR_SUBBRIGHT 10
#define	SPR_MULTIPLY  11

#define	ORG_LEFTTOP		 0
#define	ORG_LEFTCENTER   1
#define	ORG_LEFTBOTTOM   2
#define	ORG_RIGHTTOP	 3
#define	ORG_RIGHTCENTER  4
#define	ORG_RIGHTBOTTOM  5
#define	ORG_CENTERTOP    6
#define	ORG_CENTER		 7
#define	ORG_CENTERBOTTOM 8

///////////////////////////////////////////////////////////
//	構造体

//	ピクセルフォーマット
struct AFPIXELFORMAT
{
	int		ShiftR,ShiftG,ShiftB;
	int		BitCountR,BitCountG,BitCountB,BitCountRGB;
	DWORD	BitR,BitG,BitB;
	union
	{
		DWORD	ColorFormatR;
		DWORD	MaskR;
	};
	union
	{
		DWORD	ColorFormatG;
		DWORD	MaskG;
	};
	union
	{
		DWORD	ColorFormatB;
		DWORD	MaskB;
	};
	union
	{
		DWORD	ColorFormatW;
		DWORD	MaskRGB;
	};
};

///////////////////////////////////////////////////////////
//	スクリーンクラス

class afScreen
{
	public:
		//	構築
		afScreen();

		//	作成系
		bool	CreateScreen(int,int);
		bool	CreateFullColorScreen(int,int);

		//	設定系
		void	SetDrawArea();
		void	SetDrawArea(int,int,int,int);

		//	取得系
		void	GetScreenSize(int*,int*);
		void	GetPixelFormat(AFPIXELFORMAT*);

		//	デバイスコンテキスト系
		void	GetDC(afDC*);
		void	ReleaseDC(afDC*);

		//	メモリ系
		void	Lock(afPixelData*);
		void	Unlock(afPixelData*);

		//	作業スクリーン系
		LPDIRECTDRAWSURFACE	GetDDBackSurface();
		void	SetWorkScreen(afBitmap*);
		void	RestoreWorkScreen();

		//	表示系
		void	Clear();
		void	Clear(int,int,int,int);
		void	ClearWhite();
		void	Refresh();
		void	ShowFPS();

	private:
		//	変数
		static int	ScrnW,ScrnH;
		static LPDIRECTDRAWSURFACE	pWork;
};

///////////////////////////////////////////////////////////
//	グラフィックオブジェクトクラス

class afGrpObject
{
	public:
		//	構築
		afGrpObject();
		virtual ~afGrpObject();

		//	設定系
		virtual afGrpGroup *SetGroup(afGrpGroup*);

		//	取得系
		virtual void GetGroupPos(int*,int*);
		virtual void GetGroupPosByScreen(int*,int*);
		virtual void GetRootGroupPos(int*,int*);
		virtual void GetMarkedGroupPos(int*,int*,int);
		virtual void GetMarkedGroupPosByScreen(int*,int*,int);

	protected:
		//	変数
		afGrpGroup *pGroup;
};

///////////////////////////////////////////////////////////
//	グラフィックグループクラス

class afGrpGroup:public afGrpObject
{
	public:
		//	構築
		afGrpGroup();

		//	設定系
		virtual void SetPos(int,int);
		virtual void SetMarker(int);

		//	取得系
		virtual void GetPos(int*,int*);
		virtual void GetPos(int*,int*,afGrpGroup*);
		virtual void GetPosByScreen(int*,int*);
		void GetRootGroupPos(int*,int*);
		void GetMarkedGroupPos(int*,int*,int);
		void GetMarkedGroupPosByScreen(int*,int*,int);

	protected:
		//	変数
		int X,Y;
		int nMarker;
};

///////////////////////////////////////////////////////////
//	デバイスコンテキストクラス

class afDC:public afGrpObject
{
	//	フレンド宣言
	friend class	afScreen;
	friend class	afBitmap;

	public:
		//	構築
		afDC();

		//	設定系
		void	SetClipper();
		void	SetClipper(int,int,int,int);

		//	取得系
		COLORREF	GetPixel(int,int);

		//	表示系
		void	Pixel(int,int,COLORREF);
		void	Text(int,int,const char*,int,bool,COLORREF);
		void	Text(int,int,const char*,int,bool,COLORREF,COLORREF);
		void	Line(int,int,int,int,int,COLORREF);
		void	Circle(int,int,int,int,int,COLORREF);
		void	Circle(int,int,int,int,int,COLORREF,COLORREF);
		void	Box(int,int,int,int,int,COLORREF);
		void	Box(int,int,int,int,int,COLORREF,COLORREF);
		void	Triangle(int,int,int,int,int,int,int,COLORREF);
		void	Triangle(int,int,int,int,int,int,int,COLORREF,COLORREF);

		//	演算子
		operator HDC();

	private:
		//	変数
		HDC		hDC;
};

///////////////////////////////////////////////////////////
//	ピクセルデータクラス

class afPixelData:public afGrpObject
{
	//	フレンド宣言
	friend class	afScreen;
	friend class	afBitmap;

	public:
		//	構築
		afPixelData();

		//	設定系
		void	SetPixel(int,int,WORD);

		//	取得系
		void	GetAddress(WORD**,int*);
		WORD	GetPixel(int,int);

	private:
		//	変数
		WORD	*pPixel;
		int		Pitch;
};

///////////////////////////////////////////////////////////
//	ビットマップクラス

class afBitmap:public afGrpObject
{
	public:
		//	構築
		afBitmap();
		~afBitmap();

		//	作成系
		void	CreateBitmap(int,int);
		void	CreateBitmap(int,int,bool);
		void	LoadBitmap(const char*);
		void	LoadBitmap(const char*,bool);
		void	ReleaseBitmap();
		void	ClearBitmap();
		void	ClearWhiteBitmap();
		void	ClipScreen(int,int,int,int);

		//	設定系
		void	SetColorKey();
		void	SetColorKey(COLORREF);

		//	取得系
		LPDIRECTDRAWSURFACE	GetDDSurface();
		bool	IsLost();

		//	デバイスコンテキスト系
		void	GetDC(afDC*);
		void	ReleaseDC(afDC*);

		//	メモリ系
		void	Lock(afPixelData*);
		void	Unlock(afPixelData*);

		//	表示系
		void	Put(int,int,int,int,int,int);
		void	Put(afBitmap*,int,int,int,int,int,int);
		void	Opaque(int,int,int,int,int,int);
		void	Opaque(afBitmap*,int,int,int,int,int,int);
		void	Blend(int,int,int,int,int,int);
		void	Blend(int,int,int,int,int,int,int);
		void	Blend(int,int,int,int,int,int,int,int,int);
		void	Add(int,int,int,int,int,int);
		void	AddBright(int,int,int,int,int,int,int);
		void	Subtract(int,int,int,int,int,int);
		void	SubBright(int,int,int,int,int,int,int);
		void	Multiply(int,int,int,int,int,int);
		void	Bright(int,int,int,int,int,int,int);
		void	Bright(int,int,int,int,int,int,int,int,int);
		void	BrightOpaque(int,int,int,int,int,int,int);
		void	BrightOpaque(int,int,int,int,int,int,int,int,int);
		void	Stretch(int,int,int,int,int,int,int,int);

	private:
		//	変数
		int	nBitmap;
};

///////////////////////////////////////////////////////////
//	パターンクラス

class afPattern:public afGrpObject
{
	//	フレンド宣言
	friend class	afSprite;

	public:
		//	構築
		afPattern();

		//	作成系
		void	CreatePattern(afBitmap*,int,int,int,int);

		//	設定系
		void	SetPattern(afBitmap*,int,int,int,int);
		void	SetPattern(int,int,int,int);
		void	SetPatternPos(int,int);
		void	SetPatternSize(int,int);
		void	MovePattern(int,int);

		//	表示系
		void	Put(int,int);
		void	Opaque(int,int);
		void	Blend(int,int,int);
		void	Add(int,int);
		void	AddBright(int,int,int);
		void	Subtract(int,int);
		void	SubBright(int,int,int);
		void	Multiply(int,int);
		void	Bright(int,int,int);
		void	BrightOpaque(int,int,int);
		void	Stretch(int,int,int,int);
		void	TileOpaque(int,int,int,int);

	private:
		//	変数
		afBitmap	*pBitmap;
		int	X,Y;
		int	W,H;
};

///////////////////////////////////////////////////////////
//	スプライトクラス

class afSprite:public afGrpGroup
{
	public:
		//	構築
		afSprite();

		//	作成系
		void	CreateSprite(afPattern*,int,int);

		//	設定系
		void	SetPattern(afPattern*);
		void	SetShow(bool);
		void	SetStyle(int);
		void	SetParam(int,int b=0,int c=0,int d=0);
		void	SetParam(int,int);
		void	AddParam(int,int b=0,int c=0,int d=0);
		void	AddParam(int,int);
		void	SetMove(int,int);
		void	AddMove(int,int);
		void	ReverseMove(bool,bool);
		void	SetOrigin(int,int,int);

		//	取得系
		void	GetPosLeftTop(int*,int*);
		void	GetPosLeftTopByScreen(int*,int*);
		bool	IsShow();
		void	GetParam(int*,int *pb=NULL,int *pc=NULL,int *pd=NULL);
		void	GetParam(int*,int);
		int		*GetParam();

		//	移動系
		void	Move();
		void	Move(int,int);

		//	表示系
		void	Show();

	private:
		//	変数
		afPattern	*pPattern;
		int		MX,MY;
		int		OX,OY;
		int		nOrigin;
		int		nStyle;
		int		dParam[8];
		bool	fShow;
};

#endif	//	_AFLGRAPHICS_H_
