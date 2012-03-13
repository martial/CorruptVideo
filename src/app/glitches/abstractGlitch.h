/*
 *  abstractGlitch.h
 *  corrupt-video
 *
 *  Created by Martial on 09/10/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ABSTRCTGLITCH
#define ABSTRCTGLITCH

#include "ofMain.h"

class abstractGlitch  {
	
public:
	
	abstractGlitch();
	virtual void glitch(char * buffer, int filesize){};
	virtual void setIntensity(float pct){ intensityPct = pct;};
	float	intensityPct;
	
private:
	
	
	
};

#endif

