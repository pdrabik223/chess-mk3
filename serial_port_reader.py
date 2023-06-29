
import time
from typing import Optional
import serial.tools.list_ports
from serial import Serial, SerialException



if __name__ == "__main__":
    baudrate: int = 115200
    timeout: int = 1
    device: Optional[Serial] = None
    available_ports = serial.tools.list_ports.comports()

    print("List all available ports:")
    for port, desc, hwid in sorted(available_ports):
            print(f"\t port: '{port}', desc: '{desc}', hwid: '{hwid}")
    
    device = Serial(port="COM10", baudrate=baudrate, timeout=timeout)
    
    print("connected")
    i = 0
    while True:
        resp: bytes = device.readline()
        print(resp.strip())
        time.sleep(0.1)
        device.write(bytearray(str(i), "ascii"))
        i += 1
        time.sleep(0.1)