#include "ofApp.h"
#include "math.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    bodyColor = 0;
    isVideoPlaying = false;
    isSoundPlaying = false;
    
    ofSetLogLevel(OF_LOG_VERBOSE); //지정한 우선순위 이상의 로그메시지만 보여준다.
    
    kinect.setup();
    kinect.addImageGenerator(); //이미지 데이터 보여주기
    
    kinect.addDepthGenerator(); //depth 데이터 보여주기
    kinect.setRegister(true);
    kinect.setMirror(true);
    
    kinect.addUserGenerator(); 
    kinect.setMaxNumUsers(2);
    kinect.start();
    
    // set properties for all user masks and point clouds
    //kinect.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    kinect.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    kinect.setUsePointCloudsAllUsers(true);
    kinect.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    kinect.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    videoExplosion.loadMovie("composition_sound.mov");
    videoExplosion.play();
    videoExplosion.setVolume(0);
    
    backgroundImg.loadImage("background-01.png");
    hello.loadImage("mapping_hello.png");
    original.loadImage("mapping_original.png");
    yay.loadImage("mapping_yay.png");
    headache.loadImage("mapping_headache.png");
    hello_leftFoot.loadImage("hello_foot_left.png");
    hello_rightFoot.loadImage("hello_foot_right.png");
    original_leftFoot.loadImage("original_foot_left.png");
    original_rightFoot.loadImage("original_foot_right.png");
    yay_leftFoot.loadImage("yay_foot_left.png");
    yay_rightFoot.loadImage("yay_foot_right.png");
    headache_leftFoot.loadImage("headache_foot_left.png");
    headache_rightFoot.loadImage("headache_foot_right.png");
    helloMsg.loadImage("hello.png");
    yayMsg.loadImage("yay.png");
    yaySound.loadSound("yay_sound.mp3");
    yaySound.play();
    yaySound.setVolume(0);
    bgm.loadSound("snowman.mp3");
    bgm.play();
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    videoExplosion.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255, 255, 255);
    string msg = "";
    
    ofPushMatrix();
    kinect.drawDebug();
    // draw debug (ie., image, depth, skeleton)
    kinect.drawImage(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofPopMatrix();
    
    ofPushMatrix();
    backgroundImg.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = kinect.getNumTrackedUsers();
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = kinect.getTrackedUser(i);

        //user의 각 joint 정보를 가지고 온다.
        getAllJointDataFromUser(user);
        
        //각 joint에서 position정보를 추출한다.
        getAllPositionDataFromJoint();
 
        //캐릭터 그리기 : 이미지 맵핑
        ofPushMatrix();
        
        ofTranslate(ofGetWindowWidth()/2-300, ofGetWindowHeight()/2-100, 0);
        //팔다리 그리기
        if(bodyColor == 1) ofSetColor(246, 82, 61);
        else if (bodyColor == 2) ofSetColor(29, 115, 253);
        else if (bodyColor == 3) ofSetColor(254, 255, 18);
        else ofSetColor(135, 64, 167);
        drawArmsAndLegs();
        
        //몸통과 발
        if (bodyColor == 1) mappingBodyAndFeet(headache, headache_leftFoot, headache_rightFoot);
        else if(bodyColor == 2) mappingBodyAndFeet(yay, yay_leftFoot, yay_rightFoot);
        else if(bodyColor == 3) mappingBodyAndFeet(hello, hello_leftFoot, hello_rightFoot);
        else mappingBodyAndFeet(original, original_leftFoot, original_rightFoot);
        
        ofPopMatrix();
        
        //제스처1 : "머리가 터질 것 같아!!!!"
        int headLeftY = headPos.y - leftHandPos.y;
        int headRightY = headPos.y - rightHandPos.y;
        int headLeftX = headPos.x - leftHandPos.x;
        int headRightX = rightHandPos.x - headPos.x;
        if((headLeftY<30)&&(headLeftY>-30)&&(headRightY<30)&&(headRightY>-30)&&(headLeftX<60)&&(headRightX<60)){
            videoExplosion.setVolume(100);
            videoExplosion.draw(headPos.x+235, headPos.y-60, 240, 240);
//            isVideoPlaying = videoExplosion.isPlaying();
//            if(!isVideoPlaying){
//                msg += "checking...";
//                videoExplosion.play();
//                videoExplosion.setVolume(100);
//                videoExplosion.draw(headPos.x+175, headPos.y-100);
//            }
//            else{
//                videoExplosion.setVolume(0);
//            }
            bodyColor = 1;
            msg += "HEADACHE!!!!!!!!!!!!!!!!!!!!!!";
        }
        //제스처2 : yay! 왼쪽팔/왼쪽다리
        else if (leftShoulderPos.y>leftHandPos.y && leftFootPos.y<rightKneePos.y) {
            isSoundPlaying = yaySound.getIsPlaying();
            if(!isSoundPlaying){
                yaySound.play();
                yaySound.setVolume(100);
            }
            yayMsg.draw(headPos.x + 420, headPos.y -50);
            bodyColor = 2;
            msg = "YAY!!!!!!!!!!!";
            videoExplosion.setVolume(0);
        }
        //제스처3 : (오른손으로) 안녕
        else if ((rightShoulderPos.y>rightHandPos.y)&&(leftShoulderPos.y<leftHandPos.y)) {
            helloMsg.draw(headPos.x - 10, headPos.y - 10);
            bodyColor = 3;
            msg = "HELLO!";
        }
        //오디너리피플
        else{
            bodyColor = 0;
            videoExplosion.setVolume(0);
        }
    }

    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
    verdana.drawString(msg, 20, ofGetWindowHeight() - 20);
}

void ofApp::mappingBodyAndFeet(ofImage body, ofImage leftFoot, ofImage rightFoot){
    ofSetColor(255, 255, 255);
    leftFoot.draw(leftFootPos.x-65, leftFootPos.y-15, 80, 50);
    rightFoot.draw(rightFootPos.x-15, rightFootPos.y-15, 80, 50);
    body.draw(headPos.x-100,headPos.y-100, 200, 300);
}

void ofApp::drawArmsAndLegs(){
    ofSetLineWidth(2400);
    //팔
    ofLine(leftShoulderPos.x-30, leftShoulderPos.y, leftElbowPos.x-40, leftElbowPos.y);
    ofLine(leftElbowPos.x-40, leftElbowPos.y, leftHandPos.x-40, leftHandPos.y);
    ofLine(rightShoulderPos.x+30, rightShoulderPos.y, rightElbowPos.x+40, rightElbowPos.y);
    ofLine(rightElbowPos.x+40, rightElbowPos.y, rightHandPos.x+40, rightHandPos.y);
    ofCircle(leftHandPos.x-40, leftHandPos.y, 25);
    ofCircle(rightHandPos.x+40, rightHandPos.y, 25);
    //다리
    ofLine(leftHipPos.x, leftHipPos.y, leftKneePos.x, leftKneePos.y);
    ofLine(leftKneePos.x, leftKneePos.y, leftFootPos.x, leftFootPos.y);
    ofLine(rightHipPos.x, rightHipPos.y, rightKneePos.x, rightKneePos.y);
    ofLine(rightKneePos.x, rightKneePos.y, rightFootPos.x, rightFootPos.y);
}

void ofApp::getAllPositionDataFromJoint(){
    headPos = head.getProjectivePosition();
    neckPos = neck.getProjectivePosition();
    leftHandPos = leftHand.getProjectivePosition();
    rightHandPos = rightHand.getProjectivePosition();
    leftShoulderPos = leftShoulder.getProjectivePosition();
    rightShoulderPos = rightShoulder.getProjectivePosition();
    leftElbowPos = leftElbow.getProjectivePosition();
    rightElbowPos = rightElbow.getProjectivePosition();
    leftHipPos = leftHip.getProjectivePosition();
    rightHipPos = rightHip.getProjectivePosition();
    leftKneePos = leftKnee.getProjectivePosition();
    rightKneePos = rightKnee.getProjectivePosition();
    leftFootPos = leftFoot.getProjectivePosition();
    rightFootPos = rightFoot.getProjectivePosition();
}

void ofApp::getAllJointDataFromUser(ofxOpenNIUser & user){
    head = user.getJoint(JOINT_HEAD);
    leftHand = user.getJoint(JOINT_LEFT_HAND);
    rightHand = user.getJoint(JOINT_RIGHT_HAND);
    leftShoulder = user.getJoint(JOINT_LEFT_SHOULDER);
    rightShoulder = user.getJoint(JOINT_RIGHT_SHOULDER);
    leftElbow = user.getJoint(JOINT_LEFT_ELBOW);
    rightElbow = user.getJoint(JOINT_RIGHT_ELBOW);
    leftHip = user.getJoint(JOINT_LEFT_HIP);
    rightHip = user.getJoint(JOINT_RIGHT_HIP);
    leftKnee = user.getJoint(JOINT_LEFT_KNEE);
    rightKnee = user.getJoint(JOINT_RIGHT_KNEE);
    neck = user.getJoint(JOINT_NECK);
    leftFoot = user.getJoint(JOINT_LEFT_FOOT);
    rightFoot = user.getJoint(JOINT_RIGHT_FOOT);
}


void ofApp::drawMesh(ofMesh mesh, ofPoint startPos, ofPoint endPos){
    mesh.addColor(ofFloatColor(0,0,255));
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    //y = _a*x + b
    float a = (endPos.y-startPos.y)/(endPos.x-startPos.x);
    float _a = -(1/a);
    float bs = startPos.y - _a*startPos.x;
    float be = endPos.y - _a*endPos.x;
    
    ofPoint one, two, three, four;
    
    one.x = startPos.x + sqrt((100 * pow(a,2))/(pow(a,2) + 1));
    one.y = _a*one.x + bs;
    
    two.x = startPos.x - sqrt((100 * pow(a,2))/(pow(a,2) + 1));
    two.y = _a*two.x + bs;
    
    three.x = endPos.x + sqrt((100 * pow(a,2))/(pow(a,2) + 1));
    three.y = _a*three.x + be;
    
    four.x = endPos.x - sqrt((100 * pow(a,2))/(pow(a,2) + 1));
    four.y = _a*four.x + be;
    
    mesh.addVertex(one);
    mesh.addVertex(two);
    mesh.addVertex(three);
    mesh.addVertex(four);
    mesh.addVertex(one);
    mesh.draw();
}

//--------------------------------------------------------------
void ofApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void ofApp::exit(){
    kinect.stop();
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
