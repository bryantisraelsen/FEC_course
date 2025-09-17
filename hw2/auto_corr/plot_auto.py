import numpy as np
import matplotlib.pyplot as plt

# Load the data (one float per line)
y = np.loadtxt("output.txt")

# X axis from -15 to (len(y)-16)
x = np.arange(-15, -15 + len(y))

# Plot
plt.figure(figsize=(8, 4))
plt.stem(x, y, basefmt="k-")  # works on all matplotlib versions

plt.xlabel("Tau")
plt.ylabel("Value")
plt.title("Autocorrelation")
plt.grid(True)
plt.show()
