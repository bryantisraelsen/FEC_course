import numpy as np
from itertools import product

def generate_codewords(G):
    k, n = G.shape
    codewords = []
    for u in product([0, 1], repeat=k):
        u = np.array(u)
        cw = (u @ G) % 2
        codewords.append(tuple(cw))
    return set(codewords)

def hamming_weight(v):
    return sum(v)

def standard_array(G):
    n = G.shape[1]
    all_vecs = [tuple(v) for v in product([0,1], repeat=n)]
    codewords = generate_codewords(G)
    #put code word 0 first
    codewords = sorted(codewords, key=lambda v: (hamming_weight(v), v))
    array = []
    used = set()
    #put all-zero as the first coset leader
    leaders = [tuple([0]*n)]
    used.update(codewords)
    while len(used) < len(all_vecs):
        #pick next leader: lowest weight unused vector
        candidates = [v for v in all_vecs if v not in used]
        next_leader = min(candidates, key=lambda v: (hamming_weight(v), v))
        leaders.append(next_leader)
        #mark the coset as used
        for cw in codewords:
            coset_vec = tuple((np.array(next_leader) + np.array(cw)) % 2)
            used.add(coset_vec)

    #build rows: leader first, then leader + codeword
    for leader in leaders:
        row = [leader]  #coset leader at front
        for cw in codewords[1:]:  #skip first one already the leader
            coset_vec = tuple((np.array(leader) + np.array(cw)) % 2)
            row.append(coset_vec)
        array.append(row)

    return array

def print_standard_array(array):
    for row in array:
        print("  ".join("".join(map(str, v)) for v in row))

if __name__ == "__main__":
    G = np.array([[0,1,1,1,1,0,0,0],
                  [1,1,1,0,0,1,0,0],
                  [1,1,0,1,0,0,1,0],
                  [1,0,1,1,0,0,0,1]])
    array = standard_array(G)
    print("Standard Array:")
    print_standard_array(array)

