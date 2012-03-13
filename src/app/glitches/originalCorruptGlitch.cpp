/*
 *  originalCorruptGlitch.cpp
 *  corrupt-video
 *
 *  Created by Martial on 09/10/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "originalCorruptGlitch.h"

originalCorruptGlitch::originalCorruptGlitch() {
	abstractGlitch::abstractGlitch();
}

void originalCorruptGlitch::glitch(char * buffer, int filesize) {
	
	
	
	int scrambleStart = 417;
	int scrambleEnd = filesize;
	
	int nbOfReplacements =  floor(intensityPct * 10);
	
	for(int i = 0; i < nbOfReplacements; i++) {
		
		int PosA = (int) (ofRandom (scrambleStart, scrambleEnd - scrambleStart));
		int PosB = (int) (ofRandom (scrambleStart, scrambleEnd - scrambleStart));
		
		char tmp	 =  buffer[PosA];
		buffer[PosA] =	buffer[PosB];
		buffer[PosB] =	tmp;

	}
	
}