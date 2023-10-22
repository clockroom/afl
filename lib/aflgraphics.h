//
//	AFL Graphics by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//

#ifndef	_AFLGRAPHICS_H_
#define	_AFLGRAPHICS_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	�N���X�錾

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
//	�萔

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
//	�\����

//	�s�N�Z���t�H�[�}�b�g
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
//	�X�N���[���N���X

class afScreen
{
	public:
		//	�\�z
		afScreen();

		//	�쐬�n
		bool	CreateScreen(int,int);
		bool	CreateFullColorScreen(int,int);

		//	�ݒ�n
		void	SetDrawArea();
		void	SetDrawArea(int,int,int,int);

		//	�擾�n
		void	GetScreenSize(int*,int*);
		void	GetPixelFormat(AFPIXELFORMAT*);

		//	�f�o�C�X�R���e�L�X�g�n
		void	GetDC(afDC*);
		void	ReleaseDC(afDC*);

		//	�������n
		void	Lock(afPixelData*);
		void	Unlock(afPixelData*);

		//	��ƃX�N���[���n
		LPDIRECTDRAWSURFACE	GetDDBackSurface();
		void	SetWorkScreen(afBitmap*);
		void	RestoreWorkScreen();

		//	�\���n
		void	Clear();
		void	Clear(int,int,int,int);
		void	ClearWhite();
		void	Refresh();
		void	ShowFPS();

	private:
		//	�ϐ�
		static int	ScrnW,ScrnH;
		static LPDIRECTDRAWSURFACE	pWork;
};

///////////////////////////////////////////////////////////
//	�O���t�B�b�N�I�u�W�F�N�g�N���X

class afGrpObject
{
	public:
		//	�\�z
		afGrpObject();
		virtual ~afGrpObject();

		//	�ݒ�n
		virtual afGrpGroup *SetGroup(afGrpGroup*);

		//	�擾�n
		virtual void GetGroupPos(int*,int*);
		virtual void GetGroupPosByScreen(int*,int*);
		virtual void GetRootGroupPos(int*,int*);
		virtual void GetMarkedGroupPos(int*,int*,int);
		virtual void GetMarkedGroupPosByScreen(int*,int*,int);

	protected:
		//	�ϐ�
		afGrpGroup *pGroup;
};

///////////////////////////////////////////////////////////
//	�O���t�B�b�N�O���[�v�N���X

class afGrpGroup:public afGrpObject
{
	public:
		//	�\�z
		afGrpGroup();

		//	�ݒ�n
		virtual void SetPos(int,int);
		virtual void SetMarker(int);

		//	�擾�n
		virtual void GetPos(int*,int*);
		virtual void GetPos(int*,int*,afGrpGroup*);
		virtual void GetPosByScreen(int*,int*);
		void GetRootGroupPos(int*,int*);
		void GetMarkedGroupPos(int*,int*,int);
		void GetMarkedGroupPosByScreen(int*,int*,int);

	protected:
		//	�ϐ�
		int X,Y;
		int nMarker;
};

///////////////////////////////////////////////////////////
//	�f�o�C�X�R���e�L�X�g�N���X

class afDC:public afGrpObject
{
	//	�t�����h�錾
	friend class	afScreen;
	friend class	afBitmap;

	public:
		//	�\�z
		afDC();

		//	�ݒ�n
		void	SetClipper();
		void	SetClipper(int,int,int,int);

		//	�擾�n
		COLORREF	GetPixel(int,int);

		//	�\���n
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

		//	���Z�q
		operator HDC();

	private:
		//	�ϐ�
		HDC		hDC;
};

///////////////////////////////////////////////////////////
//	�s�N�Z���f�[�^�N���X

class afPixelData:public afGrpObject
{
	//	�t�����h�錾
	friend class	afScreen;
	friend class	afBitmap;

	public:
		//	�\�z
		afPixelData();

		//	�ݒ�n
		void	SetPixel(int,int,WORD);

		//	�擾�n
		void	GetAddress(WORD**,int*);
		WORD	GetPixel(int,int);

	private:
		//	�ϐ�
		WORD	*pPixel;
		int		Pitch;
};

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�N���X

class afBitmap:public afGrpObject
{
	public:
		//	�\�z
		afBitmap();
		~afBitmap();

		//	�쐬�n
		void	CreateBitmap(int,int);
		void	CreateBitmap(int,int,bool);
		void	LoadBitmap(const char*);
		void	LoadBitmap(const char*,bool);
		void	ReleaseBitmap();
		void	ClearBitmap();
		void	ClearWhiteBitmap();
		void	ClipScreen(int,int,int,int);

		//	�ݒ�n
		void	SetColorKey();
		void	SetColorKey(COLORREF);

		//	�擾�n
		LPDIRECTDRAWSURFACE	GetDDSurface();
		bool	IsLost();

		//	�f�o�C�X�R���e�L�X�g�n
		void	GetDC(afDC*);
		void	ReleaseDC(afDC*);

		//	�������n
		void	Lock(afPixelData*);
		void	Unlock(afPixelData*);

		//	�\���n
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
		//	�ϐ�
		int	nBitmap;
};

///////////////////////////////////////////////////////////
//	�p�^�[���N���X

class afPattern:public afGrpObject
{
	//	�t�����h�錾
	friend class	afSprite;

	public:
		//	�\�z
		afPattern();

		//	�쐬�n
		void	CreatePattern(afBitmap*,int,int,int,int);

		//	�ݒ�n
		void	SetPattern(afBitmap*,int,int,int,int);
		void	SetPattern(int,int,int,int);
		void	SetPatternPos(int,int);
		void	SetPatternSize(int,int);
		void	MovePattern(int,int);

		//	�\���n
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
		//	�ϐ�
		afBitmap	*pBitmap;
		int	X,Y;
		int	W,H;
};

///////////////////////////////////////////////////////////
//	�X�v���C�g�N���X

class afSprite:public afGrpGroup
{
	public:
		//	�\�z
		afSprite();

		//	�쐬�n
		void	CreateSprite(afPattern*,int,int);

		//	�ݒ�n
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

		//	�擾�n
		void	GetPosLeftTop(int*,int*);
		void	GetPosLeftTopByScreen(int*,int*);
		bool	IsShow();
		void	GetParam(int*,int *pb=NULL,int *pc=NULL,int *pd=NULL);
		void	GetParam(int*,int);
		int		*GetParam();

		//	�ړ��n
		void	Move();
		void	Move(int,int);

		//	�\���n
		void	Show();

	private:
		//	�ϐ�
		afPattern	*pPattern;
		int		MX,MY;
		int		OX,OY;
		int		nOrigin;
		int		nStyle;
		int		dParam[8];
		bool	fShow;
};

#endif	//	_AFLGRAPHICS_H_
