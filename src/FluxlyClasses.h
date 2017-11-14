//
//  FluxlyClasses.h
//  Fluxly
//
//  Created by as220 on 11/14/17.
//

#ifndef customClasses_h
#define customClasses_h

class FluxlyPlayer : public ofxBox2dRect {
public:
    ofImage playerImage;
    
    FluxlyPlayer() {
        playerImage.load("fluxum1.png");
    }

    void draw() {
        if(body == NULL) {
            return;
        }
        ofPushMatrix();
        ofTranslate(ofxBox2dBaseShape::getPosition());
        ofRotate(getRotation(), 0, 0, 1);
        ofSetHexColor(0xFFFFFF);
        playerImage.draw(0, 0, 64, 64 );
        ofPopMatrix();
    }
};

class FluxlyBox : public ofxBox2dRect {
public:
    FluxlyBox() {
    }
    
    ofColor color;
    
    void draw() {
        if(body == NULL) {
            return;
        }
        ofPushMatrix();
        ofSetColor(color.r, color.g, color.b);
        ofTranslate(ofxBox2dBaseShape::getPosition());
        ofRotate(getRotation(), 0, 0, 1);
        mesh.draw();
        ofPopMatrix();
        
    }
};

class FluxlyCircle : public ofxBox2dCircle {
public:
    FluxlyCircle() {
    }
    
    ofColor color;
    
    void draw() {
        if(!isBody()) return;
        ofPushMatrix();
        ofSetColor(color.r, color.g, color.b);
        ofTranslate(ofxBox2dBaseShape::getPosition());
        //ofRotate(getRotation(), 0, 0, 1);
        ofDrawCircle(0, 0, getRadius());
        ofPopMatrix();
    }
};

#endif /* customClasses_h */
