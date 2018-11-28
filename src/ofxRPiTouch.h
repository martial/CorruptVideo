#include "ofMain.h"
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>

// SYN
#define EVENT_TYPE_0	EV_SYN

// KEY
#define EVENT_TYPE_1	EV_KEY
#define EVENT_CODE_330	BTN_TOUCH
// Min	0
// Max	1

// TOUCH
#define EVENT_TYPE      EV_ABS
#define EVENT_CODE_0    ABS_X
// Min	0
// Max	800
#define EVENT_CODE_1    ABS_Y
// Min	0
// Max	480
#define EVENT_CODE_47 	ABS_MT_SLOT
// Min	0
// Max	9
#define EVENT_CODE_53 	ABS_MT_POSITION_X
// Min	0
// Max	800
#define EVENT_CODE_54 	ABS_MT_POSITION_Y
// Min	0
// Max	480
#define EVENT_CODE_57 	ABS_MT_TRACKING_ID
// Min	0
// Max	65535

//#define PORTRAIT_MODE
//#define LANDSCAPE_MODE

class ofxRPiTouch : public ofThread {
	public:

    struct input_event ev;
    int fd, size;
    char name[256];
    char *device;

    int x,y;
    int button;
    int mtSlot;
    int absMTPosX,absMTPosY;
    int absMTTrackingID;

    //int screenW = 480;
    //int screenH = 800;

//-----------------------------------------------------------------------
	int init(char * d) {
		size = sizeof (struct input_event);
		name[0]='U';
		name[1]='n';
		name[2]='k';
		name[3]='n';
		name[4]='o';
		name[5]='w';
		name[6]='n';
		device = d;

        if ((fd = open(device, O_RDONLY)) < 0) {
            //return 1;
		}
        
        string name = getName();
        ofLogNotice("trying to connect to ") << name;
        if(getName() != "FT5406 memory based driver") {
            
            close(fd);
            return 0;
            
        }
        
        ofLogNotice("connected to ") << name;

                
		startThread();
		return 1;
	}
//-----------------------------------------------------------------------
	string getName(){
		ioctl (fd, EVIOCGNAME (sizeof (name)), name);
		string str(name);
		return str;
	}
//-----------------------------------------------------------------------
	void exit(){
		stopThread();
	}
//-----------------------------------------------------------------------
	void threadedFunction(){
		while(isThreadRunning()) {
	        	const size_t ev_size = sizeof(struct input_event);
		        ssize_t size;
		        size = read(fd, &ev, ev_size);
		        if (size < ev_size) {
	        	    ofLog()<<"Error size!\n";
		        }

			//KEY
                        if (ev.type == EVENT_TYPE_1 && ev.code == EVENT_CODE_330){
                                if(ev.code == EVENT_CODE_330)
                                        button = ev.value;
                        	        btn = button;
                        }

		        //TOUCH
		        if (ev.type == EVENT_TYPE && ( ev.code == EVENT_CODE_0 || ev.code == EVENT_CODE_1 || ev.code == EVENT_CODE_47 || ev.code == EVENT_CODE_53 || ev.code == EVENT_CODE_54 || ev.code == EVENT_CODE_57 )) {
			    	if(ev.code == EVENT_CODE_1)
					x = ofMap(ev.value, 0,480,480,0);
			    	if(ev.code == EVENT_CODE_0)
					y = ofMap(ev.value, 0,800,0,800);
					pos.set(x,y);

				if (ev.code == EVENT_CODE_47)
					mtSlot = ev.value;
					mtSlt = mtSlot;

				if (ev.code == EVENT_CODE_53)
					absMTPosX = ev.value;
				if (ev.code == EVENT_CODE_54)
					absMTPosY = ev.value;
					absPos.set(absMTPosX,absMTPosY);

				if (ev.code == EVENT_CODE_57)
					absMTTrackingID = ev.value;
					absTrackingID = absMTTrackingID;
			}
		}
	}
			//----------------------------
				// Position
				ofVec2f pos;
				ofVec2f getCoordTouch(){
					return pos;
				}
			//----------------------------
				//Clicked
				int btn;
				int getButton(){
					return btn;
				}
			//----------------------------
				//Finger ID
				int mtSlt;
				int getMTSlot(){
					return mtSlt;
				}
			//----------------------------
				//Absolute Position
				ofVec2f absPos;
				ofVec2f getAbsPos(){
					return absPos;
				}

			//----------------------------
				//Tracking ID
				int absTrackingID;
				int getAbsTrackingID(){
					return absTrackingID;
				}
};
