#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <MQ135.h>


#define LED_PIN_1 3  // Pin of first LED
#define LED_PIN_2 4  // Pin of second LED
#define LED_PIN_3 5  // Pin of third LED
#define LED_COUNT 3  // number of LED in every device

#define DHTPIN 12 // Pin of DHT22 sensor

#define TEMPPIN 9 // Pin of temperature servo
#define HUMIPIN 10  // Pin of humidity servo 
#define CO2PIN 11 // Pin of CO2 servo

#define DHTTYPE DHT22 // type of DHT
#define PIN_MQ135 A2  // Pin of CO2 sensor

// Setup the Adafruit NeoPixel library with the LED count, pin, and color order
Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN_3, NEO_GRB + NEO_KHZ800);

// Initialize sersons and servos
DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135_sensor(PIN_MQ135);
Servo servo_temp;
Servo servo_humi;
Servo servo_co2;

// Save postion of servos in global variables
float pos_t;
float pos_h;
float pos_c;

void setup() {
  // Initialize the serial port
  Serial.begin(9600);
  // Initialize the DHT sensor
  dht.begin();

  // Attach the servos to the correct pins and PWM range
  servo_temp.attach(TEMPPIN, 500, 1800);
  servo_humi.attach(HUMIPIN, 500, 1800);
  servo_co2.attach(CO2PIN, 500, 1800);

  // Initialize the Adafruit NeoPixel library
  strip1.begin();
  strip2.begin();
  strip3.begin();

  // Set to zero
  Serial.println("Zero!");
  RGB_control(0, 0, 0);
  servo_temp.write(0);
  servo_humi.write(0);
  servo_co2.write(0);

  // Set the initial values for the servos
  pos_t = 0;
  pos_h = 0;
  pos_c = 0;

  // boot up animation and test
  for(int i = 0; i <= 100; i++){
    RGB_control(i * 0.1 + 20, i * 0.5 + 30, i * 6.5 + 350);
    Servo_control(i * 0.1 + 20, i * 0.5 + 30, i * 6.5 + 350);
    delay(30);
  }
  // Serial.println("over");
  // delay(10000);
}

void loop() {
  // Read the temperature, humidity, and ppm from sensors
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float ppm = mq135_sensor.getCorrectedPPM(t, h);

  // Serial.println(dht.readTemperature());
  // Serial.println(dht.readHumidity());
  // Serial.println(mq135_sensor.getRZero());

  // Set the RGB strip and servo values
  RGB_control(t, h, ppm);
  Servo_control(t, h, ppm);

  // loop per 30 seconds
  delay(10000);
}

/// @brief control RGB strip based on data
/// @param t temperature
/// @param h humidity
/// @param ppm co2 value(ppm)
void RGB_control(float t, float h, float ppm){
  // Set the RGB strip values based on the temperature
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

  // Set the RGB strip values based on the ppm
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
    strip2.setPixelColor(0, 255, 0, 50 - co2_b);
    strip2.setPixelColor(1, 255, 0, 50 - co2_b);
    strip2.setPixelColor(2, 255, 0, 50 - co2_b);
    strip2.show();
  }
  
  // Set the RGB strip values based on the humidity
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

/// @brief control servo position based on data
/// @param t temperature
/// @param h humidity
/// @param ppm co2 value(ppm)
void Servo_control(float t, float h, float ppm){
  // Set the servo values based on the temperature
  if(t >= 30){
    float temp = 180;
    smoother(servo_temp, temp, &pos_t);
  }else if(t <= 20){
    float temp = 0;
    smoother(servo_temp, temp, &pos_t);
  }else{
    float temp = (t - 20) / 10 * 180;
    smoother(servo_temp, temp, &pos_t);
  }

  // Set the servo values based on the humidity
  smoother(servo_humi, h * 1.8, &pos_h);

  // Set the servo values based on the ppm
  if(ppm >= 1000){
    float temp = 180;
    smoother(servo_co2, temp, &pos_c);
  }else if(ppm <= 350){
    float temp = 0;
    smoother(servo_co2, temp, &pos_c);
  }else{
    float temp = (ppm - 350) / 650 * 180;
    smoother(servo_co2, temp, &pos_c);
  }
}


/// @brief smooth the servo rotating
/// @param servo servo you want to control
/// @param tar target postion
/// @param prev pointer of previous position(which is pos_t, pos_h, pos_c)
void smoother(Servo servo, float tar, float* prev){
  if(*prev > tar){
      for(*prev; *prev > tar; *prev = (*prev * 100 - 1) / 100){
        servo.write(*prev);
        // delay(1);
      }
    }else if(*prev < tar){
      for(*prev; *prev < tar; *prev = (*prev * 100 + 1) / 100){
        servo.write(*prev);
        // delay(1);
      }
    }
}