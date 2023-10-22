//
//	AFL Error Message Box Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afErrorBox
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "afldialog.h"
#include "aflinside.h"

///////////////////////////////////////////////////////////
//	�G���[�{�b�N�X�I�u�W�F�N�g�\�z
//	���l	�Ȃ�

afErrorBox::afErrorBox()
{
	dTitle=0;
	dFileName=0;
	dFunctionName=0;
	dMessage=0;
	dRepair=0;
}

///////////////////////////////////////////////////////////
//	�G���[�{�b�N�X�I�u�W�F�N�g�j��
//	���l	�Ȃ�

afErrorBox::~afErrorBox()
{
	delete[] dTitle;
	delete[] dFileName;
	delete[] dFunctionName;
	delete[] dMessage;
	delete[] dRepair;
}

///////////////////////////////////////////////////////////
//	�^�C�g����ݒ�
//	���l	char*	�^�C�g���̕�����

void afErrorBox::SetTitle(const char *s)
{
	delete[] dTitle;
	if(s==NULL)
	{
		dTitle=0;
		return;
	}
	dTitle=new char[strlen(s)+1];
	strcpy(dTitle,s);
}

///////////////////////////////////////////////////////////
//	�t�@�C������ݒ�
//	���l	char*	�t�@�C�����̕�����

void afErrorBox::SetFileName(const char *s)
{
	delete[] dFileName;
	if(s==NULL)
	{
		dFileName=0;
		return;
	}
	dFileName=new char[strlen(s)+1];
	strcpy(dFileName,s);
}

///////////////////////////////////////////////////////////
//	�֐�����ݒ�
//	���l	char*	�֐����̕�����

void afErrorBox::SetFunctionName(const char *s)
{
	delete[] dFunctionName;
	if(s==NULL)
	{
		dFunctionName=0;
		return;
	}
	dFunctionName=new char[strlen(s)+1];
	strcpy(dFunctionName,s);
}

///////////////////////////////////////////////////////////
//	�G���[���b�Z�[�W��ݒ�
//	���l	char*	���b�Z�[�W�̕�����

void afErrorBox::SetMessage(const char *s)
{
	delete[] dMessage;
	if(s==NULL)
	{
		dMessage=0;
		return;
	}
	dMessage=new char[strlen(s)+1];
	strcpy(dMessage,s);
}

///////////////////////////////////////////////////////////
//	�Ώ��@��ݒ�
//	���l	char*	�Ώ��@�ւ̕�����

void	afErrorBox::SetRepair(const char *s)
{
	delete[] dRepair;
	if(s==NULL)
	{
		dRepair=0;
		return;
	}
	dRepair=new char[strlen(s)+1];
	strcpy(dRepair,s);
}

///////////////////////////////////////////////////////////
//	�G���[�{�b�N�X���J��
//	���l	�Ȃ�
//	�Ԓl	int		��� IDOK ���Ԃ�

int afErrorBox::OpenBox()
{
	LPDIRECTDRAW	ddobj=GetDDObject();
	HWND			hwnd=GetWindowHandle();
	char	ttl[128];
	char	str[2048];

	if(dTitle==0) strcpy(ttl,"�G���[����");
	else		  strcpy(ttl,dTitle);

	str[0]='\0';
	if(dFileName!=0)
	{
		strcat(str,"�t�@�C�����F\n");
		strcat(str,dFileName);
		strcat(str,"\n");
	}

	if(dFunctionName!=0)
	{
		strcat(str,"�֐����F\n");
		strcat(str,dFunctionName);
		strcat(str,"\n");
	}

	if(dFileName!=0||dFunctionName!=0)
	{
		strcat(str,"\n");
	}

	strcat(str,"���e�F\n");
	if(dMessage!=0)
	{
		strcat(str,dMessage);
	}
	else
	{
		strcat(str,"�G���[���������܂����B");
	}

	if(dRepair!=0)
	{
		strcat(str,"\n\n");
		strcat(str,"�Ώ��@�F\n");
		strcat(str,dRepair);
	}

	if(ddobj!=NULL) ddobj->FlipToGDISurface();

	MessageBox(hwnd,str,ttl,MB_OK|MB_ICONEXCLAMATION|MB_SYSTEMMODAL);

	SetCursor(NULL);

	return IDOK;
}
