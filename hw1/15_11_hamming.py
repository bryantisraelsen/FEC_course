import math
import random
import numpy as np
from numpy.random import rand
import matplotlib.pyplot as plt
from scipy import special as sp

def qfunc(x):
    return 0.5-0.5*sp.erf(x/np.sqrt(2))

LOG2M = 1
Ec = 1
R = 11/15; #Hamming (15,11)
Eb = Ec/R
startSNRdB = 0
endSNRdB = 11
SNRdBstep = 1
Pbiterrorlist = []
theoretical = []
maxbiterrorcount = 100
k = 11
n = 15
H = np.array([[1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1], [0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1], [0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1], [0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1]])
H_T = H.T
for SNRdb in range(startSNRdB,endSNRdB,SNRdBstep):
    print("SNRdb is ", SNRdb)
    SNR = 10**(SNRdb/10) #SNRdb = 10Log10(SNR)
    N0 = Ec/(R*SNR)
    crossover_prob = qfunc(np.sqrt((2*Ec)/(N0)))
    biterrorcount = 0
    numbits = 0
    biterrorcount = 0
    decoded = np.array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
    while(biterrorcount < maxbiterrorcount):
        received = (np.random.rand(n) < crossover_prob).astype(int)
        numbits += k
        syndrome = received @ H_T

        if not np.all(syndrome == 0):
            for k in range(n):
                if np.array_equal(H_T[k], syndrome):
                    received[k] ^= 1
            decoded[10] = received[10];
            decoded[9] = received[9];
            decoded[8] = received[8];
            decoded[7] = received[7];
            decoded[6] = received[6];
            decoded[5] = received[5];
            decoded[4] = received[4];
            decoded[3] = received[3];
            decoded[2] = received[2];
            decoded[1] = received[1];
            decoded[0] = received[0];
            #count the number of 1's (that is the number of remaining errors)
            biterrorcount += np.sum(decoded)
            if np.sum(decoded) != 0:
                print("***bit error count is ", biterrorcount, " decoded is ", decoded)

    Pbiterror = biterrorcount/numbits
    Pbiterrorlist.append(Pbiterror) #Save Pbiterror in an array for plotting
    #theoretical.append(qfunc((tau + np.sqrt(Eb))/sigma)*P_0 + qfunc((np.sqrt(Eb)-tau)/sigma)*P_1)
    theoretical.append(qfunc(np.sqrt(2*(LOG2M*Eb)/(N0))))
print("Exited loop")

plt.figure(1); plt.clf()
plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), Pbiterrorlist)
plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), theoretical)
#plt.axvline(x=9.6, color = 'r')
#plt.legend(["P_0 = 0.5 Bit Error vs SNR", "P_0 = 0.5 Theoretical", "P_0 = 0.25 Bit Error vs SNR", "P_0 = 0.25 Theoretical", "P_0 = 0.1 Bit Error vs SNR", "P_0 = 0.1 Theoretical"], loc="upper right")
plt.legend(["Simulated Hamming(15,11) BPSK", "Theortical Bit Error for Uncoded"], loc="upper right")
plt.xlabel("Eb/N0  (dB)")
plt.ylabel("Pb")
plt.show()
