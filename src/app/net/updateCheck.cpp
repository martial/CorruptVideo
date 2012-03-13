/*
 *  updateCheck.cpp
 *  corrupt-video
 *
 *  Created by Martial on 17/01/2012.
 *  Copyright 2012 Martial. All rights reserved.
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