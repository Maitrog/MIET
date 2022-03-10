import random

if __name__ == '__main__':
    x = [random.randint(0,10000) for _ in range(10000)]
    print(x)
    res = int(input('Введите число: '))
    sum = 0
    min = 0
    i = 0
    while i < 10000:
        if sum == res:
            for j in range(min, i):
                print(x[j], end=" ")
            break
        if sum < res:
            sum += x[i]
            i += 1
        if sum > res:
            sum -= x[min]
            min += 1
    if sum != res:
        print('False')
