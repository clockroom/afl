//
//	AFL DC Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	(afGrpObject)
//		afDC
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	DCオブジェクト構築
//	引値	なし

afDC::afDC()
{
	hDC=NULL;
}

///////////////////////////////////////////////////////////
//	クリッパーを全画面に設定
//	引値	なし

void afDC::SetClipper()
{
	SelectClipRgn(hDC,NULL);
}

///////////////////////////////////////////////////////////
//	クリッパーを設定
//	引値	int		左上X座標
//			int		左上Y座標
//			int		右下X座標
//			int		右下Y座標

void afDC::SetClipper(int x1,int y1,int x2,int y2)
{
	HRGN	hrgn;

	hrgn=CreateRectRgn(x1,y1,x2,y2);
	SelectClipRgn(hDC,hrgn);
}

///////////////////////////////////////////////////////////
//	指定座標の色を取得 (afScreenには使用不可)
//	引値	int			X座標
//			int			Y座標
//	返値	COLORREF	色

COLORREF afDC::GetPixel(int x,int y)
{
	int	gx,gy;
	COLORREF	c;

	GetGroupPosByScreen(&gx,&gy);
	c=::GetPixel(hDC,gx+x,gy+y);

	return	c;
}

///////////////////////////////////////////////////////////
//	指定座標に点を表示
//	引値	int			X座標
//			int			Y座標
//			COLORREF	色

void afDC::Pixel(int x,int y,COLORREF c)
{
	int	gx,gy;

	GetGroupPosByScreen(&gx,&gy);
	c=::SetPixel(hDC,gx+x,gy+y,c);
}

///////////////////////////////////////////////////////////
//	文字列を表示
//	引値	int			X座標
//			int			Y座標
//			char*		文字列へのポインタ
//			int			文字サイズ
//			bool		太字(true=太字 or false=標準)
//			COLORREF	文字色

void afDC::Text(int x,int y,const char *str,int size,bool bold,COLORREF col)
{
	int		gx,gy;
	HFONT	hofont,hnfont;
	LOGFONT	lf;

	ZeroMemory(&lf,sizeof(LOGFONT));
	lf.lfHeight=size;
	lf.lfWidth=0;
	lf.lfCharSet=SHIFTJIS_CHARSET;
	strcpy(lf.lfFaceName,"標準ゴシック");

	hnfont=CreateFontIndirect(&lf);
	hofont=(HFONT)SelectObject(hDC,hnfont);

	SetBkMode(hDC,TRANSPARENT);
	SetTextColor(hDC,col);
	GetGroupPosByScreen(&gx,&gy);

	TextOut(hDC,gx+x,gy+y,str,strlen(str));
	if(bold) TextOut(hDC,gx+x+1,gy+y,str,strlen(str));

	SelectObject(hDC,hofont);
	DeleteObject(hnfont);
}

///////////////////////////////////////////////////////////
//	文字列を表示(影付き)
//	引値	int			X座標
//			int			Y座標
//			char*		文字列へのポインタ
//			int			文字サイズ
//			bool		太字(true=太字 or false=標準)
//			COLORREF	文字色
//			COLORREF	影色

void afDC::Text(int x,int y,const char *str,int size,bool bold,COLORREF col,COLORREF shc)
{
	int		gx,gy;
	HFONT	hofont,hnfont;
	LOGFONT	lf;

	ZeroMemory(&lf,sizeof(LOGFONT));
	lf.lfHeight=size;
	lf.lfWidth=0;
	lf.lfCharSet=SHIFTJIS_CHARSET;
	strcpy(lf.lfFaceName,"標準ゴシック");

	hnfont=CreateFontIndirect(&lf);
	hofont=(HFONT)SelectObject(hDC,hnfont);

	SetBkMode(hDC,TRANSPARENT);
	GetGroupPosByScreen(&gx,&gy);

	SetTextColor(hDC,shc);
	TextOut(hDC,gx+x+1,gy+y+1,str,strlen(str));
	if(bold) TextOut(hDC,gx+x+2,gy+y+1,str,strlen(str));

	SetTextColor(hDC,col);
	TextOut(hDC,gx+x,gy+y,str,strlen(str));
	if(bold) TextOut(hDC,gx+x+1,gy+y,str,strlen(str));

	SelectObject(hDC,hofont);
	DeleteObject(hnfont);
}

///////////////////////////////////////////////////////////
//	直線を表示
//	引値	int			開始X座標
//			int			開始Y座標
//			int			終了X座標
//			int			終了Y座標
//			int			線の太さ
//			COLORREF	線の色

void afDC::Line(int x1,int y1,int x2,int y2,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;

	hnpen=CreatePen(PS_SOLID,size,col);
	hopen=(HPEN)SelectObject(hDC,hnpen);

	GetGroupPosByScreen(&gx,&gy);
	MoveToEx(hDC,gx+x1,gy+y1,NULL);
	LineTo(hDC,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	DeleteObject(hnpen);
}

///////////////////////////////////////////////////////////
//	円を表示
//	引値	int			左上X座標
//			int			左上Y座標
//			int			右下X座標
//			int			右下Y座標
//			int			線の太さ
//			COLORREF	線の色

void afDC::Circle(int x1,int y1,int x2,int y2,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=(HBRUSH)GetStockObject(NULL_BRUSH);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Ellipse(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	円を表示
//	引値	int			左上X座標
//			int			左上Y座標
//			int			右下X座標
//			int			右下Y座標
//			int			線の太さ
//			COLORREF	線の色
//			COLORREF	中塗りの色

void afDC::Circle(int x1,int y1,int x2,int y2,int size,COLORREF col,COLORREF fill)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=CreateSolidBrush(fill);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Ellipse(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	四角形を表示
//	引値	int			左上X座標
//			int			左上Y座標
//			int			右下X座標
//			int			右下Y座標
//			int			線の太さ
//			COLORREF	線の色

void afDC::Box(int x1,int y1,int x2,int y2,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=(HBRUSH)GetStockObject(NULL_BRUSH);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Rectangle(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	四角形を表示
//	引値	int			左上X座標
//			int			左上Y座標
//			int			右下X座標
//			int			右下Y座標
//			int			線の太さ
//			COLORREF	線の色
//			COLORREF	中塗りの色

void afDC::Box(int x1,int y1,int x2,int y2,int size,COLORREF col,COLORREF fill)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=CreateSolidBrush(fill);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	Rectangle(hDC,gx+x1,gy+y1,gx+x2,gy+y2);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	三角形を表示
//	引値	int			第1X座標
//			int			第1Y座標
//			int			第2X座標
//			int			第2Y座標
//			int			第3X座標
//			int			第3Y座標
//			int			線の太さ
//			COLORREF	線の色

void afDC::Triangle(int x1,int y1,int x2,int y2,int x3,int y3,int size,COLORREF col)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;
	POINT	dpt[3];

	if(x1==y1 && x1==x2 && x1==y2 && x1==x3 && x1==y3)
	{
		Pixel(x1,y1,col);
		return;
	}

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=(HBRUSH)GetStockObject(NULL_BRUSH);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	dpt[0].x=gx+x1;
	dpt[0].y=gy+y1;
	dpt[1].x=gx+x2;
	dpt[1].y=gy+y2;
	dpt[2].x=gx+x3;
	dpt[2].y=gy+y3;
	Polygon(hDC,dpt,3);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	三角形を表示
//	引値	int			第1X座標
//			int			第1Y座標
//			int			第2X座標
//			int			第2Y座標
//			int			第3X座標
//			int			第3Y座標
//			int			線の太さ
//			COLORREF	線の色
//			COLORREF	中塗りの色

void afDC::Triangle(int x1,int y1,int x2,int y2,int x3,int y3,int size,COLORREF col,COLORREF fill)
{
	int		gx,gy;
	HPEN	hopen,hnpen;
	HBRUSH	hobrs,hnbrs;
	POINT	dpt[3];

	if(x1==y1 && x1==x2 && x1==y2 && x1==x3 && x1==y3)
	{
		Pixel(x1,y1,col);
		return;
	}

	hnpen=CreatePen(PS_SOLID,size,col);
	hnbrs=CreateSolidBrush(fill);
	hopen=(HPEN)SelectObject(hDC,hnpen);
	hobrs=(HBRUSH)SelectObject(hDC,hnbrs);

	GetGroupPosByScreen(&gx,&gy);
	dpt[0].x=gx+x1;
	dpt[0].y=gy+y1;
	dpt[1].x=gx+x2;
	dpt[1].y=gy+y2;
	dpt[2].x=gx+x3;
	dpt[2].y=gy+y3;
	Polygon(hDC,dpt,3);

	SelectObject(hDC,hopen);
	SelectObject(hDC,hobrs);
	DeleteObject(hnpen);
	DeleteObject(hnbrs);
}

///////////////////////////////////////////////////////////
//	(HDC)変換演算子
//	引値	なし

afDC::operator HDC()
{
	return	hDC;
}
