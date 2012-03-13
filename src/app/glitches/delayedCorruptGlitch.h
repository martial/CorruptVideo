/*
 *  originalCorruptGlitch.h
 *  corrupt-video
 *
 *  Created by Martial on 09/10/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DLDCRPTGLTCH
#define DLDCRPTGLTCH

#include "ofMain.h"
#include "abstractGlitch.h"

class delayedCorruptGlitch : public  abstractGlitch {
	
	public :
	
	delayedCorruptGlitch();
	void glitch(char * buffer, int filesize);
	void changePos(int filesize);
	
	vector<ofPoint>	positions;
	
	int nbOfReplacements;
	bool bReady;
};

#endif