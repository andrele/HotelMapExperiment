#include "testApp.h"
#include "OpenStreetMapProvider.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Loading CSV file
    csv.loadFile(ofToDataPath("hotelShort.txt"),"~");
    
    for (int i = 1; i<csv.numRows; i++) {
        
        locations.push_back(Location((double)csv.getFloat(i, 12),(double)csv.getFloat(i, 13)));
        cout << "Adding lat and long to locations vector: " << csv.getFloat(i, 12) << "," << csv.getFloat(i, 13) << endl;
    }
    
	ofSetVerticalSync(true);
	//ofSetFrameRate(100);
	map.setup(new OpenStreetMapProvider(), (double)ofGetWidth(), (double)ofGetHeight());
	map.setZoom(3);
    
    // Change color of circle

}

//--------------------------------------------------------------
void testApp::update(){
	map.update();
	//map.sc += 0.01 * sin(ofGetElapsedTimef());
	//map.tx += 0.01 * cos(ofGetElapsedTimef());
	//map.ty += 0.01 * sin(ofGetElapsedTimef());
}

//--------------------------------------------------------------
void testApp::draw(){    
    map.draw();
    
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofFill();
    // Draw points on screen
    for (std::vector<Location>::iterator it = locations.begin(); it != locations.end(); ++it) {
        ofCircle(map.locationPoint(*it).x, map.locationPoint(*it).y, 10);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	map.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	map.keyReleased(key);
	
	if (key == 'f' || key == 'F') {
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	// TODO: change mouse cursor if over map?
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	// TODO: check if we're over the map
	map.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	map.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	map.mouseReleased(x,y,button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	// TODO: map.setSize(w,h)?
	map.width = w;
	map.height = h;
}

