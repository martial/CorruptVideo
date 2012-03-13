/*
 *  textBoxView.cpp
 *  corrupt-video
 *
 *  Created by Martial on 28/11/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#include "textBoxView.h"

void textBoxView::setup () {
	str="";
	font.loadFont("fonts/Arial.ttf", 9, false, false, false);
	

}

void textBoxView::setString(string str){
	this->str = str;
	fontRect = font.getStringBoundingBox(str, 0.0, 0.0);
	width = fontRect.width + 40;
}
void textBoxView::setFileString(string path) {
	
	ofBuffer file;
	file = ofBufferFromFile(path, true);
	this->str = file.getText();
	fontRect = font.getStringBoundingBox(str, 0.0, 0.0);
	width = fontRect.width + 40;
	
}

void textBoxView::draw() {
	
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 200);
	ofRect(15, 15, width-15 + 20, fontRect.height -15 +40);
	ofDisableAlphaBlending();
	
	ofSetColor(255, 255, 255);
	font.drawString(str, 15 + 20, 15 + 20);
	
	
	

}