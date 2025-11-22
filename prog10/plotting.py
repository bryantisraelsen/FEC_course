import numpy as np
import matplotlib.pyplot as plt
from scipy.special import erfc

def Q(x):
    return 0.5 * erfc(x / np.sqrt(2.0))

data = np.loadtxt("results.txt")
R = 1/2;
snr = data[:,0]
uncoded = data[:,1]
hard = data[:,2]
soft = data[:,3]

k = 1
dfree = 5
a_dfree = 1
n_dfree = 1

EbN0_lin = 10**(snr/10)
EcN0_lin =R*EbN0_lin
union_bound = (1/k) * a_dfree * Q(np.sqrt(2 * dfree * EcN0_lin))

asymp = (1.0/k) * 0.5 * a_dfree * n_dfree * np.exp(-dfree * EcN0_lin)

plt.semilogy(snr, union_bound, '--', label="Bound")
plt.semilogy(snr, asymp, '--', label="Asymptotic approx")

plt.semilogy(snr, uncoded, label="Uncoded BPSK")
plt.semilogy(snr, hard, label="Hard-decision")
plt.semilogy(snr, soft, label="Soft-decision")

plt.grid(True, which="both")
plt.legend()
plt.show()

