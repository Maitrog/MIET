from multiprocessing import Pool
import random
import time


def matrix(p):
    return 1 / (1 + abs(p))


if __name__ == '__main__':
    count = 5000
    r = list()
    p = [random.randint(0, 100) for _ in range(count)]
    q = [random.randint(0, 100) for _ in range(count)]
    for i in range(count):
        for j in range(count):
            r.append(p[i] - q[j])

    start_time = time.time()
    for i in r:
        matrix(i)
    t = (time.time() - start_time)
    print("Pool(0): -— {} s seconds —-".format(t))

    for i in range(1, 9):
        with Pool(i) as p:
            start_time = time.time()
            p.map(matrix, r)
            t = (time.time() - start_time)
            print("Pool({}): -— {} s seconds —-".format(i, t))
