from set_up_connection import set_up_serial_connection


if __name__ == "__main__":
    device = set_up_serial_connection()
    buffer = ""
    while True:
        resp: bytes = device.readline()
        print(resp)
