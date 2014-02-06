#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Map.h"
#include "OpenStreetMapProvider.h"
#include "ofxCsv.h"
#include "ofxGrabCam.h"

using namespace wng;

struct Hotel {
    Location location;
    int rating;
    int rooms;
    int chainId;
    string url;
    string tripadvisor;
    Hotel(float lt, float lg, int rt, int rms, int chain, string pUrl, string taurl) {
        location = Location(lt, lg);
        rooms = rms;
        rating = rt;
        chainId = chain;
        url = pUrl;
        tripadvisor = taurl;
    }
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void loadLocations();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	Map map;
    ofxCsv csv;
    ofxCsv airports;
    ofxCsv flightPaths;
    vector<Hotel> locations;
    bool doneParsing;
    
    ofxGrabCam cam;
    ofMesh mesh;
    ofVboMesh vboMesh;
};

#endif
