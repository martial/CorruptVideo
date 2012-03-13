/*
 *  abstractComponent.cpp
 *  corrupt-video
 *
 *  Created by Martial on 02/12/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#include "abstractComponent.h"

abstractComponent::abstractComponent( ) {
	
}

void abstractComponent::setup(string label){
	this->label = label;
	bHasFreePos = false;
	bEnabled = true;
}
void abstractComponent::update(){
}

void abstractComponent::draw(){
	
	
}

void abstractComponent::draw(float x, float y){
	
	pos.set((int)x, (int)y);
}

bool abstractComponent::hitTest (int x, int y) {
	
	return ((x > pos.x) && (x < pos.x + width) && (y > pos.y) && (y< pos.y + height));	
	
}

void abstractComponent::mouseMoved(int x, int y) {
	
	
	
}

void abstractComponent::mousePressed(int x, int y){
	
	if(hitTest(x,y)) {
		ofNotifyEvent(eventClick, label, this );
	}
	
	
}