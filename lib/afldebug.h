//
//	AFL Debug by ClockRoom 2002
//	Program by Y.Kumagai ClockRoom 2002
//
//	First Edition 2002/01/06
//	Last  Edition 2002/01/06
//

#ifndef _AFLDEBUG_H_
#define _AFLDEBUG_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <aflinclude.h>

///////////////////////////////////////////////////////////
//	クラス

class afDebugQueue;

///////////////////////////////////////////////////////////
//	クラス

class afDebugQueue
{
	public:
		//	構築系
		afDebugQueue();
		~afDebugQueue();

		//	作成系
		void ClearQueue();

		//	設定系
		void SetShowState(int,int,COLORREF);

		//	操作系
		void PostString(const char*,...);
		void Show();

	private:
		//	変数
		char **pdpsString;
		int  cString;
		int  PosX,PosY;
		COLORREF ColorText;
};

#endif	//	_AFLDEBUG_H_
