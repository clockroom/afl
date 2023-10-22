//
//	AFL Music Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afMusic
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflsound.h"
#include "aflcore.h"
#include "afldialog.h"

///////////////////////////////////////////////////////////
//	�ÓI�ϐ�������

afMusic *afMusic::pActiveObject=NULL;

///////////////////////////////////////////////////////////
//	�~���[�W�b�N�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afMusic::afMusic()
{
	fLock=false;
	fRepeat=true;
	dFileName=0;
}

///////////////////////////////////////////////////////////
//	�~���[�W�b�N�I�u�W�F�N�g�j��
//	���l	�Ȃ�

afMusic::~afMusic()
{
	delete[] dFileName;
}

///////////////////////////////////////////////////////////
//	�t�@�C������ݒ�
//	���l	char*	�t�@�C�����̕�����

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
//	���s�[�g�Đ���ݒ�
//	���l	bool	���s�[�g�Đ�
//						true	���s�[�g
//						false	�P�񂾂��Đ�

void afMusic::SetRepeat(bool f)
{
	fRepeat=f;
	if(pActiveObject==this)	_coreMusic::fRepeat=fRepeat;
}

///////////////////////////////////////////////////////////
//	�Đ��󋵂��擾
//	���l	�Ȃ�
//	�Ԓl	bool	�Đ���	true	�Đ���
//								false	��~��

bool afMusic::IsPlaying()
{
	if(pActiveObject!=this)	return false;
	return _coreMusic::fPlay;
}

///////////////////////////////////////////////////////////
//	SMF���Đ�
//	���l	�Ȃ�

void afMusic::Play()
{
	afErrorBox	eb;

	if(fLock && IsPlaying()) return;

	if(dFileName==0)
	{
		eb.SetFunctionName("afMusic::Play()");
		eb.SetMessage("�t�@�C�������ݒ肳��Ă��܂���B");
		eb.OpenBox();
		return;
	}

	_coreMusic::Play(dFileName);
	_coreMusic::fRepeat=fRepeat;

	fLock=true;
	pActiveObject=this;
}

///////////////////////////////////////////////////////////
//	�w���SMF���Đ�
//	���l	char*	�t�@�C����

void afMusic::Play(const char *fn)
{
	SetFileName(fn);
	Play();
}

///////////////////////////////////////////////////////////
//	���y���~����
//	���l	�Ȃ�

void afMusic::Stop()
{
	if(pActiveObject!=this)	return;

	_coreMusic::Stop();
	fLock=false;
}

///////////////////////////////////////////////////////////
//	���y��S��~
//	���l	�Ȃ�

void afMusic::StopAll()
{
	_coreMusic::Stop();
}
