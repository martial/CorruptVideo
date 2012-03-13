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

#ifndef GLTCHMNGR
#define GLTCHMNGR

#include "ofMain.h"
#include "abstractGlitch.h"
#include "originalCorruptGlitch.h"
#include "delayedCorruptGlitch.h"
#include "mergedCorruptGlitch.h"
#include "ofxImgSizeUtils.h"

class glitchManager  {
	
public:
	
	void setup();
	void draw(int x, int y, float width, float height);
	void drawFullScreen(float width, float height);
	
	void setupGlitches();
	
	void glitchThis(unsigned char * pixels, int width, int height, ofImageType colorMode);
	void setGlitchTypeByIndex(int index);
	
	void setCompressionQuality( float pct);
	void setCompressionQualityEvtHandler( float & pct){setCompressionQuality(pct);};
	void setIntensity(float pct);
	void setIntensityEvtHandler(float & pct){setIntensity(pct);};
	void setFileFormat(ofImageFormat format );
	void enableFormatMix(bool b);
	
	
	unsigned char * getPixels();
	
	bool			bHasLoaded;
	
	
	float			glitchIntensity, qualityPct;
private:
	
	ofImage			*		bufferImg;
	ofImage			*		glitchImg;
	
	vector<abstractGlitch*>	glitches;
	abstractGlitch	*		currentGlitch;
	
	string								outputImgURL;
	vector<ofImageQualityType>			qualityLevels;
	vector<ofImageFormat>				formatsAllowed;
	ofImageQualityType					currentQuality;
	
	bool						bFormatMixEnabled;
	
	string ext; // file format
	
};


#endif