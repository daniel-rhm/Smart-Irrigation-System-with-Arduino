#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

// Pin definitions
const int soilPin    = A2;  // Soil moisture sensor analog input
const int relayPin   = 5;   // Relay control pin for water pump
const int ledRed     = 2;   // Red LED
const int ledYellow  = 3;   // Yellow LED
const int ledGreen   = 4;   // Green LED

// Sensor calibration values
const int dryValue = 462;   // Raw value when soil is completely dry (~0%)
const int wetValue = 160;   // Raw value when soil is completely wet (~100%)

// Thresholds for moisture levels
const int dryThreshold  = 30;  // Below 30% moisture → soil is dry
const int goodThreshold = 60;  // Above 60% moisture → soil is good

// State variables
int currentStage = 0;                 // Current system stage (1-4)
unsigned long stageStartTime = 0;     // Timestamp when current stage started
bool wateringActive = false;          // Flag indicating if watering is active

void setup() {
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(relayPin, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  
  // Initial state: pump off, LEDs off
  digitalWrite(relayPin, HIGH);  // Pump OFF (HIGH = off for most relay modules)
  allLedsOff();
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  
  // Start in ideal condition (stage 4)
  currentStage = 4;
  updateDisplay();
}

void loop() {
  // Read raw sensor value and convert to moisture percentage
  int rawValue = analogRead(soilPin);
  int moisture = map(rawValue, dryValue, wetValue, 0, 100);
  moisture = constrain(moisture, 0, 100);
  
  Serial.print("Moisture: ");
  Serial.println(moisture);

  // Stage 1: Soil detected as dry
  if (moisture < dryThreshold && currentStage != 1 && currentStage != 2 && currentStage != 3) {
    currentStage = 1;
    stageStartTime = millis();
    updateDisplay();
  }

  // Stage 1 → Stage 2: Wait 30 seconds before proceeding
  if (currentStage == 1 && millis() - stageStartTime >= 30000UL) {
    currentStage = 2;
    stageStartTime = millis();
    updateDisplay();
  }

  // Stage 2 → Stage 3: After 10 seconds, start watering
  if (currentStage == 2 && millis() - stageStartTime >= 10000UL) {
    currentStage = 3;
    wateringActive = true;
    digitalWrite(relayPin, LOW);  // Pump ON
    updateDisplay();
  }

  // Stage 3: Watering in progress – blink yellow LED
  if (currentStage == 3) {
    // Blink yellow LED (500ms interval)
    digitalWrite(ledYellow, (millis() / 500) % 2 == 0 ? HIGH : LOW);
    
    // Stop watering when soil reaches good moisture level
    if (moisture >= goodThreshold) {
      currentStage = 4;
      wateringActive = false;
      digitalWrite(relayPin, HIGH);  // Pump OFF
      updateDisplay();
    }
  }

  // Stage 4: Ideal condition – restart cycle when soil dries again (with hysteresis)
  if (currentStage == 4 && moisture < dryThreshold - 10) {
    currentStage = 1;
    stageStartTime = millis();
    updateDisplay();
  }

  delay(500);  // Loop delay for stability
}

void updateDisplay() {
  lcd.clear();
  
  // Turn off all LEDs before setting the correct one
  allLedsOff();
  
  switch (currentStage) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Stage 1");
      lcd.setCursor(0, 1);
      lcd.print("Soil is Dry");
      digitalWrite(ledRed, HIGH);
      break;
      
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Stage 2");
      lcd.setCursor(0, 1);
      lcd.print("Start Watering");
      digitalWrite(ledYellow, HIGH);  // Solid yellow
      break;
      
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Stage 3");
      lcd.setCursor(0, 1);
      lcd.print("Watering...");
      // Yellow blinking handled in loop()
      break;
      
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Stage 4");
      lcd.setCursor(0, 1);
      lcd.print("Condition Ideal");
      digitalWrite(ledGreen, HIGH);
      break;
  }
}

void allLedsOff() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
}
