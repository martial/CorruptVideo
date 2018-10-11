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
	
	bButtonRecordSent = false;
	bBoutonImageSearchSent = false;
	oldToggleVal = 0;
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
	ard.sendDigitalPinMode(2, ARD_INPUT);		// on diecimelia: 11 pwm?*/
	ard.sendDigitalPinMode(4, ARD_INPUT);
	bSetupArduino = true;
	
}

void arduinoManager::updateArduino () {
	ard.update();
	
	int toggleVal = ard.getDigital(2);
	
	if(toggleVal != oldToggleVal ) {
		int a = 0;
		ofNotifyEvent(button1Event, a, this);
	} 
	oldToggleVal = toggleVal;
	
	int buttonValue = ard.getDigital(4);
	
	if(buttonValue == 1 ) {
		if(!bBoutonImageSearchSent) ofNotifyEvent(button2Event, buttonValue, this);
		bBoutonImageSearchSent = true;
	} else {
		bBoutonImageSearchSent = false;
	}
	
	int knobValue = ard.getAnalog(0);
	
	if(knobValue != oldKnobValue ) {
		float pct = 1.0 - (float) knobValue / 1024.0;
		ofNotifyEvent(knobEvent, pct, this);
	}
	
	oldKnobValue = knobValue;
	
}

