#include <Adafruit_CircuitPlayground.h>  // Library for Circuit Playground functions
#include "pitches.h"                     // File for musical tones


#define CPLAY_NEOPIXELNB 10

// Pattern types supported:
enum  pattern { NONE, RAINBOW_CYCLE, THEATER_CHASE, COLOR_WIPE, SCANNER, FADE };
// Patern directions supported:
enum  direction { FORWARD, REVERSE };




class NeoPatterns : public Adafruit_CircuitPlayground
{
    public:

    // Member Variables:  
    pattern  ActivePattern;  // which pattern is running
    direction Direction;     // direction to run the pattern
    
    unsigned long Interval;   // milliseconds between updates
    unsigned long lastUpdate; // last update of position
    
    uint32_t Color1, Color2;  	// What colors are in use
    uint16_t TotalSteps;  	// total number of steps in the pattern
    uint16_t Index;  		// current step within the pattern
    
    void (*OnComplete)();  // Callback on completion of pattern

    // ----- Constructor - calls base-class constructor to initialize strip ----------------------------------
    NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)()) : Adafruit_CircuitPlayground()
    {
        OnComplete = callback;
    }

    // ----- Update the pattern -------------------------------------------------------------------------------------
    void Update()
    {
        if((millis() - lastUpdate) > Interval) // time to update
        {
            lastUpdate = millis();
            switch(ActivePattern)
            {
                case RAINBOW_CYCLE: 	RainbowCycleUpdate(); 	break;
                case THEATER_CHASE: 	TheaterChaseUpdate(); 	break;
                case COLOR_WIPE:	ColorWipeUpdate();	break;
                case SCANNER:		ScannerUpdate();	break;
                case FADE:		FadeUpdate();		break;
                default: break;
            }
        }
    }

    // ---- Reverse pattern direction ---------------------------------------------------------------------
    void Reverse()
    {
        if (Direction == FORWARD)
        {
            Direction = REVERSE;
            Index = TotalSteps-1;
        }
        else
        {
            Direction = FORWARD;
            Index = 0;
        }
    }
    // ----- Increment the Index and reset at the end --------------------------------------------------------------------
    void Increment()
    {
        if (Direction == FORWARD)
        {
           Index++;
           if (Index >= TotalSteps)
            {
                Index = 0;
                if (OnComplete != NULL) { OnComplete(); }
            }
        }
        else // Direction == REVERSE
        {
            --Index;
            if (Index <= 0)
            {
                Index = TotalSteps-1;
                if (OnComplete != NULL) { OnComplete(); }
            }
        }
    }

	// ----- Initialize for a ColorWipe -----------------------------------------------------------------
	    void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD)
	    {
		ActivePattern = COLOR_WIPE;
		Interval = interval;
		TotalSteps = CPLAY_NEOPIXELNB;
		Color1 = color;
		Index = 0;
		Direction = dir;
	    }
    
	// ----- Update the Color Wipe Pattern ------------------------------------------------------------
	    void ColorWipeUpdate()
	    {
		setPixelColor(Index, Color1);
		show();
		Increment();
	    }    
}






setup()
{
  // ????? CircuitPlayground.begin();  ?????? CPLAY_NEOPIXELPIN
}

loop()
{
}


