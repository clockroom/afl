//
//	AFL Music Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afMusic
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflsound.h"
#include "aflcore.h"
#include "afldialog.h"

///////////////////////////////////////////////////////////
//	静的変数初期化

afMusic *afMusic::pActiveObject=NULL;

///////////////////////////////////////////////////////////
//	ミュージックオブジェクト構築
//	引値	なし

afMusic::afMusic()
{
	fLock=false;
	fRepeat=true;
	dFileName=0;
}

///////////////////////////////////////////////////////////
//	ミュージックオブジェクト破棄
//	引値	なし

afMusic::~afMusic()
{
	delete[] dFileName;
}

///////////////////////////////////////////////////////////
//	ファイル名を設定
//	引値	char*	ファイル名の文字列

void afMusic::SetFileName(const char *fn)
{
	if(dFileName!=0 && fn!=NULL)
	{
		if(strcmp(dFileName,fn)==0)	return;
	}

	fLock=false;

	delete[] dFileName;
	if(fn==NULL)
	{
		dFileName=0;
		return;
	}

	dFileName=new char[strlen(fn)+1];
	strcpy(dFileName,fn);
}

///////////////////////////////////////////////////////////
//	リピート再生を設定
//	引値	bool	リピート再生
//						true	リピート
//						false	１回だけ再生

void afMusic::SetRepeat(bool f)
{
	fRepeat=f;
	if(pActiveObject==this)	_coreMusic::fRepeat=fRepeat;
}

///////////////////////////////////////////////////////////
//	再生状況を取得
//	引値	なし
//	返値	bool	再生状況	true	再生中
//								false	停止中

bool afMusic::IsPlaying()
{
	if(pActiveObject!=this)	return false;
	return _coreMusic::fPlay;
}

///////////////////////////////////////////////////////////
//	SMFを再生
//	引値	なし

void afMusic::Play()
{
	afErrorBox	eb;

	if(fLock && IsPlaying()) return;

	if(dFileName==0)
	{
		eb.SetFunctionName("afMusic::Play()");
		eb.SetMessage("ファイル名が設定されていません。");
		eb.OpenBox();
		return;
	}

	_coreMusic::Play(dFileName);
	_coreMusic::fRepeat=fRepeat;

	fLock=true;
	pActiveObject=this;
}

///////////////////////////////////////////////////////////
//	指定のSMFを再生
//	引値	char*	ファイル名

void afMusic::Play(const char *fn)
{
	SetFileName(fn);
	Play();
}

///////////////////////////////////////////////////////////
//	音楽を停止する
//	引値	なし

void afMusic::Stop()
{
	if(pActiveObject!=this)	return;

	_coreMusic::Stop();
	fLock=false;
}

///////////////////////////////////////////////////////////
//	音楽を全停止
//	引値	なし

void afMusic::StopAll()
{
	_coreMusic::Stop();
}
