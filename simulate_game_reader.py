from Board import Board
from set_up_connection import set_up_serial_connection


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

        # for id, param in enumerate(test_params):
        #     print(id, param)

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
        # print(resp)
        try:
            if "iteration_end" in resp.decode("utf-8"):
                buffer = buffer + resp.decode("utf-8")
                test_example = SimulateGameTestCase.parse_string(buffer)
                test_example.board.display_using_unicode()
                
                buffer = ""
            else:
                buffer = buffer + resp.decode("utf-8")

        except Exception as ex:
            print("error:", str(ex), "raw:", resp, "decoded:", resp.decode("utf-8"))
