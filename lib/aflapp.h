//
//	AFL Application by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//

#ifndef _AFLAPP_H_
#define _AFLAPP_H_

///////////////////////////////////////////////////////////
//	定数定義

#define APP_INIT	1
#define APP_FINAL	2
#define APP_MAIN	3
#define	APP_USER	4

///////////////////////////////////////////////////////////
//	クラス宣言

class afApp;

///////////////////////////////////////////////////////////
//	アプリケーションクラス

class afApp
{
	public:
		//	構築系
		afApp();
		virtual	~afApp();

		//	システム系
		bool			DefAppSwitch(int);
		virtual bool	AppSwitch(int);

		//	処理系
		virtual void	InitApp();
		virtual void	FinalApp();
		virtual void	Main();
};

#endif	//	_AFLAPP_H_
