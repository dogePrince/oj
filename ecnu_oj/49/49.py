end = 10**12
start = end - 10**6
sum = 0

def is_su(num):
    sub_end = int(num**0.5) + 1
    for i in range(2, sub_end):
        if num % i == 0:
            return False
    return True

for i in range(start, end):
    print(i)
    if is_su(i):
        sum += i

print(sum)
