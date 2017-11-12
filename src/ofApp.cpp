#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if (nWorlds == 1) { worldY[0] += 190; }
    for (int i=0;i<nControls; i++) {
        controlX[i] = 50 + controlX[i] * 75;
        controlImage[i].load(controlImageFilename[i]);
    }
    
    ofSetFrameRate(60);
    
    for (int i=0; i<nWorlds; i++) {
      background[i].load("background.png");
      player[i].load(playerImage[i]);
        
      // the world bounds
      bounds[i].set(0, 0, worldW, worldH);
     
      box2d[i].init();
      box2d[i].setFPS(60);
      box2d[i].setGravity(gravityX, gravityY);
      box2d[i].createBounds(bounds[0]);
      box2d[i].registerGrabbing();
    }
    
    // add some boxes to world A
    for(int i=0; i<10; i++) {
        shared_ptr<ofxBox2dRect> c = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
        c.get()->setPhysics(1, 0.5, 1);
        c.get()->setup(box2d[0].getWorld(), ofRandom(-50, 50), ofRandom(-50, 50), ofRandom(10,30), ofRandom(10,30));
        circlesA.push_back(c);
    }

    // add some cirlces to world B
    for(int i=0; i<10; i++) {
        shared_ptr<ofxBox2dCircle> c = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1, 0.5, 1);
        c.get()->setup(box2d[1].getWorld(), 250+ofRandom(-50, 50), 10, ofRandom(10,30));
        circlesB.push_back(c);
    }
    vagRounded.load("vag.ttf", 32);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (controlState[GRAVITY_UP_CONTROL] == 2 ) {
        //Wakeup?
        if (controlState[MORE_GRAVITY_CONTROL] == 2) {
            if (gravityY < gravityYMax) gravityY++;
        }
        if (gravityY > gravityYMin) gravityY--;
    } else {
        if (controlState[MORE_GRAVITY_CONTROL] == 2) {
            if (gravityY < gravityYMax) gravityY++;
        } else {
            gravityY = origGravityY;
        }
    }
   if (controlState[WIND_FROM_EAST_CONTROL] == 2) {
        //Wakeup?
        if (controlState[WIND_FROM_WEST_CONTROL] == 2) {
            if (gravityX < gravityXMax) gravityX++;
        }
        if (gravityX > gravityXMin) gravityX--;
    } else {
        if (controlState[WIND_FROM_WEST_CONTROL] == 2) {
            if (gravityX < gravityXMax) gravityX++;
        } else {
            gravityX = origGravityX;
        }
    }
    
    box2d[0].setGravity(gravityX, gravityY);
    box2d[1].setGravity(gravityX, gravityY);
    eventString = ofToString(gravityY);
    
    box2d[0].update();
    box2d[1].update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    for (int w=0; w < nWorlds; w++) {
        ofSetHexColor(0xFFFFFF);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofPushMatrix();
        ofTranslate(worldX[w], worldY[w]);
        background[w].draw(0, 0, 1379, 295);
        ofPopMatrix();
        ofSetHexColor(0xFFFFFF);
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        for (int i=0;i < nControls; i++) {
            if (controlState[i+w*nControls] > 0) {
              ofPushMatrix();
              if (controlState[i+w*nControls] == 1) {
                  ofSetHexColor(0xFFFFFF);
              } else {
                  ofSetHexColor(0xFFFF00);
              }
              ofTranslate(controlX[i], controlY[i]+worldY[w]+worldH+40);
              controlImage[i].draw(0, 0, controlW, controlH);
              ofPopMatrix();
            }
        }
    }
    
    // A World Circles
    for (int i=0; i<circlesA.size(); i++) {
        ofSetHexColor(0xBFE364);
        circlesA[i].get()->draw();
    }
    
    // B World Circles
    ofPushMatrix();
    ofTranslate(worldX[1], worldY[1]);
    for (int i=0; i<circlesB.size(); i++) {
        ofSetHexColor(0xE83AAB);
        circlesB[i].get()->draw();
    }
    ofPopMatrix();
    vagRounded.drawString(eventString, 98,198);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    /*
     Player 1: Fluxum
    w. jump
    a. left
    d. right
    s. stand up
    
    Player 2: Fluxa
    i. jump
    j. left
    l. right
    k. stand up
    
    Both players
    e. more boxen
    r. wind from east
    t. wind from west
    y. earthquake
    u. less gravity
    o. more gravity
    f. conjure clouds
    g. conjure lightning
    h. teleport bubble
    p. bubbles
    v. star
    c. ?
    x. spiral
    space. more/pause
     */

    if(key){
       
        switch(key){
            case OF_KEY_LEFT:
                    if (controlState[REVERSE_TIME] > 0) controlState[REVERSE_TIME] = 2;
                    break;
            case OF_KEY_RIGHT:
                    if (controlState[STEP_TIME] > 0) controlState[STEP_TIME] = 2;
                    break;
            case OF_KEY_DOWN:
                    if (controlState[HOLD_TIME] > 0) controlState[HOLD_TIME] = 2;
                    break;
            case 'w':
                 eventString = "up";
                 if (controlState[UP_CONTROL] > 0) controlState[UP_CONTROL] = 2;
                 break;
            case 'a':
                eventString = "left";
                if (controlState[LEFT_CONTROL] > 0) controlState[LEFT_CONTROL] = 2;
                break;
            case 'd':
                if (controlState[RIGHT_CONTROL] > 0) controlState[RIGHT_CONTROL] = 2;
                break;
            case 's':
                if (controlState[DOWN_CONTROL] > 0) controlState[DOWN_CONTROL] = 2;
                break;
            case 'e':
                if (controlState[BOXEN_CONTROL] > 0) controlState[BOXEN_CONTROL] = 2;
                break;
            case 'r':
                if (controlState[WIND_FROM_EAST_CONTROL] > 0) controlState[WIND_FROM_EAST_CONTROL] = 2;
                break;
            case 't':
                if (controlState[WIND_FROM_WEST_CONTROL] > 0) controlState[WIND_FROM_WEST_CONTROL] = 2;
                break;
            case 'y':
                if (controlState[EARTHQUAKE_CONTROL] > 0) controlState[EARTHQUAKE_CONTROL] = 2;
                break;
            case 'u':
                if (controlState[GRAVITY_UP_CONTROL] > 0) controlState[GRAVITY_UP_CONTROL] = 2;
                break;
            case 'o':
                if (controlState[MORE_GRAVITY_CONTROL] > 0) controlState[MORE_GRAVITY_CONTROL] = 2;
                break;
            case 'p':
                if (controlState[BUBBLE_CONTROL] > 0) controlState[BUBBLE_CONTROL] = 2;
                break;
            case 'f':
                if (controlState[CLOUD_CONTROL] > 0) controlState[CLOUD_CONTROL] = 2;
                break;
            case 'g':
                if (controlState[LIGHTNING_CONTROL] > 0) controlState[LIGHTNING_CONTROL] = 2;
                break;
            case 'h':
                if (controlState[TELEPORT_CONTROL] > 0) controlState[TELEPORT_CONTROL] = 2;
                break;
            case 'v':
                if (controlState[STAR_CONTROL] > 0) controlState[STAR_CONTROL] = 2;
                break;
            case 'c':
                if (controlState[QUESTION_CONTROL] > 0) controlState[QUESTION_CONTROL] = 2;
                break;
            case 'x':
                if (controlState[SPIRAL_CONTROL] > 0) controlState[SPIRAL_CONTROL] = 2;
                break;
            case ' ':
                if (controlState[MORE_CONTROL] > 0) controlState[MORE_CONTROL] = 2;
                break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key){
        switch(key){
            case OF_KEY_LEFT:
                if (controlState[REVERSE_TIME] > 0) controlState[REVERSE_TIME] = 1;
                break;
            case OF_KEY_RIGHT:
                if (controlState[STEP_TIME] > 0) controlState[STEP_TIME] = 1;
                break;
            case OF_KEY_DOWN:
                if (controlState[HOLD_TIME] > 0) controlState[HOLD_TIME] = 1;
                break;
            case 'w':
                eventString = "up";
                if (controlState[UP_CONTROL] > 0) controlState[UP_CONTROL] = 1;
                break;
            case 'a':
                eventString = "left";
                if (controlState[LEFT_CONTROL] > 0) controlState[LEFT_CONTROL] = 1;
                break;
            case 'd':
                if (controlState[RIGHT_CONTROL] > 0) controlState[RIGHT_CONTROL] = 1;
                break;
            case 's':
                if (controlState[DOWN_CONTROL] > 0) controlState[DOWN_CONTROL] = 1;
                break;
            case 'e':
                if (controlState[BOXEN_CONTROL] > 0) controlState[BOXEN_CONTROL] = 1;
                break;
            case 'r':
                if (controlState[WIND_FROM_EAST_CONTROL] > 0) controlState[WIND_FROM_EAST_CONTROL] = 1;
                break;
            case 't':
                if (controlState[WIND_FROM_WEST_CONTROL] > 0) controlState[WIND_FROM_WEST_CONTROL] = 1;
                break;
            case 'y':
                if (controlState[EARTHQUAKE_CONTROL] > 0) controlState[EARTHQUAKE_CONTROL] = 1;
                break;
            case 'u':
                if (controlState[GRAVITY_UP_CONTROL] > 0) controlState[GRAVITY_UP_CONTROL] = 1;
                break;
            case 'o':
                if (controlState[MORE_GRAVITY_CONTROL] > 0) controlState[MORE_GRAVITY_CONTROL] = 1;
                break;
            case 'p':
                if (controlState[BUBBLE_CONTROL] > 0) controlState[BUBBLE_CONTROL] = 1;
                break;
            case 'f':
                if (controlState[CLOUD_CONTROL] > 0) controlState[CLOUD_CONTROL] = 1;
                break;
            case 'g':
                if (controlState[LIGHTNING_CONTROL] > 0) controlState[LIGHTNING_CONTROL] = 1;
                break;
            case 'h':
                if (controlState[TELEPORT_CONTROL] > 0) controlState[TELEPORT_CONTROL] = 1;
                break;
            case 'v':
                if (controlState[STAR_CONTROL] > 0) controlState[STAR_CONTROL] = 1;
                break;
            case 'c':
                if (controlState[QUESTION_CONTROL] > 0) controlState[QUESTION_CONTROL] = 1;
                break;
            case 'x':
                if (controlState[SPIRAL_CONTROL] > 0) controlState[SPIRAL_CONTROL] = 1;
                break;
            case ' ':
                if (controlState[MORE_CONTROL] > 0) controlState[MORE_CONTROL] = 1;
                break;
        }
    }
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
