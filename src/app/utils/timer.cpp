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


#include "timer.h"

void timer::setup() {
	
	bActive = false;
	currentMsElapsed = 0;
	
	setTimerDelay(3000);
	
	ofAddListener(timer.timerReached, this, &timer::onTimerDoneHandler);
	
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

void timer::onTimerDoneHandler(ofEventArgs & e) {
	
		ofLog(OF_LOG_NOTICE, "DONE! %d", getSecRemaining());
	
	int dumm = 0;
	ofNotifyEvent(timerDoneEvent, dumm, this);
}
