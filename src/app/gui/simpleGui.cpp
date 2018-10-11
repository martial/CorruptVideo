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


#include "simpleGui.h"




void simpleGui::setup (videoManager * video, glitchManager * glitch) {
	
	this->video = video;
	this->glitch = glitch;
	
	font.load("fonts/Arial.ttf", 9, false, false, false);
	
	logo.load("images/logo.png");
	
	height = logo.getHeight();
	diffHeight = 0.0;
	xPadding = 1.0;
	
	currentSetID = 0;
	
	setButtons();
	
	enable();
}

void simpleGui::setButtons() {
	
	// set buttons 
	
	simpleButton * webcamBtn = new simpleButton();
	webcamBtn->setup("Webcam", height, &font);
	
	
	simpleButton * loadMovieBtn = new simpleButton();
	loadMovieBtn->setup("Load movie", height, &font);
	
	simpleButton * desktopMovie = new simpleButton();
	desktopMovie->setup("Desktop", height, &font);
	
	simpleButton * imgSearch = new simpleButton();
	imgSearch->setup("GIF Search", height, &font);

	
	
	//simpleButton * galleryBtn = new simpleButton();
	//galleryBtn->setup("Gallery", height, &font);
	
	simpleButton * infoBtn = new simpleButton();
	infoBtn->setup("Info", height, &font);
	infoBtn->bTemporary = false;
	
	
	simpleSlider * intensitySlider = new simpleSlider();
	intensitySlider->setup("Glitch %",  &glitch->glitchIntensity, 130, height, &font);
	intensitySlider->padding.set(14, height - 35);
	intensitySlider->bEnabled = true;
	ofAddListener(intensitySlider->eventUpdate, glitch, &glitchManager::setIntensityEvtHandler );
	
	simpleSlider * compressionSlider = new simpleSlider();
	compressionSlider->setup("Quality %",  &glitch->qualityPct, 130, height, &font);
	compressionSlider->padding.set(14, height - 35);
	compressionSlider->bEnabled = true;
	ofAddListener(compressionSlider->eventUpdate, glitch, &glitchManager::setCompressionQualityEvtHandler );
	
	
	permanentBtns.push_back(webcamBtn);
	permanentBtns.push_back(loadMovieBtn);
	permanentBtns.push_back(desktopMovie);
	//permanentBtns.push_back(imgSearch);
	//permanentBtns.push_back(galleryBtn);
	permanentBtns.push_back(infoBtn);
	permanentBtns.push_back(intensitySlider);
	permanentBtns.push_back(compressionSlider);
	
	// set pages
	
	vector<abstractComponent*> * webcamSet = new vector<abstractComponent*>();
	
	
	
	simpleButton * recordBtn = new simpleButton();
	recordBtn->setup("Record", height, &font);
	webcamSet->push_back(recordBtn);
	ofAddListener(recordBtn->eventClick, this, &simpleGui::onButtonClick );
	
    
	simpleButton * fftModeBtn = new simpleButton();
	fftModeBtn->setup("FFT Mode", height, &font);
	fftModeBtn->bTemporary = false;
	//webcamSet->push_back(fftModeBtn);
	ofAddListener(fftModeBtn->eventClick, this, &simpleGui::onButtonClick );
	
	
	simpleButton * faceTrack = new simpleButton();
	faceTrack->setup("Face Track", height, &font);
	faceTrack->bTemporary = false;
	webcamSet->push_back(faceTrack);
	ofAddListener(faceTrack->eventClick, this, &simpleGui::onButtonClick );
	
	
	
	videoSlider = new simpleSlider();
	videoSlider->setup("Video position",  &video->moviePos, 200, height, &font);
	videoSlider->padding.set(20, height - 30);
	videoSlider->bEnabled = false;
	//videoSlider->bHasFreePos = true;
	webcamSet->push_back(videoSlider);
	ofAddListener(videoSlider->eventUpdate, video, &videoManager::setMoviePositionEvtHandler );
	
	
	animtypeSelectBtn = new multLabelButton();
	animtypeSelectBtn->setup("Glitch type", height, &font);
	animtypeSelectBtn->bTemporary = true;
	
	animtypeSelectBtn->addStringValue("JPEG");
	animtypeSelectBtn->addStringValue("TIFF");
	//animtypeSelectBtn->addStringValue("PNG");
	//animtypeSelectBtn->addStringValue("GIF");
	//animtypeSelectBtn->addStringValue("RDM");
	
	webcamSet->push_back(animtypeSelectBtn);
	ofAddListener(animtypeSelectBtn->eventClick, this, &simpleGui::onButtonClick );
	
	sets.push_back(webcamSet);
	
	vector<abstractComponent*> * gallerySet = new vector<abstractComponent*>();
	sets.push_back(gallerySet);
	
	
	for ( int i=0; i<permanentBtns.size(); i++) {
		ofAddListener(permanentBtns[i]->eventClick, this, &simpleGui::onButtonClick );
	}
	
	
}

void simpleGui::onButtonClick(string & name ) {
	ofNotifyEvent(guiEvent, name, this );
}

void simpleGui::onSliderUpdate(float & pct) {
	ofNotifyEvent(sliderUpdate, pct, this );
}

void simpleGui::changeSet(int id) {
	
	currentSetID = id;
	
}

bool simpleGui::mouseMoved() {
	ofMouseEventArgs e;
	e.x = ofGetMouseX();
	e.y = ofGetMouseY();
	mouseMoved(e);
}

bool simpleGui::mouseMoved(ofMouseEventArgs &e ) {
	int i;
	for ( i=0; i<permanentBtns.size(); i++) {
		permanentBtns[i]->mouseMoved(e.x, e.y);
	}
	
	vector<abstractComponent*> * set = sets[currentSetID];
	for ( i=0; i<set->size(); i++) {
		set->at(i)->mouseMoved(e.x, e.y);	
	}
}

bool simpleGui::mousePressed(ofMouseEventArgs &e ) {
	int i;
	for ( i=0; i<permanentBtns.size(); i++) {
		permanentBtns[i]->mousePressed(e.x, e.y);
	}
	
	vector<abstractComponent*> * set = sets[currentSetID];
	for ( i=0; i<set->size(); i++) {
		set->at(i)->mousePressed(e.x, e.y);	
	}
	
}

bool simpleGui::mouseReleased(ofMouseEventArgs &e ) {
	int i;
	for ( i=0; i<permanentBtns.size(); i++) {
		permanentBtns[i]->mouseReleased();
	}
	
	vector<abstractComponent*> * set = sets[currentSetID];
	for ( i=0; i<set->size(); i++) {
		set->at(i)->mouseReleased();	
	}
	
}

bool simpleGui::mouseDragged(ofMouseEventArgs &e ) {
	int i;
	for ( i=0; i<permanentBtns.size(); i++) {
		permanentBtns[i]->mouseDragged(e.x, e.y, e.button);
	}
	
	vector<abstractComponent*> * set = sets[currentSetID];
	for ( i=0; i<set->size(); i++) {
		set->at(i)->mouseDragged(e.x, e.y, e.button);	
	}
	
}

void simpleGui::update () {
	
	yPos = ofGetHeight() - height + diffHeight;
	
	if(bEnabled) {
		
		if(diffHeight> 0.0 ) diffHeight -= 5;
		
	} else {
		if(diffHeight< height ) diffHeight += 5;
	}
	
	
	
	
	
}

void simpleGui::draw () {
	
	
	float xPos = ofGetWidth();
	if(xPos < 750 ) xPos = 750;
	
	
	ofEnableAlphaBlending();
	
	ofPushMatrix();
	ofTranslate(0.0, 0.0, 0.0);
	
	// draw rect
	ofSetColor(0, 0, 0, 75);
	ofRect(0, yPos -1, ofGetWidth(), height+1);
	
	// draw logo
	ofSetColor(255, 255, 255, 255);
	logo.draw(0, yPos);
	
	// draw permanent buttons
	
	int i;
	
	for ( i=0; i<permanentBtns.size(); i++) {
		permanentBtns[i]->draw(xPos - permanentBtns[i]->width, yPos );
		xPos -= permanentBtns[i]->width + xPadding;
	}
	
	
	// draw current set
	
	if(sets.size() > 0 ) {
		
		vector<abstractComponent*> * set = sets[currentSetID];
		
		xPos = logo.getWidth() + xPadding;
		for ( i=0; i<set->size(); i++) {
			
			if(set->at(i)->bEnabled == false) continue;
			
			if(set->at(i)->bHasFreePos) {
				
				set->at(i)->draw();
			} else {
				
				set->at(i)->draw(xPos, yPos);
				xPos += set->at(i)->width + xPadding;
			}
			
			
		}
		
	}
	
	
	
	ofPopMatrix();
	
	ofDisableAlphaBlending();
	
}

void simpleGui::enable() {
	
	ofRegisterMouseEvents(this);
	bEnabled = true;
}

void simpleGui::disable() {
	ofUnregisterMouseEvents(this);
	mouseMoved();
	bEnabled = false;
}


