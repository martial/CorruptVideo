/*
 *  arduinoManager.h
 *  corrupt-video
 *
 *  Created by Martial on 09/02/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#ifndef ARDMNGR
#define ARDMNGR

#include "ofMain.h"

class arduinoManager {

public:
	
	void setup();
	void update();
	
	void setupArduino(const int & version);
	void updateArduino();
	
	ofArduino	ard;
	bool		bSetupArduino;	
		
	
	ofEvent<int> buttonEvent;
	ofEvent<float> knobEvent;
	bool bButtonSent;
	int oldKnobValue;
};

#endif
