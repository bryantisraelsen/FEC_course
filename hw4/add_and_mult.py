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

def mult(a,b,mod=0b10001):
    result = 0
    for i in range(b.bit_length()):
        if (b>>i) & 1:
            result ^= a << i

    mod_deg = mod.bit_length() - 1

    while result.bit_length() >= mod_deg + 1:
        shift = result.bit_length() - (mod_deg + 1)
        result ^= mod << shift
    return result



if __name__ == "__main__":
    mod = 0b10001
    n = 16
    addition_table = [[0 for _ in range(mod)] for _ in range(mod)]
    for i in range(mod):
        for j in range(mod):
            addition_table[i][j] = addition(i, j)
            #print("adding ", bin(i), " and ", bin(j), " together and got ", "".join(str_polynomial(addition_table[i][j])))


    COL_WIDTH=11
    print("\nAddition:\n")
    #label row
    labels = [str_polynomial(i) for i in range(n)]
    print(f"{'':{2*COL_WIDTH-3}}", end="")
    for lbl in labels:
        print(f"{''.join(lbl):{COL_WIDTH}}", end="")
    print()

    for i in range(n):
        print(f"{''.join(labels[i]):{COL_WIDTH}}", end="")
        for j in range(n):
            print(f"{addition_table[i][j]:{COL_WIDTH}b}", end="")
        print()
    print("\n\n\n\nMultiplication:\n")

    mult_table = [[0 for _ in range(mod)] for _ in range(mod)]
    for i in range(mod):
        for j in range(mod):
            mult_table[i][j] = mult(i, j)

    #header row
    labels = [str_polynomial(i) for i in range(n)]
    print(f"{'':{2*COL_WIDTH-3}}", end="")
    for lbl in labels:
        print(f"{''.join(lbl):{COL_WIDTH}}", end="")
    print()

    #row
    for i in range(n):
        print(f"{''.join(labels[i]):{COL_WIDTH}}", end="")
        for j in range(n):
            print(f"{mult_table[i][j]:{COL_WIDTH}b}", end="")
        print()
