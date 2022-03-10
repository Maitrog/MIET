import random

if __name__ == '__main__':
    x = [random.randint(1, 100) for _ in range(1000000)]
    # print(x)
    count = 0
    while len(set(x)) > 1:
        minimum = min(x)
        if minimum == 1:
            count += sum(x) - len(x)
            break
        for i in range(len(x)):
            if x[i] > minimum:
                if x[i] % minimum == 0:
                    k = x[i] // minimum - 1
                else:
                    k = x[i] // minimum
                count += k
                x[i] -= k * minimum

    print(count)
