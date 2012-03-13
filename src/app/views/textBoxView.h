/*
 *  textBoxView.h
 *  corrupt-video
 *
 *  Created by Martial on 28/11/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#ifndef TXTBXVIEW
#define TXTBXVIEW

#include "ofMain.h"

class textBoxView {

public:
	
	virtual void setup();
	virtual void setString(string str);
	virtual void setFileString(string path);
	
	virtual void draw();
	
	int width;
	string str;
	ofTrueTypeFont font;
	ofRectangle fontRect;
	
	private :
	
	
	
	
};


#endif