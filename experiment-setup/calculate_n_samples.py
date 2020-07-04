from scipy.stats import t
from math import sqrt

standard_deviation = 0.5
confidence_level = 0.99

margin_of_error_goal = 0.05

def margin_of_error(n):
    return t.ppf((1+confidence_level)/2, n) * standard_deviation / sqrt(n)

for n in range(10, 100000, 10):
    if margin_of_error(n) < margin_of_error_goal:
        print(f'We need {n} samples for {confidence_level*100}% confidence for margin of error < {margin_of_error_goal*100}% assuming standard deviation is {standard_deviation}.')
        break

