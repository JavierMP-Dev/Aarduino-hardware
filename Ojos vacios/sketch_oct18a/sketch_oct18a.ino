#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definimos el ancho y alto de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaramos la dirección I2C de la pantalla (usualmente 0x3C)
#define OLED_I2C_ADDRESS 0x3C

// Creamos una instancia de la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Coordenadas del centro de los ojos
const int ojoIzqX = 40;
const int ojoIzqY = 32;
const int ojoDerX = 88;
const int ojoDerY = 32;
const int radioOjo = 20;
const int radioPupila = 6;

// Estructura para almacenar posiciones de la pupila
struct PosicionPupila {
  int x;
  int y;
};

// Array de posiciones para las pupilas (arriba, derecha, abajo, izquierda)
PosicionPupila posiciones[] = {
  {0, -5},  // Arriba
  {5, 0},   // Derecha
  {0, 5},   // Abajo
  {-5, 0}   // Izquierda
};
const int totalPosiciones = 4;
int indicePosicion = 0;

void setup() {
  // Iniciar comunicación serial para depuración (opcional)
  Serial.begin(9600);

  // Iniciar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("No se encuentra la pantalla OLED"));
    while (1); // Detener el programa si no se encuentra la pantalla
  }

  // Limpiar el buffer de la pantalla
  display.clearDisplay();

  // Configurar texto (opcional)
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("18-10-2024");
  display.display();
  delay(2000); // Esperar 2 segundos antes de comenzar la animación
}

void dibujarOjos(int pupilaOffsetX, int pupilaOffsetY) {
  // Limpiar la pantalla
  display.clearDisplay();

  // Dibuja el texto
  display.setCursor(0, 0);
  display.println("18-10-2024");

  // Dibujar los ojos
  // Ojo Izquierdo
  display.drawCircle(ojoIzqX, ojoIzqY, radioOjo, SSD1306_WHITE);
  // Ojo Derecho
  display.drawCircle(ojoDerX, ojoDerY, radioOjo, SSD1306_WHITE);

  // Dibujar las pupilas con desplazamiento
  // Pupila Izquierda
  display.fillCircle(ojoIzqX + pupilaOffsetX, ojoIzqY + pupilaOffsetY, radioPupila, SSD1306_WHITE);
  // Pupila Derecha
  display.fillCircle(ojoDerX + pupilaOffsetX, ojoDerY + pupilaOffsetY, radioPupila, SSD1306_WHITE);

  // Actualizar la pantalla
  display.display();
}

void loop() {
  // Obtener la posición actual de la pupila
  int offsetX = posiciones[indicePosicion].x;
  int offsetY = posiciones[indicePosicion].y;

  // Dibujar los ojos con la posición actual de la pupila
  dibujarOjos(offsetX, offsetY);

  // Incrementar el índice de posición
  indicePosicion++;
  if (indicePosicion >= totalPosiciones) {
    indicePosicion = 0; // Reiniciar el índice si supera el total de posiciones
  }

  // Esperar 2 segundos antes de cambiar la posición
  delay(5000);
}

