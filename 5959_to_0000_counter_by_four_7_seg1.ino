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
byte btn,a,b,c;

void setup()
{
  pinMode(1, INPUT_PULLUP);
  for (byte i = 0; i < 8; i++) {
    pinMode(segment_pins[i], OUTPUT); 
  }
  for (byte i = 0; i < 4; i++) {
    pinMode(power_pins[i], OUTPUT);
  }
  start_time = millis() / 500;
}

void loop()
{
  btn = digitalRead(1);
  count = millis() / 500 - start_time;//count為顯示的秒數 
  if(btn==LOW)
  {
  set_decimal(count);
  }
  else
  {
    ATR_set_decimal(count);
  }
  for(byte k = 0; k < 4; k++){

    for(byte j = 0; j < 4; j++) {
      digitalWrite(power_pins[j],LOW);
    }//預設每個7seg的power的初始值    

    for(byte j = 0; j < 8; j++){
      digitalWrite(segment_pins[j], digit[d[k]][j]);
    }//顯示對應數字

    for(byte j = 0; j < 4; j++) {
      digitalWrite(power_pins[j], scan[k][j]);
      if(k==2)digitalWrite(segment_pins[7],LOW);
    }//每個7seg顯示各自的數字   
    delay(4);

  }
}

void set_decimal(int count){ 
  //count = millis() / 500 - start_time，count為顯示的秒數
  /*小數後二位*/d[0] =count%10;
  /*小數後一位*/d[1] =(count/10)%6;
  /*個位*/d[2] = (count/60)%10;
  /*十位*/d[3] = (count/1000)%6;
}

void ATR_set_decimal(int count){ 
  //count = millis() / 500 - start_time，count為顯示的秒數
  /*小數後二位*/d[0] =9-(count%10);
  /*小數後一位*/d[1] =5-((count/10)%6);
  /*個位*/d[2] = 9-((count/60)%10);
  /*十位*/d[3] = 5-((count/1000)%6);
}

