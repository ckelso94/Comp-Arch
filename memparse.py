#!/bin/python

lines = []
with open("out.txt") as file:
    lines = file.readlines()

nums = []
data = []
for line in lines:
    if line[0] == 'i' or line[0] == 'd' or line[0] == 'o':
        nums.append(0)
        data.append(0)
        continue
    if len(line) == 6:
        nums.append(line[0:-1])
    elif len(line) == 7:
        data.append(line[0:-1])

print(nums)
print(data)

with open("nums.txt", "w") as outfile:
    for n in nums:
        outfile.write(str(n) + "\n")

with open("dats.txt", "w") as outfile:
    for d in data:
        outfile.write(str(d) + "\n")

