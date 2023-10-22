//
//	AFL Pattern Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	(afGrpObject)
//		afPattern
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	パターンオブジェクト構築
//	引値	なし

afPattern::afPattern()
{
	pBitmap=NULL;
	X=0;
	Y=0;
	W=0;
	H=0;
}

///////////////////////////////////////////////////////////
//	パターン作成
//	引値	afBitmap*	afBitmapオブジェクトへのポインタ
//			int			X座標
//			int			Y座標
//			int			幅
//			int			高さ

void afPattern::CreatePattern(afBitmap *p,int x,int y,int w,int h)
{
	pBitmap=p;
	X=x;
	Y=y;
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	パターンを設定
//	引値	afBitmap*	afBitmapオブジェクトへのポインタ
//			int			X座標
//			int			Y座標
//			int			幅
//			int			高さ

void afPattern::SetPattern(afBitmap *p,int x,int y,int w,int h)
{
	pBitmap=p;
	X=x;
	Y=y;
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	パターンを設定
//	引値	int		X座標
//			int		Y座標
//			int		幅
//			int		高さ

void afPattern::SetPattern(int x,int y,int w,int h)
{
	X=x;
	Y=y;
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	パターンの位置を設定
//	引値	int		X座標
//			int		Y座標

void afPattern::SetPatternPos(int x,int y)
{
	X=x;
	Y=y;
}

///////////////////////////////////////////////////////////
//	パターンサイズを設定
//	引値	int		幅
//			int		高さ

void afPattern::SetPatternSize(int w,int h)
{
	W=w;
	H=h;
}

///////////////////////////////////////////////////////////
//	パターンの位置を相対移動
//	引値	int		X移動量
//			int		Y移動量

void afPattern::MovePattern(int x,int y)
{
	X+=x;
	Y+=y;
}

///////////////////////////////////////////////////////////
//	パターンを表示
//	引値	int		X座標
//			int		Y座標

void afPattern::Put(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Put(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを透明色を無視して表示
//	引値	int		X座標
//			int		Y座標

void afPattern::Opaque(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Opaque(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを半透明で表示
//	引値	int		X座標
//			int		Y座標

void afPattern::Blend(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Blend(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを加算半透明で表示
//	引値	int		X座標
//			int		Y座標

void afPattern::Add(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Add(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを加算調光で表示
//	引値	int		X座標
//			int		Y座標
//			int		調光率

void afPattern::AddBright(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->AddBright(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを減算半透明で表示
//	引値	int		X座標
//			int		Y座標

void afPattern::Subtract(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Subtract(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを減算調光で表示
//	引値	int		X座標
//			int		Y座標
//			int		調光率

void afPattern::SubBright(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->SubBright(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを乗算半透明で表示
//	引値	int		X座標
//			int		Y座標
//			int		調光率

void afPattern::Multiply(int x,int y)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Multiply(x,y,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを調光で表示
//	引値	int		X座標
//			int		Y座標
//			int		調光率

void afPattern::Bright(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Bright(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを透明色無視で調光表示
//	引値	int		X座標
//			int		Y座標
//			int		調光率

void afPattern::BrightOpaque(int x,int y,int b)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->BrightOpaque(x,y,b,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを拡縮表示
//	引値	int		X座標
//			int		Y座標
//			int		幅
//			int		高さ

void afPattern::Stretch(int x,int y,int w,int h)
{
	afGrpGroup	*p;

	p=pBitmap->SetGroup(pGroup);
	pBitmap->Stretch(x,y,w,h,X,Y,W,H);
	pBitmap->SetGroup(p);
}

///////////////////////////////////////////////////////////
//	パターンを透明色を無視してならべて表示
//	引値	int		X座標
//			int		Y座標
//			int		幅
//			int		高さ

void afPattern::TileOpaque(int x,int y,int w,int h)
{
	afGrpGroup	*p;
	int	i,j,a,b;

	p=pBitmap->SetGroup(pGroup);
	for(j=0;j<h;j+=H)
		for(i=0;i<w;i+=W)
		{
			a=(w<i+W)?w%W:W;
			b=(h<j+H)?h%H:H;
			pBitmap->Opaque(x+i,y+j,X,Y,a,b);
		}
	pBitmap->SetGroup(p);
}
