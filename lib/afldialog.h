//
//	AFL Dialog by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef _AFLDIALOG_H_
#define _AFLDIALOG_H_

///////////////////////////////////////////////////////////
//	�N���X�錾

class afMsgBox;
class afErrorBox;
class afFileBox;

///////////////////////////////////////////////////////////
//	�萔��`

#define MB_INFORMATION	0
#define MB_QUESTION		1
#define FB_OPEN	0
#define FB_SAVE	1

///////////////////////////////////////////////////////////
//	���b�Z�[�W�{�b�N�X�N���X

class afMsgBox
{
	public:
		//	�\�z
		afMsgBox(int);
		~afMsgBox();

		//	�ݒ�n
		void	SetTitle(const char*);
		void	SetMessage(const char*);

		//	�\���n
		int		OpenBox();

	private:
		//	�ϐ�
		int		nStyle;
		char	*dTitle;
		char	*dMessage;
};

///////////////////////////////////////////////////////////
//	�G���[�{�b�N�X�N���X

class afErrorBox
{
	public:
		//	�\�z
		afErrorBox();
		~afErrorBox();

		//	�ݒ�n
		void	SetTitle(const char*);
		void	SetFileName(const char*);
		void	SetFunctionName(const char*);
		void	SetMessage(const char*);
		void	SetRepair(const char*);

		//	�\���n
		int		OpenBox();

	private:
		//	�ϐ�
		char	*dTitle;
		char	*dFileName;
		char	*dFunctionName;
		char	*dMessage;
		char	*dRepair;
};

///////////////////////////////////////////////////////////
//	�t�@�C���{�b�N�X�N���X

class afFileBox
{
	public:
		//	�\�z
		afFileBox(int);
		~afFileBox();

		//	�ݒ�n
		void	SetTitle(const char*);
		void	AddFilter(const char*,const char*);
		void	SetDefExt(const char*);
		void	SetInitialDir(const char*);

		//	�擾�n
		void	GetFileName(char*);

		//	�\���n
		int		OpenBox();

	private:
		//	�ϐ�
		int		nStyle;
		char	*dTitle;
		char	*dFilter;
		char	*dDefExt;
		char	*dInitDir;
		char	*dFileName;
};

#endif	//	_AFLDIALOG_H_
