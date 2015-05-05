#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
public:
    
    ofLight light;
    
    ofTrueTypeFont verdana;
    ofxOpenNI kinect;
    
    ofPoint leftPoint;
    ofPoint rightPoint;
    
    int leftDepth;
    int rightDepth;
    
    ofTexture text; //텍스처 매핑 클래스
    
    float angle; //각도를 위한 변수 선언
};
