//
//	AFL Application Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "aflapp.h"

///////////////////////////////////////////////////////////
//	�\�z

afApp::afApp()
{
}

afApp::~afApp()
{
}

///////////////////////////////////////////////////////////
//	�V�X�e��

bool afApp::DefAppSwitch(int nFunc)
{
	switch(nFunc)
	{
	case APP_INIT: InitApp(); return true;
	case APP_FINAL:FinalApp();return true;
	case APP_MAIN: Main();	  return true;
	}

	return false;
}

bool afApp::AppSwitch(int nFunc)
{
	return afApp::DefAppSwitch(nFunc);
}

///////////////////////////////////////////////////////////
//	������

void afApp::InitApp()
{
}

void afApp::FinalApp()
{
}

///////////////////////////////////////////////////////////
//	���C��

void afApp::Main()
{
}
