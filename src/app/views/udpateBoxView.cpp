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


#include "udpateBoxView.h"

udpateBoxView::udpateBoxView() {
	
}




void udpateBoxView::draw (string currentVersion, string newVersion) {
	
	
	textBoxView::draw();
	
	float yPos = 15 + fontRect.height  -15 +40 + 15;
	

	
	ofSetColor(255, 255, 255);
	font.drawString("Current Version : " + currentVersion  + "\nVersion online : " + newVersion, 15 + 20, yPos + 15);
	
}