//
//	AFL Application by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//

#ifndef _AFLAPP_H_
#define _AFLAPP_H_

///////////////////////////////////////////////////////////
//	�萔��`

#define APP_INIT	1
#define APP_FINAL	2
#define APP_MAIN	3
#define	APP_USER	4

///////////////////////////////////////////////////////////
//	�N���X�錾

class afApp;

///////////////////////////////////////////////////////////
//	�A�v���P�[�V�����N���X

class afApp
{
	public:
		//	�\�z�n
		afApp();
		virtual	~afApp();

		//	�V�X�e���n
		bool			DefAppSwitch(int);
		virtual bool	AppSwitch(int);

		//	�����n
		virtual void	InitApp();
		virtual void	FinalApp();
		virtual void	Main();
};

#endif	//	_AFLAPP_H_
