/*
 *  timer.cpp
 *  CorruptVideo
 *
 *  Created by Martial on 07/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#include "timer.h"

void timer::setup() {
	
	bActive = false;
	currentMsElapsed = 0;
	
	setTimerDelay(3000);
	
	ofAddListener(timer.TIMER_REACHED, this, &timer::onTimerDoneHandler);
	
}

void timer::setTimerDelay(int delay) {
	
	this->delay = delay;
	
}

void timer::startTimer (int delay){
	
	setTimerDelay(delay);
	startTimer();
}

void timer::startTimer() {
	
	ofLog(OF_LOG_NOTICE, "START TIMER DONE");
	stopTimer();
	timer.setup(delay, 1);
	timer.startTimer();
	
	currentMsElapsed = ofGetElapsedTimeMillis();
	bActive = true;
}

void timer::stopTimer(){
	
	timer.stopTimer();
	timer.reset();
	currentMsElapsed = 0;
	bActive = false;
}

int timer::getSecRemaining(){
	
	if(currentMsElapsed == 0) return 0;
	
	int ms = ofGetElapsedTimeMillis();
	int diff = 1000 + delay - ( ms - currentMsElapsed  );
	return int(floor(diff / 1000));
	
}
bool timer::isActive() {
	return bActive;
}

void timer::onTimerDoneHandler(int & e) {
	
	
	
	ofLog(OF_LOG_NOTICE, "DONE! %d", getSecRemaining());
	
	
	int dumm = 0;
	ofNotifyEvent(timerDoneEvent, dumm, this);
}