//
//	AFL Debug Queue Class by ClockRoom 2002
//	Program by Y.Kumagai ClockRoom 2002
//
//	First Edition 2002/01/06
//	Last  Edition 2002/01/06
//
//	afDebugQueue
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afldefine.h>
#include <aflgraphics.h>
#include <afldebug.h>

///////////////////////////////////////////////////////////
//	�\�z

afDebugQueue::afDebugQueue()
{
	pdpsString=PNULL;
	cString=0;
	PosX=0;
	PosY=24;
	ColorText=RGB(255,255,255);
}

afDebugQueue::~afDebugQueue()
{
	ClearQueue();
}

///////////////////////////////////////////////////////////
//	�L���[������
//
//	���l �Ȃ�
//
//	�Ԓl �Ȃ�

void afDebugQueue::ClearQueue()
{
	int	i;

	for(i=0;i<cString;i++) delete[] pdpsString[i];
	delete[] pdpsString;
	pdpsString=PNULL;
	cString=0;
}

///////////////////////////////////////////////////////////
//	�\����Ԃ�ݒ�
//
//	���l int		�\������w���W
//		 int		�\������x���W
//		 COLORREF	�����F
//
//	�Ԓl �Ȃ�

void afDebugQueue::SetShowState(int x,int y,COLORREF ct)
{
	PosX=x;
	PosY=y;
	ColorText=ct;
}

///////////////////////////////////////////////////////////
//	�L���[�ɕ�������|�X�g
//
//	���l char*	�t�H�[�}�b�g������
//		 ...	�t�H�[�}�b�g����
//
//	�Ԓl �Ȃ�

void afDebugQueue::PostString(const char *psFormat,...)
{
	char	str[1024];
	char	**pp;
	int		i;

	//	�o�b�t�@���R�s�[
	pp=new char*[cString+1];
	for(i=0;i<cString;i++) pp[i]=pdpsString[i];

	//	��������|�X�g
	vsprintf(str,psFormat,(char*)(&psFormat+1));
	pp[cString]=new char[strlen(str)];
	strcpy(pp[cString],str);

	//	�o�b�t�@��ݒ�
	delete[] pdpsString;
	pdpsString=pp;
	cString++;
}

///////////////////////////////////////////////////////////
//	�L���[�̓��e��\���i�\����̓L���[��j���j
//
//	���l �Ȃ�
//
//	�Ԓl �Ȃ�

void afDebugQueue::Show()
{
	afScreen	scr;
	afDC	dc;
	int		i;

	scr.GetDC(&dc);
	for(i=0;i<cString;i++)
	{
		dc.Text(PosX,PosY+i*16,pdpsString[i],16,false,ColorText);
	}
	scr.ReleaseDC(&dc);

	ClearQueue();
}
