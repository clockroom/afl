//
//	AFL Graphic Group Class ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/30
//	Last  Edition 2001/09/30
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	グラフィックグループオブジェクト構築
//	引値	なし

afGrpGroup::afGrpGroup()
{
	X=0;
	Y=0;
	nMarker=NULL;
}

///////////////////////////////////////////////////////////
//	位置設定
//	引値	int		X座標
//			int		Y座標

void afGrpGroup::SetPos(int x,int y)
{
	X=x;
	Y=y;
}

///////////////////////////////////////////////////////////
//	マーカを設定
//
//	引値 int	マーカ
//
//	返値 なし

void afGrpGroup::SetMarker(int n)
{
	nMarker=n;
}

///////////////////////////////////////////////////////////
//	位置取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void afGrpGroup::GetPos(int *px,int *py)
{
	if(px!=NULL) *px=X;
	if(py!=NULL) *py=Y;
}

///////////////////////////////////////////////////////////
//	指定オブジェクトを基準とした位置取得
//	引値	int*		X座標を格納する変数のアドレス
//			int*		Y座標を格納する変数のアドレス
//			afGrpGroup*	基準オブジェクトへポインタ

void afGrpGroup::GetPos(int *px,int *py,afGrpGroup *pg)
{
	int	ax,ay,bx,by;

	GetPosByScreen(&ax,&ay);
	if(pg!=NULL) {pg->GetPosByScreen(&bx,&by);}
	else		 {bx=0; by=0;}

	if(px!=NULL) *px=ax-bx;
	if(py!=NULL) *py=ay-by;
}

///////////////////////////////////////////////////////////
//	オブジェクトの位置をスクリーン座標で取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void afGrpGroup::GetPosByScreen(int *px,int *py)
{
	GetGroupPosByScreen(px,py);
	if(px!=NULL) *px+=X;
	if(py!=NULL) *py+=Y;
}

///////////////////////////////////////////////////////////
//	ルートグループの位置を取得
//
//	引値 int*	X座標を格納する変数のアドレス
//		 int*	Y座標を格納する変数のアドレス
//
//	返値 なし

void afGrpGroup::GetRootGroupPos(int* px,int* py)
{
	if(pGroup==NULL || nMarker==MARKER_ROOTGROUP)
	{
		GetPosByScreen(px,py);
		return;
	}

	pGroup->GetRootGroupPos(px,py);
}

///////////////////////////////////////////////////////////
//	マークされたグループの位置を取得
//
//	引値 int*	Ｘ座標を格納する変数のアドレス
//		 int*	Ｙ座標を格納する変数のアドレス
//		 int	マーカ
//
//	返値 なし

void afGrpGroup::GetMarkedGroupPos(int *px,int *py,int n)
{
	if(nMarker==n)
	{
		GetPos(px,py);
		return;
	}

	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetMarkedGroupPos(px,py,n);
}

///////////////////////////////////////////////////////////
//	マークされたグループの位置をスクリーン座標で取得
//
//	引値 int*	Ｘ座標を格納する変数のアドレス
//		 int*	Ｙ座標を格納する変数のアドレス
//		 int	マーカ
//
//	返値 なし

void afGrpGroup::GetMarkedGroupPosByScreen(int *px,int *py,int n)
{
	if(nMarker==n)
	{
		GetPosByScreen(px,py);
		return;
	}

	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetMarkedGroupPosByScreen(px,py,n);
}
