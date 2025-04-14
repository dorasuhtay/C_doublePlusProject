#include "StdAfx.h"
#include "WinAPI_func.h"

#include <windows.h>


bool EnterFullscreen ()
{
	DEVMODE newSettings;	
	// now fill the DEVMODE with standard settings, mainly monitor frequenzy
	EnumDisplaySettings ( NULL, 0, &newSettings );
	// set desired screen size and resolution	
	newSettings.dmPelsWidth  = 800;		
	newSettings.dmPelsHeight = 600;		
	newSettings.dmBitsPerPel = 16;	

    newSettings.dmPelsWidth = 1024;
    newSettings.dmPelsHeight = 768;
    newSettings.dmBitsPerPel = 32;

	//set those flags to let the next function know what we want to change
	newSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	// and apply the new settings
	if ( ChangeDisplaySettings ( &newSettings, CDS_FULLSCREEN ) 
		!= DISP_CHANGE_SUCCESSFUL )
		return false; // in case of error
	else return true;
}

/*
    memset(&screen,0,sizeof(screen));
    screen.dmSize = sizeof(screen);
    screen.dmPelsWidth = 1024;
    screen.dmPelsHeight = 768;
    screen.dmBitsPerPel = 32;
    screen.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
    ChangeDisplaySettings(&screen, CDS_FULLSCREEN);
*/

void ResetScreen ()
{
	// this resets the screen to the registry-stored values
  	ChangeDisplaySettings ( NULL, 0 );
}


