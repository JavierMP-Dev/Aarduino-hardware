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

// Variables para simular la velocidad
int velocidad = 0;  // Velocidad simulada (0 a 100)
int maxVelocidad = 100;

// Centro del tacómetro
const int centroX = 64; // Centro horizontal (mitad de la pantalla)
const int centroY = 48; // Centro vertical (casi al fondo)

// Radio del tacómetro
const int radioTacometro = 30;

// Angulo inicial y final del tacómetro (en grados)
const int anguloMin = 135;  // Mínimo (posicion 0 de velocidad)
const int anguloMax = 45;   // Máximo (posicion máxima de velocidad)

// Función para convertir grados a radianes
float gradosARadianes(float grados) {
  return grados * (PI / 180);
}

// Función para convertir velocidad en ángulo
int calcularAngulo(int velocidad, int maxVelocidad) {
  // Mapea la velocidad en el rango de ángulos del tacómetro
  return map(velocidad, 0, maxVelocidad, anguloMin, anguloMax);
}

// Función para dibujar el tacómetro
void dibujarTacometro(int velocidad) {
  // Limpiar la pantalla
  display.clearDisplay();

  // Dibujar el borde circular del tacómetro
  display.drawCircle(centroX, centroY, radioTacometro, SSD1306_WHITE);

  // Dibujar las marcas de la escala del tacómetro (cada 20 unidades de velocidad)
  for (int i = 0; i <= maxVelocidad; i += 20) {
    int angulo = calcularAngulo(i, maxVelocidad);
    int xInicio = centroX + cos(gradosARadianes(angulo)) * (radioTacometro - 5);
    int yInicio = centroY - sin(gradosARadianes(angulo)) * (radioTacometro - 5);
    int xFin = centroX + cos(gradosARadianes(angulo)) * radioTacometro;
    int yFin = centroY - sin(gradosARadianes(angulo)) * radioTacometro;
    display.drawLine(xInicio, yInicio, xFin, yFin, SSD1306_WHITE);
  }

  // Calcular el ángulo actual según la velocidad simulada
  int anguloActual = calcularAngulo(velocidad, maxVelocidad);

  // Calcular la posición del puntero del tacómetro
  int xPuntero = centroX + cos(gradosARadianes(anguloActual)) * (radioTacometro - 10);
  int yPuntero = centroY - sin(gradosARadianes(anguloActual)) * (radioTacometro - 10);

  // Dibujar el puntero del tacómetro
  display.drawLine(centroX, centroY, xPuntero, yPuntero, SSD1306_WHITE);

  // Mostrar la velocidad actual en el centro del tacómetro
  display.setCursor(centroX - 10, centroY - 5);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print(velocidad);
  display.println(" km/h");

  // Actualizar la pantalla
  display.display();
}

void setup() {
  // Iniciar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("No se encuentra la pantalla OLED"));
    while (1);
  }

  // Limpiar el buffer de la pantalla
  display.clearDisplay();
}

void loop() {
  // Simular un aumento de velocidad
  dibujarTacometro(velocidad);

  // Incrementar la velocidad simulada
  velocidad += 5;
  if (velocidad > maxVelocidad) {
    velocidad = 0; // Reiniciar la velocidad si supera el máximo
  }

  // Esperar 500ms antes de actualizar
  delay(500);
}
