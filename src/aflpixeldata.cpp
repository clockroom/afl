//
//	AFL Pixel Data Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	(afGrpObject)
//		afPixelData
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	ピクセルデータオブジェクト構築
//	引値	なし

afPixelData::afPixelData()
{
	pPixel=NULL;
	Pitch=0;
}

///////////////////////////////////////////////////////////
//	指定座標に指定の色を設定
//	引値	int		X座標
//			int		Y座標
//			WORD	色

void afPixelData::SetPixel(int x,int y,WORD col)
{
	WORD	*p;
	int		gx,gy;

	if(pPixel==NULL)	return;

	GetGroupPosByScreen(&gx,&gy);
	p=pPixel+(gy+y)*Pitch+(gx+x);
	*p=col;
}

///////////////////////////////////////////////////////////
//	データのアドレスを取得
//	引値	WORD**	アドレスを格納するポインタのアドレス
//			int*	ピッチを格納する変数のアドレス

void afPixelData::GetAddress(WORD **add,int *pt)
{
	*add=pPixel;
	*pt	=Pitch;
}

///////////////////////////////////////////////////////////
//	指定座標の色を取得
//	引値	int		X座標
//			int		Y座標
//	返値	WORD	色

WORD afPixelData::GetPixel(int x,int y)
{
	WORD	*p;
	int		gx,gy;

	if(pPixel==NULL)	return 0;

	GetGroupPosByScreen(&gx,&gy);
	p=pPixel+(gy+y)*Pitch+(gx+x);

	return *p;
}
