//
//	AFL Figure by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef	_AFLFIGURE_H_
#define	_AFLFIGURE_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	�N���X�錾

class afPoint;
class afRect;

///////////////////////////////////////////////////////////
//	�_�N���X

class afPoint:public POINT
{
	public:
		//	�\�z
		afPoint();
		afPoint(int,int);

		//	�ݒ�n
		void	SetPoint(int,int);

		//	�擾�n
		void	GetPoint(int*,int*);

		//	�ړ��n
		void	Move(int,int);
};

///////////////////////////////////////////////////////////
//	�l�p�`�N���X

class afRect:public	RECT
{
	public:
		//	�\�z
		afRect();
		afRect(int,int,int,int);

		//	�ݒ�n
		void	SetRect(int,int,int,int);

		//	�擾�n
		void	GetRect(int*,int*,int*,int*);

		//	�ړ��n
		void	Move(int,int);
};

#endif	//	_AFLFIGURE_H_
