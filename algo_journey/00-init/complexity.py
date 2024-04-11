import numpy as np
import math
import matplotlib.pyplot as plt

Hz = 4.5 * 1e6 #cpu speed
inst_count = 500 #instractions count

time_type = ['second', 'minute', 'hour', 'day', 'month', 'year', 'century']
time_val = [1, 60, 60*60, 60*60*24, 60*60*24*30, 60*60*24*365, 60*60*24*36500]
function = ['lg(n)', 'sqrt(n)', 'n', 'n lg(n)', 'n^2', 'n^3', '2^n', 'n!']

def get_inst_seconds(method, frequency, n):
    return (method(n)/frequency)

print(get_inst_seconds(np.log, Hz, inst_count))

complexity_buffer = []
for i in range(len(time_type[:7])):
    buff = []
    val = time_val[i]
    buff.append(0)
    buff.append(np.log(val))
    buff.append(math.sqrt(val))
    buff.append(val)
    buff.append(val * np.log(val))
    buff.append(val ** 2)
    buff.append(val ** 3)
    #buff.append(2 ** val)
    #buff.append(math.factorial(val)) it is too long to count this sheet
    complexity_buffer.append(buff)

print(complexity_buffer)

x = time_val[:7]
plt.plot(x,complexity_buffer[0])
plt.show()
