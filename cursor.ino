#define DS 4
#define ST 5
#define SH 6

#define ZUP 7
#define ZDOWN 8
#define XRIGHT 10
#define YUP 11
#define XLEFT 12
#define YDOWN 13

#define SPEED 1000
#define DSPEED 1

int fieldMap[1][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int posX = 0, posY = 0, posZ = 0;

int dPosX = 0, dPosY = 0, dPosZ = 0;

int movimiento = 0;

bool canPress[7] = {true, true, true, true, true, true};

void cleanPos(int index) {
  for (int i = 0; i < 16; i++) {
    fieldMap[index][i] = 0;
  }
}

void cleanLayer() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(i, HIGH);
  }
}

void shiftHelper(int index) {
  digitalWrite(ST, 0);
  for (int i = 15; i >= 0; i--) {
    digitalWrite(DS, fieldMap[index][i]);
    digitalWrite(SH, 0);
    digitalWrite(SH, 1);
  }
  digitalWrite(ST, 1);
}

void bottonHelper(int pin, int* move, int con) {
  bool isPressed = digitalRead(pin);
  if (isPressed && canPress[pin - 7]) {
    canPress[pin - 7] = false;
    if (movimiento == pin) {
      movimiento = 0;
    } else {
      movimiento = pin;
    }
  }
  if (!isPressed && !canPress[pin - 7]) {
    canPress[pin - 7] = true;
  }

  if (movimiento == pin) {
    *move += (con * DSPEED);
    *move=constrain(*move, 0, 3000);
  }
}

void move() {
  bottonHelper(ZUP, &dPosZ, -1);
  bottonHelper(ZDOWN, &dPosZ, 1);
  bottonHelper(XLEFT, &dPosX, 1);
  bottonHelper(YUP, &dPosY, -1);
  bottonHelper(XRIGHT, &dPosX, -1);
  bottonHelper(YDOWN, &dPosY, 1);
  cleanLayer();
  cleanPos(0);
  posX=(dPosX/SPEED);
  posY=(dPosY/SPEED);
  posZ=(dPosZ/SPEED);
  fieldMap[0][posX + (posY * 4)] = 1;
  digitalWrite(posZ, LOW);
  shiftHelper(0);
}

void setup() {
  for (int i = 0; i < 14; i++) {
    if (i < 7) {
      pinMode(i, OUTPUT);
    } else {
      pinMode(i, INPUT);
    }
  }
}

void loop() { move(); }