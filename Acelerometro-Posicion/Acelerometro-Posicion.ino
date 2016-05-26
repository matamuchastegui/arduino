#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
float dx, dy, dz = 0;
int16_t gx, gy, gz;





#define LED_PIN 13
bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    //Serial.begin(38400);
    Serial.begin(9600);
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    Serial.println("Updating internal sensor offsets...");

    accelgyro.setXGyroOffset(85);
    accelgyro.setYGyroOffset(1);
    accelgyro.setZGyroOffset(-4);
    accelgyro.setXAccelOffset(-4269);
    accelgyro.setYAccelOffset(-4836);
    accelgyro.setZAccelOffset(1080);

    pinMode(LED_PIN, OUTPUT);
}

void loop() {

        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

        dx=dx+(float)(((float)ax/(float)16384)*9.8*0.05*0.05);
        dy=dy+(float)(((float)ay/(float)16384)*9.8*0.05*0.05);
        dz=dz+(float)(((float)az/(float)16384)*9.8*0.05*0.05);
        Serial.print(dx); Serial.print("\t");
        Serial.print(dy); Serial.print("\t");
        Serial.print(dz); Serial.print("\t\n");


delay(10);
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
