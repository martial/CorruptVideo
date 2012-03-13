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

#ifndef SUPERINTPNL
#define SUPERINTPNL

#include "ofMain.h"
#include "glitchManager.h"
#include "videoManager.h"
#include "ofxSoundManager.h"

#include "ofxSuperInterface.h"
#include "superInterfaceEventArgs.h"
#include "superInterfaceFFT.h"
#include "superInterfaceHSlider.h"
#include "superInterfaceSimpleButton.h"

class corruptVideoApp;

class superInterfacePanel {

	public :
	
	void setup(corruptVideoApp * mom, videoManager * video, glitchManager * glitch, ofxSoundManager * soun);
	void update();
	void draw();
	
	void setRecordMode(superInterfaceEventArgs & args);
	void setWebcamMode(superInterfaceEventArgs & args);
	
	private :
	
	corruptVideoApp		*		mom;
	ofxSoundManager		*		sound;
	
	ofxSuperInterface			superInterface;
	superInterfaceHSlider		intensitySlider, compressionSlider;
	superInterfaceSimpleButton	webcamMode, fftMode, recordMode;
	superInterfaceFFT			fft;
	
	
};

#endif