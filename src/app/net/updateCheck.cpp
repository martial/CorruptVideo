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


#include "updateCheck.h"

void updateCheck::checkIfValid (string version) {
	this->currentVersion = version;
	state = "OK";
	ofRegisterURLNotification(this);  
	ofLoadURLAsync("http://www.uglitch.com/app/version.txt");
	updateBox.setup();
	
}

void updateCheck :: urlResponse ( ofHttpResponse &response )  
{   
	
	 cout << response.request.name << endl;  
	
    if(response.status==200 ){  
		
		if(	state == "WRONG_VERSION" ) {
			updateBox.setString(response.data.getText());
			return;
		}
		
		this->onlineVersion = response.data.getText() ;			
		if ( currentVersion != onlineVersion ) {
			state = "WRONG_VERSION";
			ofLoadURLAsync("http://www.uglitch.com/app/changelog.txt");
		}
		
    }else{  
		updateBox.setFileString("txt/offline.txt");
        state = "OFFLINE";
    }  
}  



void updateCheck::draw () {
	
	if(state != "OK") updateBox.draw(currentVersion, onlineVersion);

}

void updateCheck::spacePressed () {
	state = "OK";
}