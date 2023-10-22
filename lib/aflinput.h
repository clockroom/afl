//
//	AFL Input by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef	_AFLINPUT_H_
#define	_AFLINPUT_H_

///////////////////////////////////////////////////////////
//	�萔��`

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
//	�N���X�錾

class	afKey;
class	afJoykey;
class	afJoyKeyRep;
class	afMouse;

class	afPattern;

///////////////////////////////////////////////////////////
//	�L�[�N���X

class	afKey
{
	public:
		//	�\�z
		afKey(int);

		//	�X�V�n
		void	UpdateKey();
		void	InvalidateKey();
		void	ResetKey();

		//	�ݒ�n
		void	SetKeyCode(int);

		//	�擾�n
		int	GetKey();

		//	���Z�q
		operator int();

	private:
		//	�ϐ�
		int		nCode;
		int		nState;
		bool	fInvalidate;
};

///////////////////////////////////////////////////////////
//	�W���C�L�[�N���X

class	afJoykey
{
	public:
		//	�\�z
		afJoykey();

		//	�擾�n
		int		GetJoykey();
		void	GetJoykey(int*,int*);
		int		GetJoykey4();
		void	GetJoykey4(int*,int*);
};

///////////////////////////////////////////////////////////
//	���s�[�g�Ή��W���C�L�[�N���X

class	afJoykeyRep:public afJoykey
{
	public:
		//	�\�z
		afJoykeyRep();
		afJoykeyRep(int,int);

		//	�X�V�n
		void	UpdateJoykey();
		void	ResetJoykey();

		//	�ݒ�n
		void	SetWait(int,int);

		//	�擾�n
		int		GetJoykey();
		void	GetJoykey(int*,int*);
		int		GetJoykey4();
		void	GetJoykey4(int*,int*);

	private:
		int	FWait,SWait;
		int	Count;
};

///////////////////////////////////////////////////////////
//	�}�E�X�N���X

class	afMouse
{
	public:
		//	�\�z
		afMouse();

		//	�ݒ�n
		void	SetPattern(afPattern*);
		void	SetHotSpot(int,int);

		//	�擾�n
		void	GetPos(int*,int*);
		int		GetKeyL();
		int		GetKeyR();
		int		GetKey();
		void	GetKey(int*,int*);

		//	�X�V�n
		void	UpdateKey();
		void	UpdateKeyL();
		void	UpdateKeyR();
		void	InvalidateKey();
		void	InvalidateKeyL();
		void	InvalidateKeyR();
		void	ResetKey();
		void	ResetKeyL();
		void	ResetKeyR();

		//	�\���n
		void	Show();

		//	���Z�q
		operator int();

	private:
		//	�ϐ�
		afPattern	*pPatMos;
		afKey		KeyL;
		afKey		KeyR;
		int			HX,HY;
};

#endif	//	_AFLINPUT_H_
