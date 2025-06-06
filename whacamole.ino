#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C address 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
const int ledPins[] = {6, 7, 8};
const int buttonPins[] = {9, 10, A0};
const int buzzerPin = A2;
const int startButton = A1;

int activeIndex = -1;
int score = 0;
int highScore = 0;

bool gameActive = false;
unsigned long lightOnTime;
unsigned long reactionTime = 1000;
unsigned long gameStartTime;
unsigned long gameDuration = 30000; // 30 seconds
bool newHighScoreSet = false;

void setup() {
  lcd.init();       
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("--Press Start--");

  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }

  pinMode(buzzerPin, OUTPUT);
  pinMode(startButton, INPUT);
  randomSeed(analogRead(A3));
}

void loop() {
  if (!gameActive) {
    if (digitalRead(startButton) == HIGH) {
      startGame();
    }
    return;
  }

  // Timer
  unsigned long elapsed = millis() - gameStartTime;
  unsigned long timeLeft = (gameDuration - elapsed) / 1000;
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(timeLeft);
  lcd.print("s   "); 

  if (elapsed >= gameDuration) {
    endGame();
    return;
  }

  if (millis() - lightOnTime > reactionTime) {
    digitalWrite(ledPins[activeIndex], LOW);
    delay(200);
    pickNextMole();
  }

  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      if (i == activeIndex && millis() - lightOnTime <= reactionTime) {
        score++;
      if (score > highScore) {
        highScore = score;
        if (!newHighScoreSet) {
          playHighScoreMelody();
          newHighScoreSet = true;
        }
      }
      beep(1);
      updateScoreDisplay();
      digitalWrite(ledPins[activeIndex], LOW);
      delay(300);
      updateDifficulty();
      pickNextMole();
      } else {
        if (score > 0) score--;
        beep(0); // wrong or late
        updateScoreDisplay();
        delay(300);
      }
    }
  }
}

void pickNextMole() {
  activeIndex = random(0, 3);
  digitalWrite(ledPins[activeIndex], HIGH);
  lightOnTime = millis();
}

void updateDifficulty() {
  if (score % 5 == 0 && reactionTime > 200) {
    reactionTime -= 100;
  }
}

void updateScoreDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.print(score);
  lcd.print(" Hi:");
  if (highScore < 10) lcd.print(" "); 
  lcd.print(highScore);
}

void startGame() {
  gameActive = true;
  newHighScoreSet = false;
  score = 0;
  reactionTime = 1000;
  lcd.clear();
  updateScoreDisplay();
  gameStartTime = millis();
  pickNextMole();
}

void endGame() {
  gameActive = false;
  for (int i = 0; i < 3; i++) digitalWrite(ledPins[i], LOW);
  lcd.clear();
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Final: ");
  lcd.print(score);
  delay(3000);
  lcd.clear();
  lcd.print("--Try Again!--");
}

void beep(bool correct) {
  tone(buzzerPin, correct ? 1000 : 300, 150);
}

void playHighScoreMelody() {
  tone(buzzerPin, 880, 150);  
  delay(150);
  tone(buzzerPin, 1046, 150); 
  delay(150);
  tone(buzzerPin, 1318, 250); 
  delay(250);
}
