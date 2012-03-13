/*
 *  glitchManager.cpp
 *  CorruptVideo
 *
 *  Created by Martial on 07/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#include "glitchManager.h"


void glitchManager::setup() {
	
	bufferImg = new ofImage();
	glitchImg = new ofImage();
		
	setupGlitches();
	
	setFileFormat(OF_IMAGE_FORMAT_JPEG);
	
	
	// set different qualities
	qualityLevels.push_back(OF_IMAGE_QUALITY_WORST);
	qualityLevels.push_back(OF_IMAGE_QUALITY_LOW);
	qualityLevels.push_back(OF_IMAGE_QUALITY_MEDIUM);
	qualityLevels.push_back(OF_IMAGE_QUALITY_BEST);
	qualityLevels.push_back(OF_IMAGE_QUALITY_HIGH);
	
	formatsAllowed.push_back(OF_IMAGE_FORMAT_JPEG);
	formatsAllowed.push_back(OF_IMAGE_FORMAT_TIFF);
	formatsAllowed.push_back(OF_IMAGE_FORMAT_GIF);
	
	setCompressionQuality(.5);
	setIntensity(1.0);
	
	bHasLoaded = false;
	bFormatMixEnabled = false;
	
	
}

void glitchManager::setupGlitches(){
	
	glitches.push_back ( new mergedCorruptGlitch());
	glitches.push_back ( new originalCorruptGlitch());
	currentGlitch = glitches[0];
	
}


void glitchManager::draw(int x, int y, float width, float height) {
	
	glitchImg->draw(x,y, width, height);
	
}


void glitchManager::drawFullScreen(float width, float height){
	
	int screenW = ofGetWidth();
	int screenH = ofGetHeight();
	
	float x,y;
	ofVec2f imgSize = ofxImgSizeUtils::getSizeRatio(screenW, screenH, width, height);
	x = screenW *.5 - imgSize.x*.5;
	y = screenH *.5 - imgSize.y*.5;
	
	glitchImg->draw(x,y,imgSize.x,imgSize.y);
	
}





void glitchManager::glitchThis(unsigned char * pixels, int width, int height, ofImageType colorMode){
	
	// if no pixels - skip
	if(!pixels) return;
	
	if(bFormatMixEnabled) {
		int rdm = floor(ofRandom(formatsAllowed.size()));
		setFileFormat(formatsAllowed[rdm]);
	}
	
	// choose your glitch class - can be random 
	int index = floor(ofRandom(glitches.size()));
	currentGlitch = glitches[1];
	// update intensity values
	currentGlitch->setIntensity(glitchIntensity);
	
	// thanks to the original example by Kyle McDonald
	// implementation is quite similar, no surprises in there
	
	// we clear memory first 
	
	bufferImg->clear();
	//if(bHasLoaded) glitchImg->clear();
	
	// set pixels and be sure we're converting it to RGB, we'll need this further for image recording
	// also alpha is needed for desktop mode 
	
	bufferImg->setFromPixels(pixels, width, height, colorMode, true);
	bufferImg->setImageType(OF_IMAGE_COLOR);
	
	// save image ( one frame ) locally
	bufferImg->saveImage(outputImgURL, currentQuality);
	
	// open buffer from file to get binary data
	ofBuffer file = ofBufferFromFile(outputImgURL, true);
	
	// send this data to glitch it!
	currentGlitch->glitch(file.getBinaryBuffer(), file.size());
	
	file.resetLineReader();
	// create a new image from this
	ofBufferToFile(outputImgURL, file, true);
	
	// and then we try to load this image again
	// glitch can be randomly corrupted, so we have to be careful on this 
	
	bHasLoaded = true;
	if(!glitchImg->loadImage(file)) {
		bHasLoaded = false;
		
	}
	
	// force to RGB again
	glitchImg->setImageType(OF_IMAGE_COLOR);
	
	// clear mem
	file.clear();
	
}



void glitchManager::setGlitchTypeByIndex(int index){
	
}


void glitchManager::setCompressionQuality( float pct){
	qualityPct  =pct;
	currentQuality = qualityLevels[floor(pct * qualityLevels.size())];
}

void glitchManager::setIntensity(float pct){
	glitchIntensity = pct;
}

void glitchManager::enableFormatMix(bool b) {
	bFormatMixEnabled = b;
}

void glitchManager::setFileFormat(ofImageFormat format) {
	
	
	
	switch (format) {
		case OF_IMAGE_FORMAT_JPEG:
				ext = ".jpg";
			break;
			
		case OF_IMAGE_FORMAT_TIFF:
			ext = ".tiff";
			break;
			
			
		case OF_IMAGE_FORMAT_GIF:
			ext = ".gif";
			break;
			
			
		case OF_IMAGE_FORMAT_PNG:
			ext = ".png";
			break;
			
		default:
			break;
	}
	outputImgURL = "images/buffer" + ext;
}


unsigned char * glitchManager::getPixels(){
	return glitchImg->getPixels();
}

