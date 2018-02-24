# Interfacing-VL53L0X-with-Arduino
This repo consist of codes for interfacing two VL53L0X sensors with Arduino using polulu library

the library repo - https://github.com/pololu/vl53l0x-arduino


# Procedure to get two VL53L0X working on the same I2C bus
*	The XSHUT pins of the two sensors (S1 & S2) must be connected to two GPIOs
*	The GPIOs to which XSHUT are connected must be initiated as output and brought to LOW first (to shutdown both the sensors).
*	Then XSHUT of one of the sensors (S1) must be brought to high (This can be done by redefining the pin as input and letting the sensor drive it to high, or defining the GPIO as open drain output).
*	Then the sensor should be initialized by calling the VL53L0X_DataInit(), VL53L0X_StaticInit(), and VL53L0X_PerformRefCalibration() functions which are exposed by the API.
*	Now S1 is up and S2 is in standby mode.
*	Now we should change the address of S1. The default address is 0x29 (0b0101001). 
*	This can be done by writing the new address (7 bit address) to the register 0x8A. 
*	After changing the address of S1, S2 can be booted up by making the XSHUT of it high and initiating it. (We can optionally change the address of S2 too).
*	Then if there is a calibration offset it should be added/subtracted to the existing value in the registers 0x28, 0x29 (note that the offset is a 16-bit value and hence stored in two registers with MSB stored in 0x28).
*	Then the timing budget of both the sensors must be set to 200 000 micro seconds for high accuracy. This is done by calling the API function VL53L0X_set_measurement_timing_budget_micro_seconds().
*	Then the reading can be taken by calling the API function VL53L0X_PerformSingleRangingMeasurement() alternatively for each sensor.
