from imaplib import IMAP4_SSL
import logging
import os
from dotenv import load_dotenv
import time


def save_log(msg, filename):
    logging.basicConfig(level=logging.INFO, filename=filename, format='%(message)s')
    logging.info(msg)


flag = False

load_dotenv()
while True:
    with IMAP4_SSL(os.getenv('IMAP_HOST'), int(os.getenv('IMAP_PORT'))) as M:
        rc, recp = M.login(os.getenv('EMAIL_LOGIN'), os.getenv('EMAIL_PASSWORD'))
        M.select()
        typ, data = M.search(None, '(UNSEEN)', 'FROM', os.getenv('EMAIL_LOGIN'))
        for num in data[0].split():
            typ, data = M.fetch(num, '(RFC822)')
            text = data[0][1].decode('utf8')
            print(text)
            subject = text.split('\r\n')[11].split(' ')
            msg = text.split('\r\n')[13]
            if len(subject) == 2:
                subject = subject[1]
            with open('success_request.log', 'r', encoding='utf8') as myLog:
                if os.stat('success_request.log').st_size == 0:
                    save_log('ID {} : {}'.format(subject, msg), 'success_request.log')
                else:
                    for s in myLog:
                        if subject in s:
                            flag = True
                            break
                    if flag:
                        save_log(msg, 'error_request.log')
                        flag = False
                    else:
                        save_log('ID {} : {}'.format(subject, msg), 'success_request.log')
    time.sleep(int(os.getenv('PERIOD_CHECK')))
