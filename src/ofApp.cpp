#include "ofApp.h"
#include "ofAppGLFWWindow.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofAppGLFWWindow win;
    
    //win.setMultiDisplayFullscreen(true); //this makes the fullscreen window span across all your monitors
    
    ofSetupOpenGL(&win, 800,500, OF_FULLSCREEN);

	
    ofBackground(0,0,0);
    
	camWidth 		= 640;	// try to grab at this size.
	camHeight 		= 400;
    
    outWidth        = 1280;
    outHeight       = 800;
    
    vidGrabber.setDeviceID(0);
	vidGrabber.setVerbose(true);
	vidGrabber.setup(outWidth, outHeight);
    
    fontSize = 15;
    
	font.loadFont("Arial Unicode.ttf", fontSize, true, true);
    
    spaceX = fontSize - 2;
    spaceY = fontSize;
    
    // this set of characters comes from processing: 
    //http://processing.org/learning/library/asciivideo.html
    
    resp = ofLoadURL("http://www.dontpad.com/duplo.txt");
    str = string(resp.data);
    gatilho = "subliminar";
    
    
    found = str.find(gatilho);
    if((found > str.size()) || (str.size() <= 0)) {
        pio = false;
    } else {
        pio = true;
        str.erase(str.size()-gatilho.size(), str.size());
    }
    
    cout << str << endl;
    
    array0 = string(". . . - - - ` ` ` ");
    
    array1 = string("+=;:<>i~-*!ljt");  // array that updates with dontpad
    
    array2 = string("zaqxswcdevrbgnhymuopz");
    
    array3 =  string("@&#8MN3AQWKHUO09");

    
    dontpad = string(str);
    
    int charsCount = camWidth/(spaceX) * camHeight/spaceY; // chars Array
    chars.resize(charsCount);


    cout << charsCount;
    
    for(int i = 0; i < charsCount; i++){
        
        r = rand() % array2.size();
        chars[i] = array2[r];
    }
	
    ofEnableAlphaBlending();
    
    start = time(0);


}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // change background video alpha value based on the mouse position
    float videoAlphaValue = ofMap(mouseX, 0,ofGetWidth(),0,255);
    
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,videoAlphaValue);

    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(0,0);

	ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    ofSetHexColor(0xffffff);
    int x = 0;
    int y = 0;
    for (int j = 0; j < outHeight; j+= spaceY){

    for (int i = 0; i < outWidth; i+= spaceX){
        
        
            character = x + y * outWidth;
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();
         //   int character = powf( ofMap(lightness, 0, 100, 0, 1), 2.5) * asciiCharacters.size();
        
        if(lightness > 255-10){
            
              r = rand() % array3.size();
            font.drawString(ofToString(array3[r]), i, j);

        }
        
        
            if((lightness >= 4*(255)/5)&&(lightness <= 255-10)){
       // if(lightness < (255)/3){

                    font.drawString(ofToString(chars[x]), i, j);
            }
            
            
            if((lightness < 4*(255)/5)&&(lightness >= 2*(255)/3)){ // penumbra
                
                r = rand() % array2.size();

                font.drawString(ofToString(array2[r]), i, j);
                
            }
        
        if((lightness > 3*(255)/5)&&(lightness < 2*(255)/3)){ // penumbra
            
            r = rand() % array1.size();
            
            font.drawString(ofToString(array1[r]), i, j);
            
        }
        
        
        if((lightness > 2*(255)/5)&&(lightness <= 3*(255)/5)){ // penumbra
            
            r = rand() % array0.size();
            
            font.drawString(ofToString(array0[r]), i, j);
            
        }
        
        if(x >= chars.size()-1){
            x = 0;
        }
        x++;

        

            // calculate the index of the character from our asciiCharacters array
          //  int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
            // draw the character at the correct location
        }
    }
    double seconds_since_start = difftime( time(0), start); // calculate difference between inital time and current time
    
//    if(seconds_since_start == 0){
                if(pio == false){
                    
        for(int i = chars.size()-1; i >= ((outWidth/spaceX)-1); i--){
            chars[i] = chars[i - ((outWidth/spaceX))];
        }
        for(int i = 0; i <= ((outWidth/spaceX)); i++){
            
                r = rand() % array2.size();
                chars[i] = array2[r];
        }
            } else {
                for(int i = chars.size()-1; i >= array1.size(); i--){
                    chars[i] = chars[i - array1.size()];
                }
                for(int i = 0; i <= array1.size(); i++){
                
                chars[i] = array1[n];
                    if(n >= array1.size()-1){
                        n = 0;
                    } else {
                        n++;
                    }
            }
    
   //     }
    }
    
    if (seconds_since_start == 5){  // every 30 seconds...
        start = time(0);  // restart counter
        lapse++; // add "minute"
        cout << "30 seconds lapse: " << lapse << '\n';
        // load dontpad and check for code and amount of chararacts
        resp = ofLoadURL("http://www.dontpad.com/duplo.txt");
        str = string(resp.data);
        
        found = str.find(gatilho);
        if((found > str.size()) || (str.size() == 0)) {
            pio = false;
        } else {
            pio = true;
            str.erase(str.size()-gatilho.size(), str.size());
            array1 = string(str);
        }
    }

}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
