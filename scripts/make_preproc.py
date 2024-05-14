import numpy as np
import statistics as stat


def calculate_rse(data):
    mean_value = np.mean(data)
    std_dev = np.std(data)
    rse = std_dev / mean_value * 100
    return rse


with open('../config/sizes_of_arr.txt') as config_sizes:
    sizes = config_sizes.readline().split()


for name in ["main_index", "main_pointer_index", "main_pointer"]:
    for type in ["in", "out"]:
        for size in sizes:
            data = [float(i) for i in open(f'../data/{name}_{type}_{size}.txt').readlines()]
            data = [data[0]] + [data[i] for i in range(1, len(data)) if calculate_rse(data[:i + 1]) > 1.0]
            with open(f'../preproc_data/{name}_{type}.txt', 'a') as output:
                output.write(f"{size} ")
                output.write(f"{stat.mean(data)} ")
                output.write(f"{max(data)} ")
                output.write(f"{min(data)} ")
                if len(data) == 1:
                    output.write(f"{data[0]} ")
                    output.write(f"{data[0]} ")
                    output.write(f"{data[0]}\n")
                else:
                    output.write(f"{stat.quantiles(data=data, n=4)[0]} ")
                    output.write(f"{stat.quantiles(data=data, n=4)[1]} ")
                    output.write(f"{stat.quantiles(data=data, n=4)[2]}\n")