from enum import Enum
from typing import Callable, List


from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QGridLayout,
    QMainWindow,
    QWidget,
    QLabel,
)


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
    " ",
    "♟︎",
    "♞",
    "♝",
    "♜",
    "♛",
    "♚",
    "♟︎",
    "♞",
    "♝",
    "♜",
    "♛",
    "♚",
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
SQUARE_BACKGROUND_COLOR_DARK = "rgb(70, 70, 70)"
SQUARE_BACKGROUND_COLOR_LIGHT = "rgb(120, 120, 120)"

PIECE_COLOR_LIGHT = "rgb(192, 193, 194)"
PIECE_COLOR_DARK = "rgb(12, 12, 12)"

SQUARE_BACKGROUND_HIGHLIGHT_COLOR = "rgb(30, 144, 214)"


class Square(QWidget):
    def __init__(self, square_color: str):
        super().__init__()

        self.native_square_color = square_color
        self.highlight = False

        self.main_layout = QGridLayout()
        self.setLayout(self.main_layout)

        self.setStyleSheet(f"background-color: {self.native_square_color};")
        self.piece_symbol = QLabel(" ")

        self.main_layout.addWidget(self.piece_symbol, *(0, 0))
        self.piece_symbol.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.set_piece()

        self.set_highlight(False)

    def on_export_scan_button_press(self, function: Callable) -> None:
        self.clicked.connect(function)

    def set_piece(self, piece: Piece = Piece.empty):
        symbol_id = int(piece.value)
        color = PIECE_COLOR_LIGHT
        if symbol_id >= Piece.b_pawn.value:
            symbol_id -= 6
            color = PIECE_COLOR_DARK

        symbol: str = unicode_symbol_encoding_all_black[symbol_id]

        self.piece_symbol.setText(symbol)
        self.piece_symbol.setStyleSheet(f"color: {color};  font-size: 40px;")

    def set_highlight(self, highlight: bool = True):
        self.highlight = highlight
        if self.highlight:
            self.setStyleSheet(
                f"background-color: {SQUARE_BACKGROUND_HIGHLIGHT_COLOR};"
            )
        else:
            self.setStyleSheet(f"background-color: {self.native_square_color};")

    def toggle_highlight(self):
        if self.highlight:
            self.setStyleSheet(f"background-color: {self.native_square_color};")
        else:
            self.setStyleSheet(
                f"background-color: {SQUARE_BACKGROUND_HIGHLIGHT_COLOR};"
            )


class MainWindow(QMainWindow):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self._init_ui()
        self.display_board()

    def _init_ui(self):
        self.setWindowTitle("Chess mk3")

        self.setGeometry(100, 100, 800, 800)

        self.main_layout = QGridLayout()
        self.main_layout.setHorizontalSpacing(2)

        for x in range(8):
            for y in range(8):
                square_color = SQUARE_BACKGROUND_COLOR_DARK
                if (x + y) % 2 == 0:
                    square_color = SQUARE_BACKGROUND_COLOR_LIGHT

                self.main_layout.addWidget(Square(square_color), *(x, y))

        widget = QWidget()
        widget.setLayout(self.main_layout)
        self.setCentralWidget(widget)

    def display_board(
        self,
        board: str = "rnbqkbnrppppppppeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeePPPPPPPPRNBQKBNR",
        highlight: List[int] = [12, 32],
        estimation: int = 0,
    ):
        for id, piece_char in enumerate(board):
            self.main_layout.itemAt(id).widget().set_piece(
                ascii_to_piece_encoding[piece_char]
            )

        for id, highlight_id in enumerate(highlight):
            self.main_layout.itemAt(highlight_id).widget().set_highlight(False)
            self.main_layout.itemAt(highlight_id).widget().set_highlight(True)
