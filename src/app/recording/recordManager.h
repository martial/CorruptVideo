/*
 *  recordManager.h
 *  CorruptVideo
 *
 *  Created by Martial on 07/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#ifndef RCRDMNGR
#define RCRDMNGR

#include "ofMain.h"
#include "ofxVideoRecorder.h"
#include "ofxGifEncoder.h"


class recordManager {

public:
	
	void setup(string recordDir = "your_glitches");
	
	void setupRecording(int width, int height);
	void allowRecording(int & e);
	void allowRecording();
	void stopRecord();
	
	bool isRecording();
	
	void addFrames(unsigned char * pixels, float fps);
	
	// choose if we want to record every (num) frames
	// careful, put 0 can result in very large gifs
	
	void setGifFrameDelay(int gifFrameDelay);
	
	ofEvent<string> gifCreatedEvent;
	
	bool	bProcessingGif;

	
private:
	
	string getNextAvailableName(string subdir);
	
	void onGifSavedHandler(string &fileName) ;
	
	//ofxQtVideoSaver *  videoSaver;
    //ofVideoGrabber 			vidGrabber;
    ofxVideoRecorder     * videoSaver;
	ofxGifEncoder		gifSaver;
	
	string recordDir, videoDir, gifDir;
	string currentVideoName;

	int		gifFrameDelay;
	
	int		currW, currH;
	bool	bRecordAllowed;
	};


#endif
