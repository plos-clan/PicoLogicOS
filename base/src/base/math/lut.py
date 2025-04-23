import math

print('sin')
print(','.join([f'{math.sin(x / 128 * 2 * math.pi):.8f}f' for x in range(128)]))

print('cos')
print(','.join([f'{math.cos(x / 128 * 2 * math.pi):.8f}f' for x in range(128)]))

print('tan')
print(','.join([f'{math.tan(x / 128 * 2 *  math.pi):.8f}f' for x in range(128)]))
