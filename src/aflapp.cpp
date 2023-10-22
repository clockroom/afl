//
//	AFL Application Class by ClockRoom 1999
//	Program by Y.Kumagai ClockRoom 1999
//

///////////////////////////////////////////////////////////
//	インクルード

#include "aflapp.h"

///////////////////////////////////////////////////////////
//	構築

afApp::afApp()
{
}

afApp::~afApp()
{
}

///////////////////////////////////////////////////////////
//	システム

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
//	初期化

void afApp::InitApp()
{
}

void afApp::FinalApp()
{
}

///////////////////////////////////////////////////////////
//	メイン

void afApp::Main()
{
}
