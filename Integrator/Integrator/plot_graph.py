import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import interp1d

# Read configuration
with open('plot_config.txt', 'r') as config_file:
    title = config_file.readline().strip()
    function_name = config_file.readline().strip()

# Read data
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

# Convert lists to numpy arrays and take the log of the values
log_tolerances = np.log10(tolerances)
log_errors = np.log10(errors)

# Create interpolation function in log space
f = interp1d(log_tolerances, log_errors, kind='linear')

# Create more points for a smoother curve
x_new_log = np.linspace(min(log_tolerances), max(log_tolerances), 500)
y_new_log = f(x_new_log)

# Convert back from log space
x_new = 10**x_new_log
y_new = 10**y_new_log

plt.figure(figsize=(10, 6))
# Plot the smooth curve and the original points
plt.plot(x_new, y_new, '-', color='b', label="Interpolated Error")
plt.plot(tolerances, errors, 'o', color='b', label="Data points")
plt.xscale('log') 
plt.yscale('log') 
plt.xlabel("Tolerance")
plt.ylabel("Error (%)")
plt.title(f"{title}\n{function_name}", fontsize=16, fontweight='bold')
plt.legend()
plt.grid(True)
plt.show()