import random
import time
from colorama import Back, Fore, Style
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
unicode_symbol_encoding_all_black = [
    "  ",
    "♟︎ ",
    "♞ ",
    "♝ ",
    "♜ ",
    "♛ ",
    "♚ ",
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
        self.color_to_move = ""
        self.moving_from = 0
        self.moving_to = 0

    def display_using_unicode(self):
        starting_positions_highlight_color = Back.GREEN
        moves_highlight_color = Back.YELLOW
        best_move_color = Back.RED
        best_move_start_color = Back.CYAN

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
            if self.color_to_move == "white":
                if id in self.moves or id in self.starting_positions:
                    id_of_best_move = self.moves_estimation.index(
                        max(self.moves_estimation)
                    )
                    if id == self.moves[id_of_best_move]:
                        background_color = best_move_color + best_move_color
                    if id == self.starting_positions[id_of_best_move]:
                        background_color = best_move_start_color + best_move_start_color

            elif self.color_to_move == "black":
                if id in self.moves or id in self.starting_positions:
                    id_of_best_move = self.moves_estimation.index(
                        min(self.moves_estimation)
                    )
                    if id == self.moves[id_of_best_move]:
                        best_move_color + best_move_color
                    if id == self.starting_positions[id_of_best_move]:
                        background_color = best_move_start_color + best_move_start_color

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

    def display_using_unicode_minimalistic(
        self,
        from_pos: int = None,
        to_pos: int = None,
        use_class_variables: bool = False,
    ):
        if use_class_variables:
            from_pos = self.moving_from
            to_pos = self.moving_to

        to_8_counter = 0
        to_2_counter = 0
        final_string = ""
        for id, piece in enumerate(self.data):
            if to_2_counter % 2 == 0:
                background_color = Back.LIGHTBLACK_EX

                if id == from_pos:
                    background_color = Back.LIGHTYELLOW_EX
                if id == to_pos:
                    background_color = Back.LIGHTYELLOW_EX
            else:
                background_color = Back.BLACK

                if id == from_pos:
                    background_color = Back.YELLOW
                if id == to_pos:
                    background_color = Back.YELLOW

            if piece.value <= Piece.w_king.value:
                text_color = Fore.WHITE
            else:
                text_color = Fore.RED

            if to_8_counter % 8 == 7:
                endline = "\n"
            else:
                to_2_counter += 1
                endline = ""

            final_string += (
                background_color
                + text_color
                + unicode_symbol_encoding_all_black[piece.value]
                + Style.RESET_ALL
                + endline
            )
            to_8_counter += 1

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
