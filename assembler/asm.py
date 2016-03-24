import sys
import os

ALU_OPS = {"add", "sub", "sll", "srl", "and", "or", "xor", "nor"}
ALU_FUNC = {"add":0x0, "sub":0x1, "sll":0x2, "srl":0x3, "and":0x4, "or":0x5, "xor":0x6, "nor":0x7}
REGS = {"$zero":0x0, "$v0":0x1, "$v1":0x2, "$v2":0x3, "$v3":0x4, "$t0":0x5, "$a0":0x6, "$a1":0x7}

#start point of code e.g. first PC value
BASE_ADDR = 0x20

#different syntaxes
R = 1
I = 2
L = 3
J = 4

#returns a 4 bit value
def op_encode(op):
    if op in ALU_OPS:#alu operations
        return 0x0, R
    elif op[0:-1] in ALU_OPS:#immediate alu operations
        return ALU_FUNC[op[0:-1]] | 0x8, I
    elif op=="lw":
        return 0x1, L
    elif op=="sw":
        return 0x2, L
    elif op=="seq":
        return 0x3, I
    elif op=="jmp":
        return 0x4, J
    elif op=="slt":
        return 0x5, R
    elif op=="slti":
        return 0x6, I
    elif op=="sne":
        return 0x7, I
    else:
        raise(Exception("uh oh " + op))


#makes it easy to convert from string to int if the base is either 10 or 16
def int_base(s):
    if len(s) > 2 and s[1] == "x":
        return int(s,16)
    else:
        return int(s,10)

def main():
    numArgs = len(sys.argv) - 1
    if numArgs == 0:
        print("not enough arguments")
        print("format: python script.py input [-o output]")
        quit()

    outfilename = "a.out"

    if sys.argv[1] == "-o":
        if numArgs == 1:
            print("invalid arguments")
            quit()
        outfilename = sys.argv[2]
    else:
        #first argument is the source file
        filename = sys.argv[1]

        if numArgs >= 2 and sys.argv[2] == "-o":
            if numArgs == 2:
                print("invalid arguments")
                quit()
            outfilename = sys.argv[3]

    #get all the lines in the file
    lines = {}
    with open(filename) as infile:
        lines = infile.readlines()

    #will be a dictionary linking labels to real addresses
    labels = {}

    #list of machine codes
    codes = []

    #loop to clean up spacing and record labels
    #lines with labels are deleted
    i = 0
    while i < len(lines):
        #fixing spacing
        lines[i] = lines[i].strip("\n\r")
        lines[i] = lines[i].replace("\t"," ")
        #need to remove completely blank lines
        if len(lines[i]) == 0:
            lines = lines[0:i] + lines[i+1:]
            continue
        #stripping leading spaces
        while len(lines[i]) > 0 and lines[i][0] == " ":
            lines[i] = lines[i][1:]
        #need to remove blank lines again because we just stripped spacing
        if len(lines[i]) == 0:
            lines = lines[0:i] + lines[i+1:]
            continue
        #removing trailing spaces
        j = len(lines[i]) - 1
        while lines[i][j] == " ":
            lines[i] = lines[i][0:j]
            j -= 1
        #removing comments
        lines[i] = lines[i].split(";")[0]
        lines[i] = lines[i].split("#")[0]
        #need to remove blank lines *again* because we just removed comments
        if len(lines[i]) == 0:
            lines = lines[0:i] + lines[i+1:]
            continue
        #dealing with labels
        if lines[i][-1] == ":":
            labels[lines[i][0:-1]] = BASE_ADDR + 2 * i
            lines = lines[0:i] + lines[i+1:]
        else:
            i += 1

    #this fails if outfilename doesn't exist, so just ignore it
    try:
        os.unlink(outfilename)
    except:
        pass

    #now we actually look at the code
    for line in lines:
        # get the opcode and the arguments
        op = line.split(" ")[0]
        args = [arg.strip(" ") for arg in line[len(op)::].strip(" \n\r").split(",")]
        opcode, type = op_encode(op)

        #look at the arguments, figure out what's rs,rt,etc
        rs = 0
        rt = 0
        rd = 0
        const = 0
        func = 0
        if type == R:
            rs = REGS[args[1]]
            rt = REGS[args[2]]
            rd = REGS[args[0]]
            if op in ALU_OPS:
                func = ALU_FUNC[op]
        elif type == I:
            rs = REGS[args[0]]
            rt = REGS[args[1]]
            try:#if it's not a valid int, assume it's a label
                const = int_base(args[2]);
            except:
                const = 0#we don't want to use labels with I instructions, and this lets us use I-type for sne and seq
        elif type == J:
            try:#if it's not a valid int, assume it's a label
                #this weird stuff with n is to ignore whitespace
                n = 1
                addr = line.split(" ")[n]
                while not addr:
                    n += 1
                    addr = line.split(" ")[n]
                const = int_base(addr)
            except:
                const = labels[addr]
        elif type == L:#lw and sw are weird because they're like lw rs,const(rt)
            rs = REGS[args[0]]
            pred = args[1].split("(")
            rt = REGS[pred[1].strip(" ")[0:-1]]
            try:#if it's not a valid int, assume it's a label
                const = int_base(pred[0].strip(" "))
            except:
                const = labels[pred[0].strip(" ")]

        #cut everything to the correct size
        opcode &= 0xF
        rs &= 0x7
        rt &= 0x7
        rd &= 0x7
        func &= 0x7
        if type == I:
            const &= 0x3F
        elif type == J:
            const &= 0xFFF

        #pack everything together
        hex = opcode << 12

        if type == R:
            hex |= rs << 9
            hex |= rt << 6
            hex |= rd << 3
            hex |= func
        elif type == I or type == L:
            hex |= rs << 9
            hex |= rt << 6
            hex |= const
        elif type == J:
            hex |= const

        codes.append(hex)
        with open(outfilename, "ab") as f:
            f.write(bytes([hex & 0x00FF]))
            f.write(bytes([(hex & 0xFF00) >> 8]))

main()
