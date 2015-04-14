/**
@file 	control_LMS7002App.cpp
@author Lime Microsystems
@brief 	Code for Application Main Class
*/

#include "control_LMS7002App.h"
#include "controlPanelGUI/ResourceImagesLoader.h"
//(*AppHeaders
#include "controlPanel_LMS7002.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(control_LMS7002App);

bool control_LMS7002App::OnInit()
{
    #ifndef __unix__
    wxInitAllImageHandlers();
    wxDisableAsserts();
    wxBitmap *splashImage = CreateBitmapFromPngResource("splashImage");
    wxSplashScreen* splash = new wxSplashScreen( *splashImage,
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          6000, NULL, -1, wxDefaultPosition, wxDefaultSize,
          wxSIMPLE_BORDER|wxSTAY_ON_TOP);    
    #endif
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	controlPanel_LMS7002* Frame = new controlPanel_LMS7002(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    #ifndef __unix__
	delete splash;
    #endif
    return wxsOK;

}


