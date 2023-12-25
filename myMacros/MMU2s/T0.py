#!/usr/bin/python

import serial

ser = serial.Serial('/dev/serial/by-id/usb-Arduino_LLC_Arduino_Leonardo-if00')  	# open serial port
ser.write("T0")     									# write a string
while True:
    if(ser.inWaiting() != 0):             								
	ser.close()									# close port