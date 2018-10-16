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


#include "CustomTimer.h"

void CustomTimer::setup() {
	
	bActive = false;
	currentMsElapsed = 0;
	
	setTimerDelay(3000);
	
	ofAddListener(timer.timerReached, this, &CustomTimer::onTimerDoneHandler);
	
}

void CustomTimer::setTimerDelay(int delay) {
	
	this->delay = delay;
	
}

void CustomTimer::startTimer (int delay){
	
	setTimerDelay(delay);
	startTimer();
}

void CustomTimer::startTimer() {
	
	stopTimer();
	timer.setup(delay, 1);
	timer.startTimer();
	
	currentMsElapsed = ofGetElapsedTimeMillis();
	bActive = true;
}

void CustomTimer::stopTimer(){
	
	timer.stopTimer();
	timer.reset();
	currentMsElapsed = 0;
	bActive = false;
}

int CustomTimer::getSecRemaining(){
	
	if(currentMsElapsed == 0) return 0;
	
	int ms = ofGetElapsedTimeMillis();
	int diff = 1000 + delay - ( ms - currentMsElapsed  );
	return int(floor(diff / 1000));
	
}
bool CustomTimer::isActive() {
	return bActive;
}

void CustomTimer::onTimerDoneHandler(ofEventArgs & e) {
		
	int dumm = 0;
	ofNotifyEvent(timerDoneEvent, dumm, this);
}
