#pragma once
class DetectingEffect
{
public:
	DetectingEffect(void);
    DetectingEffect(int ID);
	~DetectingEffect(void);

	void startEffect(float x, float y);
	void update();
	void display();

private:
    int effectID;
	int dt;
	bool visible;
	float positionX;
	float positionY;
};

