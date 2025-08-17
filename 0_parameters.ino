// ---------------------------------------------------
// -------------------PARAMETERS----------------------
// ---------------------------------------------------

// capture parameters
int numSamples = 20;
int shiftPixels = 26; // works for 20 samples, shift of 19 works for 50
int multiplier = 1;
int bias = 0;
int timer = 1000;

// image min and max pixel values
int minVal = 255;
int maxVal = 0;

// image display parameters
bool stretch = 0;
bool zoom = false;

// states from serial commands
bool running = false;
bool probing = false;


// stepper motor parameters
int stepsUntilContactX = 20;
int stepsMultiplierX = 32;
int stepsUntilContactY = 17;
int stepsMultiplierY = 32;

