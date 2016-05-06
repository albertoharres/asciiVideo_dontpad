#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//ofAppGLFWWindow win;
	//win.setMultiDisplayFullscreen(true); //this makes the fullscreen window span across all your monitors
    //ofSetupOpenGL(&win, 800,500, OF_FULLSCREEN);

	ofBackground(0, 0);

	ScreenWidth = ofGetWindowWidth();
	ScreenHeight = ofGetWindowHeight();

	//cout << "Screen Width: " << ScreenWidth << endl;
	//cout << "Screen Height: " << ScreenHeight << endl; 


	camWidth = ofGetWidth();	// try to grab at this size.
	camHeight = ofGetHeight();

	outWidth = ofGetWidth();
	outHeight = ofGetHeight();

	vidGrabber.setDeviceID(0);
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(outWidth, outHeight);

	videoMirror = new unsigned char[camWidth*camHeight * 3];
	mirrorTexture.allocate(camWidth, camHeight, GL_RGB);

	fontSize = 15;

	font.load("Arial Unicode.ttf", fontSize, true, true);

	spaceX = fontSize - 2;
	spaceY = fontSize;

	// this set of characters comes from processing: 
	//http://processing.org/learning/library/asciivideo.html

	/* dontpad for Array2 - meio-tom*/
	resp = ofLoadURL("http://www.dontpad.com/duplo.txt");
	str = string(resp.data);
	gatilho = "subliminar";

	found = str.find(gatilho);
	if ((found > str.size()) || (str.size() <= 0)) {
		pio = false;
	}
	else {
		pio = true;
		str.erase(str.size() - gatilho.size(), str.size());
	}

	/* dontpad for Array3 - claro*/
	resp0 = ofLoadURL("http://www.dontpad.com/claro.txt");
	str0 = string(resp.data);
	gatilho0 = "SUBLIMINAR";

	found0 = str0.find(gatilho0);
	if ((found > str0.size()) || (str0.size() <= 0)) {
		pio0 = false;
	}
	else {
		pio0 = true;
		str0.erase(str0.size() - gatilho0.size(), str0.size());
	}


	array0 = string("...---```");

	array1 = string("+=;:<>i~-*!ljt");

	array2 = string("zaqxswcdevrbgnhymuopz");   // array that updates with dontpad

	array3 = string("@&#8MN3AQWKHUO09AUIVBCHZKAQ%!&81725");


	dontpad = string(str);
	dontpad0 = string(str0);

	charsCount = outWidth / (spaceX)* outHeight / spaceY; // chars Array
	chars.resize(charsCount);
	chars0.resize(charsCount);


	cout << charsCount;

	for (int i = 0; i < charsCount; i++) {
		r = rand() % array2.size();
		int r0 = rand() % array3.size();
		chars[i] = array2[r];
		chars0[i] = array3[r];
	}

	ofEnableAlphaBlending();

	start = time(0);

	//ofToggleFullscreen();
	//ofSetFrameRate(20);
	ofSetVerticalSync(true);

	segundo = 1;
    
    milli = 100;
    
    gettimeofday(&t0, 0);

}


//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();
	if (vidGrabber.isFrameNew()) {
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < camHeight; i++) {
			for (int j = 0; j < camWidth * 3; j += 3) {
				// pixel number
				int pix1 = (i*camWidth * 3) + j;
				int pix2 = (i*camWidth * 3) + (j + 1);
				int pix3 = (i*camWidth * 3) + (j + 2);
				// mirror pixel number
				int mir1 = (i*camWidth * 3) + 1 * (camWidth * 3 - j - 3);
				int mir2 = (i*camWidth * 3) + 1 * (camWidth * 3 - j - 2);
				int mir3 = (i*camWidth * 3) + 1 * (camWidth * 3 - j - 1);
				// swap pixels
				videoMirror[pix1] = pixels[mir1];
				videoMirror[pix2] = pixels[mir2];
				videoMirror[pix3] = pixels[mir3];
			}
		}
		mirrorTexture.loadData(videoMirror, camWidth, camHeight, GL_RGB);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	glViewport(0, 0, ofGetWidth(), ofGetHeight());

	// change background video alpha value based on the mouse position
	float videoAlphaValue = ofMap(mouseX, 0, ofGetWidth(), 0, 255);

	// set a white fill color with the alpha generated above
	ofSetColor(255, 255, 255, videoAlphaValue);

	// draw the raw video frame with the alpha value generated above
	mirrorTexture.draw(0, 0, ofGetWidth(), ofGetHeight());

	ofPixelsRef pixelsRef = vidGrabber.getPixels();

	ofSetHexColor(0xffffff);
	int x = 0;
	int y = 0;
	int x0 = 0;
	for (int j = 0; j < outHeight; j += spaceY) {
		for (int i = 0; i < outWidth; i += spaceX) {

			//    character = x + y * outWidth;
			// get the pixel and its lightness (lightness is the average of its RGB values)
			float lightness = pixelsRef.getColor(outWidth - i, j).getLightness();
			//   int character = powf( ofMap(lightness, 0, 100, 0, 1), 2.5) * asciiCharacters.size();

			if (lightness > 255 - 10) {                           //  mais claro - Letras Naiusculas

				r = rand() % array3.size();
				font.drawString(ofToString(chars0[x]), i, j);

			} else if (lightness >= 4 * (255) / 5)  {    //

				font.drawString(ofToString(chars[x]), i, j);
		//	} else if (lightness >= 2 * (255) / 3) { // penumbra

		//		r = rand() % array2.size();

		//		font.drawString(ofToString(array2[r]), i, j);

			} else if (lightness > 3 * (255) / 5) {

				r = rand() % array1.size();

				font.drawString(ofToString(array1[r]), i, j);

			} else if (lightness > 2 * (255) / 5) {

				r = rand() % array0.size();

				font.drawString(ofToString(array0[r]), i, j);

			}

			if (x >= chars.size() - 1) {
				x = 0;
			}
			x++;
			if (x0 >= chars0.size() - 1) {
				x0 = 0;
			}
			x0++;



			// calculate the index of the character from our asciiCharacters array
		    //  int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
			// draw the character at the correct location
		}
	}
	double seconds_since_start = difftime(time(0), start); // calculate difference between inital time and current time
    
	if (seconds_since_start == segundo) {

		segundo++;
	}
    
    elapsed = ofGetElapsedTimeMillis();
    if (elapsed > 1000){
        ofResetElapsedTimeCounter();
        milli = 0;

    }
    
    if (elapsed > milli){
        /* array3 */
        if (pio0 == false) {
            for (int i = chars0.size() - 1; i >= ((outWidth / spaceX) - 1); i--) {
                chars0[i] = chars0[i - array3.size()];
            }
            for (int i = 0; i <= ((outWidth / spaceX)); i++) {
                
                int r0 = rand() % array3.size();                            // aleatorio dentro de string array3
                chars0[i] = array3[r0];
            }
        }
        else {
            
            for (int i = chars0.size() - 1; i >= array3.size(); i--) {
                chars0[i] = chars0[i - array3.size()];
            }
            for (int i = 0; i <= array3.size(); i++) {
                
                chars0[i] = array3[n0];
                
                if (n0 >= array3.size() - 1) {
                    n0 = 0;
                }
                else {
                    n0++;
                }
            }
        }
        
        /* array2  (subliminar)*/
        if (pio == false) {                                      //
            
            for (int i = chars.size() - 1; i >= ((outWidth / spaceX) - 1); i--) {   // retira os caracteres
                chars[i] = chars[i - ((outWidth / spaceX))];
            }
            for (int i = 0; i <= chars0.size(); i++) {                 // adiciona novos
                
                r = rand() % array2.size();                            // aleatorio dentro de string array2
                chars[i] = array2[r];
            }
        }
        else {
            for (int i = chars.size() - 1; i >= array2.size(); i--) {
                chars[i] = chars[i - array2.size()];
            }
            for (int i = 0; i <= array2.size(); i++) {
                
                chars[i] = array2[n];
                if (n >= array2.size() - 1) {
                    n = 0;
                }
                else {
                    n++;
                }
            }
        }
        
        cout << elapsed << endl;
        milli+= 90;
    }
    

	/* fim array2 */

	if (seconds_since_start == 5) {  // every 10 seconds...
		start = time(0);  // restart counter
		lapse++; // add "minute"
		cout << "30 seconds lapse: " << lapse << '\n';

		/* ARRAY 2 check*/
		// load dontpad and check for code and amount of chararacts
		resp = ofLoadURL("http://www.dontpad.com/duplo.txt");
		str = string(resp.data);

		found = str.find(gatilho);
		if ((found > str.size()) || (str.size() == 0)) {
			pio = false;
			array2 = string("zaqxswcdevrbgnhymuopz");

		}

		else {
			pio = true;
			str.erase(str.size() - gatilho.size(), str.size());
			if (str.size() > 1) {
				array2 = string(str);
			}
		}
	}
	if (seconds_since_start == 10){   // every 10 seconds

		start = time(0);  // restart counter
		lapse++; // add "minute"
		cout << "30 seconds lapse: " << lapse << '\n';

		/* ARRAY 3 check*/
		// load dontpad and check for code and amount of chararacts
		resp0 = ofLoadURL("http://www.dontpad.com/claro.txt");
		str0 = string(resp0.data);

		found0 = str0.find(gatilho0);
		if ((found0 > str0.size()) || (str0.size() == 0)) {
			pio0 = false;
			array3 = string("@&#8MN3AQWKHUO09AUIVBCHZKAQ%!&81725");

		}
		else {
			pio0 = true;
			str0.erase(str0.size() - gatilho0.size(), str0.size());
			if (str0.size() > 1) {
				array3 = string(str0);
			}
		}
	}
	
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...

	if (key == 's' || key == 'S') {
		vidGrabber.videoSettings();
	}
	if (key == 'f' || key == 'F') {
			ofToggleFullscreen();
			camWidth = ofGetWidth();	// try to grab at this size.
			camHeight = ofGetHeight();
			//outWidth = ofGetWidth();
		//	outHeight = ofGetHeight();
		//	charsCount = outWidth / (spaceX)* outHeight / spaceY; // chars Array
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
