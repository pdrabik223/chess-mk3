from Board import Board
from set_up_connection import set_up_serial_connection

import statistics

if __name__ == "__main__":

    device = set_up_serial_connection()
    measurements = []    
    for i in range(5_000):
        
        for _ in range(100):
            resp: bytes = device.readline()
            
        resp: bytes = device.readline()
        if resp.decode("utf-8").strip() != '':
            measurements.append(int(resp.decode("utf-8").strip()))
            print(i, int(resp.decode("utf-8").strip()), 'avg:', statistics.mean(measurements))
