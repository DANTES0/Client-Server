#include "sdddApp.h"

//(*AppHeaders
#include "sdddMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(sdddApp);

bool sdddApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	sdddFrame* Frame = new sdddFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
