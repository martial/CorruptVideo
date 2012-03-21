/*
 *  originalCorruptGlitch.h
 *  corrupt-video
 *
 *  Created by Martial on 09/10/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MRGDCRPTGLTCH
#define MRGDCRPTGLTCH

#include "ofMain.h"
#include "abstractGlitch.h"

class mergedCorruptGlitch : public  abstractGlitch {
	
	public :
	
	mergedCorruptGlitch();
	void glitch(char * buffer, int filesize);
	
};

#endif