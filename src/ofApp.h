#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

#define nControls (18)
#define nWorlds (2)

#define MORE_CONTROL (0)
#define LEFT_CONTROL (1)
#define UP_CONTROL (2)
#define DOWN_CONTROL (3)
#define RIGHT_CONTROL (4)
#define GRAVITY_UP_CONTROL (5)
#define BOXEN_CONTROL (6)
#define WIND_FROM_EAST_CONTROL (7)
#define WIND_FROM_WEST_CONTROL (8)
#define LIGHTNING_CONTROL (9)
#define CLOUD_CONTROL (10)
#define EARTHQUAKE_CONTROL (11)
#define MORE_GRAVITY_CONTROL (12)
#define TELEPORT_CONTROL (13)
#define BUBBLE_CONTROL (14)
#define STAR_CONTROL (15)
#define SPIRAL_CONTROL (16)
#define QUESTION_CONTROL (17)
#define REVERSE_TIME (18)
#define HOLD_TIME (19)
#define STEP_TIME (20)

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void checkControls();
    
    int controlType[nControls*2] = {
        STAR_CONTROL, BOXEN_CONTROL, WIND_FROM_EAST_CONTROL, GRAVITY_UP_CONTROL, EARTHQUAKE_CONTROL,  QUESTION_CONTROL, SPIRAL_CONTROL, LEFT_CONTROL, UP_CONTROL , DOWN_CONTROL, RIGHT_CONTROL, CLOUD_CONTROL, LIGHTNING_CONTROL, TELEPORT_CONTROL, MORE_GRAVITY_CONTROL, WIND_FROM_WEST_CONTROL, BUBBLE_CONTROL, MORE_CONTROL,
        
        STAR_CONTROL, BOXEN_CONTROL, WIND_FROM_EAST_CONTROL, GRAVITY_UP_CONTROL, EARTHQUAKE_CONTROL,  QUESTION_CONTROL, SPIRAL_CONTROL, LEFT_CONTROL, UP_CONTROL , DOWN_CONTROL, RIGHT_CONTROL, CLOUD_CONTROL, LIGHTNING_CONTROL, TELEPORT_CONTROL, MORE_GRAVITY_CONTROL, WIND_FROM_WEST_CONTROL, BUBBLE_CONTROL, MORE_CONTROL
    };
    
    int controlX[nControls] = { 17, 7, 8, 9, 10, 3, 1, 2, 15, 12, 11, 4, 14, 13, 16, 0, 6, 5 };
    int controlY[nControls] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int controlW = 62;
    int controlH = 62;
     // 0 = inactive, 1 = not pressed, 2 = pressed
    int controlState[nControls*2] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    
    float gravityX = 0.0;
    float gravityY = 20.0;
    float gravityXMin = -20.0;
    float gravityXMax = 20.0;
    float gravityYMin = -20.0;
    float gravityYMax = 20.0;
    float origGravityX = 0.0;
    float origGravityY = 20.0;
    
    ofTrueTypeFont vagRounded;
    string eventString;
    
    int worldX[2] = { 0, 0 };
    int worldY[2] = { 0, 384 };
    int worldW = 1380;
    int worldH = 295;
    
    ofImage controlImage[nControls];
    ofImage background[nWorlds];
    ofImage player[nWorlds];
    
    string controlImageFilename[nControls] = {
        "pauseMore.png", "left.png", "up.png", "down.png", "right.png", "lessGravity.png",
        "moreBoxen.png", "windFromEast.png", "windFromWest.png", "lightning.png",
        "clouds.png", "shake.png", "moreGravity.png", "teleport.png", "bubbles.png",
        "star.png", "swirl.png", "questionMark.png"
    };
    
    string playerImage[nWorlds] = { "fluxum.png", "fluxa1.png" };
    
    ofxBox2d                 box2d[nWorlds];
    
    vector <shared_ptr<ofxBox2dRect> >  circlesA;
    vector <shared_ptr<ofxBox2dCircle> >  circlesB;
    vector <shared_ptr<ofxBox2dRect> >    sharedRects;
    
    ofRectangle bounds[nWorlds];
		
};
