/*
 *  udpateBoxView.cpp
 *  corrupt-video
 *
 *  Created by Martial on 17/01/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#include "udpateBoxView.h"

udpateBoxView::udpateBoxView() {
	
}




void udpateBoxView::draw (string currentVersion, string newVersion) {
	
	
	textBoxView::draw();
	
	float yPos = 15 + fontRect.height  -15 +40 + 15;
	

	
	ofSetColor(255, 255, 255);
	font.drawString("Current Version : " + currentVersion  + "\nVersion online : " + newVersion, 15 + 20, yPos + 15);
	
}