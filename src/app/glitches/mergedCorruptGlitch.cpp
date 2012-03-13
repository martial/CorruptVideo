/*
 *  originalCorruptGlitch.cpp
 *  corrupt-video
 *
 *  Created by Martial on 09/10/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "mergedCorruptGlitch.h"

mergedCorruptGlitch::mergedCorruptGlitch() {
	abstractGlitch::abstractGlitch();
}

void mergedCorruptGlitch::glitch(char * buffer, int filesize) {
	
	// divide into steps
	
	int steps = 1 + floor(intensityPct * 11);
	int start = 10;
	int end = filesize;
	
	
	int step = (int)(end / steps);
	int count = 0;
	
	
	vector<vector<char> > data;
	
	
	for(int i = start; i < end; i++) {
		
		if( i % (step) == 0 && i!= filesize -1 || i == start) {
			vector<char> vecData;
			data.push_back(vecData);
			count ++;
		}
		data[count-1].push_back(buffer[i]);		
	}
	
	int index = index = floor(ofRandom(steps));
	count = 0;
	for(int i = start; i < end; i++) {
							
		if( i % (step) == 0 && i!= filesize -1 || i == start) {
			count = 0;
			index = floor(ofRandom(steps));
			count = 0;
		}
		
		int _index =  ( i % 2 != 0) ? count+1 : count-1; 
		
		 _index = (int) ofClamp(count, 0.0, (float)(data[index].size()-1));
		
		buffer[i] = data[index][_index];				
		count ++;
	}
	
	
}

