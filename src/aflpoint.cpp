//
//	AFL Point Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afPoint
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflfigure.h"

///////////////////////////////////////////////////////////
//	点オブジェクト構築
//	引値	なし

afPoint::afPoint()
{
	x=0;
	y=0;
}

///////////////////////////////////////////////////////////
//	点オブジェクト構築
//	引値	int		X座標
//			int		Y座標

afPoint::afPoint(int a,int b)
{
	x=a;
	y=b;
}

///////////////////////////////////////////////////////////
//	点設定
//	引値	int		X座標
//			int		Y座標

void afPoint::SetPoint(int a,int b)
{
	x=a;
	y=b;
}

///////////////////////////////////////////////////////////
//	点取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void afPoint::GetPoint(int *px,int *py)
{
	if(px!=NULL) *px=x;
	if(py!=NULL) *py=y;
}

///////////////////////////////////////////////////////////
//	点を相対移動
//	引値	int		X移動量
//			int		Y移動量

void afPoint::Move(int mx,int my)
{
	x+=mx;
	y+=my;
}
