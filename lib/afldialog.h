//
//	AFL Dialog by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef _AFLDIALOG_H_
#define _AFLDIALOG_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class afMsgBox;
class afErrorBox;
class afFileBox;

///////////////////////////////////////////////////////////
//	定数定義

#define MB_INFORMATION	0
#define MB_QUESTION		1
#define FB_OPEN	0
#define FB_SAVE	1

///////////////////////////////////////////////////////////
//	メッセージボックスクラス

class afMsgBox
{
	public:
		//	構築
		afMsgBox(int);
		~afMsgBox();

		//	設定系
		void	SetTitle(const char*);
		void	SetMessage(const char*);

		//	表示系
		int		OpenBox();

	private:
		//	変数
		int		nStyle;
		char	*dTitle;
		char	*dMessage;
};

///////////////////////////////////////////////////////////
//	エラーボックスクラス

class afErrorBox
{
	public:
		//	構築
		afErrorBox();
		~afErrorBox();

		//	設定系
		void	SetTitle(const char*);
		void	SetFileName(const char*);
		void	SetFunctionName(const char*);
		void	SetMessage(const char*);
		void	SetRepair(const char*);

		//	表示系
		int		OpenBox();

	private:
		//	変数
		char	*dTitle;
		char	*dFileName;
		char	*dFunctionName;
		char	*dMessage;
		char	*dRepair;
};

///////////////////////////////////////////////////////////
//	ファイルボックスクラス

class afFileBox
{
	public:
		//	構築
		afFileBox(int);
		~afFileBox();

		//	設定系
		void	SetTitle(const char*);
		void	AddFilter(const char*,const char*);
		void	SetDefExt(const char*);
		void	SetInitialDir(const char*);

		//	取得系
		void	GetFileName(char*);

		//	表示系
		int		OpenBox();

	private:
		//	変数
		int		nStyle;
		char	*dTitle;
		char	*dFilter;
		char	*dDefExt;
		char	*dInitDir;
		char	*dFileName;
};

#endif	//	_AFLDIALOG_H_
