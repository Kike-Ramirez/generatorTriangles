#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableAntiAliasing();
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0, 255, 255);
    bPressed = false;
    bPlay = false;
    bEdited = false;
    color = 0;
    
    centerB.set(ofRandom(300), ofRandom(200, 400));
    centerA.set(ofRandom(300,600), ofRandom(200,400));

    colors.push_back(0x000);
    colors.push_back(0xffffff);
    colors.push_back(0xaaaaaa);
    colors.push_back(0xff1222);
    colors.push_back(0x0048d4);
    colors.push_back(0xfcfc00);
    colors.push_back(0xff1eaa);
    colors.push_back(0xff41ff);
    colors.push_back(0x00d8fd);
    colors.push_back(0xff4c1f);
    readFile();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 255, 255);
        
    if(bPlay){
        string filename = ToFilename() + "/" + ofToString(c, 2, '0') + ".png";

        for(int i = 0; i < steps[c].size(); i++){
            ofVec3f p = steps[c][i];

            float angleInit;
            float angleEnd;

            ofVec3f center;
            ofVec3f a;
            ofVec3f b;

            if (folder == 0) {
                angleInit = ofMap(p.x, 0, 600, 2*PI, 0);
                angleEnd = angleInit + ofMap(p.y, 0, 600, 2*PI, 0);
                center.set(centerA.x, centerA.y);
                a.set(center.x + 600 * cos(angleInit), center.y + 600*sin(angleInit));
                b.set(center.x + 600 * cos(angleEnd), center.y + 600*sin(angleEnd));
            }

            else if (folder == 1) {
                angleInit = ofMap(p.x, 0, 600, 0, 2*PI);
                angleEnd = angleInit + ofMap(p.y, 0, 600, 0, 2*PI);
                center.set(centerB.x, centerB.y);
                a.set(center.x - 600 * cos(angleInit), center.y - 600*sin(angleInit));
                b.set(center.x - 600 * cos(angleEnd), center.y - 600*sin(angleEnd));
            }

            ofSetHexColor(colors[p.z]);
            //ofDrawRectangle(0, p.x, 600, p.y);
            ofDrawTriangle(center.x, center.y, a.x, a.y, b.x, b.y);

        }

        ofSaveScreen(filename);
        c += 1;

        if(c == N && folder == 1){
            bPlay = false;
            c = 0;
            folder = 0;
            cout << "DONE!" << endl;
        }
        else{
            if(c == N){
                c = 0;
                folder += 1;
                readFile();
            }
        }
        
        cout << filename << endl;

    }
    else{

        for(int i = 0; i < steps[c].size(); i++){
            ofVec3f p = steps[c][i];

            ofSetHexColor(colors[p.z]);
            ofDrawRectangle(0, p.x, 600, p.y);

        }

        if(bPressed) {

            ofSetHexColor(colors[color]);
            ofDrawRectangle(0, prev, 600, mouseY - prev);
        }

        ofSetColor(255, 0, 0);
        ofDrawBitmapString(ToFilename() + " " + ofToString(c), 10, 20);
        ofSetHexColor(colors[color]);
        ofDrawRectangle(580, 0, 20, 20);
    }
}


string ofApp::ToFilename(){
    switch (folder) {
        case 0:
            return "mask_A";
            break;
        case 1:
            return "mask_B";
            break;
        case 2:
            return "face_A";
            break;
        case 3:
            return "face_B";
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key >= '0' && key <= '9'){
        color = key - '0';
    }
    switch (key) {
        case 'p':
            bPlay = !bPlay;
            if(bPlay){
                c = 0;
                folder = 0;
                readFile();
            }
            else{
                
                ofSetFrameRate(30);
            }
            break;
            
        case ' ':
            c ++;
            saveFile();
            if (c > N) c = N;
            break;
            
        case '-':
            c --;
            if(c < 0) c = 0;
            break;
        case 'x':
            for(int i = 0; i < steps[c].size(); i++){
                ofVec3f p = steps[c][i];
                if(abs(mouseY -  p.x) < 5){
                    steps[c].erase(steps[c].begin() + i);
                    break;
                }
            }
            break;
            
        case 'X':
            steps[c].clear();
            break;
            
        case 'c':
            steps[c] = steps[c - 1];
            break;
            
        case 'r':
            readFile();
            break;
            
        case '+':
            saveFile();
            folder += 1;
            folder = folder % 4;
            readFile();
            break;
            
        default:
            break;
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    prev = y;
    bPressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bPressed = false;
    
    steps[c].push_back(ofVec3f(prev,  mouseY - prev, color));
    bEdited = true;
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

void ofApp::saveFile(){
    
    if(!bEdited) return;
    file.open(ToFilename() + ".txt", ofFile::WriteOnly);
    for(int j = 0; j < N; j ++){
        for(int i = 0; i < steps[j].size(); i++){
            ofVec3f p = steps[j][i];
            file << j << ";" << p.x << ";" << p.y << ";" << p.z << endl;
        }
    }
    file.close();
    bEdited = false;
    
}

void ofApp::readFile(){
    
    buffer = ofBufferFromFile(ToFilename() + ".txt");
    
    for(int j = 0; j < N; j ++)
        steps[j].clear();
    
    for (auto line : buffer.getLines()){
        if(ofSplitString(line, ";").size() != 4)
            break;
        int j = ofToInt(ofSplitString(line, ";")[0]);
        ofPoint p;
        p.x =  ofToInt(ofSplitString(line, ";")[1]);
        p.y =  ofToInt(ofSplitString(line, ";")[2]);
        p.z =  ofToInt(ofSplitString(line, ";")[3]);
        if(j < N)
            steps[j].push_back(p);
    }
}
