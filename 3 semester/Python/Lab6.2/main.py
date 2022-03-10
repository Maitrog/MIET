import threading

sem = threading.Semaphore(1)


def factor(str, num):
    ans = 1
    sem.acquire()
    with open(str, "a") as f:
        for i in range(1, num + 1):
            ans *= i
            f.write("{}\n".format(ans))
        sem.release()
        return ans


def sum(str, num):
    ans = 0
    sem.acquire()
    with open(str, "a") as f:
        for i in range(1, num + 1):
            ans += i
            f.write("{}\n".format(ans))
        sem.release()
        return ans


f = open("factor.txt", "w")
f.close()
thread1 = threading.Thread(target=factor, args=("factor.txt", 10,))
thread2 = threading.Thread(target=sum, args=("factor.txt", 10,))
thread1.start()
thread2.start()
thread1.join()
thread2.join()
