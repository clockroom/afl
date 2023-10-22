//
//	AFL Function by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <aflfunction.h>
#include <aflinclude.h>
#include <aflapp.h>
#include <afldialog.h>

///////////////////////////////////////////////////////////
//	�t�@�C���ϐ���`

//	�A�v���P�[�V�����n�֐�
static afApp	 *_af_pActiveApp=NULL;
static FPAPPFUNC _af_fpActiveAppFunc=NULL;

//	���w�n�֐�
static int _af_dSinTbl[256];
static int _af_dCosTbl[256];

///////////////////////////////////////////////////////////
//
//	�V�X�e���n�֐�
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	�m�s���ǂ����擾
//
//	���l �Ȃ�
//
//	�Ԓl bool	true	NT
//				false	9x

bool IsWindowsNT()
{
	OSVERSIONINFO	ovi;

	ovi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&ovi);

	if(ovi.dwPlatformId==VER_PLATFORM_WIN32_NT) return true;

	return false;
}

///////////////////////////////////////////////////////////
//
//	�A�v���P�[�V�����n�֐�
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	�A�v���P�[�V������ݒ�
//	���l	afApp*	�A�v���P�[�V�����I�u�W�F�N�g�ւ̃|�C���^
//			int		���[�`��	������	APP_INIT
//								�I��	APP_FINAL
//								���C��	APP_MAIN

void SetActiveApp(afApp *pApp,int nFunc)
{
	_af_pActiveApp=pApp;
	_af_fpActiveAppFunc=*((FPAPPFUNC*)&nFunc);
}

///////////////////////////////////////////////////////////
//	�A�v���P�[�V������ݒ�
//	���l	afApp*		�A�v���P�[�V�����I�u�W�F�N�g�ւ̃|�C���^
//			afApp::*	�A�v���P�[�V�����N���X�����o�ւ̃|�C���^

void SetActiveApp(afApp *pApp,FPAPPFUNC fpFunc)
{
	_af_pActiveApp=pApp;
	_af_fpActiveAppFunc=fpFunc;
}

///////////////////////////////////////////////////////////
//	�A�v���P�[�V������ݒ�
//	���l	void	(*)()	�֐��ւ̃|�C���^

void SetActiveApp(void (*fpFunc)())
{
	_af_pActiveApp=NULL;
	_af_fpActiveAppFunc=*((FPAPPFUNC*)&fpFunc);
}

///////////////////////////////////////////////////////////
//	�A�N�e�B�u�A�v���P�[�V�����Ăяo��
//	���l	�Ȃ�

bool CallActiveApp()
{
	if(_af_fpActiveAppFunc==NULL) return false;

	if(_af_pActiveApp==NULL)
	{
		(*((void(**)())&_af_fpActiveAppFunc))();
		return true;
	}

	if(_af_pActiveApp->AppSwitch(*((int*)&_af_fpActiveAppFunc))) return true;

	(_af_pActiveApp->*_af_fpActiveAppFunc)();

	return true;
}

///////////////////////////////////////////////////////////
//
//	�t�@�C�������n
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	�t�@�C���̗L�����m�F
//	���l	char*	�t�@�C�����ւ̃|�C���^
//	�Ԓl	bool	����(true=���� or false)

bool SearchFile(const char *file)
{
	FILE	*fp;

	if((fp=fopen(file,"rb"))==NULL) return false;
	fclose(fp);
	return true;
}

///////////////////////////////////////////////////////////
//
//	������n�֐�
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	�t�@�C��������t���p�X�t�@�C�������擾
//	���l	char*	�t���p�X�t�@�C�������i�[����o�b�t�@�̃A�h���X
//			char*	�t�@�C�����ւ̃|�C���^

void GetFullPathFileName(char *path,const char *file)
{
	char	buf[512];
	char	*p;

	//	�t���p�X�t�@�C�������n���ꂽ�ꍇ
	if(strchr(file,':')!=NULL)
	{
		strcpy(path,file);
		return;
	}

	//	�t�@�C�������n���ꂽ�ꍇ
	GetModuleFileName(NULL,buf,512);
	p=strrchr(buf,'\\')+1;
	*p='\0';

	//	�R�s�[
	strcat(buf,file);
	strcpy(path,buf);
}

///////////////////////////////////////////////////////////
//	�p�X�t�@�C��������t�@�C�������擾
//	���l	char*	�t�@�C�������i�[����o�b�t�@�̃A�h���X
//			char*	�p�X�t�@�C�����ւ̃|�C���^

void GetFileName(char *file,const char *path)
{
	char	*p;

	p=strrchr(path,'\\');
	if(p!=NULL) strcpy(file,p+1);
	else		strcpy(file,path);
}

///////////////////////////////////////////////////////////
//	�p�X�t�@�C��������p�X�����擾
//	���l	char*	�p�X�����i�[����o�b�t�@�̃A�h���X
//			char*	�p�X�t�@�C�����ւ̃|�C���^

void GetPath(char *path,const char *file)
{
	char	*p;

	strcpy(path,file);
	p=strrchr(path,'\\');
	if(p!=NULL) *p='\0';
	else		path[0]='\0';
}

///////////////////////////////////////////////////////////
//
//	���w�n�֐�
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	�w��l�܂ł̗�����Ԃ�
//	���l	int		�ő�l
//	�Ԓl	int		����

int randr(int n)
{
	return	rand()%(n+1);
}

///////////////////////////////////////////////////////////
//	�w��͈̗͂�����Ԃ�
//	���l	int		�ŏ��l
//			int		�ő�l
//			bool	0�̋���(true=���� or false)
//	�Ԓl	int		����

int randr(int min,int max,bool z)
{
	int	r;
	int	a=(max-min)+1;

	do	r=rand()%a+min;	while(z==false&&r==0);

	return	r;
}

///////////////////////////////////////////////////////////
//	�O�p�֐�������������
//	���l	�Ȃ�

void InitTriFunc()
{
	int		i;
	double	a;

	for(i=0;i<256;i++)
	{
		a=3.141592*((double)i)/128.0;
		_af_dSinTbl[i]=(int)(sin(a)*256.0);
		_af_dCosTbl[i]=(int)(cos(a)*256.0);
	}
}

///////////////////////////////////////////////////////////
//	sin �̒l���Œ菬���\�L�ŕԂ�
//	���l	int		�p�x(256�ň��)
//	�Ԓl	int		sin ��256�{�����l

int isin(int a)
{
	return	_af_dSinTbl[a&0x000000ff];
}

///////////////////////////////////////////////////////////
//	cos �̒l���Œ菬���\�L�ŕԂ�
//	���l	int		�p�x(256�ň��)
//	�Ԓl	int		cos ��256�{�����l

int icos(int a)
{
	return	_af_dCosTbl[a&0x000000ff];
}

///////////////////////////////////////////////////////////
//
//	�֗��n�֐�
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	�w��t�H�[�}�b�g�̕�������_�C�A���O�ŕ\��
//	���l	bool	true	�\��
//					false	��\��
//			char*	�t�H�[�}�b�g
//			...		�ϐ�

void OpenDebugBox(bool f,const char *format,...)
{
	afErrorBox	eb;
	char	str[1024];

	if(!f) return;

	vsprintf(str,format,(char*)(&format+1));

	eb.SetTitle("�f�o�b�O");
	eb.SetMessage(str);
	eb.OpenBox();
}

///////////////////////////////////////////////////////////
//	�w��t�H�[�}�b�g�̕�������_�C�A���O�ŕ\��
//	���l	char*	�t�H�[�}�b�g
//			...		�ϐ�

void OpenDebugBox(const char *format,...)
{
	afErrorBox	eb;
	char	str[1024];

	vsprintf(str,format,(char*)(&format+1));

	eb.SetTitle("�f�o�b�O");
	eb.SetMessage(str);
	eb.OpenBox();
}
