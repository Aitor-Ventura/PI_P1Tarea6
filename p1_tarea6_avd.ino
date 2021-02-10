/* Contador de dos digitos y sincronizacion por interrupciones
 *  Utilizamos las interrupciones como tecnica de sincronizacion
 */
byte Uno     = 0x06;
byte Dos     = 0x5B;
byte Tres    = 0x4F;
byte Cuatro  = 0x66;
byte Cinco   = 0x6D;
byte Seis    = 0x7D;
byte Siete   = 0x07;
byte Ocho    = 0x7F;
byte Nueve   = 0x67;
byte Cero    = 0x3F;
byte Unidades = 0;
byte Decenas = 0;
unsigned long time;

void setup() {
  time = millis();
  // Que empiecen con un pullup
  pinMode(21, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  noInterrupts();
  attachInterrupt(digitalPinToInterrupt(21), pup, LOW);
  attachInterrupt(digitalPinToInterrupt(20), pdown, FALLING);
  attachInterrupt(digitalPinToInterrupt(19), pcenter, FALLING);
  interrupts();
  // Monitor serie
  Serial.begin(9600);
  DDRA = B11111111;
  PORTC = 0xFF;
  DDRL = 0x0F;
  DDRC = 0xFE;
}

void digit(byte dig) {
  switch (dig) {
    case 0: {
        PORTA = Cero;
        break;
      }
    case 1: {
        PORTA = Uno;
        break;
      }
    case 2: {
        PORTA = Dos;
        break;
      }
    case 3: {
        PORTA = Tres;
        break;
      }
    case 4: {
        PORTA = Cuatro;
        break;
      }
    case 5: {
        PORTA = Cinco;
        break;
      }
    case 6: {
        PORTA = Seis;
        break;
      }
    case 7: {
        PORTA = Siete;
        break;
      }
    case 8: {
        PORTA = Ocho;
        break;
      }
    case 9: {
        PORTA = Nueve;
        break;
      }
  }
}

// Pone las unidades a 0
int pcenter() {
  if (time + 200 < millis()) {
    time = millis();
    Unidades = 0;
    Decenas = 0;
  }
}

// Aumenta los digitos en una unidad
int pup() {
  if (time + 200 < millis()) {
    time = millis();
    if (Unidades == 9) {
      Unidades = 0;
      if (Decenas == 9) {
        Decenas = 0;
      } else {
        Decenas++;
      }
    } else {
      Unidades++;
    }
  }
}

// Decrementa los digitos en una unidad
int pdown() {
  if (time + 200 < millis()) {
    time = millis();
    if (Unidades == 0) {
      Unidades = 9;
      if (Decenas == 0) {
        Decenas = 9;
      } else {
        Decenas--;
      }
    } else {
      Unidades--;
    }
  }
}

void loop() {
  // Barrido continuo
  DDRL = 0b1;
  digit(Unidades);
  delay(5);
  DDRL = 0b10;
  digit(Decenas);
  delay(5);
}
