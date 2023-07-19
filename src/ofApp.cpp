#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(255);

	// Initializing States //
	isHappy = true;
	isHungry = false;
	isTired = false;
	isDirty = false;
	isBored = false;
	isDead = false;

	// Initializing Stats //
	// Temp variables are used to save integer values separately from float values
	hunger = 10;
	tempHunger = int(hunger);
	exhaustion = 10;
	tempExhaustion = int(exhaustion);
	hygiene = 10;
	tempHygiene = int(hygiene);
	fun = 10;
	tempFun = int(fun);
	total = (hunger + exhaustion + hygiene + fun) / 4;

	// Font and string //
	pixelFont.load("Pixeled.ttf", 12);
	hungerValue = to_string(tempHunger);
	tiredValue = to_string(tempExhaustion);
	hygieneValue = to_string(tempHygiene);
	funValue = to_string(tempFun);

	// Animation //
	moduloRemainder = 0;

	// Creates tiny dots to represent flies for dirty state
	speedX.resize(AMOUNT);
	speedY.resize(AMOUNT);
	for (int i = 0; i < AMOUNT; i++)
	{
		speedX[i] = ofRandom(0.6, 0.9);
		speedY[i] = ofRandom(0.6, 0.9);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// 60 as in every 60 frames
	// The downside of using the line below is that it is assuming everyone has 60 Hz monitors
	// - Animations will be slower on 30 Hz screens and faster on above 60 Hz screens
	// - Values will be decreasing slower or faster
	moduloRemainder = ofGetFrameNum() % 60; // ofGetFrameNum() returns an int

	// These if statements are used to immediately turn the value to 0 as soon as it falls below 1
	// The user only sees integers, so they assume when it hits 0, it is exactly 0
	if (hunger < 1)
	{
		hunger = 0;
	}
	else // If it's above 1, it will slowly decrease the value overtime
	{
		hunger -= hungerDecrease;
	}

	if (exhaustion < 1)
	{
		exhaustion = 0;
	}
	else
	{
		exhaustion -= exhaustionDecrease;
	}

	if (hygiene < 1)
	{
		hygiene = 0;
	}
	else
	{
		hygiene -= hygieneDecrease;
	}

	if (fun < 1)
	{
		fun = 0;
	}
	else
	{
		fun -= funDecrease;
	}
	total = (hunger + exhaustion + hygiene + fun) / 4; // Used to calculate an average of all values

	// Rounds values to nearest integer
	tempHunger = round(hunger);
	tempExhaustion = round(exhaustion);
	tempHygiene = round(hygiene);
	tempFun = round(fun);

	// Applies new values to string to be displayed to user
	hungerValue = to_string(tempHunger);
	tiredValue = to_string(tempExhaustion);
	hygieneValue = to_string(tempHygiene);
	funValue = to_string(tempFun);

	// Figures out which state to be applied based on the values and punishes user for exceeding tamagotchi's limits
	if (isDead != true)
	{
		if (total <= 0) // If all stats are at 0
		{
			isDead = true;
		}
		else if (isHungry == false && isTired == false && isDirty == false && isBored == false) // If all values don't drop to a certain extent, it is happy
		{
			isHappy = true;
		}

		if (hunger <= 5) // Changes to hungry state
		{
			isHappy = false;
			isHungry = true;
		}
		else if (hunger > 10) // Punishes for feeding too much
		{
			hunger = 10;
			hygiene -= tooMuchFoodDecrase; // The more you feed, the dirtier it gets
		}
		else // If above 5, it is not hungry
		{
			isHungry = false;
		}

		if (exhaustion <= 5) // Changes to tired state
		{
			isHappy = false;
			isTired = true;
		}
		else if (exhaustion > 10) // Punishes for sleeping too much
		{
			exhaustion = 10;
			hunger -= tooMuchSleepDecrease; // The more it sleeps, the hungrier it gets
		}
		else // If above 5, it is not tired
		{
			isTired = false;
		}

		if (hygiene <= 5) // Changes to dirty state
		{
			isHappy = false;
			isDirty = true;
		}
		else if (hygiene > 10) // Punishes for washing too much
		{
			hygiene = 10;
			fun -= tooMuchWashDecrease; // The more it is washed, the more bored it is
		}
		else // If above 5, it is not dirty
		{
			isDirty = false;
		}

		if (fun <= 5) // Changes to bored state
		{
			isHappy = false;
			isBored = true;
		}
		else if (fun > 10) // Punishes for having too much fun
		{
			fun = 10;
			exhaustion -= tooMuchFunDecrease; // The more it is playing, the more tired it is
		}
		else // If above 5, it is not bored
		{
			isBored = false;
		}
	}
}

//--------------------------------------------------------------
// Appears when none of the stats are below a certain threshold
void happyState(int frame)
{
	// Animates idle movement
	if (frame < 30) // Raised Tamagotchi
	{
		ofPushMatrix();
		ofTranslate(ofGetWindowWidth() / 2 - 60, ofGetWindowHeight() / 2 - 200);
		ofSetColor(0);

		// Left Ear
		ofDrawRectangle(20, 10, 10, 50);
		ofDrawRectangle(30, 0, 10, 10);
		ofDrawRectangle(40, 10, 10, 50);

		// Right Ear
		ofDrawRectangle(70, 10, 10, 50);
		ofDrawRectangle(80, 0, 10, 10);
		ofDrawRectangle(90, 10, 10, 50);

		// Head
		ofDrawRectangle(10, 50, 100, 10);
		ofDrawRectangle(0, 60, 10, 60);
		ofDrawRectangle(110, 60, 10, 60);
		ofDrawRectangle(10, 120, 100, 10);

		// Eyes
		ofDrawRectangle(30, 70, 10, 10);
		ofDrawRectangle(80, 70, 10, 10);

		// Mouth
		ofDrawRectangle(30, 90, 10, 10);
		ofDrawRectangle(80, 90, 10, 10);
		ofDrawRectangle(30, 100, 60, 10);

		// Legs
		ofDrawRectangle(20, 130, 10, 50);
		ofDrawRectangle(90, 130, 10, 50);

		ofPopMatrix();
	}
	else if (frame >= 30) // Lowered Tamagotchi
	{
		ofPushMatrix();
		ofTranslate(ofGetWindowWidth() / 2 - 60, ofGetWindowHeight() / 2 - 200);
		ofSetColor(0);

		// Left Ear
		ofDrawRectangle(20, 20, 10, 50);
		ofDrawRectangle(30, 10, 10, 10);
		ofDrawRectangle(40, 20, 10, 50);

		// Right Ear
		ofDrawRectangle(70, 20, 10, 50);
		ofDrawRectangle(80, 10, 10, 10);
		ofDrawRectangle(90, 20, 10, 50);

		// Head
		ofDrawRectangle(10, 60, 100, 10);
		ofDrawRectangle(0, 70, 10, 60);
		ofDrawRectangle(110, 70, 10, 60);
		ofDrawRectangle(10, 130, 100, 10);

		// Eyes
		ofDrawRectangle(30, 80, 10, 10);
		ofDrawRectangle(80, 80, 10, 10);

		// Mouth
		ofDrawRectangle(30, 100, 10, 10);
		ofDrawRectangle(80, 100, 10, 10);
		ofDrawRectangle(30, 110, 60, 10);

		// Legs
		ofDrawRectangle(20, 130, 10, 50);
		ofDrawRectangle(90, 130, 10, 50);

		ofPopMatrix();
	}
}

// Appears when one of the stats is below a certain threshold
void sadState()
{
	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() / 2 - 60, ofGetWindowHeight() / 2 - 200);
	ofSetColor(0);

	// Left Ear
	ofDrawRectangle(0, 50, 50, 10);
	ofDrawRectangle(-10, 60, 20, 40);

	// Right Ear
	ofDrawRectangle(70, 50, 50, 10);
	ofDrawRectangle(110, 60, 20, 40);

	// Head
	ofDrawRectangle(10, 60, 100, 10);
	ofDrawRectangle(0, 70, 10, 60);
	ofDrawRectangle(110, 70, 10, 60);
	ofDrawRectangle(10, 130, 100, 10);

	// Eyes
	ofDrawRectangle(30, 80, 10, 10);
	ofDrawRectangle(80, 80, 10, 10);

	// Mouth
	ofDrawRectangle(30, 110, 10, 10);
	ofDrawRectangle(80, 110, 10, 10);
	ofDrawRectangle(30, 100, 60, 10);

	// Legs
	ofDrawRectangle(20, 130, 10, 50);
	ofDrawRectangle(90, 130, 10, 50);

	ofPopMatrix();
}

// Appears when the fun levels are low
void boredState()
{
	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() / 2 - 60, ofGetWindowHeight() / 2 - 200);
	ofSetColor(0);

	// Left Ear
	ofDrawRectangle(20, 30, 10, 20);
	ofDrawRectangle(10, 20, 30, 10);
	ofDrawRectangle(40, 30, 10, 20);

	// Right Ear
	ofDrawRectangle(70, 30, 10, 20);
	ofDrawRectangle(80, 20, 30, 10);
	ofDrawRectangle(90, 30, 10, 20);

	// Head
	ofDrawRectangle(10, 50, 100, 10);
	ofDrawRectangle(0, 60, 10, 60);
	ofDrawRectangle(110, 60, 10, 60);
	ofDrawRectangle(10, 120, 100, 10);

	// Eyes
	ofDrawRectangle(30, 70, 20, 10);
	ofDrawRectangle(70, 70, 20, 10);

	// Mouth
	ofDrawRectangle(30, 90, 60, 10);

	// Legs
	ofDrawRectangle(20, 130, 10, 50);
	ofDrawRectangle(90, 130, 10, 50);

	ofPopMatrix();
}

// A grave appears for the tamagotchi
void deadState()
{
	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() / 2 - 60, ofGetWindowHeight() / 2 - 200);
	ofSetColor(0);

	// Grave
	ofDrawRectangle(20, 180, 90, 10);
	ofDrawRectangle(20, 100, 10, 80);
	ofDrawRectangle(30, 90, 10, 10);
	ofDrawRectangle(40, 80, 10, 10);
	ofDrawRectangle(50, 70, 30, 10);
	ofDrawRectangle(80, 80, 10, 10);
	ofDrawRectangle(90, 90, 10, 10);
	ofDrawRectangle(100, 100, 10, 80);

	// RIP text
	ofDrawRectangle(35, 115, 15, 5);
	ofDrawRectangle(50, 120, 5, 10);
	ofDrawRectangle(40, 130, 10, 5);
	ofDrawRectangle(35, 120, 5, 30);
	ofDrawRectangle(40, 135, 5, 5);
	ofDrawRectangle(45, 140, 5, 5);
	ofDrawRectangle(50, 145, 5, 5);

	ofDrawRectangle(62.5, 115, 5, 35);

	ofDrawRectangle(75, 115, 5, 35);
	ofDrawRectangle(80, 115, 10, 5);
	ofDrawRectangle(90, 120, 5, 10);
	ofDrawRectangle(80, 130, 10, 5);

	ofDrawRectangle(35, 155, 60, 5);

	ofPopMatrix();
}

// Will make a decreasing heart meter animation (flashes betwen half empty and empty)
void hungryIcon(int frame)
{
	if (frame < 30) // Half-filled heart
	{
		ofPushMatrix();
		ofTranslate(ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 180);

		// Heart shape
		ofDrawRectangle(5, 0, 10, 5);
		ofDrawRectangle(15, 5, 5, 5);
		ofDrawRectangle(20, 0, 10, 5);
		ofDrawRectangle(30, 5, 5, 15);
		ofDrawRectangle(25, 20, 5, 5);
		ofDrawRectangle(20, 25, 5, 5);
		ofDrawRectangle(15, 30, 5, 5);
		ofDrawRectangle(10, 25, 5, 5);
		ofDrawRectangle(5, 20, 5, 5);
		ofDrawRectangle(0, 5, 5, 15);

		// Half-filled
		ofDrawRectangle(5, 15, 25, 5);
		ofDrawRectangle(10, 20, 15, 5);
		ofDrawRectangle(15, 25, 5, 5);

		ofPopMatrix();
	}
	else if (frame >= 30) // Empty heart
	{
		ofPushMatrix();
		ofTranslate(ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 180);

		// Heart shape
		ofDrawRectangle(5, 0, 10, 5);
		ofDrawRectangle(15, 5, 5, 5);
		ofDrawRectangle(20, 0, 10, 5);
		ofDrawRectangle(30, 5, 5, 15);
		ofDrawRectangle(25, 20, 5, 5);
		ofDrawRectangle(20, 25, 5, 5);
		ofDrawRectangle(15, 30, 5, 5);
		ofDrawRectangle(10, 25, 5, 5);
		ofDrawRectangle(5, 20, 5, 5);
		ofDrawRectangle(0, 5, 5, 15);

		ofPopMatrix();
	}
}

// Animates the ZZZ icon
void tiredIcon(int frame)
{
	int y_Increase = 0;

	if (frame < 30)
	{
		y_Increase = 10;
	}
	else if (frame >= 30)
	{
		y_Increase = 0;
	}

	// Some letters go up, some down
	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() / 2 + 60, ofGetWindowHeight() / 2 - 180 + y_Increase);
	ofDrawRectangle(0, 0, 20, 5);
	ofDrawRectangle(10, 5, 5, 5);
	ofDrawRectangle(5, 10, 5, 5);
	ofDrawRectangle(0, 15, 20, 5);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() / 2 + 60, ofGetWindowHeight() / 2 - 180 - y_Increase);
	ofDrawRectangle(25, 5, 20, 5);
	ofDrawRectangle(35, 10, 5, 5);
	ofDrawRectangle(30, 15, 5, 5);
	ofDrawRectangle(25, 20, 20, 5);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() / 2 + 60, ofGetWindowHeight() / 2 - 180 + y_Increase);
	ofDrawRectangle(50, 10, 20, 5);
	ofDrawRectangle(60, 15, 5, 5);
	ofDrawRectangle(55, 20, 5, 5);
	ofDrawRectangle(50, 25, 20, 5);
	ofPopMatrix();
}

// Animates flies around the tamagotchi
void dirtyIcon(vector<float> speedX, vector<float> speedY) // Will make tiny flies move in noise around the tamagotchi
{
	float time = ofGetElapsedTimef();
	float x = 0;
	float y = 0;

	for (int i = 0; i < AMOUNT; i++)
	{
		// Randomises the position on the perlin noise with randomised speed to simulate a fly
		x = ofGetWidth() * ofNoise(time * speedX[i]);
		y = ofGetHeight() * ofNoise(time * speedY[i]);

		// Keeps the flies contained in a small area to fit around the tamagotchi
		float tempX = ofMap(x, 0, ofGetWidth(), 0, 300, true);
		float tempY = ofMap(y, 0, ofGetHeight(), 0, 300, true);

		// Translates/Draws the flies onto the tamagotchi
		ofPushMatrix();
		ofTranslate(100,0);
		ofDrawRectangle(tempX, tempY, 3, 3);
		ofPopMatrix();
	}
}

// Menu UI
void menu(ofTrueTypeFont pixelFont, string hungerName, string tiredName, string hygieneName, string funName, string hungerValue, string tiredValue, string hygieneValue, string funValue, string feedKey, string sleepKey, string washKey, string playKey)
{
	ofDrawRectangle(0, 300, ofGetWindowWidth(), 20);
	pixelFont.drawString(hungerName, ofGetWidth() / 2 - pixelFont.stringWidth(hungerName) / 2 - 182, ofGetHeight() / 2 - pixelFont.stringHeight(hungerName) / 2 + 120);
	pixelFont.drawString(tiredName, ofGetWidth() / 2 - pixelFont.stringWidth(tiredName) / 2 - 195, ofGetHeight() / 2 - pixelFont.stringHeight(tiredName) / 2 + 160);
	pixelFont.drawString(hygieneName, ofGetWidth() / 2 - pixelFont.stringWidth(hygieneName) / 2 - 176, ofGetHeight() / 2 - pixelFont.stringHeight(hygieneName) / 2 + 200);
	pixelFont.drawString(funName, ofGetWidth() / 2 - pixelFont.stringWidth(funName) / 2 - 204, ofGetHeight() / 2 - pixelFont.stringHeight(funName) / 2 + 240);

	pixelFont.drawString(hungerValue, ofGetWidth() / 2 - pixelFont.stringWidth(hungerValue) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(hungerValue) / 2 + 120);
	pixelFont.drawString(tiredValue, ofGetWidth() / 2 - pixelFont.stringWidth(tiredValue) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(tiredValue) / 2 + 160);
	pixelFont.drawString(hygieneValue, ofGetWidth() / 2 - pixelFont.stringWidth(hygieneValue) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(hygieneValue) / 2 + 200);
	pixelFont.drawString(funValue, ofGetWidth() / 2 - pixelFont.stringWidth(funValue) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(funValue) / 2 + 240);

	pixelFont.drawString(feedKey, ofGetWidth() / 2 + 200 - pixelFont.stringWidth(feedKey) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(feedKey) / 2 + 120);
	pixelFont.drawString(sleepKey, ofGetWidth() / 2 + 200 - pixelFont.stringWidth(sleepKey) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(sleepKey) / 2 + 160);
	pixelFont.drawString(washKey, ofGetWidth() / 2 + 200 - pixelFont.stringWidth(washKey) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(washKey) / 2 + 200);
	pixelFont.drawString(playKey, ofGetWidth() / 2 + 200 - pixelFont.stringWidth(playKey) / 2, ofGetHeight() / 2 - pixelFont.stringHeight(playKey) / 2 + 240);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Draws different states depending on the boolean variables
	if (isDead != true)
	{
		if (isHappy == false && isBored == false && isTired == false) // If the rest of the values are low except fun and exhaustion, it becomes sad
		{
			sadState(); // Draws sad state
		}
		else if (isBored == true || isTired == true) // If either fun or exhaustion is low, it becomes bored/tired/annoyed
		{
			boredState(); // Draws bored state
		}
		else if (isHappy == true)
		{
			happyState(moduloRemainder); // Draws happy state
		}

		if (isHungry == true)
		{
			hungryIcon(moduloRemainder); // Animates hungry icon
		}

		if (isTired == true)
		{
			tiredIcon(moduloRemainder); // Animates tired icon
		}

		if (isDirty == true)
		{
			dirtyIcon(speedX, speedY); // Animates flies
		}
	}
	else
	{
		deadState(); // Draws dead state
	}

	menu(pixelFont, hungerName, tiredName, hygieneName, funName, hungerValue, tiredValue, hygieneValue, funValue, feedKey, sleepKey, washKey, playKey); // Draws UI
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	// If isDead is true, it disables key presses
	if (isDead != true)
	{
		// Feeding key
		if (key == 81 || key == 113) // Q
		{
			hunger += feedNum;
		}

		// Sleeping key
		if (key == 87 || key == 119) // W
		{
			exhaustion += sleepNum;
		}

		// Washing key
		if (key == 69 || key == 101) // E
		{
			hygiene += cleanNum;
		}

		// Playing key
		if (key == 82 || key == 114) // R
		{
			fun += playNum;
		}
	}
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
