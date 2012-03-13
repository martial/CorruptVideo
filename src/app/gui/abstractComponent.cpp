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


#include "abstractComponent.h"

abstractComponent::abstractComponent( ) {
	
}

void abstractComponent::setup(string label){
	this->label = label;
	bHasFreePos = false;
	bEnabled = true;
}
void abstractComponent::update(){
}

void abstractComponent::draw(){
	
	
}

void abstractComponent::draw(float x, float y){
	
	pos.set((int)x, (int)y);
}

bool abstractComponent::hitTest (int x, int y) {
	
	return ((x > pos.x) && (x < pos.x + width) && (y > pos.y) && (y< pos.y + height));	
	
}

void abstractComponent::mouseMoved(int x, int y) {
	
	
	
}

void abstractComponent::mousePressed(int x, int y){
	
	if(hitTest(x,y)) {
		ofNotifyEvent(eventClick, label, this );
	}
	
	
}