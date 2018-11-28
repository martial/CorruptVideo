#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(24);
	updateChecker.checkIfValid("0.2");
	
	app = new corruptVideoApp();
	app->setup();
	ofSoundStreamSetup(0,2,this, 44100, 128, 4);
    
    
#ifdef __ARM_ARCH_6__
    
    //ofRemoveListener(ofEvents().mouseMoved, this, &ofApp::mouseMoved);
    
    ofHideCursor();
    // this is ugly
    if(touchTest.init("/dev/input/event0"))
        touch.init("/dev/input/event0");
    
    if(touchTest.init("/dev/input/event1"))
        touch.init("/dev/input/event1");
    
    if(touchTest.init("/dev/input/event2"))
        touch.init("/dev/input/event2");
    
    touchPressed = false;
    
    mousePos.set(0,0);
    
#endif
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
	if(updateChecker.state == "OK") app->update();

#ifdef __ARM_ARCH_6__
    
    handleTouchScreen();
    
#endif
    
    
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

void ofApp::mouseMoved(int x, int y) {
    
    ofLogNotice("Mouse Event Moved") << x << " " << y;
    
    // intensitu
    if( x > 100) {

        float intensityPct = ofNormalize(x, 0.0, ofGetWidth());
        app->glitch.setIntensity(intensityPct);
    }
}


void ofApp::mousePressed(int x, int y, int button) {
    
    ofLogNotice("Mouse Event Pressed") << x << " " << y;
    
    
    if( x < 100) {
        
        // record
        app->startRecord();
    }
    
    
}


void ofApp::handleTouchScreen() {
    
#ifdef __ARM_ARCH_6__
    
 //  ofLogNotice("Mouse Event") << touch.getAbsPos().x << " " << touch.getAbsPos().y;
    
    ofPoint current;
    current.set( touch.getAbsPos().x,  touch.getAbsPos().y);
    
    if(current != mousePos) {
        mouseMoved(touch.getAbsPos().x,  touch.getAbsPos().y);
        mousePos.set( touch.getAbsPos().x,  touch.getAbsPos().y);

    }

    

    
    if ( touch.getButton() != touchPressed) {
        
        touchPressed = touch.getButton();
        
        if(touchPressed) {
            mousePressed(touch.getAbsPos().x,  touch.getAbsPos().y, touch.getMTSlot());
        } else {
            mouseReleased(touch.getAbsPos().x,  touch.getAbsPos().y, touch.getMTSlot());
        }
        
       
        
    }
#endif
}

