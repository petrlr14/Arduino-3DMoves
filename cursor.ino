#define DS 4
#define ST 5
#define SH 6

#define SPEED 1000
#define DSPEED 1

int fieldMap[1][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int posX = 0, posY = 0, posZ = 0;

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

void sumPos(int *pos) {
  int rand = random(0, 2);
  switch (rand) {
    case 0:
      *pos = *pos + 1;
      break;
    case 1:
      *pos = *pos - 1;
      break;
  }
  *pos = constrain(*pos, 0, 3);
}

void move() {
  cleanLayer();
  cleanPos(0);
  int rand = random(0, 3);
  switch (rand) {
    case 0:
      sumPos(&posX);
      break;
    case 1:
      sumPos(&posY);
      break;
    case 2:
      sumPos(&posZ);
      break;
  }
  fieldMap[0][posX + (posY * 4)] = 1;
  digitalWrite(posZ, LOW);
  shiftHelper(0);
  delay(500);
}

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(i, OUTPUT);
  }
  randomSeed(analogRead(A0));
}

void loop() { move(); }