with open("input.txt", "r") as input:
    for line in input:
        data = ([int(x) for x in line.split()])

input.close()
result = 0
for i in data:
    result += i

output = open("output.txt", "w")
output.write(str(result))
output.close()