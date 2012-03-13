#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(24);
	updateChecker.checkIfValid("0.1");
	
	app = new corruptVideoApp();
	app->setup();
	
	
	ofSoundStreamSetup(0,2,this, 44100, 128, 4);	
}

//--------------------------------------------------------------
void testApp::update(){
	if(updateChecker.state == "OK") app->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0, 0, 0);
	if(updateChecker.state == "OK") {
		
		app->draw();
		
	} else {
		
		updateChecker.draw();
		
	}
	
}


//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
	app->audioIn(input, bufferSize);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	switch ( key ) {
	
	case 32:
	updateChecker.spacePressed();
	break;
			
	}
}


//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

