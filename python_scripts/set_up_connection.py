from typing import Optional
import serial.tools.list_ports
from serial import Serial
import serial


def set_up_serial_connection():
    baudrate: int = 115200
    timeout: int = 1
    device: Optional[Serial] = None
    available_ports = serial.tools.list_ports.comports()

    print("List all available ports:")
    for port, desc, hwid in sorted(available_ports):
        print(f"\t port: '{port}', desc: '{desc}', hwid: '{hwid}")
        if "USB Serial Device" in desc:
            device = Serial(port=port, baudrate=baudrate, timeout=timeout)
            print("connected to device on port:",port)
            
            break

    return device
