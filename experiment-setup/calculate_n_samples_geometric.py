from scipy.stats import t, tmean, gstd, tstd
from scipy import e, log
from math import sqrt

min_val = 0.01
max_val = 1.00
confidence_level = 0.99
margin_of_error_goal = 1.05

def margin_of_error(n, confidence_level, std):
    return t.ppf((1+confidence_level)/2, n-1) * std / sqrt(n)

def estimate_samples(confidence_level, min_val, max_val, goal, space):
    def max_std(n, min_val, max_val):
        n_first_half = n // 2
        n_second_half = n - n_first_half
        extreme_samples = [min_val] * n_first_half + [max_val] * n_second_half
        return tstd(extreme_samples)

    for n in space:
        std = max_std(n, min_val, max_val)
        moe = margin_of_error(n, confidence_level, std)
        if moe < goal:
            print(f'We need {n} samples for {confidence_level*100}% confidence '
                  f'for margin of error < {goal*100:.2f}% '
                  f'with range([{min_val}, {max_val}]) '
                  f'max standard deviation is {std:.2f}.')
            return n
    return None

def estimate_samples_geometric(confidence_level, min_val, max_val, goal, space):
    def max_gstd(n, min_val, max_val):
        n_first_half = n // 2
        n_second_half = n - n_first_half
        extreme_samples = [min_val] * n_first_half + [max_val] * n_second_half
        return gstd(extreme_samples)
    for n in space:
        std = log(max_gstd(n, min_val, max_val))
        moe = e**margin_of_error(n, confidence_level, std)
        if moe < goal:
            print(f'We need {n} samples for {confidence_level*100}% confidence '
                  f'for margin of error < {goal*100:.2f}% '
                  f'with range([{min_val}, {max_val}]) '
                  f'max standard deviation is {std:.2f}.')
            return n
    return None

n_samples = estimate_samples(0.99, 0, 1, 0.05, range(10, 100000, 10))
n_samples_geometric = estimate_samples_geometric(0.99, 0.01, 1.00, 1.05, range(10, 100000, 10))
print(n_samples_geometric)

moe = e**margin_of_error(700, 0.99, log(1.1))
print(moe)
print([0.8 / moe, 0.8 * moe])
