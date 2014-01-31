#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Map.h"
#include "OpenStreetMapProvider.h"
#include "ofxCsv.h"

using namespace wng;

struct geoPoint {
    float latitude;
    float longitude;
    geoPoint(float lt, float lg) {
        latitude = lt;
        longitude = lg;
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
    vector<Location> locations;
    bool doneParsing;
};

#endif
