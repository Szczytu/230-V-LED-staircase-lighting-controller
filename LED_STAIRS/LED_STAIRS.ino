const int dataPin = 2;   // D2 - A (Data)
const int clockPin = 3;  // D3 - SHIFT_CLK (Clock)
const int latchPin = 4;  // D4 - LATCH_CLK (Latch)
int photoresistor = A0;
int potenciometr = A1;
// Tablica przechowująca stan LED-ów (4 rejestry dla 26 diod)
byte leds[4] = {0};

unsigned long lastMovementTime = 0;  // Ostatni czas wykrycia ruchu
const unsigned long timeout = 2000; // 30 sekund
bool isExecuting = false;            // Czy sekwencja jest w trakcie
int activeSequence = -1;             // -1 = brak, 0 = góra, 1 = dół, 2 = taras, 3 = drzwi wejściowe

void setup() {
  Serial.begin(115200);
  // Czujniki ruchu
  pinMode(5, INPUT); // czujnik klatka góra
  pinMode(6, INPUT); // czujnik klatka dół
  pinMode(7, INPUT); // czujnik taras
  pinMode(8, INPUT); // czujnik dodatkowy drzwi wejściowe
  // Rejestr przesuwny
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  // Zgaszenie wszystkich diod
  clearAllLeds();
}

void loop() {
  photoresistor = analogRead(A0);
  photoresistor = map(photoresistor, 0 , 1023, 0 , 100);
  Serial.print("Poziom ciemnosci:");
  Serial.println(photoresistor);
  potenciometr = analogRead(A1);
  int sensitivity = map(potenciometr, 0, 1023, 0, 100); 
  Serial.print("ustawiony poziom czułości na światło:");
  Serial.println(sensitivity);
  if (photoresistor  < sensitivity) {
  // Sprawdź, który czujnik wykrył ruch
  bool upperTriggered = digitalRead(5) == HIGH;
  bool lowerTriggered = digitalRead(6) == HIGH;
  bool terraceTriggered = digitalRead(7) == HIGH;
  bool entrance_doorTriggered = digitalRead(8) == HIGH;
  if (!isExecuting) {
    // Zidentyfikuj pierwszy ruch i rozpocznij odpowiednią sekwencję
    if (upperTriggered) {
      Serial.println("Ruch na górze");
      isExecuting = true;
      activeSequence = 0;
      lastMovementTime = millis();  // Aktualizuj czas ostatniego ruchu
      TriggerON_Upper_staircase();
      isExecuting = false;
    } else if (lowerTriggered) {
      Serial.println("Ruch na dole");
      isExecuting = true;
      activeSequence = 1;
      lastMovementTime = millis();  // Aktualizuj czas ostatniego ruchu
      TriggerON_Lower_staircase();
      isExecuting = false;
    } else if (terraceTriggered) {
      Serial.println("Ruch na schodach na tarasie");
      isExecuting = true;
      activeSequence = 2;
      lastMovementTime = millis();  // Aktualizuj czas ostatniego ruchu
      TriggerON_Terrace();
      isExecuting = false;
    } else if (entrance_doorTriggered) {
      Serial.println("Ruch na drzwiach wejściowych");
      isExecuting = true;
      activeSequence = 3;
      lastMovementTime = millis();  // Aktualizuj czas ostatniego ruchu
      TriggerON_entrance_door();
      isExecuting = false;
    }

  }

  // Po zakończeniu sekwencji monitoruj czujniki
  // Po zakończeniu sekwencji monitoruj czujniki
  if (activeSequence != -1) {
    if (upperTriggered || lowerTriggered || terraceTriggered || entrance_doorTriggered) {
       lastMovementTime = millis(); // Aktualizacja czasu przy każdym ruchu
       Serial.println("Ruch wykryty - resetowanie odliczania czasu.");
  }

  // Oblicz czas pozostały do zgaszenia LED
  double elapsedTime = millis() - lastMovementTime;
  if (elapsedTime < timeout) {
    double remainingTime = timeout - elapsedTime;
    Serial.print("Pozostały czas do zgaśnięcia LED: ");
    Serial.print(remainingTime / 1000); // Wyświetl w sekundach
    Serial.println(" s");
  }
}

// Jeśli brak ruchu przez określony czas, zgaś wszystkie diody
if (millis() - lastMovementTime > timeout) {
  Serial.println("Brak ruchu - gaszę wszystkie diody.");
  clearAllLeds();
  activeSequence = -1; // Reset aktywnej sekwencji
}
  } else{
    Serial.println("Jasno na klatce");
  }
  
}

// Funkcja zapalania diod dla górnej klatki
void TriggerON_Upper_staircase() {
  for (int i = 0; i <= 8; i++) {
    setLed(i, HIGH);
    delay(500);
  }
  for (int x = 9, y = 18; x <= 17 || y <= 25; x++, y++) {
    setLed(x, HIGH);
    setLed(y, HIGH);
    delay(500);
  }
}

// Funkcja zapalania diod dla dolnej klatki
void TriggerON_Lower_staircase() {
  for (int i = 17; i >= 9; i--) {
    setLed(i, HIGH);
    Serial.print("Zapalam LED: ");
    Serial.println(i);
    delay(500);
  }
  for (int x = 8, y = 18; x >= 0 || y <= 25; x--, y++) {
    setLed(x, HIGH);
    setLed(y, HIGH);
    Serial.print("Zapalam LED: ");
    Serial.print(x);
    Serial.print(" i LED: ");
    Serial.println(y);
    delay(500);
  }
}


// Funkcja zapalania diod od tarasu
void TriggerON_Terrace() {
  for (int i = 25; i >= 18; i--) {
    setLed(i, HIGH);
    delay(500);
  }
  for (int x = 8, y = 9; x >= 0 || y <= 17; x--, y++) {
    setLed(x, HIGH);
    setLed(y, HIGH);
    delay(500);
  }

}

// Funkcja zapalania diod na schodach tylko na tarasie
void TriggerON_entrance_door() {
  for (int i = 25; i >= 18; i--) {
    setLed(i, HIGH);
    delay(500);
  }
}

// Funkcja obsługi diod (zapalenie lub zgaszenie)
void setLed(int led, bool state) {
  int reg = led / 8;       // Który rejestr (0, 1, 2, 3)
  int bit = led % 8;       // Który bit w rejestrze
  bitWrite(leds[reg], bit, state);
  updateShiftRegisters();
}

void updateShiftRegisters() {
  digitalWrite(latchPin, LOW);
  for (int i = 3; i >= 0; i--) {
    shiftOut(dataPin, clockPin, MSBFIRST, leds[i]);
  }
  digitalWrite(latchPin, HIGH);
}

// Zgaszenie wszystkich diod
void clearAllLeds() {
  for (int i = 0; i < 4; i++) {
    leds[i] = 0;
  }
  updateShiftRegisters();
}
