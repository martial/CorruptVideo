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


#include "multLabelButton.h"

multLabelButton::multLabelButton () {
	//simpleButton::simpleButton();
}

void multLabelButton::setup(string name, float height, ofTrueTypeFont * font) {
	simpleButton::setup(name, height, font);
	
	index = 0;
	selected = "";
}



void multLabelButton::addStringValue(string str){
	values.push_back(str);
	
	// if first value inserted - set by default
	if(values.size() == 1 ) 
	selected = str;
	
}

void multLabelButton::draw(){
	simpleButton::draw();
}

void multLabelButton::draw(float x, float y){
	
	abstractComponent::draw(x,y);
	
	string str = ( values.size() > 0 ) ? selected : "";
	
	sndLabelFontRect = font->getStringBoundingBox(str, 0.0, 0.0);


	ofPushMatrix();
	ofTranslate(x, y, 0.0);
	
	
	ofSetColor((bRollOver || bActive) ? rollOverColor : normalColor);
	ofRect(0.0, 0.0, width, height);
	
	
	ofSetColor(0, 0, 0);
	font->drawString(label, width*.5 - fontRect.width*.5, (int)(height * .5 - fontRect.height * .25 ));
	font->drawString(str, (int)(width*.5 - sndLabelFontRect.width*.5), (int)(height * .5 + fontRect.height * 1.25));
	ofPopMatrix();
	ofSetColor(255, 255, 255);
	
}

void multLabelButton::mousePressed(int x, int y) {

	
	
	if ( hitTest(x,y) ) { // should be written differently but no time 
		
		index++;
		if (index > values.size() -1) {
			index = 0;
		}
		selected = values[index];
		
		
	}
	simpleButton::mousePressed(x,y);
}
