import functools
n = int(input())
num_set = input().strip().split(' ')
def mcmp(a, b):
    i = 0
    len_a = len(a)
    len_b = len(b)
    while i<len_a and i<len_b and a[i] == b[i]:
        i += 1
    if i==len_a or i==len_b:
        if i==len_a and i==len_b:
            return True
        elif i==len_a:
            return mcmp(a, b[i:])
        else:
            return mcmp(a[i:], b)
    else:
        return a[i] < b[i]

num_set.sort(key=functools.cmp_to_key(mcmp))
print(num_set)
