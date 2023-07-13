

from dataclasses import Field, dataclass
from pprint import pprint


@dataclass
class DataPoint:
    iteration:int 
    color:str 
    no_moves:int 
    position_estimation:float
    best_move_estimation:float
    elapsed_time_int_milliseconds:int 





if __name__ == "__main__":
    print("log_analyzer")
    whole_file = ""
    with open('output.txt', 'r') as f:
        for x in f:
            line = x.strip()
            if len(line) > 0:
                whole_file += line

    whole_file = whole_file.split(':')
    whole_file = [x for x in whole_file if len(x) > 0]
    
    
    whole_file_buffer = []
    buffer = []
    for x in whole_file:
        buffer.append(x)
        if x == 'iteration_end':
            whole_file_buffer.append(buffer)
            buffer = []
            
    for x in whole_file_buffer:
        # x = [ 'iteration',
        #       '16',
        #       'color',
        #       'white',
        #       'no_moves',
        #       '61',
        #       'position_estimation',
        #       '11.10',
        #       'best_move_estimation',
        #       '10.50',
        #       'elapsed time',
        #       '4229',
        #       'iteration_end']
        data_point = DataPoint(iteration = int(x[1]),color= x[3],no_moves = int(x[5]),position_estimation = float(x[7]),best_move_estimation=float(x[9]),elapsed_time_int_milliseconds=int(x[11]))
        print(data_point)
    
    import matplotlib.pyplot as plt
    import numpy as np
    
    xpoints = np.array([0, 6])
    ypoints = np.array([0, 250])
    
    plt.plot(xpoints, ypoints)
    plt.show()