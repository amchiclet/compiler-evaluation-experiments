import math
import random
from loguru import logger
def find_iteration_attributes(n):
    # Requirement 1: GCD(offset, period) must be 1

    # First, find the smallest 2^x that's greater than n
    # We are doing this because the only prime factor of m would be 2
    # When the only prime factor is 2, it's easy to find other attributes
    period = 1
    while period < n:
        period *= 2

    # Since period is an even number,
    # any odd number would satisfy requirement 1
    offset = period // 2
    if offset % 2 == 0:
        offset += 1

    # Requirement 2:
    # Let b = coeff - 1
    # b must be a multiple of every prime factors
    # The only prime factor is 2, so any even number works
    # let's just use 4
    b = 4

    # Requirement 3: if m is a multiple of 4, then b must be too
    # b is already 4, so nothing to do here
    coeff = b + 1
    return coeff, offset, period

class Sampler:
    def __init__(self, n):
        coeff, offset, period = find_iteration_attributes(n)
        self.update = lambda x : (x * coeff + offset) % period
        self.period = period
        self.n = n
        logger.info(f'{coeff}*x + {offset} with period {period} with n {n}')
    def iterate(self):
        x = random.randint(0, self.period-1)
        for i in range(self.period):
            x = self.update(x)
            if x < self.n:
                yield x
