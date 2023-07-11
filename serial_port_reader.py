import random
import time
from typing import Optional
import serial.tools.list_ports
from serial import Serial
from colorama import Fore, Back, Style
from enum import Enum


class Piece(Enum):
    empty = 0
    w_pawn = 1
    w_knight = 2
    w_bishop = 3
    w_rook = 4
    w_queen = 5
    w_king = 6
    b_pawn = 7
    b_knight = 8
    b_bishop = 9
    b_rook = 10
    b_queen = 11
    b_king = 12


ascii_symbol_encoding = [
    "e",
    "p",
    "n",
    "b",
    "r",
    "q",
    "k",
    "P",
    "N",
    "B",
    "R",
    "Q",
    "K",
]
unicode_symbol_encoding = [
    "  ",
    "♙ ",
    "♘ ",
    "♗ ",
    "♖ ",
    "♕ ",
    "♔ ",
    "♟︎ ",
    "♞ ",
    "♝ ",
    "♜ ",
    "♛ ",
    "♚ ",
]

ascii_to_piece_encoding = {
    "e": Piece.empty,
    "p": Piece.w_pawn,
    "n": Piece.w_knight,
    "b": Piece.w_bishop,
    "r": Piece.w_rook,
    "q": Piece.w_queen,
    "k": Piece.w_king,
    "P": Piece.b_pawn,
    "N": Piece.b_knight,
    "B": Piece.b_bishop,
    "R": Piece.b_rook,
    "Q": Piece.b_queen,
    "K": Piece.b_king,
}


class Board:
    def __init__(self) -> None:
        self.data = [Piece.empty for _ in range(64)]
        self.starting_positions = []
        self.moves = []
        self.moves_estimation = []
        self.color_to_move = ''

    def display_using_unicode(self):
        starting_positions_highlight_color = Back.GREEN
        moves_highlight_color = Back.YELLOW
        best_move_color = Back.RED
        best_move_piece_color = Back.CYAN
        
        
        to_8_counter = 0
        to_2_counter = 0
        final_string = ""
        for id, piece in enumerate(self.data):
            if to_2_counter == 0:
                background_color = Back.WHITE + Back.WHITE
            else:
                background_color = Back.BLACK + Back.BLACK

            if id in self.starting_positions:
                background_color = (
                    starting_positions_highlight_color
                    + starting_positions_highlight_color
                )
            # if id in self.starting_positions:
            #     if self.moves_estimation[self.starting_positions.index(id)] == max(self.moves_estimation):
            #         background_color = best_move_piece_color + best_move_piece_color
                
            if id in self.moves:
                background_color = moves_highlight_color + moves_highlight_color
            if self.color_to_move == 'white':
                if id in self.moves:
                    if self.moves_estimation[self.moves.index(id)] == max(self.moves_estimation):
                        background_color = best_move_color + best_move_color
            elif self.color_to_move == 'black':
                if id in self.moves:
                    if self.moves_estimation[self.moves.index(id)] == min(self.moves_estimation):
                        background_color = best_move_color + best_move_color
                        
                        
            if to_8_counter == 7:
                endline = "\n"

                if to_2_counter == 0:
                    to_2_counter = 1
                else:
                    to_2_counter = 0
            else:
                endline = ""

            final_string += (
                background_color
                + unicode_symbol_encoding[piece.value]
                + Style.RESET_ALL
                + endline
            )
            to_2_counter += 1
            to_8_counter += 1

            if to_2_counter == 2:
                to_2_counter = 0
            if to_8_counter == 8:
                to_8_counter = 0

        print(final_string)

    def add_random_move(self):
        self.data[random.randint(0, 63)] = Piece.w_pawn

    def parse_board(self, message: str):
        # message = message.strip()
        # message = message[:64]
        # message = message.decode("ASCII")
        for id, symbol in enumerate(message):
            self.data[id] = ascii_to_piece_encoding[symbol]

    def read_board(self, device):
        for _ in range(5):
            resp: bytes = device.readline()

            if "board:" in str(resp.strip()):
                resp: bytes = device.readline()
                self.parse_board(resp)
                return
            else:
                print("failed to read board, retrying... resp:", (resp))
            time.sleep(0.2)

    def read_possible_moves(self, device):
        for _ in range(5):
            resp: bytes = device.readline()

            if "moves:" in str(resp.strip()):
                resp: bytes = device.readline()
                print("starting positions:")
                print([int(r) for r in resp])

                # resp: bytes = device.readline()
                # print("moves:")
                # print([int(r) for r in resp])

                return
            else:
                print("failed to read possible moves retrying... resp:", (resp))
            time.sleep(0.2)

    def send_board(self, device):
        message = "".join([ascii_symbol_encoding[piece.value] for piece in self.data])
        print(message, len(message))
        device.write(bytes(message + "\n", "ASCII"))


def set_up_serial_connection():
    baudrate: int = 115200
    timeout: int = 1
    device: Optional[Serial] = None
    available_ports = serial.tools.list_ports.comports()

    print("List all available ports:")
    for port, desc, hwid in sorted(available_ports):
        print(f"\t port: '{port}', desc: '{desc}', hwid: '{hwid}")

    device = Serial(port="COM10", baudrate=baudrate, timeout=timeout)
    print("connected")
    return device


def move_over_board_and_print_info_about_pieces():
    device = set_up_serial_connection()

    Board.read_board()

    while True:
        resp: bytes = device.readline()
        board = Board()
        board.parse_board(resp)
        board.display_using_unicode()
        time.sleep(0.1)


def all_possible_positions(device):
    for _ in range(10):
        loca_board = Board()
        loca_board.add_random_move()
        loca_board.display_using_unicode()
        loca_board.send_board(device)
        loca_board.read_board(device)
        loca_board.display_using_unicode()
        loca_board.read_possible_moves(device)
        time.sleep(1)


class TestCase:
    def __init__(
        self,
        test_case_no,
        board,
        position_estimation,
        no_moves,
        starting_positions,
        moves,
    ) -> None:
        self.test_case_no: int = test_case_no
        self.board: Board = board
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
        for id, param in enumerate(test_params):
            print(id, param)

        no_moves = int(test_params[7])
        board = Board()
        board.parse_board(test_params[3])

        starting_positions = []
        moves = []
        moves_estimation = []

        if no_moves > 0:
            starting_positions = [int(pos) for pos in test_params[9].split(" ")]
            moves = [int(pos) for pos in test_params[11].split(" ")]
            moves_estimation = [float(pos) for pos in test_params[13].split(" ")]
            
            board.moves = moves
            board.starting_positions = starting_positions
            board.moves_estimation = moves_estimation
            
        return TestCase(
            test_case_no=int(test_params[1]),
            board=board,
            position_estimation=float(test_params[5]),
            no_moves=no_moves,
            starting_positions=starting_positions,
            moves=moves,
        )
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
        self.color:str = color
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
        
        for id, param in enumerate(test_params):
            print(id, param)

        board = Board()
        board.parse_board(test_params[5])

        starting_positions = []
        moves = []
        moves_estimation = []

        no_moves = int(test_params[9])
        if no_moves > 0:
            starting_positions = [int(pos) for pos in test_params[11].split(" ")]
            moves = [int(pos) for pos in test_params[13].split(" ")]
            moves_estimation = [float(pos) for pos in test_params[15].split(" ")]
            
            board.starting_positions = starting_positions
            board.moves_estimation = moves_estimation
            board.moves = moves
            board.color_to_move = test_params[3]
            
        return SimulateGameTestCase(
            iteration=int(test_params[1]),
            color=test_params[3],
            board=board,
            position_estimation=float(test_params[7]),
            no_moves=no_moves,
            starting_positions=starting_positions,
            moves=moves,
        )

if __name__ == "__main__":
    device = set_up_serial_connection()
    buffer = ""
    while True:
        resp: bytes = device.readline()
        try:
            print(resp)
            # if "test_end"  in resp.decode("utf-8") or "iteration_end" in resp.decode("utf-8"):
            #     buffer = buffer + resp.decode("utf-8")
            #     test_example = SimulateGameTestCase.parse_string(buffer)
            #     test_example.board.display_using_unicode()
            #     buffer = ""
            # else:
            #     buffer = buffer + resp.decode("utf-8")

        except Exception as ex:
            print("error:", str(ex), "raw", resp)
