import time
from Board import Board
from set_up_connection import set_up_serial_connection
import subprocess

class SimulateGameTestCase:
    def __init__(
        self,
        iteration,
        color,
        board,
        position_estimation,
        no_moves,
        starting_positions,
        moves,
    ) -> None:
        self.iteration: int = iteration
        self.board: Board = board
        self.color: str = color
        self.position_estimation: float = position_estimation
        self.no_moves: int = no_moves
        self.starting_positions: list[int] = starting_positions
        self.moves: list[int] = moves

    @staticmethod
    def parse_string(test_str: str):
        test_params = test_str.split(":")
        test_params = [param.strip() for param in test_params]
        test_params = [param.replace("\r", "") for param in test_params]
        test_params = [param.replace("\n", " ") for param in test_params]
        test_params = [param for param in test_params if param != ""]


        param_dict = {}
        for i in range(0,len(test_params),2):
            try:
                param_dict[test_params[i]] = test_params[i+1]
            except Exception:
                pass
        # print(param_dict)

        board = Board()
        board.parse_board(param_dict['board'])

        starting_positions = []
        moves = []
        moves_estimation = []

        no_moves = int(param_dict['no_moves'])
        if no_moves > 0:
            starting_positions = [int(pos) for pos in param_dict['starting_positions_str'].split(" ")]
            moves = [int(pos) for pos in param_dict['moves_str'].split(" ")]
            moves_estimation = [int(pos) for pos in param_dict['moves_estimation'].split(" ")]

            board.starting_positions = starting_positions
            board.moves_estimation = moves_estimation
            board.moves = moves
            board.color_to_move = param_dict['color']
            board.moving_to = int(param_dict['to'])
            board.moving_from = int(param_dict['from'])
            
        return SimulateGameTestCase(
            iteration=int(param_dict['iteration']),
            color=param_dict['color'],
            board=board,
            position_estimation=int(param_dict['position_estimation']),
            no_moves=no_moves,
            starting_positions=starting_positions,
            moves=moves,
        )
if __name__ == "__main__":

    # device = set_up_serial_connection()
    # device = open("some_file.txt", 'rb')
    buffer = ""
    chess_engine_proc = subprocess.Popen([r"C:\Users\piotr\Documents\chess-mk3\chess_board\Debug\ChessEngineMk3.exe"], stdout=subprocess.PIPE)
    
    while True:
        for line in chess_engine_proc.stdout:
            resp = line.decode()
            try:
                if "iteration_end" in str(resp):
                    buffer = buffer + resp
                    test_example = SimulateGameTestCase.parse_string(buffer)
                    test_example.board.display_using_unicode_minimalistic(use_class_variables=True)
                    # time.sleep(1)  # import time
                    buffer = ""
                else:
                    buffer = buffer + resp
                pass
            except Exception as ex:
                print("error:", str(ex), "raw:", resp, "decoded:", resp)
