import matplotlib.pyplot as plt

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

plt.figure(figsize=(10, 6))

plt.plot(tolerances, errors, marker='o', linestyle='-', color='b', label="Error (%)")
plt.xscale('log') 
plt.yscale('log') 

plt.xlabel("Tolerance")
plt.ylabel("Error (%)")
plt.title("Plot of Error vs Tolerance for Adaptive Simpson's Integration", fontsize=16, fontweight='bold')

plt.legend()
plt.show()