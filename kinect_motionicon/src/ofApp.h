#pragma once

#include "ofxOpenNI.h"
#include "ofMain.h"

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

        void userEvent(ofxOpenNIUserEvent & event);
    
public:
    ofxOpenNI kinect;
    
    //skeleton 각 joint 정보
    ofxOpenNIJoint head, leftHand, rightHand,leftShoulder, rightShoulder, leftElbow, rightElbow, leftHip, rightHip, leftKnee, rightKnee, neck,leftFoot,rightFoot;
    ofPoint headPos, neckPos,leftHandPos, rightHandPos, leftShoulderPos, rightShoulderPos, leftElbowPos, rightElbowPos, leftHipPos, rightHipPos, leftKneePos, rightKneePos, leftFootPos, rightFootPos;
    
    //제스처에 따라 달라지는 몸통이미지 구분 flag
    int bodyColor;
    
    //캐릭터 맵핑 이미지
    ofImage backgroundImg;
    ofImage original;
    ofImage hello;
    ofImage yay;
    ofImage headache;
    ofImage hello_leftFoot;
    ofImage hello_rightFoot;
    ofImage yay_leftFoot;
    ofImage yay_rightFoot;
    ofImage headache_leftFoot;
    ofImage headache_rightFoot;
    ofImage original_leftFoot;
    ofImage original_rightFoot;
    ofImage helloMsg;
    ofImage yayMsg;
    
    //사운드, 비디오 소스
    ofSoundPlayer bgm;
    ofSoundPlayer yaySound;
    ofVideoPlayer videoExplosion;
    bool isSoundPlaying;
    bool isVideoPlaying;
    
    void getAllJointDataFromUser(ofxOpenNIUser & user);
    void getAllPositionDataFromJoint();
    void mappingBodyAndFeet(ofImage body, ofImage leftFoot, ofImage rightFoot);
    void drawArmsAndLegs();
    
    //점 두개에서 quad mesh를 그려주는 함수 정의
    void drawMesh(ofMesh mesh, ofPoint startPos, ofPoint endPos);
    ofMesh leftArmMesh;
    ofMesh rightArmMesh;
    ofMesh leftShoulderMesh;
    ofMesh rightShoulderMesh;
    ofMesh leftTopLegMesh;
    ofMesh rightTopLegMesh;
    ofMesh leftBottomLegMesh;
    ofMesh rightBottomLegMesh;
    ofMesh torso;
    
    ofTrueTypeFont verdana;

};
