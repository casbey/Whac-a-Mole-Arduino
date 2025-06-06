# Arduino Whack-a-Mole Game

A reaction-based game built using an Arduino Uno. Players must press the correct button corresponding to a lit LED before time runs out. The game tracks score, high score, and uses an I2C LCD display for a clean user interface.

---

## Components Used

| Component               | Quantity | Notes                                      |
|-------------------------|----------|--------------------------------------------|
| Arduino Uno             | 1        | Main microcontroller board                 |
| 16x2 I2C LCD Display    | 1        | Display score, time, messages (SDA/SCL)    |
| LEDs                    | 3        | Light up randomly for player to respond    |
| 220Ω resistors          | 4        | For LEDs and buzzer protection             |
| Push Buttons            | 4        | 3 for gameplay, 1 for start/reset          |
| 10kΩ resistors          | 4        | Pull-down resistors for buttons            |
| Passive Buzzer          | 1        | Provides audio feedback                    |
| Breadboard              | 1        | Circuit assembly                           |
| Jumper Wires            | Many     | To connect all components                  |

---

## How It Works

- The game starts when the player presses the **start/reset button**
- One of the 3 LEDs turns on randomly
- The player must press the corresponding button **within the reaction time**
- Points are awarded for correct hits, and **deducted** for wrong or late presses (score doesn't go below 0)
- **High score** is tracked during the session
- A special melody plays if the player beats the high score
- The game lasts **30 seconds**, after which it ends and displays the final score

---

## Arduino Pin Layout

| Function        | Arduino Pin |
|----------------|-------------|
| LED 1–3         | D6, D7, D8  |
| Button 1–3      | D9, D10, A0 |
| Start Button    | A1          |
| Buzzer          | A2          |
| LCD SDA         | A4          |
| LCD SCL         | A5          |

---

## Key Features

-  Real-time reaction game logic
-  Timer displayed on LCD
-  Score + high score tracking
-  Sound effects for hits and misses
-  Melody for breaking high score
-  Difficulty scaling (faster reaction time as you score, starts with 1 second and gets smaller with each 5 points)

---

## Video

- 
