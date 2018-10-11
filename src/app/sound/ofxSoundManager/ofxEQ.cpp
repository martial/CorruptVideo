/*
 *  ofxEQ.cpp
 *  xmlSettingsExample
 *
 *  Created by Martial Geoffre Rouland on 14/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxEQ.h"

ofxEQ::ofxEQ() {
	bIsReady = false;
    
    minRange = 1;
	maxRange = 8;
	
	range = minRange;
	smooth = 1.0;
	signal = 1.0;
	ratio = 0.0;
	
	filterRange = 0;
    setRangeLimit(1,128);
}

void ofxEQ::setup() {
	
	
	
	left = new float[BUFFER_SIZE];
	right = new float[BUFFER_SIZE];
	
	leftAverage = new float[BUFFER_SIZE];
	rightAverage = new float[BUFFER_SIZE];
	
	leftTemp = new float [BUFFER_SIZE];
	rightTemp = new float [BUFFER_SIZE];
	
	leftPreview = new float[BUFFER_SIZE];
	rightPreview = new float[BUFFER_SIZE];
	
	leftAveragePreview = new float[BUFFER_SIZE];
	rightAveragePreview = new float[BUFFER_SIZE];
	
    memset(left, 0, sizeof(int) * sizeof(left));
    memset(right, 0, sizeof(int) * sizeof(right));
    
    memset(leftAverage, 0, sizeof(int) * sizeof(leftAverage));
    memset(rightAverage, 0, sizeof(int) * sizeof(rightAverage));
	
	memset(leftPreview, 0, sizeof(int) * sizeof(leftPreview));
    memset(rightPreview, 0, sizeof(int) * sizeof(rightPreview));
    memset(leftAveragePreview, 0, sizeof(int) * sizeof(leftAveragePreview));
    memset(rightAveragePreview, 0, sizeof(int) * sizeof(rightAveragePreview));
	
		
	/*
	 * Setup FFT analyzer
	 */
    
    linearEQIntercept = 1.05f;
    linearEQSlope = 0.5f;
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
	FFTanalyzer.peakHoldTime = 200; // hold longer
	FFTanalyzer.peakDecayRate = 0.65f; // decay slower
	FFTanalyzer.linearEQIntercept = linearEQIntercept; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = linearEQSlope; // increasing gain at higher frequencies
	
	// fbo
    
    viewerHeight = BUFFER_SIZE;
	//fboEqualizer.allocate((int)BUFFER_SIZE*2, (int)viewerHeight, GL_RGBA, 4);

	
	bIsReady = true;
	
}





void ofxEQ::setRangeLimit(int min, int max) {
    
	minRange = min;
	maxRange = max;
	
	setRange(maxRange);
	
}

void ofxEQ::setRange(int val){
    
	range = ofClamp( (int)( (val * maxRange ) / BUFFER_SIZE-1), minRange, maxRange);
    ratio = .5 - ((range*.5) / maxRange);
   	
	setFilterRange(filterRange);
    
}

void ofxEQ::applyRange(float * arr, float * arrPreview) {
    
	int step = (int)floor(BUFFER_SIZE / range);
	int count = 0;
    
	float totalAverage;
	
	while ( count < range ) {
        
		int start, end, i;
		start = step * count;
		end = start + step;
		
		if ( count == range - 1 ) end = BUFFER_SIZE;	
		
        totalAverage = 0.0f;
        
		int iter = 0;
		for ( i = start; i < end; i++){
            totalAverage += arrPreview[i];
			iter++;
		}
        
		
		totalAverage /= iter;
		
		// update preview with range
		for ( i = start; i < end; i++) 
            arrPreview[i] = totalAverage;
		
		
		if ( filterRange == -1 ) {
			for ( i = start; i < end; i++) 
                arr[i] = totalAverage;
			
		}
        
		if ( count == filterRange) {
			for ( i = 0; i < BUFFER_SIZE; i++) 
				arr[i] = totalAverage;
			
		}
        
		
		count++;		
	}
	
	
}

void ofxEQ::setFilterRange(int filterRange) {
	
	if ( filterRange > range+1 ) filterRange = range +1;
	if ( filterRange < -1 ) filterRange = -1;
	this->filterRange = filterRange;
	
}






void ofxEQ::updateFFTAnalyzer (float * currentArr, float * finalArr, float * finalAverageArr, float * finalArrPreview, float * finalAverageArrPreview) {
    
	
	float avg_power = 0.0f;	
	
	/* do the FFT	*/
	myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, currentArr,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
	
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		freq[i] = magnitude[i];
	}
	
	FFTanalyzer.calculate(freq);
	
	float numOfAverages = FFTanalyzer.nAverages;
	int step = int( BUFFER_SIZE / numOfAverages);
	int count = 0;
    
    float tempArr[BUFFER_SIZE];
    float tempArrAvg[BUFFER_SIZE];
	
	float tempArrPreview[BUFFER_SIZE];
    float tempArrAvgPreview[BUFFER_SIZE];
    
	while ( count < numOfAverages) {
		
		int start, end, i;
		start = step * count;
		end = start + step;
        
		if ( count == numOfAverages - 1 ) end = BUFFER_SIZE;	
		
		for ( i = start; i < end; i++){
			tempArrAvg[i] = ofNormalize(FFTanalyzer.peaks[count]/50,0, 1);
			tempArr[i] = ofNormalize(FFTanalyzer.averages[count]/50, 0, 1);
			
			tempArrAvgPreview[i] = ofNormalize(FFTanalyzer.peaks[count]/50,0, 1);
			tempArrPreview[i] = ofNormalize(FFTanalyzer.averages[count]/50, 0, 1);
			
		}
		count++;
	}
	
    applyRange(tempArr,tempArrPreview);
    applyRange(tempArrAvg,tempArrAvgPreview);
    
    for (int i= 0; i<BUFFER_SIZE; i++ ) {
		finalArr[i] = tempArr[i];
		finalAverageArr[i] = tempArrAvg[i];
		
		finalArrPreview[i] = tempArrPreview[i];
		finalAverageArrPreview[i] = tempArrAvgPreview[i];
		
    }
    
}

void ofxEQ::normalize () {
	
	for ( int i=0; i<BUFFER_SIZE; i++) {
		
		left[i] = ofClamp(left[i] / (1-ratio) * signal, 0.0, 1.0);
		right[i] = ofClamp(right[i] / (1-ratio) * signal, 0.0, 1.0);
        
        leftAverage[i] = ofClamp(leftAverage[i] / (1-ratio) * signal, 0.0, 1.0);
		rightAverage[i] = ofClamp(rightAverage[i] / (1-ratio) * signal, 0.0, 1.0);
		
	}
	
	
}

void ofxEQ::debugDraw () {
		
    
	//fboEqualizer.begin();
	
   // glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    
	ofSetColor(0, 0, 0);
	ofRect(0, 0, BUFFER_SIZE*2, viewerHeight);
	
	ofEnableAlphaBlending();
	
	int totalSteps = (int)(BUFFER_SIZE / range);
	
	for (int i = 0; i < BUFFER_SIZE; i++){
		
        int colorRatio = 255;
		
		ofPushMatrix();
				
		ofTranslate(BUFFER_SIZE, 0, 0);
		glScalef(-1, 1, 1);
		
		
		ofSetColor(colorRatio, 0, 0);
		float val = leftPreview[i]*viewerHeight;
		ofRect(i*1, 0.0, 1, val);
		
		//ofSetColor(colorRatio, 255, 0);
		//val = leftAveragePreview[i]*viewerHeight;
		//ofRect(i*1, viewerHeight-val, 1, 2);
		
		
		ofPopMatrix();
		
		
		ofSetColor( 0,colorRatio, 0);
		val = rightPreview[i]*viewerHeight;
		ofRect((BUFFER_SIZE*1)+i*1, 0.0, 1, val);
		
		//ofSetColor(255, colorRatio, 0);
		//val = rightAveragePreview[i]*viewerHeight;
		//ofRect((BUFFER_SIZE*1)+i*1, viewerHeight-val, 1, 2);
						
	}
    
	ofDisableAlphaBlending();
	///fboEqualizer.end();
	
	//fboEqualizer.draw(0,0);
	
}






void ofxEQ::audioReceived(float * input, int bufferSize){
		
	if(!bIsReady) return;
    
	
	FFTanalyzer.peakDecayRate = ( smooth == 1 ) ? 0 : 1 -(smooth/10);
	FFTanalyzer.peakHoldTime =  ( smooth == 1 ) ? 0 : 20 -(smooth*20);
    FFTanalyzer.linearEQIntercept = linearEQIntercept; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = linearEQSlope; // increasing gain at higher frequencies
	
    
	for (int i = 0; i < bufferSize; i++){
		leftTemp[i] = input[i*2];
		rightTemp[i] = input[i*2+1];
	}
	
	
    updateFFTAnalyzer(leftTemp, left, leftAverage, leftPreview, leftAveragePreview);
    updateFFTAnalyzer(rightTemp, right, rightAverage, rightPreview, rightAveragePreview);
	
	    
    normalize();
    
	
}


vector<float> * ofxEQ::getSpectrum () {
	
	vector<float> * values = new vector<float>();
	for ( int i=0; i<range; i++ ) {
		int index = (int)(i * 128.0 / (float)range);
		values->push_back(leftPreview[index]);
		
	}
	
	for ( int i=0; i<range; i++ ) {
		int index = (int)(i * 128.0 / (float)range);
		values->push_back(rightPreview[index]);
		
	}
	return values;
}
