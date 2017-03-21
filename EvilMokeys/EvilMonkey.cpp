#include "stdwx.h"


//AppFrame Class
#include "AppFrame.h"

class EvilMonkneysApp : public wxApp
{
	virtual bool OnInit();
};

//Create the main Function for the application
IMPLEMENT_APP(EvilMonkneysApp);

bool EvilMonkneysApp::OnInit()
{
	//create the main window

	AppFrame *frame = new AppFrame("Evil Mokeys", wxPoint(100, 100),
		wxSize(900,550));

	frame->Show(TRUE);

	SetTopWindow(frame);
	return true;

}
