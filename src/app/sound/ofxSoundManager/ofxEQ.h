/*
 *  ofxSoundManager.h
 *  xmlSettingsExample
 *
 *  Created by Martial Geoffre Rouland on 14/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef OFXEQ
#define OFXEQ

#include "ofMain.h"
#include "fft.h"
#include "FFTOctaveAnalyzer.h"



#define BUFFER_SIZE 128

class ofxEQ {
    
public:
	
	ofxEQ();
	void							setup();
	void							debugDraw();
	void							normalize();
	
	void							setRangeLimit(int min, int max);
	void							setRange(int val);
	void							applyRange(float * arr, float * arrPreview);
	void							setFilterRange(int filterRange);
	
	void							updateFFTAnalyzer (float * currentArr, float * finalArr, float * finalAverageArr, float * finalArrPreview, float * finalAverageArrPreview);
    
	
	void							audioReceived (float * input, int bufferSize); 
	vector<float>			*		getSpectrum();
	
	
	float							smooth;
	
	float					*		left;
	float					*		right;
    
	float					*		leftAverage;
	float					*		rightAverage;
	
	float					*		leftPreview;
	float					*		rightPreview;
	
	float					*		leftAveragePreview;
	float					*		rightAveragePreview;
	
	
	int								range, filterRange;
	float							signal;
	float							ratio;
	
	
	ofFbo							fboEqualizer;
    
        
	FFTOctaveAnalyzer				FFTanalyzer;
	
	float                           linearEQIntercept;
    float                           linearEQSlope;
	
    int								minRange;
	int								maxRange;
	
	
	
	
	
private:	
	
	float					*		leftTemp;
	float					*		rightTemp;
    
	
	fft								myfft;
	
	float							magnitude[512];
	float							phase[512];
	float							power[512];
	float							freq[512/2];
    
    

	
    float                           viewerHeight;
	
	bool							bIsReady;
    
};

#endif