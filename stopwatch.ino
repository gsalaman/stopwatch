// SoftwareSerial is used to communicate with the XBee
// Adding LCD interface with Meep 4WD

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

/*================
 * LCD CONNECTIONS:  (note...we're using 4 bit mode here...)
 *   1 to GND
 *   2 to 5V
 *   3 to the contrast control...I did a hardcoded voltage divider.
 *   4 to Arduino digital pin LCD_REG_SEL
 *   5 to GND
 *   6 to Arduino digital pin LCD_ENABLE
 *   7 (no connection)
 *   8 (no connection)
 *   9 (no connection)
 *   10 (no connection)
 *   11 to Arduino  digital pin LCD_D4
 *   12 to Arduino  digital pin LCD_D5
 *   13 to Arduino  digital pin LCD_D6
 *   14 to Arduino  digital pin LCD_D7
 *   15 to 5V
 *   16 to GND
 *====================*/
 
#define LCD_D7         A0 
#define LCD_D6         A1
#define LCD_D5         A2
#define LCD_D4         A3
#define LCD_ENABLE     A4
#define LCD_REG_SEL    A5

#define BUTTON_PIN 10

// Our LCD has 2 rows of 16 characters.
#define LCD_CHARS 16
#define LCD_ROWS 2

LiquidCrystal lcd(LCD_REG_SEL, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*=====================================================================
 * Function: setup
 */
void setup() 
{  
  Serial.begin(9600); // Start serial communication

  pinMode(10, INPUT_PULLUP);
  
  lcd.begin(LCD_CHARS, LCD_ROWS);
  lcd.clear();
  lcd.print("Ready");
  
  Serial.println("Stopwatch initialized");
 
} // end of setup


/*=====================================================================
 * Function: loop
 */
void loop() 
{
  static bool running = false;
  static int last_button_state = HIGH;
  int current_button_state;
  static unsigned long start_time=0;
  unsigned long current_time;
  unsigned long running_time;
  unsigned long hours;
  unsigned long minutes;
  unsigned long seconds;
  
  // button presses start and restart the stopwatch.
  current_button_state = digitalRead(BUTTON_PIN);
  if ((last_button_state == HIGH) && (current_button_state == LOW))
  {
    running = true;
    start_time = millis();
  }
  last_button_state = current_button_state;

  if (running)
  {
    current_time = millis();
    running_time = current_time - start_time;
    seconds = running_time / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    
    seconds = seconds % 60;
    minutes = minutes % 60;

    lcd.setCursor(0,1);
    lcd.print(hours);
    lcd.print(":");
    if (minutes < 10) lcd.print("0");
    lcd.print(minutes);
    lcd.print(":");
    if (seconds < 10) lcd.print("0");
    lcd.print(seconds);
  }

  //delay(300);
  
}  // end of loop
