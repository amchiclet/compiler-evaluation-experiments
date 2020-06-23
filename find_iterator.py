import math
import random

def find_iteration_attributes(n):
    # Find the smallest 2^x that's greater than n
    # We are doing this because the only prime factor of m would be 2
    # When the only prime factor is 2, it's easy to find other attributes
    period = 1
    while period < n:
        period *= 2
    # Requirement 1: GCD(offset, m) must be 1
    # Any odd number would do
    offset = (period // 2) + 1

    # Define b = coeff - 1
    # Requirement 2: b must be a multiple of every prime factors
    # The only prime factor is 2, so any even number works
    # let's just use 4
    b = 4

    # Requirement 3: if m is a multiple of 4, then b must be too
    # b is already 4, so nothing to do here
    coeff = b + 1
    return coeff, offset, period

coeff, offset, period = find_iteration_attributes(1000)
print(coeff, offset, period)

s = set()
x = random.randint(0, period-1)
xs = []
for i in range(period):
    x = (coeff*x + offset) % period
    xs.append(x)
    s.add(x)

print(len(s))
print(xs)
