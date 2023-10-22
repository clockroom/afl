//
//	AFL Music Core Class (DM) by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	_coreMusic2
//

///////////////////////////////////////////////////////////
//	インクルード

#include <aflinside.h>
#include <aflfunction.h>
#include <afldialog.h>
#include "aflcore.h"

///////////////////////////////////////////////////////////
//	定数定義

#define MAX_MUSIC	64

///////////////////////////////////////////////////////////
//	クラス変数定義

IDirectMusic		    *_coreMusic2::pDMObject=NULL;
IDirectMusicPort	    *_coreMusic2::pDMPort=NULL;
IDirectMusicPerformance *_coreMusic2::pDMPerformance=NULL;
IDirectMusicLoader	    *_coreMusic2::pDMLoader=NULL;
LPDIRECTSOUNDBUFFER	    _coreMusic2::pDSBuffer=NULL;
_coreMusic2::_tMUSIC2   _coreMusic2::dMusic[MAX_MUSIC];
bool _coreMusic2::fEnable=false;

///////////////////////////////////////////////////////////
//	初期化

void _coreMusic2::InitMusic()
{
	DMUS_PORTPARAMS	dmpp;
	DSBUFFERDESC	dsbd;
	WAVEFORMATEX	wf;
	DWORD	wfs,dss;
	int		i;

	//	使用可能フラグ設定
	fEnable=false;

	//	セグメント初期化
	for(i=0;i<MAX_MUSIC;i++) dMusic[i].pDMSegment=NULL;

	//	COM初期化
	if(CoInitialize(NULL)!=S_OK) return;

	//	パフォーマンス作成
	if(CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,IID_IDirectMusicPerformance,(void**)&pDMPerformance)!=S_OK)
	{
		pDMPerformance=NULL;
		FailInit();
		return;
	}

	//	パフォーマンス初期化
	if(pDMPerformance->Init(&pDMObject,_coreSound::pDSObject,GetWindowHandle())!=S_OK)
	{
		pDMObject=NULL;
		FailInit();
		return;
	}

	//	ポート作成
	ZeroMemory(&dmpp,sizeof(DMUS_PORTPARAMS));
	dmpp.dwSize=sizeof(DMUS_PORTPARAMS);
	dmpp.dwValidParams=NULL;
	if(pDMObject->CreatePort(GUID_NULL,&dmpp,&pDMPort,NULL)!=S_OK)
	{
		pDMPort=NULL;
		FailInit();
		return;
	}

	//	サウンドバッファ作成
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

	//	サウンドバッファ接続
	if(pDMPort->SetDirectSound(_coreSound::pDSObject,pDSBuffer)!=S_OK)
	{
		FailInit();
		return;
	}

	//	ポート設定
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

	//	ローダ作成
	if(CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,IID_IDirectMusicLoader,(void**)&pDMLoader)!=S_OK)
	{
		pDMLoader=NULL;
		FailInit();
		return;
	}

	//	使用可能フラグ設定
	fEnable=true;

	return;
}

///////////////////////////////////////////////////////////
//	初期化失敗時処理

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
//	破棄

void _coreMusic2::DestroyMusic()
{
	int	i;

	if(!fEnable) return;

	//	パフォーマンス停止
	if(pDMPerformance!=NULL) Stop();

	//	セグメント解放
	for(i=0;i<MAX_MUSIC;i++)
	{
		if(dMusic[i].pDMSegment==NULL) continue;
		dMusic[i].pDMSegment->SetParam(GUID_Unload,0xffffffff,0,0,(void*)pDMPerformance);
		dMusic[i].pDMSegment->Release();
		dMusic[i].pDMSegment=NULL;
	}

	//	ローダ解放
	if(pDMLoader!=NULL) pDMLoader->Release();
	pDMLoader=NULL;

	//	パフォーマンス解放
	if(pDMPerformance!=NULL)
	{
		pDMPerformance->CloseDown();
		pDMPerformance->Release();
		pDMPerformance=NULL;
	}

	//	ポート解放
	if(pDMPort!=NULL) pDMPort->Release();
	pDMPort=NULL;

	//	DirectMusic オブジェクト解放
	if(pDMObject!=NULL) pDMObject->Release();
	pDMObject=NULL;

	//	サウンドバッファ解放
	if(pDSBuffer!=NULL) pDSBuffer->Release();
	pDSBuffer=NULL;

	//	COM解放
	CoUninitialize();

	//	その他最終処理
	fEnable=false;
}

///////////////////////////////////////////////////////////
//	マスターボリューム設定

void _coreMusic2::SetMasterVolume(long vol)
{
	long	v=vol;

	if(!fEnable) return;
	pDMPerformance->SetGlobalParam(GUID_PerfMasterVolume,(void*)&v,sizeof(long));
}

///////////////////////////////////////////////////////////
//	マスターエクスプレッション設定

void _coreMusic2::SetMasterExpression(long vol)
{
	if(!fEnable) return;
	pDSBuffer->SetVolume(vol);
}

///////////////////////////////////////////////////////////
//	ロード

int _coreMusic2::LoadMusic(const char *psFileName)
{
	afErrorBox	eb;
	DMUS_OBJECTDESC		desc;
	WCHAR	wcsFileName[1024];
	char	str[1024];
	int		i;
	int		no;

	if(!fEnable) return -1;

	//	セグメント検索
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
		eb.SetMessage("ミュージックバッファが上限に達しました。");
		eb.SetRepair("ロードされたミュージックの数が多すぎます。");
		eb.OpenBox();
		return -1;
	}

	//	ファイル名取得
	GetFullPathFileName(str,psFileName);

	//	文字フォーマット変換
	if(IsWindowsNT()) setlocale(LC_ALL,"jpn");
	else			  setlocale(LC_ALL,"C");
	mbstowcs(wcsFileName,str,1024);

	//	読み込み準備
	ZeroMemory(&desc,sizeof(DMUS_OBJECTDESC));
	desc.dwSize		=sizeof(DMUS_OBJECTDESC);
	desc.guidClass	=CLSID_DirectMusicSegment;
	desc.dwValidData=DMUS_OBJ_CLASS|DMUS_OBJ_FILENAME|DMUS_OBJ_FULLPATH;
	wcscpy(desc.wszFileName,wcsFileName);

	//	読み込み
	if(pDMLoader->GetObject(&desc,IID_IDirectMusicSegment,(void**)&dMusic[no].pDMSegment)!=S_OK)
	{
		eb.SetTitle("AFL Inside Error");
		eb.SetMessage("ミュージックを読み込めません。");
		eb.SetRepair("次のいずれかの原因が考えられます。\n"
					 "ファイル名が間違っている。\n"
					 "メモリが不足している。");
		eb.OpenBox();

		pDMLoader->Release();
		dMusic[no].pDMSegment=NULL;

		return -1;
	}

	//	セグメント設定
	dMusic[no].pDMSegment->SetParam(GUID_StandardMIDIFile,0xffffffff,0,0,NULL);
	dMusic[no].pDMSegment->SetParam(GUID_Download,0xffffffff,0,0,(void*)pDMPerformance);

	return no;
}

///////////////////////////////////////////////////////////
//	解放

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
//	開始位置設定

void _coreMusic2::SetStartPoint(int no,DWORD pos)
{
	if(!fEnable) return;
	dMusic[no].pDMSegment->SetStartPoint(pos);
}

///////////////////////////////////////////////////////////
//	リピート範囲設定

void _coreMusic2::SetLoopPoint(int no,DWORD s,DWORD e)
{
	if(!fEnable) return;
	dMusic[no].pDMSegment->SetLoopPoints(s,e);
}

///////////////////////////////////////////////////////////
//	リピート設定

void _coreMusic2::SetRepeat(int no,bool f)
{
	if(!fEnable) return;

	if(f) dMusic[no].pDMSegment->SetRepeats(0xffffffff);
	else  dMusic[no].pDMSegment->SetRepeats(0);
}

///////////////////////////////////////////////////////////
//	再生取得

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
//	再生

void _coreMusic2::Play(int no)
{
	if(!fEnable) return;
	Stop();
	pDMPerformance->PlaySegment(dMusic[no].pDMSegment,0,0,NULL);
}

///////////////////////////////////////////////////////////
//	停止

void _coreMusic2::Stop()
{
	if(!fEnable) return;
	pDMPerformance->Stop(NULL,NULL,0,0);
}
