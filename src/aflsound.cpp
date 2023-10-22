//
//	AFL Sound Class by ClockRoom 2000
//	Program by Y.Kumagai ClockRoom 2000
//
//	afSound
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflsound.h"
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	�ÓI�ϐ�������

int afSound::MasterVolume=0;

///////////////////////////////////////////////////////////
//	�T�E���h�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afSound::afSound()
{
	fRepeat=false;
	nSound=-1;
	Volume=0;
	AbsoluteVolume=0;
}

///////////////////////////////////////////////////////////
//	�T�E���h�I�u�W�F�N�g�j��
//	���l	�Ȃ�

afSound::~afSound()
{
	ReleaseSound();
}

///////////////////////////////////////////////////////////
//	�T�E���h��RAM�Ƀ��[�h
//	���l	char*	�t�@�C����

void afSound::LoadSound(const char *ps)
{
	ReleaseSound();
	nSound=_coreSound::LoadSound(ps,1,false);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	�T�E���h�����[�h
//	���l	char*	�t�@�C����
//			bool	false	RAM
//					true	�T�E���hRAM or RAM

void afSound::LoadSound(const char *ps,bool f)
{
	ReleaseSound();
	nSound=_coreSound::LoadSound(ps,1,f);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	���d�����\�ȃT�E���h��RAM�Ƀ��[�h
//	���l	char*	�t�@�C����
//			int		���������\��

void afSound::LoadSound(const char *ps,int poly)
{
	ReleaseSound();

	if(poly<1)			  poly=1;
	if(poly>_CS_MAX_POLY) poly=_CS_MAX_POLY;
	nSound=_coreSound::LoadSound(ps,poly,false);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	���d�����\�ȃT�E���h�����[�h
//	���l	char*	�t�@�C����
//			int		���������\��
//			bool	false	RAM
//					true	�T�E���hRAM or RAM

void afSound::LoadSound(const char *ps,int poly,bool f)
{
	ReleaseSound();

	if(poly<1)			  poly=1;
	if(poly>_CS_MAX_POLY) poly=_CS_MAX_POLY;
	nSound=_coreSound::LoadSound(ps,poly,f);

	ResetSound();
}

///////////////////////////////////////////////////////////
//	�T�E���h�����
//	���l	�Ȃ�

void afSound::ReleaseSound()
{
	if(nSound<0) return;

	_coreSound::ReleaseSound(nSound);
	nSound=-1;
}

///////////////////////////////////////////////////////////
//	���Z�b�g
//
//	���l �Ȃ�
//
//	�Ԓl �Ȃ�

void afSound::ResetSound()
{
	SetRepeat(false);
	SetVolume(0);
	SetPan(0);
	SetPitch(0);
}

///////////////////////////////////////////////////////////
//	���s�[�g�ݒ�
//
//	���l bool	false ���s�[�g���Ȃ�
//				true  ���s�[�g����
//
//	�Ԓl �Ȃ�

void afSound::SetRepeat(bool f)
{
	if(nSound<0) return;
	fRepeat=f;
}

///////////////////////////////////////////////////////////
//	�{�����[����ݒ�
//	���l	int		�{�����[��

void afSound::SetVolume(int vol)
{
	if(nSound<0) return;

	Volume=vol;
	AbsoluteVolume=MasterVolume+vol;

	_coreSound::SetVolume(nSound,AbsoluteVolume);
}

///////////////////////////////////////////////////////////
//	�p����ݒ�
//	���l	int		�p���i ��(�E) �` 0(��) �` ��(��) �j

void afSound::SetPan(int pan)
{
	if(nSound<0) return;
	_coreSound::SetPan(nSound,pan);
}

///////////////////////////////////////////////////////////
//	�s�b�`��ݒ�
//	���l	int		�s�b�`�i ��(��) �` 0(��) �` ��(��) �j

void afSound::SetPitch(int pitch)
{
	if(nSound<0) return;
	_coreSound::SetPitch(nSound,pitch);
}

///////////////////////////////////////////////////////////
//	�Đ����擾
//	���l	�Ȃ�
//	�Ԓl	bool	true	�Đ���
//					false	��~��

bool afSound::IsPlaying()
{
	if(nSound<0) return false;

	return _coreSound::IsPlaying(nSound);
}

///////////////////////////////////////////////////////////
//	�T�E���h���Đ�
//	���l	�Ȃ�

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
//	�T�E���h���~
//	���l	�Ȃ�

void afSound::Stop()
{
	if(nSound<0)	return;
	_coreSound::Stop(nSound);
}

///////////////////////////////////////////////////////////
//	�Đ������ݒ�

void afSound::SetSoundQuality(int bits)
{
	_coreSound::SetSoundQuality(bits);
}

///////////////////////////////////////////////////////////
//	�}�X�^�[�{�����[���̐ݒ�
//	���l	int		�{�����[���i0 �ȉ��j

void afSound::SetMasterVolume(int vol)
{
	MasterVolume=vol;
}
