//
//  textInput.h
//  textInput
//
//  Created by Elliot Woods on 12/09/2011.
//  Copyright 2011 Kimchi and Chips.
//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//

#include "ofMain.h"
#include "ofEvents.h"

class textInput {
public:
	textInput();
	void	init();
	void	draw() ;
	void	keyPressed(int key);
	void	clear();
	
	int	getWidth();
	int	getHeight();
	
	string	text;
	int		position;
	
	ofEvent<string> evtEnter;
	ofRectangle		bnds;
	
protected:
	void	keyPressedEvent(ofKeyEventArgs &a);
	int		cursorx, cursory;
	
	
	ofTrueTypeFont	font;
};
