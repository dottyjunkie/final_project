import serial
import paho.mqtt.client as paho
import time

serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

while(1):

    buffer=""
    get=s.read(1)
    if get.decode()=='$':
        while(1):
            get=s.read(1)
            if get.decode()=='#':
                break
            buffer+=get.decode()


s.close()