#include <M5Stack.h>
#include <FastLED.h>

// Angleセンサーのピン
static const int ANGLE_SENSOR_PIN = 36;
// NeoPlixelのピン
static const int NEO_PIXEL_PIN = 21;
// NeoPixelの数
static const int NUM_PIXELS = 29;

static uint8_t r = 0;
static uint8_t g = 0;
static uint8_t b = 0;

static CRGB pixels[NUM_PIXELS];

static uint8_t convertToUint8(uint16_t value) {
  if (value < 0) {
    return 0;
  }
  if (value > 255) {
    return 255;
  }
  return (u_char)value;
}

static void showColorToLcd(uint8_t r, uint8_t g, uint8_t b) {
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(WHITE ,BLACK);
  M5.Lcd.setCursor(30, 80);
  char text[4] = {'\0'};
  snprintf(text, sizeof(text), "%03d", r);
  M5.Lcd.print(text);

  M5.Lcd.setCursor(126, 80);
  snprintf(text, sizeof(text), "%03d", g);
  M5.Lcd.print(text);

  M5.Lcd.setCursor(222, 80);
  snprintf(text, sizeof(text), "%03d", b);
  M5.Lcd.print(text);
}

void setup() {
  // M5Stackの初期化
  M5.begin();

  // NeoPixelの初期化
  FastLED.addLeds<NEOPIXEL, NEO_PIXEL_PIN>(pixels, NUM_PIXELS);

  // ノイズで音が鳴るのでスピーカーをオフにする
  dacWrite(25, 0);

  // Angleセンサーを読み込むモードにする。
  // AngleセンサーはPORT.Bにつなぐ。
  pinMode(ANGLE_SENSOR_PIN, INPUT);

  // M5StackのLCD(液晶ディスプレイ)を黒で塗りつぶす
  M5.Lcd.fillScreen(BLACK);

  // M5StackのLCDで表示する文字の大きさを設定
  M5.Lcd.setTextSize(4);

  M5.Lcd.setTextColor(RED ,BLACK);
  M5.Lcd.setCursor(60, 200);
  M5.Lcd.print("R");

  M5.Lcd.setTextColor(GREEN ,BLACK);
  M5.Lcd.setCursor(156, 200);
  M5.Lcd.print("G");

  M5.Lcd.setTextColor(BLUE ,BLACK);
  M5.Lcd.setCursor(252, 200);
  M5.Lcd.print("B");

  showColorToLcd(r, g, b);

  FastLED.show();
}

int mode = 0;

void loop() {
  // M5StackのボタンA/B/Cの読み取り状態を更新
  M5.update();

  uint8_t newR = r;
  uint8_t newG = g;
  uint8_t newB = b;

  if (M5.BtnA.isPressed()) {
    uint16_t v = analogRead(ANGLE_SENSOR_PIN);
    newR = convertToUint8(round(v * ((float)255 / 4096)));
  }
  if (M5.BtnB.isPressed()) {
    uint16_t v = analogRead(ANGLE_SENSOR_PIN);
    newG = convertToUint8(round(v * ((float)255 / 4096)));
  }
  if (M5.BtnC.isPressed()) {
    uint16_t v = analogRead(ANGLE_SENSOR_PIN);
    newB = convertToUint8(round(v * ((float)255 / 4096)));
  }

  if (r != newR || g != newG || b != newB) {
    r = newR;
    g = newG;
    b = newB;

    showColorToLcd(r, g, b);

    for (int i = 0; i < NUM_PIXELS; ++i) {
      pixels[i] = CRGB().setRGB(r, g, b);
    }
    FastLED.show();
  }

  // 100ミリ秒停止します
  delay(100);
}