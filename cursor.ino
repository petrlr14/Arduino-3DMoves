#define DS 4
#define ST 5
#define SH 6

#define ZUP 7
#define ZDOWN 8
#define XRIGHT 10
#define YUP 11
#define XLEFT 12
#define YDOWN 13

int fieldMap[1][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int posX = 0, posY = 0, posZ = 0;

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

void bottonHelper(int pin, int* data, int dx) {
  bool isPressed = digitalRead(pin);
  if (isPressed && canPress[pin - 7]) {
    canPress[pin - 7] = false;
    *data+=dx;
    *data=constrain(*data, 0, 3);
  }
  if (!isPressed && !canPress[pin - 7]) {
    canPress[pin - 7] = true;
  }
}

void move() {
  bottonHelper(ZUP, posZ, -1);
  bottonHelper(ZDOWN, posZ, 1);
  bottonHelper(XLEFT, posX, -1);
  bottonHelper(YUP, posY, -1);
  bottonHelper(XRIGHT, posX, 1);
  bottonHelper(YDOWN, posY, 1);
  cleanLayer();
  cleanPos(0);
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

void loop() {
  move();
}