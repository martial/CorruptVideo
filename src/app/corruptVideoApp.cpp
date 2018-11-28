/*
 *   
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 *  
 */

#include "corruptVideoApp.h"

void corruptVideoApp::setup(){
	
	faceTrack = NULL;
		
	video.setup(320, 240);
	glitch.setup();
	preRecordTimer.setup();
	recordTimer.setup();
	recorder.setup();
	display.setup();
	
    /*
	arduino.setup();
	ofAddListener(arduino.button1Event, this, &corruptVideoApp::onButton1EventHandler);
	ofAddListener(arduino.button2Event, this, &corruptVideoApp::onButton2EventHandler);
	ofAddListener(arduino.knobEvent, this, &corruptVideoApp::onKnobEventHandler);
     */
	
	soundManager.setup();
	soundManager.setRangeLimit(1, 8);
	soundManager.setRange(127);
	
	gui.setup(&video, &glitch);
	ofAddListener(gui.guiEvent, this, &corruptVideoApp::onGuiEventHandler );
	
	bGuiVisible	   = false;
	bFaceTrackMode = false;
	bFFTMode	   = false;
	bInfoVisible   = false;
	
	setRecordDuration(11000);
	setPreRecordDelay(4000);
	setGifUpload("public");
	
	display.showMessage("Welcome to youglitch.", 5000);
	
	bWebcam = true;
	
	ofAddListener(ofEvents().keyPressed, this, &corruptVideoApp::onKeyPressedEventHandler);
		
}

void corruptVideoApp::update(){
	
	//arduino.update();
	
	video.update();
	gui.update();
	
	
	if(!video.bHasPixels ) return;
	
	
	// if face track enabled, find faces !
	if( bFaceTrackMode && video.getVideoMode() == CORRUPT_VIDEOMODE_WEBCAM ) {
		faceTrack->findFaces(video.getPixels(), video.width, video.height);
	}
	
	if ( video.getVideoMode() != CORRUPT_VIDEOMODE_OFF ) 
		glitch.glitchThis(video.getPixels(), video.width, video.height, video.colorMode);
	
	
}

void corruptVideoApp::draw(){
	

	ofSetColor(255,255,255);
    
	
	
	if(glitch.bHasLoaded) {
		
		glitch.drawFullScreen(video.width, video.height);
		
		// we try to send the frames to record.
		// by default recorder is not allowed so no worries
		recorder.addFrames(glitch.getPixels(), 1.0 / 24.0);
		
	}
	
	if( bFaceTrackMode && video.getVideoMode() == CORRUPT_VIDEOMODE_WEBCAM ) 
		faceTrack->drawFaces(video.width, video.height);
	
	
	if ( video.getVideoMode() == CORRUPT_VIDEOMODE_IMGSEARCH && !recorder.isRecording())
		display.showInputBox();
		
	
	if(preRecordTimer.getSecRemaining() > 0 ) display.drawPreRecordSec(preRecordTimer.getSecRemaining());
	if(recordTimer.getSecRemaining() > 0 ) display.drawRecordingSec(recordTimer.getSecRemaining());
	if(recorder.bProcessingGif) display.drawTopLineString("Processing GIF");
	
	display.draw();
	
	if(bInfoVisible) display.showInfo();
	
	if( bGuiVisible ) gui.draw();
	
	
}

//========================================================================

void corruptVideoApp::startRecord(){
    
    ofLogNotice("start  record..");

	
	// delete event by security
    ofRemoveListener(preRecordTimer.timerDoneEvent, this, &corruptVideoApp::startRecord);
	ofRemoveListener(preRecordTimer.timerDoneEvent, this, &corruptVideoApp::stopRecord);
	
	// we setup the recording stuff, mainly for the size
	recorder.setupRecording(video.width, video.height);
	recorder.allowRecording();
	
	// and set the time duration
	recordTimer.startTimer(recordDuration);
	ofAddListener(recordTimer.timerDoneEvent, this, &corruptVideoApp::stopRecord);
	
	// we might want to hide the GUI here
	gui.disable();
	gui.changeSet(0);
}


void corruptVideoApp::stopRecord(){
	
	ofRemoveListener(recordTimer.timerDoneEvent, this, &corruptVideoApp::stopRecord);
	recorder.stopRecord();
	gui.enable();
	
}



//========================================================================


void corruptVideoApp::setVideoMode(corruptVideoMode mode){
	video.setVideoMode(mode);
}

void corruptVideoApp::setGifUpload(string folder) {
	gifUpload.setup(folder);
	ofAddListener(recorder.gifCreatedEvent, &gifUpload, &gifWebUploader::sendFile );
	ofAddListener(recorder.gifCreatedEvent, this, &corruptVideoApp::onGifCreatedHandler );
	ofAddListener(gifUpload.gifMaxSizeEvent, this, &corruptVideoApp::onGifUploadErrorHandler );
	
	
}

void corruptVideoApp::setFaceTrackMode(bool b){
	
	if(b && !faceTrack) {
		
		faceTrack = new faceTrackWrapper();
		faceTrack->setup();
		ofAddListener(faceTrack->faceDetectedChangedEvent, this, &corruptVideoApp::onFaceTrackedHandler);
	} 
	
	bFaceTrackMode = b;
	
}

void corruptVideoApp::setGlitchIntensity(float pct){
	
}

void corruptVideoApp::setFFTMode(bool b){
	bFFTMode = b;
}

void corruptVideoApp::setGlitchType(){
	
}

void corruptVideoApp::showGui(bool b){
	bGuiVisible = b;
	
	(bGuiVisible) ? gui.enable() : gui.disable();

}

void corruptVideoApp::toggleGui() {
	showGui(!bGuiVisible);
}

void corruptVideoApp::setRecordDuration(int duration) {
	recordDuration = duration;
}

void corruptVideoApp::setPreRecordDelay(int delay) {
	preRecordDelay = delay;
}


//========================================================================
/* GUI events - catch by btn name */ 

void corruptVideoApp::onGuiEventHandler ( string & name ) {
	
	
	if ( name == "Webcam" ) {
		setVideoMode(CORRUPT_VIDEOMODE_WEBCAM);
		gifUpload.setMode(CORRUPT_VIDEOMODE_WEBCAM);
		gui.videoSlider->bEnabled = false;
		gifUpload.setKeyWord("");
	}
	
	if ( name == "Load movie" ) {
		setVideoMode(CORRUPT_VIDEOMODE_MOVIE);
		gifUpload.setMode(CORRUPT_VIDEOMODE_MOVIE);
		gui.videoSlider->bEnabled = true;
		gifUpload.setKeyWord("");
	}
	
	if ( name == "Desktop" ) {
		setVideoMode(CORRUPT_VIDEOMODE_DESKTOP);
		gifUpload.setMode(CORRUPT_VIDEOMODE_DESKTOP);
		gui.videoSlider->bEnabled = false;
		gifUpload.setKeyWord("");
	}
	
	if ( name == "GIF Search" ) {
		setVideoMode(CORRUPT_VIDEOMODE_IMGSEARCH);
		gifUpload.setMode(CORRUPT_VIDEOMODE_IMGSEARCH);
		gui.videoSlider->bEnabled = false;
		ofAddListener(display.textBox.evtEnter, this, &corruptVideoApp::onGoogleRequestHandler);
		gifUpload.setKeyWord("");
	}
	
	if ( name == "Face Track" ) {
		setFaceTrackMode(!bFaceTrackMode);
	}
	
	if ( name == "Glitch type" ) {
		
		glitch.enableFormatMix(gui.animtypeSelectBtn->selected == "RDM");
		
		if(gui.animtypeSelectBtn->selected == "JPEG" ) glitch.setFileFormat(OF_IMAGE_FORMAT_JPEG);
		if(gui.animtypeSelectBtn->selected == "TIFF" ) glitch.setFileFormat(OF_IMAGE_FORMAT_TIFF);
		if(gui.animtypeSelectBtn->selected == "GIF" ) glitch.setFileFormat(OF_IMAGE_FORMAT_GIF);
		if(gui.animtypeSelectBtn->selected == "PNG" ) glitch.setFileFormat(OF_IMAGE_FORMAT_PNG);
		
	}
	
	if ( name == "Record" ) {
		
		if(video.getVideoMode() == CORRUPT_VIDEOMODE_WEBCAM ) {
            ofLogNotice("start timer record..");

            preRecordTimer.startTimer(preRecordDelay);
            // event to tell record we're ok to receive data
            ofAddListener(preRecordTimer.timerDoneEvent, this, &corruptVideoApp::startRecord);
            
		} else {
			
			startRecord();
			
		}
	}
	
	if ( name == "FFT Mode" ) {
		bFFTMode = !bFFTMode;
	}
	
	if ( name == "Info" ) {
		bInfoVisible = !bInfoVisible;
	}
	
}


void corruptVideoApp::onGifCreatedHandler( string & filename ) {
	display.showMessage("Trying to upload gif to www.uglitch.com", 5000);
}

void corruptVideoApp::onGifUploadErrorHandler( string & message ) {
	display.showMessage(message, 5000);
}

void corruptVideoApp::onFaceTrackedHandler(int & numOffaces) {
	
	if(!recorder.isRecording()) {
		
		if(numOffaces > 0 ) {
			
			preRecordTimer.startTimer(preRecordDelay);		
			ofAddListener(preRecordTimer.timerDoneEvent, this, &corruptVideoApp::startRecord);
			
		} else {
			
			preRecordTimer.stopTimer();		
			ofRemoveListener(preRecordTimer.timerDoneEvent, this, &corruptVideoApp::startRecord);
		}
		
	}
}

void corruptVideoApp::onGoogleRequestHandler( string & req) {
		
	video.loadMovie(ggleJson.request(req));
	gifUpload.setKeyWord(ggleJson.urlencode(req));
}

void corruptVideoApp::onKeyPressedEventHandler(ofKeyEventArgs & e) {
	
	if(video.getVideoMode() == CORRUPT_VIDEOMODE_IMGSEARCH ) return;
	
	switch(e.key) {
			
		case 'f':
			ofToggleFullscreen();
			break;
			
		case 'g':
			toggleGui();
			break;
			
	}
	
}

//========================================================================
void corruptVideoApp::audioIn(float * input, int bufferSize){
	
	soundManager.audioReceived(input, bufferSize);
	
	if(bFFTMode) {
		
		glitch.setIntensity(soundManager.left[64] * .45);
		glitch.setCompressionQuality(1.0 - soundManager.left[64]);
		
	} else {
		
		
	}
	
	
}

//========================================================================

void corruptVideoApp::checkForUpdate(){
	
}

void corruptVideoApp::onButton1EventHandler(int & e) {
	bWebcam = !bWebcam;
	string mode;
	if(bWebcam ) {
		mode ="Webcam";
	} else {
		mode ="GIF Search";
	}
	onGuiEventHandler(mode);
}
void corruptVideoApp::onButton2EventHandler(int & e) {
	string mode = "Record";
	onGuiEventHandler(mode);
	
	
};
void corruptVideoApp::onKnobEventHandler(float & val) {
	glitch.setIntensity(val*4);
};


void corruptVideoApp::exit(){
	
}
