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
    
   // vidGrabber.setGrabber(videoSaver);
    
    //videoSaver->initRecording();
    

	
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
	videoSaver = new ofxVideoRecorder();
    
    videoSaver->setVideoCodec("mpeg4");
    videoSaver->setVideoBitrate("800k");
    videoSaver->setAudioCodec("mp3");
    videoSaver->setAudioBitrate("192k");
    
    videoSaver->setup(recordDir + "/" + videoDir +"/" + currentVideoName + ".tmp", width, height, 30, 44100, 3);
    videoSaver->start();

	
	currentVideoName = getNextAvailableName(videoDir);
	
	
	// setup gifSaver
    gifSaver.reset();
	gifSaver.setup(width, height, .15, 32);
	
	
}
void recordManager::stopRecord(){
	
	videoSaver->close();
	
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
	
    ofPixels p;
    p.setFromExternalPixels(pixels, currW, currH,  3);
    
	if(videoSaver->isInitialized() )
        bool success = videoSaver->addFrame(p);

		//videoSaver->addFrame(pixels, 1.0f / 24.0f);
	
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
	for ( int i=numOfFiles-1; i>=0; i-- ) {
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
