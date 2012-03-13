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


#ifndef GIFWEBUPL
#define GIFWEBUPL

#include "ofMain.h"
#include "videoManager.h"

class gifWebUploader {

public:
	
	void setup(string folder);
	void sendFile(string  & filePath);
	
	void setFolder(string folder);
	void setMode(corruptVideoMode mode);
	void setKeyWord(string keyword);
	
	void exit();
	
	ofEvent<string>	gifMaxSizeEvent;
	ofEvent<int>	uploadDone;
	
	
	private :
	
	string folder;
	int mode;
	int maxSize;
	string keyword;
};

#endif
