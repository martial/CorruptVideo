/*
 *  originalCorruptGlitch.cpp
 *  corrupt-video
 *
 *  Created by Martial on 09/10/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "delayedCorruptGlitch.h"

delayedCorruptGlitch::delayedCorruptGlitch() {
	abstractGlitch::abstractGlitch();
	bReady = false;
	nbOfReplacements = 0;
}

void delayedCorruptGlitch::glitch(char * buffer, int filesize) {
	
	float rdm = ofRandom(1);
	if(!bReady || rdm > intensityPct) {
		changePos(filesize);
	}
	
	for(int i = 0; i < nbOfReplacements; i++) {
		
		int PosA = positions[i].x;
		int PosB = positions[i].y;
		
		char tmp	 =  buffer[PosA];
		buffer[PosA] =	buffer[PosB];
		buffer[PosB] =	tmp;
		
	}
		
	
	
}


void delayedCorruptGlitch::changePos (int filesize) {
	
	positions.clear();
	
	int scrambleStart = 600;
	int scrambleEnd = filesize;
	
	nbOfReplacements =  floor(intensityPct * 10);
	
	for(int i = 0; i < nbOfReplacements; i++) {
		
		ofPoint pos;
		
		pos.x = (int) (ofRandom (scrambleStart, scrambleEnd - scrambleStart));
		pos.y = (int) (ofRandom (scrambleStart, scrambleEnd - scrambleStart));
				
		positions.push_back(pos);
		
		
	}
	
	bReady = true;
}