import socket
from smtplib import SMTP, SMTPRecipientsRefused
import os
from dotenv import load_dotenv
import hashlib

load_dotenv()

HOST = 'localhost'
PORT = 25565
EMAIL_ADMIN = os.getenv('EMAIL_LOGIN')
while True:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(1)
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                TO, text = data.decode('utf8').split('|')
                ADMIN_MSG = "\r\n".join((
                    "From: %s" % os.getenv('EMAIL_LOGIN'),
                    "To: %s" % EMAIL_ADMIN,
                    "Subject: %d" % (
                                int(hashlib.sha224(bytearray(text, encoding='utf8')).hexdigest(), 16) % (10 ** 10)),
                    "",
                    text
                ))
                USER_MSG = "\r\n".join((
                    "From: %s" % os.getenv('EMAIL_LOGIN'),
                    "To: %s" % TO,
                    "Subject: %d" % (
                                int(hashlib.sha224(bytearray(text, encoding='utf8')).hexdigest(), 16) % (10 ** 10)),
                    ""
                ))
                try:
                    with SMTP("{}:{}".format(os.getenv('SMTP_HOST'), os.getenv('SMTP_PORT'))) as smtp:
                        smtp.starttls()
                        smtp.login(os.getenv('EMAIL_LOGIN'), os.getenv('EMAIL_PASSWORD'))
                        smtp.sendmail(os.getenv('EMAIL_LOGIN'), EMAIL_ADMIN, ADMIN_MSG)
                        smtp.sendmail(os.getenv('EMAIL_LOGIN'), TO, USER_MSG)
                    conn.sendall(b'OK')
                except SMTPRecipientsRefused:
                    conn.sendall(bytearray('Incorrect email', 'utf8'))
                except UnicodeEncodeError:
                    conn.sendall(bytearray('Unacceptable character', 'utf8'))
