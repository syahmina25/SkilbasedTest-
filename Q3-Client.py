import socket

def main():
    host = "127.0.0.1"
    port = 8888

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

    quote = s.recv(1024).decode()
    print(f"Quote of the Day: {quote}")
    s.close()

if __name__ == "_main_":
    main()
