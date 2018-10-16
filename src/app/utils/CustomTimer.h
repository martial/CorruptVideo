/*
 *  appTimer.h
 *  corrupt-video
 *
 *  Created by Martial on 25/10/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#ifndef APPTMR
#define APPTMR

#include "ofMain.h"
#include "ofxTimer.h"


class CustomTimer {
	
public:
	
	void setup();
	
	void setTimerDelay(int delay);
	
	void startTimer (int delay);
	void startTimer ();
	void stopTimer();
	
	int getSecRemaining();
	bool isActive();
	
	void onTimerDoneHandler(ofEventArgs & e);
	
	ofEvent<int> timerDoneEvent;
	
	private : 
	
	ofxTimer timer;
	
	int delay;	
	int currentMsElapsed;

	bool bActive;
	
};

#endif
