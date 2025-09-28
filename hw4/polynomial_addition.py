def addition(a, b):
    answer = a^b
    return answer

def str_polynomial(x):
    if (x == 0):
        return "0"
    string_to_read = []
    for i in reversed(range(x.bit_length())):
        if (x & (1 << i)):
            if (i == 0):
                if (len(string_to_read)>0):
                    string_to_read.append("+1")
                else:
                    string_to_read.append("1")
            elif (i == 1):
                if (len(string_to_read)>0):
                    string_to_read.append("+x")
                else:
                    string_to_read.append("x")
            else:
                if (len(string_to_read)>0):
                    string_to_read.append(f"+x^{i}")
                else:
                    string_to_read.append(f"x^{i}")

        if (i == 0):
            return string_to_read




if __name__ == "__main__":
    mod = 0b10001
    a = 0b0
    b = 0b0
    n = 16
    addition_table = [[0 for _ in range(mod)] for _ in range(mod)]
    for i in range(mod):
        for j in range(mod):
            addition_table[i][j] = addition(i, j)
            #print("adding ", bin(i), " and ", bin(j), " together and got ", "".join(str_polynomial(addition_table[i][j])))

    # Print header row
    labels = [str_polynomial(i) for i in range(n)]
    print(f"{'':17}", end="")  # padding for corner
    for lbl in labels:
        print(f"{''.join(lbl):17}", end="")
    print()

    # Print each row with label
    for i in range(n):
        print(f"{''.join(labels[i]):17}", end="")
        for j in range(n):
            print(f"{''.join(str_polynomial(addition_table[i][j])):17}", end="")
        print()
