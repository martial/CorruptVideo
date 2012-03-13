//
//  textInput.cpp
//  textInput
//
//  Created by Elliot Woods on 12/09/2011.
//  Copyright 2011 Kimchi and Chips.
//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//

#include "textInput.h"

textInput::textInput() {
	text="";
	position=0;
	cursorx=0;
	cursory=0;
}

void textInput::init() {
	ofAddListener(ofEvents.keyPressed, this, &textInput::keyPressedEvent);
	font.loadFont("fonts/Lekton-bold.ttf", 12, true, false, false);
}

void textInput::draw()  {
	
	bnds = font.getStringBoundingBox(text, 0.0, 0.0);
	
	//draw text
	//ofDrawBitmapString(text, 10,10);
	
	font.drawString(text, 0, 0);
	
	//draw cursor line
	ofPushStyle();
	float timeFrac = 0.5 * sin(3.0f * ofGetElapsedTimef()) + 0.5;
	
	ofColor col = ofGetStyle().color;
	
	ofSetColor(col.r * timeFrac, col.g * timeFrac, col.b * timeFrac);
	ofSetLineWidth(3.0f);
	ofLine(cursorx*8.2 + 0, 13.7*cursory - 12, cursorx*8.2 + 0, 10+13.7*cursory - 6);
	ofPopStyle();
}

void textInput::keyPressed(int key) {	
	//add charachter (non unicode sorry!)
	if (key >=32 && key <=126) {
		text.insert(text.begin()+position, key);
		position++;
	}
	
	if (key==OF_KEY_RETURN) {
		ofNotifyEvent(evtEnter, text, this);
		//if (evtEnter.empty()) {
			//text.insert(text.begin()+position, '\n');
			//position++;
		//}
	}
	
	if (key==OF_KEY_BACKSPACE) {
		if (position>0) {
			text.erase(text.begin()+position-1);
			--position;
		}
	}
	
	if (key==OF_KEY_DEL) {
		if (text.size() > position) {
			text.erase(text.begin()+position);
		}
	}
	
	if (key==OF_KEY_LEFT)
		if (position>0)
			--position;
	
	if (key==OF_KEY_RIGHT)
		if (position<text.size()+1)
			++position;	
	
	//for multiline:
	cursorx = cursory = 0;
	for (int i=0; i<position; ++i) {
		if (*(text.begin()+i) == '\n') {
			++cursory;
			cursorx = 0;
		} else {
			cursorx++;
		}
	}
}

int textInput::getWidth() {
		
	return bnds.width;
}

int textInput::getHeight() {
	
	return bnds.height;
	
}

void textInput::clear() {
	text.clear();
	position=0;
}

void textInput::keyPressedEvent(ofKeyEventArgs &a) {
	keyPressed(a.key);
}