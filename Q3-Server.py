import socket
import threading
import random

quotes = [
    "When in doubt go to the library.",
    "However difficult life may seem, there is always something you can do and succeed at.",
    "There are no secret to success. It is the result of preparation, hard work, and learning from failure.",
    "Striving for success without hard work is like trying to harvest where you haven't planted.",
    "Success is not final, failure is not fatal: It is the courage to continue that counts."
]

def handle_client(client_socket):
    quote = random.choice(quotes)
    client_socket.send(quote.encode())
    client_socket.close()

def main():
    host = "192.168.229.128"
    port = 8888

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(5)
    print(f"[*] Listening on {host}:{port}")

    while True:
        client, addr = s.accept()
        print(f"[*] Connection from {addr}")

        client_handler = threading.Thread(target=handle_client, args=(client,))
        client_handler.start()

if __name__ == "_main_":
    main()


