//
//	AFL Input by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef	_AFLINPUT_H_
#define	_AFLINPUT_H_

///////////////////////////////////////////////////////////
//	定数定義

#define	KEY_FREE	0
#define	KEY_PUSH	1
#define	KEY_HOLD	2
#define	KEY_PULL	3

#define	ML_FREE		0x0000
#define	ML_PUSH		0x0100
#define	ML_HOLD		0x0200
#define	ML_PULL		0x0300
#define	ML_ONLY		0xff00
#define	MR_FREE		0x0000
#define	MR_PUSH		0x0001
#define	MR_HOLD		0x0002
#define	MR_PULL		0x0003
#define	MR_ONLY		0x00ff

///////////////////////////////////////////////////////////
//	クラス宣言

class	afKey;
class	afJoykey;
class	afJoyKeyRep;
class	afMouse;

class	afPattern;

///////////////////////////////////////////////////////////
//	キークラス

class	afKey
{
	public:
		//	構築
		afKey(int);

		//	更新系
		void	UpdateKey();
		void	InvalidateKey();
		void	ResetKey();

		//	設定系
		void	SetKeyCode(int);

		//	取得系
		int	GetKey();

		//	演算子
		operator int();

	private:
		//	変数
		int		nCode;
		int		nState;
		bool	fInvalidate;
};

///////////////////////////////////////////////////////////
//	ジョイキークラス

class	afJoykey
{
	public:
		//	構築
		afJoykey();

		//	取得系
		int		GetJoykey();
		void	GetJoykey(int*,int*);
		int		GetJoykey4();
		void	GetJoykey4(int*,int*);
};

///////////////////////////////////////////////////////////
//	リピート対応ジョイキークラス

class	afJoykeyRep:public afJoykey
{
	public:
		//	構築
		afJoykeyRep();
		afJoykeyRep(int,int);

		//	更新系
		void	UpdateJoykey();
		void	ResetJoykey();

		//	設定系
		void	SetWait(int,int);

		//	取得系
		int		GetJoykey();
		void	GetJoykey(int*,int*);
		int		GetJoykey4();
		void	GetJoykey4(int*,int*);

	private:
		int	FWait,SWait;
		int	Count;
};

///////////////////////////////////////////////////////////
//	マウスクラス

class	afMouse
{
	public:
		//	構築
		afMouse();

		//	設定系
		void	SetPattern(afPattern*);
		void	SetHotSpot(int,int);

		//	取得系
		void	GetPos(int*,int*);
		int		GetKeyL();
		int		GetKeyR();
		int		GetKey();
		void	GetKey(int*,int*);

		//	更新系
		void	UpdateKey();
		void	UpdateKeyL();
		void	UpdateKeyR();
		void	InvalidateKey();
		void	InvalidateKeyL();
		void	InvalidateKeyR();
		void	ResetKey();
		void	ResetKeyL();
		void	ResetKeyR();

		//	表示系
		void	Show();

		//	演算子
		operator int();

	private:
		//	変数
		afPattern	*pPatMos;
		afKey		KeyL;
		afKey		KeyR;
		int			HX,HY;
};

#endif	//	_AFLINPUT_H_
