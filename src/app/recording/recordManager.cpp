/*
 *  recordManager.cpp
 *  CorruptVideo
 *
 *  Created by Martial on 07/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#include "recordManager.h"

void recordManager::setup(string recordDir) {
	
	this->recordDir = recordDir;
	
	// first check if folder video exists
	ofDirectory dir;
	
    dir.open(recordDir);
    if (!dir.exists()) {
		dir.create();
		dir.setWriteable(true);
		dir.setReadOnly(false);
	}
	
	videoDir = "videos";
	gifDir = "gifs";
	
	
	gifFrameDelay = 6;
	
	bRecordAllowed = false;
	bProcessingGif = false;
	
	ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &recordManager::onGifSavedHandler);
	
}

void recordManager::allowRecording(int & e) {
	
	allowRecording();
	
}
void recordManager::allowRecording() {
	
	bRecordAllowed = true;
	
}

bool recordManager::isRecording() {
	return bRecordAllowed;
}

void recordManager::setupRecording(int width, int height) {
		
	currW = width;
	currH = height;
	
	// clear memory
	if(videoSaver) 
		videoSaver = NULL;
		
	
	// go for new instance of video saver
	// buggy if we don't 
	videoSaver = new ofxQtVideoSaver();
	videoSaver->setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_NORMAL);
	
	currentVideoName = getNextAvailableName(videoDir);
	
	videoSaver->setup(width, height, recordDir + "/" + videoDir +"/" + currentVideoName + ".tmp");
	
	// setup gifSaver
	gifSaver.setup(width, height, .15, 32);
	
	
}
void recordManager::stopRecord(){
	
	videoSaver->finishMovie();
	
	// rename movie to .mov to prevent user closing app when recording
	
	ofFile video;
	video.open(  recordDir + "/" + videoDir +"/" + currentVideoName+".tmp", ofFile::ReadWrite);
	
	if(video.exists() ){
		
		video.renameTo(recordDir + "/" + videoDir +"/" + currentVideoName + ".mov");
		
	} else {
		
		ofLog(OF_LOG_NOTICE, "failing renaming .. " + currentVideoName);
	}
	
	
	// and save gif!
	
	gifSaver.save(  recordDir + "/" + gifDir +"/" + getNextAvailableName(gifDir)+".gif");
	
	bProcessingGif = true;
	bRecordAllowed = false;
	
}

void recordManager::addFrames(unsigned char * pixels, float fps){
	
	if(!bRecordAllowed) return;
	
	if(videoSaver->bAmSetupForRecording() ) 
		videoSaver->addFrame(pixels, 1.0f / 24.0f);
	
	if ( ofGetFrameNum() % gifFrameDelay == 0 ) 
		gifSaver.addFrame(pixels, currW, currH, 24);
	
}


//========================================================================


void recordManager::setGifFrameDelay(int gifFrameDelay) {
		
	this->gifFrameDelay = gifFrameDelay;
}


void recordManager::onGifSavedHandler(string &fileName) {
	
	//string gifPath = recordDir + "/" + gifDir +"/" +fileName;
	ofNotifyEvent(gifCreatedEvent, fileName, this);
	bProcessingGif = false;
}


//========================================================================

string recordManager::getNextAvailableName (string subdir) {
	
	// we want to get a name for our media
	
	int numOfFiles = 0;
	
	// first check if folder video exists
	ofDirectory dir;
	
    dir.open(recordDir +"/" + subdir +"/");
	ofLog(OF_LOG_NOTICE, recordDir +"/" + subdir +"/");
    if (!dir.exists()) {
		dir.create();
		dir.setWriteable(true);
		dir.setReadOnly(false);
		
	} else {
		
		numOfFiles = dir.listDir();
	}
	
	// clean wrong files -
	int validCount = 0;
	for ( int i=0; i<numOfFiles; i++ ) {
		ofFile file = dir.getFile(i);
		string ext = file.getExtension();
		if (ext == "tmp" || ext == "ficache" ) {
			file.remove();
		} else {
			file.renameTo(recordDir +"/" + subdir +"/" + subdir +"_" + ofToString(validCount) + "."+ext);
			validCount++;
		}
	}
	
    dir.reset();
	
	numOfFiles++;
	
	return "glitch_" + ofToString(numOfFiles);
	
}