/*
 *  googleJson.h
 *  CorruptVideo
 *
 *  Created by Martial on 12/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#ifndef GGLEJSON
#define GGLEJSON

#include "ofMain.h"
#include "ofxJSONElement.h"

class googleJson {

public : 


	string request(string req);
	string urlencode(const string &c);
	
private:
	

	
	string  char2hex( char dec );
	ofxJSONElement json;

};
#endif