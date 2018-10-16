/*
 *  publicGui.h
 *  corrupt-video
 *
 *  Created by Martial on 23/11/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "abstractComponent.h"
#include "simpleButton.h"
#include "simpleSlider.h"
#include "multLabelButton.h"

#include "videoManager.h"
#include "glitchManager.h"

class simpleGui {
	
	
public:
	
	void setup(videoManager * video, glitchManager * glitch);
	void setButtons();
	void update();
	void draw();
	
	void changeSet(int id);
	
	// mouse 
    bool mouseMoved();

    bool mouseMoved(ofMouseEventArgs & args);
    bool mousePressed(ofMouseEventArgs & args);
    bool mouseDragged(ofMouseEventArgs & args);
    bool mouseReleased(ofMouseEventArgs & args);
    bool mouseScrolled(ofMouseEventArgs & ){return false;};
    bool mouseEntered(ofMouseEventArgs & ){return false;};
    bool mouseExited(ofMouseEventArgs & ){return false;};
   
	
	void enable();
	void disable();
		
	void onButtonClick(string & name );
	void onSliderUpdate(float & pct);
	ofEvent<string>   guiEvent;
	ofEvent<float>	  sliderUpdate;
	bool bEnabled;
	
	simpleSlider						* videoSlider;
	multLabelButton					    * animtypeSelectBtn;
	
private:
	
	videoManager * video;
	glitchManager * glitch;
	
	vector<abstractComponent*>					permanentBtns;
	vector< vector<abstractComponent*>* >		sets;
	
	
	
	int											currentSetID;
	
	float height, diffHeight;
	float xPadding;
	
	ofImage logo;
	
	ofTrueTypeFont	font;
	
	float yPos;
	
	
};

