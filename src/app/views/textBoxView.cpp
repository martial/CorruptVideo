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


#include "textBoxView.h"

void textBoxView::setup () {
	str="";
	font.loadFont("fonts/Arial.ttf", 9, false, false, false);
	

}

void textBoxView::setString(string str){
	this->str = str;
	fontRect = font.getStringBoundingBox(str, 0.0, 0.0);
	width = fontRect.width + 40;
}
void textBoxView::setFileString(string path) {
	
	ofBuffer file;
	file = ofBufferFromFile(path, true);
	this->str = file.getText();
	fontRect = font.getStringBoundingBox(str, 0.0, 0.0);
	width = fontRect.width + 40;
	
}

void textBoxView::draw() {
	
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 200);
	ofRect(15, 15, width-15 + 20, fontRect.height -15 +40);
	ofDisableAlphaBlending();
	
	ofSetColor(255, 255, 255);
	font.drawString(str, 15 + 20, 15 + 20);
	
	
	

}