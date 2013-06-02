/*
Arduino Simon Says

Jenna deBoisblanc
jdeboi.com
3/19/2013
*/

int index = 0;
int top = 0;
int randomArray[100];
int oldState[4];
int ledPins[] = {2, 3, 4, 5};
int buttonPins[] = {8, 9, 10, 11};

void setup() {
  // set LED pins as output and button pins as input
  for(int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  Serial.begin(9600);
  // initialize the Simon Says array with random integers
  randomizeArray();
  // light up the first LED in the randomArray
  play(0);
  
}

void loop(){
  for(int i = 0; i < 4; i++){
    // light up LED if button it's currently being pressed
    setLEDState(i);
    // if button state changes (first pressed), 
    // check to see if the correct button was hit 
    if(checkButtonState(i)){
      if(i == randomArray[index]){
        if(index == top){
          index = 0;
          top++;
          play(top);
        }
        else {
          index++;
        }
      }
      else{
        endGame();
      }
    }
  }
}


//randomize all the elements of the randomArray
void randomizeArray() {
  for (int i = 0; i < 100; i++){
    randomArray[i] = (int) random(4);
  }
}

// plays LEDs of the randomArray from the first
// to the "top" LED
void play(int index){
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(500);
  for (int i = 0; i <= index; i++) {
    digitalWrite(ledPins[randomArray[i]], HIGH);
    delay(1000);
    digitalWrite(ledPins[randomArray[i]], LOW);
    delay(250);
  }
}

//returns true if the button's state changes
boolean checkButtonState(int num){
  int old = oldState[num];
  int state = digitalRead(buttonPins[num]);
  
  if(state == HIGH && old == LOW){
    oldState[num] = state;
    delay(150);
    return true;
  }
  else {
    oldState[num] = state;
    return false;
  }
}

// turn LED on/off if corresponding button is pressed
void setLEDState(int num){
  int state = digitalRead(buttonPins[num]);
  if(state == HIGH) {
    digitalWrite(ledPins[num], HIGH);
  }
  else {
    digitalWrite(ledPins[num], LOW);
  }
}

//blink LEDs for the total time passed as a parameter
void blinkLEDs(int duration){
  for(int i = 0; i < 4; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(duration/3);
  for(int i = 0; i < 4; i++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(duration/3);
  for(int i = 0; i < 4; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(duration/3);
  for(int i = 0; i < 4; i++){
    digitalWrite(ledPins[i], LOW);
  }
}

//a function that resets variables and plays an end sequence
void endGame(){
  Serial.println(top);
  Serial.println("GAME OVER");
  Serial.println("----------------------------");
  blinkLEDs(1000);
  index = 0;
  top = 0;
  randomizeArray();
  play(0);
}
