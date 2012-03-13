/*
 *  simpleButton.h
 *  corrupt-video
 *
 *  Created by Martial on 23/11/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#ifndef SMPLBTN
#define SMPLBTN

#include "ofMain.h"
#include "abstractComponent.h"

class simpleButton : public abstractComponent {
	
	
public:
	
	simpleButton();
	void setup(string name, float height, ofTrueTypeFont * font);
	void update();
	void draw();
	void draw(float x, float y);
	
	void mouseDragged(int x, int y, int button){};
	void mouseMoved(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased() {};
	
	
		
	bool	bTemporary, bActive;
	
	
	
private:
	
	
	
	
	
	
	
	
protected:
	
	ofColor		normalColor;
	ofColor		rollOverColor;
	ofTrueTypeFont * font;
	ofRectangle fontRect;
	
};

#endif