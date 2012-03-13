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

#include "superInterfacePanel.h"
#include "corruptVideoApp.h"

void superInterfacePanel::setup(corruptVideoApp * mom, videoManager * video, glitchManager * glitch, ofxSoundManager * sound){
	
	this->mom = mom;
	this->sound = sound;
	
	
	superInterface.setup("");
	
	intensitySlider.setup(&superInterface, &glitch->intensityPct, 20, 20, 10, 2, 0.0, 1.0, "Glitch Intensity");
	compressionSlider.setup(&superInterface, &glitch->compressionPct, 80, 60, 10, 2, 0.0, 1.0, "Compression Intensity");

	
	webcamMode.setup(&superInterface, "Webcam Mode", 20, 50, 12, 4);
	webcamMode.isEnabled(true);
	
	recordMode.setup(&superInterface, "Record Video", 70, 50, 12, 4);
	
	fftMode.setup(&superInterface, mom->bFftMode, "FFT Mode", 60, 50, 12, 4);
	
	
	fft.setup(&superInterface, 16, &sound->filterRange, 34,20, 42,16);
	
	ofAddListener(webcamMode.eventMouseDown, this, &superInterfacePanel::setWebcamMode);
	ofAddListener(recordMode.eventMouseDown, this, &superInterfacePanel::setRecordMode);
	
	superInterface.addComponent(&intensitySlider, 0);
	superInterface.addComponent(&compressionSlider, 0);
	superInterface.addComponent(&webcamMode, 0);
	superInterface.addComponent(&recordMode, 0);
	superInterface.addComponent(&fft, 0);
	superInterface.addComponent(&fftMode, 0);
	
	superInterface.showMenu(true);
	
	
}
void superInterfacePanel::update(){
	
	fft.updateValues(sound->getSpectrum());
	
	superInterface.update();
}

void superInterfacePanel::draw(){
	
	superInterface.draw();
}


void superInterfacePanel::setWebcamMode(superInterfaceEventArgs & args)  {
	
	bool b = *webcamMode.value;
	
	if(b) {
		mom->video.setUseWebcam();
	} else {
		mom->video.setUseVideo();
	}
	
}


void superInterfacePanel::setRecordMode(superInterfaceEventArgs & args)  {
	
	bool b = *recordMode.value;
	
	if(b) {
		mom->video.startRecord();
	} else {
		mom->video.stopRecord();
	}
	

}