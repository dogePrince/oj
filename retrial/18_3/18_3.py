import sys
n = int(input())
nums = input()
num_set = nums.strip().split(' ')
num_set.sort(key=lambda x: int(x))
for num in num_set:
    sys.stdout.write(num + ' ')
sys.stdout.flush()
