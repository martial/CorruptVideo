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


#include "corruptDisplay.h"

void corruptDisplay::setup(){
	
	font.load("fonts/Lekton-bold.ttf", 12, true, false, false);
	bigFont.load("fonts/Lekton-bold.ttf", 512, true, false, false);
    
#ifndef __linux__
	sndPlayer.load("mp3/bip.mp3", false);
#endif
	
	oldSec = 0;
	
	message = "";
	messageYPos = -100;
	
	// info txt
	ofBuffer file;
	file = ofBufferFromFile("txt/info.txt", true);
	this->infoStr = file.getText();
	
	textBox.init();
	
}

void corruptDisplay::update() {
	
}

void corruptDisplay::draw() {
	
	if(bMessageVisible && messageYPos < 0) 
		messageYPos += 2.0;
		
	
	if(!bMessageVisible && messageYPos > -100) 
		messageYPos -= 2.0;
	
	
	ofPushMatrix();
	ofTranslate(0, messageYPos, 0);
	drawTopLineString(message);
	ofPopMatrix();
}

void corruptDisplay::drawPreRecordSec(int secs) {
	
	secs -= 1;
	
	int screenW = ofGetWidth();
	int screenH = ofGetHeight();
	
	ofRectangle typeBox = bigFont.getStringBoundingBox(ofToString(secs),0,0);
	
	ofPushMatrix();
	ofTranslate(screenW * .5 - typeBox.width * .5, screenH * .5 - typeBox.height * .5 + typeBox.height, 0);
	ofSetColor(255, 0, 0, 125);
	ofEnableAlphaBlending();
	bigFont.drawString(ofToString(secs), 0,0);
	
	
	ofDisableAlphaBlending();
	ofPopMatrix();
	
	if ( oldSec != secs ) {
		
		ofSetColor(255, 0, 0);
#ifndef __linux__
		sndPlayer.play();
#endif
		
	} else {
		ofSetColor(255,255,255);
	}
	
	oldSec = secs;
	
}

void corruptDisplay::drawRecordingSec(int secs) {
	
	secs -= 1;
	
	drawTopLineString(ofToString(secs) + " secs left");
	
	if(ofGetFrameNum() % 16 > 8 ) { 
		ofSetColor(255, 0, 0);
		ofDrawCircle(20, 16, 6);
	}
	
}

void corruptDisplay::drawTopLineString(string str) {
	
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 125);
	ofDrawRectangle(0,0, ofGetWidth(), 35);
	ofDisableAlphaBlending();
	
	ofSetColor(255);
	font.drawString(str, 35,20);
}

void corruptDisplay::showMessage (string message, int duration) {
	this->message = message;
	timerMessage.setup(duration, 1);
	timerMessage.startTimer();
	ofAddListener(timerMessage.timerReached, this, &corruptDisplay::onTimerDoneHandler);
	bMessageVisible = true;
	
	
}

void corruptDisplay::onTimerDoneHandler(ofEventArgs & e) {
		
	ofRemoveListener(timerMessage.timerReached, this, &corruptDisplay::onTimerDoneHandler);
	bMessageVisible = false;
}

void corruptDisplay::showInfo () {
		
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 125);
	ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
	
	ofSetColor(255);
	font.drawString(infoStr, 25,25);
	
	ofDisableAlphaBlending();
	
	
}


void corruptDisplay::showInputBox () {
	
	
	
	ofSetColor(255);
	ofPushMatrix();
	
	ofTranslate((int)(ofGetWidth() * .5), (int)(ofGetHeight()*.5), 0);
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 75);
	ofDrawRectangle(-204,(int) (- 15) , 408 , 25);
	ofDisableAlphaBlending();
	
	//ofTranslate(ofGetWidth() * .5, ofGetHeight()*.5, 0);
	ofTranslate( (int)(- textBox.getWidth() * .5),  2, 0);
	ofSetColor(255);
	textBox.draw();
	ofPopMatrix();
	
	ofPushMatrix();
	
	
	ofTranslate((int)(ofGetWidth() * .5), (int)(ofGetHeight()*.5), 0);	
	
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 75);
	ofDrawRectangle(-84, -47 , 168 , 25);
	ofDisableAlphaBlending();
	ofSetColor(255);
	string req = "TYPE YOUR REQUEST : ";
	font.drawString(req, (int)(- font.stringWidth(req) * .5), -31);
	ofPopMatrix();
	
	ofPopMatrix();
	
	
	
}

