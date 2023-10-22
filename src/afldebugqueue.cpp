//
//	AFL Debug Queue Class by ClockRoom 2002
//	Program by Y.Kumagai ClockRoom 2002
//
//	First Edition 2002/01/06
//	Last  Edition 2002/01/06
//
//	afDebugQueue
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afldefine.h>
#include <aflgraphics.h>
#include <afldebug.h>

///////////////////////////////////////////////////////////
//	構築

afDebugQueue::afDebugQueue()
{
	pdpsString=PNULL;
	cString=0;
	PosX=0;
	PosY=24;
	ColorText=RGB(255,255,255);
}

afDebugQueue::~afDebugQueue()
{
	ClearQueue();
}

///////////////////////////////////////////////////////////
//	キューを消去
//
//	引値 なし
//
//	返値 なし

void afDebugQueue::ClearQueue()
{
	int	i;

	for(i=0;i<cString;i++) delete[] pdpsString[i];
	delete[] pdpsString;
	pdpsString=PNULL;
	cString=0;
}

///////////////////////////////////////////////////////////
//	表示状態を設定
//
//	引値 int		表示するＸ座標
//		 int		表示するＹ座標
//		 COLORREF	文字色
//
//	返値 なし

void afDebugQueue::SetShowState(int x,int y,COLORREF ct)
{
	PosX=x;
	PosY=y;
	ColorText=ct;
}

///////////////////////////////////////////////////////////
//	キューに文字列をポスト
//
//	引値 char*	フォーマット文字列
//		 ...	フォーマット引数
//
//	返値 なし

void afDebugQueue::PostString(const char *psFormat,...)
{
	char	str[1024];
	char	**pp;
	int		i;

	//	バッファをコピー
	pp=new char*[cString+1];
	for(i=0;i<cString;i++) pp[i]=pdpsString[i];

	//	文字列をポスト
	vsprintf(str,psFormat,(char*)(&psFormat+1));
	pp[cString]=new char[strlen(str)];
	strcpy(pp[cString],str);

	//	バッファを設定
	delete[] pdpsString;
	pdpsString=pp;
	cString++;
}

///////////////////////////////////////////////////////////
//	キューの内容を表示（表示後はキューを破棄）
//
//	引値 なし
//
//	返値 なし

void afDebugQueue::Show()
{
	afScreen	scr;
	afDC	dc;
	int		i;

	scr.GetDC(&dc);
	for(i=0;i<cString;i++)
	{
		dc.Text(PosX,PosY+i*16,pdpsString[i],16,false,ColorText);
	}
	scr.ReleaseDC(&dc);

	ClearQueue();
}
