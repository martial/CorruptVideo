#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(24);
	updateChecker.checkIfValid("0.2");
	
	app = new corruptVideoApp();
	app->setup();
	ofSoundStreamSetup(0,2,this, 44100, 128, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
	if(updateChecker.state == "OK") app->update();

    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(0, 0, 0);
        
	if(updateChecker.state == "OK") {
		
		app->draw();
		
	} else {
		
		updateChecker.draw();
		
	}
	
}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	app->audioIn(input, bufferSize);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	switch ( key ) {
	
        case 32:
        updateChecker.spacePressed();
        break;
			
	}
}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

