#include "ofMain.h"
#include "ofApp.h"

#include "ofAppGLFWWindow.h"
//========================================================================
int main( ){
    ofAppGLFWWindow win;
	ofSetupOpenGL(&win, 1640,1480, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
