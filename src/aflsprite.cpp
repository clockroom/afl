//
//	AFL Sprite Class by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	(afGrpGroup)
//		afSprite
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflgraphics.h"

///////////////////////////////////////////////////////////
//	スプライトオブジェクト構築
//	引値	なし

afSprite::afSprite()
{
	int	i;

	pPattern=NULL;

	MX=0;
	MY=0;
	OX=0;
	OY=0;

	nOrigin=ORG_LEFTTOP;
	nStyle =SPR_NORMAL;

	for(i=0;i<8;i++) dParam[i]=0;

	fShow=false;
}

///////////////////////////////////////////////////////////
//	スプライト作成
//	引値	afPattern*	afPatternオブジェクトへのポインタ
//			int			初期X座標
//			int			初期Y座標

void afSprite::CreateSprite(afPattern *p,int x,int y)
{
	int	i;

	pPattern=p;

	SetPos(x,y);
	MX=0;
	MY=0;
	OX=0;
	OY=0;

	nOrigin=ORG_LEFTTOP;
	nStyle =SPR_NORMAL;

	for(i=0;i<8;i++) dParam[i]=0;

	fShow=true;
}

///////////////////////////////////////////////////////////
//	パターン設定
//	引値	afPattern*	afPatternオブジェクトへのポインタ

void afSprite::SetPattern(afPattern *p)
{
	pPattern=p;
}

///////////////////////////////////////////////////////////
//	表示設定
//	引値	bool	true	表示
//					false	非表示

void afSprite::SetShow(bool f)
{
	fShow=f;
}

///////////////////////////////////////////////////////////
//	表示方法設定
//	引値	int		表示方法
//						SPR_NORMAL		ノーマル
//						SPR_OPAQUE		透明色無視
//						SPR_BLEND50		50%混合
//						SPR_BLEND		比率指定混合
//							P1=割合(0-64)
//						SPR_BLENDRGB	RGB比率指定混合
//							P1=R割合(0-64)
//							P2=G割合(0-64)
//							P3=B割合(0-64)
//						SPR_ADD			加算合成
//						SPR_SUBTRACT	減算合成
//						SPR_STRETCH		拡大縮小
//							P1=変換後W
//							P2=変換後H
//						SPR_ADDBRIGHT	加算調光合成
//							P1=割合(0 - 64)
//						SPR_SUBBRIGHT	減算調光合成
//							P1=割合(0 - 64)
//	(P1,P2,P3 は afSprite::SetParam() 関数で設定)

void afSprite::SetStyle(int s)
{
	nStyle=s;
}

///////////////////////////////////////////////////////////
//	パラメータ設定
//	引値	int		パラメータ1
//			int		パラメータ2(省略=0)
//			int		パラメータ3(省略=0)
//			int		パラメータ4(省略=0)

void afSprite::SetParam(int a,int b,int c,int d)
{
	dParam[0]=a;
	dParam[1]=b;
	dParam[2]=c;
	dParam[3]=d;
}

///////////////////////////////////////////////////////////
//	パラメータ設定
//	引値	int		インデックス(0-7)
//			int		パラメータ

void afSprite::SetParam(int n,int p)
{
	dParam[n]=p;
}

///////////////////////////////////////////////////////////
//	パラメータ加算
//	引値	int		パラメータ1
//			int		パラメータ2(省略=0)
//			int		パラメータ3(省略=0)
//			int		パラメータ4(省略=0)

void afSprite::AddParam(int a,int b,int c,int d)
{
	dParam[0]+=a;
	dParam[1]+=b;
	dParam[2]+=c;
	dParam[3]+=d;
}

///////////////////////////////////////////////////////////
//	パラメータ加算
//	引値	int		インデックス
//			int		パラメータ

void afSprite::AddParam(int n,int p)
{
	dParam[n]+=p;
}

///////////////////////////////////////////////////////////
//	移動量設定
//	引値	int		X移動量
//			int		Y移動量

void afSprite::SetMove(int x,int y)
{
	MX=x;
	MY=y;
}

///////////////////////////////////////////////////////////
//	移動量加算
//	引値	int		X移動量
//			int		Y移動量

void afSprite::AddMove(int x,int y)
{
	MX+=x;
	MY+=y;
}

///////////////////////////////////////////////////////////
//	逆方向移動設定
//	引値	bool	X移動量逆転	false	保持
//								true	逆転
//			bool	Y移動量逆転	false	保持
//								true	逆転

void afSprite::ReverseMove(bool fx,bool fy)
{
	MX*=(fx?-1:1);
	MY*=(fy?-1:1);
}

///////////////////////////////////////////////////////////
//	原点を設定
//	引値	int		基準
//						ORG_LEFTTOP			左上を基準
//						ORG_LEFTCENTER		左中央を基準
//						ORG_LEFTBOTTOM		左下を基準
//						ORG_RIGHTTOP		右上を基準
//						ORG_RIGHTCENTER		右中央を基準
//						ORG_RIGHTBOTTM		右下を基準
//						ORG_CENTERTOP		中央上を基準
//						ORG_CENTER			中央を基準
//						ORG_CENTERBOTTOM	中央下を基準
//			int		基準からのX座標
//			int		基準からのY座標

void afSprite::SetOrigin(int n,int x,int y)
{
	nOrigin=n;
	OX=x;
	OY=y;
}

///////////////////////////////////////////////////////////
//	スプライトの左上の位置を取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void	afSprite::GetPosLeftTop(int *px,int *py)
{
	int	x,y;
	int	w,h;

	if(pPattern==NULL)
	{
		GetPos(px,py);
		return;
	}

	w=pPattern->W;
	h=pPattern->H;

	switch(nOrigin)
	{
	case ORG_LEFTTOP:		x=0;		y=0;		break;
	case ORG_LEFTCENTER:	x=0;		y=(h>>1);	break;
	case ORG_LEFTBOTTOM:	x=0;		y=h;		break;
	case ORG_RIGHTTOP:		x=w;		y=0;		break;
	case ORG_RIGHTCENTER:	x=w;		y=(h>>1);	break;
	case ORG_RIGHTBOTTOM:	x=w;		y=h;		break;
	case ORG_CENTERTOP:		x=(w>>1);	y=0;		break;
	case ORG_CENTER:		x=(w>>1);	y=(h>>1);	break;
	case ORG_CENTERBOTTOM:	x=(w>>1);	y=h;		break;
	}

	if(px!=NULL) *px=X-x-OX;
	if(py!=NULL) *py=Y-y-OY;
}

///////////////////////////////////////////////////////////
//	スプライトの左上の位置をスクリーン座標で取得
//	引値	int*	X座標を格納する変数のアドレス
//			int*	Y座標を格納する変数のアドレス

void afSprite::GetPosLeftTopByScreen(int *px,int *py)
{
	int	gx,gy;

	GetPosLeftTop(px,py);
	GetGroupPosByScreen(&gx,&gy);

	if(px!=NULL) *px+=gx;
	if(py!=NULL) *py+=gy;
}

///////////////////////////////////////////////////////////
//	スプライトの表示状態を取得
//	引値	なし
//	返値	bool	true	表示
//					false	非表示

bool afSprite::IsShow()
{
	return fShow;
}

///////////////////////////////////////////////////////////
//	パラメータを取得
//	引値	int*	パラメータ1を格納する変数のアドレス
//			int*	パラメータ2を格納する変数のアドレス
//			int*	パラメータ3を格納する変数のアドレス
//			int*	パラメータ4を格納する変数のアドレス

void afSprite::GetParam(int *pa,int *pb,int *pc,int *pd)
{
	if(pa!=NULL) *pa=dParam[0];
	if(pb!=NULL) *pb=dParam[1];
	if(pc!=NULL) *pc=dParam[2];
	if(pd!=NULL) *pd=dParam[3];
}

///////////////////////////////////////////////////////////
//	パラメータ取得
//	引値	int*	パラメータを格納する変数のアドレス
//			int		インデックス

void afSprite::GetParam(int *p,int n)
{
	if(p!=NULL) *p=dParam[n];
}

///////////////////////////////////////////////////////////
//	パラメータ取得
//	引値	なし
//	返値	パラメータ配列へのポインタ

int *afSprite::GetParam()
{
	return dParam;
}

///////////////////////////////////////////////////////////
//	移動量だけ移動
//	引値	なし

void afSprite::Move()
{
	X+=MX;
	Y+=MY;
}

///////////////////////////////////////////////////////////
//	指定量だけ相対移動
//	引値	int		X移動量
//			int		Y移動量

void afSprite::Move(int x,int y)
{
	X+=x;
	Y+=y;
}

///////////////////////////////////////////////////////////
//	スプライトを表示
//	引値	なし

void afSprite::Show()
{
	afGrpGroup	*pg;
	afBitmap	*pb;

	int	dx,dy;
	int	sx,sy,sw,sh;

	int	a=dParam[0];
	int	b=dParam[1];
	int	c=dParam[2];

	if(!fShow)		   return;
	if(pPattern==NULL) return;

	pb=pPattern->pBitmap;

	if(pb==NULL) return;

	sx=pPattern->X;
	sy=pPattern->Y;
	sw=pPattern->W;
	sh=pPattern->H;

	GetPosLeftTop(&dx,&dy);

	pg=pb->SetGroup(pGroup);
	switch(nStyle)
	{
	case SPR_NORMAL:   pb->Put      (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_BLEND50:  pb->Blend    (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_BLEND:	   pb->Blend    (dx,dy,a    ,sx,sy,sw,sh);break;
	case SPR_BLENDRGB: pb->Blend    (dx,dy,a,b,c,sx,sy,sw,sh);break;
	case SPR_ADD:	   pb->Add      (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_SUBTRACT: pb->Subtract (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_STRETCH:  pb->Stretch  (dx,dy,a,b  ,sx,sy,sw,sh);break;
	case SPR_OPAQUE:   pb->Opaque   (dx,dy      ,sx,sy,sw,sh);break;
	case SPR_ADDBRIGHT:pb->AddBright(dx,dy,a    ,sx,sy,sw,sh);break;
	case SPR_SUBBRIGHT:pb->SubBright(dx,dy,a    ,sx,sy,sw,sh);break;
	case SPR_MULTIPLY: pb->Multiply (dx,dy      ,sx,sy,sw,sh);break;
	}
	pb->SetGroup(pg);
}
