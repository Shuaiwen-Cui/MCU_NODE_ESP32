from machine import Pin
import time

def blink(LED, time_interval=1):
    LED.value(1)
    time.sleep(time_interval)
    LED.value(0)
    time.sleep(time_interval)

def main():
    print("Welcome to MicroPython!")
    LED = Pin(1, Pin.OUT)
    while True:
        blink(LED)
    
if __name__ == '__main__':
    main()