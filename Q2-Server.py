import socket

def fahrenheit_to_celsius(fahrenheit):
    celsius = (fahrenheit - 32) * 5/9
    return celsius

def main():
    host = "127.0.0.1"
    port = 8080

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(1)
    print(f"[*] Listening on {host}:{port}")

    conn, addr = s.accept()
    print(f"[*] Connection from {addr}")

    while True:
        data = conn.recv(1024)
        if not data:
            break
        fahrenheit = float(data.decode())
        celsius = fahrenheit_to_celsius(fahrenheit)
        conn.send(str(celsius).encode())
    conn.close()

if __name__ == "_main_":
    main()

