//B -> Pins 8 to 13 used as output to light
//D -> pins 0 to 7 used as input from buttons

//Configure
#define redButton 8
#define redLED 3
#define blueButton 9
#define blueLED 5
#define greenButton 10
#define greenLED 7
#define yellowButton 11

#define startLevel 3
#define maxLevel 20

char colors [4] = {'R', 'G', 'B', 'Y'};
//colors[0] = 'R';
//colors[1] = 'G';
//colors[2] = 'B';
//colors[3] = 'Y';

int level = startLevel;
char sequence [maxLevel];
char playerSeq [maxLevel];

void buttonWait(int pinButton)
{
  int buttonState = 0;
  while (buttonState == LOW)
  {
    buttonState = digitalRead(pinButton);
  }
}

char getNextInput()
{
  int num = 0x00;
  while ((num & 0xF) == 0x00)
  {
    num = ~(PINB & 0xF);
  }
  if ((num & 0xF) == 0x01)
  {
    delay(250);
    return 'R';
  }
  else if ((num & 0xF) == 0x02)
  {
    delay(250);
    return 'G';
  }
  else if ((num & 0xF) == 0x04)
  {
    delay(250);
    return 'B';
  }
  else if ((num & 0xF) == 0x08)
  {
    delay(250);
    return 'Y';
  }
  else
  {
    Serial.println("ERROR");
  } 
}

void showSequence()
{
  int i = 0;
  while (sequence[i] != NULL)
  {
    //Serial.print(sequence[i]);
    if (sequence[i] == 'R')
    {
      Serial.print('R');
      PORTD = PORTD ^ 0b00001000;
      delay(250);
      PORTD = PORTD ^ 0b00001000;
      delay(250);
    }
    else if (sequence[i] == 'B')
    {
      Serial.print('B');
      PORTD = PORTD ^ 0b00100000;
      delay(250);
      PORTD = PORTD ^ 0b00100000;
      delay(250);
    }
    else if (sequence[i] == 'G')
    {
      Serial.print('G');
      PORTD = PORTD ^ 0b10000000;
      delay(250);
      PORTD = PORTD ^ 0b10000000;
      delay(250);
    }
    else if (sequence[i] == 'Y')
    {
      Serial.print('Y');
      PORTD = PORTD ^ 0b00101000;
      delay(250);
      PORTD = PORTD ^ 0b00101000;
      delay(250);
    }
    i++;
  }
  Serial.println();
}

char genNextColor()
{
  return colors[random(0,4)];
}

void initGame() {
  for (int i = 0; i < startLevel; i++)
  {
    sequence[i] = genNextColor();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initGame();

  //DDRB = DDRB | B00000111; //Setting pins to read
  DDRD = DDRD | B10101000; //Setting pins to read
  pinMode(redButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(yellowButton, INPUT);
  digitalWrite(redButton, HIGH);
  digitalWrite(greenButton, HIGH);
  digitalWrite(blueButton, HIGH);
  digitalWrite(yellowButton, HIGH);
  //Serial.println(genNextColor()); 
}

int tracker = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (level > maxLevel)
  {
    PORTD = PORTD ^ 0b00001000; //Flash all three colors
    while (true) //Game over
      {
        PORTD = PORTD ^ 0b00101000; //Flash all three colors
        delay(500);
        PORTD = PORTD ^ 0b10100000; //Flash all three colors
        delay(500);
        PORTD = PORTD ^ 0b10001000; //Flash all three colors
        delay(500);
      }
  }
  showSequence();
  for (tracker = 0; tracker < level; tracker++)
  {
    if (getNextInput() != sequence[tracker])
    {
      Serial.println("You lose!");
      while (true) //Game over
      {
        PORTD = PORTD ^ 0b10101000; //Flash all three colors
        delay(1000);
      }
    }
  }
  level++;
  sequence[level - 1] = genNextColor();
}
