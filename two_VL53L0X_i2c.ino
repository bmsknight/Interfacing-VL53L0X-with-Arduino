#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
VL53L0X sensor2;

void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
   pinMode(9, OUTPUT);
  digitalWrite(9, LOW);

  pinMode(9, INPUT);      //connect r&b sensor on 9
  delay(500);

  Wire.begin();
  Serial.begin (9600);


  Serial.println("Start");

  sensor1.init(true);
  sensor1.setAddress((uint8_t)20);
  sensor1.writeReg16Bit(sensor1.ALGO_PART_TO_PART_RANGE_OFFSET_MM,(uint16_t)100);   //offset calibration
  Serial.println("Sensor 1 initiated");
  delay(100);
  Serial.println("Sensor 1 address set");

  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(8, INPUT);
  delay(500);
  sensor2.init(true);
  sensor2.setAddress((uint8_t)30);        //comment this line to use default address for sensor 2
  //sensor2.writeReg16Bit(sensor2.ALGO_PART_TO_PART_RANGE_OFFSET_MM,(uint16_t)140);
  Serial.println("Sensor 2 initiated & using default address");

  pinMode(9, INPUT);
  delay(500);

  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  for (byte i = 1; i < 120; i++)
  {

    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Found address: ");
      Serial.println (i, DEC);
      count++;
      delay (1);  
    } 
  }
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");

  
  sensor1.setMeasurementTimingBudget(200000);
  sensor2.setMeasurementTimingBudget(200000);
  sensor1.setTimeout(500);
  sensor2.setTimeout(500);
  delay(500);
  
  Serial.println(sensor1.readReg16Bit(sensor1.ALGO_PART_TO_PART_RANGE_OFFSET_MM));
  Serial.println(sensor2.readReg16Bit(sensor2.ALGO_PART_TO_PART_RANGE_OFFSET_MM));

}

void loop() {
  //Serial.print("1 :");
  Serial.print (sensor1.readRangeSingleMillimeters());
  //delay(300);
  Serial.print("\t ");
  Serial.println (sensor2.readRangeSingleMillimeters());
  //Serial.println("....................................................");

  //delay(1000);
  
}
