/*
 *  updateCheck.h
 *  corrupt-video
 *
 *  Created by Martial on 17/01/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */


#ifndef UPDTCHECK
#define UPDTCHECK

#include "ofMain.h"
#include "udpateBoxView.h"
class updateCheck {


public:
	
	void checkIfValid(string version);
	void urlResponse( ofHttpResponse &response);
	void draw();
	void spacePressed();
	string currentVersion, onlineVersion;
	string state;
	udpateBoxView updateBox;
};

#endif