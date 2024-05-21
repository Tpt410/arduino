#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <stdio.h>

#define DELAY_TIME_SLOW 8000 // 8 sec
#define DELAY_TIME_NORMAL 4000 // 4 sec
#define DELAY_TIME_FAST 2000 // 2 sec
#define DELAY_TIME_EXTREME 500 // 0.5 sec

#define LED_PIN_1 7
#define LED_PIN_2 6
#define LED_PIN_3 5

#define BUTTON_PIN_START 2
#define BUTTON_PIN_SPEED 3

int iLedOnCnt = 0;
boolean bLedStatus1 = LOW; 
boolean bLedStatus2 = LOW; 
boolean bLedStatus3 = LOW;

// set the LCD address to 0x27
LiquidCrystal_PCF8574 lcd(0x27); 

// THESAURUS Words
const char WordStr[][16] = {
  "Happy", "Joyful",
  "Big", "Large",
  "Small", "Little",
  "Good", "Excellent",
  "Bad", "Poor",
  "Fast", "Quick",
  "Slow", "Sluggish",
  "Hot", "Warm",
  "Cold", "Chilly",
  "Beautiful", "Gorgeous",
  "Ugly", "Unattractive",
  "Strong", "Powerful",
  "Weak", "Frail",
  "Smart", "Intelligent",
  "Stupid", "Foolish",
  "Rich", "Wealthy",
  "Poor", "Needy",
  "Happy", "Content",
  "Sad", "Melancholy",
  "Big", "Huge",
  "Small", "Tiny",
  "Fast", "Rapid",
  "Slow", "Leisurely",
  "Hot", "Scorching",
  "Cold", "Freezing",
  "Beautiful", "Lovely",
  "Ugly", "Hideous",
  "Strong", "Robust",
  "Weak", "Feeble",
  "Smart", "Clever",
  "Stupid", "Ignorant",
  "Rich", "Affluent",
  "Poor", "Destitute",
  "Happy", "Delighted",
  "Dumb", "Dim-witted",
  "Brave", "Fearless",
  "Cowardly", "Timid",
  "Kind", "Compassionate",
  "Mean", "Nasty",
  "Strong", "Mighty",
  "Weak", "Feeble",
  "Rich", "Affluent",
  "Clean", "Spotless",
  "Dirty", "Grimy",
  "Hard", "Firm",
  "Soft", "Smooth",
  "Loud", "Boisterous",
  "Quiet", "Hushed",
  "Happy", "Elated",
  ""
  };

// Set light status of LEDs : LED1, LED2, LED3
void setLED(boolean led1, boolean led2, boolean led3)
{
  digitalWrite(LED_PIN_1, led1);
  digitalWrite(LED_PIN_2, led2);
  digitalWrite(LED_PIN_3, led3);
  bLedStatus1 = led1;
  bLedStatus2 = led2;
  bLedStatus3 = led3;
} // setLed()

// Print LCD  
void printLCD(const char* row1, const char* row2)
{
  lcd.clear();  //clean screen

  lcd.setCursor(0, 0); // Row 1
  lcd.print(row1);
  
  lcd.setCursor(0, 1); // Row 2
  lcd.print(row2);
} // printLCD()

void setup()
{
  lcd.begin(16,2);
  lcd.setBacklight(255);
  printLCD("HELLO EVERYONE!!", "");
  delay(2000);

  pinMode(LED_PIN_1, INPUT);
  pinMode(LED_PIN_2, INPUT);
  pinMode(LED_PIN_3, INPUT);
  pinMode(BUTTON_PIN_START, INPUT);
  pinMode(BUTTON_PIN_SPEED, INPUT);

  // default speed : Normal  
  setLED(HIGH, LOW, LOW);
  iLedOnCnt = 1;

  printLCD("  -THESAURUS-  ", " By Potter Tsai ");
  delay(2000);
    
} // setup()

void loop()
{
  // L Key : Set the speed
  // R Key : Start 
  printLCD("L KEY : SPEED", "R KEY : START");

  // Set the speed
  while (digitalRead(BUTTON_PIN_START) == LOW) // waiting for START pressing
  {
    if (digitalRead(BUTTON_PIN_SPEED) == HIGH) // if SPEED pressed
    {  
      iLedOnCnt = iLedOnCnt + 1;
     
      switch (iLedOnCnt){
        case 1:
          setLED(HIGH, LOW, LOW);
          printLCD("Set speed to", "Normal");
        break;
        case 2:
          setLED(HIGH, HIGH, LOW);
          printLCD("Set speed to", "Fast");
        break;
        case 3:
          setLED(HIGH, HIGH, HIGH);
          printLCD("Set speed to", "Extreme!!");
        break;
        default: // 0 or others
          setLED(LOW, LOW, LOW);
          printLCD("Set speed to", "Slow");
          iLedOnCnt = 0;
        break;
      }
    }
    delay(150);
  }

  printLCD("Let's get...", "Started!!");
  delay(DELAY_TIME_NORMAL); 
  
  // Show words
  for (int i = 0; strlen(WordStr[i]); i = i + 2) 
  {
    printLCD(WordStr[i], WordStr[i+1]);

    if (bLedStatus1 == HIGH && bLedStatus2 == HIGH && bLedStatus3 == HIGH) 
      delay(DELAY_TIME_EXTREME); 
    else if(bLedStatus1 == HIGH && bLedStatus2 == HIGH && bLedStatus3 == LOW) 
      delay(DELAY_TIME_FAST); 
    else if(bLedStatus1 == HIGH && bLedStatus2 == LOW && bLedStatus3 == LOW) 
      delay(DELAY_TIME_NORMAL);
    else 
      delay(DELAY_TIME_SLOW);   
  }
} // loop()