import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import interp1d
import sys

def create_plot(config_file_name):
    with open(config_file_name, 'r') as config_file:
        title = config_file.readline().strip()
        function_name = config_file.readline().strip()

    data_file_name = config_file_name.replace('config', 'data')

    # Read data
    tolerances = []
    subintervals = []
    results = []
    errors = []

    with open(data_file_name, 'r') as file:
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
    plt.title(f"{title}\n{function_name}", fontsize=16, fontweight='bold')
    plt.legend()
    plt.grid(True)
    
    plot_name = config_file_name.replace('config', 'result').replace('.txt', '.png')
    plt.savefig(plot_name)
    plt.show()  
    plt.close()

def main():
    config_file_name = sys.argv[1] if len(sys.argv) > 1 else 'plot_config_simpson.txt'
    create_plot(config_file_name)

if __name__ == "__main__":
    main()