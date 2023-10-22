//
//	AFL Sound by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//

#ifndef _AFLSOUND_H_
#define _AFLSOUND_H_

///////////////////////////////////////////////////////////
//	インクルード

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	定数定義

#define afMusic1	afMusic

#define MUSIC_BEAT	DMUS_PPQ

///////////////////////////////////////////////////////////
//	クラス宣言

class afSound;
class afMusic;
class afMusic2;

///////////////////////////////////////////////////////////
//	サウンドクラス

class afSound
{
	public:
		//	構築
		afSound();
		~afSound();

		//	作成系
		void LoadSound(const char*);
		void LoadSound(const char*,bool);
		void LoadSound(const char*,int);
		void LoadSound(const char*,int,bool);
		void ReleaseSound();

		//	操作系
		void ResetSound();

		//	設定系
		void SetRepeat(bool);
		void SetVolume(int);
		void SetPan(int);
		void SetPitch(int);

		//	取得系
		bool IsPlaying();

		//	再生系
		void Play();
		void Stop();

		//	マスター系
		static void SetSoundQuality(int);
		static void SetMasterVolume(int);

	private:
		//	変数
		bool fRepeat;
		int  nSound;
		int  Volume;
		int  AbsoluteVolume;

		static int MasterVolume;
};

///////////////////////////////////////////////////////////
//	ミュージッククラス

class afMusic
{
	public:
		//	構築
		afMusic();
		~afMusic();

		//	設定系
		void SetFileName(const char*);
		void SetRepeat(bool);

		//	取得系
		bool IsPlaying();

		//	再生系
		void Play();
		void Play(const char*);
		void Stop();

		//	マスター系
		static void StopAll();

	private:
		//	変数
		char *dFileName;
		bool fLock;
		bool fRepeat;

		static afMusic *pActiveObject;
};

///////////////////////////////////////////////////////////
//	ミュージッククラス (DM)

class afMusic2
{
	public:
		//	マスター系
		static void InitMusic2();
		static void SetMasterVolume(long);
		static void SetMasterExpression(long);
		static void StopAll();

		//	構築
		afMusic2();
		~afMusic2();

		//	作成系
		void LoadMusic(const char*);
		void ReleaseMusic();

		//	設定系
		void SetStartPoint(DWORD);
		void SetStartPointByBeat(DWORD);
		void SetLoopPointByBeat(DWORD,DWORD);
		void SetRepeat(bool);

		//	取得系
		bool IsPlaying();

		//	再生系
		void Play();
		void Stop();

	private:
		//	変数
		int nMusic;
};

#endif	//	_AFLSOUND_H_
