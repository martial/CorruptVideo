/*
 *  corruptDisplay.h
 *  CorruptVideo
 *
 *  Created by Martial on 08/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */


#ifndef APPDISPL
#define APPDISPL

#include "ofMain.h"
#include "ofxTimer.h"
#include "textInput.h"


class corruptDisplay {
	
public:
	
	void setup();
	void update();
	void draw();
	void drawPreRecordSec(int secs);
	void drawRecordingSec(int secs);
	void drawTopLineString(string str);
	
	void showMessage (string message, int duration); 
	void showInputBox();
	
	void showInfo();
	
	textInput		textBox;
	
private :
	
	void onTimerDoneHandler(ofEventArgs & e);
	
	ofTrueTypeFont	font,bigFont;
	ofSoundPlayer	sndPlayer;
	
	
	int oldSec;
	
	ofxTimer	timerMessage;
	string		message;
	bool		bMessageVisible;
	float		messageYPos;
	
	string infoStr;
};

#endif
