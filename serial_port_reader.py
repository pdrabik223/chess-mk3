
import time
from typing import Optional
import serial.tools.list_ports
from serial import Serial, SerialException


def parse_board(message:bytes):
    message = message.strip()
    message = message[:64]
    message = message.decode('utf-8')
    chess_board_visualization = ""
    for row in range(0,64,8):
        chess_board_visualization += message[row:row+8] + "\n"
    return chess_board_visualization


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
        if 'board:' in str(resp.strip()):
            time.sleep(0.1)
            resp: bytes = device.readline()
            print("board:\n",str(parse_board(resp)))
        else:    
            print('failed to read, retrying...')
        time.sleep(0.1)
