#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <MQ135.h>


#define LED_PIN_1 3  // 第一个灯串的引脚
#define LED_PIN_2 4  // 第二个灯串的引脚
#define LED_PIN_3 5  // 第三个灯串的引脚
#define LED_COUNT 3  // 每个灯串的LED数量

#define DHTPIN 12

#define TEMPPIN 9
#define HUMIPIN 10
#define CO2PIN 11

#define DHTTYPE DHT22
#define PIN_MQ135 A2



float save = 0;
// 创建三个NeoPixel对象，分别代表三个灯串
Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN_3, NEO_GRB + NEO_KHZ800);

DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135_sensor(PIN_MQ135);

Servo servo_temp;
Servo servo_humi;
Servo servo_co2;

float pos_t;
float pos_h;
float pos_c;

void setup() {
  Serial.begin(9600);
  dht.begin();

  servo_temp.attach(TEMPPIN, 500, 1800);
  servo_humi.attach(HUMIPIN, 500, 1800);
  servo_co2.attach(CO2PIN, 500, 1800);

  strip1.begin();
  strip2.begin();
  strip3.begin();

  Serial.println("First zero");
  RGB_control(0, 0, 0);
  Servo_control(0, 0, 0);

  pos_t = 0;
  pos_h = 0;
  pos_c = 0;

  for(int i = 0; i <= 100; i++){
    // Serial.println(i);
    RGB_control(i * 0.1 + 20, i * 0.5 + 30, i * 6.5 + 350);
    Servo_control(i * 0.1 + 20, i * 0.5 +30, i * 6.5 + 350);
    delay(30);
  }
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float ppm = mq135_sensor.getCorrectedPPM(t, h);

  // Serial.println(dht.readTemperature());
  // Serial.println(dht.readHumidity());
  // Serial.println(mq135_sensor.getRZero());

  RGB_control(t, h, ppm);
  Servo_control(t, h, ppm);

  delay(30000);
}

void RGB_control(float t, float h, float ppm){
    // 设置第一个灯串的颜色
  if(t > 30){
    strip1.setPixelColor(0, 0, 255, 0);
    strip1.setPixelColor(1, 0, 255, 0);
    strip1.setPixelColor(2, 0, 255, 0);
    strip1.show();
  }else if(t < 20){
    strip1.setPixelColor(0, 50, 255, 0);
    strip1.setPixelColor(1, 50, 255, 0);
    strip1.setPixelColor(2, 50, 255, 0);
    strip1.show();
  }else{
    int temp_g = 0;
    temp_g = (30 - t) * 50 / 10;
    strip1.setPixelColor(0, temp_g, 255, 0);
    strip1.setPixelColor(1, temp_g, 255, 0);
    strip1.setPixelColor(2, temp_g, 255, 0);
    strip1.show();
  }

  // 设置第二个灯串的颜色
  if(ppm >= 1000){
    strip2.setPixelColor(0, 255, 0, 0); 
    strip2.setPixelColor(1, 255, 0, 0); 
    strip2.setPixelColor(2, 255, 0, 0); 
    strip2.show();
  }else if(ppm <= 350){
    strip2.setPixelColor(0, 255, 0, 50);
    strip2.setPixelColor(1, 255, 0, 50);
    strip2.setPixelColor(2, 255, 0, 50);
    strip2.show();
  }else{
    int co2_b = 0;
    co2_b = (ppm - 350) / 650 * 50;
    strip2.setPixelColor(0, 255, 0, co2_b);
    strip2.setPixelColor(1, 255, 0, co2_b);
    strip2.setPixelColor(2, 255, 0, co2_b);
    strip2.show();
  }

  // 设置第三个灯串的颜色
  if(h > 80){
    strip3.setPixelColor(0, 0, 0, 254);
    strip3.setPixelColor(1, 0, 0, 254);
    strip3.setPixelColor(2, 0, 0, 254);
    strip3.show();
  }else if(h < 30){
    strip3.setPixelColor(0, 80, 80, 255);
    strip3.setPixelColor(1, 80, 80, 255);
    strip3.setPixelColor(2, 80, 80, 255);
    strip3.show();
  }else{
    int humi_g = 0;
    int humi_r = 0;
    humi_g = (80 - h) * 80 / 50;
    humi_r = (80 - h) * 80 / 50;
    strip3.setPixelColor(0, humi_g, humi_r, 255);
    strip3.setPixelColor(1, humi_g, humi_r, 255);
    strip3.setPixelColor(2, humi_g, humi_r, 255);
    strip3.show();
  }
}

void Servo_control(float t, float h, float ppm){
  if(t >= 30){
    float temp = 200;
    smoother(servo_temp, temp, &pos_t);
  }else if(t <= 20){
    float temp = 0;
    smoother(servo_temp, temp, &pos_t);
  }else{
    float temp = (t - 20) / 10 * 200;
    smoother(servo_temp, temp, &pos_t);
  }

  smoother(servo_humi, h * 2, &pos_h);

  if(ppm >= 1000){
    float temp = 200;
    smoother(servo_co2, temp, &pos_c);
  }else if(ppm <= 350){
    float temp = 0;
    smoother(servo_co2, temp, &pos_c);
  }else{
    float temp = (ppm - 350) / 650 * 200;
    smoother(servo_co2, temp, &pos_c);
  }
}

void smoother(Servo servo, float des, float* prev){
  if(*prev > des){
      for(*prev; *prev > des; *prev = (*prev * 100 - 1) / 100){
        servo.write(*prev);
        // delay(1);
      }
    }else if(*prev < des){
      for(*prev; *prev < des; *prev = (*prev * 100 + 1) / 100){
        servo.write(*prev);
        // delay(1);
      }
    }
}
