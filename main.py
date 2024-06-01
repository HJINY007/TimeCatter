import serial
import time
from datetime import datetime
from playsound import playsound
import threading

# Function to play the meow sound

# Replace with your Arduino's serial port
ser = serial.Serial('/dev/cu.usbserial-DN02T4CC', 9600)
time.sleep(2)  # Wait for the serial connection to initialize

def send_time_and_listen():
    while True:
        now = datetime.now()
        current_time = now.strftime("%Y/%m/%d %H:%M:%S\n")
        ser.write(current_time.encode())
        time.sleep(1)  # Send the time every second
        print("working")

        if ser.in_waiting > 0:
            message = ser.readline().decode().strip()
            if "Activity triggered" in message:
                playsound('meow.mp3')
                print(message)

send_time_and_listen()
