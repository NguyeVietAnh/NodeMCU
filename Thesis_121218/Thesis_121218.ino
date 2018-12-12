
// SDA -- PIN D1
// SCL -- PIN D2
// POWER -   5V
// VRX  -    D6
// VRY -     D7
// SW  -     D8
// PWM -     D3
// DIR -     D4
// BRAK -    D5

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

//----------------------------------------------------------------------------------
#define SW_VERSION "ServoCtrlBlynk_V.1" 

/*NodeMCU */
#include <ESP8266WiFi.h>
char ssid [] = "NgocChau";
char pass [] = "67689606";

/* Blynk */
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth [] = "784fc5249758459e848f8352ab353f33"; // Servo Control Project // Servo Control Project
//----------------------------


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define Vx D6 // Define / Equate "Vx" with D6, the pin where Vx is connected
#define Vy D7 // Define / Equate "Vy" with D7, the pin where Vy is connected
#define Button D8 // Define / Equate Button with D8, the pin where the button is connected


void setup()
{
  Serial.begin(9600);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  //------Initial LCD display------
  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  testdrawstyles();
  //--------Initial configuration of Joystick--------------------------------------------------
  pinMode(Vx, INPUT); // Configure Vx (A0) as an Input
  pinMode(Vy, INPUT); // Configure Vy (A1) as an Input
  pinMode(Button, INPUT_PULLUP); // Configure Button (D8) as an Input, internally "pulled-up" to 5V
                                 // Note, we're configuring an Analog input as digital input
                                 // which is perfectly fine.  I did this to make the wiring easier
                                 // and keep all of the wires on the same side of the board

  Blynk.begin(auth, ssid, pass);  // Set up Wifi

}


void loop()
{
  int x, y, btn;
  
  x = analogRead(Vx); // Read the analog value of Vx (Analog Values are from 0-1023 which equate to 0V to 5V)
  y = analogRead(Vy); // Read the analog value of Vy
  btn = digitalRead(Button); // Read the button.  When the button is open (unpushed),
                             // the input will read High (+5V)
                             // When the button is closed (pressed), the input pin
                             // is connected to ground and will read Low (0V)
  
//  Serial.print(x);  // Print the X value to the serial port
//  Serial.print("\t"); // Print a Tab character 
//  Serial.print(y);  // Print the Y value
//  Serial.print("\t"); // Print a Tab
//  Serial.println(btn); // Print the value of the Btn (0=Pushed, 1 = Not Pushed)
  
//  delay(50); // Delay 250ms so the results don't print too quickly
 if (btn == 0)
 {
 int pwm_adc;
 pwm_adc = analogRead(D6); /* Input from Potentiometer for speed control */
 analogWrite(D3,pwm_adc);
 delayMicroseconds(10);



  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Running..."));
  display.display();
  delay(1);

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,16);             // Start at top-left corner
  display.println(F("Speed"));
  display.display();
  delay(1);
 
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(66,16);             // Start at top-left corner
  display.printf("%d",pwm_adc); 
  display.display();
  delay(1);
  display.clearDisplay();
 }


  
  
}
void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("BME Departerment"));
  display.display();
  delay(2000); 
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Electrospinning"));
  display.display();
  delay(2000);
  display.clearDisplay(); 

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Design by NVA"));
  display.display();
  display.clearDisplay();
  delay(2000); 
 
 
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Running..."));
  display.display();
  delay(100);

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,16);             // Start at top-left corner
  display.println(F("Speed"));
  display.display();
  delay(100);
 



 
  


}
