 
#define lightFadePin 6   // Light dimming is connected to pin 6
#define IRledPin  13    // IR Blaster connected to digital pin 13
//MotorPinA controls the oven
#define motorPinA1 8    // Blue   - 28BYJ48 pin 1
#define motorPinA2 9    // Pink   - 28BYJ48 pin 2
#define motorPinA3 10    // Yellow - 28BYJ48 pin 3
#define motorPinA4 11    // Orange - 28BYJ48 pin 4

int motorSpeedA = 1200;
int motorStepRevA = 512; //steps per full rev
int lookupA[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
//How many steps stepperA has taken. for counting how much degrees to reset
int stepperA = 0;
int currentLightBrightness = 70;

// The setup() method runs once, when the sketch starts
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
  pinMode(motorPinA1, OUTPUT);
  pinMode(motorPinA2, OUTPUT);
  pinMode(motorPinA3, OUTPUT);
  pinMode(motorPinA4, OUTPUT);
  pinMode(lightFadePin, OUTPUT);
  Serial.begin(9600);
}

void loop()                     
{
  byte inputCommand;
  int stepperA = 0;
  if (Serial.available()) {
    Serial.println("Running Code");
    inputCommand = Serial.read();
    Serial.println(inputCommand);
    switch (inputCommand) {
      case 97:
        currentLightBrightness = 0;
        break;
        
      case 98:  
        currentLightBrightness = 28;
        break;
        
      case 99:
        currentLightBrightness = 57;
        break;
        
      case 100:
        currentLightBrightness = 85;
        break;
        
      case 101:
        currentLightBrightness = 113;
        break;
        
      case 102:
        currentLightBrightness = 142;
        break;
        
      case 103:
        currentLightBrightness = 170;
        break;
        
      case 104:
        currentLightBrightness = 198;
        break;
        
      case 105:
        currentLightBrightness = 227;
        break;
        
      case 106:
        currentLightBrightness = 255;
        break;
        
      case 67:
        Serial.write('Mute');
        SendMuteCode();
        break;
      case 117:
        Serial.write('0');
        SendOnCode();
        break;
      case 118:
        Serial.write('0');
        SendOnCode();
        break;
      case 119:
        Serial.write('1');
        SendChannelUpCode();
        break;
      case 120:
        Serial.write('2');
        SendChannelDownCode();
        break;
      case 121:
        Serial.write('3');
        SendVolUpCode();
        delay(300);
        SendVolUpCode();
        delay(250);
        SendVolUpCode();
        delay(250);
        SendVolUpCode();
        delay(250);
        SendVolUpCode();
        delay(250);
        SendVolUpCode();
        break;
      case 122:
        Serial.write('4');
        SendVolDownCode();
        delay(300);
        SendVolDownCode();
        delay(250);
        SendVolDownCode();
        delay(250);
        SendVolDownCode();
        delay(250);
        SendVolDownCode();
        delay(250);
        SendVolDownCode();
        break;
      case 123:
        Serial.write('5');
        SendChannel59Code();
        break;
      case 61:
        //Reset
        turnResetCode();
        break;
      case 62:
      //> Turn to 350
        turnResetCode();
        turnCode(224);
        break;
      case 63:
      //? Turn to 375
        turnResetCode();
        turnCode(256);
        break;
      case 64:
      //@ 400
        turnResetCode();
        turnCode(292);
        break;
      case 65:
       // A 425
        turnResetCode();
        turnCode(324);
        break;
      case 66:
       // B 450
        turnResetCode();
        turnCode(356);
        break;
    }
  }
  
  analogWrite(lightFadePin, currentLightBrightness);
}



// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait

  cli();  // this turns off any background interrupts

  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds

   // so 26 microseconds altogether
   microsecs -= 26;
 }
 
  sei();  // this turns them back on
}

void SendOnCode() {

// Turn On and Off
delayMicroseconds(64348);
pulseIR(8860);
delayMicroseconds(4320);
pulseIR(620);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(38920);
pulseIR(8820);
delayMicroseconds(2160);
pulseIR(600);
delayMicroseconds(28304);
pulseIR(8860);
delayMicroseconds(2120);
pulseIR(600);
delayMicroseconds(28304);
pulseIR(8860);
delayMicroseconds(2140);
pulseIR(600);
}
void SendChannelUpCode() {
//Change Channel Up
delayMicroseconds(23880);
pulseIR(8760);
delayMicroseconds(4400);
pulseIR(540);
delayMicroseconds(580);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(500);
pulseIR(540);
delayMicroseconds(560);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(500);
pulseIR(540);
delayMicroseconds(1640);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(560);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(540);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(540);
delayMicroseconds(1660);
pulseIR(600);
delayMicroseconds(480);
pulseIR(560);
delayMicroseconds(540);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(540);
delayMicroseconds(560);
pulseIR(600);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(480);
pulseIR(540);
delayMicroseconds(560);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(540);
delayMicroseconds(1660);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(540);
delayMicroseconds(1640);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(520);
delayMicroseconds(39000);
pulseIR(8800);
delayMicroseconds(2180);
pulseIR(640);
delayMicroseconds(28264);
pulseIR(8800);
delayMicroseconds(2200);
pulseIR(620);

}
void SendChannelDownCode() {

//Change Channel Down
delayMicroseconds(14308);
pulseIR(8820);
delayMicroseconds(4360);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(580);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(520);
delayMicroseconds(1660);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(560);
delayMicroseconds(1640);
pulseIR(600);
delayMicroseconds(480);
pulseIR(580);
delayMicroseconds(540);
pulseIR(580);
delayMicroseconds(1580);
pulseIR(580);
delayMicroseconds(540);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(480);
pulseIR(560);
delayMicroseconds(560);
pulseIR(580);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(540);
delayMicroseconds(560);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(38940);
pulseIR(8820);
delayMicroseconds(2180);
pulseIR(580);
delayMicroseconds(28324);
pulseIR(8780);
delayMicroseconds(2200);
pulseIR(580);

}

void SendVolUpCode() {
//Vol Up
delayMicroseconds(44280);
pulseIR(8860);
delayMicroseconds(4320);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(620);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(38920);
pulseIR(8840);
delayMicroseconds(2140);
pulseIR(600);
}
void SendVolDownCode() {

//Vol Down
delayMicroseconds(272);
pulseIR(8820);
delayMicroseconds(4360);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(500);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(520);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(580);
delayMicroseconds(520);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(580);
delayMicroseconds(540);
pulseIR(580);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(500);
pulseIR(560);
delayMicroseconds(520);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(560);
delayMicroseconds(540);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(38940);
pulseIR(8820);
delayMicroseconds(2180);
pulseIR(580);

}
void SendChannel59Code() {

//Channel 59
delayMicroseconds(28436);
pulseIR(8780);
delayMicroseconds(4380);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(480);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(500);
pulseIR(640);
delayMicroseconds(440);
pulseIR(640);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(680);
delayMicroseconds(1520);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(38920);
pulseIR(8800);
delayMicroseconds(2200);
pulseIR(600);
delayMicroseconds(28304);
pulseIR(8780);
delayMicroseconds(2200);
pulseIR(620);

delay(2);
delayMicroseconds(18604);
pulseIR(8780);
delayMicroseconds(4400);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(460);
pulseIR(680);
delayMicroseconds(420);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(680);
delayMicroseconds(1520);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(480);
pulseIR(640);
delayMicroseconds(440);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(540);
delayMicroseconds(39000);
pulseIR(8760);
delayMicroseconds(2220);
pulseIR(620);

delay(2);
delayMicroseconds(3500);
pulseIR(8840);
delayMicroseconds(4340);
pulseIR(640);
delayMicroseconds(460);
pulseIR(600);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(540);
delayMicroseconds(1640);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(520);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(520);
pulseIR(540);
delayMicroseconds(560);
pulseIR(560);
delayMicroseconds(520);
pulseIR(620);
delayMicroseconds(480);
pulseIR(540);
delayMicroseconds(1640);
pulseIR(620);
delayMicroseconds(480);
pulseIR(540);
delayMicroseconds(560);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(520);
delayMicroseconds(1660);
pulseIR(600);
delayMicroseconds(38940);
pulseIR(8820);
delayMicroseconds(2160);
pulseIR(600);
delayMicroseconds(28304);
pulseIR(8840);
delayMicroseconds(2140);
pulseIR(640);
}

void SendMuteCode() {
delayMicroseconds(5284);
pulseIR(8820);
delayMicroseconds(4360);
pulseIR(580);
delayMicroseconds(520);
pulseIR(560);
delayMicroseconds(540);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(520);
pulseIR(600);
delayMicroseconds(480);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(520);
pulseIR(600);
delayMicroseconds(480);
pulseIR(580);
delayMicroseconds(1620);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(560);
delayMicroseconds(520);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(560);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(1620);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(600);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(500);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(520);
pulseIR(560);
delayMicroseconds(520);
pulseIR(600);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(580);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(1600);
pulseIR(540);
delayMicroseconds(39000);
pulseIR(8820);
delayMicroseconds(2160);
pulseIR(600);
}

void turnResetCode() {
  while (stepperA > 0) {
    for (int i = 0; i < 8; i++) {
      setOutputA(i);
      delayMicroseconds(motorSpeedA);
    }
  stepperA--;
  }
}

void turnCode(int steps) {
  while (stepperA <= steps) {
    for (int i = 7; i >= 0; i--) {
      setOutputA(i);
      delayMicroseconds(motorSpeedA);
    }
  stepperA++;
  }
}

void setOutputA(int out) {
  digitalWrite(motorPinA1, bitRead(lookupA[out], 0));
  digitalWrite(motorPinA2, bitRead(lookupA[out], 1));
  digitalWrite(motorPinA3, bitRead(lookupA[out], 2));
  digitalWrite(motorPinA4, bitRead(lookupA[out], 3));
}
