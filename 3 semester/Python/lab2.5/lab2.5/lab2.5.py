liter = {}
with open("input.txt", "r") as input:
    for line in input:
        for i in line:
            if i in liter:
                liter[i] += 1
            else:
                liter[i] = 1
liter_item = list(liter.items())
liter_item.sort(key=lambda i: i[1])
with open("output.txt", "w") as output:
    for i in liter_item:
        output.write(str(i[0]) + " : " + str(i[1]) + '\n')