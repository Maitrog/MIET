
def monotone(a):
    for i in range(0, len(a)-1):
        if a[i] > a[i+1]:
            return False
    return True



a = tuple(input())
print(monotone(a))