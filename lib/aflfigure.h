//
//	AFL Figure by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

#ifndef	_AFLFIGURE_H_
#define	_AFLFIGURE_H_

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	クラス宣言

class afPoint;
class afRect;

///////////////////////////////////////////////////////////
//	点クラス

class afPoint:public POINT
{
	public:
		//	構築
		afPoint();
		afPoint(int,int);

		//	設定系
		void	SetPoint(int,int);

		//	取得系
		void	GetPoint(int*,int*);

		//	移動系
		void	Move(int,int);
};

///////////////////////////////////////////////////////////
//	四角形クラス

class afRect:public	RECT
{
	public:
		//	構築
		afRect();
		afRect(int,int,int,int);

		//	設定系
		void	SetRect(int,int,int,int);

		//	取得系
		void	GetRect(int*,int*,int*,int*);

		//	移動系
		void	Move(int,int);
};

#endif	//	_AFLFIGURE_H_
