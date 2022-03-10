
def easy(a, b):
    easy = list()
    for i in range(2,b):
        easy.append(i)
    for i in easy:
        for j in easy:
            if j % i == 0 and j != i:
                easy.remove(j)
    min = 0
    while a:
        if a in easy:
            min = easy.index(a)
            break
        else:
            a += 1
    return easy[min:len(easy)]


print("Ведите число A:")
a = int(input())
print("Ведите число B:")
b = int(input())
print(easy(a,b))