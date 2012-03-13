/*
 *  faceTrackWrapper.cpp
 *  CorruptVideo
 *
 *  Created by Martial on 09/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#include "faceTrackWrapper.h"

void faceTrackWrapper::setup() {
	
	haarFinder.setup("facetrack/haarcascade_frontalface_default.xml");
	haarFinder.setScaleHaar(1.8);
	currentFaceDetected = 0;
	bHasFaces = FALSE;
	bIsFaceStable = FALSE;
	noFaceLackCount = 0;
	faceStableCount = 0;
	
	
}

void faceTrackWrapper::findFaces(unsigned char * pixels, int width, int height) {
	
	haarFinder.findHaarObjects(pixels, width, height,12,12);
	
	int numOfBlobs = haarFinder.blobs.size();
	
	if( currentFaceDetected != numOfBlobs ) {
		
		// something changed
		
		if ( !bHasFaces && numOfBlobs > 0 ) {
			bHasFaces = true;
			noFaceLackCount = 0;
			faceStableCount = 0;
		}
		
		//ofLog(OF_LOG_NOTICE, "FACE CHANGED : %d", numOfBlobs);
		
		currentFaceDetected = numOfBlobs;
		
	}
	
	if(bHasFaces && !bIsFaceStable) {
		faceStableCount++;
		if(faceStableCount > 20 ) {
			bIsFaceStable = true;
			ofNotifyEvent(faceDetectedChangedEvent, currentFaceDetected, this);
			//ofLog(OF_LOG_NOTICE, "FACE STABLE : %d", currentFaceDetected);
		}
	}
	
	if(bHasFaces && bIsFaceStable && currentFaceDetected == 0) {
		noFaceLackCount++;
		if(noFaceLackCount > 30 ) {
			// we've lost it
			bHasFaces = false;
			bIsFaceStable = false;
			noFaceLackCount = 0;
			faceStableCount = 0;
			ofNotifyEvent(faceDetectedChangedEvent, currentFaceDetected, this);
			//ofLog(OF_LOG_NOTICE, "FACE LOST... : %d", currentFaceDetected);
		}
	}
	
	
	
}

void faceTrackWrapper::drawFaces(int videoWidth, int videoHeight) {
	
	
	int screenW = ofGetWidth();
	int screenH = ofGetHeight();
	
	float x,y, scalex, scaley;
	ofVec2f imgSize = ofxImgSizeUtils::getSizeRatio(screenW, screenH, videoWidth, videoHeight);
	x = screenW *.5 - imgSize.x*.5;
	y = screenH *.5 - imgSize.y*.5;
	
	scalex = imgSize.x / videoWidth;
	scaley = imgSize.y / videoHeight;
	
	int numOfBlobs = haarFinder.blobs.size();
	
	ofNoFill();
	
	for(int i=0; i<numOfBlobs; i++ ) {
		ofRectangle cur = haarFinder.blobs[i].boundingRect;
		ofRect(cur.x*scalex, cur.y*scaley, cur.width*scalex, cur.height*scaley);
	}
	
	ofFill();
}








