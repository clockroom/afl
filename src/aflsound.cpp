//
//	AFL Sound Class by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//
//	afSound
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflsound.h"
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	静的変数初期化

int afSound::MasterVolume=0;

///////////////////////////////////////////////////////////
//	サウンドオブジェクト構築
//	引値	なし

afSound::afSound()
{
	fRepeat=false;
	nSound=-1;
	Volume=0;
	AbsoluteVolume=0;
}

///////////////////////////////////////////////////////////
//	サウンドオブジェクト破棄
//	引値	なし

afSound::~afSound()
{
	ReleaseSound();
}

///////////////////////////////////////////////////////////
//	サウンドをRAMにロード
//	引値	char*	ファイル名

void afSound::LoadSound(const char *ps)
{
	ReleaseSound();
	nSound=_coreSound::LoadSound(ps,1,false);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	サウンドをロード
//	引値	char*	ファイル名
//			bool	false	RAM
//					true	サウンドRAM or RAM

void afSound::LoadSound(const char *ps,bool f)
{
	ReleaseSound();
	nSound=_coreSound::LoadSound(ps,1,f);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	多重発音可能なサウンドをRAMにロード
//	引値	char*	ファイル名
//			int		同時発音可能数

void afSound::LoadSound(const char *ps,int poly)
{
	ReleaseSound();

	if(poly<1)			  poly=1;
	if(poly>_CS_MAX_POLY) poly=_CS_MAX_POLY;
	nSound=_coreSound::LoadSound(ps,poly,false);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	多重発音可能なサウンドをロード
//	引値	char*	ファイル名
//			int		同時発音可能数
//			bool	false	RAM
//					true	サウンドRAM or RAM

void afSound::LoadSound(const char *ps,int poly,bool f)
{
	ReleaseSound();

	if(poly<1)			  poly=1;
	if(poly>_CS_MAX_POLY) poly=_CS_MAX_POLY;
	nSound=_coreSound::LoadSound(ps,poly,f);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	サウンドを解放
//	引値	なし

void afSound::ReleaseSound()
{
	if(nSound<0) return;

	_coreSound::ReleaseSound(nSound);
	nSound=-1;
}

///////////////////////////////////////////////////////////
//	リセット
//
//	引値 なし
//
//	返値 なし

void afSound::ResetSound()
{
	SetRepeat(false);
	SetVolume(0);
	SetPan(0);
	SetPitch(0);
}

///////////////////////////////////////////////////////////
//	リピート設定
//
//	引値 bool	false リピートしない
//				true  リピートする
//
//	返値 なし

void afSound::SetRepeat(bool f)
{
	if(nSound<0) return;
	fRepeat=f;
}

///////////////////////////////////////////////////////////
//	ボリュームを設定
//	引値	int		ボリューム

void afSound::SetVolume(int vol)
{
	if(nSound<0) return;

	Volume=vol;
	AbsoluteVolume=MasterVolume+vol;

	_coreSound::SetVolume(nSound,AbsoluteVolume);
}

///////////////////////////////////////////////////////////
//	パンを設定
//	引値	int		パン（ 負(右) ～ 0(中) ～ 正(左) ）

void afSound::SetPan(int pan)
{
	if(nSound<0) return;
	_coreSound::SetPan(nSound,pan);
}

///////////////////////////////////////////////////////////
//	ピッチを設定
//	引値	int		ピッチ（ 負(低) ～ 0(正) ～ 正(高) ）

void afSound::SetPitch(int pitch)
{
	if(nSound<0) return;
	_coreSound::SetPitch(nSound,pitch);
}

///////////////////////////////////////////////////////////
//	再生中取得
//	引値	なし
//	返値	bool	true	再生中
//					false	停止中

bool afSound::IsPlaying()
{
	if(nSound<0) return false;

	return _coreSound::IsPlaying(nSound);
}

///////////////////////////////////////////////////////////
//	サウンドを再生
//	引値	なし

void afSound::Play()
{
	if(nSound<0) return;

	if(MasterVolume+Volume!=AbsoluteVolume)
	{
		SetVolume(Volume);
	}

	if(!fRepeat) _coreSound::Play(nSound);
	else		 _coreSound::Loop(nSound);
}

///////////////////////////////////////////////////////////
//	サウンドを停止
//	引値	なし

void afSound::Stop()
{
	if(nSound<0)	return;
	_coreSound::Stop(nSound);
}

///////////////////////////////////////////////////////////
//	再生音質設定

void afSound::SetSoundQuality(int bits)
{
	_coreSound::SetSoundQuality(bits);
}

///////////////////////////////////////////////////////////
//	マスターボリュームの設定
//	引値	int		ボリューム（0 以下）

void afSound::SetMasterVolume(int vol)
{
	MasterVolume=vol;
}
