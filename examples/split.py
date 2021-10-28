
with open("factorial_100000.txt", "r") as r_file:
    line = r_file.readline()
    line_lis = [line[i:i+70] for i in range(0, len(line), 70)]
    for li in line_lis:
        print(li)
