#Тюльников Михаил ПИН-22 Дополнительный номер
def SumDigits(num):
    sum = 0
    while(num!=0):
        sum += num%10
        num //=10
    return sum


def back_zero(num):
    zero_count = 0
    num -= 9
    while num % 10 == 0:
        zero_count += 1
        num //= 10
    return zero_count

def temp(zero):
    sum = 0
    while zero != 1:
        sum += 10**(zero - 1)
        zero -= 1
    return sum



def chek(num):
    zero = back_zero(num)
    if (num - 9) / (10**zero) < 100:
        return 1
    return 0


x = int(input())
count = 0
num = 10

import time
start_time = time.time()
while count!=x:
    num += 9
    sum = SumDigits(num)
    if sum == 10:
        count += 1
    elif chek(num) == 1 and num > 1000:
            zero = back_zero(num)
            factor = temp(zero)
            first = num // 10**(zero+1)
            num += 9 * (first * factor + first - 1)
    elif sum > 10:
        while num % 100 < 90:
            num += 9

t = (time.time() - start_time)
print("--- %s seconds ---" % t)
print(num)
