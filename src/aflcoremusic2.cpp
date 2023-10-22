//
//	AFL Music Core Class (DM) by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	_coreMusic2
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <aflinside.h>
#include <aflfunction.h>
#include <afldialog.h>
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define MAX_MUSIC	64

///////////////////////////////////////////////////////////
//	�N���X�ϐ���`

IDirectMusic		    *_coreMusic2::pDMObject=NULL;
IDirectMusicPort	    *_coreMusic2::pDMPort=NULL;
IDirectMusicPerformance *_coreMusic2::pDMPerformance=NULL;
IDirectMusicLoader	    *_coreMusic2::pDMLoader=NULL;
LPDIRECTSOUNDBUFFER	    _coreMusic2::pDSBuffer=NULL;
_coreMusic2::_tMUSIC2   _coreMusic2::dMusic[MAX_MUSIC];
bool _coreMusic2::fEnable=false;

///////////////////////////////////////////////////////////
//	������

void _coreMusic2::InitMusic()
{
	DMUS_PORTPARAMS	dmpp;
	DSBUFFERDESC	dsbd;
	WAVEFORMATEX	wf;
	DWORD	wfs,dss;
	int		i;

	//	�g�p�\�t���O�ݒ�
	fEnable=false;

	//	�Z�O�����g������
	for(i=0;i<MAX_MUSIC;i++) dMusic[i].pDMSegment=NULL;

	//	COM������
	if(CoInitialize(NULL)!=S_OK) return;

	//	�p�t�H�[�}���X�쐬
	if(CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,IID_IDirectMusicPerformance,(void**)&pDMPerformance)!=S_OK)
	{
		pDMPerformance=NULL;
		FailInit();
		return;
	}

	//	�p�t�H�[�}���X������
	if(pDMPerformance->Init(&pDMObject,_coreSound::pDSObject,GetWindowHandle())!=S_OK)
	{
		pDMObject=NULL;
		FailInit();
		return;
	}

	//	�|�[�g�쐬
	ZeroMemory(&dmpp,sizeof(DMUS_PORTPARAMS));
	dmpp.dwSize=sizeof(DMUS_PORTPARAMS);
	dmpp.dwValidParams=NULL;
	if(pDMObject->CreatePort(GUID_NULL,&dmpp,&pDMPort,NULL)!=S_OK)
	{
		pDMPort=NULL;
		FailInit();
		return;
	}

	//	�T�E���h�o�b�t�@�쐬
	ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
	ZeroMemory(&wf,sizeof(WAVEFORMATEX));
	wfs=sizeof(WAVEFORMATEX);
	pDMPort->GetFormat(&wf,&wfs,&dss);
	dsbd.dwSize=sizeof(DSBUFFERDESC);
	dsbd.dwFlags=DSBCAPS_CTRLVOLUME;
	dsbd.lpwfxFormat=&wf;
	dsbd.dwBufferBytes=dss;
	if(_coreSound::pDSObject->CreateSoundBuffer(&dsbd,&pDSBuffer,NULL)!=DS_OK)
	{
		pDSBuffer=NULL;
		FailInit();
		return;
	}

	//	�T�E���h�o�b�t�@�ڑ�
	if(pDMPort->SetDirectSound(_coreSound::pDSObject,pDSBuffer)!=S_OK)
	{
		FailInit();
		return;
	}

	//	�|�[�g�ݒ�
	if(pDMPort->Activate(TRUE)!=S_OK)
	{
		FailInit();
		return;
	}
	if(pDMPerformance->AddPort(pDMPort)!=S_OK)
	{
		FailInit();
		return;
	}
	if(pDMPerformance->AssignPChannelBlock(0,pDMPort,1)!=S_OK)
	{
		FailInit();
		return;
	}

	//	���[�_�쐬
	if(CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,IID_IDirectMusicLoader,(void**)&pDMLoader)!=S_OK)
	{
		pDMLoader=NULL;
		FailInit();
		return;
	}

	//	�g�p�\�t���O�ݒ�
	fEnable=true;

	return;
}

///////////////////////////////////////////////////////////
//	���������s������

void _coreMusic2::FailInit()
{
	if(pDMLoader!=NULL) pDMLoader->Release();
	pDMLoader=NULL;

	if(pDMPerformance!=NULL)
	{
		pDMPerformance->CloseDown();
		pDMPerformance->Release();
		pDMPerformance=NULL;
	}

	if(pDMPort!=NULL) pDMPort->Release();
	pDMPort=NULL;

	if(pDMObject!=NULL) pDMObject->Release();
	pDMObject=NULL;

	if(pDSBuffer!=NULL) pDSBuffer->Release();
	pDSBuffer=NULL;

	CoUninitialize();
}

///////////////////////////////////////////////////////////
//	�j��

void _coreMusic2::DestroyMusic()
{
	int	i;

	if(!fEnable) return;

	//	�p�t�H�[�}���X��~
	if(pDMPerformance!=NULL) Stop();

	//	�Z�O�����g���
	for(i=0;i<MAX_MUSIC;i++)
	{
		if(dMusic[i].pDMSegment==NULL) continue;
		dMusic[i].pDMSegment->SetParam(GUID_Unload,0xffffffff,0,0,(void*)pDMPerformance);
		dMusic[i].pDMSegment->Release();
		dMusic[i].pDMSegment=NULL;
	}

	//	���[�_���
	if(pDMLoader!=NULL) pDMLoader->Release();
	pDMLoader=NULL;

	//	�p�t�H�[�}���X���
	if(pDMPerformance!=NULL)
	{
		pDMPerformance->CloseDown();
		pDMPerformance->Release();
		pDMPerformance=NULL;
	}

	//	�|�[�g���
	if(pDMPort!=NULL) pDMPort->Release();
	pDMPort=NULL;

	//	DirectMusic �I�u�W�F�N�g���
	if(pDMObject!=NULL) pDMObject->Release();
	pDMObject=NULL;

	//	�T�E���h�o�b�t�@���
	if(pDSBuffer!=NULL) pDSBuffer->Release();
	pDSBuffer=NULL;

	//	COM���
	CoUninitialize();

	//	���̑��ŏI����
	fEnable=false;
}

///////////////////////////////////////////////////////////
//	�}�X�^�[�{�����[���ݒ�

void _coreMusic2::SetMasterVolume(long vol)
{
	long	v=vol;

	if(!fEnable) return;
	pDMPerformance->SetGlobalParam(GUID_PerfMasterVolume,(void*)&v,sizeof(long));
}

///////////////////////////////////////////////////////////
//	�}�X�^�[�G�N�X�v���b�V�����ݒ�

void _coreMusic2::SetMasterExpression(long vol)
{
	if(!fEnable) return;
	pDSBuffer->SetVolume(vol);
}

///////////////////////////////////////////////////////////
//	���[�h

int _coreMusic2::LoadMusic(const char *psFileName)
{
	afErrorBox	eb;
	DMUS_OBJECTDESC		desc;
	WCHAR	wcsFileName[1024];
	char	str[1024];
	int		i;
	int		no;

	if(!fEnable) return -1;

	//	�Z�O�����g����
	no=-1;
	for(i=0;i<MAX_MUSIC;i++)
	{
		if(dMusic[i].pDMSegment!=NULL) continue;
		no=i;
		break;
	}

	if(no==-1)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("�~���[�W�b�N�o�b�t�@������ɒB���܂����B");
		eb.SetRepair("���[�h���ꂽ�~���[�W�b�N�̐����������܂��B");
		eb.OpenBox();
		return -1;
	}

	//	�t�@�C�����擾
	GetFullPathFileName(str,psFileName);

	//	�����t�H�[�}�b�g�ϊ�
	if(IsWindowsNT()) setlocale(LC_ALL,"jpn");
	else			  setlocale(LC_ALL,"C");
	mbstowcs(wcsFileName,str,1024);

	//	�ǂݍ��ݏ���
	ZeroMemory(&desc,sizeof(DMUS_OBJECTDESC));
	desc.dwSize		=sizeof(DMUS_OBJECTDESC);
	desc.guidClass	=CLSID_DirectMusicSegment;
	desc.dwValidData=DMUS_OBJ_CLASS|DMUS_OBJ_FILENAME|DMUS_OBJ_FULLPATH;
	wcscpy(desc.wszFileName,wcsFileName);

	//	�ǂݍ���
	if(pDMLoader->GetObject(&desc,IID_IDirectMusicSegment,(void**)&dMusic[no].pDMSegment)!=S_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("�~���[�W�b�N��ǂݍ��߂܂���B");
		eb.SetRepair("���̂����ꂩ�̌������l�����܂��B\n"
					 "�t�@�C�������Ԉ���Ă���B\n"
					 "���������s�����Ă���B");
		eb.OpenBox();

		pDMLoader->Release();
		dMusic[no].pDMSegment=NULL;

		return -1;
	}

	//	�Z�O�����g�ݒ�
	dMusic[no].pDMSegment->SetParam(GUID_StandardMIDIFile,0xffffffff,0,0,NULL);
	dMusic[no].pDMSegment->SetParam(GUID_Download,0xffffffff,0,0,(void*)pDMPerformance);

	return no;
}

///////////////////////////////////////////////////////////
//	���

void _coreMusic2::ReleaseMusic(int no)
{
	if(!fEnable) return;
	if(dMusic[no].pDMSegment==NULL) return;

	if(IsPlaying(no)) Stop();

	dMusic[no].pDMSegment->SetParam(GUID_Unload,0xffffffff,0,0,(void*)pDMPerformance);
	dMusic[no].pDMSegment->Release();
	dMusic[no].pDMSegment=NULL;
}

///////////////////////////////////////////////////////////
//	�J�n�ʒu�ݒ�

void _coreMusic2::SetStartPoint(int no,DWORD pos)
{
	if(!fEnable) return;
	dMusic[no].pDMSegment->SetStartPoint(pos);
}

///////////////////////////////////////////////////////////
//	���s�[�g�͈͐ݒ�

void _coreMusic2::SetLoopPoint(int no,DWORD s,DWORD e)
{
	if(!fEnable) return;
	dMusic[no].pDMSegment->SetLoopPoints(s,e);
}

///////////////////////////////////////////////////////////
//	���s�[�g�ݒ�

void _coreMusic2::SetRepeat(int no,bool f)
{
	if(!fEnable) return;

	if(f) dMusic[no].pDMSegment->SetRepeats(0xffffffff);
	else  dMusic[no].pDMSegment->SetRepeats(0);
}

///////////////////////////////////////////////////////////
//	�Đ��擾

bool _coreMusic2::IsPlaying(int no)
{
	if(!fEnable) return false;

	if(pDMPerformance->IsPlaying(dMusic[no].pDMSegment,NULL)==S_OK)
	{
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////
//	�Đ�

void _coreMusic2::Play(int no)
{
	if(!fEnable) return;
	Stop();
	pDMPerformance->PlaySegment(dMusic[no].pDMSegment,0,0,NULL);
}

///////////////////////////////////////////////////////////
//	��~

void _coreMusic2::Stop()
{
	if(!fEnable) return;
	pDMPerformance->Stop(NULL,NULL,0,0);
}
