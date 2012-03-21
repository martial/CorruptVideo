/*
 *  arduinoManager.cpp
 *  corrupt-video
 *
 *  Created by Martial on 09/02/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#include "arduinoManager.h"

void arduinoManager::setup () {
	ard.connect("tty.usbserial-A700dX35", 57600);
	ofAddListener(ard.EInitialized, this, &arduinoManager::setupArduino);
	
	bSetupArduino	= false;
	oldKnobValue = -1;
}

void arduinoManager::update () {
	updateArduino();

}

void arduinoManager::setupArduino(const int & version) {
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &arduinoManager::setupArduino);
	
	for (int i = 0; i < 13; i++){
		ard.sendDigitalPinMode(i, ARD_OUTPUT);
	}
	
	ard.sendAnalogPinReporting(0, ARD_ANALOG);	// AB: report data
	ard.sendDigitalPinMode(11, ARD_INPUT);		// on diecimelia: 11 pwm?*/
	bSetupArduino = true;
	
}

void arduinoManager::updateArduino () {
	ard.update();
	
	int buttonValue = ard.getDigital(11);
	
	if(buttonValue == 1 ) {
		if(!bButtonSent) ofNotifyEvent(buttonEvent, buttonValue, this);
		bButtonSent = true;
	} else {
		bButtonSent = false;
	}
	
	int knobValue = ard.getAnalog(0);
	
	if(knobValue != oldKnobValue ) {
		float pct = 1.0 - (float) knobValue / 1024.0;
		ofNotifyEvent(knobEvent, pct, this);
	}
	
	oldKnobValue = knobValue;
	
}

