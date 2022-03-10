max = 0
min = 10000
min_lastname = ""
max_lastname = ""

with open("input.txt", "r", newline="") as input:
    for line in input:
        str = line.split(";")
        age = int((str[2].split())[0])
        if age > max:
            max = age
            max_lastname = str[0]
        if age < min:
            min = age
            min_lastname = str[0]

input.close()

output = open("output.txt" , "w")
output.write(min_lastname + '\n')
output.write(max_lastname)
output.close()