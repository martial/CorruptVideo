/*
 *  simpleSlider.h
 *  corrupt-video
 *
 *  Created by Martial on 02/12/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#ifndef SMPLSLD
#define SMPLSLD

#include "ofMain.h"
#include "abstractComponent.h"

class simpleSlider : public abstractComponent {
	
	
public:
	
	simpleSlider();
	void setup(string label, float width, float height, ofTrueTypeFont * font);
	void setup(string name, float * value, float width, float height, ofTrueTypeFont * font);
	void update();
	
	void draw();
	void draw(float x, float y);
	
	bool hitTest(int x, int y);
	
	void mouseDragged(int x, int y, int button);
	void mouseMoved(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased() {bActive=false;};
	
	float	* value;
	float	pct;
	ofEvent	<float>	  eventUpdate;
	ofPoint padding;
	
private:
	
	ofTrueTypeFont * font;
	ofRectangle fontRect;
	
	ofColor		normalColor;
	ofColor		rollOverColor;
	ofColor		bgColor;
	ofColor		sliderColor;
	
	bool		bActive;
	
};

#endif