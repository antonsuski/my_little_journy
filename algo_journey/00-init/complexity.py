import numpy as np
import math
import matplotlib.pyplot as plt
import operator
from functools import partial

Hz = 4.5 * 1e6 #cpu speed
inst_count = 500 #instractions count

time_type = ['second', 'minute', 'hour', 'day', 'month', 'year', 'century']
time_val = [1, 60, 60*60, 60*60*24, 60*60*24*30, 60*60*24*365, 60*60*24*36500]

def nlogn(n):
    return n*np.log(n)

def pow2(n):
    return math.pow(n, 2)

def pow3(n):
    return math.pow(n, 3)

def pow_of2(n):
    return math.pow(2, n)

functions = {'lg(n)': np.log, 'sqrt(n)': math.sqrt, 'n': np.abs, 'n lg(n)': nlogn, 'n^2': pow2, 'n^3': pow3}

def get_inst_seconds(method, frequency, n):
    return (method(n)/frequency)

print(get_inst_seconds(np.log, Hz, inst_count))

complexity_buffer = {}
for fn, fe in functions.items():
    buff = []
    for time in time_val:
        buff.append(fe(time))
    # complexity_buffer.append({fn: buff})
    complexity_buffer[fn] = buff
print(complexity_buffer)
x_range = 2**np.arange(1,8)
print(x_range)

for fn, buf in complexity_buffer.items():
    plt.plot(time_val, buf, label=fn)
    plt.ylim(0, 10000)
    plt.xlim(0, 10000)

plt.legend()
plt.show()
