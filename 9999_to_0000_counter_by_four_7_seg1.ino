const byte segment_pins[8] = {9, 8, 7, 6, 5, 4, 3, 2};
const byte power_pins[4] = {10, 11, 12, 13};
const byte digit[10][8] = {
  //0顯示,1不顯示
  //a,b,c,d,e,f,g,dp
  {0, 0, 0, 0, 0, 0, 1, 1},//0
  {1, 0, 0, 1, 1, 1, 1, 1},//1
  {0, 0, 1, 0, 0, 1, 0, 1},//2
  {0, 0, 0, 0, 1, 1, 0, 1},//3
  {1, 0, 0, 1, 1, 0, 0, 1},//4
  {0, 1, 0, 0, 1, 0, 0, 1},//5
  {1, 1, 0, 0, 0, 0, 0, 1},//6
  {0, 0, 0, 1, 1, 1, 1, 1},//7
  {0, 0, 0, 0, 0, 0, 0, 1},//8
  {0, 0, 0, 1, 1, 0, 0, 1},//9
};
const byte scan[4][4] = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};

byte d[4];
unsigned long start_time, count;

void setup()
{
  for (byte i = 0; i < 8; i++) {
    pinMode(segment_pins[i], OUTPUT); 
  }
  for (byte i = 0; i < 4; i++) {
    pinMode(power_pins[i], OUTPUT);
  }
  start_time = millis() / 500;
  Serial.begin(9600);
}

void loop()
{
  count = millis() / 500 - start_time;//count為顯示的秒數  
  set_decimal(count);
  for(byte k = 0; k < 4; k++){

    for(byte j = 0; j < 4; j++) {
      digitalWrite(power_pins[j],LOW);
    }//預設每個7seg的power的初始值    

    for(byte j = 0; j < 8; j++){
      digitalWrite(segment_pins[j], digit[d[k]][j]);
    }//顯示對應數字

    for(byte j = 0; j < 4; j++) {
      digitalWrite(power_pins[j], scan[k][j]);
    }//每個7seg顯示各自的數字   
    delay(4);
  }
}

void set_decimal(int count){ 
  //count = millis() / 500 - start_time，count為顯示的秒數
  /*個位*/d[0] = 9-(count%10); 
  /*十位*/d[1] = 9-((count/10)%10); 
  /*百位*/d[2] = 9-((count/100)%10); 
  /*千位*/d[3] = 9-((count/1000)%10); 
}

