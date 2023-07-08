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
    w_rook= 4
    w_queen = 5
    w_king = 6
    b_pawn = 7
    b_knight= 8
    b_bishop= 9
    b_rook =10
    b_queen = 11
    b_king = 12

ascii_symbol_encoding  = ['e', 'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K']
unicode_symbol_encoding = ['  ','♙ ','♘ ','♗ ','♖ ','♕ ','♔ ','♟︎ ','♞ ','♝ ','♜ ','♛ ','♚ ']

ascii_to_piece_encoding = {
    'e':Piece.empty, 
    'p':Piece.w_pawn,
    'n':Piece.w_knight,
    'b':Piece.w_bishop,
    'r':Piece.w_rook,
    'q':Piece.w_queen,
    'k':Piece.w_king,
    'P':Piece.b_pawn,
    'N':Piece.b_knight,
    'B':Piece.b_bishop,
    'R':Piece.b_rook,
    'Q':Piece.b_queen,
    'K':Piece.b_king,
    
}

class Board:
    
    
    def __init__(self) -> None:
        self.data = [Piece.empty for _ in range(64)] 

    
    def display_using_unicode(self):
        
        to_8_counter = 0
        to_2_counter = 0
        final_string = ''
        for piece in self.data:
            if to_2_counter == 0:
                background_color = Back.WHITE + Back.WHITE
            else:
                background_color = Back.BLACK + Back.BLACK
            
            if to_8_counter == 7:
                endline = '\n'
                
                if to_2_counter == 0:
                    to_2_counter = 1
                else:
                    to_2_counter = 0
            else:
                endline = ''
                
            final_string += background_color + unicode_symbol_encoding[piece.value] + Style.RESET_ALL + endline
            to_2_counter += 1
            to_8_counter += 1
            
            if to_2_counter == 2: to_2_counter = 0
            if to_8_counter == 8: to_8_counter = 0
            
        print(final_string)
    
    
    def parse_board(self, message: bytes):
        message = message.strip()
        message = message[:64]
        message = message.decode("ASCII")
        for id, symbol in enumerate(message):
            self.data[id] = ascii_to_piece_encoding[symbol]

    @staticmethod
    def read_board(device):
        while True:
            resp: bytes = device.readline()
            print(resp.strip())
            if "board:" in str(resp.strip()):
                resp: bytes = device.readline()
                board = Board()
                board.parse_board(resp)
                print("board:")
                board.display_using_unicode()
                return
            else:
                print("failed to read, retrying...")
            time.sleep(0.1)
 
    def send_board(self, device):
        message = ''.join([ascii_symbol_encoding[piece.value] for piece in self.data])
        device.write(bytes(message, "ASCII"))


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
    
    loca_board = Board()
    
    for _ in range(10):
        Board.read_board(device)
        # loca_board.add_random_move()
        loca_board.send_board(device)
        time.sleep(1)


if __name__ == "__main__":
    test = Board()
    test.display_using_unicode()
    device = set_up_serial_connection()
    all_possible_positions(device)
