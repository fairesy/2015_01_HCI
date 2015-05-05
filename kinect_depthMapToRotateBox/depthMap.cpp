#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    light.setPosition(ofGetWindowWidth()/3, 0, 20);
    
    angle = 0; //각도는 0으로 초기화.
    
//    ofEnableNormalizedTexCoords();
//    
//    ofImage img; //이미지 변수 선언.
//    img.loadImage("testImg.jpg");  //텍스처 맵 이미지를 로드한다.
//    text.allocate(400,400,GL_RGB, true); // 사이즈, color plate가 RGB인,
//
//    
//    glEnable(GL_DEPTH_TEST);
//    text.loadData(img.getPixels(), 400, 400, GL_RGB); //텍스처 맵을 등록한다.
//    
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
    kinect.setup();
//    kinect.setLogLevel(OF_LOG_VERBOSE); //설정한 priority이상의 로그 메시지만 보여준다.
    kinect.addDepthGenerator();
//    kinect.addImageGenerator();
    kinect.start();
    kinect.setMirror(true);
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 25);
    
    leftPoint = ofPoint(20, ofGetWindowHeight()/2);
    rightPoint = ofPoint(ofGetWindowWidth()-20, ofGetWindowHeight()/2);
}

//--------------------------------------------------------------
void ofApp::exit(){
    kinect.stop();
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    
    if(leftDepth < 900){ //leftDepth point에 물체가 가까이 오면 왼쪽으로 rotate
        angle -= 0.8;
    }
    if(rightDepth < 900){ //rightDepth point에 오면 오른쪽으로 rotate
        angle += 0.8;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    light.enable();
    light.draw();
    
    ofPushMatrix();
    ofSetColor(255, 255, 255);
    kinect.drawDepth(0, 0, 1280, 960);
    
//    kinect에서 depthData를 받아와서 left/right 지점의 depth갑을 구한다.
    ofShortPixels depthMap = kinect.getDepthRawPixels();
    leftDepth = depthMap[leftPoint.x/2 + leftPoint.y/2 * 640];
    rightDepth = depthMap[rightPoint.x/2 + rightPoint.y/2 * 640];
    
//    left/rightDepth 값을 메시지로 출력한다. 
    ofSetColor(0, 255, 0);
    string msg = "leftDepth : " + ofToString(leftDepth) + " rightDepth : " + ofToString(rightDepth);
    verdana.drawString(msg, 20, ofGetWindowHeight()-20);
    
//    화면 왼쪽/오른쪽 depth값을 수집하는 지점에 원을 그린다. 
    ofSetColor(255, 0, 0);
    ofCircle(leftPoint.x, leftPoint.y, 15);
    ofCircle(rightPoint.x, rightPoint.y, 15);
    ofPopMatrix();
    
//    화면중앙에 cube를 그린다.
    ofPushMatrix();
//    text.bind();
    ofTranslate(ofGetWindowWidth()*.5, ofGetWindowHeight()*.5, 0); //화면 중앙으로.
    ofRotate(angle, 0.0, 1.0, 0.0); //ofRotate(float degrees, float vecX, float vecY, float vecZ).
    ofSetColor(200, 40, 40);
    ofBox(200);
//    text.unbind();
    ofPopMatrix();
    
    ofDisableLighting();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
