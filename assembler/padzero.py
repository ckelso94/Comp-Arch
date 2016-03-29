i = 1
while True:
    try:
        i = input()
        while len(i) < 16:
            i = "0" + i
        print(i)
    except:
        break
