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

