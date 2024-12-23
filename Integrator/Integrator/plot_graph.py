import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import interp1d

tolerances = []
subintervals = []
results = []
errors = []
with open('plot_data.txt', 'r') as file:
    for line in file:
        data = line.split()
        tolerances.append(float(data[0]))
        subintervals.append(int(data[1]))
        results.append(float(data[2]))
        errors.append(float(data[3]))

log_tolerances = np.log10(tolerances)
log_errors = np.log10(errors)

f = interp1d(log_tolerances, log_errors, kind='linear')

x_new_log = np.linspace(min(log_tolerances), max(log_tolerances), 500)
y_new_log = f(x_new_log)

x_new = 10**x_new_log
y_new = 10**y_new_log

plt.figure(figsize=(10, 6))
plt.plot(x_new, y_new, '-', color='b', label="Interpolated Error")
plt.plot(tolerances, errors, 'o', color='b', label="Data points")
plt.xscale('log') 
plt.yscale('log') 
plt.xlabel("Tolerance")
plt.ylabel("Error (%)")
plt.title("Plot of Error vs Tolerance for Adaptive Simpson's Integration", 
          fontsize=16, fontweight='bold')
plt.legend()
plt.grid(True)
plt.show()