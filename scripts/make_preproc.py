import statistics as stat
from math import sqrt


def my_rse(data):
    avg = sum(data) / len(data)
    s_sq = 0
    for i in range(len(data)):
        s_sq += (data[i] - avg) * (data[i] - avg)
    s_sq /= len(data) - 1

    s = sqrt(s_sq)
    std_err = s / sqrt(len(data))
    rse = (std_err / avg) * 100
    return rse


with open('../config/sizes_of_arr.txt') as config_sizes:
    sizes = config_sizes.readline().split()

for name in ["main_index", "main_pointer_index", "main_pointer"]:
    for type in ["in", "out"]:
        for size in sizes:
            data = [float(i) for i in open(f'../data/{name}_{type}_{size}.txt').readlines()]
            data_new = [data[0]] + [data[i] for i in range(1, len(data)) if my_rse(data[:i + 1]) > 1.0]
            if len(data_new) == 1:
                print(f"{size} {stat.mean(data[:2]) / 10**6:.2f} {2} {my_rse(data[:2]):.2f}")
            else:
                print(f"{size} {stat.mean(data_new) / 10**6:.2f} {len(data_new)} {my_rse(data_new):.2f}")
            with open(f'../preproc_data/{name}_{type}.txt', 'a') as output:
                output.write(f"{size} ")
                output.write(f"{stat.mean(data_new)} ")
                output.write(f"{max(data_new)} ")
                output.write(f"{min(data_new)} ")
                if len(data_new) == 1:
                    output.write(f"{data_new[0]} ")
                    output.write(f"{data_new[0]} ")
                    output.write(f"{data_new[0]}\n")
                else:
                    output.write(f"{stat.quantiles(data=data_new, n=4)[0]} ")
                    output.write(f"{stat.quantiles(data=data_new, n=4)[1]} ")
                    output.write(f"{stat.quantiles(data=data_new, n=4)[2]}\n")