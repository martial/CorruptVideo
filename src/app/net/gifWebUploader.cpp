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

#include "gifWebUploader.h"

void gifWebUploader::setup(string folder) {
	
	setFolder(folder);
	maxSize = 500000000; // should be 5Mo but not sure about it :-)
}



void gifWebUploader::sendFile(string  &filePath) {
	
	// ofxHttpForm does not work with some servers
	// need to resolve this to have a request back
	// maybe curl lib ?
	
	/*
	ofxHttpForm form;
	form.action = "http://the.imoca.ie/glitch/upload.php";
	//form.action = "http://www.murielserf.com/glitch/upload.php";
	//form.action = "http://www.164-prod.com/upload.php";
	form.method = OFX_HTTP_POST;
	
	form.addFormField("name", "file");
	form.addFile("file",filePath);
	httpUtils.addForm(form);	
	*/
	// done
	
	
	
	// we should check file size before uploading.
	// if file size too high, deny 
	
	ofFile gif;
	gif.open(filePath);
	int size = gif.getSize();
	
	if(size > maxSize ) {
		string message = "File Too big to upload " + ofToString(size) +" "+ ofToString(maxSize) +" allowed - skip";
		ofNotifyEvent(gifMaxSizeEvent, message, this);
		ofLog(OF_LOG_NOTICE, "File Too big to upload %d - %d allowed", size, maxSize);
		return;
	}
	
	string modeName;
	
	switch (mode) {
		case CORRUPT_VIDEOMODE_OFF:
			modeName = "off";
			break;
			
		case CORRUPT_VIDEOMODE_WEBCAM:
			modeName = "webcam";
			break;

			
		case CORRUPT_VIDEOMODE_DESKTOP:
			modeName = "desktop";
			break;
			
		case CORRUPT_VIDEOMODE_MOVIE:
			modeName = "video";
			break;
			
			
		case CORRUPT_VIDEOMODE_IMGSEARCH:
			modeName = "image";
			break;
			
		default:
			modeName = "desktop";
			break;
	}
	
	ofLog(OF_LOG_NOTICE, "http://www.uglitch.com/uglitch/upload/"+folder+"/"+modeName + "/"+keyword);
		
	string commandLine = "curl -F file=@"+ofToDataPath(filePath, false)+" http://www.uglitch.com/uglitch/upload/"+folder+"/"+modeName + "/"+keyword;
	//int i;
	system(commandLine.c_str());
	
	
	int dumm = 0;
	ofNotifyEvent(uploadDone, dumm, this);

	
	
}




void gifWebUploader::setFolder(string folder) {
	this->folder = folder;
}

void gifWebUploader::setKeyWord(string keyword) {
	this->keyword = keyword;
}

void gifWebUploader::setMode(corruptVideoMode mode) {
	this->mode = mode;
}


void gifWebUploader::exit() {
	
	//httpUtils.stop();
	
}