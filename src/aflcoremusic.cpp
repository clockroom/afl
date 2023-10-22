//
//	AFL Music Core Class by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	_coreMusic
//

///////////////////////////////////////////////////////////
//	インクルード

#include <aflinside.h>
#include <aflfunction.h>
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	静的変数定義

bool	_coreMusic::fPlay;
bool	_coreMusic::fRepeat;

///////////////////////////////////////////////////////////
//	初期化

void	_coreMusic::InitMusic()
{
	fPlay=false;
	fRepeat=true;
}

///////////////////////////////////////////////////////////
//	破棄

void	_coreMusic::DestroyMusic()
{
	Stop();
}

///////////////////////////////////////////////////////////
//	MIDI再生

void	_coreMusic::Play(const char* filename)
{
	char	buf[256];
	char	full[256];

	Stop();

	GetFullPathFileName(full,filename);
	sprintf(buf,"open \"%s\" type sequencer alias midi",full);

	mciSendString(buf,NULL,0,NULL);
	mciSendString("seek midi to start",NULL,0,NULL);
	mciSendString("play midi notify",NULL,0,GetWindowHandle());

	fPlay=true;
	fRepeat=true;
}

///////////////////////////////////////////////////////////
//	停止

void	_coreMusic::Stop()
{
	if(!fPlay)	return;

	mciSendString("stop midi",NULL,0,NULL);
	mciSendString("close midi",NULL,0,NULL);

	fPlay=false;
}

///////////////////////////////////////////////////////////
//	リプレイ

void	_coreMusic::Replay()
{
	if(fRepeat)
	{
		mciSendString("seek midi to start",NULL,0,NULL);
		mciSendString("play midi notify",NULL,0,GetWindowHandle());
	}
	else
	{
		Stop();
	}
}
