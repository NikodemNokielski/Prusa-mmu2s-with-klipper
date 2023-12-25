#!/usr/bin/python

import serial

ser = serial.Serial('/dev/serial/by-id/usb-Arduino_LLC_Arduino_Leonardo-if00')  	# open serial port
ser.write("TS1")     									# write a string
ser.close()             								# close port