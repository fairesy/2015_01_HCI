#include "DetectingEffect.h"
#include "ofMain.h"

#define phase_1 20
#define	phase_2 40

DetectingEffect::DetectingEffect(void)
{
    effectID = 0;
	dt = 0;
	visible = false;
	positionX = 0.0f;
	positionY = 0.0f;
}

DetectingEffect::DetectingEffect(int ID)
{
    effectID = ID;
    dt = 0;
    visible = false;
    positionX = 0.0f;
    positionY = 0.0f;
}




DetectingEffect::~DetectingEffect(void)
{
}

void DetectingEffect::startEffect(float x, float y){
	dt = 0;
	positionX = x;
	positionY = y;
	visible = true;
}

void DetectingEffect::update(){
	dt = dt + 3;

	// check to init instance
	if (dt >= 120)
	{
		dt = 0;
		visible = false;
	}
}

void DetectingEffect::display()
{
	if (!visible)
	{
		return;
	}

	update();
    if (effectID == 0) {
        ofSetColor(30, 153, 197);
        ofEllipse(positionX, positionY, 10, 10);

        if (dt >= phase_1){
            ofSetColor(196, 15, 132);
            ofEllipse(positionX, positionY, dt - phase_1, dt - phase_1);
        }

        if (dt >= phase_2){
            ofSetColor(204, 232, 36);
            ofEllipse(positionX, positionY, dt - phase_2, dt - phase_2);
        }
    } else if (effectID == 1) {
        ofSetColor(30, 153, 197);
        ofEllipse(positionX, positionY, 10, 10);
        
        if (dt >= phase_1){
            ofSetColor(196, 132, 15);
            ofEllipse(positionX, positionY, dt - phase_1, dt - phase_1);
        }
        
        if (dt >= phase_2){
            ofSetColor(36, 232, 204);
            ofEllipse(positionX, positionY, dt - phase_2, dt - phase_2);
        }
    }
}