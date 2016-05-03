#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"           /* font library */
#include <ctime>                         /* time function */
#include <fstream>                       /* read and write files */
#include <stdlib.h>                      /* srand, rand */
#include <string>
#include <vector>




class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    

		
		ofVideoGrabber 		vidGrabber;
        bool                pio;
		int 				camWidth;
		int 				camHeight;
        int 				outWidth;
        int 				outHeight;
        int                 spaceX;
        int                 spaceY;
        int                 fontSize;
        int                 charsCount;
        int                 character;
        int                 r;           // random int
        int                 n;           // num in string
        int                 lapse;

    
        ofxTrueTypeFontUC   font;
        ofBuffer            buffer;
    
        string              chars;
        string              gatilho;
        string              allCamera;
        string              dontpad;
        string              array0;
        string              array1;
        string              array2;
        string              array3;

        string              str;
    
        size_t              found;
    
        time_t              start;
    
    
        ofHttpResponse      resp;
    
};
