/*
 *  abstractComponent.h
 *  corrupt-video
 *
 *  Created by Martial on 02/12/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#ifndef ABSTRCTCMP
#define ABSTRCTCMP

#include "ofMain.h"

class abstractComponent  {
	
public:
	
	abstractComponent();
	virtual void setup(string label);
	virtual void update();
	
	virtual void draw();
	virtual void draw(float x, float y);
	
	
	virtual  bool hitTest(int x, int y);
	virtual  void mouseMoved(int x, int y);
	virtual  void mouseDragged(int x, int y, int button){};
	virtual  void mousePressed(int x, int y);
	virtual  void mouseReleased() {};
	
	ofEvent<string>   eventClick;
	
	
	string label;
	
	bool	bEnabled, bRollOver;
	
	float width, height;
	ofPoint pos;

	
	bool bHasFreePos;
	
	
	
};

#endif