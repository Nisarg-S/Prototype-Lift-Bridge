//-------------------------------------------------------------------------------
//Author: Nisarg Shah
//Program: Liftbridge Arudino Function Code
//Last edited: February 28th, 2019
//Description: Code which controls all functions of the Down and Under Liftbridge
//-------------------------------------------------------------------------------
//Times for Vertical and Horizontal Movement
const int horizontalTime = 4400;
const int verticalTime = 3800;

//Inital Motor Power
int motorPower = 55;

//Pin Numbers of Devices
// Open and Close Buttons
const int openButton = 2;
const int closeButton = 13;

//Vertical Motor
const int verticalClockwise  = 5;  // Pin 14 of L293
const int veritcalCounterClockwise  = 6;  // Pin 10 of L293

//Horizontal Motor
const int horizontalClockwise  = 10; // Pin  7 of L293
const int horizontalCounterClockwise  = 9;  // Pin  2 of L293

//Warning Symbols
const int ledPin = 1;
const int speakerPin = 11;

//determines if bridge is closed or opened
bool bridgeState = true;//true= closed, false = open

void setup() {
  //Setting pin modes for each device

  //Button Pins, set as input
  pinMode(openButton, INPUT);
  pinMode(closeButton, INPUT);

  //Motor and Warning Device Pins, set as output
  pinMode(verticalClockwise, OUTPUT);
  pinMode(veritcalCounterClockwise, OUTPUT);
  pinMode(horizontalClockwise, OUTPUT);
  pinMode(horizontalCounterClockwise, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
}


void loop() {
  //Main Program Loop
  int closeState = digitalRead(openButton); //sets variable based on whether the open button was pressed
  if (closeState == HIGH && bridgeState == true) {
      //if the open button was pressed run the function below
      opening();
  }
  int openState = digitalRead(closeButton);//sets variable based on whether the close button was pressed
  if (openState ==  HIGH && birdgeState == false) {
      //the close button was pressed run the function below
      closing();
  }
}

void opening() {
  //Function for gate opening: motors turn clockwise
  //sets polarity of vertical motor to clockwise
  analogWrite(verticalClockwise, motorPower);
  analogWrite(veritcalCounterClockwise, 0);
  analogWrite(horizontalClockwise, 0);
  analogWrite(horizontalCounterClockwise, 0);
  //motor ramp up loop, flash LED and speaker tone changes (runs for 3 iterations over 3 seconds)
  //speaker tones and LED flash ocillates every 500ms
  for (int i = 1; i <= 3; i++) {
    analogWrite(verticalClockwise, motorPower);
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    //ensures motorPower value doesnt increase past 255 (due to analogWrite parameters any value above 255 causes the function to calculate the value as  value%255)
    if (motorPower < 255) {
      delay(500);
      motorPower += 66;//motor power increment by 66
    }
    tone(speakerPin, 25);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  //extra Motor run time outside of ramp up (runs for integer iterations of seconnds over 4 seconds)
  //speaker tones and LED flash ocillates every 500ms
  for (int j = 1; j < floor((verticalTime / 1000)) - 4; j++) {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    delay(500);
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 25);
    delay(500);
  }
  delay(verticalTime - 4000 - floor(verticalTime / 1000) * 1000); //runs for any excess non-integer second times (ex: 400ms)

  motorPower = 55;//sets motor power back to default value
  //sets polarity of horizontal motor to counterclockwise
  analogWrite(verticalClockwise, 0);
  analogWrite(veritcalCounterClockwise, 0);
  analogWrite(horizontalClockwise, motorPower);
  analogWrite(horizontalCounterClockwise, 0);
  //motor ramp up loop, flash LED and speaker tone changes (runs for 4 iterations over 4 seconds)
  //speaker tones and LED flash ocillates every 500ms
  
  for (int i = 1; i <= 4; i++) {
    analogWrite(horizontalClockwise, motorPower);
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    //ensures motorPower value doesnt increase past 255
    if (motorPower < 255) {
      delay(500);
      motorPower += 50;//motor power increment by 50
    }
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 25);
    delay(500);
  }
  //extra Motor run time outside of ramp up (runs for integer iterations of seconnds over 4 seconds)
  //speaker tones and LED flash ocillates every 500ms
  for (int j = 1; j < floor(horizontalTime / 1000) - 4; j++) {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    delay(500);
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 25);
    delay(500);
  }
  delay(horizontalTime - 4000 - floor(horizontalTime / 1000) * 1000); //runs for any excess non-integer second times (ex: 400ms)
  motorPower = 55;
  analogWrite(horizontalClockwise, 0);//turns off motor
  pinMode(speakerPin, INPUT); //turns off speaker
  bridgeState = false;
}


void closing() {
  //Function for gate closing: motors turn counterclockwise
  //sets polarity of horizontal motor to counterclockwise
  analogWrite(verticalClockwise, 0);
  analogWrite(veritcalCounterClockwise, 0);
  analogWrite(horizontalClockwise, 0);
  analogWrite(horizontalCounterClockwise, motorPower);
  //motor ramp up loop, flash LED and speaker tone changes (runs for 4 iterations over 4 seconds)
  //speaker tones and LED flash ocillates every 500ms
  //ensures motorPower value doesnt increase past 255
  for (int i = 1; i <= 4; i++) {
    analogWrite(horizontalCounterClockwise, motorPower);
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    if (motorPower < 255) {
      delay(500);
      motorPower += 50;//motor power increase by 50
    }
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 25);
    delay(500);
  }
  //extra Motor run time outside of ramp up (runs for integer iterations of seconnds over 4 seconds)
  //speaker tones and LED flash ocillates every 500ms
  for (int j = 1; j < floor(horizontalTime / 1000) - 4; j++) {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    delay(500);
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 25);
    delay(500);
  }
  delay(horizontalTime - 4000 - floor(horizontalTime / 1000) * 1000); //runs for any excess non-integer second times (ex: 400ms)
  motorPower = 55;
  //sets polarity of vertical motor to counterclockwise
  analogWrite(verticalClockwise, 0);
  analogWrite(veritcalCounterClockwise, motorPower);
  analogWrite(horizontalClockwise, 0);
  analogWrite(horizontalCounterClockwise, 0);
  digitalWrite(speakerPin, HIGH);
  //motor ramp up loop, flash LED and speaker tone changes (runs for 3 iterations over 3 seconds)
  //speaker tones and LED flash ocillates every 500ms
  for (int i = 1; i <= 3; i++) {
    analogWrite(veritcalCounterClockwise, motorPower);
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    //ensures motorPower value doesnt increase past 255 
    if (motorPower < 255) {
      delay(500);
      motorPower += 66;//motor power increment by 66
    }
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 25);
    delay(500);
  }
  //extra Motor run time outside of ramp up (runs for integer iterations of seconnds over 4 seconds)
  //speaker tones and LED flash ocillates every 500ms
  for (int j = 1; j < floor(verticalTime / 1000) - 4; j++) {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 27);
    delay(500);
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 25);
    delay(500);
  }
  delay(verticalTime - 4000 - floor(verticalTime / 1000) * 1000); //runs for any excess non-integer second times (ex: 400ms)
  analogWrite(veritcalCounterClockwise, 0);//turns off motor
  pinMode(speakerPin, INPUT);//turns off speaker
  motorPower = 55;//sets motor power back to inital
  bridgeState = true;

}
