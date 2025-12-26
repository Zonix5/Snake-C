#include <Adafruit_NeoPixel.h>
#include <stdlib.h>
#include "snake.h"
#include "pathfinding.h"

#define PIN 14
#define NUM_LEDS SNAKE_MAX_SIZE
#define BRIGHTNESS 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, 48, NEO_GRB + NEO_KHZ800);
Snake snake;
Direction direction = { 1, 0 };

static Path path ;

void updateScreen();

void setup() {
  Serial.begin(115200);
  initSnake(&snake);

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.clear();
  strip.show();
  
  led.setBrightness(BRIGHTNESS);
  led.begin();
  led.clear();
  led.setPixelColor(0, 255, 255, 255);
  led.show();
  delay(1000);
  led.setPixelColor(0, 0, 0, 0);
  led.show();

}

void loop() {
  if (!snake.dead) {
      findPath(&snake, &path);
      for (int i = 0; i < path.sizePath; i++){
        run(&snake, path.arrPos[i]);
        updateScreen();
        if (snake.dead){
          break;
        }
        delay(50);
      }
      Serial.print("Score:");
      Serial.println(snake.score);
      // updateScreen();
    }
  else {
    Serial.print("Mort : ");
    Serial.println(snake.score);
  }
  delay(50); //100
}


void updateScreen() {
  strip.clear();
  int index;
  float coef;
  int r = 0;
  int g = 0;
  int b = 0;
  for (int i = 0; i < snake.snakeSize; i++) {
    index = snake.snakePosition[i].y * snake.width + snake.snakePosition[i].x;
    coef = (float)(snake.snakeSize - 1 - i) / ((float)snake.snakeSize - 1);
    g = (int)(255 * coef);
    b = 255 - (int)(255 * coef);
    strip.setPixelColor(index, r, g, b);
  }

  if (snake.foodOnBoard) {
    index = snake.foodPosition.y * snake.width + snake.foodPosition.x;
    strip.setPixelColor(index, 255, 0, 0);
  }
  strip.show();
}