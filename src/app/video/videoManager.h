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

#pragma once

#include "ofMain.h"

//#define OFXRPI_CAMERA

#ifdef OFXRPI_CAMERA
#include "TerminalListener.h"
#include "RPiVideoGrabber.h"
#endif

enum corruptVideoMode {
	CORRUPT_VIDEOMODE_OFF = 0,
	CORRUPT_VIDEOMODE_WEBCAM = 1,
	CORRUPT_VIDEOMODE_MOVIE = 2,
	CORRUPT_VIDEOMODE_DESKTOP = 3,
	CORRUPT_VIDEOMODE_IMGSEARCH = 4
};

#ifdef OFXRPI_CAMERA
class videoManager : public ofBaseApp, public KeyListener{
#else
class videoManager {
#endif
public:
	
	videoManager();
	void setup(int webcamW = 320, int webcamH = 240);
	void update();
	
	void draw(int x = 0, int y = 0);
	void draw(int x, int y, float width, float height);
	
	unsigned char * getPixels();
	
	void setVideoMode(corruptVideoMode mode);
	int	 getVideoMode();
	int  getColorMode();
	
	void stopVideos();
	
	/* for movie mode */
	bool  loadMovie();
	bool  loadMovie(string path);
	void  setMoviePosition(float pct);
	void  setMoviePositionEvtHandler(float & pct){setMoviePosition(pct);};
	float getMoviePosition();
	float moviePos; // only for GUI 
		
	/* for webcam mode*/
	void showWebcamSettings();
	
	void windowResized(ofResizeEventArgs & e );
	void exit();
	
	/* Get current size of the video */
	int  width, height;
	ofImageType  colorMode;
	
	/* Know if video has pixels */ 
	bool bHasPixels;
	
	
	
private:
	
	
	void				clear();
	
	ofVideoPlayer	*	videoPlayer;
    
#ifdef OFXRPI_CAMERA
    
    TerminalListener consoleListener;
    RPiVideoGrabber videoGrabber;
    OMXCameraSettings omxCameraSettings;
    void onCharacterReceived(KeyListenerEventData& e){};

#else
    ofVideoGrabber        videoGrabber;

#endif
	
	//unsigned char *		pixels;
    ofPixels            pixels;
	
	ofDirectory			dir;
	string				videoDirectory;
	
	int					videoMode;
	
};

