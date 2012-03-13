/*
 *  googleJson.cpp
 *  CorruptVideo
 *
 *  Created by Martial on 12/03/2012.
 *  Copyright 2012 Martial. All rights reserved.
 *
 */

#include "googleJson.h"

string googleJson::request(string req) {
		
	bool parsingSuccessful = json.open("http://ajax.googleapis.com/ajax/services/search/images?v=1.0&as_filetype=gif&q=" + urlencode(req));
	
	
	cout  << urlencode(req) + "\n" << endl;
	
	if ( !parsingSuccessful )
    {
		cout  << "Failed to parse JSON\n" << endl;
		
		
	} else {
	
	int numImages = json["responseData"]["results"].size();	
	for(int i=0; i<numImages; i++) {
		string url = json["responseData"]["results"][i]["url"].asString();
		
	}
		
		
		int index = floor(ofRandom(numImages));
		string result = json["responseData"]["results"][index]["unescapedUrl"].asString();
		ofBuffer buf = ofLoadURL(result).data;
		ofBufferToFile("dl/dl_gif.gif", buf, true);
		
		
		
	}

	// load file and save locally ?
		
	return "dl/dl_gif.gif";
	
}

//based on javascript encodeURIComponent()
string googleJson::urlencode(const string &c)
{
    
    string escaped="";
    int max = c.length();
    for(int i=0; i<max; i++)
    {
        if ( (48 <= c[i] && c[i] <= 57) ||//0-9
			(65 <= c[i] && c[i] <= 90) ||//abc...xyz
			(97 <= c[i] && c[i] <= 122) || //ABC...XYZ
			(c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\'')
			)
        {
            escaped.append( &c[i], 1);
        }
        else
        {
            escaped.append("%");
            escaped.append( char2hex(c[i]) );//converts char 255 to string "ff"
        }
    }
    return escaped;
}

string googleJson::char2hex( char dec )
{
    char dig1 = (dec&0xF0)>>4;
    char dig2 = (dec&0x0F);
    if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48inascii
    if (10<= dig1 && dig1<=15) dig1+=97-10; //a,97inascii
    if ( 0<= dig2 && dig2<= 9) dig2+=48;
    if (10<= dig2 && dig2<=15) dig2+=97-10;
	
    string r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}