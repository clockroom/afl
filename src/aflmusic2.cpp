//
//	AFL Music Class (DM) ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/20
//
//	afMusic2
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflsound.h"
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	afMusic2クラスを初期化
//	引値	なし
//	２回以上呼ばないでください

void afMusic2::InitMusic2()
{
	_coreMusic2::InitMusic();
}

///////////////////////////////////////////////////////////
//	マスターボリュームを設定
//	引値	long	ボリューム

void afMusic2::SetMasterVolume(long vol)
{
	_coreMusic2::SetMasterVolume(vol*100);
}

///////////////////////////////////////////////////////////
//	マスターエクスプレッションを設定
//	引値	long	エクスプレッション

void afMusic2::SetMasterExpression(long exp)
{
	_coreMusic2::SetMasterExpression(exp*100);
}

///////////////////////////////////////////////////////////
//	全停止
//	引値	なし

void afMusic2::StopAll()
{
	_coreMusic2::Stop();
}

///////////////////////////////////////////////////////////
//	構築

afMusic2::afMusic2()
{
	nMusic=-1;
}

afMusic2::~afMusic2()
{
	ReleaseMusic();
}

///////////////////////////////////////////////////////////
//	ミュージックをロード
//	引値	char*	ファイル名

void afMusic2::LoadMusic(const char *ps)
{
	ReleaseMusic();
	nMusic=_coreMusic2::LoadMusic(ps);

	SetStartPointByBeat(0);
	SetLoopPointByBeat(0,0);
	SetRepeat(true);
}

///////////////////////////////////////////////////////////
//	ミュージックを解放
//	引値	なし

void afMusic2::ReleaseMusic()
{
	if(nMusic==-1) return;

	_coreMusic2::ReleaseMusic(nMusic);
	nMusic=-1;
}

///////////////////////////////////////////////////////////
//	開始位置を設定
//	引値	DWORD	開始位置

void afMusic2::SetStartPoint(DWORD pos)
{
	if(nMusic==-1) return;
	_coreMusic2::SetStartPoint(nMusic,pos);
}

///////////////////////////////////////////////////////////
//	開始位置を設定
//	引値	DWORD	開始位置（拍単位）

void afMusic2::SetStartPointByBeat(DWORD pos)
{
	if(nMusic==-1) return;
	_coreMusic2::SetStartPoint(nMusic,DMUS_PPQ*pos);
}

///////////////////////////////////////////////////////////
//	ループ範囲を設定
//	引値	DWORD	開始位置（拍単位）
//			DWORD	終了位置（拍単位）
//					０を指定すると最後まで

void afMusic2::SetLoopPointByBeat(DWORD s,DWORD e)
{
	if(nMusic==-1) return;
	_coreMusic2::SetLoopPoint(nMusic,DMUS_PPQ*s,DMUS_PPQ*e);
}

///////////////////////////////////////////////////////////
//	リピート設定
//	引値	bool	true	リピートする
//			bool	false	リピートしない

void afMusic2::SetRepeat(bool f)
{
	if(nMusic==-1) return;
	_coreMusic2::SetRepeat(nMusic,f);
}

///////////////////////////////////////////////////////////
//	再生状態を取得
//	引値	なし
//	返値	bool	true	再生中
//					false	停止中

bool afMusic2::IsPlaying()
{
	if(nMusic==-1) return false;
	return _coreMusic2::IsPlaying(nMusic);
}

///////////////////////////////////////////////////////////
//	再生
//	引値	なし

void afMusic2::Play()
{
	if(nMusic==-1)  return;
	if(IsPlaying()) return;
	_coreMusic2::Play(nMusic);
}

///////////////////////////////////////////////////////////
//	停止
//	引値	なし

void afMusic2::Stop()
{
	if(nMusic==-1)   return;
	if(!IsPlaying()) return;
	_coreMusic2::Stop();
}
