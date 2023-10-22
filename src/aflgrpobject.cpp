//
//	AFL Graphic Object Class ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/30
//	Last  Edition 2001/09/30
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	グラフィックオブジェクト構築
//	引値	なし

afGrpObject::afGrpObject()
{
	pGroup=NULL;
}

///////////////////////////////////////////////////////////
//	グラフィックオブジェクト破棄

afGrpObject::~afGrpObject()
{
}

///////////////////////////////////////////////////////////
//	所属グループを設定
//	引値	afGrpGroup*	グループオブジェクトのアドレス
//	返値	afGrpGroup*	設定前のグループオブジェクトのアドレス

afGrpGroup *afGrpObject::SetGroup(afGrpGroup *p)
{
	afGrpGroup	*pold=pGroup;

	pGroup=p;

	return pold;
}

///////////////////////////////////////////////////////////
//	所属グループの位置を取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void afGrpObject::GetGroupPos(int *px,int *py)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetPos(px,py);
}

///////////////////////////////////////////////////////////
//	所属グループの位置をスクリーン座標で取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void afGrpObject::GetGroupPosByScreen(int *px,int *py)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetPosByScreen(px,py);
}

///////////////////////////////////////////////////////////
//	ルートグループの位置を取得
//
//	引値 int*	X座標を格納する変数のアドレス
//		 int*	Y座標を格納する変数のアドレス
//
//	返値 なし

void afGrpObject::GetRootGroupPos(int* px,int* py)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
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

void afGrpObject::GetMarkedGroupPos(int *px,int *py,int n)
{
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

void afGrpObject::GetMarkedGroupPosByScreen(int *px,int *py,int n)
{
	if(pGroup==NULL)
	{
		if(px!=NULL) *px=0;
		if(py!=NULL) *py=0;
		return;
	}

	pGroup->GetMarkedGroupPosByScreen(px,py,n);
}
