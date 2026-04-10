#include <Adafruit_NeoPixel.h>
#include "include\snake.h"
#include "include\pathfinding.h"

#define PIN 14
#define BRIGHTNESS 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(SNAKE_MAX_SIZE, PIN, NEO_GRB + NEO_KHZ800);
Snake snake;
Direction direction = { 1, 0 };
Path path;

#ifdef CONFIG_IDF_TARGET_ESP32S3
  Path emptyPath;
  Snake virtualSnake;
  SemaphoreHandle_t pathReady;

  void pathfindTask(void *) {
    findPath(&snake, &path);
    xSemaphoreGive(pathReady);
    vTaskDelete(nullptr);
  }

  void triggerPathfind() {
    xTaskCreatePinnedToCore(
      pathfindTask, "pf",
      16384,
      nullptr, 2,
      nullptr, 0);
  }

#endif


void updateScreen(Snake *snake);

void setup() {
  Serial.begin(115200);
#ifdef CONFIG_IDF_TARGET_ESP32S3
  pathReady = xSemaphoreCreateBinary();
  initSnake(&virtualSnake);
  emptyPath.sizePath = 0;
  triggerPathfind();
#endif
  initSnake(&snake);

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.clear();
  strip.show();
}

void loop() {
  if (snake.dead) {
    Serial.print("Dead:");
    Serial.println(snake.score);
    delay(50);
    return;
  }

#ifdef CONFIG_IDF_TARGET_ESP32S3
  xSemaphoreTake(pathReady, portMAX_DELAY);
  const int pathLen = path.sizePath;

  if (pathLen == 0) {
    triggerPathfind();
    return;
  }

  static Direction localPath[SNAKE_MAX_SIZE];
  memcpy(localPath, path.arrPos, pathLen * sizeof(Direction));

  vSnake(&snake, &emptyPath, &virtualSnake);
  for (int i = 0; i < pathLen; i++) {
    run(&snake, localPath[i]);
    if (snake.dead) return;
  }

  triggerPathfind();

  for (int i = 0; i < pathLen; i++) {
    run(&virtualSnake, localPath[i]);
    if (i == pathLen - 1) {
      virtualSnake.foodPosition.x = snake.foodPosition.x;
      virtualSnake.foodPosition.y = snake.foodPosition.y;
    }
    updateScreen(&virtualSnake);
    if (virtualSnake.dead) break;
    delay(100);
  }
#else
  findPath(&snake, &path);
  for (int i = 0; i < path.sizePath; i++) {
    run(&snake, path.arrPos[i]);
    updateScreen(&snake);
    if (snake.dead) break;
    delay(100);
  }
#endif
  Serial.print("Score:");
  Serial.println(snake.score);
}

 
void updateScreen(Snake *snake ) {
  strip.clear();
  int index;
  float coef;
  int r = 0;
  int g = 0;
  int b = 0;


  for (int i = 0; i < snake->snakeSize; i++) {
    index = snake->snakePosition[i].x * snake->length + snake ->snakePosition[i].y;
    coef = (float)(snake ->snakeSize - 1 - i) / ((float)snake ->snakeSize - 1);
    g = (int)(255 * coef);
    b = 255 - g;
    strip.setPixelColor(index, r, g, b);
  }

  if (snake->foodOnBoard) {
    index = snake->foodPosition.x * snake->length + snake ->foodPosition.y;
    strip.setPixelColor(index, 255, 0, 0);
  }
  strip.show();
}