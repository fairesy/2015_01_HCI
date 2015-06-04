//address setting!!
const int s0 = 2;
const int s1 = 3;
const int s2 = 4;
const int s3 = 5;

const int SIG_pin = 0;

const int ls0 = 6;
const int ls1 = 7;
const int ls2 = 8;
const int ls3 = 9;

const int SIZE = 16;
int pinStatus[SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  
  pinMode(ls0, OUTPUT); 
  pinMode(ls1, OUTPUT); 
  pinMode(ls2, OUTPUT); 
  pinMode(ls3, OUTPUT); 

  digitalWrite(ls0, LOW);
  digitalWrite(ls1, LOW);
  digitalWrite(ls2, LOW);
  digitalWrite(ls3, LOW);
  
  Serial.begin(9600);
}

void loop(){

  for(int i = 0; i < 16; i ++){
    if(readMux(i, SIG_pin) == 0 && pinStatus[i] == 0){
      Serial.println(i);
//      Serial.print("Switch ");Serial.print(i);Serial.println(" On!!");
      pinStatus[i] = 1;
      
      switch(i){
        case 0:
          readMuxLedValue(7);delay(60);
          readMuxLedValue(6);delay(60);
          readMuxLedValue(5);delay(60);
          readMuxLedValue(4);delay(60);
          readMuxLedValue(5);delay(60);
          readMuxLedValue(6);delay(60);
          readMuxLedValue(7);
          break;
        case 1:
          readMuxLedValue(6);delay(60);
          readMuxLedValue(3);delay(60);
          readMuxLedValue(9);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(6);
          break;
        case 2:
          readMuxLedValue(5);delay(60);
          readMuxLedValue(4);delay(60);
          readMuxLedValue(0);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(10);delay(60);
          readMuxLedValue(11);delay(60);
          readMuxLedValue(10);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(0);delay(60);
          readMuxLedValue(4);delay(60);
          readMuxLedValue(5);
          break;
        case 3:
          readMuxLedValue(4);delay(60);
          readMuxLedValue(0);delay(60);
          readMuxLedValue(11);delay(60);
          readMuxLedValue(15);delay(60);
          readMuxLedValue(4);
          break;
        case 4:
          readMuxLedValue(3);delay(60);
          readMuxLedValue(8);delay(60);
          readMuxLedValue(9);delay(60);
          readMuxLedValue(10);delay(60);
          readMuxLedValue(9);delay(60);
          readMuxLedValue(8);delay(60);
          readMuxLedValue(3);
          break;
        case 5:
          readMuxLedValue(6);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(10);delay(60);
          readMuxLedValue(14);delay(60);
          readMuxLedValue(15);delay(60);
          readMuxLedValue(14);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(6);
          break;
        case 6:
          readMuxLedValue(5);delay(60);
          readMuxLedValue(3);delay(60);
          readMuxLedValue(9);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(55);
          break;
        case 7:
          readMuxLedValue(7);delay(60);
          readMuxLedValue(5);delay(60);
          readMuxLedValue(6);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(2);delay(60);
          readMuxLedValue(3);delay(60);
          readMuxLedValue(7);
          break;
        case 8:
          readMuxLedValue(8);delay(60);
          readMuxLedValue(7);delay(60);
          readMuxLedValue(6);delay(60);
          readMuxLedValue(5);delay(60);
          readMuxLedValue(4);delay(60);
          readMuxLedValue(0);delay(60);
          readMuxLedValue(11);delay(60);
          readMuxLedValue(15);delay(60);
          readMuxLedValue(8);
          break;
        case 9:
          readMuxLedValue(9);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(4);delay(60);
          readMuxLedValue(0);delay(60);
          readMuxLedValue(11);delay(60);
          readMuxLedValue(10);delay(60);
          readMuxLedValue(9);
          break;
        case 10:
          readMuxLedValue(7);delay(60);
          readMuxLedValue(6);delay(60);
          readMuxLedValue(5);delay(60);
          readMuxLedValue(4);delay(60);
          readMuxLedValue(0);delay(60);
          readMuxLedValue(1);delay(60);
          readMuxLedValue(10);
          break;
        case 11:
          readMuxLedValue(11);delay(60);
          readMuxLedValue(10);delay(60);
          readMuxLedValue(14);delay(60);
          readMuxLedValue(15);
          break;
        case 1
          break;
        case 13:
          readMuxLedValue(13);delay(60);
          readMuxLedValue(10);delay(60);
          readMuxLedValue(0);delay(60);
          readMuxLedValue(13);
          break;
        case 14:
          readMuxLedValue(14);delay(60);
          readMuxLedValue(9);delay(60);
          readMuxLedValue(3);delay(60);
          readMuxLedValue(9);delay(60);
          readMuxLedValue(14);
          break;
        case 15:
          readMuxLedValue(15);delay(60);
          readMuxLedValue(14);delay(60);
          readMuxLedValue(13);delay(60);
          readMuxLedValue(15);
          break;
      }
      
//      Serial.println(readMuxLedValue(i, ls0, ls1, ls2, ls3));
      
    }else if(readMux(i, SIG_pin) != 0){
      pinStatus[i] = 0;
    }
  }
}

int readMuxLedValue(int channel)
{
  digitalWrite(ls0, bitRead(channel, 0));
  digitalWrite(ls1, bitRead(channel, 1));
  digitalWrite(ls2, bitRead(channel, 2));
  digitalWrite(ls3, bitRead(channel, 3));
  
  int sigValue = analogRead(0);

  return sigValue;
}

int readMux(int channel, int sigPin){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  int val = analogRead(sigPin);
  return val;
}
