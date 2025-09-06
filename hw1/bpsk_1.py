import math
import random
import numpy as np
from numpy.random import rand
import matplotlib.pyplot as plt
from scipy import special as sp

def qfunc(x):
    return 0.5-0.5*sp.erf(x/np.sqrt(2))

a = 1 # PAM amplitude
LUT1 = np.array([-1,1])*a
LOG2M = 1
Eb = a**2
startSNRdB = 0
endSNRdB = 11
SNRdBstep = 1
Psymerrorlist_0_5 = []
Pbiterrorlist_0_5 = []
theoretical_0_5 = []
maxsymbolerrorcount = 200
P_0 = 0.5
P_1 = 1 - P_0
#P_0 = 0.5
for SNRdb in range(startSNRdB,endSNRdB,SNRdBstep):
    print("SNRdb is ", SNRdb)
    SNR = 10**(SNRdb/10) #SNRdb = 10Log10(SNR)
    N0 = Eb/SNR
    sigmaSquare = N0/2
    sigma = np.sqrt(sigmaSquare)
    symbolerrorcount = 0
    numsymbols = 0
    numbits = 0
    biterrorcount = 0
    ones_sent = 0
    zeros_sent = 0
    tau = (sigmaSquare/(2*np.sqrt(Eb)))*np.log(P_0/P_1)
    while(symbolerrorcount < maxsymbolerrorcount):
        numsymbols += 1
        numbits += LOG2M

        # transmitter
        bits = (rand(LOG2M) > P_0).astype(int) # generate random bits {0,1}
        #count if zero or one
        if (bits == 1):
            ones_sent += 1
        else:
            zeros_sent += 1
        for i in range(0, int(len(bits)/LOG2M)):   # S/P converter (makes it log_2_M size)
            log2_bit_list = []
            res = 0
            for j in range(0, LOG2M):
                log2_bit_list.append(bits[LOG2M*i+j])
            for ele in log2_bit_list:
                res = (res << 1) | ele
            sent_symb = res
        s_x = LUT1[sent_symb]

        # channel
        r_x = s_x + np.random.normal(0, sigma) #generate noise n with variance sigmaˆ2 in each coordinate direction

        # receiver
        if r_x > tau:
            shat = 1
        else:
            shat = 0
        if(shat != sent_symb):
            symbolerrorcount += 1
            biterrorcount += LOG2M
            print("***symbolerrorcnt is ", symbolerrorcount)

    print("Ones sent is ", ones_sent)
    print("Zeroes sent is ", zeros_sent)
    print("P_0 is ", zeros_sent/(ones_sent+zeros_sent))
    Psymerror = symbolerrorcount/numsymbols
    Pbiterror = biterrorcount/numbits
    Psymerrorlist_0_5.append(Psymerror) #Save Psymerror in an array for plotting
    Pbiterrorlist_0_5.append(Pbiterror) #Save Pbiterror in an array for plotting
    theoretical_0_5.append(qfunc((tau + np.sqrt(Eb))/sigma)*P_0 + qfunc((np.sqrt(Eb)-tau)/sigma)*P_1)
    #theoretical.append(qfunc(np.sqrt(2*(LOG2M*Eb)/(N0))))
print("Exited loop")

Psymerrorlist_0_25 = []
Pbiterrorlist_0_25 = []
theoretical_0_25 = []
P_0 = 0.25
P_1 = 1 - P_0
#P_0= 0.25
for SNRdb in range(startSNRdB,endSNRdB,SNRdBstep):
    print("SNRdb is ", SNRdb)
    SNR = 10**(SNRdb/10) #SNRdb = 10Log10(SNR)
    N0 = Eb/SNR
    sigmaSquare = N0/2
    sigma = np.sqrt(sigmaSquare)
    symbolerrorcount = 0
    numsymbols = 0
    numbits = 0
    biterrorcount = 0
    ones_sent = 0
    zeros_sent = 0
    tau = (sigmaSquare/(2*np.sqrt(Eb)))*np.log(P_0/P_1)
    while(symbolerrorcount < maxsymbolerrorcount):
        numsymbols += 1
        numbits += LOG2M

        # transmitter
        bits = (rand(LOG2M) > P_0).astype(int) # generate random bits {0,1}
        #count if zero or one
        if (bits == 1):
            ones_sent += 1
        else:
            zeros_sent += 1
        for i in range(0, int(len(bits)/LOG2M)):   # S/P converter (makes it log_2_M size)
            log2_bit_list = []
            res = 0
            for j in range(0, LOG2M):
                log2_bit_list.append(bits[LOG2M*i+j])
            for ele in log2_bit_list:
                res = (res << 1) | ele
            sent_symb = res
        s_x = LUT1[sent_symb]

        # channel
        r_x = s_x + np.random.normal(0, sigma) #generate noise n with variance sigmaˆ2 in each coordinate direction

        # receiver
        if r_x > tau:
            shat = 1
        else:
            shat = 0
        if(shat != sent_symb):
            symbolerrorcount += 1
            biterrorcount += LOG2M
            print("***symbolerrorcnt is ", symbolerrorcount)

    print("Ones sent is ", ones_sent)
    print("Zeroes sent is ", zeros_sent)
    print("P_0 is ", zeros_sent/(ones_sent+zeros_sent))
    Psymerror = symbolerrorcount/numsymbols
    Pbiterror = biterrorcount/numbits
    Psymerrorlist_0_25.append(Psymerror) #Save Psymerror in an array for plotting
    Pbiterrorlist_0_25.append(Pbiterror) #Save Pbiterror in an array for plotting
    theoretical_0_25.append(qfunc((tau + np.sqrt(Eb))/sigma)*P_0 + qfunc((np.sqrt(Eb)-tau)/sigma)*P_1)
    #theoretical.append(qfunc(np.sqrt(2*(LOG2M*Eb)/(N0))))
print("Exited loop")

Psymerrorlist_0_1 = []
Pbiterrorlist_0_1 = []
theoretical_0_1 = []
P_0 = 0.1
P_1 = 1 - P_0
#P_0=0.1
for SNRdb in range(startSNRdB,endSNRdB,SNRdBstep):
    print("SNRdb is ", SNRdb)
    SNR = 10**(SNRdb/10) #SNRdb = 10Log10(SNR)
    N0 = Eb/SNR
    sigmaSquare = N0/2
    sigma = np.sqrt(sigmaSquare)
    symbolerrorcount = 0
    numsymbols = 0
    numbits = 0
    biterrorcount = 0
    ones_sent = 0
    zeros_sent = 0
    tau = (sigmaSquare/(2*np.sqrt(Eb)))*np.log(P_0/P_1)
    while(symbolerrorcount < maxsymbolerrorcount):
        numsymbols += 1
        numbits += LOG2M

        # transmitter
        bits = (rand(LOG2M) > P_0).astype(int) # generate random bits {0,1}
        #count if zero or one
        if (bits == 1):
            ones_sent += 1
        else:
            zeros_sent += 1
        for i in range(0, int(len(bits)/LOG2M)):   # S/P converter (makes it log_2_M size)
            log2_bit_list = []
            res = 0
            for j in range(0, LOG2M):
                log2_bit_list.append(bits[LOG2M*i+j])
            for ele in log2_bit_list:
                res = (res << 1) | ele
            sent_symb = res
        s_x = LUT1[sent_symb]

        # channel
        r_x = s_x + np.random.normal(0, sigma) #generate noise n with variance sigmaˆ2 in each coordinate direction

        # receiver
        if r_x > tau:
            shat = 1
        else:
            shat = 0
        if(shat != sent_symb):
            symbolerrorcount += 1
            biterrorcount += LOG2M
            print("***symbolerrorcnt is ", symbolerrorcount)

    print("Ones sent is ", ones_sent)
    print("Zeroes sent is ", zeros_sent)
    print("P_0 is ", zeros_sent/(ones_sent+zeros_sent))
    Psymerror = symbolerrorcount/numsymbols
    Pbiterror = biterrorcount/numbits
    Psymerrorlist_0_1.append(Psymerror) #Save Psymerror in an array for plotting
    Pbiterrorlist_0_1.append(Pbiterror) #Save Pbiterror in an array for plotting
    theoretical_0_1.append(qfunc((tau + np.sqrt(Eb))/sigma)*P_0 + qfunc((np.sqrt(Eb)-tau)/sigma)*P_1)
    #theoretical.append(qfunc(np.sqrt(2*(LOG2M*Eb)/(N0))))
print("Exited loop")


plt.figure(1); plt.clf()
plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), Psymerrorlist_0_5)
#plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), theoretical_0_5)
plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), Psymerrorlist_0_25)
#plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), theoretical_0_25)
plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), Psymerrorlist_0_1)
#plt.semilogy(range(startSNRdB,endSNRdB,SNRdBstep), theoretical_0_1)
#plt.axvline(x=9.6, color = 'r')
#plt.legend(["P_0 = 0.5 Bit Error vs SNR", "P_0 = 0.5 Theoretical", "P_0 = 0.25 Bit Error vs SNR", "P_0 = 0.25 Theoretical", "P_0 = 0.1 Bit Error vs SNR", "P_0 = 0.1 Theoretical"], loc="upper right")
plt.legend(["P_0 = 0.5", "P_0 = 0.25", "P_0 = 0.1"], loc="upper right")
plt.xlabel("Eb/N0  (dB)")
plt.ylabel("Pb")
plt.show()
