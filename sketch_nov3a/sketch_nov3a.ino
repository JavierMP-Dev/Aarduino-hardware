#include <BleKeyboard.h>  // Asegúrate de tener instalada esta biblioteca

// Inicializamos el objeto BLE para el teclado
BleKeyboard bleKeyboard("ESP32 Arrow Keys", "Arduino", 100);

// Definimos los pines para cada tecla
#define UP_PIN 13
#define DOWN_PIN 12
#define LEFT_PIN 14
#define RIGHT_PIN 27

void setup() {
  Serial.begin(115200);
  
  // Configuramos los pines de las teclas como entrada
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  
  // Iniciamos el teclado BLE
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    // Detectamos el estado de cada pin y enviamos la tecla correspondiente
    if (digitalRead(UP_PIN) == LOW) {
      bleKeyboard.write(KEY_UP_ARROW);
      delay(100);  // Evitar múltiples lecturas con un retraso
    }
    if (digitalRead(DOWN_PIN) == LOW) {
      bleKeyboard.write(KEY_DOWN_ARROW);
      delay(100);
    }
    if (digitalRead(LEFT_PIN) == LOW) {
      bleKeyboard.write(KEY_LEFT_ARROW);
      delay(100);
    }
    if (digitalRead(RIGHT_PIN) == LOW) {
      bleKeyboard.write(KEY_RIGHT_ARROW);
      delay(100);
    }
  }
  
  delay(20);  // Pequeño retraso para evitar lectura excesiva
}
