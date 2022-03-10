
def cross(*params):
    str = params[0]
    for i in range(1,len(params)):
        str = set(params[i]) & set(str)
    return str


a = [1,2,3,6,5,4,7,89]
b = [1,2,3,5,9,123,54,68,7,97,9]
c = [5,7,89,55,3255,454,5,464,64,64,4,46446,464,4,59,798,7,979,8413218]
print(cross(a, b, c))