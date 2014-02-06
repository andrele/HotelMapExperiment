#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Map.h"
#include "OpenStreetMapProvider.h"
#include "ofxCsv.h"
#include "ofxGrabCam.h"

using namespace wng;

struct Hotel {
    float latitude;
    float longitude;
    int rating;
    int rooms;
    int chainId;
    string url;
    string tripadvisor;
    Hotel(float lt, float lg, int rt, int rms, int chain, string pUrl, string taurl) {
        latitude = lt;
        longitude = lg;
        rooms = rms;
        rating = rt;
        chainId = chain;
        url = pUrl;
        tripadvisor = taurl;
    }
};

struct Airport {
    string name;
    string city;
    float latitude;
    float longitude;
    Airport(string name, string city, float latitude, float longitude) {
        this->name = name;
        this->city = city;
        this->latitude = latitude;
        this->longitude = longitude;
    }
};

struct FlightPath {
    int sourceAirportId;
    int destAirportId;
    FlightPath(int sourceAirportId, int destAirportId){
        this->sourceAirportId = sourceAirportId;
        this->destAirportId = destAirportId;
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
    ofxCsv airportsFile;
    ofxCsv flightPathsFile;
    vector<Hotel> locations;
    vector<Airport> airports;
    vector<FlightPath> flightPaths;
    std::map< int, vector<Hotel> > chains;
    bool doneParsing;
    
    ofxGrabCam cam;
    ofMesh mesh;
    ofMesh flightMesh;
};

#endif
