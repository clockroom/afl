//
//	AFL Message Box Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//
//	afMsgBox
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "afldialog.h"
#include "afldefine.h"
#include "aflinside.h"

///////////////////////////////////////////////////////////
//	���b�Z�[�W�{�b�N�X�I�u�W�F�N�g�\�z
//	���l	int		�X�^�C��
//						MB_INFOMATION	���p
//						MB_QUESTION		����p

afMsgBox::afMsgBox(int s)
{
	switch(s)
	{
	case MB_INFORMATION:
		nStyle=MB_OK|MB_ICONINFORMATION|MB_APPLMODAL;
		break;
	case MB_QUESTION:
		nStyle=MB_YESNO|MB_ICONQUESTION|MB_APPLMODAL;
		break;
	}
	dTitle=PNULL;
	dMessage=PNULL;
}

///////////////////////////////////////////////////////////
//	���b�Z�[�W�{�b�N�X�I�u�W�F�N�g�j��
//	���l	�Ȃ�

afMsgBox::~afMsgBox()
{
	delete[] dTitle;
	delete[] dMessage;
}

///////////////////////////////////////////////////////////
//	�^�C�g���ݒ�
//	���l	char*	������ւ̃|�C���^

void afMsgBox::SetTitle(const char *s)
{
	delete[] dTitle;
	if(s==NULL)
	{
		dTitle=PNULL;
		return;
	}
	dTitle=new char[strlen(s)+1];
	strcpy(dTitle,s);
}

///////////////////////////////////////////////////////////
//	���b�Z�[�W��ݒ�
//	���l	char*	������ւ̃|�C���^

void afMsgBox::SetMessage(const char *s)
{
	delete[] dMessage;
	if(s==NULL)
	{
		dMessage=PNULL;
		return;
	}
	dMessage=new char[strlen(s)+1];
	strcpy(dMessage,s);
}

///////////////////////////////////////////////////////////
//	���b�Z�[�W�{�b�N�X���J��
//	���l	�Ȃ�
//	�Ԓl	int		����	IDOK	[OK]	�������ꂽ
//							IDYES	[�͂�]	�������ꂽ
//							IDNO	[������]�������ꂽ

int afMsgBox::OpenBox()
{
	LPDIRECTDRAW	ddobj=GetDDObject();
	HWND			hwnd=GetWindowHandle();
	int		ret;
	char	ttl[128];
	char	msg[2048];

	if(dTitle==PNULL) strcpy(ttl,"���b�Z�[�W");
	else			  strcpy(ttl,dTitle);

	if(dMessage==PNULL) strcpy(msg,"���b�Z�[�W�͂���܂���B");
	else				strcpy(msg,dMessage);

	if(ddobj!=NULL) ddobj->FlipToGDISurface();

	ret=MessageBox(hwnd,msg,ttl,nStyle);

	SetCursor(NULL);

	return	ret;
}
