import time
import sys

def set_base_down(base, down, n):
    for i in range(0, (n+1)//2 + 1):
        base[i] = (n-i)*4*i+1

    for i in range(0, (n+1)//2):
        down[i] = base[i+1]+base[i]+n-2*i-1


def plus(i, n, base, down):
    sum = 0
    j = 0
    if i < (n+1)//2:
        r_i = i
    else:
        r_i = n-i-1

    while j < r_i:
        sum += down[j]
        j += 1

    if i < (n+1)//2:
        sum += (base[i]*2 + n - 1 - 2*i) * (n-2*i)//2
    else:
        sum += down[r_i]  * (n-2*r_i)// 2
    return sum

def cut(i, j, n, base, down):
    if not -2 < i-j < 2:
        low = plus(i, n, base, down)
        high = plus(j, n, base, down)
        if low > high:
            print(i, ":\t", low)
            cut(i, (i+j)//2, n, base, down)
        else:
            print(j, ":\t", high)
            cut((i+j)//2, j, n, base, down)


if __name__=="__main__":
    n = int(sys.argv[1])
    i = int(sys.argv[2])
    base = [None]*((n+1)/2 + 1)
    down = [None]*((n+1)/2)
    set_base_down(base, down, n)
    #
    # cut(0, n-1, n, base, down)

    # max = 0
    # for i in range(0, n):
    #     a = plus(i, n, base, down)
    #     if a > max:
    #         max = a;
    #         print(max)

    print(plus(i, n, base, down))
