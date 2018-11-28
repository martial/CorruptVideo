#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
#ifdef __linux__
    bMouseMoved = false;
#endif
	
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(24);
	updateChecker.checkIfValid("0.2");
	
	app = new corruptVideoApp();
	app->setup();
	ofSoundStreamSetup(0,2,this, 44100, 128, 4);
    
    intensityPct = 1.0;
    
    
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
    
    ofToggleFullscreen();

    
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
    
    
    
    
#ifdef __linux__
    
    if( bMouseMoved ) {
        ofSetColor(255,255);
        ofDrawRectangle(ofGetWidth() - 30, ofGetHeight(), 30, ofNormalize(intensityPct, 0.0, ofGetHeight()) * ofGetHeight());
    }
    
    bMouseMoved = false;
    
    ofPushMatrix();
    ofTranslate(0.0, 50);
    ofSetColor(0,255);
    ofDrawRectangle(0.0, ofGetHeight() - 100, ofGetWidth(), 100);
    ofSetColor(255,0,0);
    ofDrawCircle(ofGetWidth() * .5, ofGetHeight() - 50, 40);
    ofSetColor(255,255);
    ofPopMatrix();

#endif
	
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

        intensityPct = ofNormalize(x, 100, ofGetHeight());
        app->glitch.setIntensity(intensityPct);
        
        
        bMouseMoved = true;
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

