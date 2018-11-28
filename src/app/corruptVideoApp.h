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

#ifndef CRPTAPP
#define CRPTAPP

#include "ofMain.h"
#include "videoManager.h"
#include "simpleGui.h"
#include "glitchManager.h"
#include "CustomTimer.h"
#include "recordManager.h"
#include "gifWebUploader.h"
#include "corruptDisplay.h"
#include "ofxSoundManager.h"
#include "faceTrackWrapper.h"
#include "googleJson.h"
#include "arduinoManager.h"

class corruptVideoApp {
	
	
public:
	
	void setup();
	void update();
	void draw();
	
	void checkForUpdate();
	
	void setVideoMode(corruptVideoMode mode);
	void setFaceTrackMode(bool b);
	void setGlitchIntensity(float pct);
	void setFFTMode(bool b);
	void setGlitchType();
	void setGifUpload(string folder);
	
	void setRecordDuration(int duration);
	void setPreRecordDelay(int delay);
	
	void startRecord();
	void stopRecord();
	
	void showGui(bool b);
	void toggleGui();
	
	void audioIn(float * input, int bufferSize);
	
	void exit();
    
    glitchManager    glitch;
    
    bool bIsRecording;

	
private:
	
	simpleGui		gui;
	videoManager	video;
	recordManager	recorder;
	CustomTimer			preRecordTimer, recordTimer;
	gifWebUploader	gifUpload;
	corruptDisplay	display;
	ofxSoundManager	soundManager;
	googleJson		ggleJson;
	
	faceTrackWrapper * faceTrack;
	arduinoManager arduino;
	
	void onGuiEventHandler ( string & name ); 
	void onGifCreatedHandler( string & filename);
	void onGifUploadErrorHandler( string & message );
	void onFaceTrackedHandler(int & numOffaces);
	void onGoogleRequestHandler( string & req);
	void onKeyPressedEventHandler(ofKeyEventArgs & e);
	// for events
	void startRecord(int & e) {startRecord();};
	void stopRecord(int & e)  { stopRecord();};
	
	bool	bFaceTrackMode, bFFTMode, bInfoVisible, bGuiVisible;;
	int		recordDuration, preRecordDelay;
	
	
	
	void onButton1EventHandler(int & e);
	void onButton2EventHandler(int & e);
	void onKnobEventHandler(float & val);
	bool bWebcam;
	
};

#endif
