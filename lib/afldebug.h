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
//	�C���N���[�h

#include <aflinclude.h>

///////////////////////////////////////////////////////////
//	�N���X

class afDebugQueue;

///////////////////////////////////////////////////////////
//	�N���X

class afDebugQueue
{
	public:
		//	�\�z�n
		afDebugQueue();
		~afDebugQueue();

		//	�쐬�n
		void ClearQueue();

		//	�ݒ�n
		void SetShowState(int,int,COLORREF);

		//	����n
		void PostString(const char*,...);
		void Show();

	private:
		//	�ϐ�
		char **pdpsString;
		int  cString;
		int  PosX,PosY;
		COLORREF ColorText;
};

#endif	//	_AFLDEBUG_H_
