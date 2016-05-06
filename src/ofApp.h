#pragma once

#include "ofMain.h"
#include <ctime>                         /* time function */
#include <fstream>                       /* read and write files */
#include <stdlib.h>                      /* srand, rand */
#include <string>
#include <vector>
#include <sys/time.h>
#include <stdio.h>


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
        int                 n;           // num in string array 2
		int                 n0;          // num in string array 3
        int                 lapse;
		int                 ScreenWidth;
		int                 ScreenHeight; 
		int                 segundo;
        int                 milli;

        float               elapsed;
    
		bool                pio;
		bool                pio0;
    
		ofTexture           mirrorTexture;
        ofTrueTypeFont      font;
        ofBuffer            buffer;

		unsigned char * videoMirror; 

		string              chars0  ;  // letras maiusculas
        string              chars;     // letras minusculas
        string              gatilho;   // trigger array2 
		string              gatilho0;  // trigger array3
        string              allCamera;
        string              dontpad;
		string              dontpad0;
        string              array0;
        string              array1;
        string              array2;
        string              array3;

        string              str;     // dontpad string for array 2 
		string              str0;    // dontpad string for array 3

        size_t              found;   // found Gatilho array 2
		size_t              found0;  // found Gatilho array 3
    
        time_t              start;
        struct              timeval t0;
        struct              timeval t1;
    
        ofHttpResponse      resp;
		ofHttpResponse      resp0;
    
};
