import socket
import threading

TCP_IP = '0.0.0.0'      # Escuta todas as interfaces
TCP_PORT = 4000         # Porta que o Arduino irá se conectar

UDP_IP = '127.0.0.1'    # Teleplot escuta no localhost
UDP_PORT = 47269

# Inicializa socket UDP
udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def handle_client(conn, addr):
    print(f"[+] Conexão TCP de {addr}")
    try:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print(f"[TCP] {data.decode().strip()}")
            udp_sock.sendto(data, (UDP_IP, UDP_PORT))
    except Exception as e:
        print(f"[Erro] {e}")
    finally:
        conn.close()
        print(f"[-] Conexão encerrada: {addr}")

# Servidor TCP
tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
tcp_sock.bind((TCP_IP, TCP_PORT))
tcp_sock.listen(5)

print(f"[TCP] Aguardando conexão na porta {TCP_PORT}...")

while True:
    conn, addr = tcp_sock.accept()
    thread = threading.Thread(target=handle_client, args=(conn, addr))
    thread.start()