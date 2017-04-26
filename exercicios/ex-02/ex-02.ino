/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int button2Pin = 2;     // the number of the pushbutton pin
const int button3Pin = 3;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int button2State = 0;         // variable for reading the pushbutton status
int button3State = 0;         // variable for reading the pushbutton status
int estadoAtual = 1;
unsigned long momentoAnterior;
unsigned long deltaT = 100000;
unsigned long ultimoMomentoPressionado2 = 0, ultimoMomentoPressionado3 = 1000;


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button2Pin, INPUT);
    // initialize the pushbutton pin as an input:
  pinMode(button3Pin, INPUT);
  //Serial.begin(9600);
}

void loop() {
 
  // read the state of the pushbutton value:
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:

  unsigned long momentoAtual = millis();

  if (button2State == LOW) {
    deltaT += 1;
    ultimoMomentoPressionado2 = millis();
  }
  else if (button3State == LOW) {
    deltaT -= 1;
    ultimoMomentoPressionado3 = millis();
  } 
  
  long deltaTBtns = ultimoMomentoPressionado2 - ultimoMomentoPressionado3;
  deltaTBtns = (deltaTBtns > 0) ? deltaTBtns : -1 * deltaTBtns; 

  if (deltaTBtns < 500) {
    while(1);
  }
  
  if (momentoAtual >= momentoAnterior + deltaT/100) {
      //Serial.println(deltaT);
      momentoAnterior = momentoAtual;
      estadoAtual = !estadoAtual;
      digitalWrite(ledPin, estadoAtual);
  }
}
