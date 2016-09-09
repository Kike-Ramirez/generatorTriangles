#pragma once

#include "ofMain.h"
#define N 40
class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    string ToFilename();
    
    void readFile();
    void saveFile();
    int y0 = 0;
    int y1 = 0;
    ofVec3f centerA, centerB;
    
    vector<ofVec3f> steps[N];
    
    vector<ofVec3f> faces[N];
    int c = 0;
    
    int prev;
    bool bPressed;
    bool bPlay;
    bool playSide;
    bool bEdited;
    
    ofFile file;
    ofBuffer buffer;
    
    vector<int> colors;
    int color = 0;
    
    int folder = 0;
    
};
