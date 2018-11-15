
// Test program to display reads of RPM libray

#include<RpmMeter.h>
#define PIN_SIGNAL   2  // pin for the signal of sensor
#define SIG_PER_TURN 1  // how many signals occur during one turn
#define SAMPLES_COUNT 1 // after how many signals calculate speed  

#define USE_LCD  //comment out if no display available... //

#ifdef USE_LCD
  // just an output display driver. her example with a 74HC595 latch  
  #include <LiquidCrystal_SR2W.h>
  #define PIN_LCD_CLK   7  // digital Pin for clock at the 74HC595
  #define PIN_LCD_DATA  8 //  digital Pin for data at the 74HC595
  LiquidCrystal_SR2W lcd(PIN_LCD_DATA, PIN_LCD_CLK ,POSITIVE);
#endif // USE_LCD

#include <LatchControl.h>
#define CLOCKPIN 9

LatchControl latch(CLOCKPIN, MODE_1W);



int rpmValue = 0;
long int microsPerTurn = 0;
void setup()
{
  RPM.initialize(PIN_SIGNAL, SIG_PER_TURN, SAMPLES_COUNT);
#ifdef USE_LCD

  lcd.begin(16,2);               // initialize the lcd
  lcd.home();                   // go home
  lcd.setBacklight(1);
  lcd.print("Test for Tacho-");
  lcd.setCursor(0,1);
  lcd.print("meter.");
  lcd.noCursor();
  delay(1200);
  lcd.clear();
#endif // USE_LCD

  Serial.begin(9600);

}

String leftFill(String a, byte len, String letter)
{
    // fills a string with letters from left side that the resulting length is reached
    while (a.length() < len)
    {
        a = letter + a;
    }
    return a;
}


void loop()
{
    rpmValue = RPM.getRpm();
    microsPerTurn = RPM.getMicrosPerTurn();

  #ifdef USE_LCD
    //lcd.home();
    //lcd.print("rpm" + leftFill(String(rpmValue), 10, " ") + " ");
    lcd.print("r");
    //lcd.setCursor(0,1);
    //lcd.print("myS/U" + leftFill(String(microsPerTurn), 8, " ") + " ");
  #endif // USE_LCD
    delay(100);
    Serial.print(leftFill(String(rpmValue), 6, " ")  + "\n");

}



