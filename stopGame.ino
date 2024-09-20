const int latchPin = 5;
const int clockPin = 6;
const int dataPin = 4;
const int buttonPin = 8;
const int buzzerPin = 13;
const int ledPin = 11;

int brightness = 5;
int fadeAmount = 5;

const int winBuzz = 500;
const int closeBuzz = 300;
const int looseBuzz = 100;

bool gameStart = 0;

unsigned long flashTimer;
unsigned long buttonTimer;

int flashTime = 500;

int points = 0;

int point = 12;
int ledPattern[13] = { 2, 4, 8, 16, 32, 64, 128, 64, 32, 16, 8, 4, 0 };

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  Serial.println("Follow Left-Most LED, Press Button to Begin! The Game Will Speed Up as Your Score Increases! [Right-Most Yellow is Red, I Ran Out :P].");

  updateShiftRegister();

  flashTimer = millis();
}

void loop() {

  while (millis() - flashTimer < flashTime - points) {
    if (digitalRead(buttonPin) == HIGH && millis() - buttonTimer > 50 && gameStart == 0) {
      gameStart = 1;
      point = 0;

      buttonTimer = millis();

      tone(buzzerPin, 100, 1500);

      Serial.println("Go in 3...");
      delay(1000);

      Serial.println("2...");
      delay(1000);

      Serial.println("1...");
      delay(1000);

      Serial.println("GOOO!!!");
    }

    if (digitalRead(buttonPin) == HIGH && millis() - buttonTimer > 50 && gameStart == 1) {
      buttonTimer = millis();

      switch (point) {
        case 3:
          points += 5;
          Serial.print("Green, Good Job! +5 points! Points are now ");
          Serial.println(points);
          tone(buzzerPin, winBuzz, 750);

          break;

        case 9:
          points += 5;
          Serial.print("Green, Good Job! +5 points! Points are now ");
          Serial.println(points);
          tone(buzzerPin, winBuzz, 750);

          break;

        case 2:
          points += 3;
          Serial.print("Yellow, So Close! +3 points! Points are now ");
          Serial.println(points);
          tone(buzzerPin, closeBuzz, 750);

          break;

        case 4:
          points += 3;
          Serial.print("Yellow, So Close! +3 points! Points are now ");
          Serial.println(points);
          tone(buzzerPin, closeBuzz, 750);

          break;

        case 8:
          points += 3;
          Serial.print("Yellow, So Close! +3 points! Points are now ");
          Serial.println(points);
          tone(buzzerPin, closeBuzz, 750);

          break;

        case 10:
          points += 3;
          Serial.print("Yellow, So Close! +3 points! Points are now ");
          Serial.println(points);
          tone(buzzerPin, closeBuzz, 750);

          break;

        default:
          points--;
          Serial.print("Red, Failed. -1 Point! Points are now ");
          Serial.println(points);
          tone(buzzerPin, looseBuzz, 750);

          break;
      }

      delay(500);
      point = 0;
      updateShiftRegister();

      delay(1000);
    }
  }

  //End of While Loop

  if (digitalRead(buttonPin) == LOW) {
    if (point < 11) {
      point++;
    }

    else if (point != 12) {
      point = 0;
    }

    flashTimer = millis();
    updateShiftRegister();
  }
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, ledPattern[point]);
  digitalWrite(latchPin, HIGH);
}
