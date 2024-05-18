#include <Wire.h>

byte deviceAddress = 0x10;  // The address of the TF-Luna device is 0x10

bool running = true;
int buzzer_pin = 8;
unsigned int frequency = 0;
unsigned int duration = 0;

int max = 800;

float f_scale = 1;
int f_intercept = 50;

float d_scale = 1;
int d_intercept = 0;

void setup() {
  Wire.begin();        // The I2C bus communication starts
  Serial.begin(9600);  // Set the baud rate of the serial port to 9600
  pinMode(buzzer_pin, OUTPUT);
}

void beep(int note, int duration) {
  //Play tone on buzzerPin
  tone(buzzer_pin, note, duration);
  delay(duration);

  //Stop tone on buzzerPin
  noTone(buzzer_pin);
}

unsigned int calculate_frequency(float distance) {
  distance = (distance == 0) ? max : distance;
  distance = (distance > max) ? max : distance;

  int frequency = f_scale * pow(2, (max - distance) * (9.5 / max)) + f_intercept;

  return frequency;
}

unsigned int calculate_delay(float distance) {
  distance = (distance == 0) ? 800 : distance;
  distance = (distance > 800) ? 800 : distance;

  //int frequency = f_scale * (2, (distance) * (11.0/max)) + f_intercept;
  int delay = d_scale * max * (log(distance+50)/log(15)-1.35) + d_intercept;

  // Return the frequency as an unsigned integer
  return delay;
}

void loop() {
  Wire.beginTransmission(deviceAddress);  // The I2C data transmission starts
  Wire.write(0x00);

  // Send command
  Wire.endTransmission();  // The I2C data transfer is complete

  Wire.requestFrom((uint8_t)deviceAddress, (uint8_t)7);  // Read 7 bytes of data
  if (Wire.available() == 7) {                           // 7 bytes of data are available
    byte data[7];
    for (int i = 0; i < 7; i++) {
      data[i] = Wire.read();  // Read data into an array
    }


    unsigned int distance = (data[1] << 8) | data[0];        // DistanceValue
    unsigned int signalStrength = (data[3] << 8) | data[2];  // signal strength

    //Serial.print("Distance: ");
    //Serial.print(distance);
    //Serial.print(" cm  \n");

    //Serial.print("Signal Strength: ");
    //Serial.print(signalStrength);
    //Serial.print("\n");
    frequency = calculate_frequency(distance);
    duration = calculate_delay(distance);
    Serial.print(duration);
    Serial.print(" , ");
    Serial.print(distance);
    Serial.print(" , ");
    Serial.println(frequency);

    beep(frequency, 150);
    delay((duration));
  }
}