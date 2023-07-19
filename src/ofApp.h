#pragma once

#include "ofMain.h"

#define AMOUNT 30 // The amount of flies for dirty state

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



		// For animation
		int moduloRemainder;



		// Font and strings //
		ofTrueTypeFont pixelFont;
		const string hungerName = "HUNGER";
		const string tiredName = "TIRED";
		const string hygieneName = "HYGIENE";
		const string funName = "FUN";
		string hungerValue;
		string tiredValue;
		string hygieneValue;
		string funValue;
		const string feedKey = "Q";
		const string sleepKey = "W";
		const string washKey = "E";
		const string playKey = "R";
		


		// Different states of the tamagotchi //
		bool isHappy;
		bool isHungry;
		bool isTired;
		bool isDirty;
		bool isBored;
		bool isDead;



		// Used for stat changes //
		const int feedNum = 5;
		const int sleepNum = 5;
		const int cleanNum = 5;
		const int playNum = 2;

		// If the stats go above 10, it will decrease other stats
		const int tooMuchFoodDecrase = 1;
		const int tooMuchSleepDecrease = 1;
		const int tooMuchWashDecrease = 1;
		const int tooMuchFunDecrease = 1;

		// Decreases stats overtime
		const float hungerDecrease = 0.01;
		const float exhaustionDecrease = 0.005;
		const float hygieneDecrease = 0.0025;
		const float funDecrease = 0.0075;



		// The stats of the tamagotchi (not visible to user) //
		float hunger;
		float exhaustion;
		float hygiene;
		float fun;
		float total; // If it reaches 0, the tamagotchi dies (average of all stats)

		// Used to round the values to integers for it to be readable for user
		int tempHunger;
		int tempExhaustion;
		int tempHygiene;
		int tempFun;



		vector<float> speedX;
		vector<float> speedY;
};
