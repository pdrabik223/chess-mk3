from Board import Board
from set_up_connection import set_up_serial_connection
import time
import winsound
previous_elapsed_times = []
previous_boards = []
prev_times = []
if __name__ == "__main__":

    device = set_up_serial_connection()
    buffer = ""
    id = 0
    average_improvement = 0.0 
    try:
        with open('analysis/2023-07-22-13-58-01.txt', 'r') as f:
            prev_times = f.readlines()
    except Exception:
        print("file with prev times could not be loaded :c")
    
    with open(f'analysis/{time.strftime("%Y-%m-%d-%H-%M-%S")}.txt', 'w') as f:
        while id < 100:
            resp: bytes = device.readline()
            # print(resp.decode("utf-8"))
            if "elapsed time" in resp.decode("utf-8"):
                resp: bytes = device.readline()
                current_measurement = int(resp.decode("utf-8"))
                if id <len(prev_times):
                    average_improvement += current_measurement  - int(prev_times[id]) ;
                    print("iteration:",f"{id}/100", "elapsed time: [s]:",current_measurement/1000, "last_measurement: [s]",int(prev_times[id])/1000, "difference: [ms]", current_measurement - int(prev_times[id]) , "mean difference: [ms]", average_improvement / (id + 1))
                else:
                    print("iteration:",f"{id}/100", "elapsed time: [s]:",current_measurement/1000, "last_measurement: no data")
                id +=1
                f.writelines([str(current_measurement), "\n"])
               

            if "board" in resp.decode("utf-8"):

                str_board: bytes = device.readline()
                from_header:bytes = device.readline()
                str_from:bytes = device.readline()
                to_header:bytes = device.readline()
                str_to:bytes = device.readline()
                
                str_board = str(str_board.decode("utf-8")).strip()
                board = Board()
                board.parse_board(str_board)
                board.display_using_unicode_minimalistic(int(str_from),int(str_to))
                previous_boards.append(str_board)
                if len(previous_boards) > 5:
                    if previous_boards[-5] == str_board:
                        break
                
    print("Simulation finished")