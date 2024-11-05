#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Número de copos de nieve
#define NUM_SNOWFLAKES 20

// Posiciones de los copos de nieve
int snowflakeX[NUM_SNOWFLAKES];
int snowflakeY[NUM_SNOWFLAKES];

void setup() {
  // Iniciar la pantalla
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();

  // Inicializar posiciones de copos de nieve
  for (int i = 0; i < NUM_SNOWFLAKES; i++) {
    snowflakeX[i] = random(0, SCREEN_WIDTH);
    snowflakeY[i] = random(0, SCREEN_HEIGHT);
  }

  drawChristmasTree();  // Dibujar el árbol
}

void loop() {
  display.clearDisplay();
  drawChristmasTree();  // Dibujar el árbol en cada iteración
  
  // Dibujar y mover los copos de nieve
  for (int i = 0; i < NUM_SNOWFLAKES; i++) {
    display.drawPixel(snowflakeX[i], snowflakeY[i], SSD1306_WHITE);
    snowflakeY[i]++;  // Mover el copo hacia abajo

    // Si el copo llega al fondo de la pantalla, reiniciar en la parte superior
    if (snowflakeY[i] >= SCREEN_HEIGHT) {
      snowflakeY[i] = 0;
      snowflakeX[i] = random(0, SCREEN_WIDTH);  // Reiniciar con una posición aleatoria
    }
  }

  display.display();
  delay(100);  // Ajustar la velocidad de la nieve
}

void drawChristmasTree() {
  // Dibujar las secciones del árbol
  display.fillTriangle(64, 10, 54, 30, 74, 30, SSD1306_WHITE); // Punta
  display.fillTriangle(64, 20, 50, 40, 78, 40, SSD1306_WHITE);
  display.fillTriangle(64, 30, 46, 50, 82, 50, SSD1306_WHITE);
  
  // Dibujar el tronco
  display.fillRect(59, 50, 10, 10, SSD1306_WHITE);
}

