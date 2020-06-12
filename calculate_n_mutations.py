# what population we want to include
# For example, if we want to compute the probability that the the top and bottom 10% is included
# in our sample, then use 0.1
threshold = 0.25

# What is the probability we are aiming for
probability_goal = 0.9

def include_top_and_bottom_prob(n_choose):
    include_top_or_bottom = 1 - ((1 - threshold*2)**n_choose)
    include_top_only = 1 - ((1-threshold)**n_choose)
    include_bottom_only = include_top_only
    include_both = include_top_or_bottom - include_top_only - include_bottom_only
    print(n_choose, include_top_or_bottom, include_top_only, include_bottom_only, -include_both)
    return -include_both

for n in range(100):
    include_both = include_top_and_bottom_prob(n)
    if include_both > probability_goal:
        print(f'We need {n} samples to include the top and bottom {threshold * 100}% with rate {probability_goal * 100}% of the time')
        break
