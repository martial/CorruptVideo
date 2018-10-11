/*
 *  ofxSoundManager.cpp
 *  xmlSettingsExample
 *
 *  Created by Martial Geoffre Rouland on 14/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxSoundManager.h"

ofxSoundManager::ofxSoundManager() {
	bIsReady = false;
}

void ofxSoundManager::setup() {
	
	
	
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
	
	

	
	minRange = 1;
	maxRange = 8;
	
	bufferCounter = 0;
	drawCounter = 0;
	range = minRange;
	smooth = 1.0;
	signal = 1.0;
	ratio = 0.0;
	
	filterRange = 0;
	
	
	//setRange(maxRange);
	//setRangeLimit(1,18);
	
	recordCount = 0;
	recordDuration = 20;
	
	/*
	 * Setup FFT analyzer
	 */
    
    linearEQIntercept = 1.05f;
    linearEQSlope = 0.5f;
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
	FFTanalyzer.peakHoldTime = 100; // hold longer
	FFTanalyzer.peakDecayRate = 0.95f; // decay slower
	FFTanalyzer.linearEQIntercept = linearEQIntercept; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = linearEQSlope; // increasing gain at higher frequencies
	
	// fbo
    
    viewerHeight = BUFFER_SIZE;
	fboEqualizer.allocate((int)BUFFER_SIZE*2, (int)viewerHeight, GL_RGBA, 4);
	
	//fboEqualizer->setup(s);
	
	/*
	for ( int i=0; i<BUFFER_SIZE; i++ ) {
		vector<float> vec;
		
		for (int j=0; j<recordDuration; j++ ) {
			vec.push_back(0.0);
		} 
		ranges.push_back(vec);
	}
	 */
	
	setRangeLimit(1,8);
	bIsReady = true;
	
}





void ofxSoundManager::setRangeLimit(int min, int max) {
		
	minRange = min;
	maxRange = max;
	
	setRange(maxRange);
	
}

void ofxSoundManager::setRange(int val){
		
	range = int ( (val * 18 ) / BUFFER_SIZE-1);
	if ( range < minRange ) range = minRange;
	if ( range > maxRange ) range = maxRange;
    ratio = .5 - ((range*.5) / 18);
	
	oldRange = minRange;
	
	setFilterRange(filterRange);
		
}

void ofxSoundManager::applyRange(float * arr, float * arrPreview) {
    
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
		for ( i = start; i < end; i++) {
            arrPreview[i] = totalAverage;
		}	
		
		if ( filterRange == -1 ) {
			for ( i = start; i < end; i++) {
            arr[i] = totalAverage;
			}	
		}
		 				
		if ( count == filterRange) {
			for ( i = 0; i < BUFFER_SIZE; i++) {
				arr[i] = totalAverage;
			}
		}
			
		
		count++;		
	}
	
    	
	//return arr;
}

void ofxSoundManager::setFilterRange(int filterRange) {
	
	if ( filterRange > range+1 ) filterRange = range +1;
	if ( filterRange < -1 ) filterRange = -1;
	this->filterRange = filterRange;
	
	//setFiltersBooleans();
}






void ofxSoundManager::updateFFTAnalyzer (float * currentArr, float * finalArr, float * finalAverageArr, float * finalArrPreview, float * finalAverageArrPreview) {
		
	//static int index=0;
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

void ofxSoundManager::calculateRatio () {
	
	for ( int i=0; i<128; i++) {
		
		left[i] = ofClamp(left[i] / (1-ratio) * signal, 0.0, 1.0);
		right[i] = ofClamp(right[i] / (1-ratio) * signal, 0.0, 1.0);
        
        leftAverage[i] = ofClamp(leftAverage[i] / (1-ratio) * signal, 0.0, 1.0);
		rightAverage[i] = ofClamp(rightAverage[i] / (1-ratio) * signal, 0.0, 1.0);
		
	}
	
	
}

void ofxSoundManager::debugDraw () {
	
	//fboEqualizer.allocate(128*2, 100);
	
   
	//fboEqualizer.begin();
	
	ofSetColor(0, 0, 0);
	ofRect(0, 0, BUFFER_SIZE*2, viewerHeight);
	
	ofEnableAlphaBlending();
	
	int totalSteps = (int)(BUFFER_SIZE / range);
	
	for (int i = 0; i < BUFFER_SIZE; i++){
		
		int start, end;
		int step = (int)( i * range  / BUFFER_SIZE );
		start = totalSteps * step;
		end = start + totalSteps;
				
		int colorRatio = 255;
		
		int alpha = (i>=start && i<=end && filterRange-1 == step || filterRange == -1 ) ? 255 : 90;
		
		ofPushMatrix();
		
		
		
		//glTranslated(BUFFER_SIZE/2, 0, 0);
		ofTranslate(BUFFER_SIZE, 0, 0);
		glScalef(-1, 1, 1);
		
		
		ofSetColor(colorRatio, 0, 0,alpha);
		float val = leftPreview[i]*viewerHeight;
		ofRect(i*1, viewerHeight - val, 1, val);
		
		ofSetColor(colorRatio, 255, 0,alpha);
		val = leftAveragePreview[i]*viewerHeight;
		ofRect(i*1, viewerHeight-val, 1, 2);
		
		
		ofPopMatrix();
		
		
		ofSetColor( 0,colorRatio, 0,alpha);
		val = rightPreview[i]*viewerHeight;
		ofRect((BUFFER_SIZE*1)+i*1, viewerHeight - val, 1, val);
		
		ofSetColor(255, colorRatio, 0,alpha);
		val = rightAveragePreview[i]*viewerHeight;
		ofRect((BUFFER_SIZE*1)+i*1, viewerHeight-val, 1, 2);
		
		//ofSetColor(0, 255, 255);
		//val = getSoundRangedForFreq(i)*viewerHeight;
		//ofRect((BUFFER_SIZE*1)+i*1, viewerHeight-val, 1, 2);
		
		
		
		/*
		ofSetColor(colorRatio, 0, 0, 120);
		val = left[BUFFER_SIZE-1-i]*viewerHeight;
		ofRect(i*1, viewerHeight - val, 1, val);
		
		ofSetColor(colorRatio, 255, 0, 120);
		val = leftAverage[BUFFER_SIZE-1-i]*viewerHeight;
		ofRect(i*1, viewerHeight-val, 1, 2);
		
		ofSetColor( 0,colorRatio, 0, 120);
		val = right[i]*viewerHeight;
		ofRect((BUFFER_SIZE*1)+i*1, viewerHeight - val, 1, val);
		
		ofSetColor(255, colorRatio, 0, 120);
		val = rightAverage[i]*viewerHeight;
		ofRect((BUFFER_SIZE*1)+i*1, viewerHeight-val, 1, 2);
		 
		 */
		
		
		
	}
	ofDisableAlphaBlending();
	//fboEqualizer.end();
	
	//fboEqualizer.draw(0,0);
	
}

void ofxSoundManager::storeMediumRange() {
		
	
	int posInArray =   recordCount % recordDuration;
	for ( int i=0; i<BUFFER_SIZE; i++ ) ranges[i][posInArray] = rightAverage[i];
	recordCount++;
	
}

ofPoint ofxSoundManager::getMediumRangeForFreq(int freq) {
	
	float min,  max;
	min = 1.0;
	max = 0.0;
	
	for ( int i=0; i<recordDuration; i++ ) {
		 
		float val =  ranges[freq][i];
		if ( val > max ) max = val;
		if ( val < min ) min = val;
		
	}
	
	ofPoint p;
	p.x = min;
	p.y = max;
	
	return p;
}

float ofxSoundManager::getSoundRangedForFreq(int freq) {
	
	ofPoint range = getMediumRangeForFreq(freq);
	
	float sound = (float)right[freq];
	if ( sound > range.y ) range.y = sound;
	if ( sound < range.x ) range.x = sound;
	
	float max = (float)range.y  - (float)range.x ;
	float val = right[freq] - range.x;
	
	if ( max < 0.1 ) return 0.0;
		
	return ofClamp(val / max, 0.0, 1.0);
	
}



void ofxSoundManager::audioReceived(float * input, int bufferSize){
	
	//if ( range != oldRange ) setRange(range);
	//oldRange = range;
	
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
	
	//storeMediumRange();
        
    /*
    applyRange(left);
    applyRange(right);
           
    applyRange(leftAverage);
    applyRange(rightAverage);
     */
            
    calculateRatio();
			
	bufferCounter++;
	
}


vector<float> * ofxSoundManager::getSpectrum () {
	
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
