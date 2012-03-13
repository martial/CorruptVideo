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

#include "simpleSlider.h"

simpleSlider::simpleSlider() {
	abstractComponent::abstractComponent();
	value = NULL;
}

void simpleSlider::setup(string label, float width, float height, ofTrueTypeFont * font){
	
	abstractComponent::setup(label);
	
	this->width		= width;
	this->height	= height;
	this->font		= font;
		
	pos.set(0.0, 0.0, 0.0);
	pct = 0.0;
	bActive = false;
	
	normalColor.set(255, 255, 255);
	rollOverColor.set(125, 125,125);
	
	
	bgColor.set(125, 125, 125);
	sliderColor.set(0, 0,0);
	
	fontRect = font->getStringBoundingBox(label, 0.0, 0.0);
}

void simpleSlider::setup(string label, float * value, float width, float height, ofTrueTypeFont * font){
	
	setup(label, width, height, font);
	this->value = value;
	
	
	
}
void simpleSlider::update(){
	abstractComponent::update();
	
}

void simpleSlider::draw(){
	
	abstractComponent::draw();
	
	draw(pos.x, pos.y);
	
}
	

void simpleSlider::draw(float x, float y){
	
	if (!bActive && value ) pct = *value;
	
	abstractComponent::draw(x,y);
	
	ofPushMatrix();
	ofTranslate(x, y, 0.0);
	
	ofSetColor(normalColor);
	ofRect(0, 0, width, height);
	
	ofSetColor(bgColor);
	ofRect(padding.x, padding.y, width - padding.x * 2, height - padding.y * 2);
	
	
	ofSetColor(0, 0, 0);
	ofRect(padding.x, padding.y, (width - padding.x * 2) *pct, height- padding.y * 2);
	
	ofSetColor(255);
	fontRect = font->getStringBoundingBox(label + " " + ofToString(0.99,2), 0.0, 0.0);
	font->drawString(label + " " + ofToString(pct,2), round(width*.5 - fontRect.width*.5), (int)(height * .5 + fontRect.height * .5 ));
	
	ofPopMatrix();
	ofSetColor(255, 255, 255);
	
	
}

void simpleSlider::mouseDragged(int x, int y, int button) {
	
	if(bActive ) {
		pct =  ofClamp(( ofGetMouseX() - pos.x - padding.x  ) / ( width - padding.x * 2), 0.0, 1.0);
		ofNotifyEvent(eventUpdate, pct, this );
	}
	
}



void simpleSlider::mouseMoved(int x, int y) {
		
	abstractComponent::mouseMoved(x,y);
	
	
}

void simpleSlider::mousePressed(int x, int y){
	abstractComponent::mousePressed(x,y);
	if(hitTest(x,y)) {
		bActive = true;
	}
	
	
}

bool simpleSlider::hitTest(int x, int y) {
	ofPoint realPos;
	float realWidth, realHeight;
	
	realPos.set(pos.x + padding.x, pos.y + padding.y);
	realWidth = width - ( padding.x * 2);
	realHeight= height;
	
	return ((x > realPos.x) && (x < realPos.x + realWidth) && (y > realPos.y) && (y< realPos.y + realHeight));	
}
