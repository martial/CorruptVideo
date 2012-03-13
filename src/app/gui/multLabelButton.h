/*
 *  multLabelButton.h
 *  CorruptVideo
 *
 *  Created by Martial on 09/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#ifndef MULTLBLBTN
#define MULTLBLBTN

#include "ofMain.h"
#include "simpleButton.h"
#include "abstractComponent.h"

class multLabelButton : public simpleButton {
	
public:
	
	multLabelButton();
	void setup(string name, float height, ofTrueTypeFont * font);
	void addStringValue(string str);
	void draw();
	void draw(float x, float y);
	
	void mousePressed(int x, int y);
	
	string selected;
	
private:
	
	vector<string> values;
	ofRectangle sndLabelFontRect;
	int index;
};

#endif