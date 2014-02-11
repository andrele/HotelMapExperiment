#include "testApp.h"
#include "OpenStreetMapProvider.h"

void testApp::loadLocations(){
    

    for (int i = 1; i<csv.numRows; i++) {
        
        // Rudimentary check for valid data
        if (!csv.data[i].empty() && !csv.data[i][12].empty() && !csv.data[i][13].empty() ) {
            
            Hotel newHotel = Hotel(csv.getFloat(i, 12),csv.getFloat(i, 13), csv.getInt(i, 21),csv.getInt(i, 15), csv.getInt(i, 16), csv.getString(i, 10), csv.getString(i, 11));
            
            if (chains.find(newHotel.chainId) == chains.end()) {
                // Not found, add it!
                vector<Hotel> chainHotels;
                chainHotels.push_back(newHotel);
                chains.insert(std::pair< int,vector<Hotel> >(newHotel.chainId,chainHotels));
                cout << "Adding new chainId: " << newHotel.chainId << endl;
            } else {
                // Added hotel to existing hashmap
                chains[newHotel.chainId].push_back(newHotel);
            }
            
            cout << "Added hotel: [" << newHotel.chainId << "] " << newHotel.longitude << "," << newHotel.latitude << endl;
            

//            locations.push_back(Hotel(csv.getFloat(i, 12),csv.getFloat(i, 13), csv.getInt(i, 21),csv.getInt(i, 15), csv.getInt(i, 16), csv.getString(i, 10), csv.getString(i, 11)));
//            mesh.addVertex(ofPoint(csv.getFloat(i, 12),csv.getFloat(i, 13), csv.getInt(i, 21)));
//            ofColor blue = ofColor::blueSteel;
//            ofColor red = ofColor::red;
//            mesh.addColor(blue.lerp(red, (float)csv.getInt(i, 21)/10));
//            cout << "Adding: " << i << " [" << csv.getInt(i, 0) << "] (" << csv.data[i][12] << "," << csv.data[i][13] << "|" << csv.getFloat(i, 12) << "," << csv.getFloat(i, 13) << ")" << endl;
        }
    }
    
    // Connect all the chainIds together
    // Add all vertices
    int chainsIndex = 0;
    for (std::map< int,vector<Hotel> >::iterator it=chains.begin(); it != chains.end(); ++it) {
        ofMesh chainMesh = ofMesh();
        chainMesh.enableColors();
        for (int i = 0; i < it->second.size(); i++) {
            chainMesh.addVertex(ofVec3f(it->second[i].latitude, it->second[i].longitude, it->second[i].rating));
            ofColor pointColor(255,0,0);
            pointColor.setHue(chainsIndex);
            chainMesh.addColor(pointColor);
            cout << "[" << it->first << "] " << it->second[i].latitude << "," << it->second[i].longitude << endl;
        }
        
//      chainMesh.enableIndices();

        if (chainsIndex == 0)
            chainMesh.setMode(OF_PRIMITIVE_POINTS);
        else
            chainMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        
        meshes.push_back(chainMesh);
        chainsIndex++;
        
        
    }
    
    for (int i = 0; i<airportsFile.numRows; i++) {
        Airport newAirport = Airport(airportsFile.getString(i, 1), airportsFile.getString(i, 4), airportsFile.getFloat(i, 6), airportsFile.getFloat(i, 7));
        if (airports.find(airportsFile.getInt(i, 0)) == airports.end()) {
            // Not found. Add one
            vector<Airport> newAirports;
            newAirports.push_back(newAirport);
            airports.insert(std::pair< int,vector<Airport> > (airportsFile.getInt(i, 0),newAirports));
            cout << "Adding new Airport: " << airportsFile.getInt(i, 0) << endl;
        } else {
            airports[airportsFile.getInt(i,0)].push_back(newAirport);
        }
    }
    
    for (int i = 0; i<flightPathsFile.numRows; i++) {
        flightPaths.push_back(FlightPath(flightPathsFile.getInt(i, 3), flightPathsFile.getInt(i, 5)));
        cout << "Added route from: " << flightPathsFile.getInt(i, 3) << " to " << flightPathsFile.getInt(i, 5) << endl;
    }
    
    doneParsing = true;
    // clean everything up
    csv.clear();
    flightPathsFile.clear();
    airportsFile.clear();
}

//--------------------------------------------------------------
void testApp::setup(){

    
    // Loading CSV file
    csv.loadFile(ofToDataPath("hotelsbase.txt"),"~");
    airportsFile.loadFile(ofToDataPath("airports.dat"));
    flightPathsFile.loadFile(ofToDataPath("flight-paths.dat"));
    
    doneParsing = false;

    loadLocations();
    
	ofSetVerticalSync(true);
	//ofSetFrameRate(100);
	map.setup(new OpenStreetMapProvider(), (double)ofGetWidth(), (double)ofGetHeight());
	map.setZoom(3);
    
    ofEnableDepthTest();
	glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
	glPointSize(2); // make the points bigger
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
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
//    map.draw();
    
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofFill();
    // Draw points on screen
    if (doneParsing){
//        for (std::vector<Hotel>::iterator it = locations.begin(); it != locations.end(); ++it) {
//            Location *loc = &it->location;
//            ofPushStyle();
//            ofColor orange = ofColor::orange;
//            ofColor blue = ofColor::blue;
//            ofSetColor(blue.lerp(orange, (float)it->rating/10));
//            ofFill();
//            ofCircle(map.locationPoint(*loc).x, map.locationPoint(*loc).y, it->rating*0.25);
//            ofPopStyle();
//        }
        cam.begin();
        ofPushMatrix();
        ofRotateX(-90);
        ofRotateY(-90);
        ofScale(2, -2, 2); // flip the y axis and zoom in a bit
//        ofRotateY(90);
        for (int i = 0;i<meshes.size();i++){
            meshes[i].draw();
        }
        ofPopMatrix();
        cam.end();

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

