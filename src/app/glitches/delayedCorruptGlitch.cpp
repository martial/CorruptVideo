/*
 *   
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 *  
 */


#include "delayedCorruptGlitch.h"

delayedCorruptGlitch::delayedCorruptGlitch() {
	//abstractGlitch::abstractGlitch();
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
