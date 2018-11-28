#pragma once

#include "ofMain.h"
#include "corruptVideoApp.h"
#include "updateCheck.h"

#ifdef __linux__
#include "ofxRPiTouch.h"
#endif

class ofApp : public ofBaseApp {

	public:
    
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		//void keyReleased(int key);
		void mouseMoved(int x, int y );
		//void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		//void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void audioIn(float * input, int bufferSize, int nChannels);
    
        void handleTouchScreen();

		corruptVideoApp * app;
		updateCheck		  updateChecker;
    
        float intensityPct;
        float bottomBarHeight;
 
#ifdef __linux__
    
        ofxRPiTouch touchTest, touch;
        bool touchPressed, bMouseMoved;
        ofPoint mousePos, oldMousePos;
    
#endif
    
};
