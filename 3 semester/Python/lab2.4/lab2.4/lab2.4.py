output = open("output.txt", "w")
with open("input1.txt", "r") as input1:
    for line in input1:
        words1 = line.split()
        for word in words1:
            input2 = open("input2.txt", "r")
            for line2 in input2:
                if (line2.find(word,0,len(line2)) != -1):
                    output.write(word + "\n")
output.close()
input1.close()
input2.close()
