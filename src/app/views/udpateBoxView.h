/*
 *  udpateBoxView.h
 *  corrupt-video
 *
 *  Created by Martial on 17/01/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#ifndef UPDBXVIEW
#define UPDBXVIEW

#include "ofMain.h"
#include "textBoxView.h"

class udpateBoxView : public textBoxView {
	
public:
	udpateBoxView();
	void draw(string currentVersion, string newVersion);
	

	
	
	};


#endif