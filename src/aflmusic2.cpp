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
//	�C���N���[�h

#include "aflsound.h"
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	afMusic2�N���X��������
//	���l	�Ȃ�
//	�Q��ȏ�Ă΂Ȃ��ł�������

void afMusic2::InitMusic2()
{
	_coreMusic2::InitMusic();
}

///////////////////////////////////////////////////////////
//	�}�X�^�[�{�����[����ݒ�
//	���l	long	�{�����[��

void afMusic2::SetMasterVolume(long vol)
{
	_coreMusic2::SetMasterVolume(vol*100);
}

///////////////////////////////////////////////////////////
//	�}�X�^�[�G�N�X�v���b�V������ݒ�
//	���l	long	�G�N�X�v���b�V����

void afMusic2::SetMasterExpression(long exp)
{
	_coreMusic2::SetMasterExpression(exp*100);
}

///////////////////////////////////////////////////////////
//	�S��~
//	���l	�Ȃ�

void afMusic2::StopAll()
{
	_coreMusic2::Stop();
}

///////////////////////////////////////////////////////////
//	�\�z

afMusic2::afMusic2()
{
	nMusic=-1;
}

afMusic2::~afMusic2()
{
	ReleaseMusic();
}

///////////////////////////////////////////////////////////
//	�~���[�W�b�N�����[�h
//	���l	char*	�t�@�C����

void afMusic2::LoadMusic(const char *ps)
{
	ReleaseMusic();
	nMusic=_coreMusic2::LoadMusic(ps);

	SetStartPointByBeat(0);
	SetLoopPointByBeat(0,0);
	SetRepeat(true);
}

///////////////////////////////////////////////////////////
//	�~���[�W�b�N�����
//	���l	�Ȃ�

void afMusic2::ReleaseMusic()
{
	if(nMusic==-1) return;

	_coreMusic2::ReleaseMusic(nMusic);
	nMusic=-1;
}

///////////////////////////////////////////////////////////
//	�J�n�ʒu��ݒ�
//	���l	DWORD	�J�n�ʒu

void afMusic2::SetStartPoint(DWORD pos)
{
	if(nMusic==-1) return;
	_coreMusic2::SetStartPoint(nMusic,pos);
}

///////////////////////////////////////////////////////////
//	�J�n�ʒu��ݒ�
//	���l	DWORD	�J�n�ʒu�i���P�ʁj

void afMusic2::SetStartPointByBeat(DWORD pos)
{
	if(nMusic==-1) return;
	_coreMusic2::SetStartPoint(nMusic,DMUS_PPQ*pos);
}

///////////////////////////////////////////////////////////
//	���[�v�͈͂�ݒ�
//	���l	DWORD	�J�n�ʒu�i���P�ʁj
//			DWORD	�I���ʒu�i���P�ʁj
//					�O���w�肷��ƍŌ�܂�

void afMusic2::SetLoopPointByBeat(DWORD s,DWORD e)
{
	if(nMusic==-1) return;
	_coreMusic2::SetLoopPoint(nMusic,DMUS_PPQ*s,DMUS_PPQ*e);
}

///////////////////////////////////////////////////////////
//	���s�[�g�ݒ�
//	���l	bool	true	���s�[�g����
//			bool	false	���s�[�g���Ȃ�

void afMusic2::SetRepeat(bool f)
{
	if(nMusic==-1) return;
	_coreMusic2::SetRepeat(nMusic,f);
}

///////////////////////////////////////////////////////////
//	�Đ���Ԃ��擾
//	���l	�Ȃ�
//	�Ԓl	bool	true	�Đ���
//					false	��~��

bool afMusic2::IsPlaying()
{
	if(nMusic==-1) return false;
	return _coreMusic2::IsPlaying(nMusic);
}

///////////////////////////////////////////////////////////
//	�Đ�
//	���l	�Ȃ�

void afMusic2::Play()
{
	if(nMusic==-1)  return;
	if(IsPlaying()) return;
	_coreMusic2::Play(nMusic);
}

///////////////////////////////////////////////////////////
//	��~
//	���l	�Ȃ�

void afMusic2::Stop()
{
	if(nMusic==-1)   return;
	if(!IsPlaying()) return;
	_coreMusic2::Stop();
}
