//
//	AFL Sound by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//

#ifndef _AFLSOUND_H_
#define _AFLSOUND_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflinclude.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define afMusic1	afMusic

#define MUSIC_BEAT	DMUS_PPQ

///////////////////////////////////////////////////////////
//	�N���X�錾

class afSound;
class afMusic;
class afMusic2;

///////////////////////////////////////////////////////////
//	�T�E���h�N���X

class afSound
{
	public:
		//	�\�z
		afSound();
		~afSound();

		//	�쐬�n
		void LoadSound(const char*);
		void LoadSound(const char*,bool);
		void LoadSound(const char*,int);
		void LoadSound(const char*,int,bool);
		void ReleaseSound();

		//	����n
		void ResetSound();

		//	�ݒ�n
		void SetRepeat(bool);
		void SetVolume(int);
		void SetPan(int);
		void SetPitch(int);

		//	�擾�n
		bool IsPlaying();

		//	�Đ��n
		void Play();
		void Stop();

		//	�}�X�^�[�n
		static void SetSoundQuality(int);
		static void SetMasterVolume(int);

	private:
		//	�ϐ�
		bool fRepeat;
		int  nSound;
		int  Volume;
		int  AbsoluteVolume;

		static int MasterVolume;
};

///////////////////////////////////////////////////////////
//	�~���[�W�b�N�N���X

class afMusic
{
	public:
		//	�\�z
		afMusic();
		~afMusic();

		//	�ݒ�n
		void SetFileName(const char*);
		void SetRepeat(bool);

		//	�擾�n
		bool IsPlaying();

		//	�Đ��n
		void Play();
		void Play(const char*);
		void Stop();

		//	�}�X�^�[�n
		static void StopAll();

	private:
		//	�ϐ�
		char *dFileName;
		bool fLock;
		bool fRepeat;

		static afMusic *pActiveObject;
};

///////////////////////////////////////////////////////////
//	�~���[�W�b�N�N���X (DM)

class afMusic2
{
	public:
		//	�}�X�^�[�n
		static void InitMusic2();
		static void SetMasterVolume(long);
		static void SetMasterExpression(long);
		static void StopAll();

		//	�\�z
		afMusic2();
		~afMusic2();

		//	�쐬�n
		void LoadMusic(const char*);
		void ReleaseMusic();

		//	�ݒ�n
		void SetStartPoint(DWORD);
		void SetStartPointByBeat(DWORD);
		void SetLoopPointByBeat(DWORD,DWORD);
		void SetRepeat(bool);

		//	�擾�n
		bool IsPlaying();

		//	�Đ��n
		void Play();
		void Stop();

	private:
		//	�ϐ�
		int nMusic;
};

#endif	//	_AFLSOUND_H_
