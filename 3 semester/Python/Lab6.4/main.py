from multiprocessing import Pool
import os
import time


def file_find():
    f = []
    for top, dirs, files in os.walk(os.getcwd()):
        for nm in files:
            name = nm.split('.')
            if len(name) > 1 and name[1] == 'py':
                with open(top + '\\' + nm, encoding='utf-8') as file:
                    for line in file:
                        if 'if' in line:
                            f.append(nm)
                            break
    return f


if __name__ == '__main__':
    start_time = time.time()
    print(file_find())
    t = (time.time() - start_time)
    print("Pool({}): -— {} s seconds —-".format(0, t))

    for i in range(1, 9):
        start_time = time.time()
        with Pool(i) as pool:
            pool.map(file_find, [])
        t = (time.time() - start_time)
        print("Pool({}): -— {} s seconds —-".format(i, t))
