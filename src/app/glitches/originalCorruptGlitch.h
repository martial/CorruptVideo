/*
 *  originalCorruptGlitch.h
 *  corrupt-video
 *
 *  Created by Martial on 09/10/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ORGNALCPRT
#define ORGNALCPRT

#include "ofMain.h"
#include "abstractGlitch.h"

class originalCorruptGlitch : public  abstractGlitch {
	
	public :
	
	originalCorruptGlitch();
	void glitch(char * buffer, int filesize);
	
};

#endif
