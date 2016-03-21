hexlines = {}
binlines = {}
with open("a.out") as hex:
    with open("bina.out") as bin:
        hexlines = hex.readlines()
        binlines = bin.readlines()
for i in range(len(hexlines) - 1):
    print(hexlines[i][0:-1] + ": " + binlines[i][0:-1])
