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
	
    ofPixels p;
    p.setFromExternalPixels(pixels, width, height, 3);
    
	haarFinder.findHaarObjects(p, 12,12);
	
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








