

import copy
from dataclasses import Field, dataclass
from pprint import pprint
from matplotlib import pyplot as plt
import pandas as pd 
import argparse

def no_moves_against_iteration(df):
    # no_moves against iteration 
    df_white = df.loc[df['color'] == "white"]
    df_black = df.loc[df['color'] == "black"]
    
    fig, axes = plt.subplots(nrows=3, ncols=2, constrained_layout=True)
    # fig.suptitle('no_moves against iteration')
    df_white.plot(ax = axes[0,0], x = "iteration", y='no_moves')
    df_black.plot(ax = axes[0,0], x = 'iteration', y = "no_moves",title = 'Number of moves')
    axes[0,0].legend(["white", "black"])
    
    
    df_white.plot(ax = axes[0,1], x = "iteration", y='best_move_estimation')
    df_black.plot(ax = axes[0,1], x = 'iteration', y = "best_move_estimation",title = 'Best Move estimation')
    axes[0,1].legend(["white", "black"])
    
    
    
    df.plot(ax = axes[1,0], y = "position_estimation",title = 'Position Estimation')
    df.plot(ax = axes[1,1], y = "elapsed_time_int_milliseconds",title = 'Elapsed Time')
    

    local_df = df.sort_values(by=['no_moves'],ascending=False)
    local_df.plot(ax = axes[2,0], x ="no_moves", y = "elapsed_time_int_milliseconds",title = 'Elapsed Time')
    axes[2,0].invert_xaxis()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                    prog='Log analyzer',
                    description='analyzes logs from arduino chess engine',
                    )
    parser.add_argument('filename') 
    args = parser.parse_args()
    
    whole_file = ""
    with open(args.filename, 'r') as f:
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
            
    df = pd.DataFrame(columns=["iteration","color","no_moves","position_estimation","best_move_estimation","elapsed_time_int_milliseconds"])
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
        data_point = pd.DataFrame({'iteration':int(x[1]), 'color':x[3], 'no_moves':int(x[5]), 'position_estimation':float(x[7]),'best_move_estimation':float(x[9]),'elapsed_time_int_milliseconds':int(x[11])}, index=[0])
        df = pd.concat([data_point,df.loc[:]]).reset_index(drop=True)
        
    df = df.loc[::-1].reset_index(drop=True)
    print(df)
    no_moves_against_iteration(df)
    plt.show()  
