//
//	AFL Rect Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afRect
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflfigure.h"

///////////////////////////////////////////////////////////
//	四角形オブジェクト構築
//	引値	なし

afRect::afRect()
{
	left=0;
	right=0;
	top=0;
	bottom=0;
}

///////////////////////////////////////////////////////////
//	四角形オブジェクト構築
//	引値	int		X座標
//			int		Y座標
//			int		幅
//			int		高さ

afRect::afRect(int x,int y,int w,int h)
{
	left=x;
	right=x+w;
	top=y;
	bottom=y+h;
}

///////////////////////////////////////////////////////////
//	四角形設定
//	引値	int		X座標
//			int		Y座標
//			int		幅
//			int		高さ

void afRect::SetRect(int x,int y,int w,int h)
{
	left=x;
	right=x+w;
	top=y;
	bottom=y+h;
}

///////////////////////////////////////////////////////////
//	四角形取得
//	引値	int*	X座標を格納する変数へのポインタ
//			int*	Y座標を格納する変数へのポインタ
//			int*	幅を格納する変数へのポインタ
//			int*	高さを格納する変数へのポインタ

void afRect::GetRect(int *px,int *py,int *pw,int *ph)
{
	if(px!=NULL) *px=left;
	if(py!=NULL) *py=top;
	if(pw!=NULL) *pw=right-left;
	if(ph!=NULL) *ph=bottom-top;
}

///////////////////////////////////////////////////////////
//	四角形を移動
//	引値	int		X移動量
//			int		Y移動量

void afRect::Move(int mx,int my)
{
	left+=mx;
	right+=mx;
	top+=my;
	bottom+=my;
}
