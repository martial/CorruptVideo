/*
 *  faceTrackWrapper.h
 *  CorruptVideo
 *
 *  Created by Martial on 09/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#ifndef FCTRACKWRP
#define FCTRACKWRP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxImgSizeUtils.h"

class faceTrackWrapper {

public:
	
	void setup();
	void findFaces(unsigned char * pixels, int width, int height);
	void drawFaces(int videoWidth, int videoHeight);
	ofEvent<int>	faceDetectedChangedEvent;
	
private :
	
	
	ofxCvHaarFinder haarFinder;
	
	
	bool			bHasFaces, bIsFaceStable;
	int				currentFaceDetected;
	
	int				noFaceLackCount;
	int				faceStableCount;
	
	
};

#endif