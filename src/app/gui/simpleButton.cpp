/*
 *  simpleButton.cpp
 *  corrupt-video
 *
 *  Created by Martial on 23/11/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#include "simpleButton.h"

simpleButton::simpleButton() {
	abstractComponent::abstractComponent();
}

void simpleButton::setup(string label, float height, ofTrueTypeFont * font){
	abstractComponent::setup(label);
	
	this->height	= height;
	this->font		= font;
	
	// calculate width - 20 padding
	
	fontRect = font->getStringBoundingBox(label, 0.0, 0.0);
	width = fontRect.width + 40;
	
	pos.set(0.0, 0.0, 0.0);
	bRollOver = false;
	
	normalColor.set(255, 255, 255);
	rollOverColor.set(125, 125,125);
	
	bTemporary = true;
	bActive = false;
	
	
}
void simpleButton::update(){
	abstractComponent::update();
}

void simpleButton::draw(){
	draw(pos.x, pos.y);
}

void simpleButton::draw(float x, float y){
	
	abstractComponent::draw(x,y);
		
	ofPushMatrix();
	ofTranslate(x, y, 0.0);
	
	
	ofSetColor((bRollOver || bActive) ? rollOverColor : normalColor);
	ofRect(0.0, 0.0, width, height);
	
	
	ofSetColor(0, 0, 0);
	font->drawString(label, width*.5 - fontRect.width*.5, (int)(height * .5 + fontRect.height * .5 ));
	ofPopMatrix();
	ofSetColor(255, 255, 255);
	
	
}



void simpleButton::mouseMoved(int x, int y) {
	
	abstractComponent::mouseMoved(x,y);
	bRollOver =  hitTest(x,y);
	
}

void simpleButton::mousePressed(int x, int y){
	abstractComponent::mousePressed(x,y);
	if(hitTest(x,y)) {
		
		if(!bTemporary) {
			bActive = !bActive;
		}
		
		//ofNotifyEvent(eventClick, label, this );
	}
	
	
}