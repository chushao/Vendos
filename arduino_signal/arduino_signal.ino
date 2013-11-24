 
int IRledPin =  13;    // LED connected to digital pin 13

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      

  Serial.begin(9600);
}

void loop()                     
{
  byte inputCommand;
  
  if (Serial.available()) {
    Serial.println("Sending IR signal");
    inputCommand = Serial.read();
    Serial.println(inputCommand);
    switch (inputCommand) {
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
      break;
      case 122:
      Serial.write('4');
      SendVolDownCode();
      break;
      case 123:
      Serial.write('5');
      SendChannel59Code();
      break;
    }

 // delay(5000);  // wait twenty seconds (10 seconds * 1000 milliseconds)
}
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
delayMicroseconds(34632);
pulseIR(8840);
delayMicroseconds(4340);
pulseIR(640);
delayMicroseconds(460);
pulseIR(600);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(500);
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
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(440);
pulseIR(620);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(660);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(640);
delayMicroseconds(38900);
pulseIR(8840);
delayMicroseconds(2140);
pulseIR(620);
delayMicroseconds(28284);
pulseIR(8840);
delayMicroseconds(2160);
pulseIR(600);

}
void SendChannelDownCode() {

//Change Channel Down
delayMicroseconds(47428);
pulseIR(8840);
delayMicroseconds(4340);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(500);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(660);
delayMicroseconds(420);
pulseIR(640);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(640);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(660);
delayMicroseconds(420);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(660);
delayMicroseconds(38880);
pulseIR(8820);
delayMicroseconds(2180);
pulseIR(600);

}

void SendVolUpCode() {

//Vol Up
delayMicroseconds(41216);
pulseIR(8840);
delayMicroseconds(4340);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(460);
pulseIR(600);
delayMicroseconds(500);
pulseIR(640);
delayMicroseconds(440);
pulseIR(640);
delayMicroseconds(460);
pulseIR(600);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(500);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(480);
pulseIR(640);
delayMicroseconds(440);
pulseIR(620);
delayMicroseconds(480);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(440);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(38920);
pulseIR(8800);
delayMicroseconds(2160);
pulseIR(640);

}
void SendVolDownCode() {

//Vol Down
delayMicroseconds(62900);
pulseIR(8820);
delayMicroseconds(4360);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(480);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(460);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(480);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1560);
pulseIR(640);
delayMicroseconds(1540);
pulseIR(640);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(480);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(460);
pulseIR(660);
delayMicroseconds(440);
pulseIR(600);
delayMicroseconds(500);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(460);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(1580);
pulseIR(600);
delayMicroseconds(1580);
pulseIR(640);
delayMicroseconds(1560);
pulseIR(620);
delayMicroseconds(38920);
pulseIR(8800);
delayMicroseconds(2160);
pulseIR(640);
delayMicroseconds(28284);
pulseIR(8840);
delayMicroseconds(2140);
pulseIR(640);

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

pause(2);
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

pause(2);
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