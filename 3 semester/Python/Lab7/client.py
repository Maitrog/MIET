import socket

HOST = 'localhost'
PORT = 25565

while True:
    addres_to = str(input('Введите адрес электронной почты:'))
    text = str(input('Введите текст сообщения:'))
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(bytearray('{}|{}'.format(addres_to, text), 'utf8'))
        data = s.recv(1024)
    if data.decode('utf8') == 'OK':
        print('OK')
        break
    else:
        print(data.decode('utf8'))
