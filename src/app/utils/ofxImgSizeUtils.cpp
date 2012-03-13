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

#include "ofxImgSizeUtils.h"



ofPoint ofxImgSizeUtils::getSizeRatio ( int maxw, int maxh, float currw, float currh, bool keepInto ) {

	float w,h;
	
	//int ofW = ofGetWidth();
	//int ofH = ofGetHeight();
	
	float stageAspectRatio = (float)maxw/(float)maxh;
	float imageAspectRatio = (float)currw/(float)currh;
	
	
	if ( stageAspectRatio >= imageAspectRatio ) {
	
	w = (float)maxw;
	h = (float)maxw / imageAspectRatio;
		
	} else {
		
	w = (float)maxh * imageAspectRatio;
	h = (float)maxh;

		
	}
	
	if ( keepInto ) {
		
		if ( currw > maxw ) {
			
			w = (float)maxw;
			float scale = maxw / currw;
			h = (float)currh * scale;
			
		} 
		
		if ( currh > maxh ) {
			
			h = (float)maxh;
			float scale = maxh / currh;
			w = (float)currw * scale;
			
		} 
		
		if ( w > maxw ) {
			
			w = (float)maxw;
			float scale = maxw / currw;
			h = (float)currh * scale;
			
		} 
		
		if ( h > maxh ) {
			
			h = (float)maxh;
			float scale = maxh / currh;
			w = (float)currw * scale;
			
		} 
		
		
	}
	
	 
	
	
	return 	ofPoint (w,h);
	
}