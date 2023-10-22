//
//	AFL Sound Core Class by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	_coreSound
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <aflinside.h>
#include <aflfunction.h>
#include <afldialog.h>
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define MAX_SOUND	70

///////////////////////////////////////////////////////////
//	�ÓI�ϐ���`

LPDIRECTSOUND		_coreSound::pDSObject=NULL;
LPDIRECTSOUNDBUFFER _coreSound::pDSBuffer=NULL;
_coreSound::_tSOUND _coreSound::dSound[MAX_SOUND];

bool _coreSound::fOK=false;

///////////////////////////////////////////////////////////
//	������

void _coreSound::InitSound()
{
	DSBUFFERDESC dsbd;
	int	i,j;

	//	DirectSound�̏�����
	if(DirectSoundCreate(NULL,&pDSObject,NULL)!=DS_OK)
	{
		fOK=false;
		return;
	}

	//	�r�����x���ݒ�
	pDSObject->SetCooperativeLevel(GetWindowHandle(),DSSCL_EXCLUSIVE);

	//	�o�b�t�@�P�̏�����
	memset(&dsbd,0,sizeof(DSBUFFERDESC));
	dsbd.dwSize=sizeof(DSBUFFERDESC);
	dsbd.dwFlags=DSBCAPS_PRIMARYBUFFER;
	pDSObject->CreateSoundBuffer(&dsbd,&pDSBuffer,NULL);

	//	�o�b�t�@�Q�̏�����
	for(i=0;i<MAX_SOUND;i++)for(j=0;j<_CS_MAX_POLY;j++)
	{
		dSound[i].dpDSBuffer[j]=NULL;
	}

	//	�f�[�^������
	for(i=0;i<MAX_SOUND;i++)
	{
		dSound[i].fEnable=false;
		dSound[i].Poly=1;
		dSound[i].nPlay=0;
		dSound[i].DefPitch=0;
	}

	//	�g�p�\�t���O��ON�ɐݒ�
	fOK=true;
}

///////////////////////////////////////////////////////////
//	�j��

void _coreSound::DestroySound()
{
	int i,j;

	if(!fOK) return;

	//	�o�b�t�@�Q�̉��
	for(i=0;i<MAX_SOUND;i++)
	{
		if(!dSound[i].fEnable) continue;

		for(j=0;j<dSound[i].Poly;j++)
		{
			dSound[i].dpDSBuffer[j]->Stop();
			dSound[i].dpDSBuffer[j]->Release();
			dSound[i].dpDSBuffer[j]=NULL;
		}
		dSound[i].fEnable=false;
	}

	//	�o�b�t�@�P�̉��
	if(pDSBuffer!=NULL) pDSBuffer->Release();

	//	DirectSound�̉��
	if(pDSObject!=NULL) pDSObject->Release();
}

///////////////////////////////////////////////////////////
//	�Đ������ݒ�

void _coreSound::SetSoundQuality(int bits)
{
	WAVEFORMATEX	wfx;

	//	���̏�Ԏ擾
	pDSBuffer->GetFormat(&wfx,sizeof(WAVEFORMATEX),NULL);

	//	�����ݒ�
	wfx.wBitsPerSample=bits;

	//	�p�����[�^�C��
	wfx.nBlockAlign=(wfx.wBitsPerSample/8)*wfx.nChannels;
	wfx.nAvgBytesPerSec=wfx.nSamplesPerSec*wfx.nBlockAlign;

	//	�ݒ�ύX
	pDSBuffer->SetFormat(&wfx);
}

///////////////////////////////////////////////////////////
//	�T�E���h�ǂݍ���

int _coreSound::LoadSound(const char* psName,int Poly,bool fMemory)
{
	afErrorBox		eb;
	DSBUFFERDESC	dsbd;
	LPWAVEFORMATEX	pWFX=NULL;
	BYTE	*pByte=NULL;
	UINT	Size;
	HRSRC	hrsrc;
	DWORD	*pdword;
	int		TopThrough;
	bool	fReadFile;
	LPVOID	pbuf1,pbuf2;
	DWORD	buf1,buf2;
	int		i,n;

	if(!fOK) return -1;

	//	�󂫃T�E���h�̌���
	for(n=0;n<MAX_SOUND;n++)
	{
		if(!dSound[n].fEnable) break;
	}

	if(n>=MAX_SOUND)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("�T�E���h�o�b�t�@������ɒB���܂����B");
		eb.SetRepair("���[�h���ꂽ�T�E���h�̐����������܂��B");
		eb.OpenBox();
		return -1;
	}

	//	�t�@�C���̌���
	if(!_ReadSoundFile(psName,&Size,&pWFX,&pByte))
	{
		pdword=(DWORD*)pWFX;

		TopThrough=0;
		fReadFile=true;
	}
	else
	{
		//	WAVE���\�[�X�̌���
		if((hrsrc=FindResource(NULL,psName,"WAVE"))==NULL)
		{
			//	RCDATA���\�[�X�̌���
			if((hrsrc=FindResource(NULL,psName,RT_RCDATA))==NULL)
			{
				eb.SetTitle("AFL Inside Error");
				eb.SetMessage("�T�E���h��ǂݍ��߂܂���B");
				eb.SetRepair("���̂����ꂩ�̌������l�����܂��B\n"
							 "�t�@�C�������Ԉ���Ă���B\n"
							 "���������s�����Ă���B");
				eb.OpenBox();
				return -1;
        	}
		}

		//	���\�[�X����̓ǂݍ���
		pdword=(DWORD*)LockResource(LoadResource(NULL,hrsrc));

		Size=*(pdword+10);
		TopThrough=5;
		fReadFile=false;
	}

	//	�����������o�b�t�@�Q�𐶐�
	dSound[n].Poly=Poly;
	dSound[n].nPlay=0;
	for(i=0;i<dSound[n].Poly;i++)
	{
		//	�o�b�t�@�Q�̏�����
		memset(&dsbd,0,sizeof(DSBUFFERDESC));
		dsbd.dwSize=sizeof(DSBUFFERDESC);
		dsbd.dwBufferBytes=Size;
		dsbd.lpwfxFormat=(LPWAVEFORMATEX)(pdword+TopThrough); 
		dsbd.dwFlags=DSBCAPS_STATIC|DSBCAPS_CTRLDEFAULT;
		if(!fMemory) dsbd.dwFlags|=DSBCAPS_LOCSOFTWARE;

		if(pDSObject->CreateSoundBuffer(&dsbd,&dSound[n].dpDSBuffer[i],NULL)!=DS_OK)
		{
			eb.SetTitle("AFL Inside Error");
			eb.SetMessage("�T�E���h�o�b�t�@���쐬�ł��܂���B");
			eb.OpenBox();
			return -1;
		}

		//	�o�b�t�@�Q�̃��b�N
		if(fReadFile)
		{
			dSound[n].dpDSBuffer[i]->Lock(0,Size,&pbuf1,&buf1,&pbuf2,&buf2,0);
		}
		else
		{
			dSound[n].dpDSBuffer[i]->Lock(0,*(pdword+10),&pbuf1,&buf1,&pbuf2,&buf2,0);
		}

		//	�����f�[�^�̐ݒ�
		if(fReadFile)
		{
			memcpy(pbuf1,pByte,Size);
		}
		else
		{
			CopyMemory(pbuf1,(BYTE*)(pdword+11),buf1);
			if(buf2!=0)
			{
				CopyMemory(pbuf2,(BYTE*)(pdword+11)+buf1,buf2);
			}
		}

		//	�o�b�t�@�Q�̃��b�N����
		dSound[n].dpDSBuffer[i]->Unlock(pbuf1,buf1,pbuf2,buf2); 

		//	�s�b�`�̎擾�Ə�����
		dSound[n].dpDSBuffer[i]->GetFrequency(&dSound[n].DefPitch);
	}

	//	�T�E���h�g�p�t���O�̐ݒ�
	dSound[n].fEnable=true;

	//	�������̉��
	if(pWFX!=NULL) GlobalFreePtr(pWFX);
	if(pByte!=NULL) GlobalFreePtr(pByte);

	return n;
}

///////////////////////////////////////////////////////////
//	�T�E���h���

void _coreSound::ReleaseSound(int s)
{
	int i;

	if(!fOK)			   return;
	if(!dSound[s].fEnable) return;

	dSound[s].fEnable=false;
	dSound[s].DefPitch=0;

	for(i=0;i<dSound[s].Poly;i++)
	{
		dSound[s].dpDSBuffer[i]->Stop();
		dSound[s].dpDSBuffer[i]->Release();
		dSound[s].dpDSBuffer[i]=NULL;
	}

	dSound[s].Poly=1;
}

///////////////////////////////////////////////////////////
//	�Đ�

void _coreSound::Play(int s)
{
	int	n=dSound[s].nPlay;

	if(!fOK) return;

	dSound[s].dpDSBuffer[n]->Stop();
	dSound[s].dpDSBuffer[n]->SetCurrentPosition(0);
	dSound[s].dpDSBuffer[n]->Play(0,0,0);

	if(++n>=dSound[s].Poly)	n=0;
	dSound[s].nPlay=n;
}

///////////////////////////////////////////////////////////
//	���[�v�Đ�

void _coreSound::Loop(int s)
{
	int	n=dSound[s].nPlay;

	if(!fOK) return;

	dSound[s].dpDSBuffer[n]->Stop();
	dSound[s].dpDSBuffer[n]->SetCurrentPosition(0);
	dSound[s].dpDSBuffer[n]->Play(0,0,DSBPLAY_LOOPING);

	if(++n>=dSound[s].Poly)	n=0;
	dSound[s].nPlay=n;
}

///////////////////////////////////////////////////////////
//	��~

void _coreSound::Stop(int s)
{
	int	i;

	if(!fOK) return;

	for(i=0;i<dSound[s].Poly;i++)
	{
		dSound[s].dpDSBuffer[i]->Stop();
		dSound[s].dpDSBuffer[i]->SetCurrentPosition(0);
	}
}

///////////////////////////////////////////////////////////
//	�s�b�`�ݒ�

void _coreSound::SetPitch(int s,int pit)
{
	int	i;

	if(!fOK) return;

	pit=dSound[s].DefPitch+pit*100;
	if(pit<100)	   pit=100;
	if(pit>100000) pit=100000;

	for(i=0;i<dSound[s].Poly;i++)
	{
		dSound[s].dpDSBuffer[i]->SetFrequency(pit);
	}
}

///////////////////////////////////////////////////////////
//	�p���ݒ�

void _coreSound::SetPan(int s,int pan)
{
	int	i;

	if(!fOK) return;

	pan*=100;
	if(pan<-10000) pan=-10000;
	if(pan> 10000) pan= 10000;

	for(i=0;i<dSound[s].Poly;i++)
	{
		dSound[s].dpDSBuffer[i]->SetPan(pan);
	}
}

///////////////////////////////////////////////////////////
//	�{�����[���ݒ�

void _coreSound::SetVolume(int s,int vol)
{
	int	i;

	if(!fOK) return;

	vol*=100;
	if(vol>0)	   vol=0;
	if(vol<-10000) vol=-10000;

	for(i=0;i<dSound[s].Poly;i++)
	{
		dSound[s].dpDSBuffer[i]->SetVolume(vol);
	}
}

///////////////////////////////////////////////////////////
//	�Đ����擾

bool _coreSound::IsPlaying(int s)
{
	int		i;
	DWORD	f;

	if(!fOK) return false;

	for(i=0;i<dSound[s].Poly;i++)
	{
		dSound[s].dpDSBuffer[i]->GetStatus(&f);
		if(f & DSBSTATUS_PLAYING) return true;
	}

	return false;
}

///////////////////////////////////////////////////////////
//	WAVE�t�@�C���ǂݍ���

bool _coreSound::_ReadSoundFile(const char *psName,UINT *pSize,WAVEFORMATEX **ppWFX,BYTE **ppData)
{
	PCMWAVEFORMAT	pwf;
	MMCKINFO	ckInRiff;
	MMCKINFO	ckIn;
	MMIOINFO	mmioinfoIn;
	HMMIO	hmmioIn;
	WORD	ExtraAlloc;
	UINT	ActualRead;
	UINT	t,DataIn;
	char	str[1024];
	bool	fError=false;

	*ppData=NULL;
	*ppWFX=NULL;
	*pSize=0;
	hmmioIn=NULL;

	do
	{
		GetFullPathFileName(str,psName);
		if((hmmioIn=mmioOpen(str,NULL,MMIO_ALLOCBUF|MMIO_READ))==NULL)
		{
			fError=true;
			break;
		}

		if(mmioDescend(hmmioIn,&ckInRiff,NULL,0)!=0)
		{
			fError=true;
			break;
		}

		if((ckInRiff.ckid!=FOURCC_RIFF) || (ckInRiff.fccType!=mmioFOURCC('W','A','V','E')))
		{
			fError=true;
			break;
		}

		ckIn.ckid=mmioFOURCC('f','m','t',' ');

		if(mmioDescend(hmmioIn,&ckIn,&ckInRiff,MMIO_FINDCHUNK)!=0)
		{
			fError=true;
			break;
		}

		if(ckIn.cksize<sizeof(PCMWAVEFORMAT))
		{
			fError=true;
			break;
		}

		if(mmioRead(hmmioIn,(HPSTR)&pwf,(long)sizeof(PCMWAVEFORMAT))!=(long)sizeof(PCMWAVEFORMAT))
		{
			fError=true;
			break;
		}

		if(pwf.wf.wFormatTag==WAVE_FORMAT_PCM)
		{
			ExtraAlloc=0;
		}
		else
		{
			if(mmioRead(hmmioIn,(LPSTR)&ExtraAlloc,(long)sizeof(WORD))!=(long)sizeof(WORD))
			{
				fError=true;
				break;
			}
		}

		if((*ppWFX=(WAVEFORMATEX*)GlobalAlloc(GMEM_FIXED,sizeof(WAVEFORMATEX)+ExtraAlloc))==NULL)
		{
			fError=true;
			break;
		}

		memcpy(*ppWFX,&pwf,sizeof(PCMWAVEFORMAT));
		(*ppWFX)->cbSize=ExtraAlloc;

		if(ExtraAlloc!=0)
		{
			if(mmioRead(hmmioIn,(LPSTR)(((BYTE*)&((*ppWFX)->cbSize))+sizeof(WORD)),(long)(ExtraAlloc))!=(long)(ExtraAlloc))
			{
				fError=true;
				break;
			}
		}

		if(mmioAscend(hmmioIn,&ckIn,0)!=0)
		{
			fError=true;
			break;
		}
	} while(false);

	if(fError)
	{
		if(*ppWFX!=NULL)
		{
			GlobalFree(*ppWFX);
			*ppWFX=NULL;
		}

		if(hmmioIn!=NULL)
		{
			mmioClose(hmmioIn,0);
			hmmioIn=NULL;
		}
	}

	if(!fError)
	{
		do
		{
			mmioSeek(hmmioIn,ckInRiff.dwDataOffset+sizeof(FOURCC),SEEK_SET);

			ckIn.ckid=mmioFOURCC('d','a','t','a');

			if (mmioDescend(hmmioIn,&ckIn,&ckInRiff,MMIO_FINDCHUNK)!=0)
			{
				fError=true;
				break;
			}
		} while(false);
	}

	if(!fError)
	{
		if((*ppData=(BYTE*)GlobalAlloc(GMEM_FIXED,ckIn.cksize))==NULL)
		{
			fError=true;
		}
	}

	if(!fError)
	{
		do
		{
			if(mmioGetInfo(hmmioIn,&mmioinfoIn,0)!=0)
			{
				fError=true;
				break;
			}

			DataIn=ckIn.cksize;

			if(DataIn>ckIn.cksize) DataIn=ckIn.cksize;

			ckIn.cksize-=DataIn;

			for(t=0;t<DataIn;t++)
			{
				if(mmioinfoIn.pchNext==mmioinfoIn.pchEndRead)
				{
					if(mmioAdvance(hmmioIn,&mmioinfoIn,MMIO_READ)!=0)
					{
						fError=true;
						break;
					}

					if(mmioinfoIn.pchNext==mmioinfoIn.pchEndRead)
					{
						fError=true;
						break;
					}
				}

				if(fError) break;

				*((BYTE*)*ppData+t)=*((BYTE*)mmioinfoIn.pchNext);
				(BYTE*)mmioinfoIn.pchNext++;
			}

			if(fError) break;

			if(mmioSetInfo(hmmioIn,&mmioinfoIn,0)!=0)
			{
				fError=true;
				break;
			}

			ActualRead=DataIn;
		} while(false);
	}

	if(fError) ActualRead=0;

	*pSize=ActualRead;

	if(fError)
	{
		if(*ppData!=NULL)
		{
			GlobalFree(*ppData);
		    *ppData=NULL;
		}

		if(*ppWFX!=NULL)
		{
			GlobalFree(*ppWFX);
			*ppWFX=NULL;
		}
	}

	if(hmmioIn!=NULL)
	{
		mmioClose(hmmioIn,0);
		hmmioIn=NULL;
	}

	return fError;
}
